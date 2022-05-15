#pragma once
#include "Core.h"
#include "Synchronize.h"
#include <Windows.h>

#include <new.h>
//实现一套自己的内存管理机制，最好要重载全局operator MATRIX_NEW函数，好处是能使整个项目统一，查找内存分配情况和处理 bug 都相对容易
//去除C4595 编译警告，Visual Studio 2015开始会对inline operator new操作进行警告 （避免无意中引入全局new操作，出了问题极其难以定位）
//相关链接： https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-by-compiler-version?view=msvc-170
#pragma warning(disable : 4595)
#define MX_NEW new
#define MX_DELETE delete
#define USE_MATRIX_NEW
//使用宏定义处理这些容易忘记的指针删除操作
#define ENGINE_DELETE(p) \
    if (p)               \
    {                    \
        delete p;        \
        p = 0;           \
    }
#define MX_ENGINE_DELETEA(p) \
    if (p)                   \
    {                        \
        delete[] p;          \
        p = 0;               \
    }
#define ENGINE_DELETEAB(p, num)       \
    if (p)                            \
    {                                 \
        for (int i = 0; i < num; i++) \
            MX_ENGINE_DELETEA(p[i]);  \
        MX_ENGINE_DELETEA(p);         \
    }

namespace Matrix
{
    namespace Core
    {

        //引擎的内存管理模块： 1.高效的管理自己的内存  2.避免出现内存泄漏
        class MATRIX_CORE_API BaseMemoryManager
        {
        public:
            BaseMemoryManager();
            virtual ~BaseMemoryManager() = 0;
            //内存分配
            virtual void *Allocate(USIZE_TYPE uSize, USIZE_TYPE uiAlignment, bool bIsArray) = 0;
            //内存管理
            virtual void Deallocate(char *pcAddr, USIZE_TYPE uiAlignment, bool bIsArray) = 0;

            static MXCriticalSection msMemLock;
            static void printInfo();
        };

        class MATRIX_CORE_API CMemoryManager : public BaseMemoryManager
        {
        public:
            CMemoryManager();
            ~CMemoryManager();
            virtual void *Allocate(USIZE_TYPE uSize, USIZE_TYPE uiAlignment, bool bIsArray);
            virtual void Deallocate(char *pcAddr, USIZE_TYPE uiAlignment, bool bIsArray);
        };

        //===========================堆内存管理====================================
#if !_DEBUG && !_WIN64
        //采用虚幻3的内存管理代码删改而成
        class MATRIX_CORE_API UEWin32MemoryAlloc : public BaseMemoryManager
        {
        public:
            UEWin32MemoryAlloc();
            ~UEWin32MemoryAlloc();

            virtual void *Allocate(USIZE_TYPE uSize, USIZE_TYPE uiAlignment, bool bIsArray) override;
            //取消已经分配的block
            virtual void Deallocate(char *pcAddr, USIZE_TYPE uiAlignment, bool bIsArray) override;

        private:
            // Counts.
            enum
            {
                POOL_CATEGORY = 42
            };
            enum
            {
                POOL_MAX = 32768 + 1
            };
            // Forward declares.
            struct FPoolInfo;
            struct FFreeBlock;

            FPoolInfo *CreateIndirect();

        private:
            //链表管理者
            struct FPoolTable
            {
                unsigned int BlockSize;   //每次可以分配的内存大小,poolinfo中单独内存块的大小
                FPoolInfo *ExhaustedPool; //分配完的 PoolInfo 链表头指针
                FPoolInfo *FirstPool;     //没有分配完的 PoolInfo 链表头指针
            };

            struct FPoolInfo
            {
                // FPoolInfo* Pre; //指向自己前一个节点
                //于 PreLink 为什么是指针的指针，其实这种方式从一个链表中删除，无须知道当前链表的头指针
                FPoolInfo **PrevLink;
                FPoolInfo *Next;    //指向自己的后一个节点
                FPoolTable *Owner;  //属于哪个链表管理者
                void *MemoryAddr;   //指向 32 位 Windows 系统分配空间的首地址
                unsigned int Taken; //每分配一次就加 1，释放一次就减 1，如果释放后为 0，那么就把 Mem 指向的内存空间还给 32 位 Windows 系统
                FFreeBlock *pAvailableBlock;
                // Fpoolinfo link 到参数中，所以需要使用引用传参，head是指向指针的指针。
                //将this插入到链表头结点。

                DWORD Bytes;   // Bytes allocated for pool.
                DWORD OsBytes; // Bytes aligned to page size.

                void Link(FPoolInfo *&Head)
                {
                    if (Head)
                    {
                        Head->PrevLink = &(this->Next);
                    }
                    this->Next = Head;
                    PrevLink = &Head;
                    Head = this;
                }
                void Unlink()
                {
                    if (Next)
                    {
                        Next->PrevLink = PrevLink;
                    }
                    *PrevLink = Next;
                }
            };
            // FreeMem的大小是8字节，可以和一个block单元公用，因为未分配才需要freemem记录，已经分配的不需要Freemem记录。
            struct FFreeBlock
            {
                FFreeBlock *Next; //在同一个 PoolInfo 中，下一个可用的单元
                DWORD Blocks;     //还剩下多少可用单元
                FPoolInfo *GetPool()
                {
                    //在Poolinfo中的任意一个地址取出高17位就可以定位这个Poolinfo
                    //因为M 为 32KB，即低15位为块内地址
                    return (FPoolInfo *)((INT)this & 0xffff8000);
                }
            };

            FPoolTable PoolTable[POOL_CATEGORY];
            FPoolTable OsTable;
            FPoolInfo *PoolIndirect[32];
            FPoolTable *MemSizeToPoolTable[POOL_MAX];
            INT PageSize;
        };

#elif _DEBUG
        //采用浮动大小的block块，BeginMask 和 EndMask隔离
        class MATRIX_CORE_API DebugMemoryAlloc : public BaseMemoryManager
        {
        public:
            DebugMemoryAlloc();
            ~DebugMemoryAlloc();

            // uSize 是这次申请的字节数
            virtual void *Allocate(USIZE_TYPE uSize, USIZE_TYPE uiAlignment, bool bIsArray) override;
            virtual void Deallocate(char *pcAddr, USIZE_TYPE uiAlignment, bool bIsArray) override;

        private:
            enum BLOCKMARK
            {
                BEGIN_MASK = 0xDEADC0DE,
                END_MASK = 0xDEADC0DE,
                RECORD_NUM = 32, //必须大于2
                CALLSTACK_NUM = 32
            };

            class Block
            {
            public:
                Block()
                {
                    for (size_t i = 0; i < CALLSTACK_NUM; i++)
                    {
                        pStackAddr[i] = NULL;
                    }
                    pPrev = NULL;
                    pNext = NULL;
                    mbAlignment = false;
                    mbArray = false;
                    mSize = 0;
                    mStackInfoNum = 0;
                }

                void *pStackAddr[CALLSTACK_NUM]; //申请内存时候的调用堆栈信息
                unsigned int mStackInfoNum;      //堆栈层数
                USIZE_TYPE mSize;                //申请空间的大小
                bool mbArray;                    //是否是数组
                bool mbAlignment;                //是否字节对齐
                Block *pPrev;                    //前一个节点
                Block *pNext;                    //后一个节点
            };

            Block *pHead;
            Block *pTail;
            unsigned int mNumNewCalls;            //调用 MATRIX_NEW 的次数
            unsigned int mNumDeleteCalls;         //调用 delete 的次数
            unsigned int mNumBlocks;              //当前有多少内存块
            unsigned int mNumBytes;               //当前有多少字节
            unsigned int mMaxNumBytes;            //最多申请多少字节
            unsigned int mMaxNumBlocks;           //最多申请多少内存块
            unsigned int mSizeRecord[RECORD_NUM]; //统计内存在2的n次方的分布情况。
            void InsertBlock(Block *pBlock);
            //仅仅负责移除，不做内存释放处理
            void RemoveBlock(Block *pBlock);

            bool GetFileAndLine(const void *pAddress, TCHAR szFile[MAX_PATH], int &line);
            //依靠 动态链接库dbhelp.dll 了。这个可以根据当前指令所在代码段中的地址打印出这行代码所在行数和文件路径的函数
            bool InitDbgHelpLib();
            void FreeLeakMem();
            void PrintInfo();
            void FreeDbgHelpLib();
        };
#else
        class MATRIX_CORE_API Win64MemoryAlloc : public BaseMemoryManager
        {
        public:
            Win64MemoryAlloc();
            ~Win64MemoryAlloc();

            virtual void *Allocate(USIZE_TYPE uSize, USIZE_TYPE uiAlignment, bool bIsArray) override;
            virtual void Deallocate(char *pcAddr, USIZE_TYPE uiAlignment, bool bIsArray) override;
        };
#endif

        //==============================栈内存管理===============================
        //栈内存管理， 参考UE的代码设计， 没有考虑线程安全，每帧都会清理

        class MATRIX_CORE_API StackMemoryManager : public BaseMemoryManager
        {
        public:
            //默认分配
            StackMemoryManager(USIZE_TYPE uiDefaultChunkSize = 65536);
            ~StackMemoryManager();

            virtual void *Allocate(USIZE_TYPE uSize, USIZE_TYPE uiAlignment, bool bIsArray) override;
            //栈内存无须主动释放，出栈即消亡（其实真正的释放操作还是由heap memory manager决定）
            virtual void Deallocate(char *pcAddr, USIZE_TYPE uiAlignment, bool bIsArray) override;

            //每帧结束或者开始的时候调用,释放所有
            void Clear();

            template <class T>
            friend class StackMemoryAdaptor;
            friend class StackMemTag;

        private:
            // Chunk 指针结构
            struct FTaggedMemory
            {
                FTaggedMemory *Next;
                USIZE_TYPE DataSize;
                BYTE Data[1];
            };

            BYTE *Top;                   //当前 Chunk块内栈头
            BYTE *End;                   //当前 Chunk块内栈尾
            USIZE_TYPE DefaultChunkSize; //默认每次分配最大 Size
            FTaggedMemory *TopChunk;     //当前已分配 Chunk 头指针
            FTaggedMemory *UnusedChunks; //当前空闲 Chunk 头指针(但是已经分配好了）

            /** The number of marks on this stack. */
            INT NumMarks;

            BYTE *AllocateNewChunk(USIZE_TYPE MinSize);
            //释放 NewTopChunk 到 TopChunk 的所有 Chunk
            void FreeChunks(FTaggedMemory *NewTopChunk);
        };

        //==============================以上为多平台的内存分配的设计实现====================================
        //=============================================================================================
        class MATRIX_CORE_API MemoryObject
        {
        public:
            MemoryObject();
            ~MemoryObject();

            static BaseMemoryManager &GetCMemoryManager();
            static BaseMemoryManager &GetMemoryManager();
            static StackMemoryManager &GetStackMemoryManager();
        };

        template <typename T>
        class StackMemoryAdaptor : public MemoryObject
        {
        public:
            //
            StackMemoryAdaptor(USIZE_TYPE uiNum = 0, USIZE_TYPE uiAlignment = 0)
            {
                if (uiNum > 0)
                {
                    StackMemoryManager &StackMem = GetStackMemoryManager();
                    mNum = uiNum;
                    Top = StackMem.Top;
                    SavedChunk = StackMem.TopChunk;
                    // track
                    StackMem.NumMarks++;
                    mPtr = (T *)StackMem.Allocate(uiNum * sizeof(T), uiAlignment, 0);
                    MX_ENGINE_ASSERT(mPtr);

                    //判断是否有构造函数，
                    if (ValueBase<T>::NeedsConstructor)
                    {
                        for (unsigned int i = 0; i < uiNum; i++)
                        {
                            //在当前内存地址中执行构造
                            MX_NEW(mPtr + i)
                            T();
                        }
                    }
                }
            }

            ~StackMemoryAdaptor()
            {
                if (mNum > 0)
                {
                    if (ValueBase<T>::NeedsDestructor)
                    {
                        for (unsigned int i = 0; i < mNum; i++)
                        {
                            (mPtr + i)->~T();
                        }
                    }
                }

                StackMemoryManager &StackMem = GetStackMemoryManager();
                // Track the number of outstanding marks on the stack.
                --StackMem.NumMarks;
                //释放 SavedChunk 前面的所有 Chunk 到空闲列表中
                if (SavedChunk != StackMem.TopChunk)
                {
                    StackMem.FreeChunks(SavedChunk);
                }
                //还原现场
                StackMem.Top = Top;
                Top = NULL;
            }

            //取得分配空间的指针
            inline T *GetPtr() const
            {
                return mPtr;
            }
            inline unsigned int GetNum() const
            {
                return mNum;
            }

        private:
            BYTE *Top;
            StackMemoryManager::FTaggedMemory *SavedChunk;
            T *mPtr;
            size_t mNum; //记录构造的数量
        };

        class StackMemTag : public MemoryObject
        {
        public:
            // Constructors.
            StackMemTag()
            {
                StackMemoryManager &StackMem = GetStackMemoryManager();
                StackMem.NumMarks++;
                Top = StackMem.Top;
                SavedChunk = StackMem.TopChunk;
            }

            /** Destructor. */
            ~StackMemTag()
            {

                StackMemoryManager &StackMem = GetStackMemoryManager();

                // Unlock any MATRIX_NEW chunks that were allocated.
                if (SavedChunk != StackMem.TopChunk)
                    StackMem.FreeChunks(SavedChunk);

                // Restore the memory stack's state.
                StackMem.Top = Top;
                StackMem.NumMarks--;
            }

        private:
            BYTE *Top;
            StackMemoryManager::FTaggedMemory *SavedChunk;
        };

        //内存分配器
        class MATRIX_CORE_API DefaultContainerMemoryAllocator
        {
        public:
            DefaultContainerMemoryAllocator()
            {
            }

            virtual ~DefaultContainerMemoryAllocator()
            {
            }

            virtual void *Allocate(USIZE_TYPE uSize, USIZE_TYPE uiAlignment, bool bIsArray)
            {
                return MemoryObject::GetMemoryManager().Allocate(uSize, uiAlignment, bIsArray);
            }
            virtual void Deallocate(char *pcAddr, USIZE_TYPE uiAlignment, bool bIsArray)
            {
                return MemoryObject::GetMemoryManager().Deallocate(pcAddr, uiAlignment, bIsArray);
            }
        };

    }
}

#define USE_MATRIX_NEW
#ifdef USE_MATRIX_NEW
inline void *operator new(size_t uSize)
{
    // Matrix::MXOutputDebugString(_T("operator MATRIX_NEW has been called!"));
    return Matrix::Core::MemoryObject::GetMemoryManager().Allocate(uSize, 0, false);
}
inline void *operator new[](size_t uSize)
{
    // Matrix::MXOutputDebugString(_T("operator MATRIX_NEW[] has been called!"));
    return Matrix::Core::MemoryObject::GetMemoryManager().Allocate(uSize, 0, true);
}
inline void operator delete(void *pvAddr)
{
    // Matrix::MXOutputDebugString(_T("operator delete has been called!"));
    return Matrix::Core::MemoryObject::GetMemoryManager().Deallocate((char *)pvAddr, 0, false);
}
inline void operator delete[](void *pvAddr)
{
    // Matrix::MXOutputDebugString(_T("operator delete[] has been called!"));
    return Matrix::Core::MemoryObject::GetMemoryManager().Deallocate((char *)pvAddr, 0, true);
}
#endif
