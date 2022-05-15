#include "Rectangle3.h"
#include "Math/Matrix4.h"
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
Rectangle3::Rectangle3()
{
}
/*----------------------------------------------------------------*/
Rectangle3::~Rectangle3()
{
}
/*----------------------------------------------------------------*/
Rectangle3::Rectangle3(const Matrix::Math::Vector3 &Center, const Matrix::Math::Vector3 &A0, const Matrix::Math::Vector3 &A1, VSREAL fA0, VSREAL fA1)
{
    Set(Center, A0, A1, fA0, fA1);
}
/*----------------------------------------------------------------*/
Rectangle3::Rectangle3(const Matrix::Math::Vector3 &Center, const Matrix::Math::Vector3 A[2], const VSREAL fA[2])
{
    Set(Center, A, fA);
}
/*----------------------------------------------------------------*/
bool Rectangle3::GetParameter(const Matrix::Math::Vector3 &Point, VSREAL fRectangleParameter[2]) const
{
    Matrix::Math::Vector3 A2;
    A2.Cross(m_A[0], m_A[1]);
    Matrix::Math::Matrix4 m;
    m.CreateInWorldObject(m_A[0], m_A[1], A2, m_Center);
    Matrix::Math::Vector3 Temp;
    Temp = Point * m;
    fRectangleParameter[0] = Temp.x;
    fRectangleParameter[1] = Temp.y;
    if (Math::ABS(Temp.z) > EPSILON_E4 || Math::ABS(Temp.x) > m_fA[0] || Math::ABS(Temp.y) > m_fA[1])
        return 0;
    return 1;
}
/*----------------------------------------------------------------*/
void Rectangle3::Transform(const Rectangle3 &Rectangle,
                           const Matrix::Math::Matrix4 &Mat)
{
    m_A[0] = Mat.Apply3X3(Rectangle.m_A[0]);
    m_A[1] = Mat.Apply3X3(Rectangle.m_A[1]);
    m_A[0].Normalize();
    m_A[1].Normalize();
    m_Center = Rectangle.m_Center * Mat;
    m_fA[0] = Rectangle.m_fA[0];
    m_fA[1] = Rectangle.m_fA[1];

    Matrix::Math::Vector3 N;
    N.Cross(m_A[0], m_A[1]);
    Plane3(N, m_Center);
}

/*----------------------------------------------------------------*/
void Rectangle3::GetPoint(Matrix::Math::Vector3 Point[4]) const
{

    Matrix::Math::Vector3 temp0 = m_Center + m_A[0] * m_fA[0];
    Matrix::Math::Vector3 temp1 = m_Center + m_A[0] * (-m_fA[0]);
    Point[0] = temp0 + m_A[1] * m_fA[1];
    Point[1] = temp1 + m_A[1] * m_fA[1];
    Point[2] = temp1 + m_A[1] * (-m_fA[1]);
    Point[3] = temp0 + m_A[1] * (-m_fA[1]);
}
/*----------------------------------------------------------------*/
VSREAL Rectangle3::SquaredDistance(const Rectangle3 &Rectangle,
                                   VSREAL fRectangle1Parameter[2], VSREAL fRectangle2Parameter[2]) const
{
    VSREAL t, temp[2];
    Segment3 Edge;
    VSREAL fSqrDist = VSMAX_REAL;
    VSREAL fSqrDistTmp;
    Matrix::Math::Vector3 RectanglePoint[4];
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
VSREAL Rectangle3::SquaredDistance(const Line3 &Line, VSREAL fRectangleParameter[2], VSREAL &fLineParameter) const
{
    return Line.SquaredDistance(*this, fLineParameter, fRectangleParameter);
}
/*----------------------------------------------------------------*/
//矩形和OBB距离
VSREAL Rectangle3::SquaredDistance(const OBB3 &OBB, VSREAL RectangleParameter[2], VSREAL OBBParameter[3]) const
{

    return OBB.SquaredDistance(*this, OBBParameter, RectangleParameter);
}
/*----------------------------------------------------------------*/
VSREAL Rectangle3::SquaredDistance(const Ray3 &Ray, VSREAL fRectangleParameter[2], VSREAL &fRayParameter) const
{
    return Ray.SquaredDistance(*this, fRayParameter, fRectangleParameter);
}
/*----------------------------------------------------------------*/
//线段到距离距离
VSREAL Rectangle3::SquaredDistance(const Segment3 &Segment, VSREAL fRectangleParameter[2], VSREAL &fSegmentParameter) const
{
    return Segment.SquaredDistance(*this, fSegmentParameter, fRectangleParameter);
}
/*----------------------------------------------------------------*/
//三角形和矩形距离
VSREAL Rectangle3::SquaredDistance(const Triangle3 &Triangle, VSREAL fRectangleParameter[2], VSREAL fTriangleParameter[3]) const
{

    return Triangle.SquaredDistance(*this, fTriangleParameter, fRectangleParameter);
}
/*----------------------------------------------------------------*/
//点和矩形距离
VSREAL Rectangle3::SquaredDistance(const Matrix::Math::Vector3 &Point, VSREAL fRectangleParameter[2]) const
{
    return Point3(Point).SquaredDistance(*this, fRectangleParameter);
}
/*----------------------------------------------------------------*/
VSREAL Rectangle3::Distance(const Sphere3 &Sphere, VSREAL fRectangleParameter[2], Matrix::Math::Vector3 &SpherePoint) const
{
    return Sphere.Distance(*this, SpherePoint, fRectangleParameter);
}
/*----------------------------------------------------------------*/
VSREAL Rectangle3::Distance(const Plane3 &Plane, Matrix::Math::Vector3 &RectanglePoint, Matrix::Math::Vector3 &PlanePoint) const
{
    return Plane.Distance(*this, PlanePoint, RectanglePoint);
}
/*----------------------------------------------------------------*/
VSREAL Rectangle3::SquaredDistance(const AABB3 &AABB, VSREAL RectangleParameter[2], VSREAL AABBParameter[3]) const
{
    return AABB.SquaredDistance(*this, RectangleParameter, AABBParameter);
}
/*----------------------------------------------------------------*/
VSREAL Rectangle3::SquaredDistance(const Polygon3 &Polygon,
                                   VSREAL fRectangleParameter[2],
                                   int &IndexTriangle,
                                   VSREAL fTriangleParameter[3]) const
{

    return Polygon.SquaredDistance(*this, IndexTriangle, fTriangleParameter, fRectangleParameter);
}

int Rectangle3::RelationWith(const Line3 &Line, bool bCull, VSREAL fRectangleParameter[2], VSREAL &fLineParameter) const
{
    return Line.RelationWith(*this, 1, fLineParameter, fRectangleParameter);
}
/*----------------------------------------------------------------*/
int Rectangle3::RelationWith(const Ray3 &Ray, bool bCull, VSREAL fRectangleParameter[2], VSREAL &fRayParameter) const
{
    return Ray.RelationWith(*this, 1, fRayParameter, fRectangleParameter);
}
/*----------------------------------------------------------------*/
int Rectangle3::RelationWith(const Segment3 &Segment, bool bCull, VSREAL fRectangleParameter[2], VSREAL &fSegmentParameter) const
{
    return Segment.RelationWith(*this, 1, fSegmentParameter, fRectangleParameter);
}
/*----------------------------------------------------------------*/
int Rectangle3::RelationWith(const Plane3 &Plane) const
{
    int iFrontNum = 0;
    int iBackNum = 0;
    Matrix::Math::Vector3 Point[4];
    GetPoint(Point);
    for (int i = 0; i < 4; i++)
    {
        int iFlag = Point3(Point[i]).RelationWith(Plane);
        if (iFlag == IT_Front)
        {
            iFrontNum++;
        }
        else if (iFlag == IT_Back)
        {
            iBackNum++;
        }
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
int Rectangle3::RelationWith(const Triangle3 &Triangle) const
{
    return Triangle.RelationWith(*this);
}
/*----------------------------------------------------------------*/
int Rectangle3::RelationWith(const Rectangle3 &Rectangle) const
{
    Matrix::Math::Vector3 Point[4];
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
        if (Segment.RelationWith(Rectangle, 0, fSegmentParameter, RectangleParameter) == IT_Intersect)
            return IT_Intersect;
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
        if (Segment.RelationWith(*this, 0, fSegmentParameter, RectangleParameter) == IT_Intersect)
            return IT_Intersect;
    }
    return IT_NoIntersect;
}
/*----------------------------------------------------------------*/
int Rectangle3::RelationWith(const AABB3 &AABB) const
{
    Plane3 Plane = GetPlane();
    if (Plane.RelationWith(AABB) != IT_Intersect)
        return IT_NoIntersect;
    int InNum = 0, OutNum = 0;
    Matrix::Math::Vector3 Point[4];
    GetPoint(Point);
    for (int i = 0; i < 4; i++)
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
    /*Plane3 Plane = GetPlane();
    if(Plane.RelationWith(AABB) != IT_Intersect)
        return IT_NoIntersect;
    Matrix::Math::Vector3 Point[4];
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
        if( iFlag == IT_Intersect)
            return IT_Intersect;
        else if(iFlag == IT_In)
            InNum ++;


    }
    if(InNum == 4)
        return IT_In;
    return IT_NoIntersect;*/
}
/*----------------------------------------------------------------*/
int Rectangle3::RelationWith(const OBB3 &OBB) const
{
    Plane3 Plane = GetPlane();
    if (Plane.RelationWith(OBB) != IT_Intersect)
        return IT_NoIntersect;
    int InNum = 0, OutNum = 0;
    Matrix::Math::Vector3 Point[4];
    GetPoint(Point);
    for (int i = 0; i < 4; i++)
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
    Matrix::Math::Vector3 Point[4];
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
        if( iFlag == IT_Intersect)
            return IT_Intersect;
        else if(iFlag == IT_In)
            InNum ++;


    }
    if(InNum == 4)
        return IT_In;
    return IT_NoIntersect;*/
}
/*----------------------------------------------------------------*/
int Rectangle3::RelationWith(const Sphere3 &Sphere) const
{
    Plane3 Plane = GetPlane();
    if (Plane.RelationWith(Sphere) != IT_Intersect)
        return IT_NoIntersect;
    int InNum = 0, OutNum = 0;
    Matrix::Math::Vector3 Point[4];
    GetPoint(Point);
    for (int i = 0; i < 4; i++)
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
    Matrix::Math::Vector3 Point[4];
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
        if( iFlag == IT_Intersect)
            return IT_Intersect;
        else if(iFlag == IT_In)
            InNum ++;


    }
    if(InNum == 4)
        return IT_In;
    return IT_NoIntersect;*/
}
/*----------------------------------------------------------------*/
int Rectangle3::RelationWith(const Plane3 &Plane, Segment3 &Segment) const
{
    Segment3 SegmentTemp;
    int InNum = 0;
    int OnNum = 0, BackNum = 0, FrontNum = 0;
    Matrix::Math::Vector3 Orig, End;
    Matrix::Math::Vector3 Point[4];
    GetPoint(Point);
    for (int i = 0; i < 4; i++)
    {
        int j = i + 1;
        if (j == 4)
            j = 0;
        SegmentTemp.Set(Point[i], Point[j]);
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
    if (OnNum == 4)
        return IT_On;
    if (BackNum == 4)
        return IT_Back;
    if (FrontNum == 4)
        return IT_Front;
    // not control all path
    return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Rectangle3::RelationWith(const Triangle3 &Triangle, Segment3 &Segment) const
{

    return Triangle.RelationWith(*this, Segment);
}
/*----------------------------------------------------------------*/
int Rectangle3::RelationWith(const Rectangle3 &Rectangle, Segment3 &Segment) const
{
    Segment3 SegmentTemp;
    int InNum = 0;
    Matrix::Math::Vector3 Orig, End;
    Matrix::Math::Vector3 Point[4];
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
    if (!InNum)
        return IT_NoIntersect;
    // not control all path
    return IT_Intersect;
}