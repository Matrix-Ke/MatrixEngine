/*----------------------------------------------------------------*/
inline void VSRectangle3::Set(const Matrix::Math::VSVector3& Center, const Matrix::Math::VSVector3& A0, const Matrix::Math::VSVector3& A1, VSREAL fA0, VSREAL fA1)
{
	m_Center = Center;
	m_A[0] = A0;
	m_A[1] = A1;
	m_A[0].Normalize();
	m_A[1].Normalize();
	m_fA[0] = Math::ABS(fA0);
	m_fA[1] = Math::ABS(fA1);
	Matrix::Math::VSVector3 N;
	N.Cross(A0, A1);
	VSPlane3::Set(N, Center);

}
/*----------------------------------------------------------------*/
inline void VSRectangle3::Set(const Matrix::Math::VSVector3& Center, const Matrix::Math::VSVector3 A[2], const VSREAL fA[2])
{
	Set(Center, A[0], A[1], fA[0], fA[1]);

}
/*----------------------------------------------------------------*/
inline void VSRectangle3::GetA(Matrix::Math::VSVector3 A[2])const
{
	A[0] = m_A[0];
	A[1] = m_A[1];
}
/*----------------------------------------------------------------*/
inline void VSRectangle3::GetfA(VSREAL fA[2])const
{
	fA[0] = m_fA[0];
	fA[1] = m_fA[1];

}
/*----------------------------------------------------------------*/
inline const Matrix::Math::VSVector3& VSRectangle3::GetCenter()const
{
	return m_Center;

}
/*----------------------------------------------------------------*/
inline Matrix::Math::VSVector3 VSRectangle3::GetParameterPoint(VSREAL fRectangleParameter[2])const
{
	return (m_Center + m_A[0] * fRectangleParameter[0] + m_A[1] * fRectangleParameter[1]);
}
/*----------------------------------------------------------------*/
inline Matrix::Math::VSVector3 VSRectangle3::GetParameterPoint(VSREAL fRectangleParameter0, VSREAL fRectangleParameter1)const
{
	return (m_Center + m_A[0] * fRectangleParameter0 + m_A[1] * fRectangleParameter1);
}