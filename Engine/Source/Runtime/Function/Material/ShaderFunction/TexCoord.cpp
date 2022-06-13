#include "TexCoord.h"
#include "ShaderStringFactory.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSTexCoord, VSShaderFunction)
BEGIN_ADD_PROPERTY(VSTexCoord, VSShaderFunction)
REGISTER_PROPERTY(m_uiTexCoordIndex, exCoordIndex, VSProperty::F_SAVE_LOAD_CLONE)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSTexCoord)
IMPLEMENT_INITIAL_END
VSTexCoord::VSTexCoord(const VSUsedName &ShowName, VSMaterial *pMaterial)
    : VSShaderFunction(ShowName, pMaterial)
{

    Container::MString OutputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    Container::MString OutputName = _T("TexCoordOutput") + OutputID;
    VSOutputNode *pOutputNode = NULL;
    pOutputNode = MX_NEW VSOutputNode(VSPutNode::VT_2, OutputName, this);
    ENGINE_ASSERT(pOutputNode);
    m_pOutput.AddElement(pOutputNode);
    VSShaderStringFactory::ms_ShaderValueIndex++;
    m_uiTexCoordIndex = 0;
}
VSTexCoord::VSTexCoord()
{
    m_uiTexCoordIndex = 0;
}
VSTexCoord::~VSTexCoord()
{
}
void VSTexCoord::ResetInShaderName(MaterialShaderPara &MSPara)
{
    Container::MString OutputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    Container::MString OutputName = _T("TexCoordOutput") + OutputID;
    m_pOutput[0]->SetNodeName(OutputName);
    VSShaderStringFactory::ms_ShaderValueIndex++;
}
bool VSTexCoord::GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const
{
    if (VSShaderStringFactory::ms_TextureInputCoordValue[m_uiTexCoordIndex].GetLength() > 0)
    {
        OutString += GetOutputNode(VSOutputNode::ONI_COLOR)->GetNodeName().GetString() + _T(" = ") + VSShaderStringFactory::ms_TextureInputCoordValue[m_uiTexCoordIndex] + _T(";\n");
    }
    return 1;
}
