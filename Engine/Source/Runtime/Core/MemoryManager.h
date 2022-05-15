#pragma once
#include "Core.h"
#include "Synchronize.h"
#include <Windows.h>

#include <new.h>
//ʵ��һ���Լ����ڴ������ƣ����Ҫ����ȫ��operator MATRIX_NEW�������ô�����ʹ������Ŀͳһ�������ڴ��������ʹ��� bug ���������
//ȥ��C4595 ���뾯�棬Visual Studio 2015��ʼ���inline operator new�������о��� ����������������ȫ��new�������������⼫�����Զ�λ��
//������ӣ� https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-by-compiler-version?view=msvc-170
#pragma warning(disable : 4595)
#define MX_NEW new
#define MX_DELETE delete
#define USE_MATRIX_NEW
//ʹ�ú궨�崦����Щ�������ǵ�ָ��ɾ������
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

        //������ڴ����ģ�飺 1.��Ч�Ĺ����Լ����ڴ�  2.��������ڴ�й©
        class MATRIX_CORE_API BaseMemoryManager
        {
        public:
            BaseMemoryManager();
            virtual ~BaseMemoryManager() = 0;
            //�ڴ����
            virtual void *Allocate(USIZE_TYPE uSize, USIZE_TYPE uiAlignment, bool bIsArray) = 0;
            //�ڴ����
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

        //===========================���ڴ����====================================
#if !_DEBUG && !_WIN64
        //�������3���ڴ�������ɾ�Ķ���
        class MATRIX_CORE_API UEWin32MemoryAlloc : public BaseMemoryManager
        {
        public:
            UEWin32MemoryAlloc();
            ~UEWin32MemoryAlloc();

            virtual void *Allocate(USIZE_TYPE uSize, USIZE_TYPE uiAlignment, bool bIsArray) override;
            //ȡ���Ѿ������block
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
            //���������
            struct FPoolTable
            {
                unsigned int BlockSize;   //ÿ�ο��Է�����ڴ��С,poolinfo�е����ڴ��Ĵ�С
                FPoolInfo *ExhaustedPool; //������� PoolInfo ����ͷָ��
                FPoolInfo *FirstPool;     //û�з������ PoolInfo ����ͷָ��
            };

            struct FPoolInfo
            {
                // FPoolInfo* Pre; //ָ���Լ�ǰһ���ڵ�
                //�� PreLink Ϊʲô��ָ���ָ�룬��ʵ���ַ�ʽ��һ��������ɾ��������֪����ǰ�����ͷָ��
                FPoolInfo **PrevLink;
                FPoolInfo *Next;    //ָ���Լ��ĺ�һ���ڵ�
                FPoolTable *Owner;  //�����ĸ����������
                void *MemoryAddr;   //ָ�� 32 λ Windows ϵͳ����ռ���׵�ַ
                unsigned int Taken; //ÿ����һ�ξͼ� 1���ͷ�һ�ξͼ� 1������ͷź�Ϊ 0����ô�Ͱ� Mem ָ����ڴ�ռ仹�� 32 λ Windows ϵͳ
                FFreeBlock *pAvailableBlock;
                // Fpoolinfo link �������У�������Ҫʹ�����ô��Σ�head��ָ��ָ���ָ�롣
                //��this���뵽����ͷ��㡣

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
            // FreeMem�Ĵ�С��8�ֽڣ����Ժ�һ��block��Ԫ���ã���Ϊδ�������Ҫfreemem��¼���Ѿ�����Ĳ���ҪFreemem��¼��
            struct FFreeBlock
            {
                FFreeBlock *Next; //��ͬһ�� PoolInfo �У���һ�����õĵ�Ԫ
                DWORD Blocks;     //��ʣ�¶��ٿ��õ�Ԫ
                FPoolInfo *GetPool()
                {
                    //��Poolinfo�е�����һ����ַȡ����17λ�Ϳ��Զ�λ���Poolinfo
                    //��ΪM Ϊ 32KB������15λΪ���ڵ�ַ
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
        //���ø�����С��block�飬BeginMask �� EndMask����
        class MATRIX_CORE_API DebugMemoryAlloc : public BaseMemoryManager
        {
        public:
            DebugMemoryAlloc();
            ~DebugMemoryAlloc();

            // uSize �����������ֽ���
            virtual void *Allocate(USIZE_TYPE uSize, USIZE_TYPE uiAlignment, bool bIsArray) override;
            virtual void Deallocate(char *pcAddr, USIZE_TYPE uiAlignment, bool bIsArray) override;

        private:
            enum BLOCKMARK
            {
                BEGIN_MASK = 0xDEADC0DE,
                END_MASK = 0xDEADC0DE,
                RECORD_NUM = 32, //�������2
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

                void *pStackAddr[CALLSTACK_NUM]; //�����ڴ�ʱ��ĵ��ö�ջ��Ϣ
                unsigned int mStackInfoNum;      //��ջ����
                USIZE_TYPE mSize;                //����ռ�Ĵ�С
                bool mbArray;                    //�Ƿ�������
                bool mbAlignment;                //�Ƿ��ֽڶ���
                Block *pPrev;                    //ǰһ���ڵ�
                Block *pNext;                    //��һ���ڵ�
            };

            Block *pHead;
            Block *pTail;
            unsigned int mNumNewCalls;            //���� MATRIX_NEW �Ĵ���
            unsigned int mNumDeleteCalls;         //���� delete �Ĵ���
            unsigned int mNumBlocks;              //��ǰ�ж����ڴ��
            unsigned int mNumBytes;               //��ǰ�ж����ֽ�
            unsigned int mMaxNumBytes;            //�����������ֽ�
            unsigned int mMaxNumBlocks;           //�����������ڴ��
            unsigned int mSizeRecord[RECORD_NUM]; //ͳ���ڴ���2��n�η��ķֲ������
            void InsertBlock(Block *pBlock);
            //���������Ƴ��������ڴ��ͷŴ���
            void RemoveBlock(Block *pBlock);

            bool GetFileAndLine(const void *pAddress, TCHAR szFile[MAX_PATH], int &line);
            //���� ��̬���ӿ�dbhelp.dll �ˡ�������Ը��ݵ�ǰָ�����ڴ�����еĵ�ַ��ӡ�����д��������������ļ�·���ĺ���
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

        //==============================ջ�ڴ����===============================
        //ջ�ڴ���� �ο�UE�Ĵ�����ƣ� û�п����̰߳�ȫ��ÿ֡��������

        class MATRIX_CORE_API StackMemoryManager : public BaseMemoryManager
        {
        public:
            //Ĭ�Ϸ���
            StackMemoryManager(USIZE_TYPE uiDefaultChunkSize = 65536);
            ~StackMemoryManager();

            virtual void *Allocate(USIZE_TYPE uSize, USIZE_TYPE uiAlignment, bool bIsArray) override;
            //ջ�ڴ����������ͷţ���ջ����������ʵ�������ͷŲ���������heap memory manager������
            virtual void Deallocate(char *pcAddr, USIZE_TYPE uiAlignment, bool bIsArray) override;

            //ÿ֡�������߿�ʼ��ʱ�����,�ͷ�����
            void Clear();

            template <class T>
            friend class StackMemoryAdaptor;
            friend class StackMemTag;

        private:
            // Chunk ָ��ṹ
            struct FTaggedMemory
            {
                FTaggedMemory *Next;
                USIZE_TYPE DataSize;
                BYTE Data[1];
            };

            BYTE *Top;                   //��ǰ Chunk����ջͷ
            BYTE *End;                   //��ǰ Chunk����ջβ
            USIZE_TYPE DefaultChunkSize; //Ĭ��ÿ�η������ Size
            FTaggedMemory *TopChunk;     //��ǰ�ѷ��� Chunk ͷָ��
            FTaggedMemory *UnusedChunks; //��ǰ���� Chunk ͷָ��(�����Ѿ�������ˣ�

            /** The number of marks on this stack. */
            INT NumMarks;

            BYTE *AllocateNewChunk(USIZE_TYPE MinSize);
            //�ͷ� NewTopChunk �� TopChunk ������ Chunk
            void FreeChunks(FTaggedMemory *NewTopChunk);
        };

        //==============================����Ϊ��ƽ̨���ڴ��������ʵ��====================================
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

                    //�ж��Ƿ��й��캯����
                    if (ValueBase<T>::NeedsConstructor)
                    {
                        for (unsigned int i = 0; i < uiNum; i++)
                        {
                            //�ڵ�ǰ�ڴ��ַ��ִ�й���
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
                //�ͷ� SavedChunk ǰ������� Chunk �������б���
                if (SavedChunk != StackMem.TopChunk)
                {
                    StackMem.FreeChunks(SavedChunk);
                }
                //��ԭ�ֳ�
                StackMem.Top = Top;
                Top = NULL;
            }

            //ȡ�÷���ռ��ָ��
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
            size_t mNum; //��¼���������
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

        //�ڴ������
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
