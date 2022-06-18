#pragma once
#include "Node/Node.h"
namespace Matrix
{
	/*
一个 VSSwitchNode 类，这个类的作用是从它的子类里面选出一个用于渲染的 LOD 信息
*/
	class MATRIX_FUNCTION_API VSSwitchNode : public VSNode
	{
		// PRIORITY

		// RTTI
		DECLARE_RTTI;
		DECLARE_INITIAL
	public:
		VSSwitchNode();
		virtual ~VSSwitchNode();

		virtual VSSpatial* GetActiveNode() const;

	protected:
		unsigned int m_uiActiveNode; //VSSwitchNode 类的主要作用都是操作当前的 m_uiActiveNode 节点。至于m_uiActiveNode 如何选择，需要子类在 UpdateView 中实现

	protected:
		virtual void UpdateWorldBound(double dAppTime); //更新世界边界体

		virtual void ComputeNodeVisibleSet(VSCuller& Culler, bool bNoCull, double dAppTime);
	};
	DECLARE_Ptr(VSSwitchNode);
	VSTYPE_MARCO(VSSwitchNode);

}
