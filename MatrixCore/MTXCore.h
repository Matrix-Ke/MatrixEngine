#pragma once
#include "MatrixPlatform.h"
#include <stdio.h>
#include <tchar.h>
#include <memory.h>
#include <assert.h>
#include <sys/stat.h>
#include <atlsimpstr.h>
#include <intrin.h>
#pragma warning(disable:4251) //去除模板导出编译的警告
#pragma warning(disable:4595) 

#ifdef MATRIXCORE_EXPORTS
#define MATRIXCORE_API __declspec(dllexport) 
#else 
#define MATRIXCORE_API __declspec(dllimport) 
#endif


namespace Matrix
{
#ifndef _DEBUG
#define _DEBUG 0
#endif 

#ifdef _DEBUG
//assert 的缺点是，频繁的调用会极大的影响程序的性能，增加额外的开销。
//在调试结束后，可以通过在包含 #include 的语句之前插入 #define NDEBUG 来禁用 assert 调用
#define MTXENGINE_ASSERT(Expression)\
	{\
		 assert(Expression);\
	}
#else
#define VSMAC_ASSERT(Expression)
#endif

#define THREAD_CALLBACK __stdcall
	inline unsigned int SizeTypeToGUID32(USIZE_TYPE Size_Type)
	{
		return (Size_Type & 0xffffffff);
	}
	inline USIZE_TYPE GUID32ToSizeType(unsigned int uiGUID)
	{
#if _WIN64
		return (uiGUID & 0x00000000ffffffff);
#else
		return (uiGUID & 0xffffffff);
#endif
	}

	inline int ComparePointer(void* Point1, void* Point2)
	{

		if (((USIZE_TYPE)Point1) == ((USIZE_TYPE)Point2))
		{
			return 0;
		}
		else if (((USIZE_TYPE)Point1) > ((USIZE_TYPE)Point2))
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}

#define LOG_BUFFER_SIZE 65536

	class MatrixCore
	{
	public:
		static TCHAR msLogbuffer[LOG_BUFFER_SIZE];
		static DWORD msMainThreadID;
	};
	inline bool MTXMemcpy(void* pDest, const void* pSrc, USIZE_TYPE uiCountSize, USIZE_TYPE uiDestBufferSize = 0)
	{
		if (!uiDestBufferSize)
		{
			uiDestBufferSize = uiCountSize;
		}
		return (memcpy_s(pDest, uiDestBufferSize, pSrc, uiCountSize) == 0);
	}

	inline  unsigned int MTXStrlen(const TCHAR* pStr)
	{
		return (unsigned int)_tcslen(pStr);
	}

	inline long MTXlockedCompareExchange(long* pDestination, long Exchange, long Comparand)
	{
		return _InterlockedCompareExchange(pDestination, Exchange, Comparand);
	}
}

