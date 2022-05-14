/*----------------------------------------------------------------*/
void Matrix::Primitive::VSLine3::Set(const Matrix::Math::VSVector3& Orig, const Matrix::Math::VSVector3& Dir)
{
	m_Orig = Orig;
	m_Dir = Dir;
	m_Dir.Normalize();
}
/*----------------------------------------------------------------*/
inline const Matrix::Math::VSVector3& Matrix::Primitive::VSLine3::GetOrig()const
{
	return m_Orig;
}
/*----------------------------------------------------------------*/
inline const Matrix::Math::VSVector3& Matrix::Primitive::VSLine3::GetDir()const
{
	return m_Dir;
}
/*----------------------------------------------------------------*/
inline Matrix::Math::VSVector3 Matrix::Primitive::VSLine3::GetParameterPoint(VSREAL fLineParameter)const
{
	return  (m_Orig + m_Dir * fLineParameter);

}
/*----------------------------------------------------------------*/
