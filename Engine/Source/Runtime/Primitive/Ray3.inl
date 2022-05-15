inline Matrix::Math::Vector3 Ray3::GetParameterPoint(VSREAL fRayParameter) const
{
	if (fRayParameter < 0)
		fRayParameter = 0;
	return Line3::GetParameterPoint(fRayParameter);
}
/*----------------------------------------------------------------*/