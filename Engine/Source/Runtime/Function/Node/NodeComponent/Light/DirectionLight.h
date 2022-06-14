#pragma once
#include "Node/NodeComponent/Light/Light.h"
#include "Render/Texture/CubeTexture.h"
#include "RenderTarget.h"
#include "DepthStencil.h"
#include "SceneRender.h"
namespace Matrix
{
    class MStream;
    class MATRIX_FUNCTION_API VSDirectionLight : public VSLocalLight
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        VSDirectionLight();
        virtual ~VSDirectionLight();

    public:
        virtual bool PostClone(MObject *pObjectSrc);
        virtual bool PostLoad(MStream *pStream);
        virtual unsigned int GetLightType() const { return LT_DIRECTION; }

        enum // ShadowType
        {
            ST_VOLUME,
            ST_OSM,
            ST_CSM,
            ST_PROJECT,
            ST_MAX
        };
        void SetShadowType(unsigned int uiShadowType);
        inline unsigned int GetShadowType() const
        {
            return m_uiShadowType;
        }
        virtual void DrawDependenceShadowMap(VSCuller &CurCuller, double dAppTime);
        virtual void DisableDependenceShadowMap(VSCuller &CurCuller, double dAppTime);
        virtual void DrawPorjectShadow(VSCuller &CurCuller, double dAppTime, VS2DTexture *pNormalDepthTexture);
        virtual void DrawVolumeShadow(VSCuller &CurCuller, double dAppTime);

        Math::Matrix4 m_CSMLightShadowMatrix[3];

    protected:
        unsigned int m_uiShadowType;

        VSProjectShadowSceneRenderPtr m_pProjectShadowSceneRender;
        VSShadowMapSceneRenderPtr m_pShadowMapSceneRender;
        VSPEVolumeShadowMapSceneRenderPtr m_pPEVolumeSMSceneRender;
        VSVolumeShadowSceneRenderPtr m_pVolumeShadowSceneRender;

        VSRenderTargetPtr m_pVolumeShadowRenderTarget;

#define m_pOSMShadowRenderTarget m_pVolumeShadowRenderTarget
#define m_pProjectShadowRenderTarget m_pVolumeShadowRenderTarget
        Container::MArray<VSRenderTargetPtr> m_pCSMRTArray;

        void DrawOSM(VSCuller &CurCuller, double dAppTime);
        void DrawCSM(VSCuller &CurCuller, double dAppTime);

        Primitive::AABB3 GetMaxAABB(Container::MArray<Primitive::AABB3> &AABBArray);

        void ResetShadow();

        VSREAL m_fLightFunWidth;
        VSREAL m_fLightFunHeight;
        VSREAL m_fLightFunFar;
        VSREAL m_fLightFunNear;
        VSREAL m_fOSMDistance;
        virtual void GetLightRange();
        Primitive::AABB3 m_WorldRenderBV;
        VSDirShadowMapCuller m_ShadowCuller;
        VSVolumeShadowMapCuller m_VolumeShadowCuller;

    public:
        inline void SetLightFuncParam(VSREAL fLightFunWidth,
                                      VSREAL fLightFunHeight,
                                      VSREAL fLightFunFar,
                                      VSREAL fLightFunNear = 1.0f)
        {
            m_fLightFunWidth = fLightFunWidth;
            m_fLightFunHeight = fLightFunHeight;
            m_fLightFunFar = fLightFunFar;
            m_fLightFunNear = fLightFunNear;
            GetLightRange();
        }
        virtual bool SetLightMaterial(VSMaterialR *pMaterial);
        virtual bool Cullby(VSCuller &Culler);
        virtual bool IsRelative(VSGeometry *pGeometry);
    };
    DECLARE_Ptr(VSDirectionLight);
    VSTYPE_MARCO(VSDirectionLight);

}
