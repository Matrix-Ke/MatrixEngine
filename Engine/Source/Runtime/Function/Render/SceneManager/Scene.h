#pragma once
#include "Node.h"
namespace Matrix
{
    class VSRenderer;
    class MStream;
    class VSQuadNode : public VSNode
    {
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        VSQuadNode();
        ~VSQuadNode();
        virtual void ComputeNodeVisibleSet(VSCuller &Culler, bool bNoCull, double dAppTime);
        bool RecursiveBuild(const Container::MArray<VSSpatial *> &pObjectArray);
        virtual unsigned int AddChild(VSSpatial *pChild);
        virtual unsigned int DeleteChild(VSSpatial *pChild);
        virtual bool DeleteChild(unsigned int i);
        virtual void DeleteAllChild();
        VSNodeComponent *GetNeedDrawNode(unsigned int uiIndex) const;
        unsigned int GetNeedDrawNodeNum() const;

    protected:
        void DeleteNeedDrawNode(VSNodeComponent *pNeedDrawNode);
        void AddNeedDrawNode(VSNodeComponent *pNeedDrawNode);
        Container::MArray<VSNodeComponent *> m_pNeedDrawNode;
    };
    DECLARE_Ptr(VSQuadNode);
    VSTYPE_MARCO(VSQuadNode);

    class MATRIX_FUNCTION_API VSScene : public MObject
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        friend class VSSceneManager;
        void Update(double dAppTime);
        void CollectUpdateInfo();
        VSScene();
        ~VSScene();

        inline VSLight *GetAllLight(unsigned int i) const;
        inline unsigned int GetAllLightNum() const;

        virtual void AddObject(VSNode *pObject);
        virtual void DeleteObject(VSNode *pObject);
        virtual void DeleteAllObject();

        virtual void ComputeVisibleSet(VSCuller &Culler, bool bNoCull, double dAppTime);
        bool Build();
        inline bool IsBuild()
        {
            return m_bIsBuild;
        }
        void GetStreamResource(const Math::Vector3 &CameraPos, const Math::Vector4 &ProjectInfo);

    protected:
        Container::MArray<VSLight *> m_pAllLight;
        Container::MArray<VSCamera *> m_pAllCamera;

        Container::MArray<VSNode *> m_pDynamic;
        VSQuadNodePtr m_pStaticRoot;
        Container::MArray<VSNode *> m_ObjectNodes;
        bool m_bIsBuild;
    };
    DECLARE_Ptr(VSScene);
    VSTYPE_MARCO(VSScene);
}