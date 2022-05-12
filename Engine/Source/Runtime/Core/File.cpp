#include "File.h"

using namespace Matrix::Core;

TCHAR File::msOpenModeArray[(unsigned int)File::EOpenMode::OM_MAX][5] =
{
	_T("rb"),
	_T("w+b"),
	_T("rt"),
	_T("w+t")
};

unsigned int File::msSeekFlag[(unsigned int)File::ESeekFlag::SF_MAX] =
{
	SEEK_CUR,
	SEEK_END,
	SEEK_SET
};

Matrix::Core::File::File()
{
	this->pFileHandle = nullptr;
	this->mOpenMode = EOpenMode::OM_MAX;
	this->mFileName[0] = EOF;
	this->mFileSize = NULL;
}

Matrix::Core::File::File(const TCHAR* pFileName, EOpenMode openMode)
{
	MTXENGINE_ASSERT(!pFileHandle);
	this->OpenFile(pFileName, openMode);
}

Matrix::Core::File::~File()
{
	this->Fclose();
}

bool Matrix::Core::File::Open(const TCHAR* pFileName, EOpenMode openMode)
{
	//如果有则关闭已经的重新打开新的
	if (pFileHandle)
	{
		MTXFclose(pFileHandle);
	}

	this->OpenFile(pFileName, openMode);
	return true;
}

void Matrix::Core::File::Fclose()
{
	if (pFileHandle)
	{
		MTXFclose(pFileHandle);
		//删除任何指针和句柄之后记得置NULL， 血的教训。
		pFileHandle = NULL;
	};
}

USIZE_TYPE Matrix::Core::File::Read(void* pBuffer, unsigned int uSize, unsigned int uCount)
{
	MTXENGINE_ASSERT(pFileHandle);
	return	MTXRead(pBuffer, uSize, uCount, pFileHandle);
}

USIZE_TYPE Matrix::Core::File::Write(const void* pBuffer, unsigned int uSize, unsigned int uCount)
{
	MTXENGINE_ASSERT(pFileHandle);
	if (EOpenMode::OM_WB == mOpenMode || EOpenMode::OM_WT == mOpenMode)
	{
		return MTXWrite(pBuffer, uSize, uCount, pFileHandle);
	}
	return 0;
}

bool Matrix::Core::File::GetLine(void* pBuffer, unsigned int uiBufferCount)
{
	MTXENGINE_ASSERT(pFileHandle);

	if (MTXGetLine((TCHAR*)pBuffer, uiBufferCount, pFileHandle))
	{
		return true;
	}
	return false;
}

bool Matrix::Core::File::Flush()
{
	return MTXFlush(pFileHandle);
}

bool Matrix::Core::File::Seek(unsigned int uiOffset, unsigned int uiOrigin)
{
	MTXENGINE_ASSERT(pFileHandle);
	return MTXSeek(pFileHandle, uiOffset, uiOrigin);
	return false;
}

bool Matrix::Core::File::IsValid() const
{
	return (pFileHandle != NULL);
}

bool Matrix::Core::File::IsFileExist(const TCHAR* pFileName)
{
	struct _stat64i32 kStat;
	if (MTXStat(pFileName, &kStat) != 0)
	{

		return false;
	}
	return true;
}

bool Matrix::Core::File::OpenFile(const TCHAR* pFileName, EOpenMode openMode)
{
	unsigned int uiLen = MTXStrLen(pFileName);
	if (uiLen > MAX_FILE_PATH_SIZE - 1)
	{
		return false;
	}
	MTXStrCopy(mFileName, MAX_FILE_PATH_SIZE, pFileName);

	mOpenMode = openMode;
	pFileHandle = MTXFopen(pFileName, msOpenModeArray[(unsigned int)openMode]);
	MTXENGINE_ASSERT(pFileHandle);

	struct _stat64i32  kStat;
	MTXStat(pFileName, &kStat);
	mFileSize = kStat.st_size;

	return true;
}
