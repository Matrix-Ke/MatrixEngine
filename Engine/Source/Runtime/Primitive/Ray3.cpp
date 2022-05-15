#include "Ray3.h"
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
Ray3::Ray3()
{
}
/*----------------------------------------------------------------*/
Ray3::Ray3(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& Dir)
{
	Set(Orig, Dir);
}
/*----------------------------------------------------------------*/
Ray3::~Ray3()
{
}

/*----------------------------------------------------------------*/
bool Ray3::GetParameter(const Matrix::Math::Vector3& Point, VSREAL& fRayParameter) const
{
	if (!Matrix::Primitive::Line3::GetParameter(Point, fRayParameter))
		return 0;

	if (fRayParameter < 0)
		return 0;

	return 1;
}
/*----------------------------------------------------------------*/
void Ray3::Transform(const Ray3& Ray, const Matrix::Math::Matrix4& Mat)
{

	Matrix::Primitive::Line3::Transform(Ray, Mat);
}


VSREAL Ray3::SquaredDistance(const Matrix::Math::Vector3& Point, VSREAL& fLineParameter) const
{
	VSREAL fSqDis = Matrix::Primitive::Line3::SquaredDistance(Point, fLineParameter);
	if (fLineParameter >= 0)
		return fSqDis;
	else
	{
		fLineParameter = 0;
		Matrix::Math::Vector3 Diff;
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
		Matrix::Math::Vector3 End = Segment.GetEnd();
		sqrDist = SquaredDistance(End, fRayParameter);
	}
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Ray3::SquaredDistance(const Triangle3& Triangle, VSREAL& fRayParameter, VSREAL fTriangleParameter[3]) const
{
	VSREAL sqrDist = Matrix::Primitive::Line3::SquaredDistance(Triangle, fRayParameter, fTriangleParameter);
	if (fRayParameter < 0)
	{
		fRayParameter = 0;
		//sqrDist = Triangle.SquaredDistance(m_Orig, )
		sqrDist = Point3(m_Orig).SquaredDistance(Triangle, fTriangleParameter);
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
		sqrDist = Point3(m_Orig).SquaredDistance(Rectangle, fRectangleParameter);
	}

	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Ray3::SquaredDistance(const OBB3& OBB, VSREAL& fRayParameter, VSREAL fOBBParameter[3]) const
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
VSREAL Ray3::Distance(const Sphere3& Sphere, VSREAL& fRayParameter, Matrix::Math::Vector3& SpherePoint) const
{
	return Sphere.Distance(*this, SpherePoint, fRayParameter);
}
/*----------------------------------------------------------------*/
VSREAL Ray3::Distance(const Plane3& Plane, Matrix::Math::Vector3& RayPoint, Matrix::Math::Vector3& PlanePoint) const
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


int Ray3::RelationWith(const Triangle3& Triangle, bool bCull, VSREAL& fRayParameter,
	VSREAL fTriangleParameter[3]) const
{
	if (Matrix::Primitive::Line3::RelationWith(Triangle, bCull, fRayParameter, fTriangleParameter) == IT_NoIntersect)
		return IT_NoIntersect;
	if (fRayParameter < 0.0f)
		return IT_NoIntersect;
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Ray3::RelationWith(const Plane3& Plane, bool bCull, VSREAL& fRayParameter) const
{
	int iFlag = Matrix::Primitive::Line3::RelationWith(Plane, bCull, fRayParameter);
	if (iFlag != IT_Intersect)
		return iFlag;
	if (fRayParameter < 0.0f)
	{
		iFlag = Point3(m_Orig).RelationWith(Plane);
		return iFlag;
	}
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Ray3::RelationWith(const Rectangle3& Rectangle, bool bCull, VSREAL& fRayParameter,
	VSREAL fRectangleParameter[2]) const
{
	if (Matrix::Primitive::Line3::RelationWith(Rectangle, bCull, fRayParameter, fRectangleParameter) == IT_NoIntersect)
		return IT_NoIntersect;
	if (fRayParameter < 0.0f)
		return IT_NoIntersect;

	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Ray3::RelationWith(const OBB3& OBB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar) const
{
	if (Matrix::Primitive::Line3::RelationWith(OBB, Quantity, tNear, tFar) == IT_NoIntersect)
		return IT_NoIntersect;
	if (tFar < 0.0f)
	{
		Quantity = 0;
		return IT_NoIntersect;
	}
	if (tNear < 0.0f)
	{
		Quantity = 1;
		tNear = tFar;
	}
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Ray3::RelationWith(const Sphere3& sphere, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar) const
{
	if (Matrix::Primitive::Line3::RelationWith(sphere, Quantity, tNear, tFar) == IT_NoIntersect)
		return IT_NoIntersect;
	if (tFar < 0.0f)
	{
		Quantity = 0;
		return IT_NoIntersect;
	}
	if (tNear < 0.0f)
	{
		Quantity = 1;
		tNear = tFar;
	}
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Ray3::RelationWith(const AABB3& AABB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar) const
{
	if (Matrix::Primitive::Line3::RelationWith(AABB, Quantity, tNear, tFar) == IT_NoIntersect)
		return IT_NoIntersect;
	if (tFar < 0.0f)
	{
		Quantity = 0;
		return IT_NoIntersect;
	}
	if (tNear < 0.0f)
	{
		Quantity = 1;
		tNear = tFar;
	}
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Ray3::RelationWith(const Polygon3& Polygon, VSREAL& fRayParameter,
	bool bCull, int& iIndexTriangle, VSREAL fTriangleParameter[3]) const
{

	return Polygon.RelationWith(*this, bCull, iIndexTriangle, fTriangleParameter, fRayParameter);
}