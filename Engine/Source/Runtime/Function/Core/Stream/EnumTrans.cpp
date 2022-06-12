#include "EnumTrans.h"
using namespace Matrix;
VSEnumTrans& VSEnumTrans::GetInstance()
{
	static VSEnumTrans EnumTrans;
	return EnumTrans;
}
VSEnumTrans::VSEnumTrans()
{
}
VSEnumTrans::~VSEnumTrans()
{
}
void VSEnumTrans::Add(const TCHAR* EnumName, const TCHAR* Value)
{
	unsigned int i = m_EnumSaver.Find(EnumName);
	if (i == m_EnumSaver.GetNum())
	{
		Container::MapElement<Container::MString, Container::MArray<Container::MString>> Element;
		Element.Key = EnumName;
		Element.Value.AddElement(Value);
		m_EnumSaver.AddElement(Element);
		return;
	}
	Container::MapElement<Container::MString, Container::MArray<Container::MString>>& Element = m_EnumSaver[i];
	Element.Value.AddElement(Value);
}
void VSEnumTrans::Get(const TCHAR* EnumName, Container::MArray<Container::MString>& AS)
{
	unsigned int i = m_EnumSaver.Find(EnumName);
	if (i == m_EnumSaver.GetNum())
	{
		return;
	}
	AS = m_EnumSaver[i].Value;
}