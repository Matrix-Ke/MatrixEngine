#pragma once
#ifdef  Function_EXPORTS
#define MATRIX_FUNCTION_API  __declspec(dllexport)
#else
#define MATRIX_FUNCTION_API  __declspec(dllimport)
#endif // Function_EXPORTS
#define PROFILER
#include "Math/Math.h"

namespace Matrix
{
#define STREAM_LEVEL 16 
#define RENDERTARGET_LEVEL 8
#define UNORDERACCESSS_LEVEL 8
#define POSTEFFECT_MAX_INPUT 4
#define UV_LEVEL 4
#define MAX_DYNAMIC_LIGHT 3
#define INVALID_SIMPLAR_REGISTER 16 
#define MAX_SIMPLE_INSTANCE_ANIM 3
#define MAX_MIP_LEVEL 20


}