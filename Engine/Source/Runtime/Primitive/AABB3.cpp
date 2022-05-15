#include "AABB3.h"
#include "Math/Matrix3X3W.h"
#include "Ray3.h"
#include "Segment3.h"
#include "Plane3.h"
#include "Point3.h"
#include "Triangle3.h"
#include "Rectangle3.h"
#include "Polygon3.h"
#include "OBB3.h"
#include "Sphere3.h"

#include "Container/Array.h"


using namespace Matrix::Primitive;

const Matrix::Math::Vector3 AABB3::m_A[3] = { Matrix::Math::Vector3(1.0f, 0.0f, 0.0f), Matrix::Math::Vector3(0.0f, 1.0f, 0.0f), Matrix::Math::Vector3(0.0f, 0.0f, 1.0f) };
/*----------------------------------------------------------------*/
AABB3::AABB3()
{
	m_fA[0] = m_fA[1] = m_fA[2] = 0.0f;
}
/*----------------------------------------------------------------*/
AABB3::~AABB3()
{
}
/*----------------------------------------------------------------*/
AABB3::AABB3(const Matrix::Math::Vector3& Max, const Matrix::Math::Vector3& Min)
{
	Set(Max, Min);
}
/*----------------------------------------------------------------*/
AABB3::AABB3(const Matrix::Math::Vector3& Center, VSREAL fA0, VSREAL fA1, VSREAL fA2)
{
	Set(Center, fA0, fA1, fA2);
}
/*----------------------------------------------------------------*/
AABB3::AABB3(const Matrix::Math::Vector3& Center, VSREAL fA[3])
{
	Set(Center, fA);
}
/*----------------------------------------------------------------*/
void AABB3::GetPlane(Plane3 pPlanes[6]) const
{
	Matrix::Math::Vector3 vcN;

	// 右面
	vcN = m_A[0];
	pPlanes[0].Set(vcN, m_Max);

	// 左面
	vcN = m_A[0] * (-1.0f);
	pPlanes[1].Set(vcN, m_Min);

	// 前面
	vcN = m_A[2] * (-1.0f);
	pPlanes[2].Set(vcN, m_Min);

	// 后面
	vcN = m_A[2];
	pPlanes[3].Set(vcN, m_Max);

	// 上面
	vcN = m_A[1];
	pPlanes[4].Set(vcN, m_Max);

	// 下面
	vcN = m_A[1] * (-1.0f);
	pPlanes[5].Set(vcN, m_Min);
}
/*----------------------------------------------------------------*/
void AABB3::GetPoint(Matrix::Math::Vector3 Point[8]) const
{
	Point[0].Set(m_Center.x + m_fA[0], m_Center.y + m_fA[1], m_Center.z + m_fA[2]);
	Point[1].Set(m_Center.x - m_fA[0], m_Center.y + m_fA[1], m_Center.z + m_fA[2]);
	Point[2].Set(m_Center.x - m_fA[0], m_Center.y - m_fA[1], m_Center.z + m_fA[2]);
	Point[3].Set(m_Center.x + m_fA[0], m_Center.y - m_fA[1], m_Center.z + m_fA[2]);
	Point[4].Set(m_Center.x + m_fA[0], m_Center.y + m_fA[1], m_Center.z - m_fA[2]);
	Point[5].Set(m_Center.x - m_fA[0], m_Center.y + m_fA[1], m_Center.z - m_fA[2]);
	Point[6].Set(m_Center.x - m_fA[0], m_Center.y - m_fA[1], m_Center.z - m_fA[2]);
	Point[7].Set(m_Center.x + m_fA[0], m_Center.y - m_fA[1], m_Center.z - m_fA[2]);
}
/*----------------------------------------------------------------*/
void AABB3::GetRectangle(Rectangle3 Rectangle[6]) const
{
	Matrix::Math::Vector3 Center[6];
	Center[0].Set(m_Center.x + m_fA[0], m_Center.y, m_Center.z);
	Center[1].Set(m_Center.x - m_fA[0], m_Center.y, m_Center.z);
	Center[2].Set(m_Center.x, m_Center.y + m_fA[1], m_Center.z);
	Center[3].Set(m_Center.x, m_Center.y - m_fA[1], m_Center.z);
	Center[4].Set(m_Center.x, m_Center.y, m_Center.z + m_fA[2]);
	Center[5].Set(m_Center.x, m_Center.y, m_Center.z - m_fA[2]);
	// right
	Rectangle[0].Set(Center[0], m_A[1], m_A[2], m_fA[1], m_fA[2]);
	// left
	Rectangle[1].Set(Center[1], m_A[1], m_A[2] * (-1), m_fA[1], m_fA[2]);

	// up
	Rectangle[2].Set(Center[4], m_A[2], m_A[0], m_fA[2], m_fA[1]);
	// down
	Rectangle[3].Set(Center[5], m_A[2], m_A[0] * (-1), m_fA[2], m_fA[0]);

	// front
	Rectangle[4].Set(Center[2], m_A[1], m_A[0] * (-1), m_fA[1], m_fA[0]);
	// back
	Rectangle[5].Set(Center[3], m_A[1], m_A[0], m_fA[1], m_fA[0]);
}
/*----------------------------------------------------------------*/
bool AABB3::GetParameter(const Matrix::Math::Vector3& Point, VSREAL fAABBParameter[3]) const
{
	for (int i = 0; i < 3; i++)
	{
		fAABBParameter[i] = Point.m[i] - m_Center.m[i];
	}
	for (int i = 0; i < 3; i++)
		if (Math::ABS(fAABBParameter[i]) > m_fA[i])
			return 0;

	return 1;
}
/*----------------------------------------------------------------*/
void AABB3::Transform(const AABB3& AABB,
	const Matrix::Math::Matrix4& m, bool bHasProject)
{
	if (bHasProject == false)
	{
		m_Max = m_Min = m.GetTranslation();
		if (m._00 > 0.0f)
		{
			m_Min.x += m._00 * AABB.m_Min.x;
			m_Max.x += m._00 * AABB.m_Max.x;
		}
		else
		{
			m_Min.x += m._00 * AABB.m_Max.x;
			m_Max.x += m._00 * AABB.m_Min.x;
		}

		if (m._01 > 0.0f)
		{
			m_Min.y += m._01 * AABB.m_Min.x;
			m_Max.y += m._01 * AABB.m_Max.x;
		}
		else
		{
			m_Min.y += m._01 * AABB.m_Max.x;
			m_Max.y += m._01 * AABB.m_Min.x;
		}

		if (m._02 > 0.0f)
		{
			m_Min.z += m._02 * AABB.m_Min.x;
			m_Max.z += m._02 * AABB.m_Max.x;
		}
		else
		{
			m_Min.z += m._02 * AABB.m_Max.x;
			m_Max.z += m._02 * AABB.m_Min.x;
		}

		if (m._10 > 0.0f)
		{
			m_Min.x += m._10 * AABB.m_Min.y;
			m_Max.x += m._10 * AABB.m_Max.y;
		}
		else
		{
			m_Min.x += m._10 * AABB.m_Max.y;
			m_Max.x += m._10 * AABB.m_Min.y;
		}

		if (m._11 > 0.0f)
		{
			m_Min.y += m._11 * AABB.m_Min.y;
			m_Max.y += m._11 * AABB.m_Max.y;
		}
		else
		{
			m_Min.y += m._11 * AABB.m_Max.y;
			m_Max.y += m._11 * AABB.m_Min.y;
		}

		if (m._12 > 0.0f)
		{
			m_Min.z += m._12 * AABB.m_Min.y;
			m_Max.z += m._12 * AABB.m_Max.y;
		}
		else
		{
			m_Min.z += m._12 * AABB.m_Max.y;
			m_Max.z += m._12 * AABB.m_Min.y;
		}

		if (m._20 > 0.0f)
		{
			m_Min.x += m._20 * AABB.m_Min.z;
			m_Max.x += m._20 * AABB.m_Max.z;
		}
		else
		{
			m_Min.x += m._20 * AABB.m_Max.z;
			m_Max.x += m._20 * AABB.m_Min.z;
		}

		if (m._21 > 0.0f)
		{
			m_Min.y += m._21 * AABB.m_Min.z;
			m_Max.y += m._21 * AABB.m_Max.z;
		}
		else
		{
			m_Min.y += m._21 * AABB.m_Max.z;
			m_Max.y += m._21 * AABB.m_Min.z;
		}

		if (m._22 > 0.0f)
		{
			m_Min.z += m._22 * AABB.m_Min.z;
			m_Max.z += m._22 * AABB.m_Max.z;
		}
		else
		{
			m_Min.z += m._22 * AABB.m_Max.z;
			m_Max.z += m._22 * AABB.m_Min.z;
		}
	}
	else
	{

		Matrix::Math::Vector3 Point[8];
		AABB.GetPoint(Point);

		m_Max = Matrix::Math::Vector3(-VSMAX_REAL, -VSMAX_REAL, -VSMAX_REAL);
		m_Min = Matrix::Math::Vector3(VSMAX_REAL, VSMAX_REAL, VSMAX_REAL);
		for (unsigned int i = 0; i < 8; i++)
		{
			Matrix::Math::Vector3 New = Point[i] * m;

			m_Min.x = Math::Min(m_Min.x, New.x);
			m_Min.y = Math::Min(m_Min.y, New.y);
			m_Min.z = Math::Min(m_Min.z, New.z);
			m_Max.x = Math::Max(m_Max.x, New.x);
			m_Max.y = Math::Max(m_Max.y, New.y);
			m_Max.z = Math::Max(m_Max.z, New.z);
		}
	}
	Set(m_Max, m_Min);
}
/*----------------------------------------------------------------*/
AABB3 AABB3::MergeAABB(const AABB3& AABB) const
{
	AABB3 Temp;
	Temp.m_Max = m_Max;
	Temp.m_Min = m_Min;
	if (Temp.m_Min.x > AABB.m_Min.x)
	{
		Temp.m_Min.x = AABB.m_Min.x;
	}
	if (Temp.m_Min.y > AABB.m_Min.y)
	{
		Temp.m_Min.y = AABB.m_Min.y;
	}
	if (Temp.m_Min.z > AABB.m_Min.z)
	{
		Temp.m_Min.z = AABB.m_Min.z;
	}

	if (Temp.m_Max.x < AABB.m_Max.x)
	{
		Temp.m_Max.x = AABB.m_Max.x;
	}
	if (Temp.m_Max.y < AABB.m_Max.y)
	{
		Temp.m_Max.y = AABB.m_Max.y;
	}
	if (Temp.m_Max.z < AABB.m_Max.z)
	{
		Temp.m_Max.z = AABB.m_Max.z;
	}
	Temp.Set(Temp.m_Max, Temp.m_Min);
	return Temp;
}
/*----------------------------------------------------------------*/
void AABB3::CreateAABB(const Matrix::Math::Vector3* const pPointArray, unsigned int uiPointNum)
{
	if (!pPointArray || !uiPointNum)
		return;
	m_Min = pPointArray[0];
	m_Max = pPointArray[0];
	for (unsigned int i = 1; i < uiPointNum; i++)
	{
		if (pPointArray[i].x < m_Min.x)
		{
			m_Min.x = pPointArray[i].x;
		}
		else if (pPointArray[i].x > m_Max.x)
		{
			m_Max.x = pPointArray[i].x;
		}

		if (pPointArray[i].y < m_Min.y)
		{
			m_Min.y = pPointArray[i].y;
		}
		else if (pPointArray[i].y > m_Max.y)
		{
			m_Max.y = pPointArray[i].y;
		}

		if (pPointArray[i].z < m_Min.z)
		{
			m_Min.z = pPointArray[i].z;
		}
		else if (pPointArray[i].z > m_Max.z)
		{
			m_Max.z = pPointArray[i].z;
		}
	}
	m_Center = (m_Min + m_Max) / 2.0f;

	Matrix::Math::Vector3 Temp = (m_Max - m_Min) / 2.0f;

	m_fA[0] = Temp.x;
	m_fA[1] = Temp.y;
	m_fA[2] = Temp.z;
}
void AABB3::GetQuadAABB(AABB3 AABB[4]) const
{
	Matrix::Math::Vector3 Point[8];
	GetPoint(Point);
	Matrix::Math::Vector3 Mid[4];
	Mid[0] = (m_Center + Point[0]) * 0.5;
	Mid[1] = (m_Center + Point[1]) * 0.5;
	Mid[2] = (m_Center + Point[4]) * 0.5;
	Mid[3] = (m_Center + Point[5]) * 0.5;
	VSREAL fA[3] = { m_fA[0] * 0.5f, m_fA[1], m_fA[2] * 0.5f };
	for (unsigned int i = 0; i < 4; i++)
	{
		Mid[i].y = m_Center.y;
		AABB[i].Set(Mid[i], fA);
	}
}
AABB3 AABB3::GetMin(const AABB3& AABB) const
{
	AABB3 Temp;
	Temp.m_Max = m_Max;
	Temp.m_Min = m_Min;
	if (Temp.m_Min.x < AABB.m_Min.x)
	{
		Temp.m_Min.x = AABB.m_Min.x;
	}
	if (Temp.m_Min.y < AABB.m_Min.y)
	{
		Temp.m_Min.y = AABB.m_Min.y;
	}
	if (Temp.m_Min.z < AABB.m_Min.z)
	{
		Temp.m_Min.z = AABB.m_Min.z;
	}

	if (Temp.m_Max.x > AABB.m_Max.x)
	{
		Temp.m_Max.x = AABB.m_Max.x;
	}
	if (Temp.m_Max.y > AABB.m_Max.y)
	{
		Temp.m_Max.y = AABB.m_Max.y;
	}
	if (Temp.m_Max.z > AABB.m_Max.z)
	{
		Temp.m_Max.z = AABB.m_Max.z;
	}
	Temp.Set(Temp.m_Max, Temp.m_Min);
	return Temp;
}
void AABB3::GetOctAABB(AABB3 AABB[8]) const
{
	Matrix::Math::Vector3 Point[8];
	GetPoint(Point);
	Matrix::Math::Vector3 Mid[8];

	VSREAL fA[3] = { m_fA[0] * 0.5f, m_fA[1] * 0.5f, m_fA[2] * 0.5f };
	for (unsigned int i = 0; i < 8; i++)
	{
		Mid[i] = (m_Center + Point[i]) * 0.5;
		AABB[i].Set(Mid[i], fA);
	}
}


/*----------------------------------------------------------------*/
int AABB3::RelationWith(const Matrix::Math::Vector3& Point) const
{
	Matrix::Math::Vector3 PointTemp = Point - m_Center;
	VSREAL fDiffX = Math::ABS(PointTemp.x) - m_fA[0];
	VSREAL fDiffY = Math::ABS(PointTemp.y) - m_fA[1];
	VSREAL fDiffZ = Math::ABS(PointTemp.z) - m_fA[2];

	if (fDiffX > EPSILON_E4 || fDiffY > EPSILON_E4 || fDiffZ > EPSILON_E4)
		return IT_Out;

	if (fDiffX < -EPSILON_E4 || fDiffY < -EPSILON_E4 || fDiffZ < -EPSILON_E4)
		return IT_In;

	return IT_On;
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
	Matrix::Math::Vector3 N = Plane.GetN();
	VSREAL fD = Plane.GetfD();
	Matrix::Math::Vector3 MinTemp, MaxTemp;
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
		return IT_Front;
	else if ((N.Dot(MaxTemp) + fD) < 0.0f)
		return IT_Back;
	else
		return IT_Intersect;
}
/*----------------------------------------------------------------*/
int AABB3::RelationWith(const Triangle3& Triangle) const
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
		return IT_NoIntersect;
	if ((m_Min.y > AABB.m_Max.y) || (AABB.m_Min.y > m_Max.y))
		return IT_NoIntersect;
	if ((m_Min.z > AABB.m_Max.z) || (AABB.m_Min.z > m_Max.z))
		return IT_NoIntersect;
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int AABB3::RelationWith(const Sphere3& Sphere) const
{
	VSREAL fAABBParameter[3];
	VSREAL Dist = Point3(Sphere.m_Center).SquaredDistance(*this, fAABBParameter);
	Dist = SQRT(Dist);
	if (Dist - Sphere.m_fRadius < 0.0f)
		return IT_Intersect;

	return IT_NoIntersect;
}
bool AABB3::GetIntersect(AABB3& AABB, AABB3& OutAABB) const
{
	using namespace Matrix::Container;

	if (RelationWith(AABB) == IT_Intersect)
	{

		MArrayOrder<VSREAL> XArray;
		XArray.AddElement(GetMinPoint().x);
		XArray.AddElement(GetMaxPoint().x);
		XArray.AddElement(AABB.GetMinPoint().x);
		XArray.AddElement(AABB.GetMaxPoint().x);

		MArrayOrder<VSREAL> YArray;
		YArray.AddElement(GetMinPoint().y);
		YArray.AddElement(GetMaxPoint().y);
		YArray.AddElement(AABB.GetMinPoint().y);
		YArray.AddElement(AABB.GetMaxPoint().y);

		MArrayOrder<VSREAL> ZArray;
		ZArray.AddElement(GetMinPoint().z);
		ZArray.AddElement(GetMaxPoint().z);
		ZArray.AddElement(AABB.GetMinPoint().z);
		ZArray.AddElement(AABB.GetMaxPoint().z);

		OutAABB.Set(Matrix::Math::Vector3(XArray[2], YArray[2], ZArray[2]), Matrix::Math::Vector3(XArray[1], YArray[1], ZArray[1]));
		return true;
	}

	return false;
}



/*----------------------------------------------------------------*/
VSREAL AABB3::SquaredDistance(const Matrix::Math::Vector3& Point, VSREAL fAABBParameter[3]) const
{
	Matrix::Math::Vector3 Diff = Point - m_Center;

	VSREAL fSqrDistance = 0.0, fDelta;

	fAABBParameter[0] = Diff.x;
	if (fAABBParameter[0] < -m_fA[0])
	{
		fDelta = fAABBParameter[0] + m_fA[0];
		fSqrDistance += fDelta * fDelta;
		fAABBParameter[0] = -m_fA[0];
	}
	else if (fAABBParameter[0] > m_fA[0])
	{
		fDelta = fAABBParameter[0] - m_fA[0];
		fSqrDistance += fDelta * fDelta;
		fAABBParameter[0] = m_fA[0];
	}

	fAABBParameter[1] = Diff.y;
	if (fAABBParameter[1] < -m_fA[1])
	{
		fDelta = fAABBParameter[1] + m_fA[1];
		fSqrDistance += fDelta * fDelta;
		fAABBParameter[1] = -m_fA[1];
	}
	else if (fAABBParameter[1] > m_fA[1])
	{
		fDelta = fAABBParameter[1] - m_fA[1];
		fSqrDistance += fDelta * fDelta;
		fAABBParameter[1] = m_fA[1];
	}

	fAABBParameter[2] = Diff.z;
	if (fAABBParameter[2] < -m_fA[2])
	{
		fDelta = fAABBParameter[2] + m_fA[2];
		fSqrDistance += fDelta * fDelta;
		fAABBParameter[2] = -m_fA[2];
	}
	else if (fAABBParameter[2] > m_fA[2])
	{
		fDelta = fAABBParameter[2] - m_fA[2];
		fSqrDistance += fDelta * fDelta;
		fAABBParameter[2] = m_fA[2];
	}
	return fSqrDistance;
}
/*----------------------------------------------------------------*/

/*----------------------------------------------------------------*/
VSREAL AABB3::SquaredDistance(const Line3& Line, VSREAL fAABBParameter[3], VSREAL& fLineParameter) const
{
	Rectangle3 Rectangle[6];
	GetRectangle(Rectangle);
	VSREAL fSqrDist = VSMAX_REAL;
	VSREAL fSqrDistTmp;
	VSREAL t, fAABB[3];
	for (int i = 0; i < 6; i++)
	{
		fSqrDistTmp = Line.SquaredDistance(*this, t, fAABB);
		if (fSqrDist < fSqrDistTmp)
		{
			fSqrDist = fSqrDistTmp;
			fLineParameter = t;
			for (int j = 0; j < 3; j++)
			{
				fAABBParameter[j] = fAABB[j];
			}
		}
	}
	return fSqrDist;
}
/*----------------------------------------------------------------*/
VSREAL AABB3::SquaredDistance(const Ray3& Ray, VSREAL fAABBParameter[3], VSREAL& fRayParameter) const
{

	return Ray.SquaredDistance(*this, fRayParameter, fAABBParameter);
}
/*----------------------------------------------------------------*/
VSREAL AABB3::SquaredDistance(const Segment3& Segment, VSREAL fAABBParameter[3], VSREAL& fSegmentParameter) const
{
	return Segment.SquaredDistance(*this, fSegmentParameter, fAABBParameter);
}
/*----------------------------------------------------------------*/
VSREAL AABB3::SquaredDistance(const Triangle3& Triangle, VSREAL AABBParameter[3],
	VSREAL TriangleParameter[3]) const
{
	Rectangle3 Rectangle[6];
	GetRectangle(Rectangle);
	VSREAL fSqrDist = VSMAX_REAL;
	VSREAL fSqrDistTmp;
	VSREAL RectP[2], TriP[3];

	fSqrDistTmp = Triangle.SquaredDistance(Rectangle[0], TriP, RectP);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		TriangleParameter[0] = TriP[0];
		TriangleParameter[1] = TriP[1];
		TriangleParameter[2] = TriP[2];
		AABBParameter[0] = m_fA[0];
		AABBParameter[1] = RectP[0];
		AABBParameter[2] = RectP[1];
	}

	fSqrDistTmp = Triangle.SquaredDistance(Rectangle[1], TriP, RectP);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		TriangleParameter[0] = TriP[0];
		TriangleParameter[1] = TriP[1];
		TriangleParameter[2] = TriP[2];
		AABBParameter[0] = -m_fA[0];
		AABBParameter[1] = RectP[0];
		AABBParameter[2] = -RectP[1];
	}

	fSqrDistTmp = Triangle.SquaredDistance(Rectangle[2], TriP, RectP);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		TriangleParameter[0] = TriP[0];
		TriangleParameter[1] = TriP[1];
		TriangleParameter[2] = TriP[2];
		AABBParameter[0] = RectP[1];
		AABBParameter[1] = m_fA[1];
		AABBParameter[2] = RectP[0];
	}

	fSqrDistTmp = Triangle.SquaredDistance(Rectangle[3], TriP, RectP);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		TriangleParameter[0] = TriP[0];
		TriangleParameter[1] = TriP[1];
		TriangleParameter[2] = TriP[2];
		AABBParameter[0] = -RectP[1];
		AABBParameter[1] = -m_fA[1];
		AABBParameter[2] = RectP[0];
	}

	fSqrDistTmp = Triangle.SquaredDistance(Rectangle[4], TriP, RectP);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		TriangleParameter[0] = TriP[0];
		TriangleParameter[1] = TriP[1];
		TriangleParameter[2] = TriP[2];
		AABBParameter[0] = -RectP[1];
		AABBParameter[1] = RectP[0];
		AABBParameter[2] = m_fA[2];
	}

	fSqrDistTmp = Triangle.SquaredDistance(Rectangle[5], TriP, RectP);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		TriangleParameter[0] = TriP[0];
		TriangleParameter[1] = TriP[1];
		TriangleParameter[2] = TriP[2];
		AABBParameter[0] = RectP[1];
		AABBParameter[1] = RectP[0];
		AABBParameter[2] = -m_fA[2];
	}
	return fSqrDist;
}
/*----------------------------------------------------------------*/
VSREAL AABB3::SquaredDistance(const Rectangle3& Rectangle, VSREAL AABBParameter[3],
	VSREAL RectangleParameter[2]) const
{

	Rectangle3 RectangleTemp[6];
	GetRectangle(RectangleTemp);
	VSREAL fSqrDist = VSMAX_REAL;
	VSREAL fSqrDistTmp;
	VSREAL RectP[2], RectP1[2];

	fSqrDistTmp = Rectangle.SquaredDistance(RectangleTemp[0], RectP1, RectP);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		RectangleParameter[0] = RectP1[0];
		RectangleParameter[1] = RectP1[1];

		AABBParameter[0] = m_fA[0];
		AABBParameter[1] = RectP[0];
		AABBParameter[2] = RectP[1];
	}

	fSqrDistTmp = Rectangle.SquaredDistance(RectangleTemp[1], RectP1, RectP);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		RectangleParameter[0] = RectP1[0];
		RectangleParameter[1] = RectP1[1];

		AABBParameter[0] = -m_fA[0];
		AABBParameter[1] = RectP[0];
		AABBParameter[2] = -RectP[1];
	}

	fSqrDistTmp = Rectangle.SquaredDistance(RectangleTemp[2], RectP1, RectP);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		RectangleParameter[0] = RectP1[0];
		RectangleParameter[1] = RectP1[1];

		AABBParameter[0] = RectP[1];
		AABBParameter[1] = m_fA[1];
		AABBParameter[2] = RectP[0];
	}

	fSqrDistTmp = Rectangle.SquaredDistance(RectangleTemp[3], RectP1, RectP);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		RectangleParameter[0] = RectP1[0];
		RectangleParameter[1] = RectP1[1];

		AABBParameter[0] = -RectP[1];
		AABBParameter[1] = -m_fA[1];
		AABBParameter[2] = RectP[0];
	}

	fSqrDistTmp = Rectangle.SquaredDistance(RectangleTemp[4], RectP1, RectP);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		RectangleParameter[0] = RectP1[0];
		RectangleParameter[1] = RectP1[1];

		AABBParameter[0] = -RectP[1];
		AABBParameter[1] = RectP[0];
		AABBParameter[2] = m_fA[2];
	}

	fSqrDistTmp = Rectangle.SquaredDistance(RectangleTemp[5], RectP1, RectP);
	if (fSqrDistTmp < fSqrDist)
	{
		fSqrDist = fSqrDistTmp;
		RectangleParameter[0] = RectP1[0];
		RectangleParameter[1] = RectP1[1];

		AABBParameter[0] = RectP[1];
		AABBParameter[1] = RectP[0];
		AABBParameter[2] = -m_fA[2];
	}
	return fSqrDist;
}
/*----------------------------------------------------------------*/
VSREAL AABB3::SquaredDistance(const AABB3& AABB, VSREAL AABB1Parameter[3],
	VSREAL AABB2Parameter[3]) const
{

	VSREAL fSqrDist = VSMAX_REAL;
	VSREAL fSqrDistTmp;
	Matrix::Math::Vector3 Point[8];
	GetPoint(Point);
	VSREAL Temp[3];
	for (int i = 0; i < 8; i++)
	{
		fSqrDistTmp = AABB.SquaredDistance(Point[i], Temp);
		if (fSqrDistTmp < fSqrDist)
		{
			GetParameter(Point[i], AABB1Parameter);
			for (int j = 0; j < 3; j++)
			{
				AABB2Parameter[j] = Temp[j];
			}
		}
	}

	return fSqrDist;
}
/*----------------------------------------------------------------*/
VSREAL AABB3::Distance(const Plane3& Plane, Matrix::Math::Vector3& AABBPoint, Matrix::Math::Vector3& PlanePoint) const
{

	return Plane.Distance(*this, PlanePoint, AABBPoint);
}
/*----------------------------------------------------------------*/
VSREAL AABB3::Distance(const Sphere3& Sphere, VSREAL fAABBParameter[3], Matrix::Math::Vector3& SpherePoint) const
{
	return Sphere.Distance(*this, SpherePoint, fAABBParameter);
}
/*----------------------------------------------------------------*/
VSREAL AABB3::SquaredDistance(const Polygon3& Polygon, VSREAL AABBParameter[3], int& IndexTriangle,
	VSREAL TriangleParameter[3]) const
{
	return Polygon.SquaredDistance(*this, IndexTriangle, TriangleParameter, AABBParameter);
}
