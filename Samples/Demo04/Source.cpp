//这个示例的主要目的是，演示在容器里面初始化会调用构造函数，构造函数里面下个断点看看

#include <iostream>
#include "Container/Array.h"
using namespace Matrix::Container;

class MyClass
{
public:
	MyClass();
	~MyClass();

	int i;
};

MyClass::MyClass()
{
	i = 0;
}

MyClass::~MyClass()
{
	i = 2;
	std::cout << "deconstructor has been called \n";
}

void main()
{
	MArray<MyClass> k1;
	k1.SetBufferNum(3);
	k1[0].i = 3;
	//std::cout << "1 value:" << i << std::endl;
}