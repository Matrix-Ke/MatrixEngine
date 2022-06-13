#pragma once
#include "Core/Object.h"
#include "Transform.h"
#include "Controller.h"
#include "AABB3.h"
#include "Resource.h"
namespace Matrix
{
    class MStream;
    class VSCuller;
    DECLARE_Ptr(VSMaterialInstance)
        DECLARE_Ptr(VSLight);
    DECLARE_Ptr(VSCamera);
    DECLARE_Proxy(VSMaterial);
    class MATRIX_FUNCTION_API VSSpatial : public MObject
    {
        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL_NO_CLASS_FACTORY;

    public:
        virtual ~VSSpatial() = 0;

    protected:
        Primitive::AABB3 m_WorldBV;

    public:
        virtual void ComputeVisibleSet(VSCuller &Culler, bool bNoCull, double dAppTime);

        enum // Cull Mode
        {
            CM_DYNAMIC,
            CM_ALAWAYS,
            CM_NEVER
        };

        virtual void UpdateView(VSCuller &Culler, double dAppTime);
        inline const Primitive::AABB3 &GetWorldAABB() const;

        virtual void CreateLocalAABB() {}

    protected:
        friend class VSNode;
        friend class VSSwitchNode;
        friend class VSScene;
        friend class VSGeometry;
        friend class VSMeshComponent;
        friend class VSSkeleton;
        friend class VSNodeComponent;
        friend class VSSkeletonMeshNode;
        bool m_bIsVisibleUpdate;

        // bool m_bForceNoCull;
    public:
        virtual void SetIsVisibleUpdate(bool bIsVisibleUpdate);

    public:
        unsigned int m_uiCullMode;

    protected:
        VSSpatial();

        virtual void UpdateWorldBound(double dAppTime) = 0; //更新边界体
        virtual void UpdateNodeAll(double dAppTime) = 0;
        virtual void ComputeNodeVisibleSet(VSCuller &Culler, bool bNoCull, double dAppTime) = 0;

    protected:
        Math::VSTransform m_World;
        Math::VSTransform m_Local;
        VSSpatial *m_pParent;
        Container::MArray<VSLight *> m_pAllLight;
        Container::MArray<VSCamera *> m_pAllCamera;

    public:
        bool m_bInheritScale;
        bool m_bInheritRotate;
        bool m_bInheritTranslate;
        virtual void UpdateTransform(double dAppTime); //更新变换信息
        virtual void UpdateAll(double dAppTime);

    public:
        inline void SetParent(VSSpatial *pParent);
        inline VSSpatial *GetParent() const;
        inline const Math::Vector3 &GetLocalScale() const;
        inline const Math::Vector3 &GetLocalTranslate() const;
        inline const Math::Matrix3 &GetLocalRotate() const;
        inline void GetLocalDir(Math::Vector3 &Dir, Math::Vector3 &Up, Math::Vector3 &Right) const;
        inline const Math::VSTransform &GetLocalTransform();

        virtual const Math::Vector3 &GetWorldScale();
        virtual const Math::Vector3 &GetWorldTranslate();
        virtual const Math::Matrix3 &GetWorldRotate();
        virtual void GetWorldDir(Math::Vector3 &Dir, Math::Vector3 &Up, Math::Vector3 &Right);
        virtual const Math::VSTransform &GetWorldTransform();

        virtual void SetWorldScale(const Math::Vector3 &fScale);
        virtual void SetWorldTranslate(const Math::Vector3 &Translate);
        virtual void SetWorldRotate(const Math::Matrix3 &Rotate);
        virtual void SetWorldTransform(const Math::VSTransform &LocalTransform);
        virtual void SetWorldMat(const VSMatrix3X3W VSMat);

        virtual void SetLocalScale(const Math::Vector3 &fScale);
        virtual void SetLocalTranslate(const Math::Vector3 &Translate);
        virtual void SetLocalRotate(const Math::Matrix3 &Rotate);
        virtual void SetLocalTransform(const Math::VSTransform &LocalTransform);
        virtual void SetLocalMat(const VSMatrix3X3W VSMat);

    public:
        Container::MArray<VSControllerPtr> m_ControllerArray;
        inline unsigned int GetControllerNum() const { return m_ControllerArray.GetNum(); }
        virtual void UpdateController(double dAppTime);
        bool AddController(VSController *pController);
        VSController *DeleteController(unsigned int ID);
        unsigned int DeleteController(VSController *pController);
        VSController *GetController(unsigned int ID) const;
        void DeleteAllController();
        inline Container::MArray<VSPointer<VSController>> *GetControllerList();

    public:
        inline void SetDynamic(bool bIsDynamic);
        inline bool IsDynamic() const { return !m_bIsStatic; }
        void ClearAllTime();

    protected:
        bool m_bIsStatic;
        bool m_bIsChanged;

    public:
        bool m_bEnable;
    };
    DECLARE_Ptr(VSSpatial);
    VSTYPE_MARCO(VSSpatial);
}