#pragma once
#include "TexSampler.h"
#include "ViewFamily.h"
namespace Matrix
{
    class MATRIX_FUNCTION_API VS1DTexSampler : public VSTexSampler
    {
        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL

    public:
        VS1DTexSampler(const VSUsedName &ShowName, VSMaterial *pMaterial);
        virtual ~VS1DTexSampler();
        virtual void SetTexture(VSTexAllStateR *pTexAllState);

        virtual unsigned int GetTexType() const
        {
            return VSTexture::TT_1D;
        }

        virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual void ResetInShaderName(MaterialShaderPara &MSPara);
        virtual bool GetOutputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

    protected:
        VS1DTexSampler();
    };
    DECLARE_Ptr(VS1DTexSampler);
    VSTYPE_MARCO(VS1DTexSampler);
}
