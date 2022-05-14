#include "Segment3.h"
#include "AABB3.h"
#include "Polygon3.h"
using namespace Matrix;
/*----------------------------------------------------------------*/
VSREAL Segment3::SquaredDistance(const Matrix::Math::VSVector3& Point, VSREAL& fSegmentParameter) const
{
	VSREAL SqDis = Ray3::SquaredDistance(Point, fSegmentParameter);
	if (fSegmentParameter > m_fLen)
	{
		fSegmentParameter = m_fLen;
		Matrix::Math::VSVector3 Diff;
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
		Matrix::Math::VSVector3 End = Segment.GetEnd();
		sqrDist = SquaredDistance(End, fSegment1Parameter);
	}
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Segment3::SquaredDistance(const VSTriangle3& Triangle, VSREAL& fSegmentParameter, VSREAL fTriangleParameter[3]) const
{
	VSREAL sqrDist = Ray3::SquaredDistance(Triangle, fSegmentParameter, fTriangleParameter);

	if (fSegmentParameter > m_fLen)
	{
		fSegmentParameter = m_fLen;
		sqrDist = m_End.SquaredDistance(Triangle, fTriangleParameter);
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
		sqrDist = m_End.SquaredDistance(Rectangle, fRectangleParameter);
	}

	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Segment3::SquaredDistance(const VSOBB3& OBB, VSREAL& fSegmentParameter, VSREAL fOBBParameter[3]) const
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
VSREAL Segment3::Distance(const Sphere3& Sphere, VSREAL& fSegmentParameter, Matrix::Math::VSVector3& SpherePoint) const
{

	return Sphere.Distance(*this, SpherePoint, fSegmentParameter);
}
/*----------------------------------------------------------------*/
VSREAL Segment3::Distance(const Plane3& Plane, Matrix::Math::VSVector3& SegmentPoint, Matrix::Math::VSVector3& PlanePoint) const
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