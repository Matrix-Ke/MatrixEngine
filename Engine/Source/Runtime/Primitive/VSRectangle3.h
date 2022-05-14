#pragma once
#include "VSPlane3.h"
#include "Math/VSVector3.h"

/********************************************************************************************


__________________
|        |        |
|    A[0]|        |
|		  |        |
|        |_A[1]___|
|                 |
|                 |
|_________________|


���ֶ��� ������ Ϊ cross (A[0],A[1]),�涨�ɼ� ����������Ļ�⣬
********************************************************************************************/
namespace Matrix
{
	namespace Primitive
	{
		class VSTriangle3;
		class MATRIX_PRIMITIVE_API VSRectangle3 :public VSPlane3
		{
		private:
			Matrix::Math::VSVector3 m_A[2];
			VSREAL m_fA[2];
			Matrix::Math::VSVector3 m_Center;
		public:
			VSRectangle3();
			~VSRectangle3();
			VSRectangle3(const Matrix::Math::VSVector3& Center, const Matrix::Math::VSVector3& A0, const Matrix::Math::VSVector3& A1, VSREAL fA0, VSREAL fA1);
			VSRectangle3(const Matrix::Math::VSVector3& Center, const Matrix::Math::VSVector3 A[2], const VSREAL fA[2]);
			bool GetParameter(const Matrix::Math::VSVector3& Point, VSREAL fRectangleParameter[2])const;
			void Transform(const VSRectangle3& Rectangle,
				const Matrix::Math::VSMatrix3X3W& Mat);
			/*************************************inline************************************************/
			inline void Set(const Matrix::Math::VSVector3& Center, const Matrix::Math::VSVector3& A0, const Matrix::Math::VSVector3& A1, VSREAL fA0, VSREAL fA1);
			inline void Set(const Matrix::Math::VSVector3& Center, const Matrix::Math::VSVector3 A[2], const VSREAL fA[2]);
			inline void GetA(Matrix::Math::VSVector3 A[2])const;
			inline void GetfA(VSREAL fA[2])const;
			inline const Matrix::Math::VSVector3& GetCenter()const;
			inline void GetPoint(Matrix::Math::VSVector3 Point[4])const;
			inline Matrix::Math::VSVector3 GetParameterPoint(VSREAL fRectangleParameter[2])const;
			inline Matrix::Math::VSVector3 GetParameterPoint(VSREAL fRectangleParameter0, VSREAL fRectangleParameter1)const;


			///*************************************����************************************************/
			////��;��ξ���
			//VSREAL SquaredDistance(const Matrix::Math::VSVector3& Point, VSREAL fRectangleParameter[2])const;

			////���κ;��ξ���
			//VSREAL SquaredDistance(const VSRectangle3& Rectangle,
			//	VSREAL fRectangle1Parameter[2], VSREAL fRectangle2Parameter[2])const;

			////�����κ;��ξ���
			//VSREAL SquaredDistance(const VSTriangle3& Triangle, VSREAL fRectangleParameter[2], VSREAL fTriangleParameter[3])const;

			////ֱ�ߺ;��ξ���
			//VSREAL SquaredDistance(const VSLine3& Line, VSREAL fRectangleParameter[2], VSREAL& fLineParameter)const;
			////���ߺ;��ξ���
			//VSREAL SquaredDistance(const VSRay3& Ray, VSREAL fRectangleParameter[2], VSREAL& fRayParameter)const;
			////�߶κ;��ξ���
			//VSREAL SquaredDistance(const VSSegment3& Segment, VSREAL fRectangleParameter[2], VSREAL& fSegmentParameter)const;
			////���κ�OBB����
			//VSREAL SquaredDistance(const VSOBB3& OBB, VSREAL RectangleParameter[2], VSREAL OBBParameter[3])const;
			////���κ���ľ���
			//VSREAL Distance(const VSSphere3& Sphere, VSREAL fRectangleParameter[2], Matrix::Math::VSVector3& SpherePoint)const;
			////���κ�ƽ�����
			//VSREAL Distance(const VSPlane3& Plane, Matrix::Math::VSVector3& RectanglePoint, Matrix::Math::VSVector3& PlanePoint)const;
			////���κ�AABB����
			//VSREAL SquaredDistance(const VSAABB3& AABB, VSREAL RectangleParameter[2]
			//	, VSREAL AABBParameter[3])const;

			////����κ;��ξ���
			//VSREAL SquaredDistance(const VSPolygon3& Polygon,
			//	VSREAL fRectangleParameter[2],
			//	int& IndexTriangle,
			//	VSREAL fTriangleParameter[3])const;
			///********************************RelationWith******************************************/
			////����ֱ�������λ�ù�ϵ
			////VSNOINTERSECT VSNTERSECT
			//int RelationWith(const VSLine3& Line, bool bCull, VSREAL fRectangleParameter[2], VSREAL& fLineParameter)const;
			////�������������λ�ù�ϵ
			////VSNOINTERSECT VSNTERSECT
			//int RelationWith(const VSRay3& Ray, bool bCull, VSREAL fRectangleParameter[2], VSREAL& fRayParameter)const;
			////�����߶������λ�ù�ϵ
			////VSNOINTERSECT VSNTERSECT
			//int RelationWith(const VSSegment3& Segment, bool bCull, VSREAL fRectangleParameter[2], VSREAL& fSegmentParameter)const;
			////ƽ��;���λ�ù�ϵ
			////VSON VSFRONT VSBACK VSINTERSECT
			//int RelationWith(const VSPlane3& Plane)const;
			//int RelationWith(const VSPlane3& Plane, VSSegment3& Segment)const;
			////�����κ;���λ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT
			//int RelationWith(const VSTriangle3& Triangle)const;
			//int RelationWith(const VSTriangle3& Triangle, VSSegment3& Segment)const;
			////���κ;���λ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT
			//int RelationWith(const VSRectangle3& Rectangle)const;
			//int RelationWith(const VSRectangle3& Rectangle, VSSegment3& Segment)const;
			////���κ�AABBλ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT VSIN
			//int RelationWith(const VSAABB3& AABB)const;

			////���κ�OBBλ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT VSIN
			//int RelationWith(const VSOBB3& OBB)const;

			////���κ�Բλ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT VSIN
			//int RelationWith(const VSSphere3& Sphere)const;
		};

#include "VSRectangle3.inl"
	}
}
