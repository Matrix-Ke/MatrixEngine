#pragma once
#include "VSLine3.h"
#include "Math/VSVector2.h"
#include "Math/VSMath.h"


namespace Matrix
{
	namespace Primitive
	{
		class MATRIX_PRIMITIVE_API VSRect2
		{
		public:
			Math::VSVector2 m_Min;
			Math::VSVector2 m_Max;
			VSRect2(void);
			VSRect2(const Math::VSVector2& Min, const Math::VSVector2& Max);

		};
	}
}