#pragma once


#if _WIN32 //_WIN32 宏定义windows平台
#define WINDOWS_PLATFORM 1
#endif

enum class EPLATFORM
{
	EP_Windows,
	EP_Android,
	EP_IOS,
	EP_MAX
};


//开始定义MatrixEngine 的跨平台数据类型 
#define MATRIX_ENGINE_BASIC_TYPE
#ifdef MATRIX_ENGINE_BASIC_TYPE
#if WINDOWS_PLATFORM
#if _WIN64
#define SYSTEM_BIT_WIDTH 64
#define USIZE_TYPE unsigned long long
#define SIZE_TYPE long long
#else
#define SYSTEM_BIT_WIDTH 32
#define USIZE_TYPE unsigned int
#define SIZE_TYPE int
#endif
#endif

#define VSUSHORT_INDEX	unsigned short
#define VSUINT_INDEX	unsigned int
//#define  VSFLOAT 
//#ifdef VSFLOAT 
#define VSREAL 		float
#endif // MATRIX_ENGINE_BASIX_TYPE


#ifdef WINDOWS_PLATFORM
//Use __declspec(align(#)) to precisely control the alignment of user - defined data
//(for example, static allocations or automatic data in a function).
#define ALIGN(n) __declspec(align(n))
#else
#define ALIGN(n)
#endif

#define BIT(i) (1 << i)



