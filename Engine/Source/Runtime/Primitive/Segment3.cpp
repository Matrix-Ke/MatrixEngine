#include "Segment3.h"
using namespace Matrix::Primitive;

/*----------------------------------------------------------------*/
Segment3::Segment3()
{
}
/*----------------------------------------------------------------*/
Segment3::~Segment3()
{
}
/*----------------------------------------------------------------*/
Segment3::Segment3(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& End)
{
	Set(Orig, End);
}
/*----------------------------------------------------------------*/
Segment3::Segment3(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& Dir, VSREAL fLen)
{
	Set(Orig, Dir, fLen);
}
/*----------------------------------------------------------------*/
void Segment3::Transform(const Segment3& Segment, const Matrix::Math::Matrix4& Mat)
{

	m_Orig = Mat * Segment.m_Orig;
	m_End = Mat * Segment.m_End;
	m_Dir = Mat.Apply3X3(Segment.m_Dir);
	m_Dir.Normalize();
	m_fLen = Segment.m_fLen;
}
/*----------------------------------------------------------------*/
bool Segment3::GetParameter(const Matrix::Math::Vector3& Point, VSREAL& fSegmentParameter) const
{
	if (!Ray3::GetParameter(Point, fSegmentParameter))
		return 0;
	if (fSegmentParameter > m_fLen)
		return 0;
	return 1;
}