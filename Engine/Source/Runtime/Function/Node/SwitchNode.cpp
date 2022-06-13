#include "SwitchNode.h"
#include "Core/GraphicInclude.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSSwitchNode, VSNode)
BEGIN_ADD_PROPERTY(VSSwitchNode, VSNode)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSSwitchNode)
IMPLEMENT_INITIAL_END
VSSwitchNode::VSSwitchNode()
{
    m_uiActiveNode = 0;
}
VSSwitchNode::~VSSwitchNode()
{
}

void VSSwitchNode::ComputeNodeVisibleSet(VSCuller &Culler, bool bNoCull, double dAppTime)
{

    UpdateView(Culler, dAppTime);
    if (m_uiActiveNode < m_pChild.GetNum())
    {
        if (m_pChild[m_uiActiveNode])
        {
            m_pChild[m_uiActiveNode]->ComputeVisibleSet(Culler, bNoCull, dAppTime);
        }
    }
}
void VSSwitchNode::UpdateWorldBound(double dAppTime)
{
    ENGINE_ASSERT(m_uiActiveNode < m_pChild.GetNum());
    {
        if (m_pChild[m_uiActiveNode])
            m_WorldBV = m_pChild[m_uiActiveNode]->m_WorldBV;
        if (m_pParent)
        {
            m_pParent->m_bIsChanged = true;
        }
    }
}
VSSpatial *VSSwitchNode::GetActiveNode() const
{
    ENGINE_ASSERT(m_uiActiveNode < m_pChild.GetNum());

    return m_pChild[m_uiActiveNode];
}
