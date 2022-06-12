#pragma once
#include "Core.h"
#include "File.h"

namespace Matrix
{
    namespace Core
    {

        class MATRIX_PLATFORM_API MXLog : public File
        {
        public:
            MXLog();
            ~MXLog();
            bool Open(const TCHAR *pFileName);
            bool WriteInfo(const TCHAR *pString);
        };
    }
}
