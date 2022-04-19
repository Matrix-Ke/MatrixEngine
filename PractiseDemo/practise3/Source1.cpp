//stack memroy unit demo
#include "MTXMemManager.h"
#include <iostream>

using namespace Matrix;
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
	StackMemAdaptor<MyStruct> Temp(10000);
	MyStruct* p = Temp.GetPtr();
	p[2].a = 1;
	p[2].c = 'k';
}

int  main()
{
	StackMemAdaptor<MyStruct> Temp(2);
	StackMemAdaptor<MyStruct> Temp1(2);

	MyStruct* p = Temp.GetPtr();
	p[1].a = 1;
	p[1].c = 'k';

	Fun5();

	return 0;
}