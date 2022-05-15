#include "Segment3.h"

#include "Ray3.h"
#include "Segment3.h"

#include "Plane3.h"
#include "Triangle3.h"
#include "Rectangle3.h"
#include "Polygon3.h"

#include "OBB3.h"
#include "AABB3.h"
#include "Sphere3.h"

using namespace Matrix::Primitive;

/*----------------------------------------------------------------*/
Segment3::Segment3()
{
}
/*----------------------------------------------------------------*/
Segment3::~Segment3()
{
}
/*----------------------------------------------------------------*/
Segment3::Segment3(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& End)
{
	Set(Orig, End);
}
/*----------------------------------------------------------------*/
Segment3::Segment3(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& Dir, VSREAL fLen)
{
	Set(Orig, Dir, fLen);
}
/*----------------------------------------------------------------*/
void Segment3::Transform(const Segment3& Segment, const Matrix::Math::Matrix4& Mat)
{

	m_Orig = Mat * Segment.m_Orig;
	m_End = Mat * Segment.m_End;
	m_Dir = Mat.Apply3X3(Segment.m_Dir);
	m_Dir.Normalize();
	m_fLen = Segment.m_fLen;
}
/*----------------------------------------------------------------*/
bool Segment3::GetParameter(const Matrix::Math::Vector3& Point, VSREAL& fSegmentParameter) const
{
	if (!Ray3::GetParameter(Point, fSegmentParameter))
		return 0;
	if (fSegmentParameter > m_fLen)
		return 0;
	return 1;
}


VSREAL Segment3::SquaredDistance(const Matrix::Math::Vector3& Point, VSREAL& fSegmentParameter) const
{
	VSREAL SqDis = Ray3::SquaredDistance(Point, fSegmentParameter);
	if (fSegmentParameter > m_fLen)
	{
		fSegmentParameter = m_fLen;
		Matrix::Math::Vector3 Diff;
		Diff = Point - m_End;
		return Diff.GetSqrLength();
	}
	else
	{
		return SqDis;
	}
}
/*----------------------------------------------------------------*/
VSREAL Segment3::SquaredDistance(const Line3& Line, VSREAL& fSegmentParameter, VSREAL& fLineParameter) const
{
	return Line.SquaredDistance(*this, fLineParameter, fSegmentParameter);
}
/*----------------------------------------------------------------*/
VSREAL Segment3::SquaredDistance(const Ray3& Ray, VSREAL& fSegmentParameter, VSREAL& fRayParameter) const
{
	return Ray.SquaredDistance(*this, fRayParameter, fSegmentParameter);
}
/*----------------------------------------------------------------*/
VSREAL Segment3::SquaredDistance(const Segment3& Segment, VSREAL& fSegment1Parameter, VSREAL& fSegment2Parameter) const
{
	const Ray3& Ray = Segment;
	VSREAL sqrDist = SquaredDistance(Ray, fSegment1Parameter, fSegment2Parameter);
	VSREAL fLen = Segment.GetLen();
	if (fSegment2Parameter > fLen)
	{
		fSegment2Parameter = fLen;
		Matrix::Math::Vector3 End = Segment.GetEnd();
		sqrDist = SquaredDistance(End, fSegment1Parameter);
	}
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Segment3::SquaredDistance(const Triangle3& Triangle, VSREAL& fSegmentParameter, VSREAL fTriangleParameter[3]) const
{
	VSREAL sqrDist = Ray3::SquaredDistance(Triangle, fSegmentParameter, fTriangleParameter);

	if (fSegmentParameter > m_fLen)
	{
		fSegmentParameter = m_fLen;
		sqrDist = Point3(m_End).SquaredDistance(Triangle, fTriangleParameter);
	}

	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Segment3::SquaredDistance(const Rectangle3& Rectangle, VSREAL& fSegmentParameter, VSREAL fRectangleParameter[2]) const
{
	VSREAL sqrDist = Ray3::SquaredDistance(Rectangle, fSegmentParameter, fRectangleParameter);

	if (fSegmentParameter > m_fLen)
	{
		fSegmentParameter = m_fLen;
		sqrDist = Point3(m_End).SquaredDistance(Rectangle, fRectangleParameter);
	}

	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Segment3::SquaredDistance(const OBB3& OBB, VSREAL& fSegmentParameter, VSREAL fOBBParameter[3]) const
{
	VSREAL sqrDist = Ray3::SquaredDistance(OBB, fSegmentParameter, fOBBParameter);
	if (fSegmentParameter > m_fLen)
	{
		fSegmentParameter = m_fLen;
		sqrDist = OBB.SquaredDistance(m_End, fOBBParameter);
	}

	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Segment3::Distance(const Sphere3& Sphere, VSREAL& fSegmentParameter, Matrix::Math::Vector3& SpherePoint) const
{

	return Sphere.Distance(*this, SpherePoint, fSegmentParameter);
}
/*----------------------------------------------------------------*/
VSREAL Segment3::Distance(const Plane3& Plane, Matrix::Math::Vector3& SegmentPoint, Matrix::Math::Vector3& PlanePoint) const
{
	return Plane.Distance(*this, PlanePoint, SegmentPoint);
}
/*----------------------------------------------------------------*/
VSREAL Segment3::SquaredDistance(const AABB3& AABB, VSREAL& fSegmentParameter, VSREAL fAABBParameter[3]) const
{
	VSREAL sqrDist = Ray3::SquaredDistance(AABB, fSegmentParameter, fAABBParameter);
	if (fSegmentParameter > m_fLen)
	{
		fSegmentParameter = m_fLen;
		sqrDist = AABB.SquaredDistance(m_End, fAABBParameter);
	}

	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Segment3::SquaredDistance(const Polygon3& Polygon, VSREAL& fSegmentParameter,
	int& IndexTriangle,
	VSREAL fTriangleParameter[3]) const
{

	return Polygon.SquaredDistance(*this, IndexTriangle, fTriangleParameter, fSegmentParameter);
}

/*----------------------------------------------------------------*/
int Segment3::RelationWith(const Triangle3& Triangle, bool bCull, VSREAL& fSegmentParameter,
	VSREAL fTriangleParameter[3]) const
{
	if (Ray3::RelationWith(Triangle, bCull, fSegmentParameter, fTriangleParameter) == IT_NoIntersect)
		return IT_NoIntersect;
	if (fSegmentParameter > m_fLen)
		return IT_NoIntersect;
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Segment3::RelationWith(const Plane3& Plane, bool bCull, VSREAL& fSegmentParameter) const
{
	int iFlag = Ray3::RelationWith(Plane, bCull, fSegmentParameter);
	if (iFlag != IT_Intersect)
		return iFlag;
	if (fSegmentParameter > m_fLen)
	{
		return Point3(m_Orig).RelationWith(Plane);
	}
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Segment3::RelationWith(const Rectangle3& Rectangle, bool bCull, VSREAL& fSegmentParameter,
	VSREAL fRectangleParameter[2]) const
{

	if (Ray3::RelationWith(Rectangle, bCull, fSegmentParameter, fRectangleParameter) == IT_NoIntersect)
		return IT_NoIntersect;
	if (fSegmentParameter > m_fLen)
		return IT_NoIntersect;
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Segment3::RelationWith(const OBB3& OBB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar) const
{
	if (Ray3::RelationWith(OBB, Quantity, tNear, tFar) == IT_NoIntersect)
		return IT_NoIntersect;
	if (tNear > m_fLen)
	{
		Quantity = 0;
		if (Point3(m_Orig).RelationWith(OBB) != IT_Out)
			return IT_In;
		return IT_NoIntersect;
	}

	if (tFar > m_fLen)
	{
		Quantity = 1;
		tFar = tNear;
	}
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Segment3::RelationWith(const Sphere3& sphere, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar) const
{
	if (Ray3::RelationWith(sphere, Quantity, tNear, tFar) == IT_NoIntersect)
		return IT_NoIntersect;
	if (tNear > m_fLen)
	{
		Quantity = 0;
		if (Point3(m_Orig).RelationWith(sphere) != IT_Out)
			return IT_In;
		return IT_NoIntersect;
	}

	if (tFar > m_fLen)
	{
		Quantity = 1;
		tFar = tNear;
	}
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Segment3::RelationWith(const AABB3& AABB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar) const
{

	if (Ray3::RelationWith(AABB, Quantity, tNear, tFar) == IT_NoIntersect)
		return IT_NoIntersect;
	if (tNear > m_fLen)
	{
		Quantity = 0;
		if (Point3(m_Orig).RelationWith(AABB) != IT_Out)
			return IT_In;
		return IT_NoIntersect;
	}

	if (tFar > m_fLen)
	{
		Quantity = 1;
		tFar = tNear;
	}
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Segment3::RelationWith(const Polygon3& Polygon, VSREAL& fSegmentParameter,
	bool bCull, int& iIndexTriangle, VSREAL fTriangleParameter[3]) const
{

	return Polygon.RelationWith(*this, bCull, iIndexTriangle, fTriangleParameter, fSegmentParameter);
}