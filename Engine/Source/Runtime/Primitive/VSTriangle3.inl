inline void VSTriangle3::Set(const Matrix::Math::VSVector3 & P0,const Matrix::Math::VSVector3 &P1,const Matrix::Math::VSVector3 &P2)
{
	m_V[0] = P0;
	m_V[2] = P2;
	m_V[1] = P1;
	VSPlane3::Set(m_V);
}
/*----------------------------------------------------------------*/
inline void VSTriangle3::Set(const Matrix::Math::VSVector3 Point[3])
{
	m_V[0] = Point[0];
	m_V[2] = Point[2];
	m_V[1] = Point[1];
	VSPlane3::Set(m_V);
}
/*----------------------------------------------------------------*/
inline void VSTriangle3::GetPoint(Matrix::Math::VSVector3  Point[3])const
{
	Point[0] = m_V[0];
	Point[1] = m_V[1];
	Point[2] = m_V[2];


}
/*----------------------------------------------------------------*/
inline Matrix::Math::VSVector3 VSTriangle3::GetParameterPoint(VSREAL fTriangleParameter[3])const
{
	return (m_V[0] * fTriangleParameter[0] + m_V[1] * fTriangleParameter[1] + m_V[2] * fTriangleParameter[2]);

}
/*----------------------------------------------------------------*/
inline Matrix::Math::VSVector3 VSTriangle3::GetParameterPoint(VSREAL fTriangleParameter0,
								  VSREAL fTriangleParameter1,VSREAL fTriangleParameter2)const
{

	return (m_V[0] * fTriangleParameter0 + m_V[1] * fTriangleParameter1 + m_V[2] * fTriangleParameter2);
}
/*----------------------------------------------------------------*/