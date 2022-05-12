#include "Core/File.h"
#include <iostream>

using namespace Matrix;
using namespace  Matrix::Core;

int main()
{
	//{} ������Ĭ�ϳ�ʼ��Ϊ0
	TCHAR dir[MAX_FILE_PATH_SIZE] = {  };
	for (unsigned i = 0; i < MAX_FILE_PATH_SIZE; i++)
	{
		MTXSprintf(_T("print: %d =  %x end\n"), i, dir[i]);
	}

	MTXGetCurrentDirectory(dir);
	MTXSprintf(_T("print: %s EOF\n"), dir);

	_tcscat_s(dir, MAX_FILE_PATH_SIZE, _T("/FileDemo.json"));
	MTXSprintf(_T("print: %s EOF\n"), dir);

	struct MyStruct
	{
		char name = 'c';
		int num = 99;
	} mystruct;
	File   jsonFile(dir, File::EOpenMode::OM_AT);
	//jsonFile.Write(dir, sizeof(TCHAR), MTXStrLen(dir));
	jsonFile.Write(&mystruct, sizeof(MyStruct), 1);


	jsonFile.Open(_T("D:\\GitDemo\\MatrixEngine\\Samples\\Demo02/FileDemo.json"), File::EOpenMode::OM_AT);
	jsonFile.DebugInfo();

	return 0;
}