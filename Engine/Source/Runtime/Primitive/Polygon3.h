#pragma once
#include "Plane3.h"
#include "Core/MemoryManager.h"

namespace Matrix
{
	namespace Primitive
	{
		class MATRIX_PRIMITIVE_API Polygon3 : public Plane3, public Core::MemoryObject
		{
		private:
			unsigned int m_PointNum;           //�����
			unsigned int m_IndexNum;           //��������
			bool m_Flag;                       // ��־λ
			Matrix::Math::Vector3* m_pPoint; // ���б�
			VSUSHORT_INDEX* m_pIndex;          // �����б�
		public:
			Polygon3();
			~Polygon3();

			Polygon3(const Matrix::Math::Vector3* pPoint, unsigned int PointNum);
			//����
			bool CopyFrom(const Polygon3& Polygon);
			//��ת��
			void SwapFaces();
			/*********************************** inline *************************************/
			inline void Set(const Matrix::Math::Vector3* pPoint, unsigned int PointNum);
			inline unsigned int GetPointNum() const;
			inline unsigned int GetIndexNum() const;
			inline const Matrix::Math::Vector3* const GetpPoint() const;
			inline const VSUSHORT_INDEX* const GetpIndex() const;
			inline unsigned int GetFlag() const;

			///*************************************����************************************************/
			////��Ͷ���ξ���
			// VSREAL SquaredDistance(const Matrix::Math::Vector3& Point, int& IndexTriangle, VSREAL fTriangleParameter[3])const;
			////����κͶ���ξ���
			// VSREAL SquaredDistance(const Triangle3& Triangle,
			//	int& IndexTriangle,
			//	VSREAL fTriangle1Parameter[3],
			//	VSREAL fTriangle2Parameter[3])const;
			////����κ;��ξ���
			// VSREAL SquaredDistance(const Rectangle3& Rectangle,
			//	int& IndexTriangle,
			//	VSREAL fTriangleParameter[3],
			//	VSREAL fRectangleParameter[2])const;

			////ֱ�ߺͶ���ξ���
			// VSREAL SquaredDistance(const Line3& Line, int& IndexTriangle,
			//	VSREAL fTriangleParameter[3], VSREAL& fLineParameter)const;
			////���ߺͶ���ξ���
			// VSREAL SquaredDistance(const Ray3& Ray, int& IndexTriangle,
			//	VSREAL fTriangleParameter[3], VSREAL& fRayParameter)const;
			////�߶κͶ���ξ���
			// VSREAL SquaredDistance(const Segment3& Segment, int& IndexTriangle,
			//	VSREAL fTriangleParameter[3], VSREAL& fSegmentParameter)const;
			////����κ�OBB����
			// VSREAL SquaredDistance(const OBB3& OBB, int& IndexTriangle,
			//	VSREAL TriangleParameter[3], VSREAL OBBParameter[3])const;
			////����κ���ľ���
			// VSREAL Distance(const Sphere3& Sphere, int& IndexTriangle,
			//	VSREAL fTriangleParameter[3], Matrix::Math::Vector3& SpherePoint)const;

			////ƽ��Ͷ���ξ���
			// VSREAL Distance(const Plane3& Plane, int& IndexTriangle,
			//	Matrix::Math::Vector3& TrianglePoint, Matrix::Math::Vector3& PlanePoint)const;
			////����κ�AABB����
			// VSREAL SquaredDistance(const AABB3& AABB, int& IndexTriangle,
			//	VSREAL TriangleParameter[3]
			//	, VSREAL AABBParameter[3])const;

			////����κͶ���ξ���
			// VSREAL SquaredDistance(const Polygon3& Polygon, int& Index1Triangle,
			//	VSREAL Triangle1Parameter[3], int& Index2Triangle,
			//	VSREAL Triangle2Parameter[3])const;
			///********************************RelationWith******************************************/
			//	//����ֱ��������λ�ù�ϵ bCullΪ�Ƿ�Ϊ�������,�Ƿ��ǳ���,t�����ཻ����
			//	//VSNOINTERSECT VSNTERSECT
			// int RelationWith(const Line3& Line, bool bCull, int& iIndexTriangle, VSREAL fTriangleParameter[3],
			//	VSREAL& fLineParameter)const;
			////��������������λ�ù�ϵ
			////VSNOINTERSECT VSNTERSECT
			// int RelationWith(const Ray3& Ray, bool bCull, int& iIndexTriangle, VSREAL fTriangleParameter[3],
			//	VSREAL& fRayParameter)const;
			////�����߶�������λ�ù�ϵ
			////VSNOINTERSECT VSNTERSECT
			// int RelationWith(const Segment3& Segment, bool bCull, int& iIndexTriangle, VSREAL fTriangleParameter[3],
			//	VSREAL& fSegmentParameter)const;
			////ƽ��Ͷ����λ�ù�ϵ
			////VSON VSFRONT VSBACK VSINTERSECT
			// int RelationWith(const Plane3& Plane)const;
			// int RelationWith(const Plane3& Plane, Segment3& Segment)const;
			////����κ�������λ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT
			// int RelationWith(const Triangle3& Triangle)const;
			// int RelationWith(const Triangle3& Triangle, Segment3& Segment)const;
			////����κ;���λ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT
			// int RelationWith(const Rectangle3& Rectangle)const;
			// int RelationWith(const Rectangle3& Rectangle, Segment3& Segment)const;
			////����κ�AABBλ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT VSIN
			// int RelationWith(const AABB3& AABB)const;

			////����κ�OBBλ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT VSIN
			// int RelationWith(const OBB3& OBB)const;

			////����κ�Բλ�ù�ϵ
			////VSNOINTERSECT VSINTERSECT VSIN
			// int RelationWith(const Sphere3& Sphere)const;

			///*************************************** Clip *********************************/
			////ƽ����ж����
			// void	Clip(const Plane3& Plane,
			//	Polygon3& pFront,
			//	Polygon3& pBack)const;
			////��AABB���ж���������ʺ�AABB
			// void	Clip(const AABB3& ABBB);
		};
#include "Polygon3.inl"
	}
}