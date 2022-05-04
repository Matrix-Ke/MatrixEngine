#pragma once
#include "Core.h"


namespace Matrix
{
	class MATRIXCORE_API MTXFile
	{
	public:
		enum //Open Mode
		{
			OM_RB,
			OM_WB,
			OM_RT,
			OM_WT,
			OM_MAX
		};
		enum
		{
			MTXMAX_PATH = 256
		};
		enum	//Seek Flag
		{
			SF_CUR,
			SF_END,
			SF_SET,
			SF_MAX

		};
		MTXFile();
		~MTXFile();
		bool Flush();

		bool Seek(unsigned int uiOffset, unsigned int uiOrigin);
		bool Open(const TCHAR* pFileName, unsigned int uiOpenMode);
		bool Write(const void* pBuffer, unsigned int uiSize, unsigned int uiCount);
		bool Read(void* pBuffer, unsigned int uiSize, unsigned int uiCount);

		bool GetLine(void* pBuffer, unsigned int uiBufferCount);
		inline unsigned int GetFileSize()const
		{
			return m_uiFileSize;
		}
		static bool IsFileExist(const TCHAR* pFileName);

	protected:
		static TCHAR ms_cOpenMode[OM_MAX][5];
		static unsigned int m_uiSeekFlag[];
		FILE* m_pFileHandle;
		unsigned int m_uiOpenMode;
		unsigned int m_uiFileSize;
		//左右值区分的关键是能否取得内存地址
		TCHAR m_tcFileName[MTXMAX_PATH];
	};
}


