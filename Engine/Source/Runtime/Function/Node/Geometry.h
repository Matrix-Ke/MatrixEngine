#pragma once
#include "Spatial.h"
#include "Array.h"
#include "VertexBuffer.h"


namespace Matrix
{

	class VSSkeleton;
	class VSMeshNode;
	class MStream;
	DECLARE_Ptr(VSBoneNode);
	DECLARE_Ptr(VSMorphSet);
	DECLARE_Ptr(VSMeshData);
	DECLARE_Ptr(VSTexAllState);
	struct MorphDataType
	{
		unsigned int Layer = 0;
		unsigned int TextureSizeY = 0;
		Container::MMapOrder<unsigned int, float> ValueMap;
		VSTexAllStatePtr MorphVDataTexture;
		VSTexAllStatePtr MorphNDataTexture;
		VSTexAllStatePtr MorphTDataTexture;
		VSTexAllStatePtr MorphBDataTexture;
	};
	class MATRIX_FUNCTION_API VSGeometry : public VSSpatial
	{
		DECLARE_RTTI;
		DECLARE_INITIAL
	public:
		enum // Update Geometry Renturn Information
		{
			UGRI_FAIL,
			UGRI_CONTINUME,
			UGRI_END,
			UGRI_MAX
		};
		enum // Geometry Use Type
		{
			GUT_NORMAL,
			GUT_SHADOW_VOLUME,
			GUT_MAX
		};
		VSGeometry();
		virtual ~VSGeometry();

		void SetMeshData(VSMeshData* pMeshData);
		VSMeshData* GetMeshData() const;
		VSMeshData* GetOriginMeshData() const;

		unsigned int GetActiveNum();
		bool SetActiveNum(unsigned int uiActiveNum);
		unsigned int GetTotalNum() const;
		unsigned int GetMeshDataType();

		virtual void CreateLocalAABB();

		void SetAffectBoneArray(const Container::MArray<VSBoneNode*>& pBoneNodeArray);
		void SetAffectBoneArray(const Container::MArray<VSUsedName>& BoneNodeArray);
		inline unsigned int GetAffectBoneNum() const
		{
			return m_pBoneNode.GetNum();
		}
		inline Container::MArray<Math::Vector4>& GetSkinWeightBuffer()
		{
			return m_SkinWeightBuffer;
		}
		inline VSBoneNode* GetAffectBone(unsigned int i) const
		{
			if (i < m_pBoneNode.GetNum())
				return m_pBoneNode[i];
			else
				return NULL;
		}
		VSSkeleton* GetAffectSkeleton() const;

		VSMeshNode* GetMeshNode() const;
		unsigned int GetVertexNum() const;

		// must send to render thread
		virtual void UpdateGeometryBeforeDrawCall();

		virtual bool PostLoad(MStream* pStream);
		virtual bool PostClone(MObject* pObjectSrc);
		inline void SetLocalBV(const Primitive::AABB3& BV)
		{
			m_LocalBV = BV;
		}
		inline Primitive::AABB3 GetLocalBV() const
		{
			return m_LocalBV;
		}
		VSUsedName m_GeometryName;
		virtual bool IsSwapCull();
		virtual unsigned int GetGeometryUseType()
		{
			return GUT_NORMAL;
		}
		static void LoadDefault();
		static VSGeometry* GetDefaultQuad()
		{
			return ms_Quad;
		}
		static VSGeometry* GetDefaultCube()
		{
			return ms_DefaultCube;
		}
		static VSGeometry* GetDefaultCubCone()
		{
			return ms_DefaultCubCone;
		}
		static VSGeometry* GetDefaultCone()
		{
			return ms_DefaultCone;
		}
		static VSGeometry* GetDefaultRenderCube()
		{
			return ms_DefaultRenderCube;
		}

		bool SetMaterialInstance(VSMaterialInstance* pMaterial, unsigned int uiIndex);
		bool SetMaterialInstance(VSMaterialR* pMaterial, unsigned int uiIndex);

		bool SetUseMaterialInstance(unsigned int uiIndex);
		unsigned int AddMaterialInstance(VSMaterialR* pMaterial);
		unsigned int AddMaterialInstance(VSMaterialInstance* pMaterial);

		void ClearAllMaterialInstance();
		void DeleteMaterialInstance(unsigned int i);
		unsigned int DeleteMaterialInstance(VSMaterialInstance* pMaterial);

		VSMaterialInstance* GetUseMaterialInstance() const;

		VSMaterialInstance* GetMaterialInstance(unsigned int i) const;
		void AddMorphAABB(VSVertexBuffer* pMorphVertexBuffer);
		void CreateMorphMeshData(Container::MMap<unsigned int, VSVertexBuffer*>& MorphDataSet);
		bool HasMorphTarget() const;
		const MorphDataType& GetMorphData()
		{
			return m_MorphData;
		}
		void SetMorphData(unsigned int Index, float fData);
		virtual void GetStreamResource(Container::MArray<VSResourceProxyBase*>& pResourceProxy, StreamInformation_TYPE& StreamInformation) const;

	protected:
		// friend class VSRenderer;
		Container::MArray<VSMaterialInstancePtr> m_pMaterialInstance;
		unsigned int m_uiCurUseMaterial;

		virtual void UpdateView(VSCuller& Culler, double dAppTime);
		virtual void UpdateWorldBound(double dAppTime); //更新世界边界体
		virtual void UpdateNodeAll(double dAppTime);
		virtual void ComputeNodeVisibleSet(VSCuller& Culler, bool bNoCull, double dAppTime);
		virtual void UpdateOther(double dAppTime);
		VSMeshDataPtr m_pMeshData;
		unsigned int m_uiActiveNum;
		Container::MArray<VSBoneNode*> m_pBoneNode;

		Container::MArray<VSUsedName> m_BoneName;
		Primitive::AABB3 m_LocalBV;
		void LinkBoneNode();
		Container::MArray<Math::Vector4> m_SkinWeightBuffer;
		MorphDataType m_MorphData;
		static VSPointer<VSGeometry> ms_Quad;
		static VSPointer<VSGeometry> ms_DefaultCube;
		static VSPointer<VSGeometry> ms_DefaultCubCone;
		static VSPointer<VSGeometry> ms_DefaultCone;
		static VSPointer<VSGeometry> ms_DefaultRenderCube;

	public:
		static bool InitialDefaultState();
		static bool TerminalDefaultState();
	};
	DECLARE_Ptr(VSGeometry);
	VSTYPE_MARCO(VSGeometry);

	class MATRIX_FUNCTION_API VSShadowVolumeGeometry : public VSGeometry
	{
		DECLARE_RTTI;
		DECLARE_INITIAL
	public:
		VSShadowVolumeGeometry();
		virtual ~VSShadowVolumeGeometry();
		virtual unsigned int GetGeometryUseType()
		{
			return GUT_SHADOW_VOLUME;
		}
		virtual void CreateClodMesh() {};
		virtual void RemoveClodMesh() {};
	};
	DECLARE_Ptr(VSShadowVolumeGeometry);
	VSTYPE_MARCO(VSShadowVolumeGeometry);
};
