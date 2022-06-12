#pragma once
#include "AnimBlendFunction.h"
namespace Matrix
{
    class MStream;
    class MATRIX_FUNCTION_API VSTwoParamAnimBlend : public VSAnimBlendFunction
    {
        // RTTI
        DECLARE_RTTI
        DECLARE_INITIAL
    public:
        virtual ~VSTwoParamAnimBlend();

        VSTwoParamAnimBlend(const VSUsedName &ShowName, VSAnimTree *pAnimTree);
        void CreateSlot(unsigned int uiWidth, unsigned int uiHeight);
        virtual bool SetObject(MObject *pObject);
        static void LineBlendTwoAll(VSTwoParamAnimBlend *pOut,
                                    VSAnimFunction *pAnimFunction1, VSAnimFunction *pAnimFunction2,
                                    VSAnimFunction *pAnimFunction3, VSAnimFunction *pAnimFunction4,
                                    VSREAL fWeight1, VSREAL fWeight2);

    protected:
        VSREAL m_fParam[2];
        VSREAL m_fParamMax[2];
        VSREAL m_fParamMin[2];
        Container::MArray<VSAnimAtom> m_BlendBoneMatrix[2];
        VSAnimAtom m_BlendRootMatrix[2];
        unsigned int m_uiWidth;
        unsigned int m_uiHeight;

        VSTwoParamAnimBlend();
        virtual bool ComputePara(double dAppTime);
        virtual bool ComputeOutBoneMatrix(double dAppTime);
        VSAnimFunction *GetAnimFunction(unsigned int i, unsigned int j);

    private:
        static void LineBlendTwo(Container::MArray<VSAnimAtom> *pOut,
                                 const Container::MArray<VSAnimAtom> *pIn1, const Container::MArray<VSAnimAtom> *pIn2, VSREAL fWeight);
        static void LineBlendTwo(Container::MArray<VSAnimAtom> *pOut,
                                 VSAnimFunction *pAnimFunction1, VSAnimFunction *pAnimFunction2, VSREAL fWeight);
        static bool LineBlendTwoRoot(VSAnimAtom &pOut,
                                     VSAnimFunction *pAnimFunction1, VSAnimFunction *pAnimFunction2, VSREAL fWeight);
    };
    DECLARE_Ptr(VSTwoParamAnimBlend);
    VSTYPE_MARCO(VSTwoParamAnimBlend);
}
