// #pragma once
// #include "Render/SceneManager/Spatial.h"

// namespace Matrix
// {
// 	class VSSort;
// 	class VSGeometry;
// 	class MStream;
// 	class VSNodeComponent;
// 	class MATRIX_FUNCTION_API VSNode : public VSSpatial
// 	{
// 		// PRIORITY

// 		// RTTI
// 		DECLARE_RTTI;
// 		DECLARE_INITIAL
// 	public:
// 		friend class VSMeshComponent;
// 		VSNode();
// 		virtual ~VSNode() = 0;
// 		inline unsigned int GetNodeNum() const;
// 		virtual unsigned int AddChild(VSSpatial* pChild);
// 		virtual unsigned int DeleteChild(VSSpatial* pChild);
// 		virtual bool DeleteChild(unsigned int i);
// 		VSSpatial* GetChild(unsigned int i) const;
// 		virtual void DeleteAllChild();
// 		inline Container::MArray<VSSpatialPtr>* GetChildList();

// 	protected:
// 		virtual void UpdateWorldBound(double dAppTime); //更新世界边界体

// 		virtual void UpdateNodeAll(double dAppTime);
// 		virtual void ComputeNodeVisibleSet(VSCuller& Culler, bool bNoCull, double dAppTime);

// 	protected:
// 		Container::MArray<VSSpatialPtr> m_pChild;

// 	public:
// 		virtual void SetIsVisibleUpdate(bool bIsVisibleUpdate);
// 		virtual void CreateLocalAABB();
// 	};
// #include "Node.inl"
// 	DECLARE_Ptr(VSNode);
// 	VSTYPE_MARCO(VSNode);
// }
