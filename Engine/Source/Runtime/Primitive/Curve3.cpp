#include "Curve3.h"
#include "Math/Matrix3X3W.h"

using namespace Matrix::Primitive;

VSCurve3::VSCurve3()
{
}
/*----------------------------------------------------------------*/
VSCurve3::~VSCurve3()
{
}
/*----------------------------------------------------------------*/
void VSCurve3::GetFixedUpBNT(VSREAL t, Math::VSVector3 &B, Math::VSVector3 &N, Math::VSVector3 &T)
{
    Math::VSMatrix3X3W Mat;
    Math::VSVector3 Point(0, 0, 0);
    Math::VSVector3 FD = GetFirstDerivative(t);
    FD.Normalize();
    Mat.CreateFromLookAt(Point, FD);
    B.x = Mat._00;
    B.y = Mat._10;
    B.z = Mat._20;

    N.x = Mat._01;
    N.y = Mat._11;
    N.z = Mat._21;

    T.x = Mat._02;
    T.y = Mat._12;
    T.z = Mat._22;
}
/*----------------------------------------------------------------*/