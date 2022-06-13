#include "CameraShaderFunction.h"
#include "ShaderStringFactory.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
using namespace Matrix;

IMPLEMENT_RTTI(VSViewWorldDir, VSShaderFunction)
BEGIN_ADD_PROPERTY(VSViewWorldDir, VSShaderFunction)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSViewWorldDir)
IMPLEMENT_INITIAL_END
VSViewWorldDir::VSViewWorldDir(const VSUsedName &ShowName, VSMaterial *pMaterial)
    : VSShaderFunction(ShowName, pMaterial)
{

    Container::MString OutputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    Container::MString OutputName = _T("ViewWorldDirOutput") + OutputID;
    VSOutputNode *pOutputNode = NULL;
    pOutputNode = MX_NEW VSOutputNode(VSPutNode::VT_3, OutputName, this);
    ENGINE_ASSERT(pOutputNode);
    m_pOutput.AddElement(pOutputNode);
    VSShaderStringFactory::ms_ShaderValueIndex++;
}
VSViewWorldDir::VSViewWorldDir()
{
}
VSViewWorldDir::~VSViewWorldDir()
{
}
void VSViewWorldDir::ResetInShaderName(MaterialShaderPara &MSPara)
{
    Container::MString OutputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    Container::MString OutputName = _T("ViewWorldDirOutput") + OutputID;
    m_pOutput[0]->SetNodeName(OutputName);
    VSShaderStringFactory::ms_ShaderValueIndex++;
}
bool VSViewWorldDir::GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const
{

    OutString += GetOutputNode(VSOutputNode::ONI_VALUE)->GetNodeName().GetString() + _T(" = ") + *VSShaderStringFactory::ms_ViewWorldDir + _T(";\n");

    return 1;
}

IMPLEMENT_RTTI(VSCameraWorldPos, VSShaderFunction)
BEGIN_ADD_PROPERTY(VSCameraWorldPos, VSShaderFunction)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSCameraWorldPos)
IMPLEMENT_INITIAL_END
VSCameraWorldPos::VSCameraWorldPos(const VSUsedName &ShowName, VSMaterial *pMaterial)
    : VSShaderFunction(ShowName, pMaterial)
{

    Container::MString OutputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    Container::MString OutputName = _T("CameraWorldPosOutput") + OutputID;
    VSOutputNode *pOutputNode = NULL;
    pOutputNode = MX_NEW VSOutputNode(VSPutNode::VT_3, OutputName, this);
    ENGINE_ASSERT(pOutputNode);
    m_pOutput.AddElement(pOutputNode);
    VSShaderStringFactory::ms_ShaderValueIndex++;
}
VSCameraWorldPos::VSCameraWorldPos()
{
}
VSCameraWorldPos::~VSCameraWorldPos()
{
}
void VSCameraWorldPos::ResetInShaderName(MaterialShaderPara &MSPara)
{
    Container::MString OutputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    Container::MString OutputName = _T("CameraWorldPosOutput") + OutputID;
    m_pOutput[0]->SetNodeName(OutputName);
    VSShaderStringFactory::ms_ShaderValueIndex++;
}
bool VSCameraWorldPos::GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const
{

    OutString += GetOutputNode(VSOutputNode::ONI_VALUE)->GetNodeName().GetString() + _T(" = ") + *VSShaderStringFactory::ms_CameraWorldPos + _T(";\n");

    return 1;
}
