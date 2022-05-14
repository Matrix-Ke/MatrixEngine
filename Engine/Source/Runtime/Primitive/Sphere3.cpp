#include "Sphere3.h"

using namespace Matrix::Primitive;

/*----------------------------------------------------------------*/
Sphere3::Sphere3()
{
}
/*----------------------------------------------------------------*/
Sphere3::~Sphere3()
{
	m_fRadius = 0.0f;
}
/*----------------------------------------------------------------*/
Sphere3::Sphere3(const Matrix::Math::Vector3& Center, VSREAL fRadius)
{
	Set(Center, fRadius);
}
/*----------------------------------------------------------------*/
void Sphere3::CreateSphere(const Matrix::Math::Vector3* pPointArray, unsigned int uiPointNum)
{
	if (!pPointArray || !uiPointNum)
		return;
	Matrix::Math::Vector3 Sum;
	for (unsigned int i = 0; i < uiPointNum; i++)
		Sum += pPointArray[i];
	m_Center = Sum / (uiPointNum * 1.0f);
	VSREAL radiusSqr = 0.0f;
	for (unsigned int i = 0; i < uiPointNum; i++)
	{
		Matrix::Math::Vector3 diff = pPointArray[i] - m_Center;
		VSREAL Temp = diff.GetSqrLength();
		if (Temp > radiusSqr)
			radiusSqr = Temp;
	}
	m_fRadius = SQRT(radiusSqr);
}
/*----------------------------------------------------------------*/
Sphere3 Sphere3::MergeSpheres(const Sphere3& Sphere) const
{
	Sphere3 Temp;
	Matrix::Math::Vector3 CenterDiff = m_Center - Sphere.m_Center;
	VSREAL fRadiusDiff = m_fRadius - Sphere.m_fRadius;
	VSREAL fRadiusDiffSqr = fRadiusDiff * fRadiusDiff;
	VSREAL Lsqr = CenterDiff.GetSqrLength();
	if (fRadiusDiffSqr >= Lsqr)
	{
		if (fRadiusDiff >= 0.0f)
		{
			Temp.m_Center = m_Center;
			Temp.m_fRadius = m_fRadius;
		}
		else
		{
			Temp.m_Center = Sphere.m_Center;
			Temp.m_fRadius = Sphere.m_fRadius;
		}
	}
	else
	{
		VSREAL L = SQRT(Lsqr);
		VSREAL t = (L + m_fRadius - Sphere.m_fRadius) / (2.0f * L);
		Temp.m_Center = Sphere.m_Center + CenterDiff * t;
		Temp.m_fRadius = (L + m_fRadius + Sphere.m_fRadius) / 2.0f;
	}

	return Temp;
}
/*----------------------------------------------------------------*/
void Sphere3::Transform(const Sphere3& Sphere, const Matrix::Math::Matrix4& Mat)
{
	m_Center = Sphere.m_Center * Mat;
	/*Math::VSMatrix3X3 M;
	Mat.Get3X3(M);
	Matrix::Math::Vector3 V[3];
	VSREAL E[3];
	M.GetEigenSystem(E,V);
	VSREAL Max = E[0];
	for(unsigned int i = 1 ; i < 3 ; i++)
	{
	if(Max < E[i])
	Max = E[i];
	}
	m_fRadius = Sphere.m_fRadius * Max;*/
	Matrix::Math::Vector3 V0(1.0f, 0.0f, 0.0f), V1(0.0f, 1.0f, 0.0f), V2(0.0f, 0.0f, 1.0f);
	Matrix::Math::Vector3 Temp0 = Sphere.m_Center + V0 * Sphere.m_fRadius;
	Matrix::Math::Vector3 Temp1 = Sphere.m_Center + V1 * Sphere.m_fRadius;
	Matrix::Math::Vector3 Temp2 = Sphere.m_Center + V2 * Sphere.m_fRadius;

	Temp0 = Temp0 * Mat;
	Temp1 = Temp1 * Mat;
	Temp2 = Temp2 * Mat;

	VSREAL fRadiusTemp;

	m_fRadius = (Temp0 - m_Center).GetLength();

	fRadiusTemp = (Temp1 - m_Center).GetLength();

	if (m_fRadius < fRadiusTemp)
		m_fRadius = fRadiusTemp;

	fRadiusTemp = (Temp2 - m_Center).GetLength();

	if (m_fRadius < fRadiusTemp)
		m_fRadius = fRadiusTemp;
}
AABB3 Sphere3::GetAABB() const
{
	Matrix::Math::Vector3 Max = m_Center + Matrix::Math::Vector3(m_fRadius, m_fRadius, m_fRadius);
	Matrix::Math::Vector3 Min = m_Center + Matrix::Math::Vector3(-m_fRadius, -m_fRadius, -m_fRadius);
	return AABB3(Max, Min);
}