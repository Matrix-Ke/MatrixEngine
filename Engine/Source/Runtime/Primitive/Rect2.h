#pragma once
#include "Line3.h"
#include "Math/Vector2.h"
#include "Math/Math.h"

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
            VSRect2(const Math::VSVector2 &Min, const Math::VSVector2 &Max);
        };
    }
}