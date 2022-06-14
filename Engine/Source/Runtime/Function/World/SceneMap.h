#pragma once
#include "Render/SceneManager/Scene.h"
#include "World/Actor/Actor.h"
namespace Matrix
{
    class MATRIX_FUNCTION_API VSSceneMap : public MObject, public VSResource
    {
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        VSSceneMap(const TCHAR *pName);
        VSSceneMap();
        virtual ~VSSceneMap();
        void AddActor(VSActor *pActor);
        VSActor *GetActor(VSUsedName Name);
        void DeleteActor(VSActor *pActor);
        VSUsedName m_Name;
        friend class VSViewFamliyInfo;
        friend class VSWorld;
        friend class VSReflectCubLightActor;
        virtual bool PostLoad(MStream *pStream);
        VSScene *GetScene()
        {
            return m_pScene;
        }
        virtual void OnDestroy();
        static bool InitialDefaultState();
        static bool TerminalDefaultState();
        DECLARE_RESOURCE(VSSceneMap, RA_ASYN_LOAD, RT_MAP, MAP, Resource / Map, VSCacheResource)
    protected:
        VSScenePtr m_pScene;
        Container::MArray<VSActorPtr> m_pActorArray;
    };
    DECLARE_Ptr(VSSceneMap);
    VSTYPE_MARCO(VSSceneMap);
    DECLARE_Proxy(VSSceneMap);
}
