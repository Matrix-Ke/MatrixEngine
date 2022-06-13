#pragma once
#include "AnimBlendFunction.h"
namespace Matrix
{
    /*
    CrossFading IMMEDIATE |______|______|  [0,1) 是动画0 [1,2) 是动画1 ，以此类推
    0		1		2


    */
    class MStream;
    class MATRIX_FUNCTION_API VSPartialAnimBlend : public VSAnimBlendFunction
    {
        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL

    public:
        virtual ~VSPartialAnimBlend();

        VSPartialAnimBlend(const VSUsedName &ShowName, VSAnimTree *pAnimTree);

        virtual void AddInputNode();

        virtual void DeleteInputNode();

        virtual void SetBoneWeight(unsigned int i, const VSUsedName &BoneName, VSREAL Weight);

        virtual bool ComputePara(double dAppTime);
        void AddControllBone(const VSUsedName &BoneName);

    protected:
#if (FAST_BLEND_PARIAL_ANIMITION == 0)
        Container::MArray<VSMatrix3X3W> m_FastTempMatrix;
        VSMatrix3X3W m_FastRootMatrix;
#endif
        Container::MArray<Container::MArray<VSREAL>> m_Weight;
        Container::MMap<VSUsedName, Container::MArray<VSREAL>> m_BoneWeight;
        void ComputeWeight();
        virtual bool IsSupportSimpleInstance() { return false; }

    public:
        VSPartialAnimBlend();
        virtual bool ComputeOutBoneMatrix(double dAppTime);
        virtual bool SetObject(MObject *pObject);
    };
    DECLARE_Ptr(VSPartialAnimBlend);
    VSTYPE_MARCO(VSPartialAnimBlend);
}
