#include "PostEffect/PostEffectSet.h"
#include "PostEffect/PEBeginFunction.h"
#include "PostEffect/PEEndFunction.h"
#include "Core/GraphicInclude.h"
#include "PostEffect/CommonPostEffect.h"
#include "PostEffect/PEMaterial.h"
#include "Render/OutputResource/RenderTarget.h"
#include "Core/Stream/Stream.h"
using namespace Matrix;
IMPLEMENT_RESOURCE(VSPostEffectSet)
IMPLEMENT_RTTI(VSPostEffectSet, MObject)
BEGIN_ADD_PROPERTY(VSPostEffectSet, MObject)
REGISTER_PROPERTY(m_ShowName, ShowName, VSProperty::F_SAVE_LOAD_CLONE)
REGISTER_PROPERTY(m_pPEBeginFunc, BeginFunction, VSProperty::F_SAVE_LOAD_CLONE)
REGISTER_PROPERTY(m_pPEEndFunc, EndFunction, VSProperty::F_SAVE_LOAD_CLONE)
REGISTER_PROPERTY(m_pPostEffectFunctionArray, PostEffectFunctionArray, VSProperty::F_SAVE_LOAD_CLONE)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSPostEffectSet)
IMPLEMENT_INITIAL_END
VSPostEffectSet::VSPostEffectSet()
{
    m_pPostEffectFunctionArray.Clear();
}
VSPostEffectSet::VSPostEffectSet(const VSUsedName &ShowName)
{
    m_pPostEffectFunctionArray.Clear();
    m_ShowName = ShowName;
    m_pPEBeginFunc = MX_NEW VSPEBeginFunction(_T("Begin"), this);
    m_pPEEndFunc = MX_NEW VSPEEndFunction(_T("End"), this);
}
VSPostEffectSet::~VSPostEffectSet()
{
    for (unsigned int i = 0; i < m_pPostEffectFunctionArray.GetNum(); i++)
    {
        VSPostEffectFunction *pShaderFunction = m_pPostEffectFunctionArray[i];
        m_pPostEffectFunctionArray[i] = NULL;
        VSMAC_DELETE(pShaderFunction);
    }
    m_pPostEffectFunctionArray.Clear();

    m_pPEBeginFunc = NULL;
    m_pPEEndFunc = NULL;
}
void VSPostEffectSet::AddPostEffectFunction(VSPostEffectFunction *pPostEffectFunction)
{
    ENGINE_ASSERT(pPostEffectFunction);

    m_pPostEffectFunctionArray.AddElement(pPostEffectFunction);
}
void VSPostEffectSet::DeletePostEffectFunction(VSPostEffectFunction *pPostEffectFunction)
{
    ENGINE_ASSERT(pPostEffectFunction);
    for (unsigned int i = 0; i < m_pPostEffectFunctionArray.GetNum(); i++)
    {
        if (m_pPostEffectFunctionArray[i] == pPostEffectFunction)
        {
            m_pPostEffectFunctionArray.Erase(i);
            return;
        }
    }
}

void VSPostEffectSet::Draw(VSCuller &Culler, double dAppTime)
{
    m_pPEEndFunc->ClearFlag();
    m_pPEEndFunc->Draw(Culler, dAppTime);
}
void VSPostEffectSet::SetBeginTargetArray(Container::MArray<VSRenderTarget *> *pBeginTargetArray)
{
    ENGINE_ASSERT(pBeginTargetArray && pBeginTargetArray->GetNum());
    m_pPEBeginFunc->SetPara(pBeginTargetArray);
    m_uiCurRTWidth = (*pBeginTargetArray)[0]->GetWidth();
    m_uiCurRTHeight = (*pBeginTargetArray)[0]->GetHeight();
}
void VSPostEffectSet::DisableRT()
{
    m_pPEEndFunc->DisableRT();
    m_uiCurRTWidth = 0;
    m_uiCurRTHeight = 0;
}
VSRenderTarget *VSPostEffectSet::GetEndTarget(unsigned int i)
{
    if (i < m_pPEEndFunc->m_pInput.GetNum())
    {
        VSRenderTarget *pTexture = m_pPEEndFunc->GetRenderTarget(m_pPEEndFunc->m_pInput[i]);
        return pTexture;
    }
    return NULL;
}
VSPostEffectFunction *VSPostEffectSet::GetPEFunctionFromShowName(const VSUsedName &ShowName)
{
    for (unsigned int i = 0; i < m_pPostEffectFunctionArray.GetNum(); i++)
    {
        if (m_pPostEffectFunctionArray[i]->GetShowName() == ShowName)
        {
            return m_pPostEffectFunctionArray[i];
        }
    }
    return NULL;
}
VSPESetGray::VSPESetGray(const VSUsedName &ShowName) : VSPostEffectSet(ShowName)
{
    VSPEGray *pPEGray = MX_NEW VSPEGray(_T("Gray"), this);
    m_pPEEndFunc->GetInputNode(VSPEEndFunction::INPUT_COLOR)->Connection(pPEGray->GetOutputNode(VSPEGray::OUT_COLOR));
    pPEGray->GetInputNode(VSPEGray::INPUT_COLOR)->Connection(m_pPEBeginFunc->GetOutputNode(VSPEBeginFunction::OUT_COLOR));
}
VSPESetGray::~VSPESetGray()
{
}

VSPESetMaterialAndGray::VSPESetMaterialAndGray(const VSUsedName &ShowName, VSMaterialR *pMaterial) : VSPostEffectSet(ShowName)
{
    VSPEGray *pPEGray = MX_NEW VSPEGray(_T("Gray"), this);
    VSPEMaterial *pPEMaterial = MX_NEW VSPEMaterial(_T("Material"), this);
    pPEMaterial->SetMaterial(pMaterial);
    m_pPEEndFunc->GetInputNode(VSPEEndFunction::INPUT_COLOR)->Connection(pPEMaterial->GetOutputNode(VSPEMaterial::OUT_COLOR));
    pPEMaterial->GetInputNode(VSPEMaterial::INPUT_COLOR)->Connection(pPEGray->GetOutputNode(VSPEGray::OUT_COLOR));
    pPEGray->GetInputNode(VSPEGray::INPUT_COLOR)->Connection(m_pPEBeginFunc->GetOutputNode(VSPEBeginFunction::OUT_COLOR));
}
VSPESetMaterialAndGray::~VSPESetMaterialAndGray()
{
}
VSPESetMaterial_Gray_Bloom::VSPESetMaterial_Gray_Bloom(const VSUsedName &ShowName, VSMaterialR *pMaterial) : VSPostEffectSet(ShowName)
{
    VSPEGray *pPEGray = MX_NEW VSPEGray(_T("Gray"), this);
    VSPEMaterial *pPEMaterial = MX_NEW VSPEMaterial(_T("Material"), this);
    VSPEBloom *pPEBloom = MX_NEW VSPEBloom(_T("Bloom"), this);
    pPEBloom->MiddleGray = 0.8f;
    pPEMaterial->SetMaterial(pMaterial);
    m_pPEEndFunc->GetInputNode(VSPEEndFunction::INPUT_COLOR)->Connection(pPEMaterial->GetOutputNode(VSPEMaterial::OUT_COLOR));
    pPEMaterial->GetInputNode(VSPEMaterial::INPUT_COLOR)->Connection(pPEGray->GetOutputNode(VSPEGray::OUT_COLOR));
    pPEGray->GetInputNode(VSPEGray::INPUT_COLOR)->Connection(pPEBloom->GetOutputNode(VSPEBloom::OUT_COLOR));
    pPEBloom->GetInputNode(VSPEBloom::INPUT_COLOR)->Connection(m_pPEBeginFunc->GetOutputNode(VSPEBeginFunction::OUT_COLOR));
}
VSPESetMaterial_Gray_Bloom::~VSPESetMaterial_Gray_Bloom()
{
}
