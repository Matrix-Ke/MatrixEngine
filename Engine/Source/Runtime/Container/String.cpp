#include "String.h"

using namespace Matrix::Container;
using namespace Matrix::Core;

MXString MXString::ms_StringNULL;
TCHAR MXString::TempBuffer[BUFFER_SIZE] = {0};
MXString::MXString()
{
    m_pBuffer = NULL;
    m_pBuffer = MX_NEW TCHAR[1];
    MX_ENGINE_ASSERT(m_pBuffer);
    m_pBuffer[0] = _T('\0');
}
MXString::MXString(const TCHAR *String)
{
    MX_ENGINE_ASSERT(String);
    m_pBuffer = NULL;
    if (String)
    {
        unsigned int uiLength = (unsigned int)MXStrLen(String);
        m_pBuffer = MX_NEW TCHAR[uiLength + 1];
        MX_ENGINE_ASSERT(m_pBuffer);

        MXStrCopy(m_pBuffer, uiLength + 1, String);
    }
    else
    {
        m_pBuffer = MX_NEW TCHAR[1];
        MX_ENGINE_ASSERT(m_pBuffer);
        m_pBuffer[0] = _T('\0');
    }
}
MXString::MXString(const MXString &String)
{
    m_pBuffer = NULL;
    unsigned int uiLength = String.GetLength();
    m_pBuffer = MX_NEW TCHAR[uiLength + 1];
    MX_ENGINE_ASSERT(m_pBuffer);

    MXStrCopy(m_pBuffer, uiLength + 1, String.GetBuffer());
}
MXString::~MXString()
{

    ENGINE_DELETE(m_pBuffer);
}
void MXString::SetTCHARBufferNum(unsigned int uiLength)
{
    ENGINE_DELETE(m_pBuffer);
    m_pBuffer = MX_NEW TCHAR[uiLength + 1];
    m_pBuffer[uiLength] = _T('\0');
}
void MXString::Clear()
{

    ENGINE_DELETE(m_pBuffer);
    m_pBuffer = MX_NEW TCHAR[1];
    MX_ENGINE_ASSERT(m_pBuffer);
    m_pBuffer[0] = _T('\0');
}
MXString &MXString::operator=(const MXString &String)
{
    ENGINE_DELETE(m_pBuffer);
    unsigned int uiLength = String.GetLength();
    m_pBuffer = MX_NEW TCHAR[uiLength + 1];
    MX_ENGINE_ASSERT(m_pBuffer);

    MXStrCopy(m_pBuffer, uiLength + 1, String.GetBuffer());
    return *this;
}
MXString &MXString::operator=(const TCHAR *String)
{
    ENGINE_DELETE(m_pBuffer);
    if (String)
    {
        unsigned int uiLength = (unsigned int)MXStrLen(String);
        m_pBuffer = MX_NEW TCHAR[uiLength + 1];
        MX_ENGINE_ASSERT(m_pBuffer);

        MXStrCopy(m_pBuffer, uiLength + 1, String);
    }
    else
    {
        MXString();
    }
    return *this;
}

TCHAR &MXString::operator[](unsigned int i)
{
    return m_pBuffer[i];
}

const MXString &MXString::operator+=(const MXString &String)
{
    unsigned int uiLength1 = GetLength();
    unsigned int uiLength2 = String.GetLength();
    if (!uiLength1)
    {
        *this = String;
        return *this;
    }
    else if (!uiLength2)
        return *this;
    else
    {
        TCHAR *pBuffer = NULL;
        unsigned int uiLength = uiLength2 + uiLength1 + 1;
        pBuffer = MX_NEW TCHAR[uiLength];
        MX_ENGINE_ASSERT(pBuffer);

        MXStrCopy(pBuffer, uiLength, GetBuffer());
        MXStrcat(pBuffer, uiLength, String.GetBuffer());

        ENGINE_DELETE(m_pBuffer);
        m_pBuffer = pBuffer;
        return *this;
    }
}
const MXString &MXString::operator+=(const TCHAR *String)
{
    unsigned int uiLength1 = GetLength();
    unsigned int uiLength2 = 0;
    if (String)
    {
        uiLength2 = (unsigned int)MXStrLen(String);
    }
    if (!uiLength1)
    {
        *this = String;
        return *this;
    }
    else if (!uiLength2)
        return *this;
    else
    {
        TCHAR *pBuffer = NULL;
        unsigned int uiLength = uiLength2 + uiLength1 + 1;
        pBuffer = MX_NEW TCHAR[uiLength];
        MX_ENGINE_ASSERT(pBuffer);

        MXStrCopy(pBuffer, uiLength, GetBuffer());
        MXStrcat(pBuffer, uiLength, String);

        ENGINE_DELETE(m_pBuffer);
        m_pBuffer = pBuffer;
        return *this;
    }
}
bool MXString::GetString(const MXString &String, unsigned int uiFind, bool bIsFront, bool bIsHaveFind)
{
    if (uiFind >= String.GetLength())
    {
        return false;
    }

    unsigned int uiLength = 0;
    unsigned int uiIndex = 0;
    if (bIsFront)
    {
        uiLength = uiFind;
        uiIndex = 0;
    }
    else
    {
        uiLength = String.GetLength() - uiFind - 1;
        uiIndex = uiFind + 1;
    }
    if (bIsHaveFind)
    {
        uiLength++;
        if (!bIsFront)
        {
            uiIndex--;
        }
    }
    if (uiIndex >= String.GetLength())
    {
        return false;
    }
    ENGINE_DELETE(m_pBuffer);
    m_pBuffer = MX_NEW TCHAR[uiLength + 1];
    MXMemcpy(m_pBuffer, &String.m_pBuffer[uiIndex], uiLength, uiLength + 1);
    m_pBuffer[uiLength] = _T('\0');
    return true;
}
bool MXString::GetString(const MXString &String, TCHAR cFind, int iFIndNum, bool bIsFront, bool bIsHaveFind)
{
    if (iFIndNum == 0)
    {
        return false;
    }
    unsigned int uiFIndNumTemp = 0;
    int uiIndex = -1;
    for (unsigned int i = 0; i < String.GetLength(); i++)
    {
        if (cFind == String.m_pBuffer[i])
        {
            uiFIndNumTemp++;
            uiIndex = i;
        }
        if (uiFIndNumTemp == iFIndNum)
        {
            break;
        }
    }
    if (uiIndex == -1)
    {
        return false;
    }
    return GetString(String, uiIndex, bIsFront, bIsHaveFind);
}
int MXString::GetSubStringIndex(const MXString &String, int iFindNum) const
{
    if (GetLength() < String.GetLength())
    {
        return -1;
    }
    unsigned int uiFindNumTemp = 0;
    int iFindIndex = -1;
    for (unsigned int Index = 0; Index < GetLength(); Index++)
    {
        unsigned int j = 0;
        for (unsigned int i = Index; i < String.GetLength() + Index; i++)
        {
            if (m_pBuffer[i] == String.m_pBuffer[j])
            {
                j++;
                continue;
            }
            else
            {
                break;
            }
        }
        if (j == String.GetLength())
        {
            iFindIndex = Index;
            uiFindNumTemp++;
            if (uiFindNumTemp == iFindNum)
            {

                return iFindIndex;
            }
        }
    }

    return iFindIndex;
}
bool MXString::RemoveSubString(const MXString &String, int iFindNum)
{
    if (GetLength() < String.GetLength())
    {
        return false;
    }
    unsigned int uiFindNumTemp = 0;
    int iFindIndex = -1;
    for (unsigned int Index = 0; Index < GetLength(); Index++)
    {
        unsigned int j = 0;
        for (unsigned int i = Index; i < String.GetLength() + Index; i++)
        {
            if (m_pBuffer[i] == String.m_pBuffer[j])
            {
                j++;
                continue;
            }
            else
            {
                break;
            }
        }
        if (j == String.GetLength())
        {
            iFindIndex = Index;
            uiFindNumTemp++;
            if (uiFindNumTemp == iFindNum)
            {
                Remove(iFindIndex, String.GetLength() + iFindIndex - 1);
                return true;
            }
        }
    }
    if (iFindIndex >= 0)
    {
        Remove(iFindIndex, String.GetLength() + iFindIndex - 1);
        return true;
    }
    return false;
}
void MXString::Remove(unsigned int i, unsigned int j)
{
    if (j > GetLength() - 1)
    {
        j = GetLength() - 1;
    }
    if (i > j)
    {
        return;
    }
    unsigned int uiLength = j - i + 1;
    unsigned DeltaLength = GetLength() - uiLength;
    TCHAR *pBuffer = MX_NEW TCHAR[DeltaLength + 1];
    pBuffer[DeltaLength] = _T('\0');
    if (i > 0)
    {
        MXMemcpy(pBuffer, m_pBuffer, i);
    }
    unsigned int LeftNum = DeltaLength - i;
    if (LeftNum > 0)
    {
        MXMemcpy(pBuffer + i, m_pBuffer + i + uiLength, LeftNum);
    }
    ENGINE_DELETE(m_pBuffer);
    m_pBuffer = pBuffer;
}
bool MXString::StripChars(const MXString &String, const TCHAR *pStripChars)
{
    if (String.GetLength() > BUFFER_SIZE || !pStripChars)
    {
        return false;
    }

    unsigned int strip_chars_len = MXStrLen(pStripChars);
    TCHAR *_string_in = String.GetBuffer(), *_string_out = TempBuffer;
    while (*_string_in != _T('\0'))
    {
        int flag = 0;
        for (unsigned int i = 0; i < strip_chars_len; i++)
        {
            if (*_string_in == pStripChars[i])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            *_string_out = *_string_in;
            _string_out++;
        }
        _string_in++;
    }
    *_string_out = _T('\0');
    *this = TempBuffer;
    return true;
}

bool MXString::ReplaceChars(const MXString &String, const TCHAR *pReplaceChars, TCHAR UseChar)
{
    if (String.GetLength() > BUFFER_SIZE || !pReplaceChars)
    {
        return false;
    }
    unsigned int replace_chars_len = MXStrLen(pReplaceChars);
    TCHAR *_string_in = String.GetBuffer(), *_string_out = TempBuffer;
    while (*_string_in != _T('\0'))
    {
        int flag = 0;
        for (unsigned int i = 0; i < replace_chars_len; i++)
        {
            if (*_string_in == pReplaceChars[i])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            *_string_out = *_string_in;
        }
        else
        {
            *_string_out = UseChar;
        }
        _string_out++;
        _string_in++;
    }
    *_string_out = _T('\0');

    *this = TempBuffer;
    return true;
}

void MXString::StringLtrim(const MXString &String)
{
    int index = 0;
    TCHAR *pString = String.GetBuffer();
    while (_istspace(pString[index]))
        index++;
    if (index == 0)
        return;
    else
    {
        unsigned int uiLength = String.GetLength();
        MXMemcpy((void *)TempBuffer, (void *)(pString + index), ((uiLength - index) + 1) * sizeof(TCHAR));
        *this = TempBuffer;
    }
}

void MXString::StringRtrim(const MXString &String)
{
    unsigned int uiLength = String.GetLength();
    if (!uiLength)
    {
        return;
    }
    unsigned int index = uiLength - 1;
    TCHAR *pString = String.GetBuffer();
    while (MXIsSpace(pString[index]))
        index--;

    MXMemcpy((void *)TempBuffer, (void *)(pString), (index + 1) * sizeof(TCHAR));
    index++;
    TempBuffer[index] = _T('\0');
    *this = TempBuffer;
}
void MXString::Format(const TCHAR *pcString, ...)
{
    static TCHAR LogBuffer[LOG_BUFFER_SIZE];
    char *pArgs;
    pArgs = (char *)&pcString + sizeof(pcString);
    MXSprintf(LogBuffer, LOG_BUFFER_SIZE, pcString, pArgs);
    *this = LogBuffer;
}
bool MXFileName::GetExtension(MXString &Extension)
{
    return Extension.GetString(*this, _T('.'), -1, false, false);
}
bool MXFileName::GetPathAndName(MXString &PathAndName)
{
    return PathAndName.GetString(*this, _T('.'), -1);
}
bool MXFileName::GetBaseName(MXString &BaseName)
{
    bool bResult = false;
    MXString BaseNameAndExtension;
    bResult = GetBaseNameAndExtension(BaseNameAndExtension);
    if (!bResult)
    {
        return false;
    }
    bResult = BaseName.GetString(BaseNameAndExtension, _T('.'), -1);
    return bResult;
}
bool MXFileName::GetBaseNameAndExtension(MXString &BaseNameAndExtension)
{
    bool bResult = false;
    bResult = BaseNameAndExtension.GetString(*this, _T('\\'), -1, false, false);
    if (!bResult)
    {
        bResult = BaseNameAndExtension.GetString(*this, _T('/'), -1, false, false);
    }
    return bResult;
}
bool MXFileName::GetPath(MXString &Path)
{
    bool bResult = false;
    bResult = Path.GetString(*this, _T('\\'), -1, true, false);
    if (!bResult)
    {
        bResult = Path.GetString(*this, _T('/'), -1, true, false);
    }
    return bResult;
}
namespace Matrix
{
    namespace Container
    {
        MXString operator+(const MXString &String1, const MXString &String2)
        {
            unsigned int uiLength1 = String1.GetLength();
            unsigned int uiLength2 = String2.GetLength();
            if (!uiLength2)
                return String1;
            else if (!uiLength1)
                return String2;
            else
            {
                TCHAR *pBuffer = NULL;
                unsigned int uiLength = uiLength2 + uiLength1 + 1;
                pBuffer = MX_NEW TCHAR[uiLength];
                MX_ENGINE_ASSERT(pBuffer);

                MXStrCopy(pBuffer, uiLength, String1.GetBuffer());
                MXStrcat(pBuffer, uiLength, String2.GetBuffer());
                MXString ReturnValue(pBuffer);
                ENGINE_DELETE(pBuffer);
                return ReturnValue;
            }
        }
        MXString operator+(const MXString &String1, const TCHAR *String2)
        {
            MX_ENGINE_ASSERT(String2);
            unsigned int uiLength1 = String1.GetLength();
            unsigned int uiLength2 = 0;
            if (String2)
            {
                uiLength2 = (unsigned int)MXStrLen(String2);
            }

            if (!uiLength2)
                return String1;
            else if (!uiLength1)
                return MXString(String2);
            else
            {
                TCHAR *pBuffer = NULL;
                unsigned int uiLength = uiLength2 + uiLength1 + 1;
                pBuffer = MX_NEW TCHAR[uiLength];
                MX_ENGINE_ASSERT(pBuffer);

                MXStrCopy(pBuffer, uiLength, String1.GetBuffer());
                MXStrcat(pBuffer, uiLength, String2);
                MXString ReturnValue(pBuffer);
                ENGINE_DELETE(pBuffer);
                return ReturnValue;
            }
        }
        MXString operator+(const TCHAR *String1, const MXString &String2)
        {
            MX_ENGINE_ASSERT(String1);
            unsigned int uiLength2 = String2.GetLength();
            unsigned int uiLength1 = 0;
            if (String1)
            {
                uiLength1 = (unsigned int)MXStrLen(String1);
            }

            if (!uiLength1)
                return String2;
            else if (!uiLength2)
                return MXString(String1);
            else
            {
                TCHAR *pBuffer = NULL;
                unsigned int uiLength = uiLength2 + uiLength1 + 1;
                pBuffer = MX_NEW TCHAR[uiLength];
                MX_ENGINE_ASSERT(pBuffer);

                MXStrCopy(pBuffer, uiLength, String1);
                MXStrcat(pBuffer, uiLength, String2.GetBuffer());
                MXString ReturnValue(pBuffer);
                ENGINE_DELETE(pBuffer);
                return ReturnValue;
            }
        }
        int CompareString(const MXString &String1, const MXString &String2)
        {
            return MXStrCmp(String1.GetBuffer(), String2.GetBuffer());
        }
        int CompareString(const MXString &String1, const TCHAR *String2)
        {
            return MXStrCmp(String1.GetBuffer(), String2);
        }
        int CompareString(const TCHAR *String1, const MXString &String2)
        {
            return MXStrCmp(String1, String2.GetBuffer());
        }

        bool operator==(const MXString &String1, const MXString &String2)
        {
            return (MXStrCmp(String1.GetBuffer(), String2.GetBuffer()) == 0);
        }
        bool operator==(const MXString &String1, const TCHAR *String2)
        {
            return (MXStrCmp(String1.GetBuffer(), String2) == 0);
        }
        bool operator==(const TCHAR *String1, MXString &String2)
        {
            return (MXStrCmp(String1, String2.GetBuffer()) == 0);
        }

        bool operator!=(const MXString &String1, const MXString &String2)
        {
            return (MXStrCmp(String1.GetBuffer(), String2.GetBuffer()) != 0);
        }
        bool operator!=(const MXString &String1, const TCHAR *String2)
        {
            return (MXStrCmp(String1.GetBuffer(), String2) != 0);
        }
        bool operator!=(const TCHAR *String1, const MXString &String2)
        {
            return (MXStrCmp(String1, String2.GetBuffer()) != 0);
        }
        int StringToInt(const MXString &String)
        {
            int i = 0;
            // MXScanf(String.GetBuffer(), "%d", (TCHAR*)&i);
            return i;
        }
        MXString IntToString(int Value)
        {
            MXSprintf(MXString::TempBuffer, 2048, _T("%d"), Value);
            return MXString(MXString::TempBuffer);
        }
        unsigned int StringToUInt(const MXString &String)
        {
            unsigned int i = 0;
            // MXScanf(String.GetBuffer(), "%d", (TCHAR*)&i);
            return i;
        }
        MXString UIntToString(unsigned int Value)
        {
            MXSprintf(MXString::TempBuffer, 2048, _T("%d"), Value);
            return MXString(MXString::TempBuffer);
        }
        float StringToReal(const MXString &String)
        {
            float f = 0.0f;
            // MXScanf(String.GetBuffer(), "%f", (TCHAR*)&f);
            return f;
        }
        MXString RealToString(float Value)
        {
            MXSprintf(MXString::TempBuffer, 2048, _T("%f"), Value);
            return MXString(MXString::TempBuffer);
        }
        bool StringToBool(const MXString &String)
        {
            if (String == _T("True") || String == _T("true") || String == _T("TRUE"))
            {
                return true;
            }
            else if (String == _T("False") || String == _T("false") || String == _T("FALSE"))
            {
                return false;
            }

            int d = StringToUInt(String.GetBuffer());
            if (d)
            {
                return true;
            }
            else
                return false;
        }
        MXString BoolToString(bool i)
        {
            if (i)
            {
                return _T("True");
            }
            else
            {
                return _T("False");
            }
        }
        MXString BoolToString(unsigned int i)
        {
            if (i)
            {
                return _T("True");
            }
            else
            {
                return _T("False");
            }
        }
    }
}