#include "File.h"

using namespace Matrix::Platform;

TCHAR File::msOpenModeArray[(unsigned int)File::EOpenMode::OM_MAX][7] =
    {
        _T("rb"),
        _T("rt"),
        _T("wb"),
        _T("wt"),
        _T("a+b"),
        _T("a+t")};

unsigned int File::msSeekFlag[(unsigned int)File::ESeekFlag::SF_MAX] =
    {
        SEEK_CUR,
        SEEK_END,
        SEEK_SET};

Matrix::Platform::File::File()
{
    this->pFileHandle = nullptr;
    this->mOpenMode = EOpenMode::OM_MAX;
    this->mFileName[0] = EOF;
    this->mFileSize = NULL;
}

Matrix::Platform::File::File(const TCHAR *pFileName, EOpenMode openMode)
{
    this->OpenFile(pFileName, openMode);
}

Matrix::Platform::File::~File()
{
    this->Fclose();
}

bool Matrix::Platform::File::Open(const TCHAR *pFileName, EOpenMode openMode)
{
    //如果有则关闭已经的重新打开新的
    if (pFileHandle)
    {
        MXFclose(pFileHandle);
    }

    this->OpenFile(pFileName, openMode);
    return true;
}

void Matrix::Platform::File::Fclose()
{
    if (pFileHandle)
    {
        MXFclose(pFileHandle);
        //删除任何指针和句柄之后记得置NULL， 血的教训。
        pFileHandle = NULL;
    };
}

USIZE_TYPE Matrix::Platform::File::Read(void *pBuffer, unsigned int uSize, unsigned int uCount)
{
    ENGINE_ASSERT(pFileHandle);
    return MXRead(pBuffer, uSize, uCount, pFileHandle);
}

USIZE_TYPE Matrix::Platform::File::Write(const void *pBuffer, unsigned int uSize, unsigned int uCount)
{
    ENGINE_ASSERT(pFileHandle);
    if (EOpenMode::OM_RB != mOpenMode && EOpenMode::OM_RT != mOpenMode)
    {
        return MXWrite(pBuffer, uSize, uCount, pFileHandle);
    }
    return 0;
}

bool Matrix::Platform::File::GetLine(void *pBuffer, unsigned int uiBufferCount) const
{
    ENGINE_ASSERT(pFileHandle);

    if (MXGetLine((TCHAR *)pBuffer, uiBufferCount, pFileHandle))
    {
        return true;
    }
    return false;
}

bool Matrix::Platform::File::Flush()
{
    return MXFlush(pFileHandle);
}

bool Matrix::Platform::File::Seek(unsigned int uiOffset, unsigned int uiOrigin)
{
    ENGINE_ASSERT(pFileHandle);
    return MXSeek(pFileHandle, uiOffset, uiOrigin);
    return false;
}

bool Matrix::Platform::File::IsValid() const
{
    return (pFileHandle != NULL);
}
void Matrix::Platform::File::DebugInfo() const
{
    TCHAR strLine[MAX_FILE_PATH_SIZE];
    if (pFileHandle)
    {
        MXSprintf(_T("File DebugInfo:\n"));
        while (GetLine(strLine, MAX_FILE_PATH_SIZE))
        {
            MXSprintf(_T("%s"), strLine);
        }
    }
}
bool Matrix::Platform::File::IsFileExist(const TCHAR *pFileName)
{
    struct _stat64i32 kStat;
    if (MXStat(pFileName, &kStat) != 0)
    {

        return false;
    }
    return true;
}

bool Matrix::Platform::File::OpenFile(const TCHAR *pFileName, EOpenMode openMode)
{
    unsigned int uiLen = MXStrLen(pFileName);
    if (uiLen > MAX_FILE_PATH_SIZE - 1)
    {
        return false;
    }
    MXStrCopy(mFileName, MAX_FILE_PATH_SIZE, pFileName);

    mOpenMode = openMode;
    pFileHandle = MXFopen(pFileName, msOpenModeArray[(unsigned int)openMode]);
    ENGINE_ASSERT(pFileHandle);

    struct _stat64i32 kStat;
    MXStat(pFileName, &kStat);
    mFileSize = kStat.st_size;

    return true;
}
