#pragma once
#include "MTXCore.h"

namespace Matrix
{

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

	};

#if !_DEBUG && !_WIN64

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
		enum BlockMacro
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

	struct FreeMem
	{
		FreeMem* Next; //在同一个 PoolInfo 中，下一个可用的单元
		DWORD Blocks; //还剩下多少可用单元
		PoolInfo* GetPool();
	};

	//链表管理者
	struct PoolTable
	{
		unsigned int TableSize; //每次可以分配的内存大小,poolinfo中单独内存块的大小
		PoolInfo* ExhaustedPool; //分配完的 PoolInfo 链表头指针
		PoolInfo* FirstPool; //没有分配完的 PoolInfo 链表头指针
	};

	struct PoolInfo
	{
		PoolInfo* Pre; //指向自己前一个节点
		PoolInfo* Next; //指向自己的后一个节点
		PoolTable* Owner; //属于哪个链表管理者
		void* Mem; //指向 32 位 Windows 系统分配空间的首地址
		unsigned int Taken; //每分配一次就加 1，释放一次就减 1，如果释放后为 0，
		//那么就把 Mem 指向的内存空间还给 32 位 Windows 系统
		FreeMem* FreeMem;
	}


#else
#endif



}

