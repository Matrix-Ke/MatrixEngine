/*----------------------------------------------------------------*/
inline const Matrix::Math::Vector3& Plane3::GetN()const
{
	return m_N;
}
/*----------------------------------------------------------------*/
inline Matrix::Math::Vector3 Plane3::GetPoint()const
{
	if (Math::ABS(m_N.z) < EPSILON_E4)
	{
		return Matrix::Math::Vector3(0.0f, 0.0f, 0.0f);
	}
	return Matrix::Math::Vector3(0.0f, 0.0f, -m_fD / m_N.z);
}
/*----------------------------------------------------------------*/
inline VSREAL Plane3::GetfD()const
{
	return m_fD;
}
/*----------------------------------------------------------------*/
inline void Plane3::Set(const Matrix::Math::Vector3& N, const Matrix::Math::Vector3& P)
{
	m_N = N;
	m_N.Normalize();
	m_fD = -(m_N.Dot(P));
}
/*----------------------------------------------------------------*/
inline void Plane3::Set(const Matrix::Math::Vector3& P0, const Matrix::Math::Vector3& P1, const Matrix::Math::Vector3& P2)
{
	Matrix::Math::Vector3 vcEdge1 = P1 - P0;
	Matrix::Math::Vector3 vcEdge2 = P2 - P0;

	m_N.Cross(vcEdge1, vcEdge2);
	m_N.Normalize();
	m_fD = -(m_N.Dot(P0));
}
/*----------------------------------------------------------------*/
inline void  Plane3::Set(const Matrix::Math::Vector3 Point[3])
{

	Set(Point[0], Point[1], Point[2]);
}
/*----------------------------------------------------------------*/
inline Plane3 Plane3::GetPlane()const
{
	return *this;

}
/*----------------------------------------------------------------*/
inline void  Plane3::Set(const Matrix::Math::Vector3& N, VSREAL fD)
{
	VSREAL Len = N.GetLength();
	m_N = N / Len;

	m_fD = fD / Len;
}