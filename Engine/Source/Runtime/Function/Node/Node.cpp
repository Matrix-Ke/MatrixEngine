#include "Node/Node.h"
#include "Math/CMathInterface.h"
#include "Node/Geometry.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
#include "Node/NodeComponent/NodeComponent.h"
using namespace Matrix;
IMPLEMENT_RTTI_NoCreateFun(VSNode, VSSpatial)
BEGIN_ADD_PROPERTY(VSNode, VSSpatial)
REGISTER_PROPERTY(m_pChild, Child, VSProperty::F_SAVE_LOAD_CLONE | VSProperty::F_REFLECT_NAME)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_NO_CLASS_FACTORY_BEGIN(VSNode)
IMPLEMENT_INITIAL_NO_CLASS_FACTORY_END
VSNode::VSNode()
{
	DeleteAllChild();
}
VSNode::~VSNode()
{
	m_pChild.Clear();
}

unsigned int VSNode::AddChild(VSSpatial* pChild)
{
	ENGINE_ASSERT(pChild);
	for (unsigned int i = 0; i < m_pChild.GetNum(); i++)
	{
		if (m_pChild[i] == pChild)
		{
			return i;
		}
	}
	pChild->SetParent(this);
	m_pChild.AddElement(pChild);
	return m_pChild.GetNum() - 1;
}
unsigned int VSNode::DeleteChild(VSSpatial* pChild)
{
	ENGINE_ASSERT(pChild);
	for (unsigned int i = 0; i < m_pChild.GetNum(); i++)
	{

		if (m_pChild[i] == pChild)
		{

			pChild->SetParent(NULL);
			m_pChild.Erase(i);
			return i;
		}
	}

	return VSMAX_UINT32;
}
bool VSNode::DeleteChild(unsigned int i)
{
	ENGINE_ASSERT(i < m_pChild.GetNum());
	VSSpatial* Temp = m_pChild[i];

	Temp->SetParent(NULL);
	m_pChild.Erase(i);

	return 1;
}

VSSpatial* VSNode::GetChild(unsigned int i) const
{
	ENGINE_ASSERT(i < m_pChild.GetNum());
	return m_pChild[i];
}

void VSNode::DeleteAllChild()
{

	for (unsigned int i = 0; i < m_pChild.GetNum(); i++)
	{
		m_pChild[i]->SetParent(NULL);
	}
	m_pChild.Clear();
}
void VSNode::CreateLocalAABB()
{
	for (unsigned int i = 0; i < m_pChild.GetNum(); i++)
	{
		if (m_pChild[i])
		{
			m_pChild[i]->CreateLocalAABB();
		}
	}
}
void VSNode::UpdateWorldBound(double dAppTime)
{
	bool bFoundFirstBound = false;
	//遍历子节点，并和所有得到子节点整体的包围盒
	for (unsigned int i = 0; i < m_pChild.GetNum(); i++)
	{
		if (m_pChild[i])
		{
			if (!bFoundFirstBound)
			{
				m_WorldBV = m_pChild[i]->m_WorldBV;
				bFoundFirstBound = true;
			}
			else
			{
				//todo 为什么不递归求解字节的的包围盒， 子节点应该不止一层才是。 
				m_WorldBV = m_WorldBV.MergeAABB(m_pChild[i]->m_WorldBV);
			}
		}
	}
	if (!bFoundFirstBound)
	{
		VSREAL fA[3];
		m_WorldBV.GetfA(fA);
		m_WorldBV.Set(GetWorldTranslate(), fA);
	}
	// 提示父节点也要更新 
	if (m_pParent)
	{
		m_pParent->m_bIsChanged = true;
	}
}
void VSNode::UpdateNodeAll(double dAppTime)
{

	if (dAppTime > 0.0f)
	{
		UpdateController(dAppTime);
	}

	UpdateTransform(dAppTime);

	for (unsigned int i = 0; i < m_pChild.GetNum(); i++)
	{
		if (m_pChild[i])
			m_pChild[i]->UpdateNodeAll(dAppTime);
	}

	if (m_bIsChanged)
	{
		UpdateWorldBound(dAppTime);
	}
	m_bIsChanged = false;
}
void VSNode::ComputeNodeVisibleSet(VSCuller& Culler, bool bNoCull, double dAppTime)
{

	UpdateView(Culler, dAppTime);

	for (unsigned int i = 0; i < m_pChild.GetNum(); i++)
	{
		if (m_pChild[i])
		{

			m_pChild[i]->ComputeVisibleSet(Culler, bNoCull, dAppTime);
		}
	}
}

void VSNode::SetIsVisibleUpdate(bool bIsVisibleUpdate)
{
	for (unsigned int i = 0; i < m_pChild.GetNum(); i++)
	{

		m_pChild[i]->SetIsVisibleUpdate(bIsVisibleUpdate);
	}
	m_bIsVisibleUpdate = bIsVisibleUpdate;
	if (!m_bIsVisibleUpdate)
	{
		m_bEnable = true;
	}
}
