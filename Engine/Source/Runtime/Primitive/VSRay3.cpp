#include "VSRay3.h"
using namespace Matrix::Primitive;
/*----------------------------------------------------------------*/
VSRay3::VSRay3()
{


}
/*----------------------------------------------------------------*/
VSRay3::VSRay3(const Matrix::Math::VSVector3& Orig, const Matrix::Math::VSVector3& Dir)
{
	Set(Orig, Dir);
}
/*----------------------------------------------------------------*/
VSRay3::~VSRay3()
{


}
/*----------------------------------------------------------------*/
bool VSRay3::GetParameter(const Matrix::Math::VSVector3& Point, VSREAL& fRayParameter)const
{
	if (!Matrix::Primitive::VSLine3::GetParameter(Point, fRayParameter))
		return 0;

	if (fRayParameter < 0)
		return 0;

	return 1;

}
/*----------------------------------------------------------------*/
void VSRay3::Transform(const VSRay3& Ray, const Matrix::Math::VSMatrix3X3W& Mat)
{

	Matrix::Primitive::VSLine3::Transform(Ray, Mat);
}