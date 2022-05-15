#pragma once
#include "Ray3.h"
#include "Math/Vector3.h"

namespace Matrix
{
	namespace Primitive
	{

		class Ray3;

		class Plane3;
		class Polygon3;
		class Triangle3;
		class Rectangle3;

		class AABB3;
		class OBB3;
		class Sphere3;


		class MATRIX_PRIMITIVE_API Segment3 : public Ray3
		{
		private:
			Matrix::Math::Vector3 m_End;
			VSREAL m_fLen;
		public:
			Segment3();
			~Segment3();
			Segment3(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& End);
			Segment3(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& Dir, VSREAL fLen);
			bool GetParameter(const Matrix::Math::Vector3& Point, VSREAL& fSegmentParameter) const;
			//�þ���任����
			void Transform(const Segment3& Segment, const Matrix::Math::Matrix4& Mat);
			/*************************************inline************************************************/
			inline const Matrix::Math::Vector3& GetEnd() const;
			inline VSREAL GetLen() const;
			inline void Set(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& End);
			inline void Set(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& Dir, VSREAL fLen);
			inline Matrix::Math::Vector3 GetParameterPoint(VSREAL fSegmentParameter) const;

			/********************************RelationWith******************************************/
			//�����߶���������λ�ù�ϵ bCullΪ�Ƿ�Ϊ�������,�Ƿ��ǳ���,t�����ཻ����
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const Triangle3& Triangle, bool bCull, VSREAL& fSegmentParameter,
				VSREAL fTriangleParameter[3])const;
			//�����߶���ƽ��λ�ù�ϵ
			//IT_NoIntersect VSNTERSECT IT_On IT_Back IT_Front
			int RelationWith(const Plane3& Plane, bool bCull, VSREAL& fSegmentParameter)const;
			//�����߶������λ�ù�ϵ
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const Rectangle3& Rectangle, bool bCull, VSREAL& fSegmentParameter,
				VSREAL fRectangleParameter[2])const;

			//�����߶���OBBλ�ù�ϵ
			//IT_NoIntersect VSNTERSECT IT_In
			int RelationWith(const OBB3& OBB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//�����߶���AABBλ�ù�ϵ
			//IT_NoIntersect VSNTERSECT IT_In
			int RelationWith(const AABB3& AABB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//�����߶�����λ�ù�ϵ
			//IT_NoIntersect VSNTERSECT IT_In
			int RelationWith(const Sphere3& sphere, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//�����߶�������λ�ù�ϵ
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const Polygon3& Polygon, VSREAL& fSegmentParameter,
				bool bCull, int& iIndexTriangle, VSREAL fTriangleParameter[3])const;

			/*************************************����************************************************/
			//����߶ξ���
			VSREAL SquaredDistance(const Matrix::Math::Vector3& Point, VSREAL& fSegmentParameter)const;
			//ֱ�ߺ��߶ξ���
			VSREAL SquaredDistance(const Line3& Line, VSREAL& fSegmentParameter, VSREAL& fLineParameter)const;
			//���ߺ��߶ξ���
			VSREAL SquaredDistance(const Ray3& Ray, VSREAL& fSegmentParameter, VSREAL& fRayParameter)const;
			//�߶κ��߶ξ���
			VSREAL SquaredDistance(const Segment3& Segment, VSREAL& fSegment1Parameter, VSREAL& fSegment2Parameter)const;
			//�߶κ������ξ���
			VSREAL SquaredDistance(const Triangle3& Triangle, VSREAL& fSegmentParameter, VSREAL fTriangleParameter[3])const;
			//�߶κ;��ξ���
			VSREAL SquaredDistance(const Rectangle3& Rectangle, VSREAL& fSegmentParameter, VSREAL fRectangleParameter[2])const;
			//�߶κ�OBB����
			VSREAL SquaredDistance(const OBB3& OBB, VSREAL& fSegmentParameter, VSREAL fOBBParameter[3])const;

			//�߶κ���ľ���
			VSREAL Distance(const Sphere3& Sphere, VSREAL& fSegmentParameter, Matrix::Math::Vector3& SpherePoint)const;

			//�߶κ�ƽ�����
			VSREAL Distance(const Plane3& Plane, Matrix::Math::Vector3& SegmentPoint, Matrix::Math::Vector3& PlanePoint)const;

			//�߶κ�AABB����
			VSREAL SquaredDistance(const AABB3& AABB, VSREAL& fSegmentParameter, VSREAL fAABBParameter[3])const;

			//�߶κͶ���ξ���
			VSREAL SquaredDistance(const Polygon3& Polygon, VSREAL& fSegmentParameter, int& IndexTriangle, VSREAL fTriangleParameter[3])const;
		};

#include "Segment3.inl"
	}
}