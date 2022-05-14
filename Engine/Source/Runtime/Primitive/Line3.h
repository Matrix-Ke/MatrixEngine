#pragma once
#include "Math/Math.h"
#include "Math/Vector3.h"
//#include "Plane3.h"
//#include "OBB3.h"
//#include "Sphere3.h"
//#include "Triangle3.h"
//#include "Rectangle3.h"
/*
	直线类
*/
#ifdef Primitive_EXPORTS
#define MATRIX_PRIMITIVE_API __declspec(dllexport)
#else MATRIX_PRIMITIVE_API __declspec(dllimport)
#endif // Primitive_EXPORT

namespace Matrix
{
	namespace Primitive
	{
		// using namespace Matrix::Math;
		class Ray3;
		class Segment3;
		class MATRIX_PRIMITIVE_API Line3
		{
		protected:
			Matrix::Math::Vector3 m_Orig; // 源点
			Matrix::Math::Vector3 m_Dir;  // 方向
		public:
			Line3();
			Line3(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& Dir);
			~Line3();
			void Transform(const Line3& Line, const Matrix::Math::Matrix4& Mat);
			bool GetParameter(const Matrix::Math::Vector3& Point, VSREAL& fLineParameter) const;
			/************************inline***************************************/
			inline void Set(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& Dir);
			inline const Matrix::Math::Vector3& GetOrig() const;
			inline const Matrix::Math::Vector3& GetDir() const;

			inline Matrix::Math::Vector3 GetParameterPoint(VSREAL fLineParameter) const;

			///********************************RelationWith******************************************/
			////测试直线与三角形位置关系 bCull为是否为背面剪裁,是否考虑朝向,t返回相交长度
			////VSNOINTERSECT VSNTERSECT
			// int RelationWith(const Triangle3& Triangle, bool bCull, VSREAL& fLineParameter,
			//	VSREAL fTriangleParameter[3])const;
			////测试直线与平面位置关系
			////VSNOINTERSECT VSNTERSECT VSON VSBACK VSFRONT
			// int RelationWith(const VSPlane3& Plane, bool bCull, VSREAL& fLineParameter)const;
			////测试直线与矩形位置关系
			////VSNOINTERSECT VSNTERSECT
			// int RelationWith(const VSRectangle3& Rectangle, bool bCull, VSREAL& fLineParameter,
			//	VSREAL fRectangleParameter[2])const;
			////测试直线与球位置关系
			////VSNOINTERSECT VSNTERSECT
			// int RelationWith(const VSSphere3& sphere, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			////测试直线与OBB位置关系
			////VSNOINTERSECT VSNTERSECT
			// int RelationWith(const OBB3& OBB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;

			////测试直线与AABB位置关系
			////VSNOINTERSECT VSNTERSECT
			// int RelationWith(const VSAABB3& AABB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;

			////测试直线与多边形位置关系 bCull为是否为背面剪裁,是否考虑朝向,t返回相交长度
			////VSNOINTERSECT VSNTERSECT
			// int RelationWith(const VSPolygon3& Polygon, VSREAL& fLineParameter,
			//	bool bCull, int& iIndexTriangle, VSREAL fTriangleParameter[3])const;
			///*************************************距离************************************************/

			////点到直线距离
			// VSREAL SquaredDistance(const Matrix::Math::Vector3& Point, VSREAL& fLineParameter)const;
			////直线和直线的距离
			// VSREAL SquaredDistance(const VSLine3& Line, VSREAL& fLine1Parameter, VSREAL& fLine2Parameter)const;
			////直线和射线距离
			// VSREAL SquaredDistance(const VSRay3& Ray, VSREAL& fLineParameter, VSREAL& fRayParameter)const;
			////直线和线段距离
			// VSREAL SquaredDistance(const VSSegment3& Segment, VSREAL& fLineParameter, VSREAL& fSegmentParameter)const;
			////直线和三角形距离
			// VSREAL SquaredDistance(const Triangle3& Triangle, VSREAL& fLineParameter, VSREAL fTriangleParameter[3])const;
			////直线和矩形距离
			// VSREAL SquaredDistance(const VSRectangle3& Rectangle, VSREAL& fLineParameter, VSREAL fRectangleParameter[2])const;
			////直线和OBB距离
			// VSREAL SquaredDistance(const OBB3& OBB, VSREAL& fLineParameter, VSREAL fOBBParameter[3])const;
			////直线和球的距离
			// VSREAL Distance(const VSSphere3& Sphere, VSREAL& fLineParameter, Matrix::Math::Vector3& SpherePoint)const;
			////直线和平面距离
			// VSREAL Distance(const VSPlane3& Plane, Matrix::Math::Vector3& LinePoint, Matrix::Math::Vector3& PlanePoint)const;
			////直线和AABB距离
			// VSREAL SquaredDistance(const VSAABB3& AABB, VSREAL& fLineParameter, VSREAL fAABBParameter[3])const;

			////直线和多边形距离
			// VSREAL SquaredDistance(const VSPolygon3& Polygon, VSREAL& fLineParameter,
			//	int& IndexTriangle,
			//	VSREAL fTriangleParameter[3])const;
		};

#include "Line3.inl"
	}
}