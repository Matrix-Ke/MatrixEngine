#pragma once
#include "Container.h"
#include "Math.h"
namespace Matrix
{
    namespace Container
    {
        class MATRIX_CONTAINER_API MXString : public MContainer<TCHAR>
        {
        public:
            enum
            {
                BUFFER_SIZE = 2048
            };
            MXString();
            MXString(const TCHAR *String);
            MXString(const MXString &String);
            ~MXString();
            static MXString ms_StringNULL;
            static TCHAR TempBuffer[BUFFER_SIZE];
            inline TCHAR *GetBuffer() const
            {
                return m_pBuffer;
            }
            inline unsigned int GetLength() const
            {

                return (unsigned int)MXStrLen(m_pBuffer);
            }
            void SetTCHARBufferNum(unsigned int uiLength);
            void Clear();
            //����=������
            MXString &operator=(const MXString &String);
            MXString &operator=(const TCHAR *String);

            //����[]������
            TCHAR &operator[](unsigned int i);

            //����+=������
            const MXString &operator+=(const MXString &String);
            const MXString &operator+=(const TCHAR *String);

            //ȡ��ָ���±��ǰ���ַ������ߺ���ַ���
            bool GetString(const MXString &String, unsigned int uiFind, bool bIsFront = true, bool bIsHaveFind = false);
            //���ҵ�iFindNum�γ��ֵ�ָ���ַ���Ȼ��ȡǰ���ַ������ߺ���ַ�����iFIndNum = -1��ʾ���һ�γ��ֵġ�
            bool GetString(const MXString &String, TCHAR cFind, int iFIndNum, bool bIsFront = true, bool bIsHaveFind = false);
            //���ҵ�ǰ�ַ����е�iFindNum�γ��ֵ�String���±꣬����-1���ʾ����ʧ��
            int GetSubStringIndex(const MXString &String, int iFindNum) const;
            bool RemoveSubString(const MXString &String, int iFindNum);
            void Remove(unsigned int i, unsigned int j);
            //ȥ��ָ�����ַ�
            bool StripChars(const MXString &String, const TCHAR *pStripChars);
            //�滻ָ�����ַ�
            bool ReplaceChars(const MXString &String, const TCHAR *pReplaceChars, TCHAR UseChar);
            //ȥ���ַ�����������пո�
            void StringLtrim(const MXString &String);
            //ȥ���ַ������ұ����пո�
            void StringRtrim(const MXString &String);

            void Format(const TCHAR *pcString, ...);

        protected:
            TCHAR *m_pBuffer;
        };
        //����+������
        MATRIX_CONTAINER_API MXString operator+(const MXString &String1, const MXString &String2);
        MATRIX_CONTAINER_API MXString operator+(const MXString &String1, const TCHAR *String2);
        MATRIX_CONTAINER_API MXString operator+(const TCHAR *String1, const MXString &String2);

        //���ڷ��ش���0��С�ڷ���С��0�����ڷ���0
        MATRIX_CONTAINER_API int CompareString(const MXString &String1, const MXString &String2);
        MATRIX_CONTAINER_API int CompareString(const MXString &String1, const TCHAR *String2);
        MATRIX_CONTAINER_API int CompareString(const TCHAR *String1, const MXString &String2);

        //����==������
        MATRIX_CONTAINER_API bool operator==(const MXString &String1, const MXString &String2);
        MATRIX_CONTAINER_API bool operator==(const MXString &String1, const TCHAR *String2);
        MATRIX_CONTAINER_API bool operator==(const TCHAR *String1, MXString &String2);
        //����!=������
        MATRIX_CONTAINER_API bool operator!=(const MXString &String1, const MXString &String2);
        MATRIX_CONTAINER_API bool operator!=(const MXString &String1, const TCHAR *String2);
        MATRIX_CONTAINER_API bool operator!=(const TCHAR *String1, const MXString &String2);

        MATRIX_CONTAINER_API int StringToInt(const MXString &String);
        MATRIX_CONTAINER_API MXString IntToString(int i);

        MATRIX_CONTAINER_API unsigned int StringToUInt(const MXString &String);
        MATRIX_CONTAINER_API MXString UIntToString(unsigned int i);

        MATRIX_CONTAINER_API bool StringToBool(const MXString &String);
        MATRIX_CONTAINER_API MXString BoolToString(bool i);
        MATRIX_CONTAINER_API MXString BoolToString(unsigned int i);

        MATRIX_CONTAINER_API float StringToReal(const MXString &String);
        MATRIX_CONTAINER_API MXString RealToString(float Value);

        class MATRIX_CONTAINER_API MXFileName : public MXString
        {
        public:
            MXFileName()
            {
            }
            MXFileName(const TCHAR *String) : MXString(String)
            {
            }
            MXFileName(const MXString &String) : MXString(String)
            {
            }
            ~MXFileName()
            {
            }
            bool GetExtension(MXString &Extension);
            bool GetBaseName(MXString &BaseName);
            bool GetBaseNameAndExtension(MXString &BaseNameAndExtension);
            bool GetPath(MXString &Path);
            bool GetPathAndName(MXString &PathAndName);
        };
    }
}
