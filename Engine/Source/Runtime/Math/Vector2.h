#pragma once
#include "CMathInterface.h"

namespace Matrix::Math
{
	class MATRIX_MATH_API Vector2
	{
	public:
		union
		{
			VSREAL m[2];
			struct
			{
				VSREAL x, y;
			};
		};
		Vector2(void);
		Vector2(VSREAL _x, VSREAL _y);

		/*************************************inline************************************************/
		inline void Set(VSREAL _x, VSREAL _y);

		void operator+=(const Vector2& v);
		void operator-=(const Vector2& v);

		void operator*=(VSREAL f);
		void operator/=(VSREAL f);
		void operator+=(VSREAL f);
		void operator-=(VSREAL f);

		VSREAL operator*(const Vector2& v) const; //点积

		bool operator==(const Vector2& v) const;

		Vector2 operator*(VSREAL f) const;
		Vector2 operator/(VSREAL f) const;
		Vector2 operator+(VSREAL f) const;
		Vector2 operator-(VSREAL f) const;

		Vector2 operator+(const Vector2& v) const;
		Vector2 operator-(const Vector2& v) const;

		void Normalize();
	};

	//判断线段求交，并输出交点
	inline bool VS2DIntersect(Vector2& A1, Vector2& B1, Vector2& A2, Vector2& B2, Vector2& Out)
	{
		VSREAL denominator = (B1.y * (A2.x - B2.x) + A1.y * (B2.x - A2.x) + (A1.x - B1.x) * (A2.y - B2.y));

		if (ABS(denominator) < 0.0001)
			return false;

		Out = Vector2((-B1.x * A2.y * B2.x + A1.y * B1.x * (B2.x - A2.x) + B1.x * A2.x * B2.y + A1.x * (B1.y * A2.x - B2.y * A2.x - B1.y * B2.x + A2.y * B2.x)) / denominator,
			(B1.y * (-A2.y * B2.x + A1.x * (A2.y - B2.y) + A2.x * B2.y) + A1.y * (A2.y * B2.x - A2.x * B2.y + B1.x * (B2.y - A2.y))) / denominator);

		return true;
	}
#include "Vector2.inl"

}