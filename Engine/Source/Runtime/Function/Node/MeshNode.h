#pragma once
#include "Node/Node.h"
#include "Core/Resource.h"
namespace Matrix
{
	class VSGeometryNode;
	class VSSwitchNode;
	class MStream;
	/*
	* VSMeshNode 只是维护了一些基本状态，如是否接受投影、是否投射阴影、是否接受光照等信息。
	* 具体的还是需要挂载的VSGeometryNode节点
	*/
	class MATRIX_FUNCTION_API VSMeshNode : public VSNode
	{
		// PRIORITY

		// RTTI
		DECLARE_RTTI;
		DECLARE_INITIAL
	public:
		VSMeshNode();
		virtual ~VSMeshNode();
		inline void SetIsDrawBoundVolume(bool bIsDrawBoundVolume)
		{
			m_bIsDrawBoundVolume = bIsDrawBoundVolume;
		}
		inline unsigned int GetRenderGroup() const
		{
			return m_uiRenderGroup;
		}
		inline void SetRenderGroup(unsigned int uiRenderGroup)
		{
			m_uiRenderGroup = uiRenderGroup;
		}
		virtual bool SetDrawInstance(bool bDrawInstance) { return false; }
		virtual void UpdateView(VSCuller& Culler, double dAppTime);

		virtual void ComputeNodeVisibleSet(VSCuller& Culler, bool bNoCull, double dAppTime);
		bool m_bReceiveShadow;
		bool m_bCastShadow;
		bool m_bLighted;
		inline bool GetDrawInstance() const
		{
			return m_bDrawInstance;
		}

	protected:
		bool m_bDrawInstance;
		bool m_bIsDrawBoundVolume;
		unsigned int m_uiRenderGroup;
	};
	DECLARE_Ptr(VSMeshNode);
	VSTYPE_MARCO(VSMeshNode);
}
