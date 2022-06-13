#include "PostEffectShaderFunction.h"
#include "ShaderStringFactory.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
#include "PosShaderFunction.h"
#include "NormalFunction.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSPostEffectShaderFunction, VSShaderFunction)
BEGIN_ADD_PROPERTY(VSPostEffectShaderFunction, VSShaderFunction)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSPostEffectShaderFunction)
IMPLEMENT_INITIAL_END
VSPostEffectShaderFunction::VSPostEffectShaderFunction(const VSUsedName &ShowName, VSMaterial *pMaterial)
    : VSShaderFunction(ShowName, pMaterial)
{

    Container::MString InputName = _T("InColor");
    VSInputNode *pInputNode = NULL;

    pInputNode = MX_NEW VSInputNode(VSPutNode::VT_4, InputName, this);
    ENGINE_ASSERT(pInputNode);
    m_pInput.AddElement(pInputNode);
}
VSPostEffectShaderFunction::VSPostEffectShaderFunction()
{
}
VSPostEffectShaderFunction::~VSPostEffectShaderFunction()
{
}

bool VSPostEffectShaderFunction::GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const
{

    OutString += VSShaderStringFactory::ms_PSOutputColorValue + _T(" = ") + m_pInput[IN_COLOR]->GetNodeName().GetString() + _T(";\n");

    return 1;
}
bool VSPostEffectShaderFunction::IsValidNodeToThis(VSShaderFunction *pShaderFunction, MaterialShaderPara &MSPara)
{
    if (pShaderFunction->GetType().IsSameType(VSLightDir::ms_Type) || pShaderFunction->GetType().IsSameType(VSLightColor::ms_Type) || pShaderFunction->GetType().IsSameType(VSLightSpecular::ms_Type) || pShaderFunction->GetType().IsSameType(VSWorldNormal::ms_Type) || pShaderFunction->GetType().IsSameType(VSViewNormal::ms_Type) || pShaderFunction->GetType().IsSameType(VSWorldPos::ms_Type) || pShaderFunction->GetType().IsSameType(VSViewPos::ms_Type))
    {
        return false;
    }
    return true;
}