#pragma once
#include "Shader.h"
namespace Matrix
{
    class MStream;
    class MATRIX_FUNCTION_API VSPShader : public VSShader
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        VSPShader();
        VSPShader(const TCHAR *pBuffer, const Container::MString &MainFunName, bool IsFromFile = false);
        VSPShader(const Container::MString &Buffer, const Container::MString &MainFunName, bool IsFromFile = false);
        virtual ~VSPShader();
        virtual unsigned int GetShaderType() const
        {
            return VSEngineFlag::ST_PIXEL;
        }

    public:
        static const VSPShader *GetDefault()
        {
            return ms_Default;
        }

    protected:
        virtual bool OnLoadResource(VSResourceIdentifier *&pID);
        static VSPointer<VSPShader> ms_Default;
    };
    DECLARE_Ptr(VSPShader);
    VSTYPE_MARCO(VSPShader);

}
