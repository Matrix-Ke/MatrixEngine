#include "Line3.h"
#include "Math/Matrix3X3W.h"

using namespace Matrix::Math;
/*----------------------------------------------------------------*/
Matrix::Primitive::Line3::Line3()
{
}
/*----------------------------------------------------------------*/
Matrix::Primitive::Line3::Line3(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& Dir)
{
	Set(Orig, Dir);
}
/*----------------------------------------------------------------*/
Matrix::Primitive::Line3::~Line3()
{
}
/*----------------------------------------------------------------*/
bool Matrix::Primitive::Line3::GetParameter(const Matrix::Math::Vector3& Point, VSREAL& fLineParameter) const
{
	Matrix::Math::Vector3 Temp = Point - m_Orig;
	if (Temp.IsParallel(m_Dir))
	{
		fLineParameter = Temp.GetLength();
		return 1;
	}
	else
		return 0;
}
/*----------------------------------------------------------------*/
void Matrix::Primitive::Line3::Transform(const Line3& Line, const Matrix::Math::Matrix4& Mat)
{
	m_Dir = Mat.Apply3X3(Line.m_Dir);
	m_Dir.Normalize();
	m_Orig = Line.m_Orig * Mat;
}