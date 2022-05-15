#include "Rect2.h"
using namespace Matrix::Primitive;

Rect2::Rect2(void)
{
}
Rect2::Rect2(const Math::Vector2& Min, const Math::Vector2& Max)
{
	m_Min = Min;
	m_Max = Max;
}