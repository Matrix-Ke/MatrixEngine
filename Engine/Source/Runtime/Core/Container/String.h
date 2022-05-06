#pragma once
#include "Container.h"
#include "Math.h"
namespace Matrix
{
	namespace Container
	{
		class MATRIX_CORE_API MTXString : public MContainer<TCHAR>
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
			//����=������
			MTXString& operator =(const MTXString& String);
			MTXString& operator =(const TCHAR* String);

			//����[]������
			TCHAR& operator[](unsigned int i);

			//����+=������
			const MTXString& operator +=(const MTXString& String);
			const MTXString& operator +=(const TCHAR* String);

			//ȡ��ָ���±��ǰ���ַ������ߺ���ַ���
			bool GetString(const MTXString& String, unsigned int uiFind, bool bIsFront = true, bool bIsHaveFind = false);
			//���ҵ�iFindNum�γ��ֵ�ָ���ַ���Ȼ��ȡǰ���ַ������ߺ���ַ�����iFIndNum = -1��ʾ���һ�γ��ֵġ�
			bool GetString(const MTXString& String, TCHAR cFind, int iFIndNum, bool bIsFront = true, bool bIsHaveFind = false);
			//���ҵ�ǰ�ַ����е�iFindNum�γ��ֵ�String���±꣬����-1���ʾ����ʧ��
			int GetSubStringIndex(const MTXString& String, int iFindNum)const;
			bool RemoveSubString(const MTXString& String, int iFindNum);
			void Remove(unsigned int i, unsigned int j);
			//ȥ��ָ�����ַ�
			bool StripChars(const MTXString& String, const TCHAR* pStripChars);
			//�滻ָ�����ַ�
			bool ReplaceChars(const MTXString& String, const TCHAR* pReplaceChars, TCHAR UseChar);
			//ȥ���ַ�����������пո�
			void StringLtrim(const MTXString& String);
			//ȥ���ַ������ұ����пո�
			void StringRtrim(const MTXString& String);

			void Format(const TCHAR* pcString, ...);
		protected:
			TCHAR* m_pBuffer;

		};
		//����+������
		MATRIX_CORE_API MTXString operator +(const MTXString& String1, const MTXString& String2);
		MATRIX_CORE_API MTXString operator +(const MTXString& String1, const TCHAR* String2);
		MATRIX_CORE_API MTXString operator +(const TCHAR* String1, const MTXString& String2);

		//���ڷ��ش���0��С�ڷ���С��0�����ڷ���0 
		MATRIX_CORE_API int CompareString(const MTXString& String1, const MTXString& String2);
		MATRIX_CORE_API int CompareString(const MTXString& String1, const TCHAR* String2);
		MATRIX_CORE_API int CompareString(const TCHAR* String1, const MTXString& String2);

		//����==������
		MATRIX_CORE_API bool operator ==(const MTXString& String1, const MTXString& String2);
		MATRIX_CORE_API bool operator ==(const MTXString& String1, const TCHAR* String2);
		MATRIX_CORE_API bool operator ==(const TCHAR* String1, MTXString& String2);
		//����!=������
		MATRIX_CORE_API bool operator !=(const MTXString& String1, const MTXString& String2);
		MATRIX_CORE_API bool operator !=(const MTXString& String1, const TCHAR* String2);
		MATRIX_CORE_API bool operator !=(const TCHAR* String1, const MTXString& String2);

		MATRIX_CORE_API int StringToInt(const MTXString& String);
		MATRIX_CORE_API MTXString IntToString(int i);

		MATRIX_CORE_API unsigned int StringToUInt(const MTXString& String);
		MATRIX_CORE_API MTXString UIntToString(unsigned int i);

		MATRIX_CORE_API bool StringToBool(const MTXString& String);
		MATRIX_CORE_API MTXString BoolToString(bool i);
		MATRIX_CORE_API MTXString BoolToString(unsigned int i);

		MATRIX_CORE_API float StringToReal(const MTXString& String);
		MATRIX_CORE_API MTXString RealToString(float Value);


		class MATRIX_CORE_API MTXFileName : public MTXString
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
