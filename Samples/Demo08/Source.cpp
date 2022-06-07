/*
չʾ�����л��洢�����������չʾ�˼�������֧�ֵ����ͣ��ṹ�壬�Զ������ͣ�ָ�룬����ָ�룬ö�٣����г����͡�����ļ�����bin\ test_stream�ļ���
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
