#pragma once
#include "Plane3.h"
/***************************************************************************************

					fTriangleParameter[1]
		   m_V[0]	_________________________m_V[1]
				   \                       /
					\                     /
					 \                   /
					  \                 /
					   \               /
						\             /
fTriangleParameter[2]  \           /  fTriangleParameter[0]
						  \         /
						   \       /
							 \    /
							  \  /
							   \/m_V[2]
***************************************************************************************/
namespace Matrix
{
	namespace Primitive
	{
		class OBB3;
		class MATRIX_PRIMITIVE_API Triangle3 : public Plane3
		{
		private:
			Matrix::Math::Vector3 m_V[3];

		public:
			Triangle3();
			~Triangle3();
			Triangle3(const Matrix::Math::Vector3& P0, const Matrix::Math::Vector3& P1, const Matrix::Math::Vector3& P2);
			Triangle3(const Matrix::Math::Vector3 Point[3]);
			bool GetParameter(const Matrix::Math::Vector3& Point, VSREAL fTriangleParameter[3]) const;
			void Transform(const Triangle3& Triangle, const Matrix::Math::Matrix4& Mat);
			/*************************************inline************************************************/

			inline void Set(const Matrix::Math::Vector3& P1, const Matrix::Math::Vector3& P2, const Matrix::Math::Vector3& P3);
			inline void Set(const Matrix::Math::Vector3 Point[3]);
			inline void GetPoint(Matrix::Math::Vector3 Point[3]) const;
			inline Matrix::Math::Vector3 GetParameterPoint(VSREAL fTriangleParameter[3]) const;
			inline Matrix::Math::Vector3 GetParameterPoint(VSREAL fTriangleParameter0,
				VSREAL fTriangleParameter1, VSREAL fTriangleParameter2) const;

			/*************************************����************************************************/
			//��������ξ���
			VSREAL SquaredDistance(const Matrix::Math::Vector3& Point, VSREAL fTriangleParameter[3])const;
			//�����κ������ξ���
			VSREAL SquaredDistance(const Triangle3& Triangle,
				VSREAL fTriangle1Parameter[3],
				VSREAL fTriangle2Parameter[3])const;
			//�����κ;��ξ���
			VSREAL SquaredDistance(const Rectangle3& Rectangle,
				VSREAL fTriangleParameter[3],
				VSREAL fRectangleParameter[2])const;

			//ֱ�ߺ������ξ���
			VSREAL SquaredDistance(const Line3& Line, VSREAL fTriangleParameter[3], VSREAL& fLineParameter)const;
			//���ߺ������ξ���
			VSREAL SquaredDistance(const Ray3& Ray, VSREAL fTriangleParameter[3], VSREAL& fRayParameter)const;
			//�߶κ������ξ���
			VSREAL SquaredDistance(const Segment3& Segment, VSREAL fTriangleParameter[3], VSREAL& fSegmentParameter)const;
			//�����κ�OBB����
			VSREAL SquaredDistance(const OBB3& OBB, VSREAL TriangleParameter[3], VSREAL OBBParameter[3])const;
			//�����κ���ľ���
			VSREAL Distance(const Sphere3& Sphere, VSREAL fTriangleParameter[3], Matrix::Math::Vector3& SpherePoint)const;

			//ƽ��������ξ���
			VSREAL Distance(const Plane3& Plane, Matrix::Math::Vector3& TrianglePoint, Matrix::Math::Vector3& PlanePoint)const;
			//�����κ�AABB����
			VSREAL SquaredDistance(const AABB3& AABB, VSREAL TriangleParameter[3]
				, VSREAL AABBParameter[3])const;
			//�����κͶ���ξ���
			VSREAL SquaredDistance(const Polygon3& Polygon,
				VSREAL fTriangle1Parameter[3],
				int& IndexTriangle,
				VSREAL fTriangle2Parameter[3])const;
			/********************************RelationWith******************************************/
			//����ֱ����������λ�ù�ϵ bCullΪ�Ƿ�Ϊ�������,�Ƿ��ǳ���,t�����ཻ����
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const Line3& Line, bool bCull, VSREAL fTriangleParameter[3],
				VSREAL& fLineParameter)const;
			//����������������λ�ù�ϵ
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const Ray3& Ray, bool bCull, VSREAL fTriangleParameter[3],
				VSREAL& fRayParameter)const;
			//�����߶���������λ�ù�ϵ
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const Segment3& Segment, bool bCull, VSREAL fTriangleParameter[3],
				VSREAL& fSegmentParameter)const;
			//ƽ���������λ�ù�ϵ
			//IT_On IT_Front IT_Back IT_Intersect
			int RelationWith(const Plane3& Plane)const;
			int RelationWith(const Plane3& Plane, Segment3& Segment)const;
			//�����κ�������λ�ù�ϵ
			//IT_NoIntersect IT_Intersect
			int RelationWith(const Triangle3& Triangle)const;
			int RelationWith(const Triangle3& Triangle, Segment3& Segment)const;
			//�����κ;���λ�ù�ϵ
			//IT_NoIntersect IT_Intersect
			int RelationWith(const Rectangle3& Rectangle)const;
			int RelationWith(const Rectangle3& Rectangle, Segment3& Segment)const;
			//�����κ�AABBλ�ù�ϵ
			//IT_NoIntersect IT_Intersect IT_In
			int RelationWith(const AABB3& AABB)const;

			//�����κ�OBBλ�ù�ϵ
			//IT_NoIntersect IT_Intersect IT_In
			int RelationWith(const OBB3& OBB)const;

			//�����κ�Բλ�ù�ϵ
			//IT_NoIntersect IT_Intersect IT_In
			int RelationWith(const Sphere3& Sphere)const;
		};

#include "Triangle3.inl"

	}
}