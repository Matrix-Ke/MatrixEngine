#pragma once
#include <stdio.h>
#include <tchar.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "ClassTest.h"

#include "../MatrixCore/MTXSingleton.h"
#pragma warning(disable:4996)


using namespace std;
using namespace Matrix;


int main()
{
	char  name[20] = "kkl";
	ClassTest   foo(name, 28);
	//ClassTest  singleTest = MTXSingleton<ClassTest>::GetInstance();

	foo.printClassInfo();

	return 0;
}
