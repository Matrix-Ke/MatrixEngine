#include "Ray3.h"
using namespace Matrix::Primitive;
/*----------------------------------------------------------------*/
Ray3::Ray3()
{
}
/*----------------------------------------------------------------*/
Ray3::Ray3(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& Dir)
{
	Set(Orig, Dir);
}
/*----------------------------------------------------------------*/
Ray3::~Ray3()
{
}
/*----------------------------------------------------------------*/
bool Ray3::GetParameter(const Matrix::Math::Vector3& Point, VSREAL& fRayParameter) const
{
	if (!Matrix::Primitive::Line3::GetParameter(Point, fRayParameter))
		return 0;

	if (fRayParameter < 0)
		return 0;

	return 1;
}
/*----------------------------------------------------------------*/
void Ray3::Transform(const Ray3& Ray, const Matrix::Math::Matrix4& Mat)
{

	Matrix::Primitive::Line3::Transform(Ray, Mat);
}