#pragma once
#include "CMathInterface.h"

namespace Matrix
{
	namespace Math
	{
		class VSVector3;
		class VSVector3W;
		class VSMatrix3X3;
		class  VSQuat;

		class MATRIX_MATH_API VSMathInstance
		{
		public:
			VSMathInstance();
			~VSMathInstance();
			VSREAL GetFastSin(unsigned int i);
			VSREAL GetFastCos(unsigned int i);
			unsigned int CRC32Compute(const void* pData, unsigned int uiDataSize);

			static VSMathInstance& GetMathInstance()
			{
				static VSMathInstance g_MathInitial;
				return g_MathInitial;
			}
		protected:
			void VSInitCRCTable();
			VSREAL FastSin[361];
			VSREAL FastCos[361];
			unsigned int CRCTable[256];
		};

		bool MATRIX_MATH_API VSInitMath();

		inline unsigned int GetTypeHash(const TCHAR* A)
		{
			return VSMathInstance::GetMathInstance().CRC32Compute(A, (unsigned int)_tcslen(A));
		}


		bool MATRIX_MATH_API IsUniformScale(VSREAL fScale);
		bool MATRIX_MATH_API IsZeroTranslate(const VSVector3& Translate);
		bool MATRIX_MATH_API IsIdentityRotate(const VSMatrix3X3& Rotate);
		bool MATRIX_MATH_API IsIdentityRotate(const VSQuat& Rotate);


		VSREAL MATRIX_MATH_API LineInterpolation(VSREAL t1, VSREAL t2, VSREAL t);
		VSVector3 MATRIX_MATH_API LineInterpolation(const VSVector3& t1, const VSVector3& t2, VSREAL t);
		VSQuat MATRIX_MATH_API LineInterpolation(const VSQuat& t1, const VSQuat& t2, VSREAL t);
		VSVector3W MATRIX_MATH_API LineInterpolation(const VSVector3W& t1, const VSVector3W& t2, VSREAL t);


	}
}
