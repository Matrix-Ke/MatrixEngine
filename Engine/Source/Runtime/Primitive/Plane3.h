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
            Matrix::Math::Vector3 m_N; //ƽ�淨����
            VSREAL m_fD;               // ��ԭ��ľ���(ax+by+cz+d=0)

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

            /*************************************����************************************************/
            //�㵽ƽ�����
            VSREAL Distance(const Matrix::Math::Vector3 &Point, Matrix::Math::Vector3 &PlanePoint) const;
            //ƽ�����ľ���
            VSREAL Distance(const Sphere3 &Sphere, Matrix::Math::Vector3 &SpherePoint) const;
            //ֱ�ߺ�ƽ�����
            VSREAL Distance(const Line3 &Line, Matrix::Math::Vector3 &PlanePoint, Matrix::Math::Vector3 &LinePoint) const;
            //���ߺ�ƽ�����
            VSREAL Distance(const Ray3 &Ray, Matrix::Math::Vector3 &PlanePoint, Matrix::Math::Vector3 &RayPoint) const;
            //�߶κ�ƽ�����
            VSREAL Distance(const Segment3 &Segment, Matrix::Math::Vector3 &PlanePoint, Matrix::Math::Vector3 &SegmentPoint) const;

            //������뺯����û�п����ཻ������¼���ģ���Ϊ�ཻ������¾���Ϊ0������RelationWith�ж�λ�ù�ϵ�������������������
            //ƽ���ƽ�����
            VSREAL Distance(const Plane3 &Plane, Matrix::Math::Vector3 &Plane1Point, Matrix::Math::Vector3 &Plane2Point) const;
            //ƽ��������ξ���
            VSREAL Distance(const Triangle3 &Triangle, Matrix::Math::Vector3 &PlanePoint, Matrix::Math::Vector3 &TrianglePoint) const;
            //���κ�ƽ�����
            VSREAL Distance(const Rectangle3 &Rectangle, Matrix::Math::Vector3 &PlanePoint, Matrix::Math::Vector3 &RectanglePoint) const;
            // OBB��ƽ�����
            VSREAL Distance(const OBB3 &OBB, Matrix::Math::Vector3 &PlanePoint, Matrix::Math::Vector3 &OBBPoint) const;
            // AABB��ƽ�����
            VSREAL Distance(const AABB3 &AABB, Matrix::Math::Vector3 &PlanePoint, Matrix::Math::Vector3 &AABBPoint) const;
            //ƽ��Ͷ���ξ���
            VSREAL Distance(const Polygon3 &Polygon, Matrix::Math::Vector3 &PlanePoint, int &IndexTriangle,
                            Matrix::Math::Vector3 &TrianglePoint) const;
            /********************************RelationWith******************************************/
            //���ƽ���λ�ù�ϵ(IT_Front IT_Back VSPLANAR)
            int RelationWith(const Matrix::Math::Vector3 &Point) const;
            //����ֱ����ƽ��λ�ù�ϵ
            // IT_NoIntersect VSNTERSECT IT_On IT_Back IT_Front
            int RelationWith(const Line3 &Line, bool bCull, VSREAL &fLineParameter) const;
            //����������ƽ��λ�ù�ϵ
            // IT_NoIntersect VSNTERSECT IT_On IT_Back IT_Front
            int RelationWith(const Ray3 &Ray, bool bCull, VSREAL &fRayParameter) const;
            //�����߶���ƽ��λ�ù�ϵ
            // IT_NoIntersect VSNTERSECT IT_On IT_Back IT_Front
            int RelationWith(const Segment3 &Segment, bool bCull, VSREAL &fSegmentParameter) const;
            //����ƽ���OBBλ�ù�ϵ
            // IT_Front IT_Back IT_Intersect
            int RelationWith(const OBB3 &OBB) const;
            //����ƽ���AABBλ�ù�ϵ
            // IT_Front IT_Back IT_Intersect
            int RelationWith(const AABB3 &AABB) const;
            //ƽ�������λ�ù�ϵ
            // IT_Front IT_Back IT_Intersect
            int RelationWith(const Sphere3 &Sphere) const;
            //ƽ���������λ�ù�ϵ
            // IT_On IT_Front IT_Back IT_Intersect
            int RelationWith(const Triangle3 &Triangle) const;
            int RelationWith(const Triangle3 &Triangle, Segment3 &Segment) const;
            //������Ϊ����ƽ���ƽ��λ�ù�ϵ
            // IT_NoIntersect IT_Intersect
            int RelationWith(const Plane3 &Plane) const;
            int RelationWith(const Plane3 &Plane, Line3 &Line) const;
            //ƽ��;���λ�ù�ϵ
            // IT_On IT_Front IT_Back IT_Intersect
            int RelationWith(const Rectangle3 &Rectangle) const;
            int RelationWith(const Rectangle3 &Rectangle, Segment3 &Segment) const;

            //ƽ��Ͷ����λ�ù�ϵ
            // IT_On IT_Front IT_Back IT_Intersect
            int RelationWith(const Polygon3 &Polygon) const;
            int RelationWith(const Polygon3 &Polygon, Segment3 &Segment) const;

        }; // class
           /*----------------------------------------------------------------*/
#include "Plane3.inl"

    };
}