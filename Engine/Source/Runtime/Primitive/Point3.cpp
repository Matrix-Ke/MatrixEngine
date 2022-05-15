#include "Point3.h"
#include "Line3.h"
#include "Ray3.h"
#include "Segment3.h"
#include "Plane3.h"
#include "Point3.h"
#include "Triangle3.h"
#include "Rectangle3.h"
#include "Polygon3.h"
#include "OBB3.h"
#include "Sphere3.h"
#include "AABB3.h"

#include "Math/Matrix4.h"
#include "Math/Quat.h"

using namespace Matrix::Primitive;

Matrix::Primitive::Point3::Point3(const Point3 &rhs)
{
    if (this != &rhs)
    {
        this->x = rhs.x;
        this->y = rhs.y;
        this->z = rhs.z;
    }
}

Matrix::Primitive::Point3::Point3(const Vector3 &rhs)
{
    if (this != &rhs)
    {
        this->x = rhs.x;
        this->y = rhs.y;
        this->z = rhs.z;
    }
}

Matrix::Primitive::Point3 &Matrix::Primitive::Point3::operator=(const Vector3 &rhs)
{
    if (this != &rhs)
    {
        this->x = rhs.x;
        this->y = rhs.y;
        this->z = rhs.z;
    }
    return *this;
}

/*----------------------------------------------------------------*/
VSREAL Matrix::Primitive::Point3::SquaredDistance(const Vector3 &Point) const
{
    return (x * Point.x + y * Point.y + z * Point.z);
}
/*----------------------------------------------------------------*/
VSREAL Matrix::Primitive::Point3::SquaredDistance(const Line3 &Line, VSREAL &fLineParameter) const
{
    return Line.SquaredDistance(*this, fLineParameter);
}
/*----------------------------------------------------------------*/
VSREAL Matrix::Primitive::Point3::SquaredDistance(const Ray3 &Ray, VSREAL &fRayParameter) const
{
    return Ray.SquaredDistance(*this, fRayParameter);
}
/*----------------------------------------------------------------*/
VSREAL Matrix::Primitive::Point3::SquaredDistance(const Segment3 &Segment, VSREAL &fSegmentParameter) const
{
    return Segment.SquaredDistance(*this, fSegmentParameter);
}
/*----------------------------------------------------------------*/
VSREAL Matrix::Primitive::Point3::SquaredDistance(const Triangle3 &Triangle, VSREAL fTriangleParameter[3]) const
{
    Vector3 TrianglePoint[3];
    Triangle.GetPoint(TrianglePoint);

    Vector3 Diff = TrianglePoint[0] - *this;
    Vector3 Edge0 = TrianglePoint[1] - TrianglePoint[0];
    Vector3 Edge1 = TrianglePoint[2] - TrianglePoint[0];

    VSREAL fA00 = Edge0.GetSqrLength();
    VSREAL fA01 = Edge0.Dot(Edge1);
    VSREAL fA11 = Edge1.GetSqrLength();
    VSREAL fB0 = Diff.Dot(Edge0);
    VSREAL fB1 = Diff.Dot(Edge1);
    VSREAL fC = Diff.GetSqrLength();
    VSREAL fDet = Math::ABS(fA00 * fA11 - fA01 * fA01);
    VSREAL fS = fA01 * fB1 - fA11 * fB0;
    VSREAL fT = fA01 * fB0 - fA00 * fB1;
    VSREAL fSqrDistance;

    if (fS + fT <= fDet)
    {
        if (fS < 0.0f)
        {
            if (fT < 0.0f) // region 4
            {
                if (fB0 < 0.0f)
                {
                    fT = 0.0f;
                    if (-fB0 >= fA00)
                    {
                        fS = 1.0f;
                        fSqrDistance = fA00 + (2.0f) * fB0 + fC;
                    }
                    else
                    {
                        fS = -fB0 / fA00;
                        fSqrDistance = fB0 * fS + fC;
                    }
                }
                else
                {
                    fS = 0.0f;
                    if (fB1 >= 0.0f)
                    {
                        fT = 0.0f;
                        fSqrDistance = fC;
                    }
                    else if (-fB1 >= fA11)
                    {
                        fT = 1.0f;
                        fSqrDistance = fA11 + 2.0f * fB1 + fC;
                    }
                    else
                    {
                        fT = -fB1 / fA11;
                        fSqrDistance = fB1 * fT + fC;
                    }
                }
            }
            else // region 3
            {
                fS = 0.0f;
                if (fB1 >= 0.0f)
                {
                    fT = 0.0f;
                    fSqrDistance = fC;
                }
                else if (-fB1 >= fA11)
                {
                    fT = 1.0f;
                    fSqrDistance = fA11 + 2.0f * fB1 + fC;
                }
                else
                {
                    fT = -fB1 / fA11;
                    fSqrDistance = fB1 * fT + fC;
                }
            }
        }
        else if (fT < 0.0f) // region 5
        {
            fT = 0.0f;
            if (fB0 >= 0.0f)
            {
                fS = 0.0f;
                fSqrDistance = fC;
            }
            else if (-fB0 >= fA00)
            {
                fS = 1.0f;
                fSqrDistance = fA00 + 2.0f * fB0 + fC;
            }
            else
            {
                fS = -fB0 / fA00;
                fSqrDistance = fB0 * fS + fC;
            }
        }
        else // region 0
        {

            VSREAL fInvDet = 1.0f / fDet;
            fS *= fInvDet;
            fT *= fInvDet;
            fSqrDistance = fS * (fA00 * fS + fA01 * fT + 2.0f * fB0) +
                           fT * (fA01 * fS + fA11 * fT + 2.0f * fB1) + fC;
        }
    }
    else
    {
        VSREAL fTmp0, fTmp1, fNumer, fDenom;

        if (fS < 0.0f) // region 2
        {
            fTmp0 = fA01 + fB0;
            fTmp1 = fA11 + fB1;
            if (fTmp1 > fTmp0)
            {
                fNumer = fTmp1 - fTmp0;
                fDenom = fA00 - 2.0f * fA01 + fA11;
                if (fNumer >= fDenom)
                {
                    fS = 1.0f;
                    fT = 0.0f;
                    fSqrDistance = fA00 + 2.0f * fB0 + fC;
                }
                else
                {
                    fS = fNumer / fDenom;
                    fT = 1.0f - fS;
                    fSqrDistance = fS * (fA00 * fS + fA01 * fT + 2.0f * fB0) +
                                   fT * (fA01 * fS + fA11 * fT + 2.0f * fB1) + fC;
                }
            }
            else
            {
                fS = 0.0f;
                if (fTmp1 <= 0.0f)
                {
                    fT = 1.0f;
                    fSqrDistance = fA11 + 2.0f * fB1 + fC;
                }
                else if (fB1 >= 0.0f)
                {
                    fT = 0.0f;
                    fSqrDistance = fC;
                }
                else
                {
                    fT = -fB1 / fA11;
                    fSqrDistance = fB1 * fT + fC;
                }
            }
        }
        else if (fT < 0.0f) // region 6
        {
            fTmp0 = fA01 + fB1;
            fTmp1 = fA00 + fB0;
            if (fTmp1 > fTmp0)
            {
                fNumer = fTmp1 - fTmp0;
                fDenom = fA00 - 2.0f * fA01 + fA11;
                if (fNumer >= fDenom)
                {
                    fT = 1.0f;
                    fS = 0.0f;
                    fSqrDistance = fA11 + 2.0f * fB1 + fC;
                }
                else
                {
                    fT = fNumer / fDenom;
                    fS = 1.0f - fT;
                    fSqrDistance = fS * (fA00 * fS + fA01 * fT + 2.0f * fB0) +
                                   fT * (fA01 * fS + fA11 * fT + 2.0f * fB1) + fC;
                }
            }
            else
            {
                fT = 0.0f;
                if (fTmp1 <= 0.0f)
                {
                    fS = 1.0f;
                    fSqrDistance = fA00 + 2.0f * fB0 + fC;
                }
                else if (fB0 >= 0.0f)
                {
                    fS = 0.0f;
                    fSqrDistance = fC;
                }
                else
                {
                    fS = -fB0 / fA00;
                    fSqrDistance = fB0 * fS + fC;
                }
            }
        }
        else // region 1
        {
            fNumer = fA11 + fB1 - fA01 - fB0;
            if (fNumer <= 0.0f)
            {
                fS = 0.0f;
                fT = 1.0f;
                fSqrDistance = fA11 + 2.0f * fB1 + fC;
            }
            else
            {
                fDenom = fA00 - 2.0f * fA01 + fA11;
                if (fNumer >= fDenom)
                {
                    fS = 1.0f;
                    fT = 0.0f;
                    fSqrDistance = fA00 + 2.0f * fB0 + fC;
                }
                else
                {
                    fS = fNumer / fDenom;
                    fT = 1.0f - fS;
                    fSqrDistance = fS * (fA00 * fS + fA01 * fT + 2.0f * fB0) +
                                   fT * (fA01 * fS + fA11 * fT + 2.0f * fB1) + fC;
                }
            }
        }
    }

    if (fSqrDistance < 0.0f)
    {
        fSqrDistance = 0.0f;
    }
    fTriangleParameter[1] = fS;
    fTriangleParameter[2] = fT;
    fTriangleParameter[0] = 1 - fTriangleParameter[1] - fTriangleParameter[2];

    return fSqrDistance;
}
/*----------------------------------------------------------------*/
VSREAL Matrix::Primitive::Point3::SquaredDistance(const Rectangle3 &Rectangle, VSREAL fRectangleParameter[2]) const
{
    Vector3 Diff = Rectangle.GetCenter() - *this;

    Vector3 A[2];
    Rectangle.GetA(A);
    VSREAL fA[2];
    Rectangle.GetfA(fA);

    VSREAL fB0 = Diff.Dot(A[0]);
    VSREAL fB1 = Diff.Dot(A[1]);
    VSREAL fS = -fB0;
    VSREAL fT = -fB1;
    VSREAL fSqrDistance = Diff.GetSqrLength();

    if (fS < -fA[0])
    {
        fS = -fA[0];
    }
    else if (fS > fA[0])
    {
        fS = fA[0];
    }
    fSqrDistance += fS * (fS + 2.0f * fB0);

    if (fT < -fA[1])
    {
        fT = -fA[1];
    }
    else if (fT > fA[1])
    {
        fT = fA[1];
    }
    fSqrDistance += fT * (fT + 2.0f * fB1);

    if (fSqrDistance < 0.0f)
    {
        fSqrDistance = 0.0f;
    }
    fRectangleParameter[0] = fS;
    fRectangleParameter[1] = fT;
    return fSqrDistance;
}
/*----------------------------------------------------------------*/
//µãºÍOBB¾àÀë
VSREAL Matrix::Primitive::Point3::SquaredDistance(const OBB3 &OBB, VSREAL fOBBParameter[3]) const
{
    return OBB.SquaredDistance(*this, fOBBParameter);
}
/*----------------------------------------------------------------*/
VSREAL Matrix::Primitive::Point3::Distance(const Sphere3 &Sphere, Vector3 &SpherePoint) const
{
    return Sphere.Distance(*this, SpherePoint);
}
/*----------------------------------------------------------------*/
VSREAL Matrix::Primitive::Point3::Distance(const Plane3 &Plane, Vector3 &PlanePoint) const
{
    return Plane.Distance(*this, PlanePoint);
}
/*----------------------------------------------------------------*/
VSREAL Matrix::Primitive::Point3::SquaredDistance(const AABB3 &AABB, VSREAL fAABBParameter[3]) const
{
    return AABB.SquaredDistance(*this, fAABBParameter);
}
/*----------------------------------------------------------------*/
VSREAL Matrix::Primitive::Point3::SquaredDistance(const Polygon3 &Polygon, int &IndexTriangle, VSREAL fTriangleParameter[3]) const
{
    return Polygon.SquaredDistance(*this, IndexTriangle, fTriangleParameter);
}

/*----------------------------------------------------------------*/
int Matrix::Primitive::Point3::RelationWith(const Sphere3 &Sphere) const
{
    VSREAL sqrDist = SquaredDistance(Sphere.m_Center);
    VSREAL diff = sqrDist - Sphere.m_fRadius * Sphere.m_fRadius;
    if (diff > EPSILON_E4)
        return IT_Out;
    else if (diff < -EPSILON_E4)
        return IT_In;
    else
        return IT_On;
}
/*----------------------------------------------------------------*/
int Matrix::Primitive::Point3::RelationWith(const Plane3 &Plane) const
{
    return Plane.RelationWith(*this);
}
/*----------------------------------------------------------------*/
int Matrix::Primitive::Point3::RelationWith(const OBB3 &OBB) const
{
    Math::Matrix4 m;
    OBB.GetTransform(m);
    Vector3 PointTemp = *this * m;
    VSREAL fA[3];
    OBB.GetfA(fA);
    VSREAL fDiffX = Math::ABS(PointTemp.x) - fA[0];
    VSREAL fDiffY = Math::ABS(PointTemp.y) - fA[1];
    VSREAL fDiffZ = Math::ABS(PointTemp.z) - fA[2];

    if (fDiffX > EPSILON_E4 || fDiffY > EPSILON_E4 || fDiffZ > EPSILON_E4)
        return IT_Out;

    if (fDiffX < -EPSILON_E4 || fDiffY < -EPSILON_E4 || fDiffZ < -EPSILON_E4)
        return IT_In;

    return IT_On;
}
/*----------------------------------------------------------------*/
// IT_In IT_Out IT_On
int Matrix::Primitive::Point3::RelationWith(const AABB3 &AABB) const
{

    return AABB.RelationWith(*this);
}