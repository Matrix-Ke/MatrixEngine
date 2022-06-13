#pragma once
#include "ShaderFunction.h"
namespace Matrix
{
    class MStream;
    class MATRIX_FUNCTION_API VSColorBuffer : public VSShaderFunction
    {
        // RTTI
        DECLARE_RTTI;
        // PRIORITY
        DECLARE_INITIAL
    public:
        VSColorBuffer(const VSUsedName &ShowName, VSMaterial *pMaterial);
        virtual ~VSColorBuffer();
        virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual void ResetInShaderName(MaterialShaderPara &MSPara);
        virtual bool GetInputValueString(Container::MString &InputString, MaterialShaderPara &MSPara) const;
        virtual bool GetOutputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

    protected:
        VSColorBuffer();
    };
    DECLARE_Ptr(VSColorBuffer);
    VSTYPE_MARCO(VSColorBuffer);
}
