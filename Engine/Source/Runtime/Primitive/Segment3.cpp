#include "Segment3.h"
using namespace Matrix::Primitive;

/*----------------------------------------------------------------*/
VSSegment3::VSSegment3()
{
}
/*----------------------------------------------------------------*/
VSSegment3::~VSSegment3()
{
}
/*----------------------------------------------------------------*/
VSSegment3::VSSegment3(const Matrix::Math::VSVector3 &Orig, const Matrix::Math::VSVector3 &End)
{
    Set(Orig, End);
}
/*----------------------------------------------------------------*/
VSSegment3::VSSegment3(const Matrix::Math::VSVector3 &Orig, const Matrix::Math::VSVector3 &Dir, VSREAL fLen)
{
    Set(Orig, Dir, fLen);
}
/*----------------------------------------------------------------*/
void VSSegment3::Transform(const VSSegment3 &Segment, const Matrix::Math::VSMatrix3X3W &Mat)
{

    m_Orig = Mat * Segment.m_Orig;
    m_End = Mat * Segment.m_End;
    m_Dir = Mat.Apply3X3(Segment.m_Dir);
    m_Dir.Normalize();
    m_fLen = Segment.m_fLen;
}
/*----------------------------------------------------------------*/
bool VSSegment3::GetParameter(const Matrix::Math::VSVector3 &Point, VSREAL &fSegmentParameter) const
{
    if (!VSRay3::GetParameter(Point, fSegmentParameter))
        return 0;
    if (fSegmentParameter > m_fLen)
        return 0;
    return 1;
}