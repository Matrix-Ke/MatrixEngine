#include "Sphere3.h"

using namespace Matrix::Primitive;

/*----------------------------------------------------------------*/
Sphere3::Sphere3()
{
}
/*----------------------------------------------------------------*/
Sphere3::~Sphere3()
{
	m_fRadius = 0.0f;
}
/*----------------------------------------------------------------*/
Sphere3::Sphere3(const Matrix::Math::Vector3& Center, VSREAL fRadius)
{
	Set(Center, fRadius);
}
/*----------------------------------------------------------------*/
void Sphere3::CreateSphere(const Matrix::Math::Vector3* pPointArray, unsigned int uiPointNum)
{
	if (!pPointArray || !uiPointNum)
		return;
	Matrix::Math::Vector3 Sum;
	for (unsigned int i = 0; i < uiPointNum; i++)
		Sum += pPointArray[i];
	m_Center = Sum / (uiPointNum * 1.0f);
	VSREAL radiusSqr = 0.0f;
	for (unsigned int i = 0; i < uiPointNum; i++)
	{
		Matrix::Math::Vector3 diff = pPointArray[i] - m_Center;
		VSREAL Temp = diff.GetSqrLength();
		if (Temp > radiusSqr)
			radiusSqr = Temp;
	}
	m_fRadius = SQRT(radiusSqr);
}
/*----------------------------------------------------------------*/
Sphere3 Sphere3::MergeSpheres(const Sphere3& Sphere) const
{
	Sphere3 Temp;
	Matrix::Math::Vector3 CenterDiff = m_Center - Sphere.m_Center;
	VSREAL fRadiusDiff = m_fRadius - Sphere.m_fRadius;
	VSREAL fRadiusDiffSqr = fRadiusDiff * fRadiusDiff;
	VSREAL Lsqr = CenterDiff.GetSqrLength();
	if (fRadiusDiffSqr >= Lsqr)
	{
		if (fRadiusDiff >= 0.0f)
		{
			Temp.m_Center = m_Center;
			Temp.m_fRadius = m_fRadius;
		}
		else
		{
			Temp.m_Center = Sphere.m_Center;
			Temp.m_fRadius = Sphere.m_fRadius;
		}
	}
	else
	{
		VSREAL L = SQRT(Lsqr);
		VSREAL t = (L + m_fRadius - Sphere.m_fRadius) / (2.0f * L);
		Temp.m_Center = Sphere.m_Center + CenterDiff * t;
		Temp.m_fRadius = (L + m_fRadius + Sphere.m_fRadius) / 2.0f;
	}

	return Temp;
}
/*----------------------------------------------------------------*/
void Sphere3::Transform(const Sphere3& Sphere, const Matrix::Math::Matrix4& Mat)
{
	m_Center = Sphere.m_Center * Mat;
	/*Math::VSMatrix3X3 M;
	Mat.Get3X3(M);
	Matrix::Math::Vector3 V[3];
	VSREAL E[3];
	M.GetEigenSystem(E,V);
	VSREAL Max = E[0];
	for(unsigned int i = 1 ; i < 3 ; i++)
	{
	if(Max < E[i])
	Max = E[i];
	}
	m_fRadius = Sphere.m_fRadius * Max;*/
	Matrix::Math::Vector3 V0(1.0f, 0.0f, 0.0f), V1(0.0f, 1.0f, 0.0f), V2(0.0f, 0.0f, 1.0f);
	Matrix::Math::Vector3 Temp0 = Sphere.m_Center + V0 * Sphere.m_fRadius;
	Matrix::Math::Vector3 Temp1 = Sphere.m_Center + V1 * Sphere.m_fRadius;
	Matrix::Math::Vector3 Temp2 = Sphere.m_Center + V2 * Sphere.m_fRadius;

	Temp0 = Temp0 * Mat;
	Temp1 = Temp1 * Mat;
	Temp2 = Temp2 * Mat;

	VSREAL fRadiusTemp;

	m_fRadius = (Temp0 - m_Center).GetLength();

	fRadiusTemp = (Temp1 - m_Center).GetLength();

	if (m_fRadius < fRadiusTemp)
		m_fRadius = fRadiusTemp;

	fRadiusTemp = (Temp2 - m_Center).GetLength();

	if (m_fRadius < fRadiusTemp)
		m_fRadius = fRadiusTemp;
}
AABB3 Sphere3::GetAABB() const
{
	Matrix::Math::Vector3 Max = m_Center + Matrix::Math::Vector3(m_fRadius, m_fRadius, m_fRadius);
	Matrix::Math::Vector3 Min = m_Center + Matrix::Math::Vector3(-m_fRadius, -m_fRadius, -m_fRadius);
	return AABB3(Max, Min);
}

/*----------------------------------------------------------------*/
VSREAL Sphere3::Distance(const Matrix::Math::Vector3& Point, Matrix::Math::Vector3& SpherePoint) const
{
	VSREAL sqrDist = Point.SquaredDistance(m_Center);

	sqrDist = SQRT(sqrDist);
	sqrDist = sqrDist - m_fRadius;

	Line3 Line(m_Center, Point);

	SpherePoint = Line.GetParameterPoint(m_fRadius);
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Sphere3::Distance(const Line3& Line, Matrix::Math::Vector3& SpherePoint, VSREAL& fLineParameter) const
{

	VSREAL sqrDist = Line.SquaredDistance(m_Center, fLineParameter);
	sqrDist = SQRT(sqrDist);
	sqrDist = sqrDist - m_fRadius;

	Line3 LineTemp(m_Center, Line.GetParameterPoint(fLineParameter));

	SpherePoint = LineTemp.GetParameterPoint(m_fRadius);
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Sphere3::Distance(const Ray3& Ray, Matrix::Math::Vector3& SpherePoint, VSREAL& fRayParameter) const
{
	VSREAL sqrDist = Ray.SquaredDistance(m_Center, fRayParameter);

	sqrDist = SQRT(sqrDist);
	sqrDist = sqrDist - m_fRadius;

	Line3 LineTemp(m_Center, Ray.GetParameterPoint(fRayParameter));

	SpherePoint = LineTemp.GetParameterPoint(m_fRadius);
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Sphere3::Distance(const Segment3& Segment, Matrix::Math::Vector3& SpherePoint, VSREAL& fSegmentParameter) const
{
	VSREAL sqrDist = Segment.SquaredDistance(m_Center, fSegmentParameter);

	sqrDist = SQRT(sqrDist);
	sqrDist = sqrDist - m_fRadius;

	Line3 LineTemp(m_Center, Segment.GetParameterPoint(fSegmentParameter));

	SpherePoint = LineTemp.GetParameterPoint(m_fRadius);
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Sphere3::Distance(const OBB3& OBB, Matrix::Math::Vector3& SpherePoint, VSREAL fOBBParameter[3]) const
{
	VSREAL sqrDist = OBB.SquaredDistance(m_Center, fOBBParameter);

	sqrDist = SQRT(sqrDist);
	sqrDist = sqrDist - m_fRadius;

	Line3 LineTemp(m_Center, OBB.GetParameterPoint(fOBBParameter));

	SpherePoint = LineTemp.GetParameterPoint(m_fRadius);
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Sphere3::Distance(const Plane3& Plane, Matrix::Math::Vector3& SpherePoint) const
{
	Matrix::Math::Vector3 PlanePoint;
	VSREAL sqrDist = Plane.Distance(m_Center, PlanePoint);

	sqrDist = sqrDist - m_fRadius;

	Line3 LineTemp(m_Center, PlanePoint);

	SpherePoint = LineTemp.GetParameterPoint(m_fRadius);
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Sphere3::Distance(const Rectangle3& Rectangle, Matrix::Math::Vector3& SpherePoint, VSREAL fRectangleParameter[2]) const
{
	VSREAL sqrDist = Rectangle.SquaredDistance(m_Center, fRectangleParameter);

	sqrDist = SQRT(sqrDist);
	sqrDist = sqrDist - m_fRadius;

	Line3 LineTemp(m_Center, Rectangle.GetParameterPoint(fRectangleParameter));

	SpherePoint = LineTemp.GetParameterPoint(m_fRadius);
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Sphere3::Distance(const Triangle3 Triangle, Matrix::Math::Vector3& SpherePoint, VSREAL fTriangleParameter[3]) const
{
	VSREAL sqrDist = Triangle.SquaredDistance(m_Center, fTriangleParameter);

	sqrDist = SQRT(sqrDist);
	sqrDist = sqrDist - m_fRadius;

	Line3 LineTemp(m_Center, Triangle.GetParameterPoint(fTriangleParameter));

	SpherePoint = LineTemp.GetParameterPoint(m_fRadius);
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Sphere3::Distance(const AABB3& AABB, Matrix::Math::Vector3& SpherePoint, VSREAL fAABBParameter[3]) const
{
	VSREAL sqrDist = AABB.SquaredDistance(m_Center, fAABBParameter);

	sqrDist = SQRT(sqrDist);
	sqrDist = sqrDist - m_fRadius;

	Line3 LineTemp(m_Center, AABB.GetParameterPoint(fAABBParameter));

	SpherePoint = LineTemp.GetParameterPoint(m_fRadius);
	return sqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Sphere3::Distance(const Polygon3& Polygon, Matrix::Math::Vector3& SpherePoint, int& IndexTriangle,
	VSREAL fTriangleParameter[3]) const
{

	return Polygon.Distance(*this, IndexTriangle, fTriangleParameter, SpherePoint);
}

int Sphere3::RelationWith(const Matrix::Math::Vector3& Point) const
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
	Matrix::Math::Vector3 N = Plane.GetN();
	VSREAL fD = Plane.GetfD();

	VSREAL test = m_Center.Dot(N) + fD;
	if (test > m_fRadius)
		return IT_Front;
	else if (test < -m_fRadius)
		return IT_Back;
	else
		return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Sphere3::RelationWith(const Triangle3 Triangle) const
{
	return Triangle.RelationWith(*this);
}
/*----------------------------------------------------------------*/
int Sphere3::RelationWith(const Rectangle3& Rectangle) const
{
	return Rectangle.RelationWith(*this);
}
/*----------------------------------------------------------------*/
int Sphere3::RelationWith(const OBB3& OBB) const
{
	return OBB.RelationWith(*this);
}
/*----------------------------------------------------------------*/
int Sphere3::RelationWith(const Sphere3& Sphere) const
{
	VSREAL Sum = m_fRadius + Sphere.m_fRadius;

	Sum *= Sum;

	Matrix::Math::Vector3 Sub = m_Center - Sphere.m_Center;

	if (Sub.GetSqrLength() > Sum)
		return IT_NoIntersect;

	return IT_Intersect;
}