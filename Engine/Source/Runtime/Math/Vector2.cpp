#include "Vector2.h"
using namespace Matrix::Math;
/*----------------------------------------------------------------*/
Vector2::Vector2(void)
{
	x = 0;
	y = 0;
}
/*----------------------------------------------------------------*/
Vector2::Vector2(VSREAL _x, VSREAL _y)
{
	x = _x;
	y = _y;
}
/*----------------------------------------------------------------*/
void Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
}
/*----------------------------------------------------------------*/

Vector2 Vector2::operator+(const Vector2& v) const
{
	return Vector2(x + v.x, y + v.y);
}
/*----------------------------------------------------------------*/
void Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
}
/*----------------------------------------------------------------*/

Vector2 Vector2::operator-(const Vector2& v) const
{
	return Vector2(x - v.x, y - v.y);
}
/*----------------------------------------------------------------*/

void Vector2::operator*=(VSREAL f)
{
	x *= f;
	y *= f;
}
/*----------------------------------------------------------------*/

void Vector2::operator/=(VSREAL f)
{
	x /= f;
	y /= f;
}
/*----------------------------------------------------------------*/

Vector2 Vector2::operator*(VSREAL f) const
{
	return Vector2(x * f, y * f);
}
/*----------------------------------------------------------------*/

Vector2 Vector2::operator/(VSREAL f) const
{
	return Vector2(x / f, y / f);
}
/*----------------------------------------------------------------*/

void Vector2::operator+=(VSREAL f)
{
	x += f;
	y += f;
}
/*----------------------------------------------------------------*/

void Vector2::operator-=(VSREAL f)
{
	x -= f;
	y -= f;
}
/*----------------------------------------------------------------*/

Vector2 Vector2::operator+(VSREAL f) const
{
	return Vector2(x + f, y + f);
}
/*----------------------------------------------------------------*/

Vector2 Vector2::operator-(VSREAL f) const
{
	return Vector2(x - f, y - f);
}
/*----------------------------------------------------------------*/

VSREAL Vector2::operator*(const Vector2& v) const
{
	return (v.x * x + v.y * y);
}
/*----------------------------------------------------------------*/
bool Vector2::operator==(const Vector2& v) const
{
	for (unsigned int i = 0; i < 2; i++)
	{
		if (ABS(m[i] - v.m[i]) > EPSILON_E4)
		{
			return false;
		}
	}
	return true;
	// 	return (ABS(x-v.x) < EPSILON_E4 &&
	// 		ABS(y-v.y) < EPSILON_E4);
}