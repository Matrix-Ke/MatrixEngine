#include "ColorBuffer.h"
#include "ShaderStringFactory.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSColorBuffer, VSShaderFunction)
BEGIN_ADD_PROPERTY(VSColorBuffer, VSShaderFunction)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSColorBuffer)
IMPLEMENT_INITIAL_END
VSColorBuffer::VSColorBuffer(const VSUsedName &ShowName, VSMaterial *pMaterial)
    : VSShaderFunction(ShowName, pMaterial)
{

    Container::MString InputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    Container::MString InputName = _T("ColorBufferInput") + InputID;
    VSInputNode *pInputNode = NULL;
    pInputNode = MX_NEW VSInputNode(VSPutNode::VT_2, InputName, this);
    ENGINE_ASSERT(pInputNode);
    m_pInput.AddElement(pInputNode);
    VSShaderStringFactory::ms_ShaderValueIndex++;

    Container::MString OutputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    Container::MString OutputName = _T("ColorBufferOutput") + OutputID;
    VSOutputNode *pOutputNode = NULL;
    pOutputNode = MX_NEW VSOutputNode(VSPutNode::VT_4, OutputName, this);
    ENGINE_ASSERT(pOutputNode);
    m_pOutput.AddElement(pOutputNode);
    VSShaderStringFactory::ms_ShaderValueIndex++;

    Container::MString OutputNameR = VSRenderer::GetValueElement(GetOutputNode(VSOutputNode::ONI_COLOR), VSRenderer::VE_R);

    pOutputNode = MX_NEW VSOutputNode(VSPutNode::VT_1, OutputNameR, this);
    ENGINE_ASSERT(pOutputNode);
    m_pOutput.AddElement(pOutputNode);

    Container::MString OutputNameG = VSRenderer::GetValueElement(GetOutputNode(VSOutputNode::ONI_COLOR), VSRenderer::VE_G);

    pOutputNode = MX_NEW VSOutputNode(VSPutNode::VT_1, OutputNameG, this);
    ENGINE_ASSERT(pOutputNode);
    m_pOutput.AddElement(pOutputNode);

    Container::MString OutputNameB = VSRenderer::GetValueElement(GetOutputNode(VSOutputNode::ONI_COLOR), VSRenderer::VE_B);

    pOutputNode = MX_NEW VSOutputNode(VSPutNode::VT_1, OutputNameB, this);
    ENGINE_ASSERT(pOutputNode);
    m_pOutput.AddElement(pOutputNode);

    Container::MString OutputNameA = VSRenderer::GetValueElement(GetOutputNode(VSOutputNode::ONI_COLOR), VSRenderer::VE_A);

    pOutputNode = MX_NEW VSOutputNode(VSPutNode::VT_1, OutputNameA, this);
    ENGINE_ASSERT(pOutputNode);
    m_pOutput.AddElement(pOutputNode);
}
VSColorBuffer::VSColorBuffer()
{
}
VSColorBuffer::~VSColorBuffer()
{
}
void VSColorBuffer::ResetInShaderName(MaterialShaderPara &MSPara)
{
    Container::MString InputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    Container::MString InputName = _T("ColorBufferInput") + InputID;
    m_pInput[0]->SetNodeName(InputName);
    VSShaderStringFactory::ms_ShaderValueIndex++;

    Container::MString OutputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    Container::MString OutputName = _T("ColorBufferOutput") + OutputID;
    m_pOutput[0]->SetNodeName(OutputName);
    VSShaderStringFactory::ms_ShaderValueIndex++;

    Container::MString OutputNameR = VSRenderer::GetValueElement(GetOutputNode(VSOutputNode::ONI_COLOR), VSRenderer::VE_R);
    m_pOutput[1]->SetNodeName(OutputNameR);

    Container::MString OutputNameG = VSRenderer::GetValueElement(GetOutputNode(VSOutputNode::ONI_COLOR), VSRenderer::VE_G);
    m_pOutput[2]->SetNodeName(OutputNameG);

    Container::MString OutputNameB = VSRenderer::GetValueElement(GetOutputNode(VSOutputNode::ONI_COLOR), VSRenderer::VE_B);
    m_pOutput[3]->SetNodeName(OutputNameB);

    Container::MString OutputNameA = VSRenderer::GetValueElement(GetOutputNode(VSOutputNode::ONI_COLOR), VSRenderer::VE_A);
    m_pOutput[4]->SetNodeName(OutputNameA);
}
bool VSColorBuffer::GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const
{
    ENGINE_ASSERT(VSRenderer::ms_pRenderer);
    OutString += VSRenderer::ms_pRenderer->TexColorBuffer(this);
    return 1;
}
bool VSColorBuffer::GetInputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const
{
    ENGINE_ASSERT(VSRenderer::ms_pRenderer);
    Container::MString Temp;
    if (m_pInput[0]->GetValueType() == VSPutNode::VT_1)
    {
        OutString += VSRenderer::ms_pRenderer->Float() + _T(" "); /*_T("VSREAL ");*/
        Temp = VSRenderer::ms_pRenderer->FloatConst(_T("0"));
    }
    else if (m_pInput[0]->GetValueType() == VSPutNode::VT_2)
    {
        OutString += VSRenderer::ms_pRenderer->Float2() + _T(" ");      /*_T("float2 ");*/
        Temp = VSRenderer::ms_pRenderer->Float2Const(_T("0"), _T("0")); /*_T("float2(0,0)");*/
    }
    else if (m_pInput[0]->GetValueType() == VSPutNode::VT_3)
    {
        OutString += VSRenderer::ms_pRenderer->Float3() + _T(" ");               /*_T("float3 ");*/
        Temp = VSRenderer::ms_pRenderer->Float3Const(_T("0"), _T("0"), _T("0")); /*_T("float3(0,0,0)");*/
    }
    else if (m_pInput[0]->GetValueType() == VSPutNode::VT_4)
    {
        OutString += VSRenderer::ms_pRenderer->Float4() + _T(" ");                        /*_T("float4 ");*/
        Temp = VSRenderer::ms_pRenderer->Float4Const(_T("0"), _T("0"), _T("0"), _T("1")); /*_T("float4(0,0,0,1)");*/
    }
    else
        return 0;
    if (!m_pInput[0]->GetOutputLink())
    {
        OutString += m_pInput[0]->GetNodeName().GetString() + _T(" = ") + VSShaderStringFactory::ms_TextureInputCoordValue[0] + _T(";\n");
        return 1;
    }

    OutString += GetValueEqualString(m_pInput[0]->GetOutputLink(), m_pInput[0]);

    return 1;
}
bool VSColorBuffer::GetOutputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const
{
    Container::MString Temp;
    if (m_pOutput[0]->GetValueType() == VSPutNode::VT_1)
    {
        OutString += VSRenderer::ms_pRenderer->Float() + _T(" "); /*_T("VSREAL ");*/
        Temp = VSRenderer::ms_pRenderer->FloatConst(_T("0"));
    }
    else if (m_pOutput[0]->GetValueType() == VSPutNode::VT_2)
    {
        OutString += VSRenderer::ms_pRenderer->Float2() + _T(" "); /*_T("float2 ")*/
        ;
        Temp = VSRenderer::ms_pRenderer->Float2Const(_T("0"), _T("0")); /*_T("float2(0,0)");*/
    }
    else if (m_pOutput[0]->GetValueType() == VSPutNode::VT_3)
    {
        OutString += VSRenderer::ms_pRenderer->Float3() + _T(" ");               /*_T("float3 ");*/
        Temp = VSRenderer::ms_pRenderer->Float3Const(_T("0"), _T("0"), _T("0")); /*_T("float3(0,0,0)");*/
    }
    else if (m_pOutput[0]->GetValueType() == VSPutNode::VT_4)
    {
        OutString += VSRenderer::ms_pRenderer->Float4() + _T(" ");                        /*_T("float4 ");*/
        Temp = VSRenderer::ms_pRenderer->Float4Const(_T("0"), _T("0"), _T("0"), _T("1")); /*_T("float4(0,0,0,1)");*/
    }
    else
        return 0;

    OutString += m_pOutput[0]->GetNodeName().GetString() + _T(" = ") + Temp + _T(";\n");

    return 1;
}