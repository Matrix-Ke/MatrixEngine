#pragma once
#include "Node.h"
namespace Matrix
{
    class MStream;
    class MATRIX_FUNCTION_API VSBoneNode : public VSNode
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        VSBoneNode();
        virtual ~VSBoneNode();

    public:
        virtual void ComputeNodeVisibleSet(VSCuller &Culler, bool bNoCull, double dAppTime);

        // Use for IK
        bool m_bIsEffector;
        Math::Vector3 m_TargetPosInWorld;

        Container::MArray<bool> m_bAllowTranslation;
        Container::MArray<VSREAL> m_fMinTranslation;
        Container::MArray<VSREAL> m_fMaxTranslation;

        Container::MArray<bool> m_bAllowRotation;
        Container::MArray<VSREAL> m_fMinRotation;
        Container::MArray<VSREAL> m_fMaxRotation;

        VSREAL m_fIKWeight;

        VSUsedName m_cName;

        void GetIKMoveAxis(Math::Vector3 Axis[3]) const;
        void ComputeIKLocalRotDelta(const Math::Matrix3 &WorldRot, Math::Matrix3 &LocalRotDelta) const;

        VSMatrix3X3W m_OffsetMatrix;

        virtual void SetLocalMat(const VSMatrix3X3W VSMat);

    public:
        inline const VSMatrix3X3W &GetBoneOffsetMatrix() const
        {
            return m_OffsetMatrix;
        }

        VSBoneNode *GetBoneNodeFromLevel(const VSUsedName &BoneName);
        unsigned int GetAllBoneNum() const;
        void GetAllBoneArray(Container::MArray<VSBoneNode *> &AllNodeArray);
    };
    DECLARE_Ptr(VSBoneNode);
    VSTYPE_MARCO(VSBoneNode);
}
