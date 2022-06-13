#pragma once
#include "ConstValue.h"
namespace Matrix
{
    class MStream;
    class MATRIX_FUNCTION_API VSConstFloatValue : public VSConstValue
    {
        // RTTI
        DECLARE_RTTI;
        // PRIORITY
        DECLARE_INITIAL
    public:
        VSConstFloatValue(const VSUsedName &ShowName, VSMaterial *pMaterial, unsigned int uiValueNum, bool bIsCustom);
        virtual ~VSConstFloatValue();
        virtual unsigned int GetType()
        {
            return VSUserConstant::VT_FLOAT;
        }
        void SetValue(unsigned int uiIndex, VSREAL Value);

        virtual bool GetOutputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual unsigned int GetValueNum() const
        {
            return m_Value.GetNum();
        }
        virtual unsigned int GetSize() const
        {
            return m_Value.GetNum() * sizeof(VSREAL);
        }
        bool GetDeclareString(Container::MString &OutString, unsigned int uiRegisterID, MaterialShaderPara &MSPara) const;
        virtual void ResetInShaderName(MaterialShaderPara &MSPara);
        Container::MArray<VSREAL> &GetValue() { return m_Value; }

    protected:
        VSConstFloatValue();
        Container::MArray<VSREAL> m_Value;
    };
    DECLARE_Ptr(VSConstFloatValue);
    VSTYPE_MARCO(VSConstFloatValue);

}
