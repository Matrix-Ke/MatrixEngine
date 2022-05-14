#pragma once
#include "VSPlane3.h"
#include "VSRectangle3.h"
#include "Math/CMathInterface.h"

/*
AABB��ԳƱ߽�У�3��������A1,A2,A3��Զƽ���ڵ�ǰ���������ᣬ������Ϊ��λ�����ᣬfA1,fA2,fA3Ϊ���᳤�ȣ������ڲ��ĵ㶼���Ա�ʾ��
a * A1 + b * A2 + c * A3 a,b,cΪ����������|a|<=fA1,|b|<=fA2,|c|<=fA3
*/
namespace Matrix
{
	namespace Primitive
	{
		class MATRIX_PRIMITIVE_API VSAABB3
		{
		private:
			static const Matrix::Math::VSVector3	m_A[3];			// 3����				
			Matrix::Math::VSVector3	m_Center;					// ���ĵ�
			VSREAL		m_fA[3];					// 3������ĳ���
			Matrix::Math::VSVector3	m_Max;						//����
			Matrix::Math::VSVector3	m_Min;						//��С��
		public:

			VSAABB3();
			~VSAABB3();

			//ͨ���������С�㹹��AABB
			VSAABB3(const Matrix::Math::VSVector3& Max, const Matrix::Math::VSVector3& Min);
			//ͨ�����ĵ��3����İ볤�ȹ���AABB
			VSAABB3(const Matrix::Math::VSVector3& Center, VSREAL fA0, VSREAL fA1, VSREAL fA2);
			VSAABB3(const Matrix::Math::VSVector3& Center, VSREAL fA[3]);
			//ͨ���㼯�Ϲ���AABB
			void CreateAABB(const Matrix::Math::VSVector3* const pPointArray, unsigned int uiPointNum);
			/*********************************** inline *************************************/
			//������Ӧ�Ĳ���
			inline void Set(const Matrix::Math::VSVector3& Max, const Matrix::Math::VSVector3& Min);
			inline void Set(const Matrix::Math::VSVector3& Center, VSREAL fA0, VSREAL fA1, VSREAL fA2);
			inline void Set(const Matrix::Math::VSVector3& Center, VSREAL fA[3]);
			//��ȡ��Ӧ�Ĳ���
			inline void GetfA(VSREAL fA[3])const;
			inline const Matrix::Math::VSVector3& GetCenter()const;
			inline Matrix::Math::VSVector3 GetParameterPoint(VSREAL fAABBParameter[3])const;
			inline Matrix::Math::VSVector3 GetParameterPoint(VSREAL fAABBParameter0, VSREAL fAABBParameter1, VSREAL fAABBParameter2)const;
			inline const Matrix::Math::VSVector3& GetMaxPoint()const;
			inline const Matrix::Math::VSVector3& GetMinPoint()const;
			//�õ�AABB6��ƽ��
			void GetPlane(VSPlane3 pPlanes[6])const;
			//�õ�AABB8����
			void GetPoint(Matrix::Math::VSVector3 Point[8])const;
			//�õ�AABB6������
			void GetRectangle(VSRectangle3 Rectangle[6])const;
			//����AABB��һ�㷵��AABB�Ĳ���
			bool GetParameter(const Matrix::Math::VSVector3& Point, VSREAL fAABBParameter[3])const;
			//�þ���任AABB
			void Transform(const VSAABB3& AABB,
				const Matrix::Math::VSMatrix3X3W& m, bool bHasProject = false);
			//�ϲ�2��AABB
			VSAABB3 MergeAABB(const VSAABB3& AABB)const;
			void GetQuadAABB(VSAABB3 AABB[4])const;
			void GetOctAABB(VSAABB3 AABB[8])const;
			VSAABB3 GetMin(const VSAABB3& AABB) const;

			bool GetIntersect(VSAABB3& AABB, VSAABB3& OutAABB)const;



			///*************************************����************************************************/
			////���AABB����
			//VSREAL SquaredDistance(const Matrix::Math::VSVector3& Point, VSREAL fAABBParameter[3])const;
			////ֱ�ߺ�AABB����
			//VSREAL SquaredDistance(const VSLine3& Line, VSREAL fAABBParameter[3], VSREAL& fLineParameter)const;
			////���ߺ�AABB����
			//VSREAL SquaredDistance(const VSRay3& Ray, VSREAL fAABBParameter[3], VSREAL& fRayParameter)const;
			////�߶κ�AABB����
			//VSREAL SquaredDistance(const VSSegment3& Segment, VSREAL fAABBParameter[3], VSREAL& fSegmentParameter)const;

			////�����κ�AABB����
			//VSREAL SquaredDistance(const VSTriangle3& Triangle, VSREAL AABBParameter[3],
			//	VSREAL TriangleParameter[3])const;

			////���κ�AABB����
			//VSREAL SquaredDistance(const VSRectangle3& Rectangle, VSREAL AABBParameter[3],
			//	VSREAL RectangleParameter[2])const;
			////AABB��AABB����
			//VSREAL SquaredDistance(const VSAABB3& AABB, VSREAL AABB1Parameter[3],
			//	VSREAL AABB2Parameter[3])const;
			////AABB����ľ���
			//VSREAL Distance(const VSSphere3& Sphere, VSREAL fAABBParameter[3], Matrix::Math::VSVector3& SpherePoint)const;

			////AABB��ƽ�����
			//VSREAL Distance(const VSPlane3& Plane, Matrix::Math::VSVector3& AABBPoint, Matrix::Math::VSVector3& PlanePoint)const;

			////����κ�AABB����
			//VSREAL SquaredDistance(const VSPolygon3& Polygon, VSREAL AABBParameter[3], int& IndexTriangle,
			//	VSREAL TriangleParameter[3])const;
			///********************************RelationWith******************************************/
			////���AABBλ�ù�ϵ
			////VSIN VSOUT VSON
			//int RelationWith(const Matrix::Math::VSVector3& Point)const;
			////����ֱ����AABBλ�ù�ϵ
			////VSNOINTERSECT VSNTERSECT
			//int RelationWith(const VSLine3& Line, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			////����������AABBλ�ù�ϵ
			////VSNOINTERSECT VSNTERSECT
			//int RelationWith(const VSRay3& Ray, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			////�����߶���AABBλ�ù�ϵ
			////VSNOINTERSECT VSNTERSECT VSIN
			//int RelationWith(const VSSegment3& Segment, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			////����ƽ���AABBλ�ù�ϵ
			////VSFRONT VSBACK VSINTERSECT
			//int RelationWith(const VSPlane3& Plane)const;
			////�����κ�AABBλ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT VSIN
			//int RelationWith(const VSTriangle3& Triangle)const;
			////���κ�AABBλ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT VSIN
			//int RelationWith(const VSRectangle3& Rectangle)const;

			////AABB��AABBλ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT
			//int RelationWith(const VSAABB3& AABB)const;

			////AABB��Բλ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT
			//int RelationWith(const VSSphere3& Sphere)const;

		};

#include "VSAABB3.inl"
	}
};