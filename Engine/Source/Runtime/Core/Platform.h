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