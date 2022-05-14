#include "Line3.h"
#include "Ray3.h"
#include "Segment3.h"
#include "AABB3.h"
#include "Polygon3.h"
using namespace Matrix;
/*----------------------------------------------------------------*/
int Matrix::Primitive::Line3::RelationWith(const VSTriangle3& Triangle, bool bCull, VSREAL& fLineParameter, VSREAL fTriangleParameter[3]) const
{
	Matrix::Math::VSVector3 pvec, tvec, qvec;
	Matrix::Math::VSVector3 TrianglePoint[3];
	Triangle.GetPoint(TrianglePoint);
	Matrix::Math::VSVector3 edge1 = TrianglePoint[1] - TrianglePoint[0];
	Matrix::Math::VSVector3 edge2 = TrianglePoint[2] - TrianglePoint[0];

	pvec.Cross(m_Dir, edge2);

	VSREAL det = edge1.Dot(pvec);
	if ((bCull) && (det < EPSILON_E4))
		return VSNOINTERSECT;
	else if ((det < EPSILON_E4) && (det > -EPSILON_E4))
		return VSNOINTERSECT;

	VSREAL f_det = 1.0f / det;
	tvec = m_Orig - TrianglePoint[0];
	VSREAL u = (tvec.Dot(pvec)) * f_det;
	if (u < 0.0f || u > 1)
		return VSNOINTERSECT;

	qvec.Cross(tvec, edge1);
	VSREAL v = (m_Dir.Dot(qvec)) * f_det;
	if (v < 0.0f || u + v > 1)
		return VSNOINTERSECT;

	VSREAL f = (edge2.Dot(qvec)) * f_det;

	fTriangleParameter[1] = u;
	fTriangleParameter[2] = v;
	fTriangleParameter[0] = 1.0f - u - v;
	fLineParameter = f;

	return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int Matrix::Primitive::Line3::RelationWith(const Plane3& Plane, bool bCull, VSREAL& fLineParameter) const
{
	VSREAL Vd = Plane.GetN().Dot(m_Dir);

	if (ABS(Vd) < EPSILON_E4)
	{

		return m_Orig.RelationWith(Plane);
	}

	if (bCull && (Vd > 0.0f))
		return VSNOINTERSECT;

	VSREAL Vo = -((Plane.GetN().Dot(m_Orig)) + Plane.GetfD());

	VSREAL _t = Vo / Vd;

	fLineParameter = _t;

	return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int Matrix::Primitive::Line3::RelationWith(const Rectangle3& Rectangle, bool bCull, VSREAL& fLineParameter, VSREAL fRectangleParameter[2]) const
{
	Plane3 Plane = Rectangle.GetPlane();
	if (bCull)
	{
		if (m_Orig.RelationWith(Plane) == VSBACK)
			return VSNOINTERSECT;
	}
	if (RelationWith(Plane, bCull, fLineParameter) == VSINTERSECT)
	{
		Matrix::Math::VSVector3 Point = GetParameterPoint(fLineParameter);
		if (Rectangle.GetParameter(Point, fRectangleParameter))
		{
			return VSINTERSECT;
		}
	}
	return VSNOINTERSECT;
}
/*----------------------------------------------------------------*/
int Matrix::Primitive::Line3::RelationWith(const VSOBB3& OBB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar) const
{
	VSREAL e, f, t1, t2, temp;
	VSREAL tmin = -VSMAX_REAL,
		tmax = VSMAX_REAL;
	Matrix::Math::VSVector3 A[3];
	VSREAL fA[3];
	Matrix::Math::VSVector3 vcP = OBB.GetCenter() - m_Orig;
	OBB.GetA(A);
	OBB.GetfA(fA);
	for (unsigned int i = 0; i < 3; i++)
	{
		e = A[i].Dot(vcP);
		f = A[i].Dot(m_Dir);
		if (ABS(f) > EPSILON_E4)
		{

			t1 = (e + fA[i]) / f;
			t2 = (e - fA[i]) / f;

			if (t1 > t2)
			{
				temp = t1;
				t1 = t2;
				t2 = temp;
			}
			if (t1 > tmin)
				tmin = t1;
			if (t2 < tmax)
				tmax = t2;
			if (tmin > tmax)
				return VSNOINTERSECT;
			if (tmax < 0.0f)
				return VSNOINTERSECT;
		}
		else if (((-e - fA[i]) > 0.0f) || ((-e + fA[i]) < 0.0f))
			return VSNOINTERSECT;
	}

	return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int Matrix::Primitive::Line3::RelationWith(const Sphere3& sphere, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar) const
{
	Matrix::Math::VSVector3 Delta = m_Orig - sphere.m_Center;
	VSREAL a0 = Delta.Dot(Delta) - sphere.m_fRadius * sphere.m_fRadius;
	VSREAL a1 = Delta.Dot(m_Dir);
	VSREAL Disc = a1 * a1 - a0;
	if (Disc < 0)
	{
		Quantity = 0;
	}
	else if (Disc >= EPSILON_E4)
	{
		VSREAL root = SQRT(Disc);

		tFar = -a1 + root;
		tNear = -a1 - root;
		Quantity = 2;
	}
	else
	{
		tNear = -a1;
		tFar = -a1;
		Quantity = 1;
	}

	if (Quantity == 0)
		return VSNOINTERSECT;
	else
		return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int Matrix::Primitive::Line3::RelationWith(const AABB3& AABB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar) const
{
	VSREAL t0, t1, tmp;
	tNear = -VSMAX_REAL;
	tFar = VSMAX_REAL;
	Matrix::Math::VSVector3 MaxT;
	Matrix::Math::VSVector3 Min = AABB.GetMinPoint();
	Matrix::Math::VSVector3 Max = AABB.GetMaxPoint();

	for (int i = 0; i < 3; i++)
	{
		if (ABS(m_Dir.m[i]) < EPSILON_E4)
		{
			if ((m_Orig.m[i] < Min.m[i]) ||
				(m_Orig.m[i] > Max.m[i]))
				return VSNOINTERSECT;
		}
		t0 = (Min.m[i] - m_Orig.m[i]) / m_Dir.m[i];
		t1 = (Max.m[i] - m_Orig.m[i]) / m_Dir.m[i];
		if (t0 > t1)
		{
			tmp = t0;
			t0 = t1;
			t1 = tmp;
		}
		if (t0 > tNear)
			tNear = t0;
		if (t1 < tFar)
			tFar = t1;
		if (tNear > tFar)
			return VSNOINTERSECT;
		if (tFar < 0)
			return VSNOINTERSECT;
	}
	return VSINTERSECT;
}
/*----------------------------------------------------------------*/
int Matrix::Primitive::Line3::RelationWith(const Polygon3& Polygon, VSREAL& fLineParameter,
	bool bCull, int& iIndexTriangle, VSREAL fTriangleParameter[3]) const
{
	return Polygon.RelationWith(*this, bCull, iIndexTriangle, fTriangleParameter, fLineParameter);
}