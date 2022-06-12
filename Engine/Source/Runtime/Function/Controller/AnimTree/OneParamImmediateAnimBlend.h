#pragma once
#include "OneParamAnimBlend.h"
namespace Matrix
{
    /*
    CrossFading IMMEDIATE|______|______|  [0,1) �Ƕ���0 [1,2) �Ƕ���1 ���Դ�����
    0		1		2


    */
    class VSStream;
    class MATRIX_FUNCTION_API VSOneParamImmediateAnimBlend : public VSOneParamAnimBlend
    {
        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL

    public:
        virtual ~VSOneParamImmediateAnimBlend();

        VSOneParamImmediateAnimBlend(const VSUsedName &ShowName, VSAnimTree *pAnimTree);
        virtual void AddInputNode();
        virtual void DeleteInputNode();

    public:
        VSOneParamImmediateAnimBlend();
        virtual bool Update(double dAppTime);
        virtual bool ComputeOutBoneMatrix(double dAppTime);

    protected:
        VSArray<VSREAL> m_NodeCrossFadingTime;
        VSREAL m_fCrossFadingTime;
        unsigned int m_uiLastAnimIndex;
        unsigned int m_uiCurAnimIndex;

    public:
        inline void SetNodeCrossFadingTime(unsigned int uiIndex, VSREAL fTime)
        {
            if (uiIndex >= m_pInput.GetNum())
            {
                return;
            }
            m_NodeCrossFadingTime[uiIndex] = fTime;
        }
    };
    DECLARE_Ptr(VSOneParamImmediateAnimBlend);
    VSTYPE_MARCO(VSOneParamImmediateAnimBlend);
}