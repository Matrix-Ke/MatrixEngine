#include "1DTexSampler.h"
#include "ShaderStringFactory.h"
#include "GraphicInclude.h"
using namespace Matrix;

IMPLEMENT_RTTI(VS1DTexSampler, VSTexSampler)
BEGIN_ADD_PROPERTY(VS1DTexSampler, VSTexSampler)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VS1DTexSampler)
IMPLEMENT_INITIAL_END

VS1DTexSampler::VS1DTexSampler(const VSUsedName &ShowName, VSMaterial *pMaterial)
    : VSTexSampler(ShowName, pMaterial)
{

    VSString InputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    VSString InputName = _T("Tex1DSamplerInput") + InputID;
    VSInputNode *pInputNode = NULL;
    pInputNode = VS_NEW VSInputNode(VSPutNode::VT_1, InputName, this);
    VSMAC_ASSERT(pInputNode);
    m_pInput.AddElement(pInputNode);
    VSShaderStringFactory::ms_ShaderValueIndex++;

    VSString OutputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    VSString OutputName = _T("Tex1DSamplerOutput") + OutputID;
    VSOutputNode *pOutputNode = NULL;
    pOutputNode = VS_NEW VSOutputNode(VSPutNode::VT_4, OutputName, this);
    VSMAC_ASSERT(pOutputNode);
    m_pOutput.AddElement(pOutputNode);
    VSShaderStringFactory::ms_ShaderValueIndex++;

    VSString OutputNameR = VSRenderer::GetValueElement(GetOutputNode(VSOutputNode::ONI_COLOR), VSRenderer::VE_R);

    pOutputNode = VS_NEW VSOutputNode(VSPutNode::VT_1, OutputNameR, this);
    VSMAC_ASSERT(pOutputNode);
    m_pOutput.AddElement(pOutputNode);

    VSString OutputNameG = VSRenderer::GetValueElement(GetOutputNode(VSOutputNode::ONI_COLOR), VSRenderer::VE_G);

    pOutputNode = VS_NEW VSOutputNode(VSPutNode::VT_1, OutputNameG, this);
    VSMAC_ASSERT(pOutputNode);
    m_pOutput.AddElement(pOutputNode);

    VSString OutputNameB = VSRenderer::GetValueElement(GetOutputNode(VSOutputNode::ONI_COLOR), VSRenderer::VE_B);

    pOutputNode = VS_NEW VSOutputNode(VSPutNode::VT_1, OutputNameB, this);
    VSMAC_ASSERT(pOutputNode);
    m_pOutput.AddElement(pOutputNode);

    VSString OutputNameA = VSRenderer::GetValueElement(GetOutputNode(VSOutputNode::ONI_COLOR), VSRenderer::VE_A);

    pOutputNode = VS_NEW VSOutputNode(VSPutNode::VT_1, OutputNameA, this);
    VSMAC_ASSERT(pOutputNode);
    m_pOutput.AddElement(pOutputNode);
}
void VS1DTexSampler::ResetInShaderName(MaterialShaderPara &MSPara)
{
    VSString InputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    VSString InputName = _T("Tex1DSamplerInput") + InputID;
    m_pInput[0]->SetNodeName(InputName);
    VSShaderStringFactory::ms_ShaderValueIndex++;

    VSString OutputID = Container::IntToString(VSShaderStringFactory::ms_ShaderValueIndex);
    VSString OutputName = _T("Tex1DSamplerOutput") + OutputID;
    m_pOutput[0]->SetNodeName(OutputName);
    VSShaderStringFactory::ms_ShaderValueIndex++;

    VSString OutputNameR = VSRenderer::GetValueElement(GetOutputNode(VSOutputNode::ONI_COLOR), VSRenderer::VE_R);
    m_pOutput[1]->SetNodeName(OutputNameR);

    VSString OutputNameG = VSRenderer::GetValueElement(GetOutputNode(VSOutputNode::ONI_COLOR), VSRenderer::VE_G);
    m_pOutput[2]->SetNodeName(OutputNameG);

    VSString OutputNameB = VSRenderer::GetValueElement(GetOutputNode(VSOutputNode::ONI_COLOR), VSRenderer::VE_B);
    m_pOutput[3]->SetNodeName(OutputNameB);

    VSString OutputNameA = VSRenderer::GetValueElement(GetOutputNode(VSOutputNode::ONI_COLOR), VSRenderer::VE_A);
    m_pOutput[4]->SetNodeName(OutputNameA);
}
VS1DTexSampler::VS1DTexSampler()
{
}
VS1DTexSampler::~VS1DTexSampler()
{
}
bool VS1DTexSampler::GetFunctionString(VSString &OutString, MaterialShaderPara &MSPara) const
{
    if (VSRenderer::ms_pRenderer)
        OutString += VSRenderer::ms_pRenderer->Tex1D(this, MSPara.uiCompileShaderType);

    if (m_uiVESRGB)
    {
        VSString NodeString = VSRenderer::GetValueElement(GetOutputNode(VSOutputNode::ONI_COLOR), m_uiVESRGB);

        OutString += NodeString + _T(" = ");
        VSRenderer::ms_pRenderer->GreaterZeroPow(NodeString, 2.2f, OutString);
        OutString += _T(";\n");
    }

    if (m_uiVEDecode)
    {
        VSString NodeString = VSRenderer::GetValueElement(GetOutputNode(VSOutputNode::ONI_COLOR), m_uiVEDecode);

        OutString += NodeString + _T(" = ");
        VSRenderer::ms_pRenderer->DecodeNormal1(NodeString, OutString);
        OutString += _T(";\n");
    }

    return 1;
}
void VS1DTexSampler::SetTexture(VSTexAllStateR *pTexAllState)
{
    VSMAC_ASSERT(pTexAllState);
    VSMAC_ASSERT(pTexAllState->GetResource()->GetTexture()->GetTexType() == VSTexture::TT_1D);
    m_pTexAllState = pTexAllState;
}
bool VS1DTexSampler::GetOutputValueString(VSString &OutString, MaterialShaderPara &MSPara) const
{
    VSString Temp;
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
        VSMAC_ASSERT(0);

    OutString += m_pOutput[0]->GetNodeName().GetString() + _T(" = ") + Temp + _T(";\n");

    return 1;
}
