#include "Sphere3.h"
#include "Math.h"
#include "Segment3.h"
#include "AABB3.h"
using namespace Matrix;
int Sphere3::RelationWith(const Matrix::Math::VSVector3& Point) const
{

	return Point.RelationWith(*this);
}
/*----------------------------------------------------------------*/
int Sphere3::RelationWith(const Line3& Line, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar) const
{
	return Line.RelationWith(*this, Quantity, tNear, tFar);
}
/*----------------------------------------------------------------*/
int Sphere3::RelationWith(const Ray3& Ray, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar) const
{
	return Ray.RelationWith(*this, Quantity, tNear, tFar);
}
/*----------------------------------------------------------------*/
int Sphere3::RelationWith(const Segment3& Segment, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar) const
{
	return Segment.RelationWith(*this, Quantity, tNear, tFar);
}
/*----------------------------------------------------------------*/
int Sphere3::RelationWith(const Plane3& Plane) const
{
	Matrix::Math::VSVector3 N = Plane.GetN();
	VSREAL fD = Plane.GetfD();

	VSREAL test = m_Center.Dot(N) + fD;
	if (test > m_fRadius)
		return VSFRONT;
	else if (test < -m_fRadius)
		return VSBACK;
	else
		return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int Sphere3::RelationWith(const VSTriangle3 Triangle) const
{
	return Triangle.RelationWith(*this);
}
/*----------------------------------------------------------------*/
int Sphere3::RelationWith(const Rectangle3& Rectangle) const
{
	return Rectangle.RelationWith(*this);
}
/*----------------------------------------------------------------*/
int Sphere3::RelationWith(const VSOBB3& OBB) const
{
	return OBB.RelationWith(*this);
}
/*----------------------------------------------------------------*/
int Sphere3::RelationWith(const Sphere3& Sphere) const
{
	VSREAL Sum = m_fRadius + Sphere.m_fRadius;

	Sum *= Sum;

	Matrix::Math::VSVector3 Sub = m_Center - Sphere.m_Center;

	if (Sub.GetSqrLength() > Sum)
		return VSNOINTERSECT;

	return VSINTERSECT;
}