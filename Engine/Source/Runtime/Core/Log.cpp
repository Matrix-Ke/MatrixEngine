#include "Log.h"

Matrix::MTXLog::MTXLog()
{
}

Matrix::MTXLog::~MTXLog()
{
}

bool Matrix::MTXLog::Open(const TCHAR* pFileName)
{
	return MTXFile::Open(pFileName, OM_WT);
}

bool Matrix::MTXLog::WriteInfo(const TCHAR* pString)
{
	//ʱʱ�̼̿ǵ��ַ����鲻ҪԽ��
	return MTXFile::Write(pString, MTXStrlen(pString) + 1, 1);
}
