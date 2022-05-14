#include "Ray3.h"
#include "Segment3.h"
#include "AABB3.h"
#include "Polygon3.h"
using namespace Matrix;
/*----------------------------------------------------------------*/
int Ray3::RelationWith(const VSTriangle3& Triangle, bool bCull, VSREAL& fRayParameter,
	VSREAL fTriangleParameter[3]) const
{
	if (Matrix::Primitive::Line3::RelationWith(Triangle, bCull, fRayParameter, fTriangleParameter) == VSNOINTERSECT)
		return VSNOINTERSECT;
	if (fRayParameter < 0.0f)
		return VSNOINTERSECT;
	return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int Ray3::RelationWith(const Plane3& Plane, bool bCull, VSREAL& fRayParameter) const
{
	int iFlag = Matrix::Primitive::Line3::RelationWith(Plane, bCull, fRayParameter);
	if (iFlag != VSINTERSECT)
		return iFlag;
	if (fRayParameter < 0.0f)
	{
		iFlag = m_Orig.RelationWith(Plane);
		return iFlag;
	}
	return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int Ray3::RelationWith(const Rectangle3& Rectangle, bool bCull, VSREAL& fRayParameter,
	VSREAL fRectangleParameter[2]) const
{
	if (Matrix::Primitive::Line3::RelationWith(Rectangle, bCull, fRayParameter, fRectangleParameter) == VSNOINTERSECT)
		return VSNOINTERSECT;
	if (fRayParameter < 0.0f)
		return VSNOINTERSECT;

	return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int Ray3::RelationWith(const VSOBB3& OBB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar) const
{
	if (Matrix::Primitive::Line3::RelationWith(OBB, Quantity, tNear, tFar) == VSNOINTERSECT)
		return VSNOINTERSECT;
	if (tFar < 0.0f)
	{
		Quantity = 0;
		return VSNOINTERSECT;
	}
	if (tNear < 0.0f)
	{
		Quantity = 1;
		tNear = tFar;
	}
	return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int Ray3::RelationWith(const Sphere3& sphere, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar) const
{
	if (Matrix::Primitive::Line3::RelationWith(sphere, Quantity, tNear, tFar) == VSNOINTERSECT)
		return VSNOINTERSECT;
	if (tFar < 0.0f)
	{
		Quantity = 0;
		return VSNOINTERSECT;
	}
	if (tNear < 0.0f)
	{
		Quantity = 1;
		tNear = tFar;
	}
	return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int Ray3::RelationWith(const AABB3& AABB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar) const
{
	if (Matrix::Primitive::Line3::RelationWith(AABB, Quantity, tNear, tFar) == VSNOINTERSECT)
		return VSNOINTERSECT;
	if (tFar < 0.0f)
	{
		Quantity = 0;
		return VSNOINTERSECT;
	}
	if (tNear < 0.0f)
	{
		Quantity = 1;
		tNear = tFar;
	}
	return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int Ray3::RelationWith(const Polygon3& Polygon, VSREAL& fRayParameter,
	bool bCull, int& iIndexTriangle, VSREAL fTriangleParameter[3]) const
{

	return Polygon.RelationWith(*this, bCull, iIndexTriangle, fTriangleParameter, fRayParameter);
}