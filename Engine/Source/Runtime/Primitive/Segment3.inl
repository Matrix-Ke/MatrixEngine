inline const Matrix::Math::VSVector3& VSSegment3::GetEnd()const
{
	return m_End;
}
/*----------------------------------------------------------------*/
inline VSREAL VSSegment3::GetLen()const
{
	return m_fLen;
}
/*----------------------------------------------------------------*/
inline void VSSegment3::Set(const Matrix::Math::VSVector3& Orig, const Matrix::Math::VSVector3& End)
{
	Matrix::Math::VSVector3 Dir = End - Orig;
	m_fLen = Dir.GetLength();

	Matrix::Primitive::VSLine3::Set(Orig, Dir);

}
/*----------------------------------------------------------------*/
inline void VSSegment3::Set(const Matrix::Math::VSVector3& Orig, const Matrix::Math::VSVector3& Dir, VSREAL fLen)
{


	Matrix::Primitive::VSLine3::Set(Orig, Dir);
	m_fLen = fLen;
	m_End = Orig + (m_Dir * m_fLen);

}
/*----------------------------------------------------------------*/
inline Matrix::Math::VSVector3 VSSegment3::GetParameterPoint(VSREAL fSegmentParameter)const
{
	if (fSegmentParameter > m_fLen)
		fSegmentParameter = m_fLen;

	return VSRay3::GetParameterPoint(fSegmentParameter);
}
/*----------------------------------------------------------------*/