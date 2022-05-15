#pragma once
#include "CMathInterface.h"

namespace Matrix
{
	namespace Math
	{
		class Matrix3;
		class Quat;
		class Ray3;
		class Line3;
		class Plane3;
		class Ray3;
		class Segment3;
		class Triangle3;
		class Rectangle3;
		class OBB3;
		class Sphere3;
		class AABB3;
		class Matrix4;
		class Polygon3;
		//向量
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
			inline VSREAL GetLength(void) const;    // 长度
			inline VSREAL GetSqrLength(void) const; // 长度平方
			inline void Negate(void);               // 乘以-1
			inline void Normalize(void);            // 单位化
			inline void Cross(const Vector3& v1,  //叉积
				const Vector3& v2);

			VSREAL AngleWith(Vector3& v);  // 两个向量的夹角(弧度)
			void Create(const Vector3& v1, // 构造向量从点v1到v2
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

			VSREAL Dot(const Vector3& v) const; //点积
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
			///********************************距离******************************************/
			////点和点距离
			// VSREAL SquaredDistance(const Vector3& Point) const;
			////点到直线距离
			// VSREAL SquaredDistance(const Line3& Line, VSREAL& fLineParameter)const;
			////点和射线距离
			// VSREAL SquaredDistance(const Ray3& Ray, VSREAL& fRayParameter)const;
			////点和线段距离
			// VSREAL SquaredDistance(const Segment3& Segment, VSREAL& fSegmentParameter)const;
			////点和三角形距离
			// VSREAL SquaredDistance(const Triangle3& Triangle, VSREAL fTriangleParameter[3])const;
			////点和矩形距离
			// VSREAL SquaredDistance(const Rectangle3& Rectangle, VSREAL fRectangleParameter[2])const;
			////点和OBB距离
			// VSREAL SquaredDistance(const OBB3& OBB, VSREAL fOBBParameter[3])const;
			////点和球的距离
			// VSREAL Distance(const Sphere3& Sphere, Vector3& SpherePoint)const;
			////点和平面距离
			// VSREAL Distance(const Plane3& Plane, Vector3& PlanePoint)const;
			////点和AABB距离
			// VSREAL SquaredDistance(const AABB3& AABB, VSREAL fAABBParameter[3])const;
			////点和多边形距离
			// VSREAL SquaredDistance(const Polygon3& Polygon, int& IndexTriangle, VSREAL fTriangleParameter[3])const;
			///********************************RelationWith******************************************/
			////点和球位置关系
			////IT_In IT_Out IT_On
			// int RelationWith(const Sphere3& Sphere)const;
			////点和平面位置关系
			////IT_Front IT_Back IT_On
			// int RelationWith(const Plane3& Plane)const;
			////点和OBB位置关系
			////IT_In IT_Out IT_On
			// int RelationWith(const OBB3& OBB)const;
			////点和AABB位置关系
			////IT_In IT_Out IT_On
			// int RelationWith(const AABB3& AABB)const;
			const static Vector3 ms_Up;
			const static Vector3 ms_Right;
			const static Vector3 ms_Front;
			const static Vector3 ms_Zero;
			const static Vector3 ms_One;
		}; // class

#include "Vector3.inl"
	}
}