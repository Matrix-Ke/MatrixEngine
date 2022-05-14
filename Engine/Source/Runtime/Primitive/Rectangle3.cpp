#include "Rectangle3.h"
#include "Math/Matrix3X3W.h"

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
Rectangle3::Rectangle3(const Matrix::Math::Vector3& Center, const Matrix::Math::Vector3& A0, const Matrix::Math::Vector3& A1, VSREAL fA0, VSREAL fA1)
{
	Set(Center, A0, A1, fA0, fA1);
}
/*----------------------------------------------------------------*/
Rectangle3::Rectangle3(const Matrix::Math::Vector3& Center, const Matrix::Math::Vector3 A[2], const VSREAL fA[2])
{
	Set(Center, A, fA);
}
/*----------------------------------------------------------------*/
bool Rectangle3::GetParameter(const Matrix::Math::Vector3& Point, VSREAL fRectangleParameter[2]) const
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
void Rectangle3::Transform(const Rectangle3& Rectangle,
	const Matrix::Math::Matrix4& Mat)
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
