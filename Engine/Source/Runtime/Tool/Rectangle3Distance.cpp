#include "Rectangle3.h"
#include "Segment3.h"
#include "AABB3.h"
#include "Polygon3.h"
using namespace Matrix;
/*----------------------------------------------------------------*/
void Rectangle3::GetPoint(Matrix::Math::VSVector3 Point[4]) const
{

	Matrix::Math::VSVector3 temp0 = m_Center + m_A[0] * m_fA[0];
	Matrix::Math::VSVector3 temp1 = m_Center + m_A[0] * (-m_fA[0]);
	Point[0] = temp0 + m_A[1] * m_fA[1];
	Point[1] = temp1 + m_A[1] * m_fA[1];
	Point[2] = temp1 + m_A[1] * (-m_fA[1]);
	Point[3] = temp0 + m_A[1] * (-m_fA[1]);
}
/*----------------------------------------------------------------*/
VSREAL Rectangle3::SquaredDistance(const Rectangle3& Rectangle,
	VSREAL fRectangle1Parameter[2], VSREAL fRectangle2Parameter[2]) const
{
	VSREAL t, temp[2];
	Segment3 Edge;
	VSREAL fSqrDist = VSMAX_REAL;
	VSREAL fSqrDistTmp;
	Matrix::Math::VSVector3 RectanglePoint[4];
	Rectangle.GetPoint(RectanglePoint);
	Edge.Set(RectanglePoint[1], RectanglePoint[0]);
	fSqrDistTmp = Edge.SquaredDistance(*this, t, temp);
	VSREAL fS0, fT0, fS1, fT1;
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		fS1 = t - Rectangle.m_fA[0];
		fT1 = Rectangle.m_fA[1];
		fS0 = temp[0];
		fT0 = temp[1];
	}

	Edge.Set(RectanglePoint[3], RectanglePoint[0]);
	fSqrDistTmp = Edge.SquaredDistance(*this, t, temp);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		fS1 = Rectangle.m_fA[0];
		fT1 = t - Rectangle.m_fA[1];
		fS0 = temp[0];
		fT0 = temp[1];
	}

	Edge.Set(RectanglePoint[2], RectanglePoint[3]);
	fSqrDistTmp = Edge.SquaredDistance(*this, t, temp);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		fS1 = t - Rectangle.m_fA[0];
		fT1 = -Rectangle.m_fA[1];
		fS0 = temp[0];
		fT0 = temp[1];
	}

	Edge.Set(RectanglePoint[2], RectanglePoint[1]);
	fSqrDistTmp = Edge.SquaredDistance(*this, t, temp);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		fS1 = -Rectangle.m_fA[0];
		fT1 = t - Rectangle.m_fA[1];
		fS0 = temp[0];
		fT0 = temp[1];
	}

	GetPoint(RectanglePoint);
	Edge.Set(RectanglePoint[1], RectanglePoint[0]);
	fSqrDistTmp = Edge.SquaredDistance(Rectangle, t, temp);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		fS0 = t - Rectangle.m_fA[0];
		fT0 = Rectangle.m_fA[1];
		fS1 = temp[0];
		fT1 = temp[1];
	}

	Edge.Set(RectanglePoint[3], RectanglePoint[0]);
	fSqrDistTmp = Edge.SquaredDistance(Rectangle, t, temp);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		fS0 = Rectangle.m_fA[0];
		fT0 = t - Rectangle.m_fA[1];
		fS1 = temp[0];
		fT1 = temp[1];
	}

	Edge.Set(RectanglePoint[2], RectanglePoint[3]);
	fSqrDistTmp = Edge.SquaredDistance(Rectangle, t, temp);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		fS0 = t - Rectangle.m_fA[0];
		fT0 = -Rectangle.m_fA[1];
		fS1 = temp[0];
		fT1 = temp[1];
	}

	Edge.Set(RectanglePoint[2], RectanglePoint[1]);
	fSqrDistTmp = Edge.SquaredDistance(Rectangle, t, temp);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		fS0 = -Rectangle.m_fA[0];
		fT0 = t - Rectangle.m_fA[1];
		fS1 = temp[0];
		fT1 = temp[1];
	}
	fRectangle1Parameter[0] = fS0;
	fRectangle1Parameter[1] = fT0;
	fRectangle2Parameter[0] = fS1;
	fRectangle2Parameter[1] = fT1;
	return fSqrDist;
}
/*----------------------------------------------------------------*/
//直线和矩形距离
VSREAL Rectangle3::SquaredDistance(const Line3& Line, VSREAL fRectangleParameter[2], VSREAL& fLineParameter) const
{
	return Line.SquaredDistance(*this, fLineParameter, fRectangleParameter);
}
/*----------------------------------------------------------------*/
//矩形和OBB距离
VSREAL Rectangle3::SquaredDistance(const VSOBB3& OBB, VSREAL RectangleParameter[2], VSREAL OBBParameter[3]) const
{

	return OBB.SquaredDistance(*this, OBBParameter, RectangleParameter);
}
/*----------------------------------------------------------------*/
VSREAL Rectangle3::SquaredDistance(const Ray3& Ray, VSREAL fRectangleParameter[2], VSREAL& fRayParameter) const
{
	return Ray.SquaredDistance(*this, fRayParameter, fRectangleParameter);
}
/*----------------------------------------------------------------*/
//线段到距离距离
VSREAL Rectangle3::SquaredDistance(const Segment3& Segment, VSREAL fRectangleParameter[2], VSREAL& fSegmentParameter) const
{
	return Segment.SquaredDistance(*this, fSegmentParameter, fRectangleParameter);
}
/*----------------------------------------------------------------*/
//三角形和矩形距离
VSREAL Rectangle3::SquaredDistance(const VSTriangle3& Triangle, VSREAL fRectangleParameter[2], VSREAL fTriangleParameter[3]) const
{

	return Triangle.SquaredDistance(*this, fTriangleParameter, fRectangleParameter);
}
/*----------------------------------------------------------------*/
//点和矩形距离
VSREAL Rectangle3::SquaredDistance(const Matrix::Math::VSVector3& Point, VSREAL fRectangleParameter[2]) const
{
	return Point.SquaredDistance(*this, fRectangleParameter);
}
/*----------------------------------------------------------------*/
VSREAL Rectangle3::Distance(const Sphere3& Sphere, VSREAL fRectangleParameter[2], Matrix::Math::VSVector3& SpherePoint) const
{
	return Sphere.Distance(*this, SpherePoint, fRectangleParameter);
}
/*----------------------------------------------------------------*/
VSREAL Rectangle3::Distance(const Plane3& Plane, Matrix::Math::VSVector3& RectanglePoint, Matrix::Math::VSVector3& PlanePoint) const
{
	return Plane.Distance(*this, PlanePoint, RectanglePoint);
}
/*----------------------------------------------------------------*/
VSREAL Rectangle3::SquaredDistance(const AABB3& AABB, VSREAL RectangleParameter[2], VSREAL AABBParameter[3]) const
{
	return AABB.SquaredDistance(*this, RectangleParameter, AABBParameter);
}
/*----------------------------------------------------------------*/
VSREAL Rectangle3::SquaredDistance(const Polygon3& Polygon,
	VSREAL fRectangleParameter[2],
	int& IndexTriangle,
	VSREAL fTriangleParameter[3]) const
{

	return Polygon.SquaredDistance(*this, IndexTriangle, fTriangleParameter, fRectangleParameter);
}