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

		//射线
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
			//测试射线与三角形是否位置关系 bCull为是否为背面剪裁,是否考虑朝向,t返回相交长度
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const Triangle3& Triangle, bool bCull, VSREAL& fRayParameter,
				VSREAL fTriangleParameter[3])const;
			//测试射线与平面位置关系
			//IT_NoIntersect VSNTERSECT IT_On IT_Back IT_Front
			int RelationWith(const Plane3& Plane, bool bCull, VSREAL& fRayParameter)const;
			//测试射线与矩形位置关系
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const Rectangle3& Rectangle, bool bCull, VSREAL& fRayParameter,
				VSREAL fRectangleParameter[2])const;

			//测试射线与OBB位置关系
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const OBB3& OBB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//测试直线与AABB位置关系
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const AABB3& AABB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//测试射线与球位置关系
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const Sphere3& sphere, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//测试射线与多边形位置关系
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const Polygon3& Polygon, VSREAL& fRayParameter,
				bool bCull, int& iIndexTriangle, VSREAL fTriangleParameter[3])const;
			/*************************************距离************************************************/
			//点和射线距离
			VSREAL SquaredDistance(const Matrix::Math::Vector3& Point, VSREAL& fLineParameter)const;
			//直线和射线距离
			VSREAL SquaredDistance(const Line3& Line, VSREAL& fRayParameter, VSREAL& fLineParameter)const;
			//射线和射线距离
			VSREAL SquaredDistance(const Ray3& Ray, VSREAL& fRay1Parameter, VSREAL& fRay2Parameter)const;
			//射线和线段距离
			VSREAL SquaredDistance(const Segment3& Segment, VSREAL& fRayParameter, VSREAL& fSegmentParameter)const;
			//射线和三角形距离
			VSREAL SquaredDistance(const Triangle3& Triangle, VSREAL& fRayParameter, VSREAL fTriangleParameter[3])const;
			//射线和矩形距离
			VSREAL SquaredDistance(const Rectangle3& Rectangle, VSREAL& fRayParameter, VSREAL fRectangleParameter[2])const;
			//射线和OBB距离
			VSREAL SquaredDistance(const OBB3& OBB, VSREAL& fRayParameter, VSREAL fOBBParameter[3])const;
			//射线和球的距离
			VSREAL Distance(const Sphere3& Sphere, VSREAL& fRayParameter, Matrix::Math::Vector3& SpherePoint)const;
			//射线和平面距离
			VSREAL Distance(const Plane3& Plane, Matrix::Math::Vector3& RayPoint, Matrix::Math::Vector3& PlanePoint)const;
			//射线和AABB距离
			VSREAL SquaredDistance(const AABB3& AABB, VSREAL& fRayParameter, VSREAL fAABBParameter[3])const;
			//射线和多边形距离
			VSREAL SquaredDistance(const Polygon3& Polygon, VSREAL& fRayParameter, int& IndexTriangle, VSREAL fTriangleParameter[3])const;
		}; // class
		/*----------------------------------------------------------------*/



#include "Ray3.inl"

	};

};
