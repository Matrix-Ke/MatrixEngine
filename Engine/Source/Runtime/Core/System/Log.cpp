#include "Log.h"

Matrix::Core::MTXLog::MTXLog()
{
}

Matrix::Core::MTXLog::~MTXLog()
{
}

bool Matrix::Core::MTXLog::Open(const TCHAR* pFileName)
{
	return File::Open(pFileName, OM_WT);
}

bool Matrix::Core::MTXLog::WriteInfo(const TCHAR* pString)
{
	//ʱʱ�̼̿ǵ��ַ����鲻ҪԽ��
	return File::Write(pString, MTXStrLen(pString) + 1, 1);
}
