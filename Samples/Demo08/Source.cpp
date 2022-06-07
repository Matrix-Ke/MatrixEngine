/*
展示了序列化存储，这个例子中展示了几乎所有支持的类型，结构体，自定义类型，指针，智能指针，枚举，还有常类型。最后文件存在bin\ test_stream文件。
*/
#include "ClassInfoObject.h"
#include "Function/Meta/Stream.h"


using namespace Matrix;


void main()
{
	//VSInitSystem();
	//VSInitMath();
	//VSMain::Initialize();
	EngineInit::Initialize();

	//new object
	Matrix::ClassInfoObject* testObj = MX_NEW  Matrix::ClassInfoObject();

	MStream    testStream;
	testStream.SetStreamFlag(MStream::AT_REGISTER);
	testStream.ArchiveAll(testObj);
	const TCHAR  Path[] = _T("test_stream.txt");
	testStream.Save(Path);

	MX_DELETE testObj;

	EngineInit::Terminate();
}
