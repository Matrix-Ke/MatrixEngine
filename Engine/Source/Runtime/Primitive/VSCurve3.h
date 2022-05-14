#pragma once
#include "VSLine3.h"
#include "Math/VSMatrix3X3.h"
#include "Core/MemoryManager.h"
/*
������

*/
namespace Matrix
{
	namespace Primitive
	{
		class MATRIX_PRIMITIVE_API VSCurve3 : public Core::MemoryObject
		{
		public:
			enum //CURVE TYPE
			{
				CT_SEGMENT,
				CT_CONTROL,
				CT_MAX
			};
			VSCurve3();
			virtual ~VSCurve3() = 0;

			virtual unsigned int GetCurveType() = 0;
			//���FrenetFrame3������
			virtual void GetFrenetFrameBNT(VSREAL t, Math::VSVector3& B, Math::VSVector3& N, Math::VSVector3& T) = 0;
			//���FixedUp3������
			void	GetFixedUpBNT(VSREAL t, Math::VSVector3& B, Math::VSVector3& N, Math::VSVector3& T);
			//����
			virtual Math::VSVector3	GetFirstDerivative(VSREAL t) = 0;
			virtual Math::VSVector3	GetSecondDerivative(VSREAL t) = 0;
			virtual Math::VSVector3	GetThirdDerivative(VSREAL t) = 0;
			//�󳤶�
			virtual VSREAL		GetLength(VSREAL t1, VSREAL t2, unsigned int uiIterations) = 0;
			//���
			virtual Math::VSVector3	GetPoint(VSREAL t) = 0;
			//���ܳ�
			virtual VSREAL		GetTotalLength(unsigned int uiIterations) = 0;
			//���ݳ��ȵõ�ʱ��
			virtual VSREAL GetTime(VSREAL fLength, unsigned int iIterations = 32,
				VSREAL fTolerance = EPSILON_E4) = 0;
			//������
			virtual VSREAL GetCurvature(VSREAL fTime) = 0;
			//��ת��
			virtual VSREAL GetTorsion(VSREAL fTime) = 0;

		};
	}
}