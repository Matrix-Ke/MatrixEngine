#include "VSLine3.h"
#include "Math/VSMatrix3X3W.h"

using namespace Matrix::Math;
/*----------------------------------------------------------------*/
Matrix::Primitive::VSLine3::VSLine3()
{


}
/*----------------------------------------------------------------*/
Matrix::Primitive::VSLine3::VSLine3(const Matrix::Math::VSVector3& Orig, const Matrix::Math::VSVector3& Dir)
{
	Set(Orig, Dir);

}
/*----------------------------------------------------------------*/
Matrix::Primitive::VSLine3::~VSLine3()
{


}
/*----------------------------------------------------------------*/
bool Matrix::Primitive::VSLine3::GetParameter(const Matrix::Math::VSVector3& Point, VSREAL& fLineParameter)const
{
	Matrix::Math::VSVector3 Temp = Point - m_Orig;
	if (Temp.IsParallel(m_Dir))
	{
		fLineParameter = Temp.GetLength();
		return 1;
	}
	else
		return 0;
}
/*----------------------------------------------------------------*/
void Matrix::Primitive::VSLine3::Transform(const VSLine3& Line, const Matrix::Math::VSMatrix3X3W& Mat)
{
	m_Dir = Mat.Apply3X3(Line.m_Dir);
	m_Dir.Normalize();
	m_Orig = Line.m_Orig * Mat;

}