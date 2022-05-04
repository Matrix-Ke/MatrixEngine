#pragma once
#include "Platform.h"
#include <stdio.h>
#include <tchar.h>
#include <memory.h>
#include <assert.h>
#include <sys/stat.h>
#include <atlsimpstr.h>
#include <intrin.h>
#pragma warning(disable:4251) //去除模板导出编译的警告
#pragma warning(disable:4595) 

#ifdef	Core_EXPORTS
#define MATRIXCORE_API __declspec(dllexport) 
#else 
#define MATRIXCORE_API __declspec(dllimport) 
#endif


namespace Matrix
{
#ifdef _DEBUG
	//assert 的缺点是，频繁的调用会极大的影响程序的性能，增加额外的开销。
	//在调试结束后，可以通过在包含 #include 的语句之前插入 #define NDEBUG 来禁用 assert 调用
#define MTXENGINE_ASSERT(Expression)\
		{\
			 assert(Expression);\
		}
#else
	//通过debug来控制
#define MTXENGINE_ASSERT(Expression)
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

	class MATRIXCORE_API MatrixCore
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
		//InterlockedCompareExchange是把目标操作数（第1参数所指向的内存中的数）与一个值（第3参数）比较，如果相等，则用另一个值（第2参数）与目标操作数（第1参数所指向的内存中的数）交换；
		//InterlockedExchange是不比较直接交换。整个操作过程是锁定内存的，其它处理器不会同时访问内存，从而实现多处理器环境下的线程互斥
		return _InterlockedCompareExchange(pDestination, Exchange, Comparand);
	}

	inline long MTXlockedAdd(long* pRefCount, long Value)
	{
		return _InterlockedExchangeAdd(pRefCount, Value);
	}

	inline long MTXlockedExchange(long* pRefCount, long Value)
	{
		//能以原子操作的方式交换俩个参数a, b，并返回a以前的值；因为InterlockedExchange 是原子函数，不会要求中止中断，所以交换指针的方式是安全的。
		return _InterlockedExchange(pRefCount, Value);
	}

	inline long MTXlockedOr(long* pRefCount, long Value)
	{
		return _InterlockedOr(pRefCount, Value);
	}
	inline long MTXlockedXor(long* pRefCount, long Value)
	{
		return _InterlockedXor(pRefCount, Value);
	}

	inline long MTXAtomicRead(long* pRefCount)
	{
		return MTXlockedCompareExchange(pRefCount, 0, 0);
	}

	inline long MTXAtomicWrite(long* pRefCount, long Value)
	{
		return MTXlockedExchange(pRefCount, Value);
	}

	inline long MTXLockedIncrement(long* pRefCount)
	{
		return _InterlockedIncrement(pRefCount);
	}

	inline long MTXLockedDecrement(long* pRefCount)
	{
		return _InterlockedDecrement(pRefCount);
	}

	inline void  MTXMemset(void* pDest, int iC, USIZE_TYPE uiCount)
	{
		memset(pDest, iC, uiCount);
	}

	inline bool MTXIsSpace(int c)
	{
		return _istspace(c);
	}

	inline void MTXStrcat(TCHAR* pDest, unsigned int uiCount, const TCHAR* pSource)
	{
		//Note that the second parameter is the total size of the buffer, not the remaining size
		_tcscat_s(pDest, uiCount, pSource);
	}

	inline TCHAR* MTXStrtok(TCHAR* strToken, const TCHAR* strDelimit, TCHAR** pContext)
	{
		////Find the next token in a string.
		return _tcstok_s(strToken, strDelimit, pContext);
	}

	inline const TCHAR* MTXCsrchr(const TCHAR* pString, int c)
	{
		//Scan a string for the last occurrence of a character.
		return _tcsrchr(pString, c);
	}

	inline void  MTXOutputDebugString(const TCHAR* pcString, ...)
	{
		char* pArgs;
		pArgs = (char*)&pcString + sizeof(pcString);
		_vstprintf_s(MatrixCore::msLogbuffer, LOG_BUFFER_SIZE, pcString, pArgs);
		OutputDebugString(MatrixCore::msLogbuffer);
	}

	inline void MTXSprintf(TCHAR* _DstBuf, unsigned int _SizeInBytes, const TCHAR* _Format, ...)
	{
		char* pArgs;
		pArgs = (char*)&_Format + sizeof(_Format);
		_vstprintf_s(_DstBuf, _SizeInBytes, _Format, pArgs);
	}

	inline void MTXSprintf(TCHAR* _DstBuf, unsigned int _SizeInBytes, const TCHAR* _Format, va_list pArgs)
	{
		_vstprintf_s(_DstBuf, _SizeInBytes, _Format, pArgs);
	}

	inline void MTXScanf(TCHAR* Buf, const TCHAR* _Format, va_list pArgs)
	{
		_stscanf_s(Buf, _Format, pArgs);
	}

	inline void MTXStrCopy(TCHAR* pDest, unsigned int uiCount, const TCHAR* pSource)
	{
		_tcscpy_s(pDest, uiCount, pSource);
	}

	inline int MTXStrCmp(const TCHAR* String1, const TCHAR* String2)
	{
		return _tcscmp(String1, String2);
	}

	inline int MTXStrnCmp(const TCHAR* String1, const TCHAR* String2, unsigned int uiMaxNum)
	{
		return _tcsncmp(String1, String2, uiMaxNum);
	}

	//字符转化
	inline void MTXMbsToWcs(wchar_t* Dest, unsigned int uiSizeInWord, const char* Source, unsigned int uiSizeInByte)
	{
		mbstowcs_s(0, Dest, uiSizeInWord, Source, uiSizeInByte);
	}

	inline bool MTXIstalnum(char c)
	{
		return _istalnum(c);
	}

	inline unsigned int MTXGetCpuNum()
	{
		SYSTEM_INFO SystemInfo;
#if _WIN64
		GetNativeSystemInfo(&SystemInfo);
#else
		GetSystemInfo(&SystemInfo);
#endif
		return SystemInfo.dwNumberOfProcessors;
	}


	inline bool MTXIsMainThread()
	{
		return MatrixCore::msMainThreadID == GetCurrentThreadId();
	}

	inline void MTXGetCurrentDirectory(TCHAR* CurDir)
	{
		GetCurrentDirectory(MAX_PATH, CurDir);
	}

	inline const wchar_t* MTXGetExeFolderName()
	{
#if _WIN64
		return _T("x64");
		//return (TCHAR*)_T("x64");
#else
		return _T("Win32");
#endif
	}

	inline EPLATFORM GetCurPlatform()
	{
		return EPLATFORM::EP_Windows;
	}

	inline const wchar_t* GetCurPlatformName()
	{
		//return (TCHAR*)_T("Windows");
		return _T("Windows");
	}
	inline void VSSetCurrentDirectory(TCHAR* CurDir)
	{
		SetCurrentDirectory(CurDir);

	}

	inline void MTXInitSystem()
	{
		MatrixCore::msMainThreadID = GetCurrentThreadId();
	}

	//线程局部变量： 如果需要在一个线程内部的各个函数调用都能访问、但其它线程不能访问的变量（被称为static memory local to a thread 线程局部静态变量，这就是TLS。
	inline unsigned int MTXTlsAlloc()
	{
		return TlsAlloc();
	}
	inline void* MTXGetTlsValue(unsigned int TlsSolt)
	{
		return TlsGetValue(TlsSolt);
	}

	inline bool MTXSetTlsValue(unsigned int TlsSolt, void* TlsValue)
	{
		return TlsSetValue(TlsSolt, TlsValue);
	}

	inline bool MTXTlsFree(unsigned int TlsSolt)
	{
		return TlsFree(TlsSolt);
	}


#ifdef WINDOWS_PLATFORM
#define ALIGN(n) __declspec(align(n))
#else
#define ALIGN(n)
#endif
	template<typename T>
	inline T ABS(T t)
	{
		return t < 0 ? -t : t;
	}
	template<typename T>
	inline T Min(T t0, T t1)
	{
		return t0 < t1 ? t0 : t1;
	}
	template<typename T>
	inline T Max(T t0, T t1)
	{
		return t0 > t1 ? t0 : t1;
	}
	template<typename T>
	inline T Clamp(T Value, T Max, T Min)
	{
		if (Value >= Max)
		{
			return Max;
		}
		if (Value <= Min)
		{
			return Min;
		}
		return Value;
	}
	template <class T>
	inline void Swap(T& t1, T& t2)
	{
		T temp;
		temp = t1;
		t1 = t2;
		t2 = temp;
	}
#define BIT(i) (1 << i)


}

