/*----------------------------------------------------------------*/
inline const Matrix::Math::VSVector3& VSPlane3::GetN()const
{
	return m_N;
}
/*----------------------------------------------------------------*/
inline Matrix::Math::VSVector3 VSPlane3::GetPoint()const
{
	if (Math::ABS(m_N.z) < EPSILON_E4)
	{
		return Matrix::Math::VSVector3(0.0f, 0.0f, 0.0f);
	}
	return Matrix::Math::VSVector3(0.0f, 0.0f, -m_fD / m_N.z);
}
/*----------------------------------------------------------------*/
inline VSREAL VSPlane3::GetfD()const
{
	return m_fD;
}
/*----------------------------------------------------------------*/
inline void VSPlane3::Set(const Matrix::Math::VSVector3& N, const Matrix::Math::VSVector3& P)
{
	m_N = N;
	m_N.Normalize();
	m_fD = -(m_N.Dot(P));
}
/*----------------------------------------------------------------*/
inline void VSPlane3::Set(const Matrix::Math::VSVector3& P0, const Matrix::Math::VSVector3& P1, const Matrix::Math::VSVector3& P2)
{
	Matrix::Math::VSVector3 vcEdge1 = P1 - P0;
	Matrix::Math::VSVector3 vcEdge2 = P2 - P0;

	m_N.Cross(vcEdge1, vcEdge2);
	m_N.Normalize();
	m_fD = -(m_N.Dot(P0));
}
/*----------------------------------------------------------------*/
inline void  VSPlane3::Set(const Matrix::Math::VSVector3 Point[3])
{

	Set(Point[0], Point[1], Point[2]);
}
/*----------------------------------------------------------------*/
inline VSPlane3 VSPlane3::GetPlane()const
{
	return *this;

}
/*----------------------------------------------------------------*/
inline void  VSPlane3::Set(const Matrix::Math::VSVector3& N, VSREAL fD)
{
	VSREAL Len = N.GetLength();
	m_N = N / Len;

	m_fD = fD / Len;
}