#include <iostream>
#include <string>
using namespace std;

class FPoolInfo
{
public:
	FPoolInfo(int number) : mNumber(number) {};
	FPoolInfo** PrevLink;
	FPoolInfo* Next; //指向自己的后一个节点
	int mNumber;
	void link(FPoolInfo*& Head)
	{
		if (Head)
		{
			Head->PrevLink = &(this->Next);
		}
		this->Next = Head;
		PrevLink = &Head;
		Head = this;
	}
};

class Table
{
public:
	FPoolInfo* firstNode;
};




int main()
{
	Table  tableT;
	FPoolInfo    poolNode(100);

	poolNode.link(tableT.firstNode);

}

