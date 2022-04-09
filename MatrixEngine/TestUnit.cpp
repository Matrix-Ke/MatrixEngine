#pragma once
#include <stdio.h>
#include <tchar.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <tchar.h>
#include <memory.h>
#include <assert.h>
#include <sys/stat.h>
#include <atlsimpstr.h>
#include <intrin.h>

//#include "../MatrixCore/MTXSingleton.h"
#pragma warning(disable:4996)


using namespace std;
//using namespace Matrix;


//typedef WCHAR TCHAR, * PTCHAR;

typedef int  KKL, LiMing;
int main()
{

	//unsigned long long  kkl = 90;
	//cout << sizeof(kkl) << endl;

	//TCHAR pStr[] = _T("中文测试");
	//中文注释测试效果很多覅Ohio是东方化工i哦化工i活动分工i
	char pStr[] = "中文测试";
	wcout << "pStr = " << sizeof(pStr) << endl;
	wcout << pStr << endl;

	//char  name[20] = "kkl";
	//ClassTest   foo(name, 28);
	////ClassTest  singleTest = MTXSingleton<ClassTest>::GetInstance();
	//foo.printClassInfo();

	return 0;
}
