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

int main()
{
	int i = 1;

	int result = (i + 1) >> 2;

	cout << result << endl;
	return 0;
}
