#pragma once
#include "MTXCore.h"
#include "MTXFile.h"


namespace Matrix
{
	class MATRIXCORE_API MTXLog : public MTXFile
	{
	public:
		MTXLog();
		~MTXLog();
		bool Open(const TCHAR* pFileName);
		bool WriteInfo(const TCHAR* pString);
	};

}

