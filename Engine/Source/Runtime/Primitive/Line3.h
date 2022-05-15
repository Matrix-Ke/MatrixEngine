#pragma once
#include "Point3.h"



namespace Matrix
{
	namespace Primitive
	{


		class Ray3;
		class Segment3;

		class Plane3;
		class Polygon3;
		class Triangle3;
		class Rectangle3;

		class AABB3;
		class OBB3;
		class Sphere3;


		class MATRIX_PRIMITIVE_API Line3
		{
		protected:
			Matrix::Math::Vector3 m_Orig; // Դ��
			Matrix::Math::Vector3 m_Dir;  // ����
		public:
			Line3();
			Line3(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& Dir);
			~Line3();
			//�������캯��
			Line3(const Line3& rhs);

			void Transform(const Line3& Line, const Matrix::Math::Matrix4& Mat);
			bool GetParameter(const Matrix::Math::Vector3& Point, VSREAL& fLineParameter) const;
			/************************inline***************************************/
			inline void Set(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& Dir);
			inline const Matrix::Math::Vector3& GetOrig() const;
			inline const Matrix::Math::Vector3& GetDir() const;

			inline Matrix::Math::Vector3 GetParameterPoint(VSREAL fLineParameter) const;



			//�㵽ֱ�߾���
			VSREAL SquaredDistance(const Matrix::Math::Vector3& Point, VSREAL& fLineParameter)const;
			//ֱ�ߺ�ֱ�ߵľ���
			VSREAL SquaredDistance(const Line3& Line, VSREAL& fLine1Parameter, VSREAL& fLine2Parameter)const;
			//ֱ�ߺ����߾���
			VSREAL SquaredDistance(const Ray3& Ray, VSREAL& fLineParameter, VSREAL& fRayParameter)const;
			//ֱ�ߺ��߶ξ���
			VSREAL SquaredDistance(const Segment3& Segment, VSREAL& fLineParameter, VSREAL& fSegmentParameter)const;
			//ֱ�ߺ������ξ���
			VSREAL SquaredDistance(const Triangle3& Triangle, VSREAL& fLineParameter, VSREAL fTriangleParameter[3])const;
			//ֱ�ߺ;��ξ���
			VSREAL SquaredDistance(const Rectangle3& Rectangle, VSREAL& fLineParameter, VSREAL fRectangleParameter[2])const;
			//ֱ�ߺ�OBB����
			VSREAL SquaredDistance(const OBB3& OBB, VSREAL& fLineParameter, VSREAL fOBBParameter[3])const;
			//ֱ�ߺ���ľ���
			VSREAL Distance(const Sphere3& Sphere, VSREAL& fLineParameter, Matrix::Math::Vector3& SpherePoint)const;
			//ֱ�ߺ�ƽ�����
			VSREAL Distance(const Plane3& Plane, Matrix::Math::Vector3& LinePoint, Matrix::Math::Vector3& PlanePoint)const;
			//ֱ�ߺ�AABB����
			VSREAL SquaredDistance(const AABB3& AABB, VSREAL& fLineParameter, VSREAL fAABBParameter[3])const;

			//ֱ�ߺͶ���ξ���
			VSREAL SquaredDistance(const Polygon3& Polygon, VSREAL& fLineParameter,
				int& IndexTriangle,
				VSREAL fTriangleParameter[3])const;


			/********************************RelationWith******************************************/
			//����ֱ����������λ�ù�ϵ bCullΪ�Ƿ�Ϊ�������,�Ƿ��ǳ���,t�����ཻ����
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const Triangle3& Triangle, bool bCull, VSREAL& fLineParameter,
				VSREAL fTriangleParameter[3])const;
			//����ֱ����ƽ��λ�ù�ϵ
			//IT_NoIntersect VSNTERSECT IT_On IT_Back IT_Front
			int RelationWith(const Plane3& Plane, bool bCull, VSREAL& fLineParameter)const;
			//����ֱ�������λ�ù�ϵ
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const Rectangle3& Rectangle, bool bCull, VSREAL& fLineParameter,
				VSREAL fRectangleParameter[2])const;
			//����ֱ������λ�ù�ϵ
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const Sphere3& sphere, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//����ֱ����OBBλ�ù�ϵ
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const OBB3& OBB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;

			//����ֱ����AABBλ�ù�ϵ
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const AABB3& AABB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;

			//����ֱ��������λ�ù�ϵ bCullΪ�Ƿ�Ϊ�������,�Ƿ��ǳ���,t�����ཻ����
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const Polygon3& Polygon, VSREAL& fLineParameter,
				bool bCull, int& iIndexTriangle, VSREAL fTriangleParameter[3])const;
			/*************************************����************************************************/
		};

#include "Line3.inl"
	}
}