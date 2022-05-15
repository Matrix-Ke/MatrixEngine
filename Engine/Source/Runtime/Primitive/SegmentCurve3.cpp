#include "SegmentCurve3.h"
#include "Ray3.h"
#include "Segment3.h"

#include "Plane3.h"
#include "Triangle3.h"
#include "Rectangle3.h"
#include "Polygon3.h"

#include "OBB3.h"
#include "AABB3.h"
#include "Sphere3.h"

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