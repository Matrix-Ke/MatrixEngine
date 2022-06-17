#pragma once
#include "Node/SwitchNode.h"
#include "Node/GeometryNode.h"
namespace Matrix
{
	/*
	用于模型 LOD:
	选择 LOD 信息的算法也很简单。采用二分法，把视野逐步二等分。如果模型位置在整个视野的前二分之一，那么 m_uiActiveNode 为 0；
	如果在后二分之一，则继续二等分。前面一半的m_uiActiveNode 为 1，对后面一半则再次划分
	主要依靠： UpdateView（） 函数操作
	*/
	class MATRIX_FUNCTION_API VSModelSwitchNode : public VSSwitchNode
	{
		// PRIORITY

		// RTTI
		DECLARE_RTTI;
		DECLARE_INITIAL
	public:
		VSModelSwitchNode();
		virtual ~VSModelSwitchNode();

	public:
		virtual VSGeometryNode* GetGeometryNode(unsigned int uiLodLevel);
		virtual void UpdateView(VSCuller& Culler, double dAppTime);
		void SetUseMaterialInstance(unsigned int SubMeshID, unsigned int UsedID);
		virtual void GetStreamResource(Container::MArray<VSResourceProxyBase*>& pResourceProxy, StreamInformation_TYPE& StreamInformation) const;
	};


	DECLARE_Ptr(VSModelSwitchNode);
	VSTYPE_MARCO(VSModelSwitchNode);

}
