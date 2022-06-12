#pragma once
#include "Node.h"
namespace Matrix
{
    class VSStream;
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
        VSVector3 m_TargetPosInWorld;

        VSArray<bool> m_bAllowTranslation;
        VSArray<VSREAL> m_fMinTranslation;
        VSArray<VSREAL> m_fMaxTranslation;

        VSArray<bool> m_bAllowRotation;
        VSArray<VSREAL> m_fMinRotation;
        VSArray<VSREAL> m_fMaxRotation;

        VSREAL m_fIKWeight;

        VSUsedName m_cName;

        void GetIKMoveAxis(VSVector3 Axis[3]) const;
        void ComputeIKLocalRotDelta(const VSMatrix3X3 &WorldRot, VSMatrix3X3 &LocalRotDelta) const;

        VSMatrix3X3W m_OffsetMatrix;

        virtual void SetLocalMat(const VSMatrix3X3W VSMat);

    public:
        inline const VSMatrix3X3W &GetBoneOffsetMatrix() const
        {
            return m_OffsetMatrix;
        }

        VSBoneNode *GetBoneNodeFromLevel(const VSUsedName &BoneName);
        unsigned int GetAllBoneNum() const;
        void GetAllBoneArray(VSArray<VSBoneNode *> &AllNodeArray);
    };
    DECLARE_Ptr(VSBoneNode);
    VSTYPE_MARCO(VSBoneNode);
}