#include "Curve3.h"
#include "Math/Matrix4.h"

using namespace Matrix::Primitive;

Curve3::Curve3()
{
}
/*----------------------------------------------------------------*/
Curve3::~Curve3()
{
}
/*----------------------------------------------------------------*/
void Curve3::GetFixedUpBNT(VSREAL t, Math::Vector3 &B, Math::Vector3 &N, Math::Vector3 &T)
{
    Math::Matrix4 Mat;
    Math::Vector3 Point(0, 0, 0);
    Math::Vector3 FD = GetFirstDerivative(t);
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