#pragma once
#include "TwoParamAnimBlend.h"
#include "AnimSequenceFunc.h"
namespace Matrix
{
    /*

        ParaMin[0]			width					ParaMax[0]

        j0				j1				j3				j4
    i0	-------------------------------------------------	ParaMin[1]
        |				|				|				|
        |				|				|				|
        |				|				|				|
        |				|				|				|
        |				|				|				|
    i1	-------------------------------------------------	 height
        |				|				|				|
        |				|				|				|
        |				|				|				|
        |				|				|				|
        |				|				|				|
    i2	-------------------------------------------------	ParaMax[1]


    */
    class MStream;
    class MATRIX_FUNCTION_API VSTwoParamAnimBlendSequence : public VSTwoParamAnimBlend
    {
        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL

    public:
        virtual ~VSTwoParamAnimBlendSequence();

        VSTwoParamAnimBlendSequence(const VSUsedName &ShowName, VSAnimTree *pAnimTree);

    public:
        VSTwoParamAnimBlendSequence();
        virtual bool ComputeOutBoneMatrix(double dAppTime);
        void CreateSlot(unsigned int uiWidth, unsigned int uiHeight);
        void SetAnim(unsigned int i, unsigned int j, const VSUsedName &AnimName);

        void SetAnimFrequency(unsigned int i, unsigned int j, double Frequency);
        void SetAnimPhase(unsigned int i, unsigned int j, double Phase);
        virtual bool IsLeafNode() { return true; }
        virtual bool SetObject(MObject *pObject);
        virtual void SetOnlyUpdateRootMotion(bool bOnlyUpdateRootMotion)
        {
            for (unsigned int i = 0; i < m_AnimSequenceFuncArray.GetNum(); i++)
            {
                if (m_AnimSequenceFuncArray[i])
                {
                    m_AnimSequenceFuncArray[i]->SetOnlyUpdateRootMotion(bOnlyUpdateRootMotion);
                }
            }
        }
        virtual bool IsSupportSimpleInstance()
        {
            for (unsigned int i = 0; i < m_AnimSequenceFuncArray.GetNum(); i++)
            {
                if (m_AnimSequenceFuncArray[i])
                {
                    if (!m_AnimSequenceFuncArray[i]->IsSupportSimpleInstance())
                    {
                        return false;
                    }
                }
            }

            return true;
        }

    protected:
        Container::MArray<VSAnimSequenceFuncPtr> m_AnimSequenceFuncArray;

        VSAnimSequenceFunc *GetAnimSequenceFunction(unsigned int i, unsigned int j);
    };
    DECLARE_Ptr(VSTwoParamAnimBlendSequence);
    VSTYPE_MARCO(VSTwoParamAnimBlendSequence);
}
