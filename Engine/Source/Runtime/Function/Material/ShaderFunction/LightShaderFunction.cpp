#include "LightShaderFunction.h"
#include "ShaderStringFactory.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
#include "PosShaderFunction.h"
#include "NormalFunction.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSLightColor, VSShaderFunction)
BEGIN_ADD_PROPERTY(VSLightColor, VSShaderFunction)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSLightColor)
IMPLEMENT_INITIAL_END
VSLightColor::VSLightColor(const VSUsedName &ShowName, VSMaterial *pMaterial)
    : VSShaderFunction(ShowName, pMaterial)
{

    Container::MString OutputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    Container::MString OutputName = _T("LightColorOutput") + OutputID;
    VSOutputNode *pOutputNode = NULL;
    pOutputNode = MX_NEW VSOutputNode(VSPutNode::VT_4, OutputName, this);
    ENGINE_ASSERT(pOutputNode);
    m_pOutput.AddElement(pOutputNode);
    VSShaderStringFactory::ms_ShaderValueIndex++;
}
VSLightColor::VSLightColor()
{
}
VSLightColor::~VSLightColor()
{
}
void VSLightColor::ResetInShaderName(MaterialShaderPara &MSPara)
{
    Container::MString OutputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    Container::MString OutputName = _T("LightColorOutput") + OutputID;
    m_pOutput[0]->SetNodeName(OutputName);
    VSShaderStringFactory::ms_ShaderValueIndex++;
}
bool VSLightColor::GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const
{

    OutString += GetOutputNode(VSOutputNode::ONI_COLOR)->GetNodeName().GetString() + _T(" = ") + *VSShaderStringFactory::ms_LightColor + _T(";\n");

    return 1;
}

IMPLEMENT_RTTI(VSLightSpecular, VSShaderFunction)
BEGIN_ADD_PROPERTY(VSLightSpecular, VSShaderFunction)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSLightSpecular)
IMPLEMENT_INITIAL_END
VSLightSpecular::VSLightSpecular(const VSUsedName &ShowName, VSMaterial *pMaterial)
    : VSShaderFunction(ShowName, pMaterial)
{

    Container::MString OutputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    Container::MString OutputName = _T("LightSpecularOutput") + OutputID;
    VSOutputNode *pOutputNode = NULL;
    pOutputNode = MX_NEW VSOutputNode(VSPutNode::VT_4, OutputName, this);
    ENGINE_ASSERT(pOutputNode);
    m_pOutput.AddElement(pOutputNode);
    VSShaderStringFactory::ms_ShaderValueIndex++;
}
VSLightSpecular::VSLightSpecular()
{
}
VSLightSpecular::~VSLightSpecular()
{
}
void VSLightSpecular::ResetInShaderName(MaterialShaderPara &MSPara)
{
    Container::MString OutputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    Container::MString OutputName = _T("LightSpecularOutput") + OutputID;
    m_pOutput[0]->SetNodeName(OutputName);
    VSShaderStringFactory::ms_ShaderValueIndex++;
}
bool VSLightSpecular::GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const
{

    OutString += GetOutputNode(VSOutputNode::ONI_COLOR)->GetNodeName().GetString() + _T(" = ") + *VSShaderStringFactory::ms_LightSpecular + _T(";\n");

    return 1;
}

IMPLEMENT_RTTI(VSLightDir, VSShaderFunction)
BEGIN_ADD_PROPERTY(VSLightDir, VSShaderFunction)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSLightDir)
IMPLEMENT_INITIAL_END
VSLightDir::VSLightDir(const VSUsedName &ShowName, VSMaterial *pMaterial)
    : VSShaderFunction(ShowName, pMaterial)
{

    Container::MString OutputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    Container::MString OutputName = _T("LightDirOutput") + OutputID;
    VSOutputNode *pOutputNode = NULL;
    pOutputNode = MX_NEW VSOutputNode(VSPutNode::VT_3, OutputName, this);
    ENGINE_ASSERT(pOutputNode);
    m_pOutput.AddElement(pOutputNode);
    VSShaderStringFactory::ms_ShaderValueIndex++;
}
VSLightDir::VSLightDir()
{
}
VSLightDir::~VSLightDir()
{
}
void VSLightDir::ResetInShaderName(MaterialShaderPara &MSPara)
{
    Container::MString OutputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    Container::MString OutputName = _T("LightDirOutput") + OutputID;
    m_pOutput[0]->SetNodeName(OutputName);
    VSShaderStringFactory::ms_ShaderValueIndex++;
}
bool VSLightDir::GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const
{

    OutString += GetOutputNode(VSOutputNode::ONI_COLOR)->GetNodeName().GetString() + _T(" = ") + *VSShaderStringFactory::ms_LightDir + _T(";\n");

    return 1;
}

IMPLEMENT_RTTI(VSLightShaderFunction, VSShaderFunction)
BEGIN_ADD_PROPERTY(VSLightShaderFunction, VSShaderFunction)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSLightShaderFunction)
IMPLEMENT_INITIAL_END
VSLightShaderFunction::VSLightShaderFunction(const VSUsedName &ShowName, VSMaterial *pMaterial)
    : VSShaderFunction(ShowName, pMaterial)
{

    Container::MString InputName = _T("DiffuseColor");
    VSInputNode *pInputNode = NULL;

    pInputNode = MX_NEW VSInputNode(VSPutNode::VT_4, InputName, this);
    ENGINE_ASSERT(pInputNode);
    m_pInput.AddElement(pInputNode);

    InputName = _T("Alpha");
    pInputNode = NULL;
    pInputNode = MX_NEW VSInputNode(VSPutNode::VT_1, InputName, this);
    ENGINE_ASSERT(pInputNode);
    m_pInput.AddElement(pInputNode);

    Container::MString OutputName = _T("OutputColor");
    VSOutputNode *pOutputNode = NULL;
    pOutputNode = MX_NEW VSOutputNode(VSPutNode::VT_4, OutputName, this);
    ENGINE_ASSERT(pOutputNode);
    m_pOutput.AddElement(pOutputNode);
}
VSLightShaderFunction::VSLightShaderFunction()
{
}
VSLightShaderFunction::~VSLightShaderFunction()
{
}
bool VSLightShaderFunction::GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const
{

    Container::MString NodeStringA = VSRenderer::GetValueElement(m_pInput[VSInputNode::INI_COLOR], VSRenderer::VE_A);
    OutString += NodeStringA + _T(" = ") + m_pInput[VSInputNode::INI_ALPHA]->GetNodeName().GetString();
    OutString += _T(";\n");
    OutString += VSShaderStringFactory::ms_PSOutputColorValue + _T(" = ") + m_pInput[VSInputNode::INI_COLOR]->GetNodeName().GetString() + _T(";\n");

    return 1;
}
bool VSLightShaderFunction::IsValidNodeToThis(VSShaderFunction *pShaderFunction, MaterialShaderPara &MSPara)
{
    if (pShaderFunction->GetType().IsSameType(VSLightDir::ms_Type) || pShaderFunction->GetType().IsSameType(VSLightColor::ms_Type) || pShaderFunction->GetType().IsSameType(VSLightSpecular::ms_Type) || pShaderFunction->GetType().IsSameType(VSWorldNormal::ms_Type) || pShaderFunction->GetType().IsSameType(VSViewNormal::ms_Type) || pShaderFunction->GetType().IsSameType(VSWorldPos::ms_Type) || pShaderFunction->GetType().IsSameType(VSViewPos::ms_Type))
    {
        return false;
    }
    return true;
}