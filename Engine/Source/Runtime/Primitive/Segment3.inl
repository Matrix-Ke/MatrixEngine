inline const Matrix::Math::Vector3& Segment3::GetEnd() const
{
	return m_End;
}
/*----------------------------------------------------------------*/
inline VSREAL Segment3::GetLen()const
{
	return m_fLen;
}
/*----------------------------------------------------------------*/
inline void Segment3::Set(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& End)
{
	Matrix::Math::Vector3 Dir = End - Orig;
	m_fLen = Dir.GetLength();

	Matrix::Primitive::Line3::Set(Orig, Dir);

}
/*----------------------------------------------------------------*/
inline void Segment3::Set(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& Dir, VSREAL fLen)
{


	Matrix::Primitive::Line3::Set(Orig, Dir);
	m_fLen = fLen;
	m_End = Orig + (m_Dir * m_fLen);

}
/*----------------------------------------------------------------*/
inline Matrix::Math::Vector3 Segment3::GetParameterPoint(VSREAL fSegmentParameter)const
{
	if (fSegmentParameter > m_fLen)
		fSegmentParameter = m_fLen;

	return Ray3::GetParameterPoint(fSegmentParameter);
}
/*----------------------------------------------------------------*/