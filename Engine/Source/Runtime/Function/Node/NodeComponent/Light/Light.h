#pragma once
#include "NodeComponent.h"
#include "Vector3.h"
#include "Vector3W.h"
#include "Resource.h"
#include "Vector2.h"
#include "Culler.h"
namespace Matrix
{
    class VSShadowMapSceneRender;
    class MStream;
    class VS2DTexture;
    class VSCamera;
    DECLARE_Ptr(VSTexAllState);
    DECLARE_Ptr(VSMaterialInstance);
    DECLARE_Ptr(VSMaterial);
    DECLARE_Ptr(VSRenderTarget);
    class MATRIX_FUNCTION_API VSLight : public VSNodeComponent
    {
        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL_NO_CLASS_FACTORY
    public:
        friend class VSSpatial;
        friend class VSScene;
        enum // LightType
        {
            LT_POINT,
            LT_SPOT,
            LT_DIRECTION,
            LT_SKY,
            LT_MAX
        };
        VSLight();
        virtual ~VSLight() = 0;

    public:
        virtual void UpdateAll(double dAppTime);
        virtual unsigned int GetLightType() const = 0;
        virtual bool IsRelative(VSGeometry *pGeometry);
        virtual bool Cullby(VSCuller &Culler);
        virtual void UpdateLightState(double dAppTime);
        virtual void GetLightRange() = 0;
        virtual void UpdateTransform(double dAppTime);
        virtual void BuildSceneInfo(VSScene *pScene);
    };
    DECLARE_Ptr(VSLight);
    VSTYPE_MARCO(VSLight);

    DECLARE_Ptr(VSLightMaterialSceneRender);
    class MATRIX_FUNCTION_API VSLocalLight : public VSLight
    {
        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL_NO_CLASS_FACTORY
    public:
        VSLocalLight();
        virtual ~VSLocalLight() = 0;
        VSColorRGBA m_Diffuse;
        VSColorRGBA m_Specular;
        virtual void DrawNoDependenceShadowMap(VSCuller &CurCuller, double dAppTime);
        virtual void DisableNoDependenceShadowMap(double dAppTime);
        virtual void DrawDependenceShadowMap(VSCuller &CurCuller, double dAppTime);
        virtual void DisableDependenceShadowMap(VSCuller &CurCuller, double dAppTime);
        virtual void DrawPorjectShadow(VSCuller &CurCuller, double dAppTime, VS2DTexture *pNormalDepthTexture);
        virtual void DrawVolumeShadow(VSCuller &CurCuller, double dAppTime);
        virtual void UpdateAll(double dAppTime);
        virtual void DrawLightMaterial(double dAppTime);
        void SetCastShadow(bool bIsCastShadow);
        inline bool GetCastShadow()
        {
            return m_bIsCastShadow;
        }
        inline void AddShadowScene(VSScene *pSecen)
        {
            if (pSecen)
            {
                for (unsigned int i = 0; i < m_pScene.GetNum(); i++)
                {
                    if (m_pScene[i] == pSecen)
                    {
                        return;
                    }
                }
                m_pScene.AddElement(pSecen);
            }
        }

        inline void ClearAllShadowScene()
        {
            m_pScene.Clear();
        }
        virtual VSTexAllState *GetShadowTexture(unsigned int ID = 0)
        {
            return m_pShadowTexture[ID];
        }
        unsigned int GetShadowTextureNum()
        {
            return m_pShadowTexture.GetNum();
        }
        unsigned int GetShadowResolution() const
        {
            return m_uiRTWidth;
        }
        inline VSTexAllState *GetLightFunDiffuseTexture() const
        {
            return m_pLightFunDiffuseTexture;
        }
        virtual bool SetLightMaterial(VSMaterialR *pMaterial);
        VSREAL m_ZBias;
        VSMatrix3X3W m_LightShadowMatrix;
        void SetLightMaterialRtWidth(unsigned int uiRtWidth);

        inline VSMaterialInstance *GetMaterialInstance() const
        {
            return m_pLightMaterial;
        }
        inline bool HaveLightFun() const
        {
            return (m_pLightMaterial != NULL);
        }
        unsigned int GetLightMaterialRtWidth()
        {
            return m_uiLightMaterialRTWidth;
        }
        inline VSMatrix3X3W &GetWVP()
        {
            return m_WVP;
        }
        virtual void BuildSceneInfo(VSScene *pScene);
        VSVector2 m_LightFunScale;
        VSVector2 m_LightFunOffset;
        VSColorRGBA m_ProjectShadowColor;
        VSREAL m_ProjectShadowFallOff;

    protected:
        bool m_bIsCastShadow;
        unsigned int m_uiRTWidth;
        Container::MArray<VSScene *> m_pScene;
        Container::MArray<VSTexAllStatePtr> m_pShadowTexture;
        VSTexAllStatePtr m_pLightFunDiffuseTexture;
        VSMaterialInstancePtr m_pLightMaterial;
        unsigned int m_uiLightMaterialRTWidth;
        VSLightMaterialSceneRenderPtr m_pLMSceneRender;
        VSRenderTargetPtr m_pLightFunDiffuseRenderTarget;
        VSRenderTargetPtr m_pLightFunSpecularRenderTarget;
        VSMatrix3X3W m_WVP;
        virtual void GetLightRange() = 0;
        void GetCullerAABBArray(VSCuller &Culler, Container::MArray<Primitive::AABB3> &AABBArray);
        bool m_bShadowMapDrawEnd;
    };
    DECLARE_Ptr(VSLocalLight);
    VSTYPE_MARCO(VSLocalLight);
    class MATRIX_FUNCTION_API VSIndirectLight : public VSLight
    {
        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL_NO_CLASS_FACTORY
    public:
        VSIndirectLight();
        virtual ~VSIndirectLight() = 0;
        virtual bool IsRelative(VSGeometry *pGeometry);
        virtual bool Cullby(VSCuller &Culler);
        virtual void SetLocalScale(const Math::Vector3 &fScale);
        virtual void SetLocalRotate(const Math::Matrix3 &Rotate);
        virtual void SetLocalTransform(const Math::VSTransform &LocalTransform);
        virtual void SetLocalMat(const VSMatrix3X3W VSMat);
        inline void SetRange(Math::Vector3 &Range)
        {
            m_Range.x = Range.x > 1.0f ? Range.x : m_Range.x;
            m_Range.y = Range.y > 1.0f ? Range.y : m_Range.y;
            m_Range.z = Range.z > 1.0f ? Range.z : m_Range.z;
            GetLightRange();
        }

    protected:
        Math::Vector3 m_Range;
        virtual void GetLightRange();
        Primitive::AABB3 m_WorldRenderBV;
    };
    DECLARE_Ptr(VSIndirectLight);
    VSTYPE_MARCO(VSIndirectLight);
}
