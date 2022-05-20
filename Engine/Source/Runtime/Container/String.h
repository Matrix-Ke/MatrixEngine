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
			//����=������
			MString& operator=(const MString& String);
			MString& operator=(const TCHAR* String);

			//����[]������
			TCHAR& operator[](unsigned int i);

			//����+=������
			const MString& operator+=(const MString& String);
			const MString& operator+=(const TCHAR* String);

			//ȡ��ָ���±��ǰ���ַ������ߺ���ַ���
			bool GetString(const MString& String, unsigned int uiFind, bool bIsFront = true, bool bIsHaveFind = false);
			//���ҵ�iFindNum�γ��ֵ�ָ���ַ���Ȼ��ȡǰ���ַ������ߺ���ַ�����iFIndNum = -1��ʾ���һ�γ��ֵġ�
			bool GetString(const MString& String, TCHAR cFind, int iFIndNum, bool bIsFront = true, bool bIsHaveFind = false);
			//���ҵ�ǰ�ַ����е�iFindNum�γ��ֵ�String���±꣬����-1���ʾ����ʧ��
			int GetSubStringIndex(const MString& String, int iFindNum) const;
			bool RemoveSubString(const MString& String, int iFindNum);
			void Remove(unsigned int i, unsigned int j);
			//ȥ��ָ�����ַ�
			bool StripChars(const MString& String, const TCHAR* pStripChars);
			//�滻ָ�����ַ�
			bool ReplaceChars(const MString& String, const TCHAR* pReplaceChars, TCHAR UseChar);
			//ȥ���ַ�����������пո�
			void StringLtrim(const MString& String);
			//ȥ���ַ������ұ����пո�
			void StringRtrim(const MString& String);

			void Format(const TCHAR* pcString, ...);

		protected:
			TCHAR* m_pBuffer;
		};
		//����+������
		MATRIX_CONTAINER_API MString operator+(const MString& String1, const MString& String2);
		MATRIX_CONTAINER_API MString operator+(const MString& String1, const TCHAR* String2);
		MATRIX_CONTAINER_API MString operator+(const TCHAR* String1, const MString& String2);

		//���ڷ��ش���0��С�ڷ���С��0�����ڷ���0
		MATRIX_CONTAINER_API int CompareString(const MString& String1, const MString& String2);
		MATRIX_CONTAINER_API int CompareString(const MString& String1, const TCHAR* String2);
		MATRIX_CONTAINER_API int CompareString(const TCHAR* String1, const MString& String2);

		//����==������
		MATRIX_CONTAINER_API bool operator==(const MString& String1, const MString& String2);
		MATRIX_CONTAINER_API bool operator==(const MString& String1, const TCHAR* String2);
		MATRIX_CONTAINER_API bool operator==(const TCHAR* String1, MString& String2);
		//����!=������
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
