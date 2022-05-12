//����c���� �ɱ��������ԭ��
//�ο����ͣ� https://www.cnblogs.com/clover-toeic/p/3736748.html
#include <stdio.h>
#include <tchar.h>
#include <stdarg.h>

double average(int num, ...)
{

	va_list valist;
	double sum = 0.0;
	int i;

	/* Ϊ num ��������ʼ�� valist */
	va_start(valist, num);

	/* �������и��� valist �Ĳ��� */
	for (i = 0; i < num; i++)
	{
		sum += va_arg(valist, int);
	}
	/* ����Ϊ valist �������ڴ� */
	va_end(valist);

	return sum / num;

}


void function(const TCHAR* pString, int number)
{

	char* addr = (char*)(&pString) + sizeof(pString);

	_tprintf(_T("first arg addr : %x\n"), addr);

	//����ڶ������ĵ�ַ
	_tprintf(_T("number addr: %x\n"), &number);

}

void function2(int* pArr, int number)
{
	char* addr = (char*)(pArr);

	_tprintf(_T("first arg addr : %x\n"), addr);

	//����ڶ������ĵ�ַ
	_tprintf(_T("number addr: %x\n"), &number);
}


int main()
{



	printf("Average of 2, 3, 4, 5 = %f\n", average(4, 2, 3, 4, 5));
	printf("Average of 5, 10, 15 = %f\n", average(3, 5, 10, 15));

	TCHAR   arr[10] = _T("kklname");
	function(_T("kklname"), 100);

	int arr1[10] = { 0 ,1, 2, 3, 4, 5, 6, 7, 8, 9 };
	_tprintf(_T("arr1 addr: %x\n"), arr1);
	function2(arr1, 999);


	return 0;
}

