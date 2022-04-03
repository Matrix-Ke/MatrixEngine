#pragma once

class ClassTest
{
public:
	ClassTest();
	ClassTest(char* name, int number);

	void printClassInfo();
private:
	int mNumber;
	char* mName;
};

