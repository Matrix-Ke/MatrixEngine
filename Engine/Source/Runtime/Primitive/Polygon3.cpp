#include "Polygon3.h"

using namespace Matrix::Primitive;
using namespace Matrix;

Polygon3::Polygon3()
{
	m_PointNum = 0;  //点个数
	m_IndexNum = 0;  //索引个数
	m_Flag = 0;      // 标志位
	m_pPoint = NULL; // 点列表
	m_pIndex = NULL; // 索引列表
}
/*----------------------------------------------------------------*/
Polygon3::~Polygon3()
{
	MX_ENGINE_DELETEA(m_pPoint);
	MX_ENGINE_DELETEA(m_pIndex);
}
/*----------------------------------------------------------------*/
Polygon3::Polygon3(const Matrix::Math::Vector3* pPoint, unsigned int PointNum)
{
	Set(pPoint, PointNum);
}
/*----------------------------------------------------------------*/
bool Polygon3::CopyFrom(const Polygon3& Polygon)
{
	if (!Polygon.m_pPoint || !Polygon.m_PointNum || !Polygon.m_pIndex || !Polygon.m_IndexNum)
		return 0;
	m_PointNum = Polygon.m_PointNum;
	m_IndexNum = Polygon.m_IndexNum;
	m_Flag = Polygon.m_Flag;
	MX_ENGINE_DELETEA(m_pPoint);
	MX_ENGINE_DELETEA(m_pIndex);
	m_pPoint = MX_NEW Matrix::Math::Vector3[m_PointNum];
	MX_ENGINE_ASSERT(m_pPoint);

	m_pIndex = MX_NEW VSUSHORT_INDEX[m_IndexNum];
	MX_ENGINE_ASSERT(m_pIndex);
	Core::MTXMemcpy(m_pPoint, Polygon.m_pPoint, sizeof(Matrix::Math::Vector3) * m_PointNum);
	Core::MTXMemcpy(m_pIndex, Polygon.m_pIndex, sizeof(VSUSHORT_INDEX) * m_IndexNum);
	return 1;
}
/*----------------------------------------------------------------*/
void Polygon3::SwapFaces()
{

	VSUSHORT_INDEX* pIndis = new VSUSHORT_INDEX[m_IndexNum];

	for (unsigned int i = 0; i < m_IndexNum; i++)
		pIndis[m_IndexNum - i - 1] = m_pIndex[i];

	m_Flag = !m_Flag;

	Plane3::Set(m_N * (-1.0f), m_fD);

	MX_ENGINE_DELETEA(m_pIndex);
	m_pIndex = pIndis;
}