#pragma once
#include "MTXCore.h"
#include "MTXSynchronize.h"

namespace Matrix
{
	//内存对齐
	template< class T > inline T Align(const T Ptr, USIZE_TYPE Alignment)
	{
		return (T)(((USIZE_TYPE)Ptr + Alignment - 1) & ~(Alignment - 1));

	}
	template< class T > inline T Align1(const T Ptr, USIZE_TYPE Alignment)
	{
		return (T)((USIZE_TYPE)Ptr + Alignment - (Ptr & (Alignment - 1)));
	}

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

		static MTXCriticalSection msMemlock;

	};

#if !_DEBUG && !_WIN64

	class MATRIXCORE_API  MTXMemWin32 : public MTXMemManager
	{
	public:
		MTXMemWin32();
		~MTXMemWin32();

		virtual void* Allocate(USIZE_TYPE uiSize, USIZE_TYPE uiAlignment, bool bIsArray);
		//取消已经分配的block
		virtual void Deallocate(char* pcAddr, USIZE_TYPE uiAlignment, bool bIsArray);

	private:
		// Counts.
		enum { POOL_CATEGORY = 42 };
		enum { POOL_MAX = 32768 + 1 };
		// Forward declares.
		struct FPoolInfo;
		struct FFreeMem;

		FPoolInfo* CreateIndirect();

	private:
		//链表管理者
		struct FPoolTable
		{
			unsigned int BlockSize; //每次可以分配的内存大小,poolinfo中单独内存块的大小
			FPoolInfo* ExhaustedPool; //分配完的 PoolInfo 链表头指针
			FPoolInfo* FirstPool; //没有分配完的 PoolInfo 链表头指针
		};

		struct FPoolInfo
		{
			//FPoolInfo* Pre; //指向自己前一个节点
			//于 PreLink 为什么是指针的指针，其实这种方式从一个链表中删除，无须知道当前链表的头指针
			FPoolInfo** PrevLink;
			FPoolInfo* Next; //指向自己的后一个节点
			FPoolTable* Owner; //属于哪个链表管理者
			void* Mem; //指向 32 位 Windows 系统分配空间的首地址
			unsigned int Taken; //每分配一次就加 1，释放一次就减 1，如果释放后为 0，那么就把 Mem 指向的内存空间还给 32 位 Windows 系统
			FFreeMem* FirstMem;
			//Fpoolinfo link 到参数中，所以需要使用引用传参，head是指向指针的指针。
			//将this插入到链表头结点。

			DWORD	    Bytes;		// Bytes allocated for pool.
			DWORD		OsBytes;	// Bytes aligned to page size.

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

		struct FFreeMem
		{
			FFreeMem* Next; //在同一个 PoolInfo 中，下一个可用的单元
			DWORD Blocks; //还剩下多少可用单元
			FPoolInfo* GetPool()
			{
				//在Poolinfo中的任意一个地址取出高17位就可以定位这个Poolinfo
				//因为M 为 32KB，即低15位为块内地址
				return (FPoolInfo*)((INT)this & 0xffff8000);
			}
		};


		FPoolTable  PoolTable[POOL_CATEGORY];
		FPoolTable OsTable;
		FPoolInfo* PoolIndirect[32];
		FPoolTable* MemSizeToPoolTable[POOL_MAX];
		INT			PageSize;

	};

#elif _DEBUG
	class MATRIXCORE_API MTXDebugMem : public MTXMemManager
	{
	public:
		MTXDebugMem();
		~MTXDebugMem();

		//uiSize 是这次申请的字节数
		virtual void* Allocate(USIZE_TYPE uiSize, USIZE_TYPE uiAlignment, bool bIsArray);
		virtual void Deallocate(char* pcAddr, USIZE_TYPE uiAlignment, bool bIsArray);


	private:
		enum  BLOCKMARK
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
					pAddr[i] = NULL;
				}
				pPrev = NULL;
				pNext = NULL;
				mbAlignment = false;
				mbArray = false;
				mSize = 0;
				mStackInfoNum = 0;
			}

			void* pAddr[CALLSTACK_NUM]; //申请内存时候的调用堆栈信息
			unsigned int mStackInfoNum; //堆栈层数
			USIZE_TYPE   mSize; //申请空间的大小
			bool mbArray; //是否是数组
			bool mbAlignment; //是否字节对齐
			Block* pPrev; //前一个节点
			Block* pNext; //后一个节点
		};

		Block* pHead;
		Block* pTail;
		unsigned int mNumNewCalls; //调用 new 的次数
		unsigned int mNumDeleteCalls; //调用 delete 的次数
		unsigned int mNumBlocks; //当前有多少内存块
		unsigned int mNumBytes; //当前有多少字节
		unsigned int mMaxNumBytes; //最多申请多少字节
		unsigned int mMaxNumBlocks; //最多申请多少内存块
		unsigned int mSizeRecord[RECORD_NUM];
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
#endif



}

