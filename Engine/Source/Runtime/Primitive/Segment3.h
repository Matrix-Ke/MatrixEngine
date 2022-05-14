#pragma once
#include "Ray3.h"
#include "Math/Vector3.h"

namespace Matrix
{
    namespace Primitive
    {
        class MATRIX_PRIMITIVE_API VSSegment3 : public VSRay3
        {
        private:
            Matrix::Math::VSVector3 m_End;
            VSREAL m_fLen;

        public:
            VSSegment3();
            ~VSSegment3();
            VSSegment3(const Matrix::Math::VSVector3 &Orig, const Matrix::Math::VSVector3 &End);
            VSSegment3(const Matrix::Math::VSVector3 &Orig, const Matrix::Math::VSVector3 &Dir, VSREAL fLen);
            bool GetParameter(const Matrix::Math::VSVector3 &Point, VSREAL &fSegmentParameter) const;
            //�þ���任����
            void Transform(const VSSegment3 &Segment, const Matrix::Math::VSMatrix3X3W &Mat);
            /*************************************inline************************************************/
            inline const Matrix::Math::VSVector3 &GetEnd() const;
            inline VSREAL GetLen() const;
            inline void Set(const Matrix::Math::VSVector3 &Orig, const Matrix::Math::VSVector3 &End);
            inline void Set(const Matrix::Math::VSVector3 &Orig, const Matrix::Math::VSVector3 &Dir, VSREAL fLen);
            inline Matrix::Math::VSVector3 GetParameterPoint(VSREAL fSegmentParameter) const;

            ///********************************RelationWith******************************************/
            ////�����߶���������λ�ù�ϵ bCullΪ�Ƿ�Ϊ�������,�Ƿ��ǳ���,t�����ཻ����
            ////VSNOINTERSECT VSNTERSECT
            // int RelationWith(const VSTriangle3& Triangle, bool bCull, VSREAL& fSegmentParameter,
            //	VSREAL fTriangleParameter[3])const;
            ////�����߶���ƽ��λ�ù�ϵ
            ////VSNOINTERSECT VSNTERSECT VSON VSBACK VSFRONT
            // int RelationWith(const VSPlane3& Plane, bool bCull, VSREAL& fSegmentParameter)const;
            ////�����߶������λ�ù�ϵ
            ////VSNOINTERSECT VSNTERSECT
            // int RelationWith(const VSRectangle3& Rectangle, bool bCull, VSREAL& fSegmentParameter,
            //	VSREAL fRectangleParameter[2])const;

            ////�����߶���OBBλ�ù�ϵ
            ////VSNOINTERSECT VSNTERSECT VSIN
            // int RelationWith(const VSOBB3& OBB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
            ////�����߶���AABBλ�ù�ϵ
            ////VSNOINTERSECT VSNTERSECT VSIN
            // int RelationWith(const VSAABB3& AABB, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
            ////�����߶�����λ�ù�ϵ
            ////VSNOINTERSECT VSNTERSECT VSIN
            // int RelationWith(const VSSphere3& sphere, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
            ////�����߶�������λ�ù�ϵ
            ////VSNOINTERSECT VSNTERSECT
            // int RelationWith(const VSPolygon3& Polygon, VSREAL& fSegmentParameter,
            //	bool bCull, int& iIndexTriangle, VSREAL fTriangleParameter[3])const;

            ///*************************************����************************************************/
            ////����߶ξ���
            // VSREAL SquaredDistance(const Matrix::Math::VSVector3& Point, VSREAL& fSegmentParameter)const;
            ////ֱ�ߺ��߶ξ���
            // VSREAL SquaredDistance(const VSLine3& Line, VSREAL& fSegmentParameter, VSREAL& fLineParameter)const;
            ////���ߺ��߶ξ���
            // VSREAL SquaredDistance(const VSRay3& Ray, VSREAL& fSegmentParameter, VSREAL& fRayParameter)const;
            ////�߶κ��߶ξ���
            // VSREAL SquaredDistance(const VSSegment3& Segment, VSREAL& fSegment1Parameter, VSREAL& fSegment2Parameter)const;
            ////�߶κ������ξ���
            // VSREAL SquaredDistance(const VSTriangle3& Triangle, VSREAL& fSegmentParameter, VSREAL fTriangleParameter[3])const;
            ////�߶κ;��ξ���
            // VSREAL SquaredDistance(const VSRectangle3& Rectangle, VSREAL& fSegmentParameter, VSREAL fRectangleParameter[2])const;
            ////�߶κ�OBB����
            // VSREAL SquaredDistance(const VSOBB3& OBB, VSREAL& fSegmentParameter, VSREAL fOBBParameter[3])const;

            ////�߶κ���ľ���
            // VSREAL Distance(const VSSphere3& Sphere, VSREAL& fSegmentParameter, Matrix::Math::VSVector3& SpherePoint)const;

            ////�߶κ�ƽ�����
            // VSREAL Distance(const VSPlane3& Plane, Matrix::Math::VSVector3& SegmentPoint, Matrix::Math::VSVector3& PlanePoint)const;

            ////�߶κ�AABB����
            // VSREAL SquaredDistance(const VSAABB3& AABB, VSREAL& fSegmentParameter, VSREAL fAABBParameter[3])const;

            ////�߶κͶ���ξ���
            // VSREAL SquaredDistance(const VSPolygon3& Polygon, VSREAL& fSegmentParameter,
            //	int& IndexTriangle,
            //	VSREAL fTriangleParameter[3])const;
        };

#include "Segment3.inl"
    }
}