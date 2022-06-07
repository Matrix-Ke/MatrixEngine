#pragma once
#include "Line3.h"
#include "Math/Vector2.h"
#include "Math/EngineMath.h"

namespace Matrix
{
    namespace Primitive
    {
        class MATRIX_PRIMITIVE_API Rect2
        {
        public:
            Math::Vector2 m_Min;
            Math::Vector2 m_Max;
            Rect2(void);
            Rect2(const Math::Vector2 &Min, const Math::Vector2 &Max);
        };
    }
}