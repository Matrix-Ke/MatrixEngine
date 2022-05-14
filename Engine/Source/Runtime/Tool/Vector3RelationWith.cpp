#include "Vector3.h"
#include "Math.h"
#include "Matrix3X3.h"
#include "Quat.h"
#include "Line3.h"
#include "Ray3.h"
#include "Segment3.h"
#include "Triangle3.h"
#include "Rectangle3.h"
#include "OBB3.h"
#include "Sphere3.h"
#include "AABB3.h"
using namespace Matrix;
/*----------------------------------------------------------------*/
int VSVector3::RelationWith(const Sphere3& Sphere) const
{
	VSREAL sqrDist = SquaredDistance(Sphere.m_Center);
	VSREAL diff = sqrDist - Sphere.m_fRadius * Sphere.m_fRadius;
	if (diff > EPSILON_E4)
		return VSOUT;
	else if (diff < -EPSILON_E4)
		return VSIN;
	else
		return VSON;
}
/*----------------------------------------------------------------*/
int VSVector3::RelationWith(const Plane3& Plane) const
{
	return Plane.RelationWith(*this);
}
/*----------------------------------------------------------------*/
int VSVector3::RelationWith(const VSOBB3& OBB) const
{
	VSMatrix3X3W m;
	OBB.GetTransform(m);
	VSVector3 PointTemp = *this * m;
	VSREAL fA[3];
	OBB.GetfA(fA);
	VSREAL fDiffX = ABS(PointTemp.x) - fA[0];
	VSREAL fDiffY = ABS(PointTemp.y) - fA[1];
	VSREAL fDiffZ = ABS(PointTemp.z) - fA[2];

	if (fDiffX > EPSILON_E4 || fDiffY > EPSILON_E4 || fDiffZ > EPSILON_E4)
		return VSOUT;

	if (fDiffX < -EPSILON_E4 || fDiffY < -EPSILON_E4 || fDiffZ < -EPSILON_E4)
		return VSIN;

	return VSON;
}
/*----------------------------------------------------------------*/
// VSIN VSOUT VSON
int VSVector3::RelationWith(const AABB3& AABB) const
{

	return AABB.RelationWith(*this);
}