//stack memroy unit demo
#include "MTXMemManager.h"
#include <iostream>

using namespace Matrix;
class MyStruct
{
public:
	int a;
	char c;
	~MyStruct()
	{
		std::cout << "MyStruct has been called\n";
	}
};
void Fun()
{

}
void Fun1()
{

}
void Fun2()
{
	Fun1();
}

void Fun3()
{
	Fun2();
}
void Fun4()
{

}
void Fun5()
{
	MTXStackMemAlloc<MyStruct> Temp(3);
	MyStruct* p = Temp.GetPtr();
	p[2].a = 1;
	p[2].c = 'k';
	Fun3();
}

int  main()
{
	MTXStackMemAlloc<MyStruct> Temp(2);
	//Fun4();
	//Fun5();
	MyStruct* p = Temp.GetPtr();
	p[1].a = 1;
	p[1].c = 'k';

	return 0;
}