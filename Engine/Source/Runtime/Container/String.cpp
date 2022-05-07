#include "String.h"


using namespace Matrix::Container;
using namespace Matrix::Core;

MTXString MTXString::ms_StringNULL;
TCHAR	MTXString::TempBuffer[BUFFER_SIZE] = { 0 };
MTXString::MTXString()
{
	m_pBuffer = NULL;
	m_pBuffer = MATRIX_NEW TCHAR[1];
	MTXENGINE_ASSERT(m_pBuffer);
	m_pBuffer[0] = _T('\0');
}
MTXString::MTXString(const TCHAR* String)
{
	MTXENGINE_ASSERT(String);
	m_pBuffer = NULL;
	if (String)
	{
		unsigned int  uiLength = (unsigned int)MTXStrLen(String);
		m_pBuffer = MATRIX_NEW TCHAR[uiLength + 1];
		MTXENGINE_ASSERT(m_pBuffer);

		MTXStrCopy(m_pBuffer, uiLength + 1, String);
	}
	else
	{
		m_pBuffer = MATRIX_NEW TCHAR[1];
		MTXENGINE_ASSERT(m_pBuffer);
		m_pBuffer[0] = _T('\0');
	}
}
MTXString::MTXString(const MTXString& String)
{
	m_pBuffer = NULL;
	unsigned int  uiLength = String.GetLength();
	m_pBuffer = MATRIX_NEW TCHAR[uiLength + 1];
	MTXENGINE_ASSERT(m_pBuffer);

	MTXStrCopy(m_pBuffer, uiLength + 1, String.GetBuffer());
}
MTXString::~MTXString()
{

	MTXENGINE_DELETE(m_pBuffer);

}
void MTXString::SetTCHARBufferNum(unsigned int uiLength)
{
	MTXENGINE_DELETE(m_pBuffer);
	m_pBuffer = MATRIX_NEW TCHAR[uiLength + 1];
	m_pBuffer[uiLength] = _T('\0');
}
void MTXString::Clear()
{

	MTXENGINE_DELETE(m_pBuffer);
	m_pBuffer = MATRIX_NEW TCHAR[1];
	MTXENGINE_ASSERT(m_pBuffer);
	m_pBuffer[0] = _T('\0');
}
MTXString& MTXString::operator =(const MTXString& String)
{
	MTXENGINE_DELETE(m_pBuffer);
	unsigned int  uiLength = String.GetLength();
	m_pBuffer = MATRIX_NEW TCHAR[uiLength + 1];
	MTXENGINE_ASSERT(m_pBuffer);

	MTXStrCopy(m_pBuffer, uiLength + 1, String.GetBuffer());
	return *this;
}
MTXString& MTXString::operator =(const TCHAR* String)
{
	MTXENGINE_DELETE(m_pBuffer);
	if (String)
	{
		unsigned int  uiLength = (unsigned int)MTXStrLen(String);
		m_pBuffer = MATRIX_NEW TCHAR[uiLength + 1];
		MTXENGINE_ASSERT(m_pBuffer);

		MTXStrCopy(m_pBuffer, uiLength + 1, String);
	}
	else
	{
		MTXString();
	}
	return *this;
}

TCHAR& MTXString::operator[](unsigned int i)
{
	return m_pBuffer[i];
}

const MTXString& MTXString::operator +=(const MTXString& String)
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
		TCHAR* pBuffer = NULL;
		unsigned int uiLength = uiLength2 + uiLength1 + 1;
		pBuffer = MATRIX_NEW TCHAR[uiLength];
		MTXENGINE_ASSERT(pBuffer);

		MTXStrCopy(pBuffer, uiLength, GetBuffer());
		MTXStrcat(pBuffer, uiLength, String.GetBuffer());

		MTXENGINE_DELETE(m_pBuffer);
		m_pBuffer = pBuffer;
		return *this;

	}
}
const MTXString& MTXString::operator +=(const TCHAR* String)
{
	unsigned int uiLength1 = GetLength();
	unsigned int uiLength2 = 0;
	if (String)
	{
		uiLength2 = (unsigned int)MTXStrLen(String);
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
		TCHAR* pBuffer = NULL;
		unsigned int uiLength = uiLength2 + uiLength1 + 1;
		pBuffer = MATRIX_NEW TCHAR[uiLength];
		MTXENGINE_ASSERT(pBuffer);

		MTXStrCopy(pBuffer, uiLength, GetBuffer());
		MTXStrcat(pBuffer, uiLength, String);

		MTXENGINE_DELETE(m_pBuffer);
		m_pBuffer = pBuffer;
		return *this;

	}
}
bool MTXString::GetString(const MTXString& String, unsigned int uiFind, bool bIsFront, bool bIsHaveFind)
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
	MTXENGINE_DELETE(m_pBuffer);
	m_pBuffer = MATRIX_NEW TCHAR[uiLength + 1];
	MTXMemcpy(m_pBuffer, &String.m_pBuffer[uiIndex], uiLength, uiLength + 1);
	m_pBuffer[uiLength] = _T('\0');
	return true;

}
bool MTXString::GetString(const MTXString& String, TCHAR cFind, int iFIndNum, bool bIsFront, bool bIsHaveFind)
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
int MTXString::GetSubStringIndex(const MTXString& String, int iFindNum)const
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
bool MTXString::RemoveSubString(const MTXString& String, int iFindNum)
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
void MTXString::Remove(unsigned int i, unsigned int j)
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
	TCHAR* pBuffer = MATRIX_NEW TCHAR[DeltaLength + 1];
	pBuffer[DeltaLength] = _T('\0');
	if (i > 0)
	{
		MTXMemcpy(pBuffer, m_pBuffer, i);
	}
	unsigned int LeftNum = DeltaLength - i;
	if (LeftNum > 0)
	{
		MTXMemcpy(pBuffer + i, m_pBuffer + i + uiLength, LeftNum);
	}
	MTXENGINE_DELETE(m_pBuffer);
	m_pBuffer = pBuffer;
}
bool MTXString::StripChars(const MTXString& String, const TCHAR* pStripChars)
{
	if (String.GetLength() > BUFFER_SIZE || !pStripChars)
	{
		return false;
	}

	unsigned int strip_chars_len = MTXStrLen(pStripChars);
	TCHAR* _string_in = String.GetBuffer(), * _string_out = TempBuffer;
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

bool MTXString::ReplaceChars(const MTXString& String, const TCHAR* pReplaceChars, TCHAR UseChar)
{
	if (String.GetLength() > BUFFER_SIZE || !pReplaceChars)
	{
		return false;
	}
	unsigned int replace_chars_len = MTXStrLen(pReplaceChars);
	TCHAR* _string_in = String.GetBuffer(), * _string_out = TempBuffer;
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

void MTXString::StringLtrim(const MTXString& String)
{
	int index = 0;
	TCHAR* pString = String.GetBuffer();
	while (_istspace(pString[index]))
		index++;
	if (index == 0)
		return;
	else
	{
		unsigned int uiLength = String.GetLength();
		MTXMemcpy((void*)TempBuffer, (void*)(pString + index), ((uiLength - index) + 1) * sizeof(TCHAR));
		*this = TempBuffer;
	}
}

void MTXString::StringRtrim(const MTXString& String)
{
	unsigned int uiLength = String.GetLength();
	if (!uiLength)
	{
		return;
	}
	unsigned int index = uiLength - 1;
	TCHAR* pString = String.GetBuffer();
	while (MTXIsSpace(pString[index]))
		index--;

	MTXMemcpy((void*)TempBuffer, (void*)(pString), (index + 1) * sizeof(TCHAR));
	index++;
	TempBuffer[index] = _T('\0');
	*this = TempBuffer;
}
void MTXString::Format(const TCHAR* pcString, ...)
{
	static TCHAR LogBuffer[LOG_BUFFER_SIZE];
	char* pArgs;
	pArgs = (char*)&pcString + sizeof(pcString);
	MTXSprintf(LogBuffer, LOG_BUFFER_SIZE, pcString, pArgs);
	*this = LogBuffer;
}
bool  MTXFileName::GetExtension(MTXString& Extension)
{
	return Extension.GetString(*this, _T('.'), -1, false, false);
}
bool MTXFileName::GetPathAndName(MTXString& PathAndName)
{
	return PathAndName.GetString(*this, _T('.'), -1);
}
bool MTXFileName::GetBaseName(MTXString& BaseName)
{
	bool bResult = false;
	MTXString BaseNameAndExtension;
	bResult = GetBaseNameAndExtension(BaseNameAndExtension);
	if (!bResult)
	{
		return false;
	}
	bResult = BaseName.GetString(BaseNameAndExtension, _T('.'), -1);
	return bResult;
}
bool MTXFileName::GetBaseNameAndExtension(MTXString& BaseNameAndExtension)
{
	bool bResult = false;
	bResult = BaseNameAndExtension.GetString(*this, _T('\\'), -1, false, false);
	if (!bResult)
	{
		bResult = BaseNameAndExtension.GetString(*this, _T('/'), -1, false, false);
	}
	return bResult;
}
bool MTXFileName::GetPath(MTXString& Path)
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
		MTXString operator +(const MTXString& String1, const MTXString& String2)
		{
			unsigned int uiLength1 = String1.GetLength();
			unsigned int uiLength2 = String2.GetLength();
			if (!uiLength2)
				return String1;
			else if (!uiLength1)
				return String2;
			else
			{
				TCHAR* pBuffer = NULL;
				unsigned int uiLength = uiLength2 + uiLength1 + 1;
				pBuffer = MATRIX_NEW TCHAR[uiLength];
				MTXENGINE_ASSERT(pBuffer);

				MTXStrCopy(pBuffer, uiLength, String1.GetBuffer());
				MTXStrcat(pBuffer, uiLength, String2.GetBuffer());
				MTXString ReturnValue(pBuffer);
				MTXENGINE_DELETE(pBuffer);
				return ReturnValue;
			}
		}
		MTXString operator +(const MTXString& String1, const TCHAR* String2)
		{
			MTXENGINE_ASSERT(String2);
			unsigned int uiLength1 = String1.GetLength();
			unsigned int uiLength2 = 0;
			if (String2)
			{
				uiLength2 = (unsigned int)MTXStrLen(String2);
			}

			if (!uiLength2)
				return String1;
			else if (!uiLength1)
				return MTXString(String2);
			else
			{
				TCHAR* pBuffer = NULL;
				unsigned int uiLength = uiLength2 + uiLength1 + 1;
				pBuffer = MATRIX_NEW TCHAR[uiLength];
				MTXENGINE_ASSERT(pBuffer);

				MTXStrCopy(pBuffer, uiLength, String1.GetBuffer());
				MTXStrcat(pBuffer, uiLength, String2);
				MTXString ReturnValue(pBuffer);
				MTXENGINE_DELETE(pBuffer);
				return ReturnValue;
			}
		}
		MTXString operator +(const TCHAR* String1, const MTXString& String2)
		{
			MTXENGINE_ASSERT(String1);
			unsigned int uiLength2 = String2.GetLength();
			unsigned int uiLength1 = 0;
			if (String1)
			{
				uiLength1 = (unsigned int)MTXStrLen(String1);
			}

			if (!uiLength1)
				return String2;
			else if (!uiLength2)
				return MTXString(String1);
			else
			{
				TCHAR* pBuffer = NULL;
				unsigned int uiLength = uiLength2 + uiLength1 + 1;
				pBuffer = MATRIX_NEW TCHAR[uiLength];
				MTXENGINE_ASSERT(pBuffer);

				MTXStrCopy(pBuffer, uiLength, String1);
				MTXStrcat(pBuffer, uiLength, String2.GetBuffer());
				MTXString ReturnValue(pBuffer);
				MTXENGINE_DELETE(pBuffer);
				return ReturnValue;
			}
		}
		int CompareString(const MTXString& String1, const MTXString& String2)
		{
			return MTXStrCmp(String1.GetBuffer(), String2.GetBuffer());

		}
		int CompareString(const MTXString& String1, const TCHAR* String2)
		{
			return MTXStrCmp(String1.GetBuffer(), String2);
		}
		int CompareString(const TCHAR* String1, const MTXString& String2)
		{
			return MTXStrCmp(String1, String2.GetBuffer());
		}



		bool operator ==(const MTXString& String1, const MTXString& String2)
		{
			return (MTXStrCmp(String1.GetBuffer(), String2.GetBuffer()) == 0);
		}
		bool operator ==(const MTXString& String1, const TCHAR* String2)
		{
			return (MTXStrCmp(String1.GetBuffer(), String2) == 0);
		}
		bool operator ==(const TCHAR* String1, MTXString& String2)
		{
			return (MTXStrCmp(String1, String2.GetBuffer()) == 0);
		}

		bool operator !=(const MTXString& String1, const MTXString& String2)
		{
			return (MTXStrCmp(String1.GetBuffer(), String2.GetBuffer()) != 0);
		}
		bool operator !=(const MTXString& String1, const TCHAR* String2)
		{
			return (MTXStrCmp(String1.GetBuffer(), String2) != 0);
		}
		bool operator !=(const TCHAR* String1, const MTXString& String2)
		{
			return (MTXStrCmp(String1, String2.GetBuffer()) != 0);
		}
		int StringToInt(const MTXString& String)
		{
			int i = 0;
			//MTXScanf(String.GetBuffer(), "%d", (TCHAR*)&i);
			return i;
		}
		MTXString IntToString(int Value)
		{
			MTXSprintf(MTXString::TempBuffer, 2048, _T("%d"), Value);
			return MTXString(MTXString::TempBuffer);
		}
		unsigned int StringToUInt(const MTXString& String)
		{
			unsigned int i = 0;
			//MTXScanf(String.GetBuffer(), "%d", (TCHAR*)&i);
			return i;
		}
		MTXString UIntToString(unsigned int Value)
		{
			MTXSprintf(MTXString::TempBuffer, 2048, _T("%d"), Value);
			return MTXString(MTXString::TempBuffer);
		}
		float StringToReal(const MTXString& String)
		{
			float f = 0.0f;
			//MTXScanf(String.GetBuffer(), "%f", (TCHAR*)&f);
			return f;
		}
		MTXString RealToString(float Value)
		{
			MTXSprintf(MTXString::TempBuffer, 2048, _T("%f"), Value);
			return MTXString(MTXString::TempBuffer);

		}
		bool StringToBool(const MTXString& String)
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
		MTXString BoolToString(bool i)
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
		MTXString BoolToString(unsigned int i)
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