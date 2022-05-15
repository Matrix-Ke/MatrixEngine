#include "Polygon3.h"
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
using namespace Matrix;

Polygon3::Polygon3()
{
	m_PointNum = 0;  //点个数
	m_IndexNum = 0;  //索引个数
	m_Flag = 0;      // 标志位
	m_pPoint = NULL; // 点列表
	m_pIndex = NULL; // 索引列表
}
/*----------------------------------------------------------------*/
Polygon3::~Polygon3()
{
	MX_ENGINE_DELETEA(m_pPoint);
	MX_ENGINE_DELETEA(m_pIndex);
}
/*----------------------------------------------------------------*/
Polygon3::Polygon3(const Matrix::Math::Vector3* pPoint, unsigned int PointNum)
{
	Set(pPoint, PointNum);
}
/*----------------------------------------------------------------*/
bool Polygon3::CopyFrom(const Polygon3& Polygon)
{
	if (!Polygon.m_pPoint || !Polygon.m_PointNum || !Polygon.m_pIndex || !Polygon.m_IndexNum)
		return 0;
	m_PointNum = Polygon.m_PointNum;
	m_IndexNum = Polygon.m_IndexNum;
	m_Flag = Polygon.m_Flag;
	MX_ENGINE_DELETEA(m_pPoint);
	MX_ENGINE_DELETEA(m_pIndex);
	m_pPoint = MX_NEW Matrix::Math::Vector3[m_PointNum];
	MX_ENGINE_ASSERT(m_pPoint);

	m_pIndex = MX_NEW VSUSHORT_INDEX[m_IndexNum];
	MX_ENGINE_ASSERT(m_pIndex);
	Core::MTXMemcpy(m_pPoint, Polygon.m_pPoint, sizeof(Matrix::Math::Vector3) * m_PointNum);
	Core::MTXMemcpy(m_pIndex, Polygon.m_pIndex, sizeof(VSUSHORT_INDEX) * m_IndexNum);
	return 1;
}
/*----------------------------------------------------------------*/
void Polygon3::SwapFaces()
{

	VSUSHORT_INDEX* pIndis = new VSUSHORT_INDEX[m_IndexNum];

	for (unsigned int i = 0; i < m_IndexNum; i++)
		pIndis[m_IndexNum - i - 1] = m_pIndex[i];

	m_Flag = !m_Flag;

	Plane3::Set(m_N * (-1.0f), m_fD);

	MX_ENGINE_DELETEA(m_pIndex);
	m_pIndex = pIndis;
}


VSREAL Polygon3::SquaredDistance(const Matrix::Math::Vector3& Point, int& IndexTriangle, VSREAL fTriangleParameter[3]) const
{
	int iTriangleNum = m_IndexNum / 3;
	Triangle3 TriangleTemp;
	VSREAL distTemp = VSMAX_REAL;

	for (int i = 0; i < iTriangleNum; i++)
	{
		TriangleTemp.Set(m_pPoint[m_pIndex[i]], m_pPoint[m_pIndex[i + 1]], m_pPoint[m_pIndex[i + 2]]);
		VSREAL fParaTemp[3];
		VSREAL dist = TriangleTemp.SquaredDistance(Point, fParaTemp);
		if (distTemp < dist)
		{
			distTemp = dist;
			for (int j = 0; j < 3; j++)
				fTriangleParameter[j] = fParaTemp[j];
			IndexTriangle = i;
		}
	}
	return distTemp;
}
VSREAL Polygon3::SquaredDistance(const Triangle3& Triangle,
	int& IndexTriangle,
	VSREAL fTriangle1Parameter[3],
	VSREAL fTriangle2Parameter[3]) const
{

	int iTriangleNum = m_IndexNum / 3;
	Triangle3 TriangleTemp;
	VSREAL distTemp = VSMAX_REAL;

	for (int i = 0; i < iTriangleNum; i++)
	{
		TriangleTemp.Set(m_pPoint[m_pIndex[i]], m_pPoint[m_pIndex[i + 1]], m_pPoint[m_pIndex[i + 2]]);
		VSREAL fPara1Temp[3];
		VSREAL fPara2Temp[3];
		VSREAL dist = TriangleTemp.SquaredDistance(Triangle, fPara1Temp, fPara2Temp);
		if (distTemp < dist)
		{
			distTemp = dist;
			for (int j = 0; j < 3; j++)
			{
				fTriangle1Parameter[j] = fPara1Temp[j];
				fTriangle2Parameter[j] = fPara2Temp[j];
			}
			IndexTriangle = i;
		}
	}
	return distTemp;
}
//多边形和矩形距离
VSREAL Polygon3::SquaredDistance(const Rectangle3& Rectangle,
	int& IndexTriangle,
	VSREAL fTriangleParameter[3],
	VSREAL fRectangleParameter[2]) const
{

	int iTriangleNum = m_IndexNum / 3;
	Triangle3 TriangleTemp;
	VSREAL distTemp = VSMAX_REAL;

	for (int i = 0; i < iTriangleNum; i++)
	{
		TriangleTemp.Set(m_pPoint[m_pIndex[i]], m_pPoint[m_pIndex[i + 1]], m_pPoint[m_pIndex[i + 2]]);
		VSREAL fPara1Temp[3];
		VSREAL fPara2Temp[2];
		VSREAL dist = TriangleTemp.SquaredDistance(Rectangle, fPara1Temp, fPara2Temp);
		if (distTemp < dist)
		{
			distTemp = dist;
			for (int j = 0; j < 3; j++)
			{
				fTriangleParameter[j] = fPara1Temp[j];
			}
			for (int k = 0; k < 2; k++)
			{
				fRectangleParameter[k] = fPara2Temp[k];
			}
			IndexTriangle = i;
		}
	}
	return distTemp;
}
VSREAL Polygon3::SquaredDistance(const Line3& Line, int& IndexTriangle,
	VSREAL fTriangleParameter[3], VSREAL& fLineParameter) const
{
	int iTriangleNum = m_IndexNum / 3;
	Triangle3 TriangleTemp;
	VSREAL distTemp = VSMAX_REAL;

	for (int i = 0; i < iTriangleNum; i++)
	{
		TriangleTemp.Set(m_pPoint[m_pIndex[i]], m_pPoint[m_pIndex[i + 1]], m_pPoint[m_pIndex[i + 2]]);
		VSREAL fPara1Temp[3];
		VSREAL fPara2;
		VSREAL dist = TriangleTemp.SquaredDistance(Line, fPara1Temp, fPara2);
		if (distTemp < dist)
		{
			distTemp = dist;
			for (int j = 0; j < 3; j++)
			{
				fTriangleParameter[j] = fPara1Temp[j];
			}
			fLineParameter = fPara2;
			IndexTriangle = i;
		}
	}
	return distTemp;
}
VSREAL Polygon3::SquaredDistance(const Ray3& Ray, int& IndexTriangle,
	VSREAL fTriangleParameter[3], VSREAL& fRayParameter) const
{
	int iTriangleNum = m_IndexNum / 3;
	Triangle3 TriangleTemp;
	VSREAL distTemp = VSMAX_REAL;

	for (int i = 0; i < iTriangleNum; i++)
	{
		TriangleTemp.Set(m_pPoint[m_pIndex[i]], m_pPoint[m_pIndex[i + 1]], m_pPoint[m_pIndex[i + 2]]);
		VSREAL fPara1Temp[3];
		VSREAL fPara2;
		VSREAL dist = TriangleTemp.SquaredDistance(Ray, fPara1Temp, fPara2);
		if (distTemp < dist)
		{
			distTemp = dist;
			for (int j = 0; j < 3; j++)
			{
				fTriangleParameter[j] = fPara1Temp[j];
			}
			fRayParameter = fPara2;
			IndexTriangle = i;
		}
	}
	return distTemp;
}
VSREAL Polygon3::SquaredDistance(const Segment3& Segment, int& IndexTriangle,
	VSREAL fTriangleParameter[3], VSREAL& fSegmentParameter) const
{

	int iTriangleNum = m_IndexNum / 3;
	Triangle3 TriangleTemp;
	VSREAL distTemp = VSMAX_REAL;

	for (int i = 0; i < iTriangleNum; i++)
	{
		TriangleTemp.Set(m_pPoint[m_pIndex[i]], m_pPoint[m_pIndex[i + 1]], m_pPoint[m_pIndex[i + 2]]);
		VSREAL fPara1Temp[3];
		VSREAL fPara2;
		VSREAL dist = TriangleTemp.SquaredDistance(Segment, fPara1Temp, fPara2);
		if (distTemp < dist)
		{
			distTemp = dist;
			for (int j = 0; j < 3; j++)
			{
				fTriangleParameter[j] = fPara1Temp[j];
			}
			fSegmentParameter = fPara2;
			IndexTriangle = i;
		}
	}
	return distTemp;
}
VSREAL Polygon3::SquaredDistance(const OBB3& OBB, int& IndexTriangle,
	VSREAL TriangleParameter[3], VSREAL OBBParameter[3]) const
{
	int iTriangleNum = m_IndexNum / 3;
	Triangle3 TriangleTemp;
	VSREAL distTemp = VSMAX_REAL;

	for (int i = 0; i < iTriangleNum; i++)
	{
		TriangleTemp.Set(m_pPoint[m_pIndex[i]], m_pPoint[m_pIndex[i + 1]], m_pPoint[m_pIndex[i + 2]]);
		VSREAL fPara1Temp[3];
		VSREAL fPara2Temp[3];
		VSREAL dist = TriangleTemp.SquaredDistance(OBB, fPara1Temp, fPara2Temp);
		if (distTemp < dist)
		{
			distTemp = dist;
			for (int j = 0; j < 3; j++)
			{
				TriangleParameter[j] = fPara1Temp[j];
				OBBParameter[j] = fPara2Temp[j];
			}
			IndexTriangle = i;
		}
	}
	return distTemp;
}

VSREAL Polygon3::Distance(const Sphere3& Sphere, int& IndexTriangle,
	VSREAL fTriangleParameter[3], Matrix::Math::Vector3& SpherePoint) const
{
	int iTriangleNum = m_IndexNum / 3;
	Triangle3 TriangleTemp;
	VSREAL distTemp = VSMAX_REAL;

	for (int i = 0; i < iTriangleNum; i++)
	{
		TriangleTemp.Set(m_pPoint[m_pIndex[i]], m_pPoint[m_pIndex[i + 1]], m_pPoint[m_pIndex[i + 2]]);
		VSREAL fPara1Temp[3];
		Matrix::Math::Vector3 Point;
		VSREAL dist = TriangleTemp.Distance(Sphere, fPara1Temp, Point);
		if (distTemp < dist)
		{
			distTemp = dist;
			for (int j = 0; j < 3; j++)
			{
				fTriangleParameter[j] = fPara1Temp[j];
			}
			SpherePoint = Point;
			IndexTriangle = i;
		}
	}
	return distTemp;
}

VSREAL Polygon3::Distance(const Plane3& Plane, int& IndexTriangle,
	Matrix::Math::Vector3& TrianglePoint, Matrix::Math::Vector3& PlanePoint) const
{
	int iTriangleNum = m_IndexNum / 3;
	Triangle3 TriangleTemp;
	VSREAL distTemp = VSMAX_REAL;

	for (int i = 0; i < iTriangleNum; i++)
	{
		TriangleTemp.Set(m_pPoint[m_pIndex[i]], m_pPoint[m_pIndex[i + 1]], m_pPoint[m_pIndex[i + 2]]);
		Matrix::Math::Vector3 Point1, Point2;
		VSREAL dist = TriangleTemp.Distance(Plane, Point1, Point2);
		if (distTemp < dist)
		{
			distTemp = dist;

			TrianglePoint = Point1;
			PlanePoint = Point2;
			IndexTriangle = i;
		}
	}
	return distTemp;
}

VSREAL Polygon3::SquaredDistance(const AABB3& AABB, int& IndexTriangle,
	VSREAL TriangleParameter[3], VSREAL AABBParameter[3]) const
{
	int iTriangleNum = m_IndexNum / 3;
	Triangle3 TriangleTemp;
	VSREAL distTemp = VSMAX_REAL;

	for (int i = 0; i < iTriangleNum; i++)
	{
		TriangleTemp.Set(m_pPoint[m_pIndex[i]], m_pPoint[m_pIndex[i + 1]], m_pPoint[m_pIndex[i + 2]]);
		VSREAL fPara1Temp[3];
		VSREAL fPara2Temp[3];
		VSREAL dist = TriangleTemp.SquaredDistance(AABB, fPara1Temp, fPara2Temp);
		if (distTemp < dist)
		{
			distTemp = dist;
			for (int j = 0; j < 3; j++)
			{
				TriangleParameter[j] = fPara1Temp[j];
				AABBParameter[j] = fPara2Temp[j];
			}
			IndexTriangle = i;
		}
	}
	return distTemp;
}
VSREAL Polygon3::SquaredDistance(const Polygon3& Polygon, int& Index1Triangle,
	VSREAL Triangle1Parameter[3], int& Index2Triangle,
	VSREAL Triangle2Parameter[3]) const
{
	int iTriangleNum = m_IndexNum / 3;
	Triangle3 TriangleTemp;
	VSREAL distTemp = VSMAX_REAL;

	for (int i = 0; i < iTriangleNum; i++)
	{
		TriangleTemp.Set(m_pPoint[m_pIndex[i]], m_pPoint[m_pIndex[i + 1]], m_pPoint[m_pIndex[i + 2]]);
		VSREAL fPara1Temp[3];
		VSREAL fPara2Temp[3];
		int k;
		VSREAL dist = TriangleTemp.SquaredDistance(Polygon, fPara1Temp, k, fPara2Temp);
		if (distTemp < dist)
		{
			distTemp = dist;
			for (int j = 0; j < 3; j++)
			{
				Triangle1Parameter[j] = fPara1Temp[j];
				Triangle2Parameter[j] = fPara2Temp[j];
			}
			Index1Triangle = i;
			Index2Triangle = k;
		}
	}
	return distTemp;
}


int Polygon3::RelationWith(const Line3& Line, bool bCull, int& iIndexTriangle, VSREAL fTriangleParameter[3],
	VSREAL& fLineParameter) const
{
	int iTriangleNum = m_IndexNum / 3;
	Triangle3 TriangleTemp;
	VSREAL distTemp = VSMAX_REAL;

	for (int i = 0; i < iTriangleNum; i++)
	{
		TriangleTemp.Set(m_pPoint[m_pIndex[i]], m_pPoint[m_pIndex[i + 1]], m_pPoint[m_pIndex[i + 2]]);
		int iFlag = TriangleTemp.RelationWith(Line, bCull, fTriangleParameter, fLineParameter);
		if (iFlag == IT_Intersect)
			return IT_Intersect;
	}

	return IT_NoIntersect;
}

int Polygon3::RelationWith(const Ray3& Ray, bool bCull, int& iIndexTriangle, VSREAL fTriangleParameter[3],
	VSREAL& fRayParameter) const
{
	int iTriangleNum = m_IndexNum / 3;
	Triangle3 TriangleTemp;
	VSREAL distTemp = VSMAX_REAL;

	for (int i = 0; i < iTriangleNum; i++)
	{
		TriangleTemp.Set(m_pPoint[m_pIndex[i]], m_pPoint[m_pIndex[i + 1]], m_pPoint[m_pIndex[i + 2]]);
		int iFlag = TriangleTemp.RelationWith(Ray, bCull, fTriangleParameter, fRayParameter);
		iIndexTriangle = i;
		if (iFlag == IT_Intersect)
			return IT_Intersect;
	}

	return IT_NoIntersect;
}

int Polygon3::RelationWith(const Segment3& Segment, bool bCull, int& iIndexTriangle, VSREAL fTriangleParameter[3],
	VSREAL& fSegmentParameter) const
{
	int iTriangleNum = m_IndexNum / 3;
	Triangle3 TriangleTemp;
	VSREAL distTemp = VSMAX_REAL;

	for (int i = 0; i < iTriangleNum; i++)
	{
		TriangleTemp.Set(m_pPoint[m_pIndex[i]], m_pPoint[m_pIndex[i + 1]], m_pPoint[m_pIndex[i + 2]]);
		int iFlag = TriangleTemp.RelationWith(Segment, bCull, fTriangleParameter, fSegmentParameter);
		iIndexTriangle = i;
		if (iFlag == IT_Intersect)
			return IT_Intersect;
	}

	return IT_NoIntersect;
}
int Polygon3::RelationWith(const Plane3& Plane) const
{
	Segment3 Segment;
	int iBackNum = 0, iFrontNum = 0;
	for (unsigned int i = 0; i < m_PointNum; i++)
	{

		int iFlag = m_pPoint[i].RelationWith(Plane);
		if (iFlag == IT_Back)
			iBackNum++;
		else if (iFlag == IT_Front)
			iFrontNum++;

		if (iBackNum > 0 && iFrontNum > 0)
			return IT_Intersect;
	}
	if (iBackNum == 0 && iFrontNum == 0)
		return IT_On;
	else if (iBackNum == 0)
		return IT_Front;
	else if (iFrontNum == 0)
		return IT_Back;
	else
		return IT_Intersect;
}
int Polygon3::RelationWith(const Plane3& Plane, Segment3& Segment) const
{
	Segment3 SegmentTemp;
	int InNum = 0;
	int OnNum = 0, BackNum = 0, FrontNum = 0;
	Matrix::Math::Vector3 Orig, End;
	for (unsigned int i = 0; i < m_PointNum; i++)
	{
		int j = i + 1;
		if (j == m_PointNum)
			j = 0;
		SegmentTemp.Set(m_pPoint[i], m_pPoint[j]);
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
int Polygon3::RelationWith(const Triangle3& Triangle) const
{
	Segment3 Segment;
	for (unsigned int i = 0; i < m_PointNum; i++)
	{
		int j = i + 1;
		if (j == m_PointNum)
			j = 0;
		Segment.Set(m_pPoint[i], m_pPoint[j]);
		VSREAL fSegmentParameter;
		VSREAL TriangleParameter[3];
		if (Segment.RelationWith(Triangle, 0, fSegmentParameter, TriangleParameter) == IT_Intersect)
			return IT_Intersect;
	}
	Matrix::Math::Vector3 Point[3];
	Triangle.GetPoint(Point);
	for (int i = 0; i < 3; i++)
	{
		int j = i + 1;
		if (j == 3)
			j = 0;
		Segment.Set(Point[i], Point[j]);
		VSREAL fSegmentParameter;
		VSREAL TriangleParameter[3];
		int Index;
		if (Segment.RelationWith(*this, fSegmentParameter, 0, Index, TriangleParameter) == IT_Intersect)
			return IT_Intersect;
	}
	return IT_NoIntersect;
}
int Polygon3::RelationWith(const Triangle3& Triangle, Segment3& Segment) const
{
	Segment3 SegmentTemp;
	int InNum = 0;
	Matrix::Math::Vector3 Orig, End;
	for (unsigned int i = 0; i < m_PointNum; i++)
	{
		int j = i + 1;
		if (j == m_PointNum)
			j = 0;
		Segment.Set(m_pPoint[i], m_pPoint[j]);
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
	Matrix::Math::Vector3 Point[3];
	Triangle.GetPoint(Point);
	for (int i = 0; i < 3; i++)
	{
		int j = i + 1;
		if (j == 3)
			j = 0;
		SegmentTemp.Set(Point[i], Point[j]);
		VSREAL fSegmentParameter;
		VSREAL fTriangleParameter[3];
		int Index;
		int iFlag = SegmentTemp.RelationWith(*this, fSegmentParameter, 0, Index, fTriangleParameter);
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
int Polygon3::RelationWith(const Rectangle3& Rectangle) const
{
	Segment3 Segment;
	for (unsigned int i = 0; i < m_PointNum; i++)
	{
		int j = i + 1;
		if (j == m_PointNum)
			j = 0;
		Segment.Set(m_pPoint[i], m_pPoint[j]);
		VSREAL fSegmentParameter;
		VSREAL TriangleParameter[2];
		if (Segment.RelationWith(Rectangle, 0, fSegmentParameter, TriangleParameter) == IT_Intersect)
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
		VSREAL TriangleParameter[3];
		int Index;
		if (Segment.RelationWith(*this, fSegmentParameter, 0, Index, TriangleParameter) == IT_Intersect)
			return IT_Intersect;
	}
	return IT_NoIntersect;
}
int Polygon3::RelationWith(const Rectangle3& Rectangle, Segment3& Segment) const
{
	Segment3 SegmentTemp;
	int InNum = 0;
	Matrix::Math::Vector3 Orig, End;
	for (unsigned int i = 0; i < m_PointNum; i++)
	{
		int j = i + 1;
		if (j == m_PointNum)
			j = 0;
		Segment.Set(m_pPoint[i], m_pPoint[j]);
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
		VSREAL fSegmentParameter;
		VSREAL fTriangleParameter[3];
		int Index;
		int iFlag = SegmentTemp.RelationWith(*this, fSegmentParameter, 0, Index, fTriangleParameter);
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
int Polygon3::RelationWith(const AABB3& AABB) const
{
	Plane3 Plane = GetPlane();
	if (Plane.RelationWith(AABB) != IT_Intersect)
		return IT_NoIntersect;
	int InNum = 0, OutNum = 0;

	for (unsigned int i = 0; i < m_PointNum; i++)
	{
		int iFlag = m_pPoint[i].RelationWith(AABB);
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
}

int Polygon3::RelationWith(const OBB3& OBB) const
{
	Plane3 Plane = GetPlane();
	if (Plane.RelationWith(OBB) != IT_Intersect)
		return IT_NoIntersect;
	int InNum = 0, OutNum = 0;

	for (unsigned int i = 0; i < m_PointNum; i++)
	{
		int iFlag = m_pPoint[i].RelationWith(OBB);
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
}

int Polygon3::RelationWith(const Sphere3& Sphere) const
{
	Plane3 Plane = GetPlane();
	if (Plane.RelationWith(Sphere) != IT_Intersect)
		return IT_NoIntersect;
	int InNum = 0, OutNum = 0;

	for (unsigned int i = 0; i < m_PointNum; i++)
	{
		int iFlag = m_pPoint[i].RelationWith(Sphere);
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
}