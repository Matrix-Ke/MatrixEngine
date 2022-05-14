#include "Rect2.h"
using namespace Matrix::Primitive;

VSRect2::VSRect2(void)
{
}
VSRect2::VSRect2(const Math::VSVector2 &Min, const Math::VSVector2 &Max)
{
    m_Min = Min;
    m_Max = Max;
}