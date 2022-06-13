#pragma once
#include "MeshComponent.h"
namespace Matrix
{
    DECLARE_Proxy(VSSkeletonMeshNode);
    DECLARE_Ptr(VSSkeletonMeshNode);
    class VSAnimAtom;
    class MATRIX_FUNCTION_API VSSkeletonMeshComponent : public VSMeshComponent
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        VSSkeletonMeshComponent();
        virtual ~VSSkeletonMeshComponent();
        void SetSkeletonMeshResource(VSSkeletonMeshNodeR *pSkeletonMeshResource);
        VSSkeletonMeshNode *GetSkeletonMeshNode();
        virtual void LoadedEvent(VSResourceProxyBase *pResourceProxy, void *Data = NULL);
        virtual void PostCreate();
        void SetIsDrawSkeleton(bool bIsDrawSkeleton);

        virtual bool BeforeSave(void *pData = NULL);
        bool PlayAnim(const Container::MString &AnimName, VSREAL fRatio = 1.0f, unsigned int uiRepeatType = VSController::RT_NONE);
        VSSocketNode *GetSocketNode(const VSUsedName &SocketName);
        void SetAnimTreeNodePara(const VSUsedName &ShowName, void *pPara);
        virtual bool PostLoad(MStream *pStream);
        const VSAnimAtom &GetRootDelta();

    protected:
        VSSkeletonMeshNodeRPtr m_pSkeletonMeshResource;
    };
    DECLARE_Ptr(VSSkeletonMeshComponent);
    VSTYPE_MARCO(VSSkeletonMeshComponent);
}
