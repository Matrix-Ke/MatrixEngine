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
    //ʱʱ�̼̿ǵ��ַ����鲻ҪԽ��
    return File::Write(pString, MXStrLen(pString) + 1, 1);
}
