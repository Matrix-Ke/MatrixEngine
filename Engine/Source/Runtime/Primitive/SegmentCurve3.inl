inline void SegmentCurve3::GetFrenetFrameBNT(VSREAL t, Matrix::Math::Vector3& B, Matrix::Math::Vector3& N, Matrix::Math::Vector3& T)
{
	Curve3::GetFixedUpBNT(t, B, N, T);
}
/*----------------------------------------------------------------*/
inline Matrix::Math::Vector3	SegmentCurve3::GetFirstDerivative(VSREAL t)
{

	return m_Segment.GetDir() * m_Segment.GetLen();
}
/*----------------------------------------------------------------*/
inline Matrix::Math::Vector3	SegmentCurve3::GetSecondDerivative(VSREAL t)
{
	return Matrix::Math::Vector3(0, 0, 0);
}
/*----------------------------------------------------------------*/
inline Matrix::Math::Vector3	SegmentCurve3::GetThirdDerivative(VSREAL t)
{

	return Matrix::Math::Vector3(0, 0, 0);
}
/*----------------------------------------------------------------*/
inline VSREAL		SegmentCurve3::GetLength(VSREAL t1, VSREAL t2, unsigned int uiIterations)
{

	return m_Segment.GetLen() * (t2 - t1);
}
/*----------------------------------------------------------------*/
inline Matrix::Math::Vector3	SegmentCurve3::GetPoint(VSREAL t)
{
	return m_Segment.GetParameterPoint(t * m_Segment.GetLen());
}
/*----------------------------------------------------------------*/
inline VSREAL		SegmentCurve3::GetTotalLength(unsigned int uiIterations)
{
	return m_Segment.GetLen();

}
/*----------------------------------------------------------------*/
inline VSREAL SegmentCurve3::GetTime(VSREAL fLength, unsigned int uiIterations,
	VSREAL fTolerance)
{
	return fLength / m_Segment.GetLen();

}
/*----------------------------------------------------------------*/
inline VSREAL SegmentCurve3::GetCurvature(VSREAL fTime)
{
	return 0;
}
/*----------------------------------------------------------------*/
inline VSREAL SegmentCurve3::GetTorsion(VSREAL fTime)
{
	return 0;
}
/*----------------------------------------------------------------*/