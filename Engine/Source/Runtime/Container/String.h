#pragma once
#include "Container.h"
#include "Math.h"
namespace Matrix
{
	namespace Container
	{
		class MATRIX_CONTAINER_API MTXString : public MContainer<TCHAR>
		{
		public:
			enum
			{
				BUFFER_SIZE = 2048
			};
			MTXString();
			MTXString(const TCHAR* String);
			MTXString(const MTXString& String);
			~MTXString();
			static MTXString ms_StringNULL;
			static TCHAR TempBuffer[BUFFER_SIZE];
			inline TCHAR* GetBuffer()const
			{
				return m_pBuffer;
			}
			inline unsigned int GetLength()const
			{

				return (unsigned int)MTXStrLen(m_pBuffer);
			}
			void SetTCHARBufferNum(unsigned int uiLength);
			void Clear();
			//重载=操作符
			MTXString& operator =(const MTXString& String);
			MTXString& operator =(const TCHAR* String);

			//重载[]操作符
			TCHAR& operator[](unsigned int i);

			//重载+=操作符
			const MTXString& operator +=(const MTXString& String);
			const MTXString& operator +=(const TCHAR* String);

			//取得指定下标的前段字符串或者后段字符串
			bool GetString(const MTXString& String, unsigned int uiFind, bool bIsFront = true, bool bIsHaveFind = false);
			//查找第iFindNum次出现的指定字符，然后取前段字符串或者后段字符串。iFIndNum = -1表示最后一次出现的。
			bool GetString(const MTXString& String, TCHAR cFind, int iFIndNum, bool bIsFront = true, bool bIsHaveFind = false);
			//查找当前字符串中第iFindNum次出现的String的下标，返回-1则表示查找失败
			int GetSubStringIndex(const MTXString& String, int iFindNum)const;
			bool RemoveSubString(const MTXString& String, int iFindNum);
			void Remove(unsigned int i, unsigned int j);
			//去掉指定的字符
			bool StripChars(const MTXString& String, const TCHAR* pStripChars);
			//替换指定的字符
			bool ReplaceChars(const MTXString& String, const TCHAR* pReplaceChars, TCHAR UseChar);
			//去掉字符串的左边所有空格
			void StringLtrim(const MTXString& String);
			//去掉字符串的右边所有空格
			void StringRtrim(const MTXString& String);

			void Format(const TCHAR* pcString, ...);
		protected:
			TCHAR* m_pBuffer;

		};
		//重载+操作符
		MATRIX_CONTAINER_API MTXString operator +(const MTXString& String1, const MTXString& String2);
		MATRIX_CONTAINER_API MTXString operator +(const MTXString& String1, const TCHAR* String2);
		MATRIX_CONTAINER_API MTXString operator +(const TCHAR* String1, const MTXString& String2);

		//大于返回大于0，小于返回小于0，等于返回0 
		MATRIX_CONTAINER_API int CompareString(const MTXString& String1, const MTXString& String2);
		MATRIX_CONTAINER_API int CompareString(const MTXString& String1, const TCHAR* String2);
		MATRIX_CONTAINER_API int CompareString(const TCHAR* String1, const MTXString& String2);

		//重载==操作符
		MATRIX_CONTAINER_API bool operator ==(const MTXString& String1, const MTXString& String2);
		MATRIX_CONTAINER_API bool operator ==(const MTXString& String1, const TCHAR* String2);
		MATRIX_CONTAINER_API bool operator ==(const TCHAR* String1, MTXString& String2);
		//重载!=操作符
		MATRIX_CONTAINER_API bool operator !=(const MTXString& String1, const MTXString& String2);
		MATRIX_CONTAINER_API bool operator !=(const MTXString& String1, const TCHAR* String2);
		MATRIX_CONTAINER_API bool operator !=(const TCHAR* String1, const MTXString& String2);

		MATRIX_CONTAINER_API int StringToInt(const MTXString& String);
		MATRIX_CONTAINER_API MTXString IntToString(int i);

		MATRIX_CONTAINER_API unsigned int StringToUInt(const MTXString& String);
		MATRIX_CONTAINER_API MTXString UIntToString(unsigned int i);

		MATRIX_CONTAINER_API bool StringToBool(const MTXString& String);
		MATRIX_CONTAINER_API MTXString BoolToString(bool i);
		MATRIX_CONTAINER_API MTXString BoolToString(unsigned int i);

		MATRIX_CONTAINER_API float StringToReal(const MTXString& String);
		MATRIX_CONTAINER_API MTXString RealToString(float Value);


		class MATRIX_CONTAINER_API MTXFileName : public MTXString
		{
		public:
			MTXFileName()
			{

			}
			MTXFileName(const TCHAR* String) :MTXString(String)
			{
			}
			MTXFileName(const MTXString& String) :MTXString(String)
			{

			}
			~MTXFileName()
			{

			}
			bool GetExtension(MTXString& Extension);
			bool GetBaseName(MTXString& BaseName);
			bool GetBaseNameAndExtension(MTXString& BaseNameAndExtension);
			bool GetPath(MTXString& Path);
			bool GetPathAndName(MTXString& PathAndName);
		};
	}
}
