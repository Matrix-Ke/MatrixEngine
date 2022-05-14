#pragma once
#include "Line3.h"
#include "Math/Vector3.h"
#include "math/Matrix3X3.h"

//#ifdef Primitive_EXPORTS
//#define MATRIX_PRIMITIVE_API   __declspec(dllexport)
//#else   MATRIX_PRIMITIVE_API   __declspec(dllimport)
//#endif // Primitive_EXPORT

namespace Matrix
{
	namespace Primitive
	{
		class Line3;
		class Sphere3;
		class VSCylinder3;
		class MATRIX_PRIMITIVE_API Plane3
		{
		protected:
			Matrix::Math::Vector3 m_N; //平面法向量
			VSREAL m_fD;                 // 到原点的距离(ax+by+cz+d=0)
		public:
			Plane3();
			Plane3(const Matrix::Math::Vector3& N, const Matrix::Math::Vector3& P);
			Plane3(const Matrix::Math::Vector3& P0, const Matrix::Math::Vector3& P1, const Matrix::Math::Vector3& P2);
			Plane3(const Matrix::Math::Vector3 Point[3]);
			Plane3(const Matrix::Math::Vector3& N, VSREAL fD);
			void Transform(const Plane3& Plane, const Matrix::Math::Matrix4& Mat);
			/*********************************** inline *************************************/
			inline const Matrix::Math::Vector3& GetN() const;
			inline Matrix::Math::Vector3 GetPoint() const;
			inline VSREAL GetfD() const;
			inline void Set(const Matrix::Math::Vector3& N, const Matrix::Math::Vector3& P);
			inline void Set(const Matrix::Math::Vector3& N, VSREAL fD);
			inline void Set(const Matrix::Math::Vector3& P0, const Matrix::Math::Vector3& P1, const Matrix::Math::Vector3& P2);
			inline void Set(const Matrix::Math::Vector3 Point[3]);
			inline Plane3 GetPlane() const;
			Matrix::Math::Vector3 ReflectDir(const Matrix::Math::Vector3& Dir) const;
			void GetReverse(Plane3& OutPlane) const;

			///*************************************距离************************************************/
			////点到平面距离
			// VSREAL Distance(const Matrix::Math::Vector3& Point, Matrix::Math::Vector3& PlanePoint)const;
			////平面和球的距离
			// VSREAL Distance(const VSSphere3& Sphere, Matrix::Math::Vector3& SpherePoint)const;
			////直线和平面距离
			// VSREAL Distance(const VSLine3& Line, Matrix::Math::Vector3& PlanePoint, Matrix::Math::Vector3& LinePoint)const;
			////射线和平面距离
			// VSREAL Distance(const VSRay3& Ray, Matrix::Math::Vector3& PlanePoint, Matrix::Math::Vector3& RayPoint)const;
			////线段和平面距离
			// VSREAL Distance(const VSSegment3& Segment, Matrix::Math::Vector3& PlanePoint, Matrix::Math::Vector3& SegmentPoint)const;

			////下面距离函数再没有考虑相交的情况下计算的，因为相交的情况下举例为0，先用RelationWith判断位置关系，再用下面来计算距离
			////平面和平面距离
			// VSREAL Distance(const VSPlane3& Plane, Matrix::Math::Vector3& Plane1Point, Matrix::Math::Vector3& Plane2Point)const;
			////平面和三角形距离
			// VSREAL Distance(const Triangle3& Triangle, Matrix::Math::Vector3& PlanePoint, Matrix::Math::Vector3& TrianglePoint)const;
			////矩形和平面距离
			// VSREAL Distance(const VSRectangle3& Rectangle, Matrix::Math::Vector3& PlanePoint, Matrix::Math::Vector3& RectanglePoint)const;
			////OBB和平面距离
			// VSREAL Distance(const OBB3& OBB, Matrix::Math::Vector3& PlanePoint, Matrix::Math::Vector3& OBBPoint)const;
			////AABB和平面距离
			// VSREAL Distance(const VSAABB3& AABB, Matrix::Math::Vector3& PlanePoint, Matrix::Math::Vector3& AABBPoint)const;
			////平面和多边形距离
			// VSREAL Distance(const VSPolygon3& Polygon, Matrix::Math::Vector3& PlanePoint, int& IndexTriangle,
			//	Matrix::Math::Vector3& TrianglePoint)const;
			///********************************RelationWith******************************************/
			////点和平面的位置关系(VSFRONT VSBACK VSPLANAR)
			// int RelationWith(const Matrix::Math::Vector3& Point)const;
			////测试直线与平面位置关系
			////VSNOINTERSECT VSNTERSECT VSON VSBACK VSFRONT
			// int RelationWith(const VSLine3& Line, bool bCull, VSREAL& fLineParameter)const;
			////测试射线与平面位置关系
			////VSNOINTERSECT VSNTERSECT VSON VSBACK VSFRONT
			// int RelationWith(const VSRay3& Ray, bool bCull, VSREAL& fRayParameter)const;
			////测试线段与平面位置关系
			////VSNOINTERSECT VSNTERSECT VSON VSBACK VSFRONT
			// int RelationWith(const VSSegment3& Segment, bool bCull, VSREAL& fSegmentParameter)const;
			////测试平面和OBB位置关系
			////VSFRONT VSBACK VSINTERSECT
			// int RelationWith(const OBB3& OBB)const;
			////测试平面和AABB位置关系
			////VSFRONT VSBACK VSINTERSECT
			// int RelationWith(const VSAABB3& AABB)const;
			////平面与球的位置关系
			////VSFRONT VSBACK VSINTERSECT
			// int RelationWith(const VSSphere3& Sphere)const;
			////平面和三角形位置关系
			////VSON VSFRONT VSBACK VSINTERSECT
			// int RelationWith(const Triangle3& Triangle)const;
			// int RelationWith(const Triangle3& Triangle, VSSegment3& Segment)const;
			////测试做为参数平面和平面位置关系
			////VSNOINTERSECT VSINTERSECT
			// int RelationWith(const VSPlane3& Plane)const;
			// int RelationWith(const VSPlane3& Plane, VSLine3& Line)const;
			////平面和矩形位置关系
			////VSON VSFRONT VSBACK VSINTERSECT
			// int RelationWith(const VSRectangle3& Rectangle)const;
			// int RelationWith(const VSRectangle3& Rectangle, VSSegment3& Segment)const;

			////平面和多边形位置关系
			////VSON VSFRONT VSBACK VSINTERSECT
			// int RelationWith(const VSPolygon3& Polygon)const;
			// int RelationWith(const VSPolygon3& Polygon, VSSegment3& Segment)const;

			////平面和圆柱位置关系
			// int RelationWith(const VSCylinder3& Cylinder3)const;

		}; // class
		   /*----------------------------------------------------------------*/
#include "Plane3.inl"

	}
}