#include "Rectangle3.h"
#include "Segment3.h"
#include "AABB3.h"
using namespace Matrix;
int Rectangle3::RelationWith(const Line3& Line, bool bCull, VSREAL fRectangleParameter[2], VSREAL& fLineParameter) const
{
	return Line.RelationWith(*this, 1, fLineParameter, fRectangleParameter);
}
/*----------------------------------------------------------------*/
int Rectangle3::RelationWith(const Ray3& Ray, bool bCull, VSREAL fRectangleParameter[2], VSREAL& fRayParameter) const
{
	return Ray.RelationWith(*this, 1, fRayParameter, fRectangleParameter);
}
/*----------------------------------------------------------------*/
int Rectangle3::RelationWith(const Segment3& Segment, bool bCull, VSREAL fRectangleParameter[2], VSREAL& fSegmentParameter) const
{
	return Segment.RelationWith(*this, 1, fSegmentParameter, fRectangleParameter);
}
/*----------------------------------------------------------------*/
int Rectangle3::RelationWith(const Plane3& Plane) const
{
	int iFrontNum = 0;
	int iBackNum = 0;
	Matrix::Math::VSVector3 Point[4];
	GetPoint(Point);
	for (int i = 0; i < 4; i++)
	{
		int iFlag = Point[i].RelationWith(Plane);
		if (iFlag == VSFRONT)
		{
			iFrontNum++;
		}
		else if (iFlag == VSBACK)
		{
			iBackNum++;
		}
	}
	if (iFrontNum == 0 && iBackNum == 0)
	{
		return VSON;
	}
	else if (iFrontNum == 0)
		return VSBACK;
	else if (iBackNum == 0)
		return VSFRONT;
	else
		return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int Rectangle3::RelationWith(const VSTriangle3& Triangle) const
{
	return Triangle.RelationWith(*this);
}
/*----------------------------------------------------------------*/
int Rectangle3::RelationWith(const Rectangle3& Rectangle) const
{
	Matrix::Math::VSVector3 Point[4];
	GetPoint(Point);

	Segment3 Segment;
	for (int i = 0; i < 4; i++)
	{
		int j = i + 1;
		if (j == 4)
			j = 0;
		Segment.Set(Point[i], Point[j]);
		VSREAL fSegmentParameter;
		VSREAL RectangleParameter[2];
		if (Segment.RelationWith(Rectangle, 0, fSegmentParameter, RectangleParameter) == VSINTERSECT)
			return VSINTERSECT;
	}
	Rectangle.GetPoint(Point);
	for (int i = 0; i < 4; i++)
	{
		int j = i + 1;
		if (j == 4)
			j = 0;
		Segment.Set(Point[i], Point[j]);
		VSREAL fSegmentParameter;
		VSREAL RectangleParameter[2];
		if (Segment.RelationWith(*this, 0, fSegmentParameter, RectangleParameter) == VSINTERSECT)
			return VSINTERSECT;
	}
	return VSNOINTERSECT;
}
/*----------------------------------------------------------------*/
int Rectangle3::RelationWith(const AABB3& AABB) const
{
	Plane3 Plane = GetPlane();
	if (Plane.RelationWith(AABB) != VSINTERSECT)
		return VSNOINTERSECT;
	int InNum = 0, OutNum = 0;
	Matrix::Math::VSVector3 Point[4];
	GetPoint(Point);
	for (int i = 0; i < 4; i++)
	{
		int iFlag = Point[i].RelationWith(AABB);
		if (iFlag == VSIN || iFlag == VSON)
		{
			InNum++;
		}
		else if (iFlag == VSOUT)
		{

			OutNum++;
		}
		if (InNum > 0 && OutNum > 0)
			return VSINTERSECT;
	}
	if (InNum == 0)
		return VSOUT;
	if (OutNum == 0)
		return VSIN;
	else
		return VSINTERSECT;
	/*Plane3 Plane = GetPlane();
	if(Plane.RelationWith(AABB) != VSINTERSECT)
		return VSNOINTERSECT;
	Matrix::Math::VSVector3 Point[4];
	GetPoint(Point);
	Segment3 Segment;
	int InNum = 0;
	for(int i = 0 ; i < 4 ; i++)
	{
		int j = i + 1;
		if(j == 4)
			j = 0;
		Segment.Set(Point[i],Point[j]);
		VSREAL fNear,fFar;
		unsigned int uiQuantity;
		int iFlag = Segment.RelationWith(AABB,uiQuantity,fNear,fFar);
		if( iFlag == VSINTERSECT)
			return VSINTERSECT;
		else if(iFlag == VSIN)
			InNum ++;


	}
	if(InNum == 4)
		return VSIN;
	return VSNOINTERSECT;*/
}
/*----------------------------------------------------------------*/
int Rectangle3::RelationWith(const VSOBB3& OBB) const
{
	Plane3 Plane = GetPlane();
	if (Plane.RelationWith(OBB) != VSINTERSECT)
		return VSNOINTERSECT;
	int InNum = 0, OutNum = 0;
	Matrix::Math::VSVector3 Point[4];
	GetPoint(Point);
	for (int i = 0; i < 4; i++)
	{
		int iFlag = Point[i].RelationWith(OBB);
		if (iFlag == VSIN || iFlag == VSON)
		{
			InNum++;
		}
		else if (iFlag == VSOUT)
		{

			OutNum++;
		}
		if (InNum > 0 && OutNum > 0)
			return VSINTERSECT;
	}
	if (InNum == 0)
		return VSOUT;
	if (OutNum == 0)
		return VSIN;
	else
		return VSINTERSECT;
	/*Plane3 Plane = GetPlane();
	if(Plane.RelationWith(OBB) != VSINTERSECT)
		return VSNOINTERSECT;
	Matrix::Math::VSVector3 Point[4];
	GetPoint(Point);
	Segment3 Segment;
	int InNum = 0;
	for(int i = 0 ; i < 4 ; i++)
	{
		int j = i + 1;
		if(j == 4)
			j = 0;
		Segment.Set(Point[i],Point[j]);
		VSREAL fNear,fFar;
		unsigned int uiQuantity;
		int iFlag = Segment.RelationWith(OBB,uiQuantity,fNear,fFar);
		if( iFlag == VSINTERSECT)
			return VSINTERSECT;
		else if(iFlag == VSIN)
			InNum ++;


	}
	if(InNum == 4)
		return VSIN;
	return VSNOINTERSECT;*/
}
/*----------------------------------------------------------------*/
int Rectangle3::RelationWith(const Sphere3& Sphere) const
{
	Plane3 Plane = GetPlane();
	if (Plane.RelationWith(Sphere) != VSINTERSECT)
		return VSNOINTERSECT;
	int InNum = 0, OutNum = 0;
	Matrix::Math::VSVector3 Point[4];
	GetPoint(Point);
	for (int i = 0; i < 4; i++)
	{
		int iFlag = Point[i].RelationWith(Sphere);
		if (iFlag == VSIN || iFlag == VSON)
		{
			InNum++;
		}
		else if (iFlag == VSOUT)
		{

			OutNum++;
		}
		if (InNum > 0 && OutNum > 0)
			return VSINTERSECT;
	}
	if (InNum == 0)
		return VSOUT;
	if (OutNum == 0)
		return VSIN;
	else
		return VSINTERSECT;
	/*Plane3 Plane = GetPlane();
	if(Plane.RelationWith(Sphere) != VSINTERSECT)
		return VSNOINTERSECT;
	Matrix::Math::VSVector3 Point[4];
	GetPoint(Point);
	Segment3 Segment;
	int InNum = 0;
	for(int i = 0 ; i < 4 ; i++)
	{
		int j = i + 1;
		if(j == 4)
			j = 0;
		Segment.Set(Point[i],Point[j]);
		VSREAL fNear,fFar;
		unsigned int uiQuantity;
		int iFlag = Segment.RelationWith(Sphere,uiQuantity,fNear,fFar);
		if( iFlag == VSINTERSECT)
			return VSINTERSECT;
		else if(iFlag == VSIN)
			InNum ++;


	}
	if(InNum == 4)
		return VSIN;
	return VSNOINTERSECT;*/
}
/*----------------------------------------------------------------*/
int Rectangle3::RelationWith(const Plane3& Plane, Segment3& Segment) const
{
	Segment3 SegmentTemp;
	int InNum = 0;
	int OnNum = 0, BackNum = 0, FrontNum = 0;
	Matrix::Math::VSVector3 Orig, End;
	Matrix::Math::VSVector3 Point[4];
	GetPoint(Point);
	for (int i = 0; i < 4; i++)
	{
		int j = i + 1;
		if (j == 4)
			j = 0;
		SegmentTemp.Set(Point[i], Point[j]);
		VSREAL t;
		int iFlag = SegmentTemp.RelationWith(Plane, 0, t);
		if (iFlag == VSINTERSECT)
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
				return VSINTERSECT;
			}
		}
		else if (iFlag == VSON)
		{
			OnNum++;
		}
		else if (iFlag == VSBACK)
		{
			BackNum++;
		}
		else if (iFlag == VSFRONT)
		{
			FrontNum++;
		}
	}
	if (OnNum == 4)
		return VSON;
	if (BackNum == 4)
		return VSBACK;
	if (FrontNum == 4)
		return VSFRONT;
	// not control all path
	return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int Rectangle3::RelationWith(const VSTriangle3& Triangle, Segment3& Segment) const
{

	return Triangle.RelationWith(*this, Segment);
}
/*----------------------------------------------------------------*/
int Rectangle3::RelationWith(const Rectangle3& Rectangle, Segment3& Segment) const
{
	Segment3 SegmentTemp;
	int InNum = 0;
	Matrix::Math::VSVector3 Orig, End;
	Matrix::Math::VSVector3 Point[4];
	GetPoint(Point);
	for (int i = 0; i < 4; i++)
	{
		int j = i + 1;
		if (j == 4)
			j = 0;
		SegmentTemp.Set(Point[i], Point[j]);
		VSREAL fSegmentParameter;
		VSREAL fRectangleParameter[2];
		int iFlag = SegmentTemp.RelationWith(Rectangle, 0, fSegmentParameter, fRectangleParameter);
		if (iFlag == VSINTERSECT)
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
				return VSINTERSECT;
			}
		}
	}

	Rectangle.GetPoint(Point);
	for (int i = 0; i < 4; i++)
	{
		int j = i + 1;
		if (j == 4)
			j = 0;
		SegmentTemp.Set(Point[i], Point[j]);
		VSREAL fSegmentParameter;
		VSREAL fRectangleParameter[2];
		int iFlag = SegmentTemp.RelationWith(*this, 0, fSegmentParameter, fRectangleParameter);
		if (iFlag == VSINTERSECT)
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
				return VSINTERSECT;
			}
		}
	}
	if (!InNum)
		return VSNOINTERSECT;
	// not control all path
	return VSINTERSECT;
}