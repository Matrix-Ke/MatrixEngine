#pragma once
#include "Line3.h"
#include "Math/Matrix3.h"
#include "Platform/MemoryManager.h"
/*
������

*/
namespace Matrix
{
    namespace Primitive
    {
        class MATRIX_PRIMITIVE_API Curve3 : public Core::MemoryObject
        {
        public:
            enum // CURVE TYPE
            {
                CT_SEGMENT,
                CT_CONTROL,
                CT_MAX
            };
            Curve3();
            virtual ~Curve3() = 0;

            virtual unsigned int GetCurveType() = 0;
            //���FrenetFrame3������
            virtual void GetFrenetFrameBNT(VSREAL t, Math::Vector3 &B, Math::Vector3 &N, Math::Vector3 &T) = 0;
            //���FixedUp3������
            void GetFixedUpBNT(VSREAL t, Math::Vector3 &B, Math::Vector3 &N, Math::Vector3 &T);
            //����
            virtual Math::Vector3 GetFirstDerivative(VSREAL t) = 0;
            virtual Math::Vector3 GetSecondDerivative(VSREAL t) = 0;
            virtual Math::Vector3 GetThirdDerivative(VSREAL t) = 0;
            //�󳤶�
            virtual VSREAL GetLength(VSREAL t1, VSREAL t2, unsigned int uiIterations) = 0;
            //���
            virtual Math::Vector3 GetPoint(VSREAL t) = 0;
            //���ܳ�
            virtual VSREAL GetTotalLength(unsigned int uiIterations) = 0;
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