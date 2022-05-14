#include "AABB3.h"
#include "Math.h"
#include "Matrix3X3.h"
#include "Line3.h"
#include "Ray3.h"
#include "Rectangle3.h"
#include "Segment3.h"
#include "..\VSDataStruct\Array.h"
using namespace Matrix;
/*----------------------------------------------------------------*/
int AABB3::RelationWith(const Matrix::Math::VSVector3& Point) const
{
	Matrix::Math::VSVector3 PointTemp = Point - m_Center;
	VSREAL fDiffX = ABS(PointTemp.x) - m_fA[0];
	VSREAL fDiffY = ABS(PointTemp.y) - m_fA[1];
	VSREAL fDiffZ = ABS(PointTemp.z) - m_fA[2];

	if (fDiffX > EPSILON_E4 || fDiffY > EPSILON_E4 || fDiffZ > EPSILON_E4)
		return VSOUT;

	if (fDiffX < -EPSILON_E4 || fDiffY < -EPSILON_E4 || fDiffZ < -EPSILON_E4)
		return VSIN;

	return VSON;
}
/*----------------------------------------------------------------*/
int AABB3::RelationWith(const Line3& Line, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar) const
{
	return Line.RelationWith(*this, Quantity, tNear, tFar);
}
/*----------------------------------------------------------------*/
int AABB3::RelationWith(const Ray3& Ray, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar) const
{

	return Ray.RelationWith(*this, Quantity, tNear, tFar);
}
/*----------------------------------------------------------------*/
int AABB3::RelationWith(const Segment3& Segment, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar) const
{
	return Segment.RelationWith(*this, Quantity, tNear, tFar);
}
/*----------------------------------------------------------------*/
int AABB3::RelationWith(const Plane3& Plane) const
{
	Matrix::Math::VSVector3 N = Plane.GetN();
	VSREAL fD = Plane.GetfD();
	Matrix::Math::VSVector3 MinTemp, MaxTemp;
	// x
	if (N.x >= 0.0f)
	{
		MinTemp.x = m_Min.x;
		MaxTemp.x = m_Max.x;
	}
	else
	{
		MinTemp.x = m_Max.x;
		MaxTemp.x = m_Min.x;
	}
	// y
	if (N.y >= 0.0f)
	{
		MinTemp.y = m_Min.y;
		MaxTemp.y = m_Max.y;
	}
	else
	{
		MinTemp.y = m_Max.y;
		MaxTemp.y = m_Min.y;
	}
	// z
	if (N.z >= 0.0f)
	{
		MinTemp.z = m_Min.z;
		MaxTemp.z = m_Max.z;
	}
	else
	{
		MinTemp.z = m_Max.z;
		MaxTemp.z = m_Min.z;
	}

	if ((N.Dot(MinTemp) + fD) > 0.0f)
		return VSFRONT;
	else if ((N.Dot(MaxTemp) + fD) < 0.0f)
		return VSBACK;
	else
		return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int AABB3::RelationWith(const VSTriangle3& Triangle) const
{
	return Triangle.RelationWith(*this);
}
/*----------------------------------------------------------------*/
int AABB3::RelationWith(const Rectangle3& Rectangle) const
{
	return Rectangle.RelationWith(*this);
}
/*----------------------------------------------------------------*/
int AABB3::RelationWith(const AABB3& AABB) const
{
	if ((m_Min.x > AABB.m_Max.x) || (AABB.m_Min.x > m_Max.x))
		return VSNOINTERSECT;
	if ((m_Min.y > AABB.m_Max.y) || (AABB.m_Min.y > m_Max.y))
		return VSNOINTERSECT;
	if ((m_Min.z > AABB.m_Max.z) || (AABB.m_Min.z > m_Max.z))
		return VSNOINTERSECT;
	return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int AABB3::RelationWith(const Sphere3& Sphere) const
{
	VSREAL fAABBParameter[3];
	VSREAL Dist = Sphere.m_Center.SquaredDistance(*this, fAABBParameter);
	Dist = SQRT(Dist);
	if (Dist - Sphere.m_fRadius < 0.0f)
		return VSINTERSECT;

	return VSNOINTERSECT;
}
bool AABB3::GetIntersect(AABB3& AABB, AABB3& OutAABB) const
{
	if (RelationWith(AABB) == VSINTERSECT)
	{

		VSArrayOrder<VSREAL> XArray;
		XArray.AddElement(GetMinPoint().x);
		XArray.AddElement(GetMaxPoint().x);
		XArray.AddElement(AABB.GetMinPoint().x);
		XArray.AddElement(AABB.GetMaxPoint().x);

		VSArrayOrder<VSREAL> YArray;
		YArray.AddElement(GetMinPoint().y);
		YArray.AddElement(GetMaxPoint().y);
		YArray.AddElement(AABB.GetMinPoint().y);
		YArray.AddElement(AABB.GetMaxPoint().y);

		VSArrayOrder<VSREAL> ZArray;
		ZArray.AddElement(GetMinPoint().z);
		ZArray.AddElement(GetMaxPoint().z);
		ZArray.AddElement(AABB.GetMinPoint().z);
		ZArray.AddElement(AABB.GetMaxPoint().z);

		OutAABB.Set(Matrix::Math::VSVector3(XArray[2], YArray[2], ZArray[2]), Matrix::Math::VSVector3(XArray[1], YArray[1], ZArray[1]));
		return true;
	}

	return false;
}