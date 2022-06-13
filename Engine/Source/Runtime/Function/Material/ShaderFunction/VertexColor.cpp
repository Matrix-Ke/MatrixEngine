#include "VertexColor.h"
#include "ShaderStringFactory.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSVertexColor, VSShaderFunction)
BEGIN_ADD_PROPERTY(VSVertexColor, VSShaderFunction)
REGISTER_PROPERTY(m_uiColorIndex, ColorIndex, VSProperty::F_SAVE_LOAD_CLONE)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSVertexColor)
IMPLEMENT_INITIAL_END
VSVertexColor::VSVertexColor(const VSUsedName &ShowName, VSMaterial *pMaterial)
    : VSShaderFunction(ShowName, pMaterial)
{

    Container::MString OutputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    Container::MString OutputName = _T("VertexColorOutput") + OutputID;
    VSOutputNode *pOutputNode = NULL;
    pOutputNode = MX_NEW VSOutputNode(VSPutNode::VT_4, OutputName, this);
    ENGINE_ASSERT(pOutputNode);
    m_pOutput.AddElement(pOutputNode);
    VSShaderStringFactory::ms_ShaderValueIndex++;
    m_uiColorIndex = 0;
}
VSVertexColor::VSVertexColor()
{
    m_uiColorIndex = 0;
}
VSVertexColor::~VSVertexColor()
{
}
void VSVertexColor::ResetInShaderName(MaterialShaderPara &MSPara)
{
    Container::MString OutputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    Container::MString OutputName = _T("VertexColorOutput") + OutputID;
    m_pOutput[0]->SetNodeName(OutputName);
    VSShaderStringFactory::ms_ShaderValueIndex++;
}
bool VSVertexColor::GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const
{
    if (VSShaderStringFactory::ms_InputColor[m_uiColorIndex].GetLength() > 0)
    {
        OutString += GetOutputNode(VSOutputNode::ONI_COLOR)->GetNodeName().GetString() + _T(" = ") + VSShaderStringFactory::ms_InputColor[m_uiColorIndex] + _T(";\n");
    }
    return 1;
}
