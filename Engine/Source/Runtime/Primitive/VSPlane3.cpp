#include "VSPlane3.h"
#include "VSLine3.h"
#include "Math/VSVector3.h"
#include "Math/VSMatrix3X3W.h"

using namespace Matrix::Primitive;
/*----------------------------------------------------------------*/
VSPlane3::VSPlane3()
{
	m_fD = 0.0f;
}
/*----------------------------------------------------------------*/
VSPlane3::VSPlane3(const Matrix::Math::VSVector3& N, VSREAL fD)
{
	Set(N, fD);
}
/*----------------------------------------------------------------*/
VSPlane3::VSPlane3(const Matrix::Math::VSVector3& N, const Matrix::Math::VSVector3& P)
{
	Set(N, P);

}
/*----------------------------------------------------------------*/
VSPlane3::VSPlane3(const Matrix::Math::VSVector3& P0, const Matrix::Math::VSVector3& P1, const Matrix::Math::VSVector3& P2)
{
	Set(P0, P1, P2);

}
/*----------------------------------------------------------------*/
VSPlane3::VSPlane3(const Matrix::Math::VSVector3 Point[3])
{
	Set(Point[0], Point[1], Point[2]);
}
/*----------------------------------------------------------------*/
void VSPlane3::Transform(const VSPlane3& Plane, const Matrix::Math::VSMatrix3X3W& Mat)
{
	Matrix::Math::VSVector3W Temp(m_N.x, m_N.y, m_N.z, m_fD);


	Matrix::Math::VSMatrix3X3W Inv;
	Inv.InverseOf(Mat);
	Matrix::Math::VSMatrix3X3W Transpose;
	Transpose.TransposeOf(Inv);
	Matrix::Math::VSVector3W Resoult = Temp * Transpose;
	Set(Matrix::Math::VSVector3(Resoult.x, Resoult.y, Resoult.z), Resoult.w);
}
Matrix::Math::VSVector3 VSPlane3::ReflectDir(const Matrix::Math::VSVector3& Dir)const
{
	Matrix::Math::VSVector3 TempN = m_N * (-1.0f);

	return Dir - m_N * Dir.Dot(m_N) * 2.0f;
}
void  VSPlane3::GetReverse(VSPlane3& OutPlane)const
{
	OutPlane.Set(m_N * (-1.0f), -m_fD);
}

