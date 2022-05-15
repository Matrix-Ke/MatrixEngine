#include <xmmintrin.h>
#include "Math/CMathInterface.h"

//msvc 不支持64位寄存器
//__m128 addWithAsm(const __m128 a, const __m128 b)
//{
//	//根据函数调用约定，xnm0, xnm1 已经存储在xnm0, xnm1中
//	__asm
//	{
//		addps xnm0, xnm1;
//	}
//}


__m128 addWithIntrin(const __m128 a, const __m128 b)
{
	return _mm_add_ps(a, b);
}


int main()
{
	ALIGN(16) float A[4] = { 0 };
	ALIGN(16) float B[4] = { 5.0f, 6.0f, 7.0f, 8.0f };

	//_mm_set_ps  把4个浮点数初始化为一个__128变量，注意是小端顺序， 小端顺序就是 尾序字节存放在低端即4.0f放在起始位置
	__m128  aSSE = _mm_set_ps(1.0f, 2.0f, 3.0f, 4.0f);
	//_mm_load_ps  把内存中的数组载入__m128变量（即SSE寄存器）
	__m128  bSSE = _mm_load_ps(B);

	__m128  resSSE = addWithIntrin(aSSE, bSSE);

	//把SSE寄存器的值，写回内存中
	_mm_store_ps(A, aSSE);
	_mm_store_ps(B, bSSE);

	printf_s("SSE result:  %f,  %f, %f, %f \n", A[0], A[1], A[2], A[3]);
	printf_s("SSE result:  %f,  %f, %f, %f \n", B[0], B[1], B[2], B[3]);


	return 0;
}
