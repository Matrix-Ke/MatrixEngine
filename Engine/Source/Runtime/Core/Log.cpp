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
	//时时刻刻记得字符数组不要越界
	return File::Write(pString, MTXStrLen(pString) + 1, 1);
}
