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
            //重载=操作符
            MXString &operator=(const MXString &String);
            MXString &operator=(const TCHAR *String);

            //重载[]操作符
            TCHAR &operator[](unsigned int i);

            //重载+=操作符
            const MXString &operator+=(const MXString &String);
            const MXString &operator+=(const TCHAR *String);

            //取得指定下标的前段字符串或者后段字符串
            bool GetString(const MXString &String, unsigned int uiFind, bool bIsFront = true, bool bIsHaveFind = false);
            //查找第iFindNum次出现的指定字符，然后取前段字符串或者后段字符串。iFIndNum = -1表示最后一次出现的。
            bool GetString(const MXString &String, TCHAR cFind, int iFIndNum, bool bIsFront = true, bool bIsHaveFind = false);
            //查找当前字符串中第iFindNum次出现的String的下标，返回-1则表示查找失败
            int GetSubStringIndex(const MXString &String, int iFindNum) const;
            bool RemoveSubString(const MXString &String, int iFindNum);
            void Remove(unsigned int i, unsigned int j);
            //去掉指定的字符
            bool StripChars(const MXString &String, const TCHAR *pStripChars);
            //替换指定的字符
            bool ReplaceChars(const MXString &String, const TCHAR *pReplaceChars, TCHAR UseChar);
            //去掉字符串的左边所有空格
            void StringLtrim(const MXString &String);
            //去掉字符串的右边所有空格
            void StringRtrim(const MXString &String);

            void Format(const TCHAR *pcString, ...);

        protected:
            TCHAR *m_pBuffer;
        };
        //重载+操作符
        MATRIX_CONTAINER_API MXString operator+(const MXString &String1, const MXString &String2);
        MATRIX_CONTAINER_API MXString operator+(const MXString &String1, const TCHAR *String2);
        MATRIX_CONTAINER_API MXString operator+(const TCHAR *String1, const MXString &String2);

        //大于返回大于0，小于返回小于0，等于返回0
        MATRIX_CONTAINER_API int CompareString(const MXString &String1, const MXString &String2);
        MATRIX_CONTAINER_API int CompareString(const MXString &String1, const TCHAR *String2);
        MATRIX_CONTAINER_API int CompareString(const TCHAR *String1, const MXString &String2);

        //重载==操作符
        MATRIX_CONTAINER_API bool operator==(const MXString &String1, const MXString &String2);
        MATRIX_CONTAINER_API bool operator==(const MXString &String1, const TCHAR *String2);
        MATRIX_CONTAINER_API bool operator==(const TCHAR *String1, MXString &String2);
        //重载!=操作符
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
