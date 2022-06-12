#pragma once
#include "ShaderFunction.h"
namespace Matrix
{
    class VSStream;
    class MATRIX_FUNCTION_API VSColorBuffer : public VSShaderFunction
    {
        // RTTI
        DECLARE_RTTI;
        // PRIORITY
        DECLARE_INITIAL
    public:
        VSColorBuffer(const VSUsedName &ShowName, VSMaterial *pMaterial);
        virtual ~VSColorBuffer();
        virtual bool GetFunctionString(VSString &OutString, MaterialShaderPara &MSPara) const;
        virtual void ResetInShaderName(MaterialShaderPara &MSPara);
        virtual bool GetInputValueString(VSString &InputString, MaterialShaderPara &MSPara) const;
        virtual bool GetOutputValueString(VSString &OutString, MaterialShaderPara &MSPara) const;

    protected:
        VSColorBuffer();
    };
    DECLARE_Ptr(VSColorBuffer);
    VSTYPE_MARCO(VSColorBuffer);
}