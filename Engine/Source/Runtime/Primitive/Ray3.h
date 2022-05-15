#pragma once
#include "Line3.h"
#include "Math/Matrix3X3W.h"

namespace Matrix
{
	namespace Primitive
	{
		class Segment3;

		class Plane3;
		class Polygon3;
		class Triangle3;
		class Rectangle3;

		class AABB3;
		class OBB3;
		class Sphere3;

		//����
		class MATRIX_PRIMITIVE_API Ray3 : public Line3
		{
		public:
			Ray3();
			Ray3(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& Dir);
			~Ray3();

			bool GetParameter(const Matrix::Math::Vector3& Point, VSREAL& fRayParameter) const;
			void Transform(const Ray3& Ray, const Matrix::Math::Matrix4& Mat);
			/************************inline***************************************/
			inline Matrix::Math::Vector3 GetParameterPoint(VSREAL fRayParameter) const;

			/********************************RelationWith******************************************/
			//�����������������Ƿ�λ�ù�ϵ bCullΪ�Ƿ�Ϊ�������,�Ƿ��ǳ���,t�����ཻ����
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const Triangle3& Triangle, bool bCull, VSREAL& fRayParameter,
				VSREAL fTriangleParameter[3])const;
			//����������ƽ��λ�ù�ϵ
			//IT_NoIntersect VSNTERSECT IT_On IT_Back IT_Front
			int RelationWith(const Plane3& Plane, bool bCull, VSREAL& fRayParameter)const;
			//�������������λ�ù�ϵ
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const Rectangle3& Rectangle, bool bCull, VSREAL& fRayParameter,
				VSREAL fRectangleParameter[2])const;

			//����������OBBλ�ù�ϵ
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const OBB3& OBB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//����ֱ����AABBλ�ù�ϵ
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const AABB3& AABB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//������������λ�ù�ϵ
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const Sphere3& sphere, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//��������������λ�ù�ϵ
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const Polygon3& Polygon, VSREAL& fRayParameter,
				bool bCull, int& iIndexTriangle, VSREAL fTriangleParameter[3])const;
			/*************************************����************************************************/
			//������߾���
			VSREAL SquaredDistance(const Matrix::Math::Vector3& Point, VSREAL& fLineParameter)const;
			//ֱ�ߺ����߾���
			VSREAL SquaredDistance(const Line3& Line, VSREAL& fRayParameter, VSREAL& fLineParameter)const;
			//���ߺ����߾���
			VSREAL SquaredDistance(const Ray3& Ray, VSREAL& fRay1Parameter, VSREAL& fRay2Parameter)const;
			//���ߺ��߶ξ���
			VSREAL SquaredDistance(const Segment3& Segment, VSREAL& fRayParameter, VSREAL& fSegmentParameter)const;
			//���ߺ������ξ���
			VSREAL SquaredDistance(const Triangle3& Triangle, VSREAL& fRayParameter, VSREAL fTriangleParameter[3])const;
			//���ߺ;��ξ���
			VSREAL SquaredDistance(const Rectangle3& Rectangle, VSREAL& fRayParameter, VSREAL fRectangleParameter[2])const;
			//���ߺ�OBB����
			VSREAL SquaredDistance(const OBB3& OBB, VSREAL& fRayParameter, VSREAL fOBBParameter[3])const;
			//���ߺ���ľ���
			VSREAL Distance(const Sphere3& Sphere, VSREAL& fRayParameter, Matrix::Math::Vector3& SpherePoint)const;
			//���ߺ�ƽ�����
			VSREAL Distance(const Plane3& Plane, Matrix::Math::Vector3& RayPoint, Matrix::Math::Vector3& PlanePoint)const;
			//���ߺ�AABB����
			VSREAL SquaredDistance(const AABB3& AABB, VSREAL& fRayParameter, VSREAL fAABBParameter[3])const;
			//���ߺͶ���ξ���
			VSREAL SquaredDistance(const Polygon3& Polygon, VSREAL& fRayParameter, int& IndexTriangle, VSREAL fTriangleParameter[3])const;
		}; // class
		/*----------------------------------------------------------------*/



#include "Ray3.inl"

	};

};
