#include "Plane3.h"
#include "Line3.h"
#include "Math/Vector3.h"
#include "Math/Matrix3X3W.h"

using namespace Matrix::Primitive;
/*----------------------------------------------------------------*/
Plane3::Plane3()
{
	m_fD = 0.0f;
}
/*----------------------------------------------------------------*/
Plane3::Plane3(const Matrix::Math::Vector3& N, VSREAL fD)
{
	Set(N, fD);
}
/*----------------------------------------------------------------*/
Plane3::Plane3(const Matrix::Math::Vector3& N, const Matrix::Math::Vector3& P)
{
	Set(N, P);
}
/*----------------------------------------------------------------*/
Plane3::Plane3(const Matrix::Math::Vector3& P0, const Matrix::Math::Vector3& P1, const Matrix::Math::Vector3& P2)
{
	Set(P0, P1, P2);
}
/*----------------------------------------------------------------*/
Plane3::Plane3(const Matrix::Math::Vector3 Point[3])
{
	Set(Point[0], Point[1], Point[2]);
}
/*----------------------------------------------------------------*/
void Plane3::Transform(const Plane3& Plane, const Matrix::Math::Matrix4& Mat)
{
	Matrix::Math::Vector4 Temp(m_N.x, m_N.y, m_N.z, m_fD);

	Matrix::Math::Matrix4 Inv;
	Inv.InverseOf(Mat);
	Matrix::Math::Matrix4 Transpose;
	Transpose.TransposeOf(Inv);
	Matrix::Math::Vector4 Resoult = Temp * Transpose;
	Set(Matrix::Math::Vector3(Resoult.x, Resoult.y, Resoult.z), Resoult.w);
}
Matrix::Math::Vector3 Plane3::ReflectDir(const Matrix::Math::Vector3& Dir) const
{
	Matrix::Math::Vector3 TempN = m_N * (-1.0f);

	return Dir - m_N * Dir.Dot(m_N) * 2.0f;
}
void Plane3::GetReverse(Plane3& OutPlane) const
{
	OutPlane.Set(m_N * (-1.0f), -m_fD);
}
