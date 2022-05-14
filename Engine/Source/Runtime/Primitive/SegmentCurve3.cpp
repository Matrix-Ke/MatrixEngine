#include "SegmentCurve3.h"

using namespace Matrix::Primitive;

VSSegmentCurve3::VSSegmentCurve3()
{
}
/*----------------------------------------------------------------*/
VSSegmentCurve3::~VSSegmentCurve3()
{
}
/*----------------------------------------------------------------*/
void VSSegmentCurve3::Set(const VSSegment3 &Segment)
{

    m_Segment = Segment;
}
/*----------------------------------------------------------------*/
VSSegment3 &VSSegmentCurve3::GetSegment()
{
    return m_Segment;
}
/*----------------------------------------------------------------*/