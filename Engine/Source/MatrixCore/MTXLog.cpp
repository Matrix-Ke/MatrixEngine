#include "MTXLog.h"

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
	//时时刻刻记得字符数组不要越界
	return MTXFile::Write(pString, MTXStrlen(pString) + 1, 1);
}
