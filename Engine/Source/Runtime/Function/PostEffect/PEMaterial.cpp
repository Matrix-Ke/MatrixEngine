#include "PEMaterial.h"
#include "Core/GraphicInclude.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSPEMaterial, VSPostEffectFunction)
BEGIN_ADD_PROPERTY(VSPEMaterial, VSPostEffectFunction)
REGISTER_PROPERTY(m_pMaterialInstance, MaterialInstance, VSProperty::F_SAVE_LOAD_CLONE | VSProperty::F_REFLECT_NAME);
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSPEMaterial)
IMPLEMENT_INITIAL_END
VSPEMaterial::VSPEMaterial(const VSUsedName &ShowName, VSPostEffectSet *pPostEffectSet)
    : VSPostEffectFunction(ShowName, pPostEffectSet)
{

    VSInputNode *pInputNode = NULL;
    pInputNode = MX_NEW VSInputNode(VSPutNode::PET_IN, _T("InputColor"), this);
    ENGINE_ASSERT(pInputNode);
    m_pInput.AddElement(pInputNode);

    VSOutputNode *pOutNode = NULL;
    pOutNode = MX_NEW VSOutputNode(VSPutNode::PET_OUT, _T("OutColor"), this);
    ENGINE_ASSERT(pOutNode);
    m_pOutput.AddElement(pOutNode);
    m_pMaterialInstance = NULL;
}
VSPEMaterial::~VSPEMaterial()
{
}
VSPEMaterial::VSPEMaterial()
{
    m_pMaterialInstance = NULL;
}
VSPostEffectSceneRender *VSPEMaterial::CreateSceneRender()
{

    if (!m_pPostEffectRender)
    {
        m_pPostEffectRender = MX_NEW VSPEMaterialSceneRender();
    }

    return m_pPostEffectRender;
}
void VSPEMaterial::SetMaterial(VSMaterialR *pMaterial)
{
    m_pMaterialInstance = MX_NEW VSMaterialInstance(pMaterial);
}
void VSPEMaterial::OnDraw(VSCuller &Culler, double dAppTime)
{
    if (!m_pMaterialInstance)
    {
        return;
    }
    VSRenderTarget *pTarget = GetRenderTarget(m_pInput[INPUT_COLOR]);

    VSPostEffectSceneRender *pTemp = m_pPostEffectRender;
    ((VSPEMaterialSceneRender *)pTemp)->SetSourceTarget((VSTexture *)pTarget->GetCreateBy());
    ((VSPEMaterialSceneRender *)pTemp)->m_pMaterialInstacne = m_pMaterialInstance;
    m_pPostEffectRender->Draw(Culler, dAppTime);
}