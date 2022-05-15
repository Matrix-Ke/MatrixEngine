#pragma once
#include "CMathInterface.h"

namespace Matrix
{
	namespace Math
	{
		class Matrix3;
		class Matrix4;
		class Quat;
		//����
		class MATRIX_MATH_API Vector3
		{
		public:
			union
			{
				VSREAL m[3];
				struct
				{
					VSREAL x, y, z;
				};
			};

			Vector3(void);
			Vector3(VSREAL _x, VSREAL _y, VSREAL _z);

			/*************************************inline************************************************/
			inline void Set(VSREAL _x, VSREAL _y, VSREAL _z);
			inline VSREAL GetLength(void) const;    // ����
			inline VSREAL GetSqrLength(void) const; // ����ƽ��
			inline void Negate(void);               // ����-1
			inline void Normalize(void);            // ��λ��
			inline void Cross(const Vector3& v1,  //���
				const Vector3& v2);

			VSREAL AngleWith(Vector3& v);  // ���������ļн�(����)
			void Create(const Vector3& v1, // ���������ӵ�v1��v2
				const Vector3& v2);

			/*            N     _
					 \	  /|\   /|
				Dir	  \	   |   /  Reflect
					  _\|  |  /
			--------------------------
			*/
			Vector3 ReflectDir(const Vector3& N) const;

			void operator+=(const Vector3& v);
			void operator-=(const Vector3& v);

			void operator*=(VSREAL f);
			void operator/=(VSREAL f);
			void operator+=(VSREAL f);
			void operator-=(VSREAL f);

			VSREAL Dot(const Vector3& v) const; //���
			bool operator==(const Vector3& v) const;

			Vector3 operator*(VSREAL f) const;
			Vector3 operator/(VSREAL f) const;
			Vector3 operator+(VSREAL f) const;
			Vector3 operator-(VSREAL f) const;

			Quat operator*(const Quat& q) const;
			Vector3 operator*(const Matrix3& m) const;
			Vector3 operator*(const Matrix4& m) const;
			Vector3 operator+(const Vector3& v) const;
			Vector3 operator-(const Vector3& v) const;
			Vector3 operator/(const Vector3& v) const;
			Vector3 operator*(const Vector3& v) const;

			void operator/=(const Vector3& v);
			void operator*=(const Vector3& v);
			bool IsParallel(const Vector3& Vector) const;


			const static Vector3 ms_Up;
			const static Vector3 ms_Right;
			const static Vector3 ms_Front;
			const static Vector3 ms_Zero;
			const static Vector3 ms_One;
		}; // class

#include "Vector3.inl"
	}
}