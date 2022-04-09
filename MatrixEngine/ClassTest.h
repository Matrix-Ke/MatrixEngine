#pragma once

class ClassTest
{
public:
	ClassTest();
	ClassTest(const char* pName);
	ClassTest(char* name, int number);

	void printClassInfo();
private:
	size_t mNumber;
	char* mName;
};

