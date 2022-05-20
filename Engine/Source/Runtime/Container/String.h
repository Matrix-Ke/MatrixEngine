#pragma once
#include "Container.h"
#include "Math.h"
namespace Matrix
{
	namespace Container
	{
		class MATRIX_CONTAINER_API MString : public MContainer<TCHAR>
		{
		public:
			enum
			{
				BUFFER_SIZE = 2048
			};
			MString();
			MString(const TCHAR* String);
			MString(const MString& String);
			~MString();
			static MString ms_StringNULL;
			static TCHAR TempBuffer[BUFFER_SIZE];
			inline TCHAR* GetBuffer() const
			{
				return m_pBuffer;
			}
			inline unsigned int GetLength() const
			{

				return (unsigned int)Core::MXStrLen(m_pBuffer);
			}
			void SetTCHARBufferNum(unsigned int uiLength);
			void Clear();
			//重载=操作符
			MString& operator=(const MString& String);
			MString& operator=(const TCHAR* String);

			//重载[]操作符
			TCHAR& operator[](unsigned int i);

			//重载+=操作符
			const MString& operator+=(const MString& String);
			const MString& operator+=(const TCHAR* String);

			//取得指定下标的前段字符串或者后段字符串
			bool GetString(const MString& String, unsigned int uiFind, bool bIsFront = true, bool bIsHaveFind = false);
			//查找第iFindNum次出现的指定字符，然后取前段字符串或者后段字符串。iFIndNum = -1表示最后一次出现的。
			bool GetString(const MString& String, TCHAR cFind, int iFIndNum, bool bIsFront = true, bool bIsHaveFind = false);
			//查找当前字符串中第iFindNum次出现的String的下标，返回-1则表示查找失败
			int GetSubStringIndex(const MString& String, int iFindNum) const;
			bool RemoveSubString(const MString& String, int iFindNum);
			void Remove(unsigned int i, unsigned int j);
			//去掉指定的字符
			bool StripChars(const MString& String, const TCHAR* pStripChars);
			//替换指定的字符
			bool ReplaceChars(const MString& String, const TCHAR* pReplaceChars, TCHAR UseChar);
			//去掉字符串的左边所有空格
			void StringLtrim(const MString& String);
			//去掉字符串的右边所有空格
			void StringRtrim(const MString& String);

			void Format(const TCHAR* pcString, ...);

		protected:
			TCHAR* m_pBuffer;
		};
		//重载+操作符
		MATRIX_CONTAINER_API MString operator+(const MString& String1, const MString& String2);
		MATRIX_CONTAINER_API MString operator+(const MString& String1, const TCHAR* String2);
		MATRIX_CONTAINER_API MString operator+(const TCHAR* String1, const MString& String2);

		//大于返回大于0，小于返回小于0，等于返回0
		MATRIX_CONTAINER_API int CompareString(const MString& String1, const MString& String2);
		MATRIX_CONTAINER_API int CompareString(const MString& String1, const TCHAR* String2);
		MATRIX_CONTAINER_API int CompareString(const TCHAR* String1, const MString& String2);

		//重载==操作符
		MATRIX_CONTAINER_API bool operator==(const MString& String1, const MString& String2);
		MATRIX_CONTAINER_API bool operator==(const MString& String1, const TCHAR* String2);
		MATRIX_CONTAINER_API bool operator==(const TCHAR* String1, MString& String2);
		//重载!=操作符
		MATRIX_CONTAINER_API bool operator!=(const MString& String1, const MString& String2);
		MATRIX_CONTAINER_API bool operator!=(const MString& String1, const TCHAR* String2);
		MATRIX_CONTAINER_API bool operator!=(const TCHAR* String1, const MString& String2);

		MATRIX_CONTAINER_API int StringToInt(const MString& String);
		MATRIX_CONTAINER_API MString IntToString(int i);

		MATRIX_CONTAINER_API unsigned int StringToUInt(const MString& String);
		MATRIX_CONTAINER_API MString UIntToString(unsigned int i);

		MATRIX_CONTAINER_API bool StringToBool(const MString& String);
		MATRIX_CONTAINER_API MString BoolToString(bool i);
		MATRIX_CONTAINER_API MString BoolToString(unsigned int i);

		MATRIX_CONTAINER_API float StringToReal(const MString& String);
		MATRIX_CONTAINER_API MString RealToString(float Value);

		class MATRIX_CONTAINER_API MFileName : public MString
		{
		public:
			MFileName()
			{
			}
			MFileName(const TCHAR* String) : MString(String)
			{
			}
			MFileName(const MString& String) : MString(String)
			{
			}
			~MFileName()
			{
			}
			bool GetExtension(MString& Extension);
			bool GetBaseName(MString& BaseName);
			bool GetBaseNameAndExtension(MString& BaseNameAndExtension);
			bool GetPath(MString& Path);
			bool GetPathAndName(MString& PathAndName);
		};
	}
}
