#pragma once
#include "Shader.h"
namespace Matrix
{
    class MStream;
    class MATRIX_FUNCTION_API VSHShader : public VSShader
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        VSHShader();
        VSHShader(const TCHAR *pBuffer, const Container::MString &MainFunName, bool IsFromFile = false);
        VSHShader(const Container::MString &Buffer, const Container::MString &MainFunName, bool IsFromFile = false);
        virtual ~VSHShader();
        virtual unsigned int GetShaderType() const
        {
            return VSEngineFlag::ST_HULL;
        }

    public:
        static const VSHShader *GetDefault()
        {
            return ms_Default;
        }

    protected:
        virtual bool OnLoadResource(VSResourceIdentifier *&pID);
        static VSPointer<VSHShader> ms_Default;
    };
    DECLARE_Ptr(VSHShader);
    VSTYPE_MARCO(VSHShader);
}
