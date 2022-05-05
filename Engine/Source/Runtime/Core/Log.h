#pragma once
#include "Core.h"
#include "File.h"


namespace Matrix
{
	namespace Core
	{

		class MATRIX_CORE_API MTXLog : public File
		{
		public:
			MTXLog();
			~MTXLog();
			bool Open(const TCHAR* pFileName);
			bool WriteInfo(const TCHAR* pString);
		};
	}
}

