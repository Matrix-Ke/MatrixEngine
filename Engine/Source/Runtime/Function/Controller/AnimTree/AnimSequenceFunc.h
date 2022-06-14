// #pragma once
// #include "Controller/AnimTree/AnimFunction.h"
// namespace Matrix
// {
//     class MStream;

//     class MATRIX_FUNCTION_API VSAnimSequenceFunc : public VSAnimFunction
//     {
//         // RTTI
//         DECLARE_RTTI;
//         DECLARE_INITIAL

//     public:
//         virtual ~VSAnimSequenceFunc();
//         virtual bool Update(double dAppTime);
//         friend class VSSkeletonMeshNode;
//         friend class VSOneParamSmoothAnimBlendSequence;
//         friend class VSTwoParamAnimBlendSequence;
//         VSAnimSequenceFunc(const VSUsedName &ShowName, VSAnimTree *pAnimTree);
//         virtual bool IsSupportSimpleInstance();
//         void SetAnim(const VSUsedName &AnimName);
//         virtual bool SetObject(MObject *pObject);
//         inline const VSAnimR *GetAnim() const
//         {
//             return m_pAnimR;
//         }
//         inline const VSUsedName &GetAnimName() const
//         {
//             return m_AnimName;
//         }
//         VSREAL GetAnimTime();
//         bool m_bOnlyAddtiveOutput;
//         virtual bool IsLeafNode() { return true; }

//     protected:
//         VSAnimSequenceFunc();

//     protected:
//         VSAnimRPtr m_pAnimR;
//         Container::MArray<unsigned int> m_UsedBoneIndexInAnim;
//         VSUsedName m_AnimName;
//         struct LAST_KEY_TYPE
//         {
//         public:
//             LAST_KEY_TYPE()
//             {
//                 Reset();
//             }
//             ~LAST_KEY_TYPE()
//             {
//             }
//             unsigned int uiLKTranslation;
//             unsigned int uiLKScale;
//             unsigned int uiLKRotator;
//             void Reset()
//             {
//                 uiLKTranslation = 0;
//                 uiLKScale = 0;
//                 uiLKRotator = 0;
//             }
//         };
//         Container::MArray<LAST_KEY_TYPE> m_LastKey;
//         Container::MArray<LAST_KEY_TYPE> m_AdditiveLastKey;
//         // used only in SkeletonMeshNode
//         void UpdateBone();
//         void LoadedEvent(VSResourceProxyBase *pResourceProxy, void *Data = NULL);

//         void ComputeAnim(VSAnim *pAnim, Container::MArray<LAST_KEY_TYPE> &LastKey, Container::MArray<VSAnimAtom> &BoneOutput);
//         Container::MArray<VSAnimAtom> m_AdditiveBoneOutput;
//         VSAnimAtom m_RootStartAtom;
//         VSAnimAtom m_LastRootAtom;
//         void GetRootStartAtom(VSAnimAtom &OutAtom, VSAnim *pAnim);

//         unsigned int m_uiIndexInAnimSet;
//     };
//     DECLARE_Ptr(VSAnimSequenceFunc);
//     VSTYPE_MARCO(VSAnimSequenceFunc);

// }
