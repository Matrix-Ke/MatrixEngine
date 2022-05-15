#include "Triangle3.h"

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
Triangle3::Triangle3()
{
}
/*----------------------------------------------------------------*/
Triangle3::~Triangle3()
{
}
/*----------------------------------------------------------------*/
Triangle3::Triangle3(const Matrix::Math::Vector3& P0, const Matrix::Math::Vector3& P1, const Matrix::Math::Vector3& P2)
{
	Set(P0, P1, P2);
}
/*----------------------------------------------------------------*/
Triangle3::Triangle3(const Matrix::Math::Vector3 Point[3])
{
	Set(Point);
}
/*----------------------------------------------------------------*/
bool Triangle3::GetParameter(const Matrix::Math::Vector3& Point, VSREAL fTriangleParameter[3]) const
{
	Matrix::Math::Vector3 v01, v02, v0p;
	Matrix::Math::Vector3 vp1, vp2;
	v01 = m_V[1] - m_V[0];
	v02 = m_V[2] - m_V[0];
	v0p = Point - m_V[0];
	vp1 = m_V[1] - Point;
	vp2 = m_V[2] - Point;

	Matrix::Math::Vector3 S[4];

	S[0].Cross(v01, v02);
	S[1].Cross(v01, v0p);
	S[2].Cross(v0p, v02);
	S[3].Cross(vp1, vp2);

	VSREAL fS[4];
	for (int i = 0; i < 4; i++)
	{
		fS[i] = S[i].GetLength();
	}
	for (int i = 0; i < 3; i++)
	{
		fTriangleParameter[i] = fS[i + 1] / fS[0];
	}
	VSREAL fSum = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		fSum += fTriangleParameter[i];
		if (fTriangleParameter[i] < 0.0f || fTriangleParameter[i] > 1.0f)
			return 0;
	}
	if (fSum > 1.0f)
		return 0;
	return 1;
	/*Matrix::Math::Vector3 V[3];
	V[0] = Point - m_V[0];
	V[1] = m_V[1] - m_V[0];
	V[2] = m_V[2] - m_V[0];
	VSREAL s1,t1,s2,t2,k1,k2;
	bool flag1 = 0;
	bool flag2 = 0;
	if(Math::ABS(V[1].x) > EPSILON_E4 && Math::ABS(V[2].x) > EPSILON_E4)
	{
		s1 = V[1].x;
		t1 = V[2].x;
		k1 = V[0].x;
		flag1 = 1;
	}

	if(Math::ABS(V[1].y) > EPSILON_E4 && Math::ABS(V[2].y) > EPSILON_E4)
	{
		if(flag1 ==0)
		{
			s1 = V[1].y;
			t1 = V[2].y;
			k1 = V[0].y;
			flag1 = 1;
		}
		else
		{
			if(Math::ABS((V[1].x * V[2].y) - (V[1].y * V[2].x))> EPSILON_E4)
			{
				flag2 = 1;
				s2 = V[1].y;
				t2 = V[2].y;
				k2 = V[0].y;
			}
		}

	}

	if(Math::ABS(V[1].z) > EPSILON_E4 && Math::ABS(V[2].z) > EPSILON_E4)
	{
		if(flag1 ==0)
		{
			return 0;
		}
		else
		{
			if(flag2 == 0)
			{
				s2 = V[1].z;
				t2 = V[2].z;
				k2 = V[0].z;
				flag2 = 1;
			}
		}

	}

	fTriangleParameter[1] = (t1 * k2 - t2 * k1) / (t1 * s2 - t2 * s1);
	fTriangleParameter[2] = (s1 * k2 - s2 * k1) / (s1 * t2 - s2 * t1);
	fTriangleParameter[0] = 1.0f - fTriangleParameter[1] - fTriangleParameter[2];

	if(fTriangleParameter[0] > 1.0f || fTriangleParameter[1] > 1.0f || fTriangleParameter[2] > 1.0f)
		return 0;
	return 1;
	*/
}
void Triangle3::Transform(const Triangle3& Triangle, const Matrix::Math::Matrix4& Mat)
{
	m_V[0] = Triangle.m_V[0] * Mat;
	m_V[1] = Triangle.m_V[1] * Mat;
	m_V[2] = Triangle.m_V[2] * Mat;
	Set(m_V);
}

/*----------------------------------------------------------------*/
VSREAL Triangle3::SquaredDistance(const Line3& Line, VSREAL fTriangleParameter[3], VSREAL& fLineParameter) const
{

	return Line.SquaredDistance(*this, fLineParameter, fTriangleParameter);
}
/*----------------------------------------------------------------*/
//三角形和OBB距离
VSREAL Triangle3::SquaredDistance(const OBB3& OBB, VSREAL TriangleParameter[3], VSREAL OBBParameter[3]) const
{

	return OBB.SquaredDistance(*this, OBBParameter, TriangleParameter);
}
/*----------------------------------------------------------------*/
//射线和三角形距离
VSREAL Triangle3::SquaredDistance(const Ray3& Ray, VSREAL fTriangleParameter[3], VSREAL& fRayParameter) const
{
	return Ray.SquaredDistance(*this, fRayParameter, fTriangleParameter);
}
/*----------------------------------------------------------------*/
//线段和三角形距离
VSREAL Triangle3::SquaredDistance(const Segment3& Segment, VSREAL fTriangleParameter[3], VSREAL& fSegmentParameter) const
{
	return Segment.SquaredDistance(*this, fSegmentParameter, fTriangleParameter);
}
/*----------------------------------------------------------------*/
//点和三角形距离
VSREAL Triangle3::SquaredDistance(const Matrix::Math::Vector3& Point, VSREAL fTriangleParameter[3]) const
{
	return Point3(Point).SquaredDistance(*this, fTriangleParameter);
}
/*----------------------------------------------------------------*/
VSREAL Triangle3::SquaredDistance(const Triangle3& Triangle,
	VSREAL fTriangle1Parameter[3],
	VSREAL fTriangle2Parameter[3]) const
{

	VSREAL fSqrDist = VSMAX_REAL;
	VSREAL fSqrDistTmp;
	Segment3 Edge;
	VSREAL Tempt0, Temp[3];
	VSREAL fR0, fS0, fT0, fR1, fS1, fT1;
	Edge.Set(m_V[0], m_V[1]);
	fSqrDistTmp = Edge.SquaredDistance(Triangle, Tempt0, Temp);

	if (fSqrDistTmp < fSqrDist)
	{

		fS0 = Tempt0 / Edge.GetLen();
		fR0 = 1.0f - fS0;
		fT0 = 0.0f;
		fR1 = Temp[0];
		fS1 = Temp[1];
		fT1 = Temp[2];
		fSqrDist = fSqrDistTmp;
	}

	Edge.Set(m_V[0], m_V[2]);
	fSqrDistTmp = Edge.SquaredDistance(Triangle, Tempt0, Temp);

	if (fSqrDistTmp < fSqrDist)
	{

		fS0 = 0.0f;
		fT0 = Tempt0 / Edge.GetLen();
		fR0 = 1.0f - fT0;

		fR1 = Temp[0];
		fS1 = Temp[1];
		fT1 = Temp[2];

		fSqrDist = fSqrDistTmp;
	}

	Edge.Set(m_V[1], m_V[2]);
	fSqrDistTmp = Edge.SquaredDistance(Triangle, Tempt0, Temp);

	if (fSqrDistTmp < fSqrDist)
	{

		fS0 = Tempt0 / Edge.GetLen();
		fT0 = 1.0f - fS0;
		fR0 = 0.0f;

		fR1 = Temp[0];
		fS1 = Temp[1];
		fT1 = Temp[2];

		fSqrDist = fSqrDistTmp;
	}

	Edge.Set(Triangle.m_V[0], Triangle.m_V[1]);
	fSqrDistTmp = Edge.SquaredDistance(*this, Tempt0, Temp);

	if (fSqrDistTmp < fSqrDist)
	{

		fS1 = Tempt0 / Edge.GetLen();
		fR1 = 1.0f - fS0;
		fT1 = 0.0f;
		fR0 = Temp[0];
		fS0 = Temp[1];
		fT0 = Temp[2];
		fSqrDist = fSqrDistTmp;
	}

	Edge.Set(Triangle.m_V[0], Triangle.m_V[2]);
	fSqrDistTmp = Edge.SquaredDistance(*this, Tempt0, Temp);

	if (fSqrDistTmp < fSqrDist)
	{

		fS1 = 0.0f;
		fT1 = Tempt0 / Edge.GetLen();
		fR1 = 1.0f - fT0;

		fR0 = Temp[0];
		fS0 = Temp[1];
		fT0 = Temp[2];

		fSqrDist = fSqrDistTmp;
	}

	Edge.Set(Triangle.m_V[1], Triangle.m_V[2]);
	fSqrDistTmp = Edge.SquaredDistance(*this, Tempt0, Temp);

	if (fSqrDistTmp < fSqrDist)
	{

		fS1 = Tempt0 / Edge.GetLen();
		fT1 = 1.0f - fS0;
		fR1 = 0.0f;

		fR0 = Temp[0];
		fS0 = Temp[1];
		fT0 = Temp[2];

		fSqrDist = fSqrDistTmp;
	}

	fTriangle1Parameter[0] = fR0;
	fTriangle1Parameter[1] = fS0;
	fTriangle1Parameter[2] = fT0;

	fTriangle2Parameter[0] = fR1;
	fTriangle2Parameter[1] = fS1;
	fTriangle2Parameter[2] = fT1;
	return fSqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Triangle3::SquaredDistance(const Rectangle3& Rectangle,
	VSREAL fTriangleParameter[3],
	VSREAL fRectangleParameter[2]) const
{

	Matrix::Math::Vector3 RectanglePoint[4];
	Rectangle.GetPoint(RectanglePoint);
	Segment3 Edge;
	// Matrix::Math::Vector3 A[2];
	// Rectangle.GetA(A);
	VSREAL fA[2];
	Rectangle.GetfA(fA);
	VSREAL t, Temp[3];
	VSREAL fSqrDist = VSMAX_REAL;
	VSREAL fSqrDistTmp;
	VSREAL fR0, fS0, fT0, fT1, fS1;
	Edge.Set(RectanglePoint[1], RectanglePoint[0]);
	fSqrDistTmp = Edge.SquaredDistance(*this, t, Temp);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;

		fS1 = t - fA[0];
		fT1 = fA[1];
		fR0 = Temp[0];
		fS0 = Temp[1];
		fT0 = Temp[2];
	}
	Edge.Set(RectanglePoint[3], RectanglePoint[0]);
	fSqrDistTmp = Edge.SquaredDistance(*this, t, Temp);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		fS1 = fA[0];
		fT1 = t - fA[1];
		fR0 = Temp[0];
		fS0 = Temp[1];
		fT0 = Temp[2];
	}
	Edge.Set(RectanglePoint[2], RectanglePoint[3]);
	fSqrDistTmp = Edge.SquaredDistance(*this, t, Temp);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		fS1 = t - fA[0];
		fT1 = -fA[1];
		fR0 = Temp[0];
		fS0 = Temp[1];
		fT0 = Temp[2];
	}
	Edge.Set(RectanglePoint[2], RectanglePoint[1]);
	fSqrDistTmp = Edge.SquaredDistance(*this, t, Temp);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		fS1 = -fA[0];
		fT1 = t - fA[1];
		fR0 = Temp[0];
		fS0 = Temp[1];
		fT0 = Temp[2];
	}

	Edge.Set(m_V[0], m_V[1]);
	fSqrDistTmp = Edge.SquaredDistance(Rectangle, t, Temp);
	if (fSqrDistTmp < fSqrDist)
	{

		fS0 = t / Edge.GetLen();
		fR0 = 1.0f - fS0;
		fT0 = 0.0f;
		fS1 = Temp[0];
		fT1 = Temp[1];
		fSqrDist = fSqrDistTmp;
	}

	Edge.Set(m_V[0], m_V[2]);
	fSqrDistTmp = Edge.SquaredDistance(Rectangle, t, Temp);
	if (fSqrDistTmp < fSqrDist)
	{

		fS0 = 0.0f;
		fT0 = t / Edge.GetLen();
		fR0 = 1.0f - fT0;

		fS1 = Temp[0];
		fT1 = Temp[1];
		fSqrDist = fSqrDistTmp;
	}

	Edge.Set(m_V[1], m_V[2]);
	fSqrDistTmp = Edge.SquaredDistance(Rectangle, t, Temp);
	if (fSqrDistTmp < fSqrDist)
	{

		fS0 = t / Edge.GetLen();
		fT0 = 1.0f - fS0;
		fR0 = 0.0f;

		fS1 = Temp[0];
		fT1 = Temp[1];
		fSqrDist = fSqrDistTmp;
	}
	fTriangleParameter[0] = fR0;
	fTriangleParameter[1] = fS0;
	fTriangleParameter[2] = fT0;
	fRectangleParameter[0] = fS1;
	fRectangleParameter[2] = fT1;
	return fSqrDist;
}
/*----------------------------------------------------------------*/
VSREAL Triangle3::Distance(const Sphere3& Sphere, VSREAL fTriangleParameter[3], Matrix::Math::Vector3& SpherePoint) const
{
	return Sphere.Distance(*this, SpherePoint, fTriangleParameter);
}
/*----------------------------------------------------------------*/
VSREAL Triangle3::Distance(const Plane3& Plane, Matrix::Math::Vector3& TrianglePoint, Matrix::Math::Vector3& PlanePoint) const
{
	return Plane.Distance(*this, PlanePoint, TrianglePoint);
}
/*----------------------------------------------------------------*/
VSREAL Triangle3::SquaredDistance(const AABB3& AABB, VSREAL TriangleParameter[3], VSREAL AABBParameter[3]) const
{

	return AABB.SquaredDistance(*this, AABBParameter, TriangleParameter);
}
/*----------------------------------------------------------------*/
VSREAL Triangle3::SquaredDistance(const Polygon3& Polygon,
	VSREAL fTriangle1Parameter[3],
	int& IndexTriangle,
	VSREAL fTriangle2Parameter[3]) const
{

	return Polygon.SquaredDistance(*this, IndexTriangle, fTriangle2Parameter, fTriangle1Parameter);
}

/*----------------------------------------------------------------*/
int Triangle3::RelationWith(const Line3& Line, bool bCull, VSREAL fTriangleParameter[3],
	VSREAL& fLineParameter) const
{

	return Line.RelationWith(*this, bCull, fLineParameter, fTriangleParameter);
}
/*----------------------------------------------------------------*/
int Triangle3::RelationWith(const Ray3& Ray, bool bCull, VSREAL fTriangleParameter[3],
	VSREAL& fRayParameter) const
{

	return Ray.RelationWith(*this, bCull, fRayParameter, fTriangleParameter);
}
/*----------------------------------------------------------------*/
int Triangle3::RelationWith(const Segment3& Segment, bool bCull, VSREAL fTriangleParameter[3],
	VSREAL& fSegmentParameter) const
{

	return Segment.RelationWith(*this, bCull, fSegmentParameter, fTriangleParameter);
}
/*----------------------------------------------------------------*/
int Triangle3::RelationWith(const Plane3& Plane) const
{
	int iFrontNum = 0;
	int iBackNum = 0;

	for (int i = 0; i < 3; i++)
	{
		int iFlag = Point3(m_V[i]).RelationWith(Plane);
		if (iFlag == IT_Front)
		{
			iFrontNum++;
		}
		else if (iFlag == IT_Back)
		{
			iBackNum++;
		}
		if (iFrontNum > 0 && iBackNum > 0)
			return IT_Intersect;
	}
	if (iFrontNum == 0 && iBackNum == 0)
	{
		return IT_On;
	}
	else if (iFrontNum == 0)
		return IT_Back;
	else if (iBackNum == 0)
		return IT_Front;
	else
		return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Triangle3::RelationWith(const Triangle3& Triangle) const
{
	Segment3 Segment;
	for (int i = 0; i < 3; i++)
	{
		int j = i + 1;
		if (j == 3)
			j = 0;
		Segment.Set(m_V[i], m_V[j]);
		VSREAL fSegmentParameter;
		VSREAL TriangleParameter[3];
		if (Segment.RelationWith(Triangle, 0, fSegmentParameter, TriangleParameter) == IT_Intersect)
			return IT_Intersect;
	}
	for (int i = 0; i < 3; i++)
	{
		int j = i + 1;
		if (j == 3)
			j = 0;
		Segment.Set(Triangle.m_V[i], Triangle.m_V[j]);
		VSREAL fSegmentParameter;
		VSREAL TriangleParameter[3];
		if (Segment.RelationWith(*this, 0, fSegmentParameter, TriangleParameter) == IT_Intersect)
			return IT_Intersect;
	}
	return IT_NoIntersect;
}
/*----------------------------------------------------------------*/
int Triangle3::RelationWith(const Rectangle3& Rectangle) const
{
	Segment3 Segment;
	for (int i = 0; i < 3; i++)
	{
		int j = i + 1;
		if (j == 3)
			j = 0;
		Segment.Set(m_V[i], m_V[j]);
		VSREAL fSegmentParameter;
		VSREAL RectangleParameter[2];
		if (Segment.RelationWith(Rectangle, 0, fSegmentParameter, RectangleParameter) == IT_Intersect)
			return IT_Intersect;
	}
	Matrix::Math::Vector3 Point[4];
	Rectangle.GetPoint(Point);
	for (int i = 0; i < 4; i++)
	{
		int j = i + 1;
		if (j == 4)
			j = 0;
		Segment.Set(Point[i], Point[j]);
		VSREAL fSegmentParameter;
		VSREAL RectangleParameter[2];
		if (Segment.RelationWith(*this, 0, fSegmentParameter, RectangleParameter) == IT_Intersect)
			return IT_Intersect;
	}
	return IT_NoIntersect;
}
/*----------------------------------------------------------------*/
int Triangle3::RelationWith(const AABB3& AABB) const
{
	Plane3 Plane = GetPlane();
	if (Plane.RelationWith(AABB) != IT_Intersect)
		return IT_NoIntersect;
	int InNum = 0, OutNum = 0;
	Matrix::Math::Vector3 Point[3];
	GetPoint(Point);
	for (int i = 0; i < 3; i++)
	{
		int iFlag = Point3(Point[i]).RelationWith(AABB);
		if (iFlag == IT_In || iFlag == IT_On)
		{
			InNum++;
		}
		else if (iFlag == IT_Out)
		{

			OutNum++;
		}
		if (InNum > 0 && OutNum > 0)
			return IT_Intersect;
	}
	if (InNum == 0)
		return IT_Out;
	if (OutNum == 0)
		return IT_In;
	else
		return IT_Intersect;
	/*Segment3 Segment;
	int InNum = 0;
	for(int i = 0 ; i < 3 ; i++)
	{
		int j = i + 1;
		if(j == 3)
			j = 0;
		Segment.Set(m_V[i],m_V[j]);
		VSREAL fNear,fFar;
		unsigned int uiQuantity;
		int iFlag = Segment.RelationWith(AABB,uiQuantity,fNear,fFar);
		if( iFlag == IT_Intersect)
			return IT_Intersect;
		else if(iFlag == IT_In)
			InNum ++;


	}
	if(InNum == 3)
		return IT_In;

	return IT_NoIntersect;*/
}
/*----------------------------------------------------------------*/
int Triangle3::RelationWith(const OBB3& OBB) const
{
	Plane3 Plane = GetPlane();
	if (Plane.RelationWith(OBB) != IT_Intersect)
		return IT_NoIntersect;
	int InNum = 0, OutNum = 0;
	Matrix::Math::Vector3 Point[3];
	GetPoint(Point);
	for (int i = 0; i < 3; i++)
	{
		int iFlag = Point3(Point[i]).RelationWith(OBB);
		if (iFlag == IT_In || iFlag == IT_On)
		{
			InNum++;
		}
		else if (iFlag == IT_Out)
		{

			OutNum++;
		}
		if (InNum > 0 && OutNum > 0)
			return IT_Intersect;
	}
	if (InNum == 0)
		return IT_Out;
	if (OutNum == 0)
		return IT_In;
	else
		return IT_Intersect;
	/*Plane3 Plane = GetPlane();
	if(Plane.RelationWith(OBB) != IT_Intersect)
		return IT_NoIntersect;
	Segment3 Segment;
	int InNum = 0;
	for(int i = 0 ; i < 3 ; i++)
	{
		int j = i + 1;
		if(j == 3)
			j = 0;
		Segment.Set(m_V[i],m_V[j]);
		VSREAL fNear,fFar;
		unsigned int uiQuantity;
		int iFlag = Segment.RelationWith(OBB,uiQuantity,fNear,fFar);
		if( iFlag == IT_Intersect)
			return IT_Intersect;
		else if(iFlag == IT_In)
			InNum ++;


	}
	if(InNum == 3)
		return IT_In;
	return IT_NoIntersect;*/
}
/*----------------------------------------------------------------*/
int Triangle3::RelationWith(const Sphere3& Sphere) const
{

	Plane3 Plane = GetPlane();
	if (Plane.RelationWith(Sphere) != IT_Intersect)
		return IT_NoIntersect;
	int InNum = 0, OutNum = 0;
	Matrix::Math::Vector3 Point[3];
	GetPoint(Point);
	for (int i = 0; i < 3; i++)
	{
		int iFlag = Point3(Point[i]).RelationWith(Sphere);
		if (iFlag == IT_In || iFlag == IT_On)
		{
			InNum++;
		}
		else if (iFlag == IT_Out)
		{

			OutNum++;
		}
		if (InNum > 0 && OutNum > 0)
			return IT_Intersect;
	}
	if (InNum == 0)
		return IT_Out;
	if (OutNum == 0)
		return IT_In;
	else
		return IT_Intersect;
	/*Plane3 Plane = GetPlane();
	if(Plane.RelationWith(Sphere) != IT_Intersect)
		return IT_NoIntersect;
	Segment3 Segment;
	int InNum = 0;
	for(int i = 0 ; i < 3 ; i++)
	{
		int j = i + 1;
		if(j == 3)
			j = 0;
		Segment.Set(m_V[i],m_V[j]);
		VSREAL fNear,fFar;
		unsigned int uiQuantity;
		int iFlag = Segment.RelationWith(Sphere,uiQuantity,fNear,fFar);
		if( iFlag == IT_Intersect)
			return IT_Intersect;
		else if(iFlag == IT_In)
			InNum ++;


	}
	if(InNum == 3)
		return IT_In;
	return IT_NoIntersect;*/
}
/*----------------------------------------------------------------*/
int Triangle3::RelationWith(const Plane3& Plane, Segment3& Segment) const
{
	Segment3 SegmentTemp;
	int InNum = 0;
	int OnNum = 0, BackNum = 0, FrontNum = 0;
	Matrix::Math::Vector3 Orig, End;
	for (int i = 0; i < 3; i++)
	{
		int j = i + 1;
		if (j == 3)
			j = 0;
		SegmentTemp.Set(m_V[i], m_V[j]);
		VSREAL t;
		int iFlag = SegmentTemp.RelationWith(Plane, 0, t);
		if (iFlag == IT_Intersect)
		{
			InNum++;
			if (InNum == 1)
			{
				Orig = SegmentTemp.GetParameterPoint(t);
			}
			else if (InNum == 2)
			{
				End = SegmentTemp.GetParameterPoint(t);
				Segment.Set(Orig, End);
				return IT_Intersect;
			}
		}
		else if (iFlag == IT_On)
		{
			OnNum++;
		}
		else if (iFlag == IT_Back)
		{
			BackNum++;
		}
		else if (iFlag == IT_Front)
		{
			FrontNum++;
		}
	}
	if (OnNum == 3)
		return IT_On;
	if (BackNum == 3)
		return IT_Back;
	if (FrontNum == 3)
		return IT_Front;
	// not control all path
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Triangle3::RelationWith(const Triangle3& Triangle, Segment3& Segment) const
{
	Segment3 SegmentTemp;
	int InNum = 0;
	Matrix::Math::Vector3 Orig, End;
	for (int i = 0; i < 3; i++)
	{
		int j = i + 1;
		if (j == 3)
			j = 0;
		SegmentTemp.Set(m_V[i], m_V[j]);
		VSREAL fTriangleParameter[3];
		VSREAL fSegmentParameter;
		int iFlag = SegmentTemp.RelationWith(Triangle, 0, fSegmentParameter, fTriangleParameter);
		if (iFlag == IT_Intersect)
		{
			InNum++;
			if (InNum == 1)
			{
				Orig = SegmentTemp.GetParameterPoint(fSegmentParameter);
			}
			else if (InNum == 2)
			{
				End = SegmentTemp.GetParameterPoint(fSegmentParameter);
				Segment.Set(Orig, End);
				return IT_Intersect;
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		int j = i + 1;
		if (j == 3)
			j = 0;
		SegmentTemp.Set(Triangle.m_V[i], Triangle.m_V[j]);
		VSREAL fTriangleParameter[3];
		VSREAL fSegmentParameter;
		int iFlag = SegmentTemp.RelationWith(*this, 0, fSegmentParameter, fTriangleParameter);
		if (iFlag == IT_Intersect)
		{
			InNum++;
			if (InNum == 1)
			{
				Orig = SegmentTemp.GetParameterPoint(fSegmentParameter);
			}
			else if (InNum == 2)
			{
				End = SegmentTemp.GetParameterPoint(fSegmentParameter);
				Segment.Set(Orig, End);
				return IT_Intersect;
			}
		}
	}
	return IT_NoIntersect;
}
/*----------------------------------------------------------------*/
int Triangle3::RelationWith(const Rectangle3& Rectangle, Segment3& Segment) const
{
	Segment3 SegmentTemp;
	int InNum = 0;
	Matrix::Math::Vector3 Orig, End;
	for (int i = 0; i < 3; i++)
	{
		int j = i + 1;
		if (j == 3)
			j = 0;
		SegmentTemp.Set(m_V[i], m_V[j]);
		VSREAL fTriangleParameter[2];
		VSREAL fSegmentParameter;
		int iFlag = SegmentTemp.RelationWith(Rectangle, 0, fSegmentParameter, fTriangleParameter);
		if (iFlag == IT_Intersect)
		{
			InNum++;
			if (InNum == 1)
			{
				Orig = SegmentTemp.GetParameterPoint(fSegmentParameter);
			}
			else if (InNum == 2)
			{
				End = SegmentTemp.GetParameterPoint(fSegmentParameter);
				Segment.Set(Orig, End);
				return IT_Intersect;
			}
		}
	}

	Matrix::Math::Vector3 Point[4];
	Rectangle.GetPoint(Point);
	for (int i = 0; i < 4; i++)
	{
		int j = i + 1;
		if (j == 4)
			j = 0;
		SegmentTemp.Set(Point[i], Point[j]);
		VSREAL fTriangleParameter[3];
		VSREAL fSegmentParameter;
		int iFlag = SegmentTemp.RelationWith(*this, 0, fSegmentParameter, fTriangleParameter);
		if (iFlag == IT_Intersect)
		{
			InNum++;
			if (InNum == 1)
			{
				Orig = SegmentTemp.GetParameterPoint(fSegmentParameter);
			}
			else if (InNum == 2)
			{
				End = SegmentTemp.GetParameterPoint(fSegmentParameter);
				Segment.Set(Orig, End);
				return IT_Intersect;
			}
		}
	}
	return IT_NoIntersect;
}