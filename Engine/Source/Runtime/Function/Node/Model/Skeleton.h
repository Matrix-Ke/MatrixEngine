#pragma once
#include "Node.h"
#include "Geometry.h"
namespace Matrix
{
    DECLARE_Ptr(VSBoneNode);
    class MStream;
    class MATRIX_FUNCTION_API VSSkeleton : public VSNode
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        VSSkeleton();
        virtual ~VSSkeleton();

    protected:
        Container::MArray<VSBoneNode *> m_pBoneArray;

        void LinkBoneArray();
        virtual void UpdateNoChild(double dAppTime);
        virtual void ComputeNodeVisibleSet(VSCuller &Culler, bool bNoCull, double dAppTime);
        virtual void UpdateWorldBound(double dAppTime);
        static VSREAL ms_fBoneAxisLength;
        void Draw(VSCamera *pCamera);
        Primitive::AABB3 m_LocalBV;
        Primitive::AABB3 m_OriginLocalBV;

    public:
        friend class VSSkeletonMeshNode;
        virtual void CreateLocalAABB();
        inline void SetLocalBV(const Primitive::AABB3 &BV)
        {
            m_LocalBV = BV;
        }
        inline Primitive::AABB3 GetLocalBV() const
        {
            return m_LocalBV;
        }
        void CreateBoneArray();

        unsigned int GetBoneNum() const;
        VSBoneNode *GetBoneNode(const VSUsedName &Name) const;
        VSBoneNode *GetBoneNode(unsigned int i) const;

        int GetBoneIndex(const VSUsedName &Name) const;
        bool m_bIsDrawSkeleton;

        virtual void UpdateView(VSCuller &Culler, double dAppTime);
        const Math::VSTransform &GetRootTransform();
    };
    DECLARE_Ptr(VSSkeleton);
    VSTYPE_MARCO(VSSkeleton);
}
