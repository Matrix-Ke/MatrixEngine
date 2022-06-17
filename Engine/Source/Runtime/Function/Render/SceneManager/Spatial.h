#pragma once
#include "Core/Object.h"
#include "Controller/Controller.h"
//#include "Core/Resource.h"

#include "Math/Transform.h"
#include "Primitive/AABB3.h"


namespace Matrix
{
	class MStream;
	class VSCuller;
	//DECLARE_Ptr(VSMaterialInstance)
	//DECLARE_Ptr(VSLight);
	//DECLARE_Ptr(VSCamera);
	//DECLARE_Proxy(VSMaterial);

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
		virtual void ComputeVisibleSet(VSCuller& Culler, bool bNoCull, double dAppTime);

		enum // Cull Mode
		{
			CM_DYNAMIC,
			CM_ALAWAYS,
			CM_NEVER
		};

		virtual void UpdateView(VSCuller& Culler, double dAppTime); //UpdateView 函数表示依据视点的更新, 类如： LOD
		inline const Primitive::AABB3& GetWorldAABB() const;

		virtual void CreateLocalAABB() {}

	public:
		inline void SetParent(VSSpatial* pParent);
		inline VSSpatial* GetParent() const;
		inline const Math::Vector3& GetLocalScale() const;
		inline const Math::Vector3& GetLocalTranslate() const;
		inline const Math::Matrix3& GetLocalRotate() const;
		inline void GetLocalDir(Math::Vector3& Dir, Math::Vector3& Up, Math::Vector3& Right) const;
		inline const Math::VSTransform& GetLocalTransform();

		virtual const Math::Vector3& GetWorldScale();
		virtual const Math::Vector3& GetWorldTranslate();
		virtual const Math::Matrix3& GetWorldRotate();
		virtual void GetWorldDir(Math::Vector3& Dir, Math::Vector3& Up, Math::Vector3& Right);
		virtual const Math::VSTransform& GetWorldTransform();

		virtual void SetWorldScale(const Math::Vector3& fScale);
		virtual void SetWorldTranslate(const Math::Vector3& Translate);
		virtual void SetWorldRotate(const Math::Matrix3& Rotate);
		virtual void SetWorldTransform(const Math::VSTransform& LocalTransform);
		virtual void SetWorldMat(const Math::Matrix4 VSMat);

		virtual void SetLocalScale(const Math::Vector3& fScale);
		virtual void SetLocalTranslate(const Math::Vector3& Translate);
		virtual void SetLocalRotate(const Math::Matrix3& Rotate);
		virtual void SetLocalTransform(const Math::VSTransform& LocalTransform);
		virtual void SetLocalMat(const Math::Matrix4 VSMat);

		virtual void UpdateTransform(double dAppTime); //更新变换信息
		/*更新的时候，根节点通过调用 virtual void UpdateAll(double dAppTime)函数，从根节点出发	一直到叶子节点更新位置信息，
		计算出世界空间中所有的位置，然后再从叶子节点回溯到根节点，计算出所有节点的世界空间的包围盒，
		*/
		virtual void UpdateAll(double dAppTime);
	public:
		Container::MArray<VSControllerPtr> m_ControllerArray;
		inline unsigned int GetControllerNum() const { return m_ControllerArray.GetNum(); }
		virtual void UpdateController(double dAppTime);
		bool AddController(VSController* pController);
		VSController* DeleteController(unsigned int ID);
		unsigned int DeleteController(VSController* pController);
		VSController* GetController(unsigned int ID) const;
		void DeleteAllController();
		inline Container::MArray<VSPointer<VSController>>* GetControllerList();

	public:
		inline void SetDynamic(bool bIsDynamic);
		inline bool IsDynamic() const { return !m_bIsStatic; }
		void ClearAllTime();
	public:
		virtual void SetIsVisibleUpdate(bool bIsVisibleUpdate);

	protected:
		VSSpatial();

		virtual void UpdateWorldBound(double dAppTime) = 0; //更新边界体
		virtual void UpdateNodeAll(double dAppTime) = 0; //子类继承实现更新操作, 更新transform和更新包围盒
		//若 bNoCull 为 true，表示这个节点完全可见；若为 false，则表示这个节点部分可见。每个子类都可以重写ComputeNodeVisibleSet这个函数，根据不同的需求做相应处理。
		virtual void ComputeNodeVisibleSet(VSCuller& Culler, bool bNoCull, double dAppTime) = 0;

	protected:
		//todo  需要这么多友元嘛？
		friend class VSNode;
		friend class VSSwitchNode;
		friend class VSScene;
		friend class VSGeometry;
		friend class VSMeshComponent;
		friend class VSSkeleton;
		friend class VSNodeComponent;
		friend class VSSkeletonMeshNode;
		bool m_bIsVisibleUpdate; //m_bIsVisibleUpdate 选项来控制与视觉无关的更新
	public:
		unsigned int m_uiCullMode; //m_uiCullMode 变量表示这个节点的裁剪方式，分别是始终裁剪、动态裁剪、从不裁剪

		// bool m_bForceNoCull;



	protected:
		Math::VSTransform m_World;
		Math::VSTransform m_Local;//local是相对世界位置的
		VSSpatial* m_pParent;
		/*
		* 由于相机与光源的特殊性，不得不单独管理，在整个场景更新的时候，要把所有的相机和光源都收集起来
		*/
		Container::MArray<VSLight*> m_pAllLight;
		Container::MArray<VSCamera*> m_pAllCamera;

	public:
		bool m_bInheritScale;
		bool m_bInheritRotate;
		bool m_bInheritTranslate;


	protected:
		bool m_bIsStatic;
		bool m_bIsChanged;

	public:
		bool m_bEnable; //比如，当有些物体不可见的时候，有些更新并不是必要的，因此那些纯粹渲染表现的更新就可以关闭
	};
	DECLARE_Ptr(VSSpatial);
	VSTYPE_MARCO(VSSpatial);
}