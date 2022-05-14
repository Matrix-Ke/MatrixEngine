#pragma once
#include "Plane3.h"
#include "Math/Vector3.h"

/********************************************************************************************


__________________
|        |        |
|    A[0]|        |
|		  |        |
|        |_A[1]___|
|                 |
|                 |
|_________________|


左手定则 法向量 为 cross (A[0],A[1]),规定可见 ，方向朝向屏幕外，
********************************************************************************************/
namespace Matrix
{
	namespace Primitive
	{
		class Triangle3;
		class MATRIX_PRIMITIVE_API Rectangle3 : public Plane3
		{
		private:
			Matrix::Math::Vector3 m_A[2];
			VSREAL m_fA[2];
			Matrix::Math::Vector3 m_Center;

		public:
			Rectangle3();
			~Rectangle3();
			Rectangle3(const Matrix::Math::Vector3& Center, const Matrix::Math::Vector3& A0, const Matrix::Math::Vector3& A1, VSREAL fA0, VSREAL fA1);
			Rectangle3(const Matrix::Math::Vector3& Center, const Matrix::Math::Vector3 A[2], const VSREAL fA[2]);
			bool GetParameter(const Matrix::Math::Vector3& Point, VSREAL fRectangleParameter[2]) const;
			void Transform(const Rectangle3& Rectangle,
				const Matrix::Math::Matrix4& Mat);
			/*************************************inline************************************************/
			inline void Set(const Matrix::Math::Vector3& Center, const Matrix::Math::Vector3& A0, const Matrix::Math::Vector3& A1, VSREAL fA0, VSREAL fA1);
			inline void Set(const Matrix::Math::Vector3& Center, const Matrix::Math::Vector3 A[2], const VSREAL fA[2]);
			inline void GetA(Matrix::Math::Vector3 A[2]) const;
			inline void GetfA(VSREAL fA[2]) const;
			inline const Matrix::Math::Vector3& GetCenter() const;
			inline void GetPoint(Matrix::Math::Vector3 Point[4]) const;
			inline Matrix::Math::Vector3 GetParameterPoint(VSREAL fRectangleParameter[2]) const;
			inline Matrix::Math::Vector3 GetParameterPoint(VSREAL fRectangleParameter0, VSREAL fRectangleParameter1) const;

			///*************************************距离************************************************/
			////点和矩形距离
			// VSREAL SquaredDistance(const Matrix::Math::Vector3& Point, VSREAL fRectangleParameter[2])const;

			////矩形和矩形距离
			// VSREAL SquaredDistance(const VSRectangle3& Rectangle,
			//	VSREAL fRectangle1Parameter[2], VSREAL fRectangle2Parameter[2])const;

			////三角形和矩形距离
			// VSREAL SquaredDistance(const Triangle3& Triangle, VSREAL fRectangleParameter[2], VSREAL fTriangleParameter[3])const;

			////直线和矩形距离
			// VSREAL SquaredDistance(const VSLine3& Line, VSREAL fRectangleParameter[2], VSREAL& fLineParameter)const;
			////射线和矩形距离
			// VSREAL SquaredDistance(const VSRay3& Ray, VSREAL fRectangleParameter[2], VSREAL& fRayParameter)const;
			////线段和矩形距离
			// VSREAL SquaredDistance(const VSSegment3& Segment, VSREAL fRectangleParameter[2], VSREAL& fSegmentParameter)const;
			////矩形和OBB距离
			// VSREAL SquaredDistance(const OBB3& OBB, VSREAL RectangleParameter[2], VSREAL OBBParameter[3])const;
			////矩形和球的距离
			// VSREAL Distance(const VSSphere3& Sphere, VSREAL fRectangleParameter[2], Matrix::Math::Vector3& SpherePoint)const;
			////矩形和平面距离
			// VSREAL Distance(const VSPlane3& Plane, Matrix::Math::Vector3& RectanglePoint, Matrix::Math::Vector3& PlanePoint)const;
			////矩形和AABB距离
			// VSREAL SquaredDistance(const VSAABB3& AABB, VSREAL RectangleParameter[2]
			//	, VSREAL AABBParameter[3])const;

			////多边形和矩形距离
			// VSREAL SquaredDistance(const VSPolygon3& Polygon,
			//	VSREAL fRectangleParameter[2],
			//	int& IndexTriangle,
			//	VSREAL fTriangleParameter[3])const;
			///********************************RelationWith******************************************/
			////测试直线与矩形位置关系
			////VSNOINTERSECT VSNTERSECT
			// int RelationWith(const VSLine3& Line, bool bCull, VSREAL fRectangleParameter[2], VSREAL& fLineParameter)const;
			////测试射线与矩形位置关系
			////VSNOINTERSECT VSNTERSECT
			// int RelationWith(const VSRay3& Ray, bool bCull, VSREAL fRectangleParameter[2], VSREAL& fRayParameter)const;
			////测试线段与矩形位置关系
			////VSNOINTERSECT VSNTERSECT
			// int RelationWith(const VSSegment3& Segment, bool bCull, VSREAL fRectangleParameter[2], VSREAL& fSegmentParameter)const;
			////平面和矩形位置关系
			////VSON VSFRONT VSBACK VSINTERSECT
			// int RelationWith(const VSPlane3& Plane)const;
			// int RelationWith(const VSPlane3& Plane, VSSegment3& Segment)const;
			////三角形和矩形位置关系
			////VSNOINTERSECT VSINTERSECT
			// int RelationWith(const Triangle3& Triangle)const;
			// int RelationWith(const Triangle3& Triangle, VSSegment3& Segment)const;
			////矩形和矩形位置关系
			////VSNOINTERSECT VSINTERSECT
			// int RelationWith(const VSRectangle3& Rectangle)const;
			// int RelationWith(const VSRectangle3& Rectangle, VSSegment3& Segment)const;
			////矩形和AABB位置关系
			////VSNOINTERSECT VSINTERSECT VSIN
			// int RelationWith(const VSAABB3& AABB)const;

			////矩形和OBB位置关系
			////VSNOINTERSECT VSINTERSECT VSIN
			// int RelationWith(const OBB3& OBB)const;

			////矩形和圆位置关系
			////VSNOINTERSECT VSINTERSECT VSIN
			// int RelationWith(const VSSphere3& Sphere)const;
		};

#include "Rectangle3.inl"
	}
}
