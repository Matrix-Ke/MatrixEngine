#pragma once
#include "Object.h"
#include "Vector3.h"
#include "Quat.h"

#include "Actor.h"
#include "SceneMap.h"
#include "CameraActor.h"
namespace Matrix
{
    class MStream;
    class VSLightActor;
    class MATRIX_FUNCTION_API VSWorld : public MObject
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;

    public:
        VSWorld();
        virtual ~VSWorld();

        DECLARE_INITIAL
        static VSWorld *ms_pWorld;

    protected:
        Container::MArray<VSSceneMapPtr> m_SceneArray;
        Container::MArray<VSActor *> m_ActorArray;
        Container::MArray<VSMessage> m_MessageArray;

    public:
        VSSceneMap *CreateScene(const TCHAR *pName);

        VSSceneMap *GetScene(const VSUsedName &Name);

        VSActor *CreateActor(const TCHAR *ActorPath, const Math::Vector3 &Pos = Math::Vector3::ms_Zero, const Math::Matrix3 &Rotate = Math::Matrix3::ms_Identity, const Math::Vector3 &Scale = Math::Vector3::ms_One, VSSceneMap *pSceneMap = NULL);
        void DestroyActor(VSActor *pActor);

        template <typename T>
        VSActor *CreateActor(const Math::Vector3 &Pos = Math::Vector3::ms_Zero, const Math::Matrix3 &Rotate = Math::Matrix3::ms_Identity, const Math::Vector3 &Scale = Math::Vector3::ms_One, VSSceneMap *pSceneMap = NULL);

        bool LoadMap(const TCHAR *MapPath, bool IsAsyn);
        bool UnLoadMap(const TCHAR *MapPath);
        void AttachCaptureViewFamilyToCamera(VSCameraActor *pCameraActor,
                                             unsigned int uiCaptureViewFamilyType, const VSString &ViewFamilyName,
                                             unsigned int uiWidth, unsigned int uiHeight,
                                             Container::MArray<VSString> &SceneMapName,
                                             const TCHAR *RenderMethodRTTIName,
                                             VSPostEffectSetR *pPostEffectSet = NULL);
        void AttachWindowViewFamilyToCamera(VSCameraActor *pCameraActor,
                                            unsigned int uiWindowViewFamilyType, const VSString &ViewFamilyName,
                                            Container::MArray<VSString> &SceneMapName,
                                            const TCHAR *RenderMethodRTTIName,
                                            int iWindowID = -1,
                                            VSPostEffectSetR *pPostEffectSet = NULL);
        VSActor *GetActor(VSUsedName Name);
        void Update(double dAppTime);
        void AddMessage(const VSMessage &Message);
        void UpdateLightActorScene(VSLightActor *pActor);
        void ProcessInput(unsigned int uiInputType, unsigned int uiEvent, unsigned int uiKey, int x, int y, int z);

    protected:
        friend class VSResourceManager;
        void AddActor(VSActor *pActor);
        void DeleteActor(VSActor *pActor);
        virtual void LoadedEvent(VSResourceProxyBase *pResourceProxy, void *Data = NULL);
        void DestroyScene(const VSUsedName &Name);
        void AddSceneMap(VSSceneMap *pSceneMap);
    };
    DECLARE_Ptr(VSWorld);
    VSTYPE_MARCO(VSWorld);
    template <typename T>
    VSActor *VSWorld::CreateActor(const Math::Vector3 &Pos, const Math::Matrix3 &Rotate, const Math::Vector3 &Scale, VSSceneMap *pSceneMap)
    {
        if (!T::ms_Type.IsDerived(VSActor::ms_Type))
            return NULL;
        VSActor *pActor = NULL;
        pActor = (VSActor *)MObject::GetInstance<T>();
        pActor->CreateDefaultComponentNode();
        pActor->SetWorldPos(Pos);
        pActor->SetWorldRotate(Rotate);
        pActor->SetWorldScale(Scale);
        if (pSceneMap)
        {
            pSceneMap->AddActor(pActor);
        }
        else
        {
            m_SceneArray[0]->AddActor(pActor);
        }
        AddActor(pActor);
        return pActor;
    }
}
