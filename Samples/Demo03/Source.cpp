//测试引擎内存池功能
#include "Core/MemoryManager.h"
#include <iostream>

class foo
{
public:
	foo()
	{
		mName = 0;
	}
	~foo()
	{
		std::cout << "deconstructor has been called! " << std::endl;
	}
private:
	int mName;
};



int main()
{
	std::cout << "sizeof(foo) = " << sizeof(foo) << std::endl;

	foo* ptr = MX_NEW foo[2];
	MX_ENGINE_DELETEA(ptr);
	return 0;
}