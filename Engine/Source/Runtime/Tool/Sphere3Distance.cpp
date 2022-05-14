#include "Sphere3.h"
#include "Math.h"
#include "Segment3.h"
#include "AABB3.h"
#include "Polygon3.h"
using namespace Matrix;
/*----------------------------------------------------------------*/
VSREAL Sphere3::Distance(const Matrix::Math::VSVector3& Point, Matrix::Math::VSVector3& SpherePoint) const
{
	VSREAL sqrDist = Point.SquaredDistance(m_Center);

	sqrDist = SQRT(sqrDist);
	sqrDist = sqrDist - m_fRadius;

	Line3 Line(m_Center, Point);

	SpherePoint = Line.GetParameterPoint(m_fRadius);
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Sphere3::Distance(const Line3& Line, Matrix::Math::VSVector3& SpherePoint, VSREAL& fLineParameter) const
{

	VSREAL sqrDist = Line.SquaredDistance(m_Center, fLineParameter);
	sqrDist = SQRT(sqrDist);
	sqrDist = sqrDist - m_fRadius;

	Line3 LineTemp(m_Center, Line.GetParameterPoint(fLineParameter));

	SpherePoint = LineTemp.GetParameterPoint(m_fRadius);
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Sphere3::Distance(const Ray3& Ray, Matrix::Math::VSVector3& SpherePoint, VSREAL& fRayParameter) const
{
	VSREAL sqrDist = Ray.SquaredDistance(m_Center, fRayParameter);

	sqrDist = SQRT(sqrDist);
	sqrDist = sqrDist - m_fRadius;

	Line3 LineTemp(m_Center, Ray.GetParameterPoint(fRayParameter));

	SpherePoint = LineTemp.GetParameterPoint(m_fRadius);
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Sphere3::Distance(const Segment3& Segment, Matrix::Math::VSVector3& SpherePoint, VSREAL& fSegmentParameter) const
{
	VSREAL sqrDist = Segment.SquaredDistance(m_Center, fSegmentParameter);

	sqrDist = SQRT(sqrDist);
	sqrDist = sqrDist - m_fRadius;

	Line3 LineTemp(m_Center, Segment.GetParameterPoint(fSegmentParameter));

	SpherePoint = LineTemp.GetParameterPoint(m_fRadius);
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Sphere3::Distance(const VSOBB3& OBB, Matrix::Math::VSVector3& SpherePoint, VSREAL fOBBParameter[3]) const
{
	VSREAL sqrDist = OBB.SquaredDistance(m_Center, fOBBParameter);

	sqrDist = SQRT(sqrDist);
	sqrDist = sqrDist - m_fRadius;

	Line3 LineTemp(m_Center, OBB.GetParameterPoint(fOBBParameter));

	SpherePoint = LineTemp.GetParameterPoint(m_fRadius);
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Sphere3::Distance(const Plane3& Plane, Matrix::Math::VSVector3& SpherePoint) const
{
	Matrix::Math::VSVector3 PlanePoint;
	VSREAL sqrDist = Plane.Distance(m_Center, PlanePoint);

	sqrDist = sqrDist - m_fRadius;

	Line3 LineTemp(m_Center, PlanePoint);

	SpherePoint = LineTemp.GetParameterPoint(m_fRadius);
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Sphere3::Distance(const Rectangle3& Rectangle, Matrix::Math::VSVector3& SpherePoint, VSREAL fRectangleParameter[2]) const
{
	VSREAL sqrDist = Rectangle.SquaredDistance(m_Center, fRectangleParameter);

	sqrDist = SQRT(sqrDist);
	sqrDist = sqrDist - m_fRadius;

	Line3 LineTemp(m_Center, Rectangle.GetParameterPoint(fRectangleParameter));

	SpherePoint = LineTemp.GetParameterPoint(m_fRadius);
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Sphere3::Distance(const VSTriangle3 Triangle, Matrix::Math::VSVector3& SpherePoint, VSREAL fTriangleParameter[3]) const
{
	VSREAL sqrDist = Triangle.SquaredDistance(m_Center, fTriangleParameter);

	sqrDist = SQRT(sqrDist);
	sqrDist = sqrDist - m_fRadius;

	Line3 LineTemp(m_Center, Triangle.GetParameterPoint(fTriangleParameter));

	SpherePoint = LineTemp.GetParameterPoint(m_fRadius);
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Sphere3::Distance(const AABB3& AABB, Matrix::Math::VSVector3& SpherePoint, VSREAL fAABBParameter[3]) const
{
	VSREAL sqrDist = AABB.SquaredDistance(m_Center, fAABBParameter);

	sqrDist = SQRT(sqrDist);
	sqrDist = sqrDist - m_fRadius;

	Line3 LineTemp(m_Center, AABB.GetParameterPoint(fAABBParameter));

	SpherePoint = LineTemp.GetParameterPoint(m_fRadius);
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Sphere3::Distance(const Polygon3& Polygon, Matrix::Math::VSVector3& SpherePoint, int& IndexTriangle,
	VSREAL fTriangleParameter[3]) const
{

	return Polygon.Distance(*this, IndexTriangle, fTriangleParameter, SpherePoint);
}