#include <vector>


#define MacroFunc(name) \
	typedef std::vector<int>    ##name##Ptr


int main()
{
	MacroFunc(int);

	intPtr     arr;

	return 0;
}
