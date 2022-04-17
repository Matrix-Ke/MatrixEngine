#pragma once
#include "MTXCore.h"

#include <iostream>


int main()
{
	using namespace std;

	int* pArr = new int[10];

	delete[] pArr;

	//cout << "test" << endl;

	return 0;
}