#include "Plane3.h"
#include "Line3.h"
#include "Math/Vector3.h"
#include "Math/Matrix3X3W.h"
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
Plane3::Plane3()
{
	m_fD = 0.0f;
}
/*----------------------------------------------------------------*/
Plane3::Plane3(const Matrix::Math::Vector3& N, VSREAL fD)
{
	Set(N, fD);
}
/*----------------------------------------------------------------*/
Plane3::Plane3(const Matrix::Math::Vector3& N, const Matrix::Math::Vector3& P)
{
	Set(N, P);
}
/*----------------------------------------------------------------*/
Plane3::Plane3(const Matrix::Math::Vector3& P0, const Matrix::Math::Vector3& P1, const Matrix::Math::Vector3& P2)
{
	Set(P0, P1, P2);
}
/*----------------------------------------------------------------*/
Plane3::Plane3(const Matrix::Math::Vector3 Point[3])
{
	Set(Point[0], Point[1], Point[2]);
}
/*----------------------------------------------------------------*/
void Plane3::Transform(const Plane3& Plane, const Matrix::Math::Matrix4& Mat)
{
	Matrix::Math::Vector4 Temp(m_N.x, m_N.y, m_N.z, m_fD);

	Matrix::Math::Matrix4 Inv;
	Inv.InverseOf(Mat);
	Matrix::Math::Matrix4 Transpose;
	Transpose.TransposeOf(Inv);
	Matrix::Math::Vector4 Resoult = Temp * Transpose;
	Set(Matrix::Math::Vector3(Resoult.x, Resoult.y, Resoult.z), Resoult.w);
}
Matrix::Math::Vector3 Plane3::ReflectDir(const Matrix::Math::Vector3& Dir) const
{
	Matrix::Math::Vector3 TempN = m_N * (-1.0f);

	return Dir - m_N * Dir.Dot(m_N) * 2.0f;
}
void Plane3::GetReverse(Plane3& OutPlane) const
{
	OutPlane.Set(m_N * (-1.0f), -m_fD);
}


/*----------------------------------------------------------------*/
VSREAL Plane3::Distance(const Matrix::Math::Vector3& Point, Matrix::Math::Vector3& PlanePoint) const
{

	VSREAL Dist = Math::ABS((m_N.Dot(Point)) - m_fD);

	Line3 Line(Point, m_N * (-1));
	PlanePoint = Line.GetParameterPoint(Dist);

	return Dist;
}
/*----------------------------------------------------------------*/
VSREAL Plane3::Distance(const Sphere3& Sphere, Matrix::Math::Vector3& SpherePoint) const
{
	return Sphere.Distance(*this, SpherePoint);
}
/*----------------------------------------------------------------*/
VSREAL Plane3::Distance(const Line3& Line, Matrix::Math::Vector3& PlanePoint, Matrix::Math::Vector3& LinePoint) const
{
	VSREAL fDot = Line.GetDir().Dot(m_N);
	if (Math::ABS(fDot) < EPSILON_E4)
	{
		LinePoint = Line.GetOrig();
		return LinePoint.Distance(*this, PlanePoint);
	}
	else
		return 0;
}
/*----------------------------------------------------------------*/
VSREAL Plane3::Distance(const Ray3& Ray, Matrix::Math::Vector3& PlanePoint, Matrix::Math::Vector3& RayPoint) const
{
	VSREAL fDot = Ray.GetDir().Dot(m_N);
	RayPoint = Ray.GetOrig();

	VSREAL f = RayPoint.Dot(m_N) + m_fD;
	if (fDot * f > 0)
		return RayPoint.Distance(*this, PlanePoint);
	else
		return 0;
}
/*----------------------------------------------------------------*/
VSREAL Plane3::Distance(const Segment3& Segment, Matrix::Math::Vector3& PlanePoint, Matrix::Math::Vector3& SegmentPoint) const
{

	Matrix::Math::Vector3 SegmentOrig = Segment.GetOrig();
	Matrix::Math::Vector3 SegmentEnd = Segment.GetEnd();
	VSREAL f0 = SegmentOrig.Dot(m_N) + m_fD;
	VSREAL f1 = SegmentEnd.Dot(m_N) + m_fD;

	if (f0 * f1 > 0)
	{
		Matrix::Math::Vector3 PPoint;
		VSREAL dist = SegmentOrig.Distance(*this, PPoint);
		SegmentPoint = SegmentOrig;
		PlanePoint = PPoint;
		VSREAL distTemp = SegmentEnd.Distance(*this, PPoint);
		if (dist > distTemp)
		{
			dist = distTemp;
			SegmentPoint = SegmentEnd;
			PlanePoint = PPoint;
		}
		return dist;
	}
	else
		return 0;
}
/*----------------------------------------------------------------*/
VSREAL Plane3::Distance(const Plane3& Plane, Matrix::Math::Vector3& Plane1Point, Matrix::Math::Vector3& Plane2Point) const
{
	if (m_N.IsParallel(Plane.m_N))
	{
		Plane1Point = GetPoint();
		return Plane1Point.Distance(Plane, Plane2Point);
	}
	else
		return 0;
}
/*----------------------------------------------------------------*/
VSREAL Plane3::Distance(const Triangle3& Triangle, Matrix::Math::Vector3& PlanePoint, Matrix::Math::Vector3& TrianglePoint) const
{
	/*int i[3];
	Matrix::Math::Vector3 Point[3];
	Triangle.GetPoint(Point);
	i[0] = RelationWith(Point[0]);
	i[1] = RelationWith(Point[1]);
	i[2] = RelationWith(Point[2]);

	if((i[0] == i[1]) && (i[1] == i[2]))
	{
		VSREAL dist[3],distTemp;
		Matrix::Math::Vector3 PlanePointTemp[3];
		dist[0] = Point[0].Distance(*this,PlanePointTemp[0]);
		dist[1] = Point[1].Distance(*this,PlanePointTemp[1]);
		dist[2] = Point[2].Distance(*this,PlanePointTemp[2]);
		distTemp = dist[0];
		PlanePoint = PlanePointTemp[0];
		TrianglePoint = Point[0];
		if(distTemp > dist[1])
		{
			distTemp = dist[1];
			PlanePoint = PlanePointTemp[1];
			TrianglePoint = Point[1];
		}
		if(distTemp > dist[2])
		{
			distTemp = dist[2];
			PlanePoint = PlanePointTemp[2];
			TrianglePoint = Point[2];
		}
		return distTemp;
	}
	return 0;*/
	Matrix::Math::Vector3 Point[3];
	Triangle.GetPoint(Point);

	VSREAL dist[3], distTemp;
	Matrix::Math::Vector3 PlanePointTemp[3];
	dist[0] = Point[0].Distance(*this, PlanePointTemp[0]);
	dist[1] = Point[1].Distance(*this, PlanePointTemp[1]);
	dist[2] = Point[2].Distance(*this, PlanePointTemp[2]);
	distTemp = dist[0];
	PlanePoint = PlanePointTemp[0];
	TrianglePoint = Point[0];
	if (distTemp > dist[1])
	{
		distTemp = dist[1];
		PlanePoint = PlanePointTemp[1];
		TrianglePoint = Point[1];
	}
	if (distTemp > dist[2])
	{
		distTemp = dist[2];
		PlanePoint = PlanePointTemp[2];
		TrianglePoint = Point[2];
	}
	return distTemp;
}
/*----------------------------------------------------------------*/
VSREAL Plane3::Distance(const Rectangle3& Rectangle, Matrix::Math::Vector3& PlanePoint, Matrix::Math::Vector3& RectanglePoint) const
{
	/*int f[4];
	Matrix::Math::Vector3 Point[4];
	Rectangle.GetPoint(Point);
	for(int i = 0 ; i < 4 ; i++)
	{
		f[i] = RelationWith(Point[i]);
	}

	if((f[0] == f[1]) && (f[1] == f[2]) && (f[2] == f[3]))
	{
		VSREAL dist[4],distTemp;
		Matrix::Math::Vector3 PlanePointTemp[4];
		for(int i = 0 ; i < 4 ; i++)
			dist[i] = Point[i].Distance(*this,PlanePointTemp[i]);

		distTemp = dist[0];
		PlanePoint = PlanePointTemp[0];
		RectanglePoint = Point[0];
		for(int i = 1 ; i < 4 ; i++)
		{
			if(distTemp > dist[i])
			{
				distTemp = dist[i];
				PlanePoint = PlanePointTemp[i];
				RectanglePoint = Point[i];
			}
		}
		return distTemp;
	}
	return 0;*/

	Matrix::Math::Vector3 Point[4];
	Rectangle.GetPoint(Point);

	VSREAL dist[4], distTemp;
	Matrix::Math::Vector3 PlanePointTemp[4];
	for (int i = 0; i < 4; i++)
		dist[i] = Point[i].Distance(*this, PlanePointTemp[i]);

	distTemp = dist[0];
	PlanePoint = PlanePointTemp[0];
	RectanglePoint = Point[0];
	for (int i = 1; i < 4; i++)
	{
		if (distTemp > dist[i])
		{
			distTemp = dist[i];
			PlanePoint = PlanePointTemp[i];
			RectanglePoint = Point[i];
		}
	}
	return distTemp;
}
/*----------------------------------------------------------------*/
VSREAL Plane3::Distance(const OBB3& OBB, Matrix::Math::Vector3& PlanePoint, Matrix::Math::Vector3& OBBPoint) const
{
	/*int f[8];
	Matrix::Math::Vector3 Point[8];
	OBB.GetPoint(Point);
	for(int i = 0 ; i < 8 ; i++)
	{
		f[i] = RelationWith(Point[i]);
	}

	if((f[0] == f[1]) && (f[1] == f[2]) && (f[2] == f[3]) && (f[3] == f[4])
			&& (f[4] == f[6]) && (f[5] == f[6]) && (f[6] == f[7]))
	{
		VSREAL dist[4],distTemp;
		Matrix::Math::Vector3 PlanePointTemp[8];
		for(int i = 0 ; i < 8 ; i++)
			dist[i] = Point[i].Distance(*this,PlanePointTemp[i]);

		distTemp = dist[0];
		PlanePoint = PlanePointTemp[0];
		OBBPoint = Point[0];
		for(int i = 1 ; i < 8 ; i++)
		{
			if(distTemp > dist[i])
			{
				distTemp = dist[i];
				PlanePoint = PlanePointTemp[i];
				OBBPoint = Point[i];
			}
		}
		return distTemp;
	}
	return 0;*/

	Matrix::Math::Vector3 Point[8];
	OBB.GetPoint(Point);

	VSREAL dist[4], distTemp;
	Matrix::Math::Vector3 PlanePointTemp[8];
	for (int i = 0; i < 8; i++)
		dist[i] = Point[i].Distance(*this, PlanePointTemp[i]);

	distTemp = dist[0];
	PlanePoint = PlanePointTemp[0];
	OBBPoint = Point[0];
	for (int i = 1; i < 8; i++)
	{
		if (distTemp > dist[i])
		{
			distTemp = dist[i];
			PlanePoint = PlanePointTemp[i];
			OBBPoint = Point[i];
		}
	}
	return distTemp;
}
/*----------------------------------------------------------------*/
VSREAL Plane3::Distance(const AABB3& AABB, Matrix::Math::Vector3& PlanePoint, Matrix::Math::Vector3& AABBPoint) const
{
	/*int f[8];
	Matrix::Math::Vector3 Point[8];
	AABB.GetPoint(Point);
	for(int i = 0 ; i < 8 ; i++)
	{
		f[i] = RelationWith(Point[i]);
	}

	if((f[0] == f[1]) && (f[1] == f[2]) && (f[2] == f[3]) && (f[3] == f[4])
		&& (f[4] == f[6]) && (f[5] == f[6]) && (f[6] == f[7]))
	{
		VSREAL dist[4],distTemp;
		Matrix::Math::Vector3 PlanePointTemp[8];
		for(int i = 0 ; i < 8 ; i++)
			dist[i] = Point[i].Distance(*this,PlanePointTemp[i]);

		distTemp = dist[0];
		PlanePoint = PlanePointTemp[0];
		AABBPoint = Point[0];
		for(int i = 1 ; i < 8 ; i++)
		{
			if(distTemp > dist[i])
			{
				distTemp = dist[i];
				PlanePoint = PlanePointTemp[i];
				AABBPoint = Point[i];
			}
		}
		return distTemp;
	}
	return 0;*/

	Matrix::Math::Vector3 Point[8];
	AABB.GetPoint(Point);

	VSREAL dist[4], distTemp;
	Matrix::Math::Vector3 PlanePointTemp[8];
	for (int i = 0; i < 8; i++)
		dist[i] = Point[i].Distance(*this, PlanePointTemp[i]);

	distTemp = dist[0];
	PlanePoint = PlanePointTemp[0];
	AABBPoint = Point[0];
	for (int i = 1; i < 8; i++)
	{
		if (distTemp > dist[i])
		{
			distTemp = dist[i];
			PlanePoint = PlanePointTemp[i];
			AABBPoint = Point[i];
		}
	}
	return distTemp;
}
/*----------------------------------------------------------------*/
VSREAL Plane3::Distance(const Polygon3& Polygon, Matrix::Math::Vector3& PlanePoint, int& IndexTriangle,
	Matrix::Math::Vector3& TrianglePoint) const
{

	return Polygon.Distance(*this, IndexTriangle, TrianglePoint, PlanePoint);
}


int Plane3::RelationWith(const Matrix::Math::Vector3& Point) const
{
	VSREAL f = (Point.Dot(m_N)) + m_fD;

	if (f > EPSILON_E4)
		return IT_Front;
	if (f < -EPSILON_E4)
		return IT_Back;
	return IT_On;
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
int Plane3::RelationWith(const OBB3& OBB) const
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
int Plane3::RelationWith(const Triangle3& Triangle) const
{
	return Triangle.RelationWith(*this);
}
/*----------------------------------------------------------------*/
int Plane3::RelationWith(const Plane3& Plane) const
{
	Matrix::Math::Vector3 vcCross;
	VSREAL fSqrLength;

	vcCross.Cross(m_N, Plane.m_N);
	fSqrLength = vcCross.GetSqrLength();

	if (fSqrLength < EPSILON_E4)
	{
		// return Plane.m_Point.RelationWith(*this);
		return IT_NoIntersect;
	}
	return IT_Intersect;
	/*VSREAL fN00 = m_N.GetSqrLength();
	VSREAL fN01 = m_N * Plane.m_N;
	VSREAL fN11 = Plane.m_N.GetSqrLength();
	VSREAL fDet = fN00*fN11 - fN01*fN01;

	if (Math::ABS(fDet) < EPSILON_E4)
		return Plane.m_Point.RelationWith(*this);

	VSREAL fInvDet = 1.0f/fDet;
	VSREAL fC0 = (fN11 * m_fD - fN01 * Plane.m_fD) * fInvDet;
	VSREAL fC1 = (fN00 * Plane.m_fD - fN01 * m_fD) * fInvDet;
	Line.Set(vcCross,m_N * fC0 + Plane.m_N * fC1);
	return IT_Intersect;*/
}
/*----------------------------------------------------------------*/
int Plane3::RelationWith(const Rectangle3& Rectangle) const
{
	return Rectangle.RelationWith(*this);
}
/*----------------------------------------------------------------*/
int Plane3::RelationWith(const Plane3& Plane, Line3& Line) const
{
	Matrix::Math::Vector3 vcCross;
	VSREAL fSqrLength;

	vcCross.Cross(m_N, Plane.m_N);
	fSqrLength = vcCross.GetSqrLength();

	if (fSqrLength < EPSILON_E4)
	{
		return IT_NoIntersect;
		// return Plane.m_Point.RelationWith(*this);
	}
	VSREAL fN00 = m_N.GetSqrLength();
	VSREAL fN01 = m_N.Dot(Plane.m_N);
	VSREAL fN11 = Plane.m_N.GetSqrLength();
	VSREAL fDet = fN00 * fN11 - fN01 * fN01;

	if (Math::ABS(fDet) < EPSILON_E4)
		return IT_NoIntersect;

	VSREAL fInvDet = 1.0f / fDet;
	VSREAL fC0 = (fN11 * m_fD - fN01 * Plane.m_fD) * fInvDet;
	VSREAL fC1 = (fN00 * Plane.m_fD - fN01 * m_fD) * fInvDet;
	Line.Set(m_N * fC0 + Plane.m_N * fC1, vcCross);
	return IT_Intersect; /**/
}
/*----------------------------------------------------------------*/
int Plane3::RelationWith(const Triangle3& Triangle, Segment3& Segment) const
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