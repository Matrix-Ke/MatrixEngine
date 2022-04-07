#include "pch.h"
#include "MTXFile.h"
using namespace Matrix;


TCHAR MTXFile::ms_cOpenMode[OM_MAX][5] =
{
	_T("rb"),
	_T("wb"),
	_T("rt"),
	_T("wt"),
};

unsigned int MTXFile::m_uiSeekFlag[] =
{
	SEEK_CUR,
	SEEK_END,
	SEEK_SET
};

MTXFile::MTXFile()
{
	m_pFileHandle = NULL;
	m_uiOpenMode = OM_MAX;
	m_uiFileSize = 0;
	//m_tcFileName = nullptr;
}

MTXFile::~MTXFile()
{
	if (m_pFileHandle)
	{
		fclose(m_pFileHandle);
		m_pFileHandle = NULL;
	}
}

bool MTXFile::Flush()
{
	return(fflush(m_pFileHandle) == 0);
}

bool MTXFile::Seek(unsigned int uiOffset, unsigned int uiOrigin)
{
	MTXENGINE_ASSERT(m_pFileHandle);
	// fseek()函数用于把文件指针以origin为起点移动offset个字节, origin数字代表含义：
	//SEEK_SET 0 文件开头
	//SEEK_CUR 1 文件指针当前位置
	//SEEK_END 2 文件尾
	return fseek(m_pFileHandle, uiOffset, uiOrigin);
}

//打开文件的同时将各种文件信息记录下来
bool MTXFile::Open(const TCHAR* pFileName, unsigned int uiOpenMode)
{
	if (m_pFileHandle)
	{
		fclose(m_pFileHandle);
	}
	MTXENGINE_ASSERT(!m_pFileHandle);
	//
	MTXENGINE_ASSERT(uiOpenMode < OM_MAX);

	unsigned int uiLen = MTXStrlen(pFileName);
	if (uiLen < MTXMAX_PATH - 1)
	{
		if (!MTXMemcpy(m_tcFileName, pFileName, static_cast<unsigned long long>(uiLen) + 1))
			return false;
	}
	else
	{
		return false;
	}

	m_uiOpenMode = uiOpenMode;
	if (m_uiOpenMode == OM_RB || m_uiOpenMode == OM_RT)
	{
		struct  _stat64i32 kStat;
		if (_tstat(pFileName, &kStat) != 0)
		{
			return false;
		}
		m_uiFileSize = kStat.st_size;
	}
	//_tfopen_s 是打开宽字符的文件路径, 如果成功返回0，失败则返回相应的错误代码
	errno_t uiError = _tfopen_s(&m_pFileHandle, pFileName, ms_cOpenMode[m_uiOpenMode]);
	if (uiError || !m_pFileHandle)
	{
		return false;
	}

	return true;
}

bool Matrix::MTXFile::Write(const void* pBuffer, unsigned int uiSize, unsigned int uiCount)
{
	MTXENGINE_ASSERT(m_pFileHandle);
	//关于fwrite和 write去别， wirte系统调用， 调用write的时候， 先将数据写到操作系统内核缓冲区， 操作系统会定期将内核缓冲区的数据写回磁盘中。
	//fwrite每次都先将数据写入一个应用缓冲区中， 然后在调用write一次性把相应数据写进内核缓冲区中。
	//ptr − This is the pointer to the array of elements to be written.
	//	size − This is the size in bytes of each element to be written.
	//	nmemb − This is the number of elements, each one with a size of size bytes.
	//	stream − This is the pointer to a FILE object that specifies an output stream.

	return fwrite(pBuffer, uiSize, uiCount, m_pFileHandle);
}

bool Matrix::MTXFile::Read(void* pBuffer, unsigned int uiSize, unsigned int uiCount)
{
	MTXENGINE_ASSERT(m_pFileHandle);
	// return actually read count. 
	return fread(pBuffer, uiSize, uiCount, m_pFileHandle);
}

bool Matrix::MTXFile::GetLine(void* pBuffer, unsigned int uiBufferCount)
{
	MTXENGINE_ASSERT(m_pFileHandle);
	MTXENGINE_ASSERT(pBuffer);
	if (!_fgetts((TCHAR*)pBuffer, uiBufferCount, m_pFileHandle))
	{
		return false;
	}
	return true;
}

bool MTXFile::IsFileExist(const TCHAR* pFileName)
{
	struct _stat64i32 kStat;
	if (_tstat(pFileName, &kStat) != 0)
	{
		return false;
	}
	return true;
}
