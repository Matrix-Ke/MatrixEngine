#pragma once
#include "Object.h"
#include "Vector3.h"
#include "Quat.h"
#include "Matrix3X3W.h"
#include "Name.h"
#include "Controller.h"
#include "Resource.h"
namespace Matrix
{
    class MStream;
    class MATRIX_FUNCTION_API VSKeyTimeInfo
    {
    public:
        VSKeyTimeInfo(){};
        ~VSKeyTimeInfo(){};
        VSREAL m_dKeyTime;
    };
    class MATRIX_FUNCTION_API VSKeyTimeVector : public VSKeyTimeInfo
    {
    public:
        VSKeyTimeVector(){};
        ~VSKeyTimeVector(){};
        Math::Vector3 m_Vector;
    };
    class MATRIX_FUNCTION_API VSKeyTimeReal : public VSKeyTimeInfo
    {
    public:
        VSKeyTimeReal() {}
        ~VSKeyTimeReal() {}
        VSREAL m_Real;
    };
    class MATRIX_FUNCTION_API VSKeyTimeQuaternion : public VSKeyTimeInfo
    {
    public:
        VSKeyTimeQuaternion(){};
        ~VSKeyTimeQuaternion(){};
        VSQuat m_Quat;
    };

    class MATRIX_FUNCTION_API VSKeyTimeVectorCompress : public VSKeyTimeInfo
    {
    public:
        VSKeyTimeVectorCompress(){};
        ~VSKeyTimeVectorCompress(){};
        unsigned short m_X;
        unsigned short m_Y;
        unsigned short m_Z;
    };
    class MATRIX_FUNCTION_API VSKeyTimeRealCompress : public VSKeyTimeInfo
    {
    public:
        VSKeyTimeRealCompress() {}
        ~VSKeyTimeRealCompress() {}
        unsigned short m_Real;
    };
    class MATRIX_FUNCTION_API VSKeyTimeQuaternionCompress : public VSKeyTimeInfo
    {
    public:
        VSKeyTimeQuaternionCompress(){};
        ~VSKeyTimeQuaternionCompress(){};
        unsigned short m_X;
        unsigned short m_Y;
        unsigned short m_Z;
        unsigned short m_W;
    };

    DECLARE_Ptr(VSBoneKeyCompress);
    class MATRIX_FUNCTION_API VSBoneKey : public MObject
    {
        // RTTI
        // RTTI
        DECLARE_RTTI;

        DECLARE_INITIAL

    public:
        virtual ~VSBoneKey();

    public:
        VSBoneKey();
        Container::MArray<VSKeyTimeVector> m_TranslationArray;
        Container::MArray<VSKeyTimeVector> m_ScaleArray;
        Container::MArray<VSKeyTimeQuaternion> m_RotatorArray;
        VSUsedName m_cName;
        void CompressSameFrame();
        void Get(VSBoneKeyCompress *pBoneKeyCompress,
                 const Math::Vector3 &MaxTranslation, const Math::Vector3 &MinTranslation,
                 const Math::Vector3 MaxScale, const Math::Vector3 MinScale);
    };
    DECLARE_Ptr(VSBoneKey);
    VSTYPE_MARCO(VSBoneKey);

    class MATRIX_FUNCTION_API VSBoneKeyCompress : public MObject
    {
        // RTTI
        // RTTI
        DECLARE_RTTI;

        DECLARE_INITIAL

    public:
        virtual ~VSBoneKeyCompress();

    public:
        VSBoneKeyCompress();
        Container::MArray<VSKeyTimeVectorCompress> m_TranslationArray;
        Container::MArray<VSKeyTimeVectorCompress> m_ScaleArray;
        Container::MArray<VSKeyTimeQuaternionCompress> m_RotatorArray;
        VSUsedName m_cName;
        void Get(VSBoneKey *pBoneKey,
                 const Math::Vector3 &MaxTranslation, const Math::Vector3 &MinTranslation,
                 const Math::Vector3 MaxScale, const Math::Vector3 MinScale);
    };
    DECLARE_Ptr(VSBoneKeyCompress);
    VSTYPE_MARCO(VSBoneKeyCompress);

    DECLARE_Proxy(VSAnim);
    class MATRIX_FUNCTION_API VSAnim : public MObject, public VSResource
    {
        // RTTI
        DECLARE_RTTI;

        DECLARE_INITIAL

    public:
        virtual ~VSAnim();

    public:
        friend class VSResourceManager;
        VSAnim();
        inline bool IsAdditive() const
        {
            return m_pBlendAnim != NULL;
        }
        inline bool IsRootAnim() const
        {
            return m_bRootAnimPlay;
        }

        inline void SetRootMotion(bool bRootAnimPlay)
        {
            m_bRootAnimPlay = bRootAnimPlay;
        }

        VSAnimR *GetBlendAnim() const
        {
            return m_pBlendAnim;
        }

    protected:
        Container::MArray<VSBoneKeyPtr> m_pBoneKeyArray;
        Container::MArray<VSBoneKeyCompressPtr> m_pBoneKeyCompressArray;
        VSREAL m_fLength;
        bool m_bCompress;
        Math::Vector3 m_MaxCompressTranslation;
        Math::Vector3 m_MinCompressTranslation;
        Math::Vector3 m_MaxCompressScale;
        Math::Vector3 m_MinCompressScale;
        bool m_bRootAnimPlay;
        VSAnimRPtr m_pBlendAnim;

    public:
        // only use fbx
        void Compress();
        void ComputeAnimLength();
        inline VSREAL GetAnimLength() const
        {
            return m_fLength;
        }
        void AddBoneKey(VSBoneKey *pBoneKey);
        VSBoneKey *GetBoneKey(const VSUsedName &AnimName) const;
        VSBoneKey *GetBoneKey(unsigned int uiIndex) const;
        inline unsigned int GetBoneKeyNum() const
        {
            return m_pBoneKeyArray.GetNum();
        }
        virtual bool PostLoad(MStream *pStream);
        VSUsedName m_cName;

        Math::Vector3 GetTranslation(const VSUsedName &UseName, VSREAL fTime, unsigned int uiRepeatType = VSController::RT_CLAMP) const;
        Math::Vector3 GetScale(const VSUsedName &UseName, VSREAL fTime, unsigned int uiRepeatType = VSController::RT_CLAMP) const;
        VSQuat GetQuat(const VSUsedName &UseName, VSREAL fTime, unsigned int uiRepeatType = VSController::RT_CLAMP) const;
        VSMatrix3X3W GetMat(const VSUsedName &UseName, VSREAL fTime, unsigned int uiRepeatType = VSController::RT_CLAMP) const;

        Math::Vector3 GetTranslation(unsigned int i, VSREAL fTime, unsigned int uiRepeatType = VSController::RT_CLAMP) const;
        Math::Vector3 GetScale(unsigned int i, VSREAL fTime, unsigned int uiRepeatType = VSController::RT_CLAMP) const;
        VSQuat GetQuat(unsigned int i, VSREAL fTime, unsigned int uiRepeatType = VSController::RT_CLAMP) const;
        VSMatrix3X3W GetMat(unsigned int i, VSREAL fTime, unsigned int uiRepeatType = VSController::RT_CLAMP) const;

        DECLARE_RESOURCE(VSAnim, RA_ASYN_LOAD | RA_ASYN_POSTLOAD | RA_ENABLE_GC, RT_ACTION, ACTION, Resource / Anim, VSCacheResource)
    };
    DECLARE_Ptr(VSAnim);
    VSTYPE_MARCO(VSAnim);
    DECLARE_Proxy(VSAnim);

    typedef VSDelegateEvent<void(void)> AddAnimEventType;

    class MATRIX_FUNCTION_API VSAnimSet : public MObject
    {
        // RTTI
        DECLARE_RTTI;

        DECLARE_INITIAL
    public:
        virtual ~VSAnimSet();

    public:
        VSAnimSet();

    protected:
        VSMapOrder<VSUsedName, VSAnimRPtr> m_pAnimArray;

    public:
        void AddAnim(VSUsedName AnimName, VSAnimR *pAnim);
        VSAnimR *GetAnim(const VSUsedName &AnimName) const;
        VSAnimR *GetAnim(unsigned int i) const;
        const VSUsedName &GetAnimName(unsigned int i) const;
        unsigned int GetAnimIndex(VSAnimR *pAnim) const;

        inline unsigned int GetAnimNum() const
        {
            return m_pAnimArray.GetNum();
        }

        AddAnimEventType m_AddAnimEvent;

        VSREAL GetMaxAnimLength() const;
    };
    DECLARE_Ptr(VSAnimSet);
    VSTYPE_MARCO(VSAnimSet);
}
