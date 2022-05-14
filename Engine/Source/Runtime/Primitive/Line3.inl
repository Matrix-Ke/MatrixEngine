/*----------------------------------------------------------------*/
void Matrix::Primitive::Line3::Set(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& Dir)
{
	m_Orig = Orig;
	m_Dir = Dir;
	m_Dir.Normalize();
}
/*----------------------------------------------------------------*/
inline const Matrix::Math::Vector3& Matrix::Primitive::Line3::GetOrig()const
{
	return m_Orig;
}
/*----------------------------------------------------------------*/
inline const Matrix::Math::Vector3& Matrix::Primitive::Line3::GetDir()const
{
	return m_Dir;
}
/*----------------------------------------------------------------*/
inline Matrix::Math::Vector3 Matrix::Primitive::Line3::GetParameterPoint(VSREAL fLineParameter)const
{
	return  (m_Orig + m_Dir * fLineParameter);

}
/*----------------------------------------------------------------*/
