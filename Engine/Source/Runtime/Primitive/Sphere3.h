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
			Matrix::Math::Vector3 m_Center; //中心
			VSREAL m_fRadius;                 //半径
			Sphere3();
			~Sphere3();
			Sphere3(const Matrix::Math::Vector3& Center, VSREAL fRadius);
			//根绝点来建立包围球
			void CreateSphere(const Matrix::Math::Vector3* pPointArray, unsigned int uiPointNum);
			//结合包围球
			Sphere3 MergeSpheres(const Sphere3& Sphere) const;
			//变换球体
			void Transform(const Sphere3& Sphere, const Matrix::Math::Matrix4& Mat);
			AABB3 GetAABB() const;
			/*************************************inline************************************************/
			inline void Set(const Matrix::Math::Vector3& Center, VSREAL fRadius);

			///*************************************距离************************************************/
			////点和球的距离
			// VSREAL Distance(const Matrix::Math::Vector3& Point, Matrix::Math::Vector3& SpherePoint)const;
			////线和球的距离
			// VSREAL Distance(const VSLine3& Line, Matrix::Math::Vector3& SpherePoint, VSREAL& fLineParameter)const;
			////射线和球的距离
			// VSREAL Distance(const VSRay3& Ray, Matrix::Math::Vector3& SpherePoint, VSREAL& fRayParameter)const;
			////线段和球的距离
			// VSREAL Distance(const VSSegment3& Segment, Matrix::Math::Vector3& SpherePoint, VSREAL& fSegmentParameter)const;
			////OBB和球的距离
			// VSREAL Distance(const OBB3& OBB, Matrix::Math::Vector3& SpherePoint, VSREAL fOBBParameter[3])const;
			////平面和球的距离
			// VSREAL Distance(const VSPlane3& Plane, Matrix::Math::Vector3& SpherePoint)const;
			////矩形和球的距离
			// VSREAL Distance(const VSRectangle3& Rectangle, Matrix::Math::Vector3& SpherePoint, VSREAL fRectangleParameter[2])const;
			////三角形和球的距离
			// VSREAL Distance(const Triangle3 Triangle, Matrix::Math::Vector3& SpherePoint, VSREAL fTriangleParameter[3])const;
			////AABB和球的距离
			// VSREAL Distance(const VSAABB3& AABB, Matrix::Math::Vector3& SpherePoint, VSREAL fAABBParameter[3])const;

			////多边形和球的距离
			// VSREAL Distance(const VSPolygon3& Polygon, Matrix::Math::Vector3& SpherePoint, int& IndexTriangle,
			//	VSREAL fTriangleParameter[3])const;
			///********************************RelationWith******************************************/
			////点和球位置关系
			////VSIN VSOUT VSON
			// int RelationWith(const Matrix::Math::Vector3& Point)const;
			////直线与球位置关系
			////VSNOINTERSECT VSNTERSECT
			// int RelationWith(const VSLine3& Line, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			////射线与球位置关系
			////VSNOINTERSECT VSNTERSECT
			// int RelationWith(const VSRay3& Ray, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			////线段与球位置关系
			////VSNOINTERSECT VSNTERSECT VSIN
			// int RelationWith(const VSSegment3& Segment, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			////平面与球的位置关系
			////VSFRONT VSBACK VSINTERSECT
			// int RelationWith(const VSPlane3& Plane)const;
			////三角形和圆位置关系
			////VSNOINTERSECT VSINTERSECT VSIN
			// int RelationWith(const Triangle3 Triangle)const;
			////矩形和圆位置关系
			////VSNOINTERSECT VSINTERSECT VSIN
			// int RelationWith(const VSRectangle3& Rectangle)const;

			////OBB和圆位置关系
			////VSNOINTERSECT VSINTERSECT
			// int RelationWith(const OBB3& OBB)const;
			////园和圆位置关系
			////VSNOINTERSECT VSINTERSECT
			// int RelationWith(const VSSphere3& Sphere)const;
		};

#include "Sphere3.inl"
	}
}