#pragma once
#include "Node/Node.h"
namespace Matrix
{
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
