#include "DirectionLight.h"
#include "GraphicInclude.h"
#include "SceneRender.h"
#include "Stream.h"
#include "Ray3.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSDirectionLight, VSLocalLight)
BEGIN_ADD_PROPERTY(VSDirectionLight, VSLocalLight)
REGISTER_ENUM_PROPERTY(m_uiShadowType, ShadowType, DirectionLightShadowType, VSProperty::F_SAVE_LOAD_CLONE | VSProperty::F_REFLECT_NAME)
REGISTER_PROPERTY(m_fLightFunWidth, LightFunWidth, VSProperty::F_SAVE_LOAD_CLONE | VSProperty::F_REFLECT_NAME)
REGISTER_PROPERTY(m_fLightFunHeight, LightFunHeight, VSProperty::F_SAVE_LOAD_CLONE | VSProperty::F_REFLECT_NAME)
REGISTER_PROPERTY(m_fLightFunNear, LightFunNear, VSProperty::F_SAVE_LOAD_CLONE | VSProperty::F_REFLECT_NAME)
REGISTER_PROPERTY(m_fLightFunFar, LightFunFar, VSProperty::F_SAVE_LOAD_CLONE | VSProperty::F_REFLECT_NAME)
REGISTER_PROPERTY(m_WorldRenderBV, WorldRenderBV, VSProperty::F_SAVE_LOAD_CLONE)
REGISTER_PROPERTY(m_fOSMDistance, OSMDistance, VSProperty::F_SAVE_LOAD_CLONE | VSProperty::F_REFLECT_NAME)
BEGIN_ADD_ENUM
ADD_ENUM(DirectionLightShadowType, ST_VOLUME)
ADD_ENUM(DirectionLightShadowType, ST_OSM)
ADD_ENUM(DirectionLightShadowType, ST_CSM)
ADD_ENUM(DirectionLightShadowType, ST_PROJECT)
END_ADD_ENUM
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSDirectionLight)
IMPLEMENT_INITIAL_END
#define CSM_LEVLE 3
VSDirectionLight::VSDirectionLight()
{
    m_uiRTWidth = 2048;
    SetShadowType(ST_OSM);
    m_ZBias = 0.005f;
    m_fLightFunWidth = 1000.0f;
    m_fLightFunHeight = 1000.0f;
    m_fLightFunNear = 1.0f;
    m_fLightFunFar = 8000.0f;
    m_fOSMDistance = 5000.0f;
}
VSDirectionLight::~VSDirectionLight()
{
}
void VSDirectionLight::ResetShadow()
{
    m_pShadowTexture.Clear();
    m_pPEVolumeSMSceneRender = NULL;
    m_pShadowMapSceneRender = NULL;
    m_pProjectShadowSceneRender = NULL;
    m_pVolumeShadowSceneRender = NULL;
    m_pCSMRTArray.Clear();
    m_VolumeShadowCuller.ClearAll();
    m_ShadowCuller.ClearAll();
}
void VSDirectionLight::SetShadowType(unsigned int uiShadowType)
{
    ResetShadow();
    if (uiShadowType == ST_VOLUME)
    {

        m_pShadowTexture.AddElement(VS_NEW VSTexAllState());
        m_pShadowTexture[0]->SetSamplerState((VSSamplerState *)VSSamplerState::GetTwoLine());

        m_pPEVolumeSMSceneRender = VS_NEW VSPEVolumeShadowMapSceneRender();
        m_pPEVolumeSMSceneRender->SetParam(VSRenderer::CF_COLOR, VSColorRGBA(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0);

        m_pVolumeShadowSceneRender = VS_NEW VSVolumeShadowSceneRender();
        m_pVolumeShadowSceneRender->m_pLocalLight = this;
        m_pVolumeShadowSceneRender->SetParam(VSRenderer::CF_STENCIL, VSColorRGBA(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 15);
    }
    else if (uiShadowType == ST_OSM || uiShadowType == ST_PROJECT)
    {
        m_pShadowTexture.AddElement(VS_NEW VSTexAllState());
        m_pShadowTexture[0]->SetSamplerState((VSSamplerState *)VSSamplerState::GetTwoLineBorderOne());
        m_pShadowMapSceneRender = VS_NEW VSShadowMapSceneRender(VSShadowMapSceneRender::SMT_SHADOWMAP);
        m_pShadowMapSceneRender->m_pLocalLight = this;
        m_pShadowMapSceneRender->SetParam(VSRenderer::CF_USE_ALL, VSColorRGBA(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0);
        if (uiShadowType == ST_PROJECT)
        {
            m_pProjectShadowSceneRender = VS_NEW VSProjectShadowSceneRender();
            m_pProjectShadowSceneRender->m_pLocalLight = this;
            m_pProjectShadowSceneRender->SetParam(VSRenderer::CF_STENCIL, VSColorRGBA(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 15);
        }
    }
    else if (uiShadowType == ST_CSM)
    {
        for (unsigned int i = 0; i < CSM_LEVLE; i++)
        {
            m_pShadowTexture.AddElement(VS_NEW VSTexAllState());
            m_pShadowTexture[i]->SetSamplerState((VSSamplerState *)VSSamplerState::GetTwoLineBorderOne());
        }
        m_pCSMRTArray.SetBufferNum(CSM_LEVLE);
        m_pShadowMapSceneRender = VS_NEW VSShadowMapSceneRender(VSShadowMapSceneRender::SMT_SHADOWMAP);
        m_pShadowMapSceneRender->m_pLocalLight = this;
        m_pShadowMapSceneRender->SetParam(VSRenderer::CF_USE_ALL, VSColorRGBA(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0);
    }
    m_uiShadowType = uiShadowType;
}
bool VSDirectionLight::PostClone(MObject *pObjectSrc)
{
    VSLight::PostClone(pObjectSrc);

    SetShadowType(m_uiShadowType);
    return true;
}
bool VSDirectionLight::PostLoad(MStream *pStream)
{
    VSLight::PostLoad(pStream);
    SetShadowType(m_uiShadowType);
    return true;
}

void VSDirectionLight::DisableDependenceShadowMap(VSCuller &CurCuller, double dAppTime)
{
    if (m_uiShadowType == ST_VOLUME || m_uiShadowType == ST_OSM || m_uiShadowType == ST_PROJECT)
    {
        if (m_pVolumeShadowRenderTarget)
        {
            VSResourceManager::DisableOutputResource(m_pVolumeShadowRenderTarget);
        }
    }
    else if (m_uiShadowType == ST_CSM)
    {
        for (unsigned int i = 0; i < CSM_LEVLE; i++)
        {
            if (m_pCSMRTArray[i])
            {
                VSResourceManager::DisableOutputResource(m_pCSMRTArray[i]);
            }
        }
    }
    for (unsigned int i = 0; i < m_pShadowTexture.GetNum(); i++)
    {
        m_pShadowTexture[i]->SetTexture(NULL);
    }
}
void VSDirectionLight::DrawVolumeShadow(VSCuller &CurCuller, double dAppTime)
{
    if (m_uiShadowType != ST_VOLUME)
    {
        return;
    }
    m_VolumeShadowCuller.GetSceneContent(*CurCuller.GetCamera(), m_pScene, this, dAppTime);

    m_pVolumeShadowSceneRender->Draw(m_VolumeShadowCuller, dAppTime);

    m_pVolumeShadowRenderTarget = VSResourceManager::GetRenderTarget(VSRenderer::ms_pRenderer->GetCurRTWidth(), VSRenderer::ms_pRenderer->GetCurRTHeight(), VSRenderer::SFT_A8R8G8B8, 0);

    m_pPEVolumeSMSceneRender->ClearRTAndDepth();
    m_pPEVolumeSMSceneRender->AddRenderTarget(m_pVolumeShadowRenderTarget);
    m_pPEVolumeSMSceneRender->Draw(CurCuller, dAppTime);

    m_pShadowTexture[0]->SetTexture((VSTexture *)m_pVolumeShadowRenderTarget->GetCreateBy());
}
Primitive::AABB3 VSDirectionLight::GetMaxAABB(Container::MArray<Primitive::AABB3> &AABBArray)
{
    Primitive::AABB3 Temp;
    for (unsigned int i = 0; i < AABBArray.GetNum(); i++)
    {

        if (i == 0)
        {
            Temp = AABBArray[i];
        }
        else
        {
            Temp = Temp.MergeAABB(AABBArray[i]);
        }
    }
    return Temp;
}
void VSDirectionLight::DrawOSM(VSCuller &CurCuller, double dAppTime)
{
#define DRAW_DEPTH                                                                                                              \
    {                                                                                                                           \
        m_pOSMShadowRenderTarget = VSResourceManager::GetRenderTarget(m_uiRTWidth, m_uiRTWidth, VSRenderer::SFT_R16F, 0);       \
        VSDepthStencil *pDepthStencil = VSResourceManager::GetDepthStencil(m_uiRTWidth, m_uiRTWidth, VSRenderer::SFT_D24S8, 0); \
        m_pShadowMapSceneRender->ClearRTAndDepth();                                                                             \
        m_pShadowMapSceneRender->SetDepthStencil(pDepthStencil, VSCuller::RG_NORMAL);                                           \
        m_pShadowMapSceneRender->AddRenderTarget(m_pOSMShadowRenderTarget);                                                     \
        m_pShadowMapSceneRender->Draw(m_ShadowCuller, dAppTime);                                                                \
        m_pShadowTexture[0]->SetTexture((VSTexture *)m_pOSMShadowRenderTarget->GetCreateBy());                                  \
        VSResourceManager::DisableOutputResource(pDepthStencil);                                                                \
    }
    VSCamera *pCamera = CurCuller.GetCamera();
    VSREAL fFar = pCamera->GetZFar();
    VSREAL fTempOSMDistance = m_fOSMDistance;
    if (fTempOSMDistance > fFar)
    {
        fTempOSMDistance = fFar;
    }
    pCamera->SetPerspectiveFov(pCamera->GetFov(), pCamera->GetAspect(), pCamera->GetZNear(), fTempOSMDistance);
    m_ShadowCuller.GetSceneContent(*pCamera, m_pScene, this, dAppTime);

    Primitive::AABB3 CasterAABB = pCamera->GetFrustumAABB();

    Math::Vector3 Center = CasterAABB.GetCenter();

    Math::Vector3 Dir, Up, Right;
    GetWorldDir(Dir, Up, Right);
    VSRay3 Ray(Center, Dir * (-1.0f));

    unsigned int Q;
    VSREAL tN, tF;
    if (CasterAABB.RelationWith(Ray, Q, tN, tF) != VSINTERSECT)
    {
        DRAW_DEPTH;
        return;
    }

    Math::Vector3 LigthPT = Center - Dir * tN * 2.0f;

    VSCamera LightCamera;
    LightCamera.CreateFromLookAt(LigthPT, Center);

    VSMatrix3X3W LightView = LightCamera.GetViewMatrix();

    Primitive::AABB3 NewCasterAABB;
    NewCasterAABB.Transform(CasterAABB, LightView);

    VSREAL NewNear = NewCasterAABB.GetMinPoint().z;
    VSREAL NewFar = NewCasterAABB.GetMaxPoint().z;
    LightCamera.SetOrthogonal(NewCasterAABB.GetMaxPoint().x - NewCasterAABB.GetMinPoint().x,
                              NewCasterAABB.GetMaxPoint().y - NewCasterAABB.GetMinPoint().y,
                              NewNear, NewFar);

    m_LightShadowMatrix = LightCamera.GetViewMatrix() * LightCamera.GetProjMatrix();

    DRAW_DEPTH;

    pCamera->SetPerspectiveFov(pCamera->GetFov(), pCamera->GetAspect(), pCamera->GetZNear(), fFar);
}
void VSDirectionLight::DrawDependenceShadowMap(VSCuller &CurCuller, double dAppTime)
{
    if (m_bEnable && m_bIsCastShadow)
    {
        if (m_uiShadowType == ST_OSM)
        {
            DrawOSM(CurCuller, dAppTime);
        }
        else if (m_uiShadowType == ST_CSM)
        {
            DrawCSM(CurCuller, dAppTime);
        }
    }
}
void VSDirectionLight::DrawCSM(VSCuller &CurCuller, double dAppTime)
{
    if (HaveLightFun())
    {
        return;
    }
#define DRAW_CSM_DEPTH                                                                                                          \
    {                                                                                                                           \
        m_pCSMRTArray[i] = VSResourceManager::GetRenderTarget(m_uiRTWidth, m_uiRTWidth, VSRenderer::SFT_R16F, 0);               \
        VSDepthStencil *pDepthStencil = VSResourceManager::GetDepthStencil(m_uiRTWidth, m_uiRTWidth, VSRenderer::SFT_D24S8, 0); \
        m_pShadowMapSceneRender->ClearRTAndDepth();                                                                             \
        m_pShadowMapSceneRender->SetDepthStencil(pDepthStencil, VSCuller::RG_NORMAL);                                           \
        m_pShadowMapSceneRender->AddRenderTarget(m_pCSMRTArray[i]);                                                             \
        m_pShadowMapSceneRender->Draw(m_ShadowCuller, dAppTime);                                                                \
        m_pShadowTexture[i]->SetTexture((VSTexture *)m_pCSMRTArray[i]->GetCreateBy());                                          \
        VSResourceManager::DisableOutputResource(pDepthStencil);                                                                \
    }

    VSCamera *pCamera = CurCuller.GetCamera();
    VSREAL fNear = pCamera->GetZNear();
    VSREAL fFar = pCamera->GetZFar();

    Math::Vector3 Dir, Up, Right;
    GetWorldDir(Dir, Up, Right);
    VSREAL Range[CSM_LEVLE + 1] = {fNear, 2000.0f, 7000.0f, fFar};
    for (unsigned int i = 0; i < CSM_LEVLE; i++)
    {
        pCamera->SetPerspectiveFov(pCamera->GetFov(), pCamera->GetAspect(), Range[i], Range[i + 1]);
        m_ShadowCuller.GetSceneContent(*pCamera, m_pScene, this, dAppTime);

        Container::MArray<Primitive::AABB3> CasterAABBArray;
        GetCullerAABBArray(m_ShadowCuller, CasterAABBArray);
        if (CasterAABBArray.GetNum() == 0)
        {
            DRAW_CSM_DEPTH;
            continue;
        }
        Primitive::AABB3 CasterAABB = GetMaxAABB(CasterAABBArray);
        Primitive::AABB3 ReceiverAABB = m_ShadowCuller.GetCamera()->GetFrustumAABB();

        VSMatrix3X3W LightRot;
        LightRot.CreateFromLookDir(Math::Vector3::ms_Zero, Dir);

        Primitive::AABB3 NewCasterAABB, NewReceiverAABB;
        NewCasterAABB.Transform(CasterAABB, LightRot);
        NewReceiverAABB.Transform(ReceiverAABB, LightRot);

        Primitive::AABB3 MinAABB = NewReceiverAABB.GetMin(NewCasterAABB);
        Math::Vector3 MinP(MinAABB.GetMinPoint().x, MinAABB.GetMinPoint().y, NewCasterAABB.GetMinPoint().z);
        Math::Vector3 MaxP(MinAABB.GetMaxPoint().x, MinAABB.GetMaxPoint().y, NewCasterAABB.GetMaxPoint().z);
        MinAABB.Set(MaxP, MinP);
        Math::Vector3 Center = MinAABB.GetCenter();

        VSRay3 Ray(Center, Math::Vector3::ms_Front * (-1.0f));

        unsigned int Q;
        VSREAL tN, tF;
        if (MinAABB.RelationWith(Ray, Q, tN, tF) != VSINTERSECT)
        {
            DRAW_CSM_DEPTH;
            continue;
        }

        Math::Vector3 LigthPT = Center - Math::Vector3::ms_Front * tN * 10.0f;

        Math::Vector3 NewLightPT = LigthPT * LightRot.GetInverse();

        VSCamera LightCamera;
        LightCamera.CreateFromLookDir(NewLightPT, Dir);

        MinAABB.Set(MinAABB.GetMaxPoint() - LigthPT, MinAABB.GetMinPoint() - LigthPT);

        LightCamera.SetOrthogonal(MinAABB.GetMaxPoint().x - MinAABB.GetMinPoint().x,
                                  MinAABB.GetMaxPoint().y - MinAABB.GetMinPoint().y,
                                  MinAABB.GetMinPoint().z, MinAABB.GetMaxPoint().z);

        m_LightShadowMatrix = LightCamera.GetViewMatrix() * LightCamera.GetProjMatrix();

        m_CSMLightShadowMatrix[i] = m_LightShadowMatrix;

        DRAW_CSM_DEPTH;
    }
    pCamera->SetPerspectiveFov(pCamera->GetFov(), pCamera->GetAspect(), fNear, fFar);
}
void VSDirectionLight::GetLightRange()
{

    Math::Vector3 Point3 = GetWorldTranslate();
    Math::Vector3 Dir, Up, Right;
    GetWorldDir(Dir, Up, Right);
    Math::Vector3 Middle = Point3 + Dir * (m_fLightFunFar + m_fLightFunNear) * 0.5;
    VSOBB3 OBB(Dir, Up, Right, (m_fLightFunFar - m_fLightFunNear) * 0.5f, m_fLightFunHeight * 0.5f, m_fLightFunWidth * 0.5f, Middle);
    m_WorldRenderBV = OBB.GetAABB();
    if (HaveLightFun())
    {
        VSCamera LightCamera;
        LightCamera.CreateFromLookDir(Point3, Dir);
        LightCamera.SetOrthogonal(m_fLightFunWidth, m_fLightFunHeight, m_fLightFunNear, m_fLightFunFar);
        LightCamera.UpdateAll(0);
        m_WVP = LightCamera.GetViewMatrix() * LightCamera.GetProjMatrix();
    }
}
bool VSDirectionLight::IsRelative(VSGeometry *pGeometry)
{
    if (!VSLight::IsRelative(pGeometry))
    {
        return false;
    }
    if (HaveLightFun())
    {
        Primitive::AABB3 GeometryAABB = pGeometry->GetWorldAABB();
        if (GeometryAABB.RelationWith(m_WorldRenderBV) == VSNOINTERSECT)
        {
            return false;
        }
    }
    return true;
}
void VSDirectionLight::DrawPorjectShadow(VSCuller &CurCuller, double dAppTime, VS2DTexture *pNormalDepthTexture)
{
    // not for dynamic instance , much instance have huge aabb box , shadow effect will be low.
    if (m_bEnable && m_bIsCastShadow && m_uiShadowType == ST_PROJECT)
    {
        Math::Vector3 Dir, Up, Right;
        GetWorldDir(Dir, Up, Right);
        m_ShadowCuller.GetSceneContent(*CurCuller.GetCamera(), m_pScene, this, dAppTime, false);

        Container::MArray<VSDirShadowMapCuller> Temp;
        VSMeshNode *pCurMeshNode = NULL;
        for (unsigned int t = 0; t <= VSCuller::VST_MAX; t++)
        {
            for (unsigned int j = 0; j < m_ShadowCuller.GetVisibleNum(t); j++)
            {
                VSRenderContext &RenderContext = m_ShadowCuller.GetVisibleSpatial(j, t);
                if (pCurMeshNode != RenderContext.m_pMeshNode || RenderContext.IsInstanceData())
                {
                    Temp.AddElement(VSDirShadowMapCuller());
                    Temp[Temp.GetNum() - 1].PushCameraPlane(*m_ShadowCuller.GetCamera());
                    pCurMeshNode = RenderContext.m_pMeshNode;
                }
                Temp[Temp.GetNum() - 1].InsertObject(RenderContext, t);
            }
        }
        m_pProjectShadowSceneRender->m_pNormalDepthTexture = pNormalDepthTexture;
        for (unsigned int i = 0; i < Temp.GetNum(); i++)
        {
            Container::MArray<Primitive::AABB3> CasterAABBArray;
            GetCullerAABBArray(Temp[i], CasterAABBArray);

            Primitive::AABB3 CasterAABB = GetMaxAABB(CasterAABBArray);
            Math::Vector3 Center = CasterAABB.GetCenter();

            VSRay3 Ray(Center, Dir * (-1.0f));

            unsigned int Q;
            VSREAL tN, tF;
            if (CasterAABB.RelationWith(Ray, Q, tN, tF) != VSINTERSECT)
            {
                continue;
            }

            Math::Vector3 LigthPT = Center - Dir * tN * 2.0f;

            VSCamera LightCamera;
            LightCamera.CreateFromLookAt(LigthPT, Center);

            LightCamera.UpdateAll(0);
            VSMatrix3X3W LightView = LightCamera.GetViewMatrix();

            Primitive::AABB3 NewCasterAABB;
            NewCasterAABB.Transform(CasterAABB, LightView);

            LightCamera.SetOrthogonal(NewCasterAABB.GetMaxPoint().x - NewCasterAABB.GetMinPoint().x,
                                      NewCasterAABB.GetMaxPoint().y - NewCasterAABB.GetMinPoint().y,
                                      NewCasterAABB.GetMinPoint().z, NewCasterAABB.GetMaxPoint().z + 10000.0f);

            m_LightShadowMatrix = LightCamera.GetViewMatrix() * LightCamera.GetProjMatrix();

            m_pProjectShadowRenderTarget = VSResourceManager::GetRenderTarget(m_uiRTWidth, m_uiRTWidth, VSRenderer::SFT_R16F, 0);
            VSDepthStencil *pDepthStencil = VSResourceManager::GetDepthStencil(m_uiRTWidth, m_uiRTWidth, VSRenderer::SFT_D24S8, 0);

            m_pShadowMapSceneRender->ClearRTAndDepth();
            m_pShadowMapSceneRender->SetDepthStencil(pDepthStencil, VSCuller::RG_NORMAL);
            m_pShadowMapSceneRender->AddRenderTarget(m_pProjectShadowRenderTarget);
            m_pShadowMapSceneRender->Draw(Temp[i], dAppTime);
            m_pShadowTexture[0]->SetTexture((VSTexture *)m_pProjectShadowRenderTarget->GetCreateBy());
            VSResourceManager::DisableOutputResource(pDepthStencil);

            m_pProjectShadowSceneRender->Draw(Temp[i], dAppTime);
            DisableDependenceShadowMap(Temp[i], dAppTime);
        }
    }
}
bool VSDirectionLight::SetLightMaterial(VSMaterialR *pMaterial)
{
    if (VSLocalLight::SetLightMaterial(pMaterial))
    {
        return true;
    }
    return false;
}
bool VSDirectionLight::Cullby(VSCuller &Culler)
{
    if (HaveLightFun())
    {
        unsigned int uiVSF = Culler.IsVisible(m_WorldRenderBV, true);
        if (uiVSF == VSCuller::VSF_ALL || uiVSF == VSCuller::VSF_PARTIAL)
        {
            m_bEnable = true;
            Culler.InsertLight(this);
        }
    }
    else
    {
        m_bEnable = true;
        Culler.InsertLight(this);
    }
    return true;
}