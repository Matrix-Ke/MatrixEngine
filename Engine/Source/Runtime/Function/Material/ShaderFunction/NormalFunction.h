#pragma once
#include "ShaderFunction.h"
namespace Matrix
{
    class MStream;
    class MATRIX_FUNCTION_API VSWorldNormal : public VSShaderFunction
    {
        // RTTI
        DECLARE_RTTI;
        // PRIORITY
        DECLARE_INITIAL
    public:
        VSWorldNormal(const VSUsedName &ShowName, VSMaterial *pMaterial);
        virtual ~VSWorldNormal();
        virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual void ResetInShaderName(MaterialShaderPara &MSPara);
        virtual bool GetOutputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

    protected:
        VSWorldNormal();

    public:
        enum
        {
            WNT_PIXEL,
            WNT_VERTEX,
            WNT_MAX
        };
        unsigned int m_uiNormalType;
    };
    DECLARE_Ptr(VSWorldNormal);
    VSTYPE_MARCO(VSWorldNormal);

    class MATRIX_FUNCTION_API VSViewNormal : public VSShaderFunction
    {
        // RTTI
        DECLARE_RTTI;
        // PRIORITY
        DECLARE_INITIAL
    public:
        VSViewNormal(const VSUsedName &ShowName, VSMaterial *pMaterial);
        virtual ~VSViewNormal();
        virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual void ResetInShaderName(MaterialShaderPara &MSPara);
        virtual bool GetOutputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

    protected:
        VSViewNormal();

    public:
        enum
        {
            VNT_PIXEL,
            VNT_VERTEX,
            VNT_MAX
        };
        unsigned int m_uiNormalType;
    };
    DECLARE_Ptr(VSViewNormal);
    VSTYPE_MARCO(VSViewNormal);
}
