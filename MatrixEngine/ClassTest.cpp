#include "ClassTest.h"
#include <iostream>


char   name[20] = "KKL";

ClassTest::ClassTest()
{
	mName = name;
	mNumber = 28;
}

ClassTest::ClassTest(char* name, int number)
{
	mName = name;
	mNumber = number;
}

void ClassTest::printClassInfo()
{
	std::cout << "class name:" << mName << "\n" << "class number:" << mNumber << std::endl;
}
