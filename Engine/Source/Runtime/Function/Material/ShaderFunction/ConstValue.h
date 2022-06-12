#pragma once
#include "Math.h"
#include "ShaderFunction.h"
#include "UserConstant.h"
namespace Matrix
{
    class VSStream;
    class MATRIX_FUNCTION_API VSConstValue : public VSShaderFunction
    {
        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL_NO_CLASS_FACTORY;

    public:
        VSConstValue(const VSUsedName &ShowName, VSMaterial *pMaterial, unsigned int uiValueNum, bool bIsCustom);
        virtual ~VSConstValue();
        virtual unsigned int GetType() = 0;
        virtual bool GetOutputValueString(VSString &OutString, MaterialShaderPara &MSPara) const = 0;
        virtual bool GetFunctionString(VSString &OutString, MaterialShaderPara &MSPara) const = 0;
        inline bool IsCustom() const
        {
            return m_bIsCustom;
        }
        virtual bool GetDeclareString(VSString &OutString, unsigned int uiRegisterID, MaterialShaderPara &MSPara) const = 0;

        virtual unsigned int GetValueNum() const = 0;

        virtual unsigned int GetSize() const = 0;

    protected:
        VSConstValue();
        bool m_bIsCustom;
    };
    DECLARE_Ptr(VSConstValue);
    VSTYPE_MARCO(VSConstValue);

}
