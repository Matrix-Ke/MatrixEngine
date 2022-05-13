#pragma once
#include "MathInterface.h"

namespace Matrix
{
	namespace Math
	{
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

	}
}
