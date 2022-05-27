#include "Log.h"

Matrix::Core::MXLog::MXLog()
{
}

Matrix::Core::MXLog::~MXLog()
{
}

bool Matrix::Core::MXLog::Open(const TCHAR *pFileName)
{
    return File::Open(pFileName, EOpenMode::OM_WT);
}

bool Matrix::Core::MXLog::WriteInfo(const TCHAR *pString)
{
    //时时刻刻记得字符数组不要越界
    return File::Write(pString, MXStrLen(pString) + 1, 1);
}
