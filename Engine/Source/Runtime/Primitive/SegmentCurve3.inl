inline void VSSegmentCurve3::GetFrenetFrameBNT(VSREAL t,Matrix::Math::VSVector3 & B,Matrix::Math::VSVector3 & N,Matrix::Math::VSVector3 &T)
{
	VSCurve3::GetFixedUpBNT(t,B,N,T);
}
/*----------------------------------------------------------------*/
inline Matrix::Math::VSVector3	VSSegmentCurve3::GetFirstDerivative(VSREAL t)
{

	return m_Segment.GetDir() * m_Segment.GetLen();
}
/*----------------------------------------------------------------*/
inline Matrix::Math::VSVector3	VSSegmentCurve3::GetSecondDerivative(VSREAL t)
{
	return Matrix::Math::VSVector3(0,0,0);
}
/*----------------------------------------------------------------*/
inline Matrix::Math::VSVector3	VSSegmentCurve3::GetThirdDerivative(VSREAL t)
{

	return Matrix::Math::VSVector3(0,0,0);
}
/*----------------------------------------------------------------*/
inline VSREAL		VSSegmentCurve3::GetLength(VSREAL t1 ,VSREAL t2,unsigned int uiIterations)
{

	return m_Segment.GetLen() * (t2 - t1);
}
/*----------------------------------------------------------------*/
inline Matrix::Math::VSVector3	VSSegmentCurve3::GetPoint(VSREAL t)
{
	return m_Segment.GetParameterPoint(t * m_Segment.GetLen());
}
/*----------------------------------------------------------------*/
inline VSREAL		VSSegmentCurve3::GetTotalLength(unsigned int uiIterations)
{
	return m_Segment.GetLen();

}
/*----------------------------------------------------------------*/
inline VSREAL VSSegmentCurve3::GetTime (VSREAL fLength, unsigned int uiIterations,
					   VSREAL fTolerance)
{
	return fLength / m_Segment.GetLen();

}
/*----------------------------------------------------------------*/
inline VSREAL VSSegmentCurve3::GetCurvature(VSREAL fTime)
{
	return 0;
}
/*----------------------------------------------------------------*/
inline VSREAL VSSegmentCurve3::GetTorsion(VSREAL fTime)
{
	return 0;
}
/*----------------------------------------------------------------*/