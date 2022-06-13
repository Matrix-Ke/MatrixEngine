#include "OneParamAnimBlend.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSOneParamAnimBlend, VSAnimBlendFunction)
BEGIN_ADD_PROPERTY(VSOneParamAnimBlend, VSAnimBlendFunction)
REGISTER_PROPERTY(m_fParamMax, ParamMax, VSProperty::F_SAVE_LOAD_CLONE)
REGISTER_PROPERTY(m_fParamMin, ParamMin, VSProperty::F_SAVE_LOAD_CLONE)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSOneParamAnimBlend)
IMPLEMENT_INITIAL_END
VSOneParamAnimBlend::~VSOneParamAnimBlend()
{
}
VSOneParamAnimBlend::VSOneParamAnimBlend()
{
    m_fParam = 0.0f;
    m_fParamMax = 1.0f;
    m_fParamMin = -1.0f;
}
VSOneParamAnimBlend::VSOneParamAnimBlend(const VSUsedName &ShowName, VSAnimTree *pAnimTree)
    : VSAnimBlendFunction(ShowName, pAnimTree)
{
    m_fParam = 0.0f;
    m_fParamMax = 1.0f;
    m_fParamMin = -1.0f;

    Container::MString InputName0 = _T("Child0");
    VSInputNode *pInputNode = NULL;
    pInputNode = MX_NEW VSInputNode(VSPutNode::AVT_ANIM, InputName0, this);
    ENGINE_ASSERT(pInputNode);
    m_pInput.AddElement(pInputNode);

    Container::MString InputName1 = _T("Child1");
    pInputNode = NULL;
    pInputNode = MX_NEW VSInputNode(VSPutNode::AVT_ANIM, InputName1, this);
    ENGINE_ASSERT(pInputNode);
    m_pInput.AddElement(pInputNode);
}
void VSOneParamAnimBlend::AddInputNode()
{
    Container::MString InputName = _T("Child");
    Container::MString ID = Container::IntToString(m_pInput.GetNum());
    InputName += ID;
    VSInputNode *pInputNode = NULL;
    pInputNode = MX_NEW VSInputNode(VSPutNode::AVT_ANIM, InputName, this);
    ENGINE_ASSERT(pInputNode);
    m_pInput.AddElement(pInputNode);
}
void VSOneParamAnimBlend::DeleteInputNode()
{
    if (m_pInput.GetNum() > 2)
    {
        VSInputNode *pInputNode = m_pInput[m_pInput.GetNum() - 1];

        m_pInput.Erase(m_pInput.GetNum() - 1);
        if (!pInputNode)
        {
            return;
        }
        VSMAC_DELETE(pInputNode);
    }
}
bool VSOneParamAnimBlend::ComputePara(double dAppTime)
{
    if (m_fParam < m_fParamMin)
    {
        m_fParam = m_fParamMin;
    }
    else if (m_fParam > m_fParamMax)
    {
        m_fParam = m_fParamMax;
    }
    return 1;
}
bool VSOneParamAnimBlend::ComputeOutBoneMatrix(double dAppTime)
{

    return 1;
}
