#pragma once
#include "MTXCore.h"
#include "MTXSynchronize.h"
#include <Windows.h>

//实现一套自己的内存管理机制，最好要重载全局new函数，好处是能使整个项目统一，查找内存分配情况和处理 bug 都相对容易
#include <new.h>
#define USE_STL_TYPE_TRAIT
#ifdef USE_STL_TYPE_TRAIT
// stl 类型萃取
#include <type_traits>
#endif // USE_STL_TYPE_TRAIT

namespace Matrix
{

#ifdef USE_STL_TYPE_TRAIT
	// C++ STL的std::is_trivially_constructible模板用于检查给定类型T是否是带有参数集的平凡可构造类型。
	//如果T是平凡可构造的类型，则它返回布尔值true，否则返回false。
#define HAS_TRIVIAL_CONSTRUCTOR(T) std::is_trivially_constructible<T>::value
#define HAS_TRIVIAL_DESTRUCTOR(T) std::is_trivially_destructible<T>::value
#define HAS_TRIVIAL_ASSIGN(T) std::is_trivially_assignable<T>::value
#define HAS_TRIVIAL_COPY(T) std::is_trivially_copyable<T>::value
#define IS_POD(T) std::is_pod<T>::value
#define IS_ENUM(T) std::is_enum<T>::value
#define IS_EMPTY(T) std::is_empty<T>::value

	// POD，是Plain Old Data的缩写，普通旧数据类型，是C++中的一种数据类型概念
	template <typename T>
	struct TIsPODType
	{
		enum
		{
			Value = IS_POD(T)
		};
	};

	template <typename T>
	struct ValueBase
	{
		enum
		{
			NeedsConstructor = !HAS_TRIVIAL_CONSTRUCTOR(T) && !TIsPODType<T>::Value
		};
		enum
		{
			NeedsDestructor = !HAS_TRIVIAL_DESTRUCTOR(T) && !TIsPODType<T>::Value
		};
	};

	//内存对齐
	template <class T>
	inline T Align(const T Ptr, USIZE_TYPE Alignment)
	{
		return (T)(((USIZE_TYPE)Ptr + Alignment - 1) & ~(Alignment - 1));
	}
	template <class T>
	inline T Align1(const T Ptr, USIZE_TYPE Alignment)
	{
		return (T)((USIZE_TYPE)Ptr + Alignment - (Ptr & (Alignment - 1)));
	}
#else
#endif
	//引擎的内存管理模块： 1.高效的管理自己的内存  2.避免出现内存泄漏
	class MATRIXCORE_API MTXMemManager
	{
	public:
		MTXMemManager();
		virtual ~MTXMemManager() = 0;

		//内存分配
		virtual void* Allocate(USIZE_TYPE uiSize, USIZE_TYPE uiAlignment, bool bIsArray) = 0;
		//内存管理
		virtual void Deallocate(char* pcAddr, USIZE_TYPE uiAlignment, bool bIsArray) = 0;

		static MTXCriticalSection msMemLock;
	};

	class MATRIXCORE_API MTXCMem : public MTXMemManager
	{
	public:
		MTXCMem();
		~MTXCMem();
		virtual void* Allocate(USIZE_TYPE uiSize, USIZE_TYPE uiAlignment, bool bIsArray);
		virtual void Deallocate(char* pcAddr, USIZE_TYPE uiAlignment, bool bIsArray);
	};

	//===========================堆内存管理====================================
#if !_DEBUG && !_WIN64
	//采用虚幻3的内存管理代码删改而成
	class MATRIXCORE_API MTXMemWin32 : public MTXMemManager
	{
	public:
		MTXMemWin32();
		~MTXMemWin32();

		virtual void* Allocate(USIZE_TYPE uiSize, USIZE_TYPE uiAlignment, bool bIsArray) override;
		//取消已经分配的block
		virtual void Deallocate(char* pcAddr, USIZE_TYPE uiAlignment, bool bIsArray) override;

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

		FPoolInfo* CreateIndirect();

	private:
		//链表管理者
		struct FPoolTable
		{
			unsigned int BlockSize;	  //每次可以分配的内存大小,poolinfo中单独内存块的大小
			FPoolInfo* ExhaustedPool; //分配完的 PoolInfo 链表头指针
			FPoolInfo* FirstPool;	  //没有分配完的 PoolInfo 链表头指针
		};

		struct FPoolInfo
		{
			// FPoolInfo* Pre; //指向自己前一个节点
			//于 PreLink 为什么是指针的指针，其实这种方式从一个链表中删除，无须知道当前链表的头指针
			FPoolInfo** PrevLink;
			FPoolInfo* Next;	//指向自己的后一个节点
			FPoolTable* Owner;	//属于哪个链表管理者
			void* MemoryAddr;	//指向 32 位 Windows 系统分配空间的首地址
			unsigned int Taken; //每分配一次就加 1，释放一次就减 1，如果释放后为 0，那么就把 Mem 指向的内存空间还给 32 位 Windows 系统
			FFreeBlock* pAvailableBlock;
			// Fpoolinfo link 到参数中，所以需要使用引用传参，head是指向指针的指针。
			//将this插入到链表头结点。

			DWORD Bytes;   // Bytes allocated for pool.
			DWORD OsBytes; // Bytes aligned to page size.

			void Link(FPoolInfo*& Head)
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
			FFreeBlock* Next; //在同一个 PoolInfo 中，下一个可用的单元
			DWORD Blocks;	  //还剩下多少可用单元
			FPoolInfo* GetPool()
			{
				//在Poolinfo中的任意一个地址取出高17位就可以定位这个Poolinfo
				//因为M 为 32KB，即低15位为块内地址
				return (FPoolInfo*)((INT)this & 0xffff8000);
			}
		};

		FPoolTable PoolTable[POOL_CATEGORY];
		FPoolTable OsTable;
		FPoolInfo* PoolIndirect[32];
		FPoolTable* MemSizeToPoolTable[POOL_MAX];
		INT PageSize;
	};

#elif _DEBUG
	//采用浮动大小的block块，BeginMask 和 EndMask隔离 
	class MATRIXCORE_API MTXDebugMem : public MTXMemManager
	{
	public:
		MTXDebugMem();
		~MTXDebugMem();

		// uiSize 是这次申请的字节数
		virtual void* Allocate(USIZE_TYPE uiSize, USIZE_TYPE uiAlignment, bool bIsArray) override;
		virtual void Deallocate(char* pcAddr, USIZE_TYPE uiAlignment, bool bIsArray) override;

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

			void* pStackAddr[CALLSTACK_NUM]; //申请内存时候的调用堆栈信息
			unsigned int mStackInfoNum;		 //堆栈层数
			USIZE_TYPE mSize;				 //申请空间的大小
			bool mbArray;					 //是否是数组
			bool mbAlignment;				 //是否字节对齐
			Block* pPrev;					 //前一个节点
			Block* pNext;					 //后一个节点
		};

		Block* pHead;
		Block* pTail;
		unsigned int mNumNewCalls;			  //调用 new 的次数
		unsigned int mNumDeleteCalls;		  //调用 delete 的次数
		unsigned int mNumBlocks;			  //当前有多少内存块
		unsigned int mNumBytes;				  //当前有多少字节
		//unsigned int mMaxNumBytes;			  //todo：最多申请多少字节
		//unsigned int mMaxNumBlocks;			  //todo：最多申请多少内存块，暂无控制含义
		unsigned int mSizeRecord[RECORD_NUM]; //统计内存在2的n次方的分布情况。
		void InsertBlock(Block* pBlock);
		//仅仅负责移除，不做内存释放处理
		void RemoveBlock(Block* pBlock);

		bool GetFileAndLine(const void* pAddress, TCHAR szFile[MAX_PATH], int& line);
		//依靠 动态链接库dbhelp.dll 了。这个可以根据当前指令所在代码段中的地址打印出这行代码所在行数和文件路径的函数
		bool InitDbgHelpLib();
		void FreeLeakMem();
		void PrintInfo();
		void FreeDbgHelpLib();
	};
#else
	class MATRIXCORE_API MTXMemWin64 : public MTXMemManager
	{
	public:
		MTXMemWin64();
		~MTXMemWin64();

		virtual void* Allocate(USIZE_TYPE uiSize, USIZE_TYPE uiAlignment, bool bIsArray) override;
		virtual void Deallocate(char* pcAddr, USIZE_TYPE uiAlignment, bool bIsArray) override;
	};
#endif

	//==============================栈内存管理===============================
	//栈内存管理， 参考UE的代码设计， 没有考虑线程安全，每帧都会清理
	class MATRIXCORE_API MTXStackMem : public MTXMemManager
	{
	public:
		//默认分配
		MTXStackMem(USIZE_TYPE uiDefaultChunkSize = 65536);
		~MTXStackMem();

		virtual void* Allocate(USIZE_TYPE uiSize, USIZE_TYPE uiAlignment, bool bIsArray) override;
		//栈内存无须主动释放，出栈即消亡
		virtual void Deallocate(char* pcAddr, USIZE_TYPE uiAlignment, bool bIsArray) override;

		//每帧结束或者开始的时候调用,释放所有
		void Clear();

		template <class T>
		friend class MTXStackMemAlloc;
		friend class MTXStackMemTag;

	private:
		// Chunk 指针结构
		struct FTaggedMemory
		{
			FTaggedMemory* Next;
			USIZE_TYPE DataSize;
			BYTE Data[1];
		};

		BYTE* Top;					 //当前 Chunk块内栈头
		BYTE* End;					 //当前 Chunk块内栈尾
		USIZE_TYPE DefaultChunkSize; //默认每次分配最大 Size
		FTaggedMemory* TopChunk;	 //当前已分配 Chunk 头指针
		FTaggedMemory* UnusedChunks; //当前空闲 Chunk 头指针(但是已经分配好了）

		/** The number of marks on this stack. */
		INT NumMarks;

		BYTE* AllocateNewChunk(USIZE_TYPE MinSize);
		//释放 NewTopChunk 到 TopChunk 的所有 Chunk
		void FreeChunks(FTaggedMemory* NewTopChunk);
	};

	//==============================以上为多平台的内存分配的设计实现====================================
	//=============================================================================================
	class MATRIXCORE_API MMemObject
	{
	public:
		MMemObject();
		~MMemObject();

		static MTXStackMem& GetStackMemManager();
		static MTXMemManager& GetMemManager();
		static MTXMemManager& GetCMemManager();
	};

	template <typename T>
	class MTXStackMemAlloc : public MMemObject
	{
	public:
		//
		MTXStackMemAlloc(USIZE_TYPE uiNum = 0, USIZE_TYPE uiAlignment = 0)
		{
			if (uiNum > 0)
			{
				MTXStackMem& StackMem = GetStackMemManager();
				mNum = uiNum;
				Top = StackMem.Top;
				SavedChunk = StackMem.TopChunk;
				// track
				StackMem.NumMarks++;
				mPtr = (T*)StackMem.Allocate(uiNum * sizeof(T), uiAlignment, 0);
				MTXENGINE_ASSERT(mPtr);

				//判断是否有构造函数，
				if (ValueBase<T>::NeedsConstructor)
				{
					for (unsigned int i = 0; i < uiNum; i++)
					{
						//在当前内存地址中执行构造
						new (mPtr + i) T();
					}
				}
			}
		}

		~MTXStackMemAlloc()
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
			MTXStackMem& StackMem = GetStackMemManager();
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
		inline T* GetPtr() const
		{
			return mPtr;
		}
		inline unsigned int GetNum() const
		{
			return mNum;
		}

	private:
		BYTE* Top;
		MTXStackMem::FTaggedMemory* SavedChunk;
		T* mPtr;
		size_t mNum; //记录构造的数量
	};

	class MTXStackMemTag : public MMemObject
	{
	public:
		// Constructors.
		MTXStackMemTag()
		{
			MTXStackMem& StackMem = GetStackMemManager();
			StackMem.NumMarks++;
			Top = StackMem.Top;
			SavedChunk = StackMem.TopChunk;
		}

		/** Destructor. */
		~MTXStackMemTag()
		{
			MTXStackMem& StackMem = GetStackMemManager();

			// Unlock any new chunks that were allocated.
			if (SavedChunk != StackMem.TopChunk)
				StackMem.FreeChunks(SavedChunk);

			// Restore the memory stack's state.
			StackMem.Top = Top;
			StackMem.NumMarks--;
		}

	private:
		BYTE* Top;
		MTXStackMem::FTaggedMemory* SavedChunk;
	};
}

#define USE_CUSTOM_NEW
#ifdef USE_CUSTOM_NEW
inline void* operator new(size_t uiSize)
{
	// Matrix::MTXOutputDebugString(_T("operator new has been called!"));
	return Matrix::MMemObject::GetMemManager().Allocate(uiSize, 0, false);
}
inline void* operator new[](size_t uiSize)
{
	// Matrix::MTXOutputDebugString(_T("operator new[] has been called!"));
	return Matrix::MMemObject::GetMemManager().Allocate(uiSize, 0, true);
}

inline void operator delete(void* pvAddr)
{
	// Matrix::MTXOutputDebugString(_T("operator delete has been called!"));
	return Matrix::MMemObject::GetMemManager().Deallocate((char*)pvAddr, 0, false);
}
inline void operator delete[](void* pvAddr)
{
	// Matrix::MTXOutputDebugString(_T("operator delete[] has been called!"));
	return Matrix::MMemObject::GetMemManager().Deallocate((char*)pvAddr, 0, true);
}
#endif // USE_CUSTOM_NEW


#define MTXENGINE_DELETE(p) if(p){delete p; p = 0;}
#define MTXENGINE_DELETEA(p) if(p){delete []p; p = 0;}
#define MTXENGINE_DELETEAB(p,num) if(p){ for(int i = 0 ; i < num ; i++) MTXENGINE_DELETEA(p[i]); MTXENGINE_DELETEA(p);}
	// use by inner mac
	template<typename T>
inline void MTXDelete(T*& p)
{
	if (p) { delete p; p = 0; }
}
template<typename T>
inline void MTXDeleteA(T*& p)
{
	if (p) { delete[]p; p = 0; }
}
template<typename T, typename N>
inline void MTXDeleteAB(T*& p, N num)
{
	if (p) { for (int i = 0; i < num; i++) MTXENGINE_DELETEA(p[i]); MTXENGINE_DELETEA(p); }
}

