#include <xmmintrin.h>
#include "Math/CMathInterface.h"

//msvc ��֧��64λ�Ĵ���
//__m128 addWithAsm(const __m128 a, const __m128 b)
//{
//	//���ݺ�������Լ����xnm0, xnm1 �Ѿ��洢��xnm0, xnm1��
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

	//_mm_set_ps  ��4����������ʼ��Ϊһ��__128������ע����С��˳�� С��˳����� β���ֽڴ���ڵͶ˼�4.0f������ʼλ��
	__m128  aSSE = _mm_set_ps(1.0f, 2.0f, 3.0f, 4.0f);
	//_mm_load_ps  ���ڴ��е���������__m128��������SSE�Ĵ�����
	__m128  bSSE = _mm_load_ps(B);

	__m128  resSSE = addWithIntrin(aSSE, bSSE);

	//��SSE�Ĵ�����ֵ��д���ڴ���
	_mm_store_ps(A, aSSE);
	_mm_store_ps(B, bSSE);

	printf_s("SSE result:  %f,  %f, %f, %f \n", A[0], A[1], A[2], A[3]);
	printf_s("SSE result:  %f,  %f, %f, %f \n", B[0], B[1], B[2], B[3]);


	return 0;
}
