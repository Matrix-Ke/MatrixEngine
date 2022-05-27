#pragma once
#include "Vector3.h"
#include "Matrix3.h"
#include "Quat.h"
#include "Vector4.h"

namespace Matrix
{
	namespace Math
	{
		bool MATRIX_MATH_API IsUniformScale(VSREAL fScale);
		bool MATRIX_MATH_API IsZeroTranslate(const Vector3& Translate);
		bool MATRIX_MATH_API IsIdentityRotate(const Matrix3& Rotate);
		bool MATRIX_MATH_API IsIdentityRotate(const Quat& Rotate);

		// 	template< typename T>
		// 	T LineInterpolation (T t1, T t2, VSREAL t)
		// 	{
		// 		return t1 + (t2 - t1) * t;
		// 	}
		// 	Quat LineInterpolation (Quat t1, Quat t2, VSREAL t)
		// 	{
		// 		VSREAL fCos = t2.Dot(t1);
		// 		if(fCos < 0.0f)
		// 		{
		// 			t1 *= -1.0f;
		// 		}
		// 		return t1 + (t2 - t1) * t;
		// 	}
		VSREAL MATRIX_MATH_API LineInterpolation(VSREAL t1, VSREAL t2, VSREAL t);

		Vector3 MATRIX_MATH_API LineInterpolation(const Vector3& t1, const Vector3& t2, VSREAL t);

		Quat MATRIX_MATH_API LineInterpolation(const Quat& t1, const Quat& t2, VSREAL t);

		Vector4 MATRIX_MATH_API LineInterpolation(const Vector4& t1, const Vector4& t2, VSREAL t);
	}
}
