#pragma once
#include "Line3.h"
#include "AABB3.h"

namespace Matrix
{
	namespace Primitive
	{
		class MATRIX_PRIMITIVE_API Sphere3
		{
		public:
			Matrix::Math::Vector3 m_Center; //����
			VSREAL m_fRadius;                 //�뾶
			Sphere3();
			~Sphere3();
			Sphere3(const Matrix::Math::Vector3& Center, VSREAL fRadius);
			//��������������Χ��
			void CreateSphere(const Matrix::Math::Vector3* pPointArray, unsigned int uiPointNum);
			//��ϰ�Χ��
			Sphere3 MergeSpheres(const Sphere3& Sphere) const;
			//�任����
			void Transform(const Sphere3& Sphere, const Matrix::Math::Matrix4& Mat);
			AABB3 GetAABB() const;
			/*************************************inline************************************************/
			inline void Set(const Matrix::Math::Vector3& Center, VSREAL fRadius);

			///*************************************����************************************************/
			////�����ľ���
			// VSREAL Distance(const Matrix::Math::Vector3& Point, Matrix::Math::Vector3& SpherePoint)const;
			////�ߺ���ľ���
			// VSREAL Distance(const VSLine3& Line, Matrix::Math::Vector3& SpherePoint, VSREAL& fLineParameter)const;
			////���ߺ���ľ���
			// VSREAL Distance(const VSRay3& Ray, Matrix::Math::Vector3& SpherePoint, VSREAL& fRayParameter)const;
			////�߶κ���ľ���
			// VSREAL Distance(const VSSegment3& Segment, Matrix::Math::Vector3& SpherePoint, VSREAL& fSegmentParameter)const;
			////OBB����ľ���
			// VSREAL Distance(const OBB3& OBB, Matrix::Math::Vector3& SpherePoint, VSREAL fOBBParameter[3])const;
			////ƽ�����ľ���
			// VSREAL Distance(const VSPlane3& Plane, Matrix::Math::Vector3& SpherePoint)const;
			////���κ���ľ���
			// VSREAL Distance(const VSRectangle3& Rectangle, Matrix::Math::Vector3& SpherePoint, VSREAL fRectangleParameter[2])const;
			////�����κ���ľ���
			// VSREAL Distance(const Triangle3 Triangle, Matrix::Math::Vector3& SpherePoint, VSREAL fTriangleParameter[3])const;
			////AABB����ľ���
			// VSREAL Distance(const VSAABB3& AABB, Matrix::Math::Vector3& SpherePoint, VSREAL fAABBParameter[3])const;

			////����κ���ľ���
			// VSREAL Distance(const VSPolygon3& Polygon, Matrix::Math::Vector3& SpherePoint, int& IndexTriangle,
			//	VSREAL fTriangleParameter[3])const;
			///********************************RelationWith******************************************/
			////�����λ�ù�ϵ
			////VSIN VSOUT VSON
			// int RelationWith(const Matrix::Math::Vector3& Point)const;
			////ֱ������λ�ù�ϵ
			////VSNOINTERSECT VSNTERSECT
			// int RelationWith(const VSLine3& Line, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			////��������λ�ù�ϵ
			////VSNOINTERSECT VSNTERSECT
			// int RelationWith(const VSRay3& Ray, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			////�߶�����λ�ù�ϵ
			////VSNOINTERSECT VSNTERSECT VSIN
			// int RelationWith(const VSSegment3& Segment, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			////ƽ�������λ�ù�ϵ
			////VSFRONT VSBACK VSINTERSECT
			// int RelationWith(const VSPlane3& Plane)const;
			////�����κ�Բλ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT VSIN
			// int RelationWith(const Triangle3 Triangle)const;
			////���κ�Բλ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT VSIN
			// int RelationWith(const VSRectangle3& Rectangle)const;

			////OBB��Բλ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT
			// int RelationWith(const OBB3& OBB)const;
			////԰��Բλ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT
			// int RelationWith(const VSSphere3& Sphere)const;
		};

#include "Sphere3.inl"
	}
}