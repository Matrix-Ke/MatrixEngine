#pragma once
#include "Ray3.h"
#include "Math/Vector3.h"

namespace Matrix
{
	namespace Primitive
	{
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
			//用矩阵变换射线
			void Transform(const Segment3& Segment, const Matrix::Math::Matrix4& Mat);
			/*************************************inline************************************************/
			inline const Matrix::Math::Vector3& GetEnd() const;
			inline VSREAL GetLen() const;
			inline void Set(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& End);
			inline void Set(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& Dir, VSREAL fLen);
			inline Matrix::Math::Vector3 GetParameterPoint(VSREAL fSegmentParameter) const;

			///********************************RelationWith******************************************/
			////测试线段与三角形位置关系 bCull为是否为背面剪裁,是否考虑朝向,t返回相交长度
			////VSNOINTERSECT VSNTERSECT
			// int RelationWith(const Triangle3& Triangle, bool bCull, VSREAL& fSegmentParameter,
			//	VSREAL fTriangleParameter[3])const;
			////测试线段与平面位置关系
			////VSNOINTERSECT VSNTERSECT VSON VSBACK VSFRONT
			// int RelationWith(const VSPlane3& Plane, bool bCull, VSREAL& fSegmentParameter)const;
			////测试线段与矩形位置关系
			////VSNOINTERSECT VSNTERSECT
			// int RelationWith(const VSRectangle3& Rectangle, bool bCull, VSREAL& fSegmentParameter,
			//	VSREAL fRectangleParameter[2])const;

			////测试线段与OBB位置关系
			////VSNOINTERSECT VSNTERSECT VSIN
			// int RelationWith(const OBB3& OBB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			////测试线段与AABB位置关系
			////VSNOINTERSECT VSNTERSECT VSIN
			// int RelationWith(const VSAABB3& AABB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			////测试线段与球位置关系
			////VSNOINTERSECT VSNTERSECT VSIN
			// int RelationWith(const VSSphere3& sphere, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			////测试线段与多边形位置关系
			////VSNOINTERSECT VSNTERSECT
			// int RelationWith(const VSPolygon3& Polygon, VSREAL& fSegmentParameter,
			//	bool bCull, int& iIndexTriangle, VSREAL fTriangleParameter[3])const;

			///*************************************距离************************************************/
			////点和线段距离
			// VSREAL SquaredDistance(const Matrix::Math::Vector3& Point, VSREAL& fSegmentParameter)const;
			////直线和线段距离
			// VSREAL SquaredDistance(const VSLine3& Line, VSREAL& fSegmentParameter, VSREAL& fLineParameter)const;
			////射线和线段距离
			// VSREAL SquaredDistance(const VSRay3& Ray, VSREAL& fSegmentParameter, VSREAL& fRayParameter)const;
			////线段和线段距离
			// VSREAL SquaredDistance(const VSSegment3& Segment, VSREAL& fSegment1Parameter, VSREAL& fSegment2Parameter)const;
			////线段和三角形距离
			// VSREAL SquaredDistance(const Triangle3& Triangle, VSREAL& fSegmentParameter, VSREAL fTriangleParameter[3])const;
			////线段和矩形距离
			// VSREAL SquaredDistance(const VSRectangle3& Rectangle, VSREAL& fSegmentParameter, VSREAL fRectangleParameter[2])const;
			////线段和OBB距离
			// VSREAL SquaredDistance(const OBB3& OBB, VSREAL& fSegmentParameter, VSREAL fOBBParameter[3])const;

			////线段和球的距离
			// VSREAL Distance(const VSSphere3& Sphere, VSREAL& fSegmentParameter, Matrix::Math::Vector3& SpherePoint)const;

			////线段和平面距离
			// VSREAL Distance(const VSPlane3& Plane, Matrix::Math::Vector3& SegmentPoint, Matrix::Math::Vector3& PlanePoint)const;

			////线段和AABB距离
			// VSREAL SquaredDistance(const VSAABB3& AABB, VSREAL& fSegmentParameter, VSREAL fAABBParameter[3])const;

			////线段和多边形距离
			// VSREAL SquaredDistance(const VSPolygon3& Polygon, VSREAL& fSegmentParameter,
			//	int& IndexTriangle,
			//	VSREAL fTriangleParameter[3])const;
		};

#include "Segment3.inl"
	}
}