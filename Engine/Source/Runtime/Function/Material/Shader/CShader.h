#pragma once
#include "Shader.h"
namespace Matrix
{
    class MStream;
    class MATRIX_FUNCTION_API VSCShader : public VSShader
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        VSCShader();
        VSCShader(const TCHAR *pBuffer, const Container::MString &MainFunName, bool IsFromFile = false);
        VSCShader(const Container::MString &Buffer, const Container::MString &MainFunName, bool IsFromFile = false);
        virtual ~VSCShader();
        virtual unsigned int GetShaderType() const
        {
            return VSEngineFlag::ST_COMPUTE;
        }

    public:
        static const VSCShader *GetDefault()
        {
            return ms_Default;
        }

    protected:
        virtual bool OnLoadResource(VSResourceIdentifier *&pID);
        static VSPointer<VSCShader> ms_Default;
    };
    DECLARE_Ptr(VSCShader);
    VSTYPE_MARCO(VSCShader);
}
