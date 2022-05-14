#pragma once
#include"VSPlane3.h"
#include "Core/MemoryManager.h"

namespace Matrix
{
	namespace Primitive
	{
		class MATRIX_PRIMITIVE_API VSPolygon3 : public VSPlane3, public Core::MemoryObject
		{
		private:

			unsigned int	m_PointNum;		//�����
			unsigned int	m_IndexNum;		//��������
			bool			m_Flag;			// ��־λ
			Matrix::Math::VSVector3* m_pPoint;		// ���б�
			VSUSHORT_INDEX* m_pIndex;		// �����б�
		public:
			VSPolygon3();
			~VSPolygon3();

			VSPolygon3(const Matrix::Math::VSVector3* pPoint, unsigned int PointNum);
			//����
			bool CopyFrom(const VSPolygon3& Polygon);
			//��ת��
			void SwapFaces();
			/*********************************** inline *************************************/
			inline void Set(const Matrix::Math::VSVector3* pPoint, unsigned int PointNum);
			inline unsigned int GetPointNum()const;
			inline unsigned int GetIndexNum()const;
			inline const Matrix::Math::VSVector3* const GetpPoint()const;
			inline const VSUSHORT_INDEX* const GetpIndex()const;
			inline unsigned int GetFlag()const;


			///*************************************����************************************************/
			////��Ͷ���ξ���
			//VSREAL SquaredDistance(const Matrix::Math::VSVector3& Point, int& IndexTriangle, VSREAL fTriangleParameter[3])const;
			////����κͶ���ξ���
			//VSREAL SquaredDistance(const VSTriangle3& Triangle,
			//	int& IndexTriangle,
			//	VSREAL fTriangle1Parameter[3],
			//	VSREAL fTriangle2Parameter[3])const;
			////����κ;��ξ���
			//VSREAL SquaredDistance(const VSRectangle3& Rectangle,
			//	int& IndexTriangle,
			//	VSREAL fTriangleParameter[3],
			//	VSREAL fRectangleParameter[2])const;

			////ֱ�ߺͶ���ξ���
			//VSREAL SquaredDistance(const VSLine3& Line, int& IndexTriangle,
			//	VSREAL fTriangleParameter[3], VSREAL& fLineParameter)const;
			////���ߺͶ���ξ���
			//VSREAL SquaredDistance(const VSRay3& Ray, int& IndexTriangle,
			//	VSREAL fTriangleParameter[3], VSREAL& fRayParameter)const;
			////�߶κͶ���ξ���
			//VSREAL SquaredDistance(const VSSegment3& Segment, int& IndexTriangle,
			//	VSREAL fTriangleParameter[3], VSREAL& fSegmentParameter)const;
			////����κ�OBB����
			//VSREAL SquaredDistance(const VSOBB3& OBB, int& IndexTriangle,
			//	VSREAL TriangleParameter[3], VSREAL OBBParameter[3])const;
			////����κ���ľ���
			//VSREAL Distance(const VSSphere3& Sphere, int& IndexTriangle,
			//	VSREAL fTriangleParameter[3], Matrix::Math::VSVector3& SpherePoint)const;

			////ƽ��Ͷ���ξ���
			//VSREAL Distance(const VSPlane3& Plane, int& IndexTriangle,
			//	Matrix::Math::VSVector3& TrianglePoint, Matrix::Math::VSVector3& PlanePoint)const;
			////����κ�AABB����
			//VSREAL SquaredDistance(const VSAABB3& AABB, int& IndexTriangle,
			//	VSREAL TriangleParameter[3]
			//	, VSREAL AABBParameter[3])const;

			////����κͶ���ξ���
			//VSREAL SquaredDistance(const VSPolygon3& Polygon, int& Index1Triangle,
			//	VSREAL Triangle1Parameter[3], int& Index2Triangle,
			//	VSREAL Triangle2Parameter[3])const;
			///********************************RelationWith******************************************/
			//	//����ֱ��������λ�ù�ϵ bCullΪ�Ƿ�Ϊ�������,�Ƿ��ǳ���,t�����ཻ����
			//	//VSNOINTERSECT VSNTERSECT
			//int RelationWith(const VSLine3& Line, bool bCull, int& iIndexTriangle, VSREAL fTriangleParameter[3],
			//	VSREAL& fLineParameter)const;
			////��������������λ�ù�ϵ
			////VSNOINTERSECT VSNTERSECT
			//int RelationWith(const VSRay3& Ray, bool bCull, int& iIndexTriangle, VSREAL fTriangleParameter[3],
			//	VSREAL& fRayParameter)const;
			////�����߶�������λ�ù�ϵ
			////VSNOINTERSECT VSNTERSECT
			//int RelationWith(const VSSegment3& Segment, bool bCull, int& iIndexTriangle, VSREAL fTriangleParameter[3],
			//	VSREAL& fSegmentParameter)const;
			////ƽ��Ͷ����λ�ù�ϵ
			////VSON VSFRONT VSBACK VSINTERSECT
			//int RelationWith(const VSPlane3& Plane)const;
			//int RelationWith(const VSPlane3& Plane, VSSegment3& Segment)const;
			////����κ�������λ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT
			//int RelationWith(const VSTriangle3& Triangle)const;
			//int RelationWith(const VSTriangle3& Triangle, VSSegment3& Segment)const;
			////����κ;���λ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT
			//int RelationWith(const VSRectangle3& Rectangle)const;
			//int RelationWith(const VSRectangle3& Rectangle, VSSegment3& Segment)const;
			////����κ�AABBλ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT VSIN
			//int RelationWith(const VSAABB3& AABB)const;

			////����κ�OBBλ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT VSIN
			//int RelationWith(const VSOBB3& OBB)const;

			////����κ�Բλ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT VSIN
			//int RelationWith(const VSSphere3& Sphere)const;

			///*************************************** Clip *********************************/
			////ƽ����ж����
			//void	Clip(const VSPlane3& Plane,
			//	VSPolygon3& pFront,
			//	VSPolygon3& pBack)const;
			////��AABB���ж���������ʺ�AABB
			//void	Clip(const VSAABB3& ABBB);
		};
#include "VSPolygon3.inl"
	}
}