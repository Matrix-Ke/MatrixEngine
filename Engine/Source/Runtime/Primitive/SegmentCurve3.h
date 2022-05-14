#pragma once
#include "Curve3.h"
#include "Segment3.h"
/*
ÇúÏß¶Î

*/
namespace Matrix
{
	namespace Primitive
	{
		class MATRIX_PRIMITIVE_API SegmentCurve3 : public Curve3
		{
		public:
			SegmentCurve3();
			~SegmentCurve3();
			void Set(const Segment3& Segment);
			Segment3& GetSegment();
			virtual unsigned int GetCurveType() { return CT_SEGMENT; }
			virtual void GetFrenetFrameBNT(VSREAL t, Matrix::Math::Vector3& B, Matrix::Math::Vector3& N, Matrix::Math::Vector3& T);
			inline virtual Matrix::Math::Vector3 GetFirstDerivative(VSREAL t);
			inline virtual Matrix::Math::Vector3 GetSecondDerivative(VSREAL t);
			inline virtual Matrix::Math::Vector3 GetThirdDerivative(VSREAL t);
			inline virtual VSREAL GetLength(VSREAL t1, VSREAL t2, unsigned int uiIterations);
			inline virtual Matrix::Math::Vector3 GetPoint(VSREAL t);
			inline virtual VSREAL GetTotalLength(unsigned int uiIterations);
			inline virtual VSREAL GetTime(VSREAL fLength, unsigned int uiIterations = 32,
				VSREAL fTolerance = EPSILON_E4);
			inline virtual VSREAL GetCurvature(VSREAL fTime);
			inline virtual VSREAL GetTorsion(VSREAL fTime);

		private:
			Segment3 m_Segment;
		};

#include "SegmentCurve3.inl"
	}
}