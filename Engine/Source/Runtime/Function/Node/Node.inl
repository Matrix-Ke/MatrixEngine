inline unsigned int VSNode::GetNodeNum()const
{
	return m_pChild.GetNum();
}
inline Container::MArray<VSSpatialPtr> * VSNode::GetChildList()
{
	return &m_pChild;
}
