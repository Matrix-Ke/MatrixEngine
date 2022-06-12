#pragma once
#include "Core.h"


namespace Matrix
{
	namespace Core
	{
		class MATRIX_CORE_API File
		{
		public:
			//选出几种代表的openmode
			enum  EOpenMode
			{
				OM_RB, //Open a text file for reading. (The file must exist.)
				OM_RT,
				OM_WB,
				OM_WT, //Open a text file for writing. If the file already exists, its contents are destroyed.
				OM_AB,
				OM_AT,
				OM_MAX
			};
			enum  ESeekFlag
			{
				// fseek()函数用于把文件指针以origin为起点移动offset个字节, origin数字代表含义：
				//SEEK_SET 0 文件开头
				//SEEK_CUR 1 文件指针当前位置
				//SEEK_END 2 文件尾
				SF_CUR,
				SF_END,
				SF_SET,
				SF_MAX
			};
			File();
			File(const TCHAR* pFileName, EOpenMode openMode = EOpenMode::OM_WT);
			~File();

			//文件的基本IO操作
			bool Open(const TCHAR* pFileName, EOpenMode openMode = EOpenMode::OM_WT);
			void Fclose();
			USIZE_TYPE Read(void* pBuffer, unsigned int uSize, unsigned int uCount);
			USIZE_TYPE Write(const void* pBuffer, unsigned int uSize, unsigned int uCount);


			bool GetLine(void* pBuffer, unsigned int uiBufferCount)  const;
			inline unsigned int GetFileSize() const
			{
				return mFileSize;
			}


			bool Flush();
			bool Seek(unsigned int uiOffset, unsigned int uiOrigin);

			bool IsValid() const;
			void DebugInfo() const;
			static bool IsFileExist(const TCHAR* pFileName);
		private:
			bool OpenFile(const TCHAR* pFileName, EOpenMode openMode);

		protected:
			static TCHAR msOpenModeArray[(unsigned int)EOpenMode::OM_MAX][7];
			static unsigned int msSeekFlag[(unsigned int)ESeekFlag::SF_MAX];

			FILE* pFileHandle;
			EOpenMode    mOpenMode;
			unsigned int mFileSize; //将需要系统调用获取的数据保存下来
			TCHAR mFileName[MAX_FILE_PATH_SIZE];
		};


	}
}


