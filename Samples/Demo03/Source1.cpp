//stack memroy unit demo
#include "Core/MemoryManager.h"
#include <iostream>

using namespace Matrix::Core;

class MyStruct
{
public:
	int a;
	char c;
	//~MyStruct()
	//{
	//	std::cout << "MyStruct has been called\n";
	//}
};

void Fun5()
{
	StackMemoryAdaptor<MyStruct> Temp(10000);
	MyStruct* p = Temp.GetPtr();
	p[2].a = 1;
	p[2].c = 'k';
}

int  main()
{
	StackMemoryAdaptor<MyStruct> Temp(2);
	StackMemoryAdaptor<MyStruct> Temp1(2);

	MyStruct* p = Temp.GetPtr();
	p[1].a = 1;
	p[1].c = 'k';

	Fun5();

	return 0;
}