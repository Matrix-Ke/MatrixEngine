#include "Segment3.h"
#include "AABB3.h"
#include "Polygon3.h"
using namespace Matrix;
/*----------------------------------------------------------------*/
int Segment3::RelationWith(const VSTriangle3& Triangle, bool bCull, VSREAL& fSegmentParameter,
	VSREAL fTriangleParameter[3]) const
{
	if (Ray3::RelationWith(Triangle, bCull, fSegmentParameter, fTriangleParameter) == VSNOINTERSECT)
		return VSNOINTERSECT;
	if (fSegmentParameter > m_fLen)
		return VSNOINTERSECT;
	return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int Segment3::RelationWith(const Plane3& Plane, bool bCull, VSREAL& fSegmentParameter) const
{
	int iFlag = Ray3::RelationWith(Plane, bCull, fSegmentParameter);
	if (iFlag != VSINTERSECT)
		return iFlag;
	if (fSegmentParameter > m_fLen)
	{
		return m_Orig.RelationWith(Plane);
	}
	return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int Segment3::RelationWith(const Rectangle3& Rectangle, bool bCull, VSREAL& fSegmentParameter,
	VSREAL fRectangleParameter[2]) const
{

	if (Ray3::RelationWith(Rectangle, bCull, fSegmentParameter, fRectangleParameter) == VSNOINTERSECT)
		return VSNOINTERSECT;
	if (fSegmentParameter > m_fLen)
		return VSNOINTERSECT;
	return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int Segment3::RelationWith(const VSOBB3& OBB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar) const
{
	if (Ray3::RelationWith(OBB, Quantity, tNear, tFar) == VSNOINTERSECT)
		return VSNOINTERSECT;
	if (tNear > m_fLen)
	{
		Quantity = 0;
		if (m_Orig.RelationWith(OBB) != VSOUT)
			return VSIN;
		return VSNOINTERSECT;
	}

	if (tFar > m_fLen)
	{
		Quantity = 1;
		tFar = tNear;
	}
	return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int Segment3::RelationWith(const Sphere3& sphere, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar) const
{
	if (Ray3::RelationWith(sphere, Quantity, tNear, tFar) == VSNOINTERSECT)
		return VSNOINTERSECT;
	if (tNear > m_fLen)
	{
		Quantity = 0;
		if (m_Orig.RelationWith(sphere) != VSOUT)
			return VSIN;
		return VSNOINTERSECT;
	}

	if (tFar > m_fLen)
	{
		Quantity = 1;
		tFar = tNear;
	}
	return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int Segment3::RelationWith(const AABB3& AABB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar) const
{

	if (Ray3::RelationWith(AABB, Quantity, tNear, tFar) == VSNOINTERSECT)
		return VSNOINTERSECT;
	if (tNear > m_fLen)
	{
		Quantity = 0;
		if (m_Orig.RelationWith(AABB) != VSOUT)
			return VSIN;
		return VSNOINTERSECT;
	}

	if (tFar > m_fLen)
	{
		Quantity = 1;
		tFar = tNear;
	}
	return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int Segment3::RelationWith(const Polygon3& Polygon, VSREAL& fSegmentParameter,
	bool bCull, int& iIndexTriangle, VSREAL fTriangleParameter[3]) const
{

	return Polygon.RelationWith(*this, bCull, iIndexTriangle, fTriangleParameter, fSegmentParameter);
}