#pragma once
#include "Controller.h"
#include "AnimSet.h"
namespace Matrix
{
    class VSAnimFunction;
    class VSAnimMainFunction;
    class VSAnimBaseFunction;
    class VSSkeletonMeshNode;
    class MStream;
    class VSAnimAtom;
    class MATRIX_FUNCTION_API VSAnimTree : public VSController, public VSResource
    {
        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL

    public:
        virtual ~VSAnimTree();
        virtual bool Update(double dAppTime);

        VSAnimTree(const VSUsedName &ShowName);

    protected:
        VSAnimTree();

    protected:
        Container::MArray<VSAnimBaseFunction *> m_pAnimFunctionArray;

        VSAnimMainFunction *m_pAnimMainFunction;
        VSUsedName m_ShowName;

    public:
        inline const VSUsedName &GetShowName() const
        {
            return m_ShowName;
        }
        VSSkeletonMeshNode *GetSkeletonMeshNode() const;

        void AddAnimFunction(VSAnimBaseFunction *pAnimFunction);
        void DeleteAnimFunction(VSAnimBaseFunction *pAnimFunction);
        inline VSAnimMainFunction *GetAnimMainFunction() const
        {
            return m_pAnimMainFunction;
        }
        virtual bool SetObject(MObject *pObject);
        void ResetAnimFunction();

        VSAnimBaseFunction *GetAnimFunctionFromShowName(const VSUsedName &ShowName);
        void SetNodePara(const VSUsedName &ShowName, void *pPara);
        DECLARE_RESOURCE(VSAnimTree, RA_ASYN_LOAD | RA_ASYN_POSTLOAD | RA_ENABLE_GC, RT_ANIMTREE, ANIMTREE, Resource / Anim, VSCacheResource)
        const VSAnimAtom &GetRootDelta();
        void SetOnlyUpdateRootMotion(bool bOnlyUpdateRootMotion);

        void GetAnimInstanceData(Container::MArray<ANIM_INSTANCE_DATA> &InstanceData);
        bool IsSupportSimpleInstance();
        bool HasRootMotion();
    };
    DECLARE_Ptr(VSAnimTree);
    VSTYPE_MARCO(VSAnimTree);
    DECLARE_Proxy(VSAnimTree);
    class MATRIX_FUNCTION_API VSAnimTreeOneAnim : public VSAnimTree
    {
    public:
        DECLARE_RTTI;
        DECLARE_INITIAL
        VSAnimTreeOneAnim();
        VSAnimTreeOneAnim(const VSUsedName &ShowName, const Container::MString &AnimName);
        ~VSAnimTreeOneAnim();
    };
    DECLARE_Ptr(VSAnimTreeOneAnim);
    VSTYPE_MARCO(VSAnimTreeOneAnim);

    class MATRIX_FUNCTION_API VSAnimTreeTwoSmoothBlendAnim : public VSAnimTree
    {
    public:
        DECLARE_RTTI;
        DECLARE_INITIAL
        VSAnimTreeTwoSmoothBlendAnim();
        VSAnimTreeTwoSmoothBlendAnim(const VSUsedName &ShowName, const Container::MString &AnimName1, const Container::MString &AnimName2);
        ~VSAnimTreeTwoSmoothBlendAnim();
    };
    DECLARE_Ptr(VSAnimTreeTwoSmoothBlendAnim);
    VSTYPE_MARCO(VSAnimTreeTwoSmoothBlendAnim);

    class MATRIX_FUNCTION_API VSAnimTreeTwoImmediateAnim : public VSAnimTree
    {
    public:
        DECLARE_RTTI;
        DECLARE_INITIAL
        VSAnimTreeTwoImmediateAnim();
        VSAnimTreeTwoImmediateAnim(const VSUsedName &ShowName, const Container::MString &AnimName1, const Container::MString &AnimName2);
        ~VSAnimTreeTwoImmediateAnim();
    };
    DECLARE_Ptr(VSAnimTreeTwoImmediateAnim);
    VSTYPE_MARCO(VSAnimTreeTwoImmediateAnim);

    class MATRIX_FUNCTION_API VSAnimTreePartialAnim : public VSAnimTree
    {
    public:
        DECLARE_RTTI;
        DECLARE_INITIAL
        VSAnimTreePartialAnim();
        VSAnimTreePartialAnim(const VSUsedName &ShowName, const Container::MString &AnimName1, const Container::MString &AnimName2);
        ~VSAnimTreePartialAnim();
    };
    DECLARE_Ptr(VSAnimTreePartialAnim);
    VSTYPE_MARCO(VSAnimTreePartialAnim);

    class MATRIX_FUNCTION_API VSAnimTreeRectBlendAnim : public VSAnimTree
    {
    public:
        DECLARE_RTTI;
        DECLARE_INITIAL
        VSAnimTreeRectBlendAnim();
        VSAnimTreeRectBlendAnim(const VSUsedName &ShowName,
                                const Container::MString &AnimName1,
                                const Container::MString &AnimName2,
                                const Container::MString &AnimName3,
                                const Container::MString &AnimName4);
        ~VSAnimTreeRectBlendAnim();
    };
    DECLARE_Ptr(VSAnimTreeRectBlendAnim);
    VSTYPE_MARCO(VSAnimTreeRectBlendAnim);

}
