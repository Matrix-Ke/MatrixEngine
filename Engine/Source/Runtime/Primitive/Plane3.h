#pragma once
#include "Line3.h"
#include "Math/Vector3.h"
#include "math/Matrix3.h"

namespace Matrix
{
    namespace Primitive
    {
        class Ray3;
        class Segment3;

        class Polygon3;
        class Triangle3;
        class Rectangle3;

        class AABB3;
        class OBB3;
        class Sphere3;

        class MATRIX_PRIMITIVE_API Plane3
        {
        protected:
            Matrix::Math::Vector3 m_N; //平面法向量
            VSREAL m_fD;               // 到原点的距离(ax+by+cz+d=0)

        public:
            Plane3();
            Plane3(const Matrix::Math::Vector3 &N, const Matrix::Math::Vector3 &P);
            Plane3(const Matrix::Math::Vector3 &P0, const Matrix::Math::Vector3 &P1, const Matrix::Math::Vector3 &P2);
            Plane3(const Matrix::Math::Vector3 Point[3]);
            Plane3(const Matrix::Math::Vector3 &N, VSREAL fD);
            void Transform(const Plane3 &Plane, const Matrix::Math::Matrix4 &Mat);
            /*********************************** inline *************************************/
            inline const Matrix::Math::Vector3 &GetN() const;
            inline Matrix::Math::Vector3 GetPoint() const;
            inline VSREAL GetfD() const;
            inline void Set(const Matrix::Math::Vector3 &N, const Matrix::Math::Vector3 &P);
            inline void Set(const Matrix::Math::Vector3 &N, VSREAL fD);
            inline void Set(const Matrix::Math::Vector3 &P0, const Matrix::Math::Vector3 &P1, const Matrix::Math::Vector3 &P2);
            inline void Set(const Matrix::Math::Vector3 Point[3]);
            inline Plane3 GetPlane() const;
            Matrix::Math::Vector3 ReflectDir(const Matrix::Math::Vector3 &Dir) const;
            void GetReverse(Plane3 &OutPlane) const;

            /*************************************距离************************************************/
            //点到平面距离
            VSREAL Distance(const Matrix::Math::Vector3 &Point, Matrix::Math::Vector3 &PlanePoint) const;
            //平面和球的距离
            VSREAL Distance(const Sphere3 &Sphere, Matrix::Math::Vector3 &SpherePoint) const;
            //直线和平面距离
            VSREAL Distance(const Line3 &Line, Matrix::Math::Vector3 &PlanePoint, Matrix::Math::Vector3 &LinePoint) const;
            //射线和平面距离
            VSREAL Distance(const Ray3 &Ray, Matrix::Math::Vector3 &PlanePoint, Matrix::Math::Vector3 &RayPoint) const;
            //线段和平面距离
            VSREAL Distance(const Segment3 &Segment, Matrix::Math::Vector3 &PlanePoint, Matrix::Math::Vector3 &SegmentPoint) const;

            //下面距离函数再没有考虑相交的情况下计算的，因为相交的情况下举例为0，先用RelationWith判断位置关系，再用下面来计算距离
            //平面和平面距离
            VSREAL Distance(const Plane3 &Plane, Matrix::Math::Vector3 &Plane1Point, Matrix::Math::Vector3 &Plane2Point) const;
            //平面和三角形距离
            VSREAL Distance(const Triangle3 &Triangle, Matrix::Math::Vector3 &PlanePoint, Matrix::Math::Vector3 &TrianglePoint) const;
            //矩形和平面距离
            VSREAL Distance(const Rectangle3 &Rectangle, Matrix::Math::Vector3 &PlanePoint, Matrix::Math::Vector3 &RectanglePoint) const;
            // OBB和平面距离
            VSREAL Distance(const OBB3 &OBB, Matrix::Math::Vector3 &PlanePoint, Matrix::Math::Vector3 &OBBPoint) const;
            // AABB和平面距离
            VSREAL Distance(const AABB3 &AABB, Matrix::Math::Vector3 &PlanePoint, Matrix::Math::Vector3 &AABBPoint) const;
            //平面和多边形距离
            VSREAL Distance(const Polygon3 &Polygon, Matrix::Math::Vector3 &PlanePoint, int &IndexTriangle,
                            Matrix::Math::Vector3 &TrianglePoint) const;
            /********************************RelationWith******************************************/
            //点和平面的位置关系(IT_Front IT_Back VSPLANAR)
            int RelationWith(const Matrix::Math::Vector3 &Point) const;
            //测试直线与平面位置关系
            // IT_NoIntersect VSNTERSECT IT_On IT_Back IT_Front
            int RelationWith(const Line3 &Line, bool bCull, VSREAL &fLineParameter) const;
            //测试射线与平面位置关系
            // IT_NoIntersect VSNTERSECT IT_On IT_Back IT_Front
            int RelationWith(const Ray3 &Ray, bool bCull, VSREAL &fRayParameter) const;
            //测试线段与平面位置关系
            // IT_NoIntersect VSNTERSECT IT_On IT_Back IT_Front
            int RelationWith(const Segment3 &Segment, bool bCull, VSREAL &fSegmentParameter) const;
            //测试平面和OBB位置关系
            // IT_Front IT_Back IT_Intersect
            int RelationWith(const OBB3 &OBB) const;
            //测试平面和AABB位置关系
            // IT_Front IT_Back IT_Intersect
            int RelationWith(const AABB3 &AABB) const;
            //平面与球的位置关系
            // IT_Front IT_Back IT_Intersect
            int RelationWith(const Sphere3 &Sphere) const;
            //平面和三角形位置关系
            // IT_On IT_Front IT_Back IT_Intersect
            int RelationWith(const Triangle3 &Triangle) const;
            int RelationWith(const Triangle3 &Triangle, Segment3 &Segment) const;
            //测试做为参数平面和平面位置关系
            // IT_NoIntersect IT_Intersect
            int RelationWith(const Plane3 &Plane) const;
            int RelationWith(const Plane3 &Plane, Line3 &Line) const;
            //平面和矩形位置关系
            // IT_On IT_Front IT_Back IT_Intersect
            int RelationWith(const Rectangle3 &Rectangle) const;
            int RelationWith(const Rectangle3 &Rectangle, Segment3 &Segment) const;

            //平面和多边形位置关系
            // IT_On IT_Front IT_Back IT_Intersect
            int RelationWith(const Polygon3 &Polygon) const;
            int RelationWith(const Polygon3 &Polygon, Segment3 &Segment) const;

        }; // class
           /*----------------------------------------------------------------*/
#include "Plane3.inl"

    };
}