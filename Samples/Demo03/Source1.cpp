//stack memroy unit demo
//≤‚ ‘pod  
//≤‚ ‘type_trait   https://www.cplusplus.com/reference/type_traits/is_trivially_constructible/
#include "Core/MemoryManager.h"
#include <iostream>
#include <typeinfo>


using namespace Matrix::Core;

class MyStruct
{
public:
	int a;
	char c;
	MyStruct()
	{
		a = 100;
		c = 'c';
	};
	MyStruct(int num, char name)
	{
		a = num;
		c = name;
	}
	//~MyStruct()
	//{
	//	std::cout << "MyStruct has been called\n";
	//}
};

//void Fun5()
//{
//	StackMemoryAdaptor<MyStruct> Temp(10000);
//	MyStruct* p = Temp.GetPtr();
//	p[2].a = 1;
//	p[2].c = 'k';
//}

int  main()
{

	if (!std::is_pod<MCriticalSection>::value)
	{
		printf("is not pod!\n");
	}

	if (/*std::is_pod<MyStruct>::value && */std::is_trivially_constructible<MyStruct, MyStruct>::value)
	{
		printf("is_trivially_constructible\n");
	}

	if (/*std::is_pod<MyStruct>::value && */std::is_default_constructible<MyStruct>::value)
	{
		printf("is_default_constructible\n");
	}


	StackMemoryAdaptor<MyStruct> Temp(2);
	//StackMemoryAdaptor<MyStruct> Temp1(2);

	//MyStruct* p = Temp.GetPtr();
	//p[1].a = 1;
	//p[1].c = 'k';

	//Fun5();
	const std::type_info& name = typeid(Temp);

	std::cout << name.hash_code() << std::endl;

	return 0;
}