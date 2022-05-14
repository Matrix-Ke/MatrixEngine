#pragma once
#include "CMathInterface.h"

namespace Matrix
{
	namespace Math
	{
		class Matrix3;
		class Quat;
		class VSRay3;
		class VSLine3;
		class VSPlane3;
		class VSRay3;
		class VSSegment3;
		class VSTriangle3;
		class VSRectangle3;
		class OBB3;
		class VSSphere3;
		class VSAABB3;
		class Matrix4;
		class VSPolygon3;
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
			///********************************����******************************************/
			////��͵����
			// VSREAL SquaredDistance(const Vector3& Point) const;
			////�㵽ֱ�߾���
			// VSREAL SquaredDistance(const VSLine3& Line, VSREAL& fLineParameter)const;
			////������߾���
			// VSREAL SquaredDistance(const VSRay3& Ray, VSREAL& fRayParameter)const;
			////����߶ξ���
			// VSREAL SquaredDistance(const VSSegment3& Segment, VSREAL& fSegmentParameter)const;
			////��������ξ���
			// VSREAL SquaredDistance(const VSTriangle3& Triangle, VSREAL fTriangleParameter[3])const;
			////��;��ξ���
			// VSREAL SquaredDistance(const VSRectangle3& Rectangle, VSREAL fRectangleParameter[2])const;
			////���OBB����
			// VSREAL SquaredDistance(const OBB3& OBB, VSREAL fOBBParameter[3])const;
			////�����ľ���
			// VSREAL Distance(const VSSphere3& Sphere, Vector3& SpherePoint)const;
			////���ƽ�����
			// VSREAL Distance(const VSPlane3& Plane, Vector3& PlanePoint)const;
			////���AABB����
			// VSREAL SquaredDistance(const VSAABB3& AABB, VSREAL fAABBParameter[3])const;
			////��Ͷ���ξ���
			// VSREAL SquaredDistance(const VSPolygon3& Polygon, int& IndexTriangle, VSREAL fTriangleParameter[3])const;
			///********************************RelationWith******************************************/
			////�����λ�ù�ϵ
			////VSIN VSOUT VSON
			// int RelationWith(const VSSphere3& Sphere)const;
			////���ƽ��λ�ù�ϵ
			////VSFRONT VSBACK VSON
			// int RelationWith(const VSPlane3& Plane)const;
			////���OBBλ�ù�ϵ
			////VSIN VSOUT VSON
			// int RelationWith(const OBB3& OBB)const;
			////���AABBλ�ù�ϵ
			////VSIN VSOUT VSON
			// int RelationWith(const VSAABB3& AABB)const;
			const static Vector3 ms_Up;
			const static Vector3 ms_Right;
			const static Vector3 ms_Front;
			const static Vector3 ms_Zero;
			const static Vector3 ms_One;
		}; // class

#include "Vector3.inl"
	}
}