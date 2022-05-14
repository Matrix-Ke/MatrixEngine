#include "Ray3.h"
#include "Segment3.h"
#include "AABB3.h"
#include "Polygon3.h"
using namespace Matrix;
/*----------------------------------------------------------------*/
VSREAL Ray3::SquaredDistance(const Matrix::Math::VSVector3& Point, VSREAL& fLineParameter) const
{
	VSREAL fSqDis = Matrix::Primitive::Line3::SquaredDistance(Point, fLineParameter);
	if (fLineParameter >= 0)
		return fSqDis;
	else
	{
		fLineParameter = 0;
		Matrix::Math::VSVector3 Diff;
		Diff = Point - m_Orig;
		return Diff.GetSqrLength();
	}
}
/*----------------------------------------------------------------*/
VSREAL Ray3::SquaredDistance(const Line3& Line, VSREAL& fRayParameter, VSREAL& fLineParameter) const
{
	return Line.SquaredDistance(*this, fLineParameter, fRayParameter);
}
/*----------------------------------------------------------------*/
VSREAL Ray3::SquaredDistance(const Ray3& Ray, VSREAL& fRay1Parameter, VSREAL& fRay2Parameter) const
{
	const Line3 Line = Ray;
	VSREAL sqrDist = SquaredDistance(Line, fRay1Parameter, fRay2Parameter);
	if (fRay2Parameter < 0)
	{
		fRay2Parameter = 0;
		sqrDist = SquaredDistance(Ray.m_Orig, fRay1Parameter);
	}

	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Ray3::SquaredDistance(const Segment3& Segment, VSREAL& fRayParameter, VSREAL& fSegmentParameter) const
{

	const Ray3 Ray = Segment;
	VSREAL sqrDist = SquaredDistance(Ray, fRayParameter, fSegmentParameter);
	VSREAL fLen = Segment.GetLen();
	if (fSegmentParameter > fLen)
	{
		fSegmentParameter = fLen;
		Matrix::Math::VSVector3 End = Segment.GetEnd();
		sqrDist = SquaredDistance(End, fRayParameter);
	}
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Ray3::SquaredDistance(const VSTriangle3& Triangle, VSREAL& fRayParameter, VSREAL fTriangleParameter[3]) const
{
	VSREAL sqrDist = Matrix::Primitive::Line3::SquaredDistance(Triangle, fRayParameter, fTriangleParameter);
	if (fRayParameter < 0)
	{
		fRayParameter = 0;
		sqrDist = m_Orig.SquaredDistance(Triangle, fTriangleParameter);
	}

	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Ray3::SquaredDistance(const Rectangle3& Rectangle, VSREAL& fRayParameter, VSREAL fRectangleParameter[2]) const
{
	VSREAL sqrDist = Matrix::Primitive::Line3::SquaredDistance(Rectangle, fRayParameter, fRectangleParameter);
	if (fRayParameter < 0)
	{
		fRayParameter = 0;
		sqrDist = m_Orig.SquaredDistance(Rectangle, fRectangleParameter);
	}

	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Ray3::SquaredDistance(const VSOBB3& OBB, VSREAL& fRayParameter, VSREAL fOBBParameter[3]) const
{
	VSREAL sqrDist = Matrix::Primitive::Line3::SquaredDistance(OBB, fRayParameter, fOBBParameter);
	if (fRayParameter < 0)
	{
		fRayParameter = 0;
		sqrDist = OBB.SquaredDistance(m_Orig, fOBBParameter);
	}

	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Ray3::Distance(const Sphere3& Sphere, VSREAL& fRayParameter, Matrix::Math::VSVector3& SpherePoint) const
{
	return Sphere.Distance(*this, SpherePoint, fRayParameter);
}
/*----------------------------------------------------------------*/
VSREAL Ray3::Distance(const Plane3& Plane, Matrix::Math::VSVector3& RayPoint, Matrix::Math::VSVector3& PlanePoint) const
{
	return Plane.Distance(*this, PlanePoint, RayPoint);
}
/*----------------------------------------------------------------*/
VSREAL Ray3::SquaredDistance(const AABB3& AABB, VSREAL& fRayParameter, VSREAL fAABBParameter[3]) const
{
	VSREAL sqrDist = Matrix::Primitive::Line3::SquaredDistance(AABB, fRayParameter, fAABBParameter);
	if (fRayParameter < 0)
	{
		fRayParameter = 0;
		sqrDist = AABB.SquaredDistance(m_Orig, fAABBParameter);
	}

	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Ray3::SquaredDistance(const Polygon3& Polygon, VSREAL& fRayParameter,
	int& IndexTriangle,
	VSREAL fTriangleParameter[3]) const
{

	return Polygon.SquaredDistance(*this, IndexTriangle, fTriangleParameter, fRayParameter);
}