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

#if WINDOWS_PLATFORM && !_DEBUG && !_WIN64

#elif _DEBUG
	class MATRIXCORE_API MTXDebugMem : public MTXMemManager
	{
	public:
		MTXDebugMem();
		~MTXDebugMem();

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
				mbAligment = false;
				mSize = 0;
				mStackInfoNum = 0;
			}

		private:
			void* pAddr[CALLSTACK_NUM]; //申请内存时候的调用堆栈信息
			unsigned int mStackInfoNum; //堆栈层数
			USIZE_TYPE   mSize; //申请空间的大小
			bool mbArray; //是否是数组
			bool mbAligment; //是否字节对齐
			Block* pPrev; //前一个节点
			Block* pNext; //后一个节点
		};

	};
#else
#endif



}

