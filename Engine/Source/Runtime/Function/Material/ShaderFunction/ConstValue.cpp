#include "ConstValue.h"
#include "ShaderStringFactory.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
using namespace Matrix;
IMPLEMENT_RTTI_NoCreateFun(VSConstValue, VSShaderFunction)
    IMPLEMENT_INITIAL_NO_CLASS_FACTORY_BEGIN(VSConstValue)
        IMPLEMENT_INITIAL_NO_CLASS_FACTORY_END
    BEGIN_ADD_PROPERTY(VSConstValue, VSShaderFunction)
        REGISTER_PROPERTY(m_bIsCustom, IsCustom, VSProperty::F_SAVE_LOAD_CLONE)
            END_ADD_PROPERTY
    VSConstValue::VSConstValue()
{
}
VSConstValue::VSConstValue(const VSUsedName &ShowName, VSMaterial *pMaterial, unsigned int uiValueNum, bool bIsCustom)
    : VSShaderFunction(ShowName, pMaterial)
{
    m_bIsCustom = bIsCustom;
}
VSConstValue::~VSConstValue()
{
}
