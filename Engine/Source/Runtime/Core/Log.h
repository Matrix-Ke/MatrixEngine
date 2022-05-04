#pragma once
#include "Core.h"
#include "File.h"


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

