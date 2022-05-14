/*----------------------------------------------------------------*/
inline void Rectangle3::Set(const Matrix::Math::Vector3& Center, const Matrix::Math::Vector3& A0, const Matrix::Math::Vector3& A1, VSREAL fA0, VSREAL fA1)
{
	m_Center = Center;
	m_A[0] = A0;
	m_A[1] = A1;
	m_A[0].Normalize();
	m_A[1].Normalize();
	m_fA[0] = Math::ABS(fA0);
	m_fA[1] = Math::ABS(fA1);
	Matrix::Math::Vector3 N;
	N.Cross(A0, A1);
	Plane3::Set(N, Center);

}
/*----------------------------------------------------------------*/
inline void Rectangle3::Set(const Matrix::Math::Vector3& Center, const Matrix::Math::Vector3 A[2], const VSREAL fA[2])
{
	Set(Center, A[0], A[1], fA[0], fA[1]);

}
/*----------------------------------------------------------------*/
inline void Rectangle3::GetA(Matrix::Math::Vector3 A[2])const
{
	A[0] = m_A[0];
	A[1] = m_A[1];
}
/*----------------------------------------------------------------*/
inline void Rectangle3::GetfA(VSREAL fA[2])const
{
	fA[0] = m_fA[0];
	fA[1] = m_fA[1];

}
/*----------------------------------------------------------------*/
inline const Matrix::Math::Vector3& Rectangle3::GetCenter()const
{
	return m_Center;

}
/*----------------------------------------------------------------*/
inline Matrix::Math::Vector3 Rectangle3::GetParameterPoint(VSREAL fRectangleParameter[2])const
{
	return (m_Center + m_A[0] * fRectangleParameter[0] + m_A[1] * fRectangleParameter[1]);
}
/*----------------------------------------------------------------*/
inline Matrix::Math::Vector3 Rectangle3::GetParameterPoint(VSREAL fRectangleParameter0, VSREAL fRectangleParameter1)const
{
	return (m_Center + m_A[0] * fRectangleParameter0 + m_A[1] * fRectangleParameter1);
}
