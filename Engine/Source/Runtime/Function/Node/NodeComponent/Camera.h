#pragma once
#include "Node/NodeComponent/NodeComponent.h"
#include "Math/Vector3.h"
#include "Math/Matrix3.h"
#include "Math/Matrix4.h"
#include "Primitive/Plane3.h"

namespace Matrix
{
	class VSRenderer;
	typedef struct VSVIEWPORT_TYPE
	{
		VSREAL XMin;
		VSREAL YMin;
		VSREAL XMax;
		VSREAL YMax;
		VSREAL ZMin;
		VSREAL ZMax;
		bool bChangeAspect;
		void Reset()
		{
			XMin = 0.0f;
			YMin = 0.0f;
			XMax = 1.0f;
			YMax = 1.0f;
			ZMin = 0.0f;
			ZMax = 1.0f;
			bChangeAspect = false;
		}
		VSVIEWPORT_TYPE()
		{
			Reset();
		}
	} VSViewPort;
	class MStream;

	/*
	* 相机就是虚拟的照相机和摄像机，不但负责构建 3D 流水线中的各种变换矩阵，
	还负责裁剪掉相机不可见的物体来加快渲染速度
	*/
	class MATRIX_FUNCTION_API VSCamera : public VSNodeComponent
	{
		// PRIORITY

		// RTTI
		DECLARE_RTTI;
		DECLARE_INITIAL
	public:
		friend class VSViewFamily;
		VSCamera();
		virtual ~VSCamera();
		enum // Camera Plane
		{
			CP_RIGHT,
			CP_LEFT,
			CP_TOP,
			CP_BOTTOM,
			CP_FAR,
			CP_NEAR,
			CP_MAX = 6
		};
		inline const Math::Matrix4& GetViewMatrix() const;
		void CreateFromEuler(const Math::Vector3& Pos, VSREAL RotX, VSREAL RotY, VSREAL RotZ);
		/*
		* CreateFromLookAt这个过程也是在创建相机的本地矩阵（LocalTransform），相机的本地便换归一化
		相机在世界空间下的变换矩阵，经过相机矩阵变换到相机空间，正好是一个单位矩阵。相机平移到相机空间下变成了相机的原点(0，0，0)，而相机旋转到相机空间下变成了单位旋转矩阵
		*/
		void CreateFromLookDir(const Math::Vector3& Pos,
			const Math::Vector3& vcDir,
			const Math::Vector3& vcUp = Math::Vector3(0, 1, 0));
		void CreateFromLookAt(const Math::Vector3& vcPos,
			const Math::Vector3& vcLookAt,
			const Math::Vector3& vcUp = Math::Vector3(0, 1, 0));
		//下面两个函数相对于世界空间创建相机矩阵
		void CreateFromLookDirWorld(const Math::Vector3& Pos,
			const Math::Vector3& vcDir,
			const Math::Vector3& vcUp = Math::Vector3(0, 1, 0));
		void CreateFromLookAtWorld(const Math::Vector3& vcPos,
			const Math::Vector3& vcLookAt,
			const Math::Vector3& vcUp = Math::Vector3(0, 1, 0));
		bool SetPerspectiveFov(VSREAL fFov,   // X方向张角
			VSREAL Aspect, //宽高比
			VSREAL fZN,    //近剪裁面
			VSREAL fZF);   //远剪裁面
		bool SetAspect(VSREAL Aspect);

		bool SetOrthogonal(VSREAL fW,   //宽
			VSREAL fH,   //高
			VSREAL fZN,  //近剪裁面
			VSREAL fZF); //远剪裁面
		inline const Math::Matrix4& GetProjMatrix() const;
		inline bool AddViewPort(const VSViewPort& ViewPort); //视口
		inline VSViewPort* GetViewPort(unsigned int i) const;
		inline unsigned int GetViewPortNum() const
		{
			return m_ViewPort.GetNum();
		}
		void GetFrustumPoint(Math::Vector3 Point[8]);
		Primitive::AABB3 GetFrustumAABB();
		void GetPlane(Primitive::Plane3 Plane[VSCamera::CP_MAX]) const;
		inline VSREAL GetZFar() const
		{
			return m_ZFar;
		}
		inline VSREAL GetZNear() const
		{
			return m_ZNear;
		}
		inline VSREAL GetAspect() const
		{
			return m_Aspect;
		}
		inline VSREAL GetFov() const
		{
			return m_Fov;
		}
		inline VSViewFamily* GetViewFamily(unsigned int uiID)
		{
			if (uiID < m_ViewFamilyArray.GetNum())
			{
				return m_ViewFamilyArray[uiID];
			}
			return NULL;
		}
		inline unsigned int GetViewFamilyNum()
		{
			return m_ViewFamilyArray.GetNum();
		}
		inline void ClearProject()
		{
			m_ProjMat.Identity();
		}
		void AddCustomCullPlane(const Primitive::Plane3& P);
		void ClearCustomCullPlane();
		Container::MArray<Primitive::Plane3> m_CustomCullPlane;
		virtual void UpdateCameraState(double dAppTime);
		VSREAL GetProjectScreenSize(const Primitive::AABB3& WorldAABB);

	public:
		VSREAL m_RotX; //在局部坐标系下的EULER角(旋转角) 和 m_Local相关联 
		VSREAL m_RotY;
		VSREAL m_RotZ;

		bool m_bEnableOcclusionQuery;
		bool m_bEnableStreamResource;
		VSREAL m_fStreamBias;

	protected:
		friend class VSFreeCameraController;
		friend class VS1stCameraController;
		friend class VSSpatial;
		friend class VSScene;
		friend class VSSceneManager;
		friend class VSViewFamily;
		friend class VSLight;

		//创建相机的过程其实就是创建ViewMatrix、ProjectMatrix、ViewPort的过程
		Container::MArray<VSViewPort> m_ViewPort;
		Math::Matrix4 m_ViewMat; //相机矩阵 = 相机世界矩阵的逆矩阵
		Math::Matrix4 m_ProjMat; //投影矩阵

		VSREAL m_Fov;
		VSREAL m_Aspect;
		VSREAL m_ZFar;
		VSREAL m_ZNear;
		Container::MArrayOrder<VSViewFamily*> m_ViewFamilyArray;

		void AddViewFamily(VSViewFamily* pViewFamily);

		void DeleteViewFamily(VSViewFamily* pViewFamily);

	public:
		virtual void UpdateTransform(double dAppTime); //更新变换信息
	public:
		static bool InitialDefaultState();
		static bool TerminalDefaultState();

	protected:
		static VSPointer<VSCamera> ms_Default;

	public:
		friend class VSProjLight;
		static const VSCamera* GetDefault()
		{
			return ms_Default;
		}
	};

#include "Camera.inl"
	DECLARE_Ptr(VSCamera);
	VSTYPE_MARCO(VSCamera);
};
