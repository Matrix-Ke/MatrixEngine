//====================================提供平台相关的系统调用接口，所有系统调用必须使用这里的接口=====================================
#pragma once
#include "Platform.h"
#include <stdio.h>
#include <tchar.h>
#include <memory.h>
#include <assert.h>
#include <sys/stat.h>  //获取文件状态
#include <atlsimpstr.h>
#include <intrin.h>
//#pragma warning(disable:4251) //去除模板导出编译的警告
#define USE_STL_TYPE_TRAIT
#ifdef USE_STL_TYPE_TRAIT
// stl 类型萃取
#include <type_traits>
#endif // USE_STL_TYPE_TRAIT

#ifdef	Core_EXPORTS
#define MATRIX_CORE_API __declspec(dllexport) 
#else 
#define MATRIX_CORE_API __declspec(dllimport) 
#endif

#ifdef _DEBUG
		//assert 的缺点是，频繁的调用会极大的影响程序的性能，增加额外的开销。
		//在调试结束后，可以通过在包含 #include 的语句之前插入 #define NDEBUG 来禁用 assert 调用
#define MX_ENGINE_ASSERT(Expression)\
		{\
			 assert(Expression);\
		}
#else
		//通过debug来控制
#define MX_ENGINE_ASSERT(Expression)
#endif

namespace Matrix
{
	namespace Core
	{
#define	MAX_FILE_PATH_SIZE  256

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
		//指针地址比较
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
		//引擎核心静态变量
		class MATRIX_CORE_API MatrixCore
		{
		public:
			static TCHAR msLogbuffer[LOG_BUFFER_SIZE];
			static DWORD msMainThreadID;
		};


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
		inline T MXAlign(const T Ptr, USIZE_TYPE Alignment)
		{
			return (T)(((USIZE_TYPE)Ptr + Alignment - 1) & ~(Alignment - 1));
		}
		template <class T>
		inline T MXAlign1(const T Ptr, USIZE_TYPE Alignment)
		{
			return (T)((USIZE_TYPE)Ptr + Alignment - (Ptr & (Alignment - 1)));
		}
#else
#endif

		//==================================文件流操作=================================
		inline FILE* MTXFopen(const TCHAR* pFileName, const TCHAR* openMode)
		{
			FILE* pFileHandle;
			errno_t err = _tfopen_s(&pFileHandle, pFileName, openMode);
			return pFileHandle;
		}
		inline bool MTXFclose(FILE* fileHandle)
		{
			return fclose(fileHandle);
		}
		inline USIZE_TYPE  MTXRead(void* pBuffer, unsigned int uSize, unsigned int uCount, FILE* fileHandle)
		{
			return fread(pBuffer, uSize, uCount, fileHandle);
		}
		inline USIZE_TYPE MTXWrite(const void* pBuffer, unsigned int uSize, unsigned int uCount, FILE* fileHandle)
		{
			//关于fwrite和 write区别， wirte系统调用， 调用write的时候， 先将数据写到操作系统内核缓冲区， 操作系统会定期将内核缓冲区的数据写回磁盘中。
			//fwrite每次都先将数据写入一个应用缓冲区中， 然后在调用write一次性把相应数据写进内核缓冲区中。
			//ptr − This is the pointer to the array of elements to be written.
			//	size − This is the size in bytes of each element to be written.
			//	nmemb − This is the number of elements, each one with a size of size bytes.
			//	stream − This is the pointer to a FILE object that specifies an output stream.
			return fwrite(pBuffer, uSize, uCount, fileHandle);
		}
		inline TCHAR* MTXGetLine(TCHAR* pBuffer, int uSize, FILE* fileHandle)
		{
			return _fgetts(pBuffer, uSize, fileHandle);
		}
		inline int MTXStat(const TCHAR* pFileName, struct _stat64i32* pStat)
		{
			return _tstat(pFileName, pStat);
		}
		inline bool MTXFlush(FILE* fileHandle)
		{
			return fflush(fileHandle);
		}
		inline bool MTXSeek(FILE* fileHandle, long offset, int origin)
		{
			return fseek(fileHandle, offset, origin);
		}
		//输入输出
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
		inline void MTXSprintf(const TCHAR* _Format, ...)
		{
			char* pArgs = (char*)(&_Format) + sizeof(_Format);
			_vtprintf(_Format, pArgs);
		}
		inline void MTXScanf(TCHAR* Buf, const TCHAR* _Format, TCHAR pArgs)
		{
			_stscanf_s(Buf, _Format, pArgs);
		}

		//==========================================内存处理相关==============================================
		inline bool MTXMemcpy(void* pDest, const void* pSrc, USIZE_TYPE uiCountSize, USIZE_TYPE uiDestBufferSize = 0)
		{
			if (!uiDestBufferSize)
			{
				uiDestBufferSize = uiCountSize;
			}
			return (memcpy_s(pDest, uiDestBufferSize, pSrc, uiCountSize) == 0);
		}
		inline void  MTXMemset(void* pDest, int iC, USIZE_TYPE uCount)
		{
			memset(pDest, iC, uCount);
		}

		//========================================字符处理相关===========================
		inline  unsigned int MTXStrLen(const TCHAR* pStr)
		{
			return (unsigned int)_tcslen(pStr);
		}
		inline void MTXStrCopy(TCHAR* pDest, unsigned int uCount, const TCHAR* pSource)
		{
			_tcscpy_s(pDest, uCount, pSource);
		}
		inline int MTXStrCmp(const TCHAR* String1, const TCHAR* String2)
		{
			return _tcscmp(String1, String2);
		}
		inline int MTXStrnCmp(const TCHAR* String1, const TCHAR* String2, unsigned int uiMaxNum)
		{
			return _tcsncmp(String1, String2, uiMaxNum);
		}
		inline void MTXMbsToWcs(wchar_t* Dest, unsigned int uiSizeInWord, const char* Source, unsigned int uiSizeInByte)
		{
			mbstowcs_s(0, Dest, uiSizeInWord, Source, uiSizeInByte);
		}
		inline bool MTXIstalnum(char c)
		{
			return _istalnum(c);
		}
		inline bool MTXIsSpace(int c)
		{
			return _istspace(c);
		}
		inline void MTXStrcat(TCHAR* pDest, unsigned int uSizeBuffer, const TCHAR* pSource)
		{
			//Note that the second parameter is the total size of the buffer, not the remaining size
			//在实际编写代码中经常出错，记住这个第二参数是pSource的bufferSize
			_tcscat_s(pDest, uSizeBuffer, pSource);
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

		//======================================获取系统信息相关=================================
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
			GetCurrentDirectory(MAX_FILE_PATH_SIZE, CurDir);
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

		//===========================线程同步操作相关===================================
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

	}
}

