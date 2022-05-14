#include "SegmentCurve3.h"

using namespace Matrix::Primitive;

SegmentCurve3::SegmentCurve3()
{
}
/*----------------------------------------------------------------*/
SegmentCurve3::~SegmentCurve3()
{
}
/*----------------------------------------------------------------*/
void SegmentCurve3::Set(const Segment3& Segment)
{

	m_Segment = Segment;
}
/*----------------------------------------------------------------*/
Segment3& SegmentCurve3::GetSegment()
{
	return m_Segment;
}
/*----------------------------------------------------------------*/