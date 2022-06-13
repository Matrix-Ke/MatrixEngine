#pragma once
#include "ShaderFunction.h"
namespace Matrix
{
    class MStream;

    class MATRIX_FUNCTION_API VSMul : public VSShaderFunction
    {
        // RTTI
        DECLARE_RTTI;
        // PRIORITY
        DECLARE_INITIAL
    public:
        VSMul(const VSUsedName &ShowName, VSMaterial *pMaterial);
        virtual ~VSMul();
        virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual void ResetInShaderName(MaterialShaderPara &MSPara);
        virtual bool ResetValueType(MaterialShaderPara &MSPara);

    protected:
        VSMul();
    };
    DECLARE_Ptr(VSMul);
    VSTYPE_MARCO(VSMul);

    class MATRIX_FUNCTION_API VSDot : public VSShaderFunction
    {
        // RTTI
        DECLARE_RTTI;
        // PRIORITY
        DECLARE_INITIAL
    public:
        VSDot(const VSUsedName &ShowName, VSMaterial *pMaterial);
        virtual ~VSDot();
        virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual void ResetInShaderName(MaterialShaderPara &MSPara);
        virtual bool ResetValueType(MaterialShaderPara &MSPara);

    protected:
        VSDot();
    };
    DECLARE_Ptr(VSDot);
    VSTYPE_MARCO(VSDot);

    class MATRIX_FUNCTION_API VSLength : public VSShaderFunction
    {
        // RTTI
        DECLARE_RTTI;
        // PRIORITY
        DECLARE_INITIAL
    public:
        VSLength(const VSUsedName &ShowName, VSMaterial *pMaterial);
        virtual ~VSLength();
        virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual void ResetInShaderName(MaterialShaderPara &MSPara);
        virtual bool ResetValueType(MaterialShaderPara &MSPara);

    protected:
        VSLength();
    };
    DECLARE_Ptr(VSLength);
    VSTYPE_MARCO(VSLength);

    class MATRIX_FUNCTION_API VSSub : public VSShaderFunction
    {
        // RTTI
        DECLARE_RTTI;
        // PRIORITY
        DECLARE_INITIAL
    public:
        VSSub(const VSUsedName &ShowName, VSMaterial *pMaterial);
        virtual ~VSSub();
        virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual void ResetInShaderName(MaterialShaderPara &MSPara);
        virtual bool ResetValueType(MaterialShaderPara &MSPara);

    protected:
        VSSub();
    };
    DECLARE_Ptr(VSSub);
    VSTYPE_MARCO(VSSub);

    class MATRIX_FUNCTION_API VSAdd : public VSShaderFunction
    {
        // RTTI
        DECLARE_RTTI;
        // PRIORITY
        DECLARE_INITIAL
    public:
        VSAdd(const VSUsedName &ShowName, VSMaterial *pMaterial);
        virtual ~VSAdd();
        virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual void ResetInShaderName(MaterialShaderPara &MSPara);
        virtual bool ResetValueType(MaterialShaderPara &MSPara);

    protected:
        VSAdd();
    };
    DECLARE_Ptr(VSAdd);
    VSTYPE_MARCO(VSAdd);

    class MATRIX_FUNCTION_API VSMakeValue : public VSShaderFunction
    {
        // RTTI
        DECLARE_RTTI;
        // PRIORITY
        DECLARE_INITIAL
    public:
        VSMakeValue(const VSUsedName &ShowName, VSMaterial *pMaterial, unsigned int uiInputNum);
        virtual ~VSMakeValue();
        virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual void ResetInShaderName(MaterialShaderPara &MSPara);
        virtual bool ResetValueType(MaterialShaderPara &MSPara);

    protected:
        VSMakeValue();
    };
    DECLARE_Ptr(VSMakeValue);
    VSTYPE_MARCO(VSMakeValue);

    class MATRIX_FUNCTION_API VSDiv : public VSShaderFunction
    {
        // RTTI
        DECLARE_RTTI;
        // PRIORITY
        DECLARE_INITIAL
    public:
        VSDiv(const VSUsedName &ShowName, VSMaterial *pMaterial);
        virtual ~VSDiv();
        virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual void ResetInShaderName(MaterialShaderPara &MSPara);
        virtual bool ResetValueType(MaterialShaderPara &MSPara);

    protected:
        VSDiv();
    };
    DECLARE_Ptr(VSDiv);
    VSTYPE_MARCO(VSDiv);

    class MATRIX_FUNCTION_API VSSaturate : public VSShaderFunction
    {
        // RTTI
        DECLARE_RTTI;
        // PRIORITY
        DECLARE_INITIAL
    public:
        VSSaturate(const VSUsedName &ShowName, VSMaterial *pMaterial);
        virtual ~VSSaturate();
        virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual void ResetInShaderName(MaterialShaderPara &MSPara);
        virtual bool ResetValueType(MaterialShaderPara &MSPara);

    protected:
        VSSaturate();
    };
    DECLARE_Ptr(VSSaturate);
    VSTYPE_MARCO(VSSaturate);
}
