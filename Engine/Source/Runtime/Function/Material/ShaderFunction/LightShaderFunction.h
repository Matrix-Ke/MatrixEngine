#pragma once
#include "ShaderFunction.h"
namespace Matrix
{
    class MStream;
    class MATRIX_FUNCTION_API VSLightColor : public VSShaderFunction
    {
        // RTTI
        DECLARE_RTTI;
        // PRIORITY
        DECLARE_INITIAL
    public:
        VSLightColor(const VSUsedName &ShowName, VSMaterial *pMaterial);
        virtual ~VSLightColor();
        virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual void ResetInShaderName(MaterialShaderPara &MSPara);

    protected:
        VSLightColor();
    };
    DECLARE_Ptr(VSLightColor);
    VSTYPE_MARCO(VSLightColor);

    class MATRIX_FUNCTION_API VSLightSpecular : public VSShaderFunction
    {
        // RTTI
        DECLARE_RTTI;
        // PRIORITY
        DECLARE_INITIAL
    public:
        VSLightSpecular(const VSUsedName &ShowName, VSMaterial *pMaterial);
        virtual ~VSLightSpecular();
        virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual void ResetInShaderName(MaterialShaderPara &MSPara);

    protected:
        VSLightSpecular();
    };
    DECLARE_Ptr(VSLightSpecular);
    VSTYPE_MARCO(VSLightSpecular);

    class MATRIX_FUNCTION_API VSLightDir : public VSShaderFunction
    {
        // RTTI
        DECLARE_RTTI;
        // PRIORITY
        DECLARE_INITIAL
    public:
        VSLightDir(const VSUsedName &ShowName, VSMaterial *pMaterial);
        virtual ~VSLightDir();
        virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual void ResetInShaderName(MaterialShaderPara &MSPara);

    protected:
        VSLightDir();
    };
    DECLARE_Ptr(VSLightDir);
    VSTYPE_MARCO(VSLightDir);

    class MATRIX_FUNCTION_API VSLightShaderFunction : public VSShaderFunction
    {
        // RTTI
        DECLARE_RTTI;
        // PRIORITY
        DECLARE_INITIAL
    public:
        VSLightShaderFunction(const VSUsedName &ShowName, VSMaterial *pMaterial);
        virtual ~VSLightShaderFunction();
        virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual void ResetInShaderName(MaterialShaderPara &MSPara){};
        virtual bool IsValidNodeToThis(VSShaderFunction *pShaderFunction, MaterialShaderPara &MSPara);

    protected:
        VSLightShaderFunction();
    };
    DECLARE_Ptr(VSLightShaderFunction);
    VSTYPE_MARCO(VSLightShaderFunction);
}
