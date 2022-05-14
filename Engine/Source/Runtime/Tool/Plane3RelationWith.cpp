#include "Plane3.h"
#include "Segment3.h"
#include "AABB3.h"
#include "Polygon3.h"
#include "Cylinder3.h"
using namespace Matrix;
int Plane3::RelationWith(const Matrix::Math::VSVector3& Point) const
{
	VSREAL f = (Point.Dot(m_N)) + m_fD;

	if (f > EPSILON_E4)
		return VSFRONT;
	if (f < -EPSILON_E4)
		return VSBACK;
	return VSON;
}
/*----------------------------------------------------------------*/
int Plane3::RelationWith(const Line3& Line, bool bCull, VSREAL& fLineParameter) const
{

	return Line.RelationWith(*this, bCull, fLineParameter);
}
/*----------------------------------------------------------------*/
int Plane3::RelationWith(const Ray3& Ray, bool bCull, VSREAL& fRayParameter) const
{
	return Ray.RelationWith(*this, bCull, fRayParameter);
}
/*----------------------------------------------------------------*/
int Plane3::RelationWith(const Segment3& Segment, bool bCull, VSREAL& fSegmentParameter) const
{
	return Segment.RelationWith(*this, bCull, fSegmentParameter);
}
/*----------------------------------------------------------------*/
int Plane3::RelationWith(const VSOBB3& OBB) const
{
	return OBB.RelationWith(*this);
}
/*----------------------------------------------------------------*/
int Plane3::RelationWith(const AABB3& AABB) const
{
	return AABB.RelationWith(*this);
}
/*----------------------------------------------------------------*/
int Plane3::RelationWith(const Sphere3& Sphere) const
{
	return Sphere.RelationWith(*this);
}
/*----------------------------------------------------------------*/
int Plane3::RelationWith(const VSTriangle3& Triangle) const
{
	return Triangle.RelationWith(*this);
}
/*----------------------------------------------------------------*/
int Plane3::RelationWith(const Plane3& Plane) const
{
	Matrix::Math::VSVector3 vcCross;
	VSREAL fSqrLength;

	vcCross.Cross(m_N, Plane.m_N);
	fSqrLength = vcCross.GetSqrLength();

	if (fSqrLength < EPSILON_E4)
	{
		// return Plane.m_Point.RelationWith(*this);
		return VSNOINTERSECT;
	}
	return VSINTERSECT;
	/*VSREAL fN00 = m_N.GetSqrLength();
	VSREAL fN01 = m_N * Plane.m_N;
	VSREAL fN11 = Plane.m_N.GetSqrLength();
	VSREAL fDet = fN00*fN11 - fN01*fN01;

	if (ABS(fDet) < EPSILON_E4)
		return Plane.m_Point.RelationWith(*this);

	VSREAL fInvDet = 1.0f/fDet;
	VSREAL fC0 = (fN11 * m_fD - fN01 * Plane.m_fD) * fInvDet;
	VSREAL fC1 = (fN00 * Plane.m_fD - fN01 * m_fD) * fInvDet;
	Line.Set(vcCross,m_N * fC0 + Plane.m_N * fC1);
	return VSINTERSECT;*/
}
/*----------------------------------------------------------------*/
int Plane3::RelationWith(const Rectangle3& Rectangle) const
{
	return Rectangle.RelationWith(*this);
}
/*----------------------------------------------------------------*/
int Plane3::RelationWith(const Plane3& Plane, Line3& Line) const
{
	Matrix::Math::VSVector3 vcCross;
	VSREAL fSqrLength;

	vcCross.Cross(m_N, Plane.m_N);
	fSqrLength = vcCross.GetSqrLength();

	if (fSqrLength < EPSILON_E4)
	{
		return VSNOINTERSECT;
		// return Plane.m_Point.RelationWith(*this);
	}
	VSREAL fN00 = m_N.GetSqrLength();
	VSREAL fN01 = m_N.Dot(Plane.m_N);
	VSREAL fN11 = Plane.m_N.GetSqrLength();
	VSREAL fDet = fN00 * fN11 - fN01 * fN01;

	if (ABS(fDet) < EPSILON_E4)
		return VSNOINTERSECT;

	VSREAL fInvDet = 1.0f / fDet;
	VSREAL fC0 = (fN11 * m_fD - fN01 * Plane.m_fD) * fInvDet;
	VSREAL fC1 = (fN00 * Plane.m_fD - fN01 * m_fD) * fInvDet;
	Line.Set(m_N * fC0 + Plane.m_N * fC1, vcCross);
	return VSINTERSECT; /**/
}
/*----------------------------------------------------------------*/
int Plane3::RelationWith(const VSTriangle3& Triangle, Segment3& Segment) const
{
	return Triangle.RelationWith(*this, Segment);
}
/*----------------------------------------------------------------*/
int Plane3::RelationWith(const Rectangle3& Rectangle, Segment3& Segment) const
{
	return Rectangle.RelationWith(*this, Segment);
}
/*----------------------------------------------------------------*/
int Plane3::RelationWith(const Polygon3& Polygon) const
{
	return Polygon.RelationWith(*this);
}
/*----------------------------------------------------------------*/
int Plane3::RelationWith(const Polygon3& Polygon, Segment3& Segment) const
{

	return Polygon.RelationWith(*this, Segment);
}
int Plane3::RelationWith(const VSCylinder3& Cylinder3) const
{
	return VSINTERSECT;
}