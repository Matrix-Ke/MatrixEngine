inline Matrix::Math::VSVector3 VSRay3::GetParameterPoint(VSREAL fRayParameter)const
{
	if (fRayParameter < 0)
		fRayParameter = 0;
	return Matrix::Primitive::VSLine3::GetParameterPoint(fRayParameter);
}
/*----------------------------------------------------------------*/