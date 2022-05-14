#pragma once
#include "Math/VSVector3.h"
#include "VSPlane3.h"
#include "VSTriangle3.h"
#include "VSAABB3.h"

/*****************************************************************************************


							   p1  _______________________________ P0
								  /|                            /|
								/  |                          /  |
							  /    |m_A[1]  |        m_A[2] /    |
						  p5/______|________|______/______/ p4   |
							|      |        |    /        |      |
							|  p2  |_ _  _ _|  / _ _ _ _ _|_ _ __| p3
							|     /         |/____________|      /
							|	 /	             m_A[0]    |    /
							|  /                          |  /
						p6	|/____________________________|/ p7



Plane0 right Plane1 left Plane2 front Plane3 back Plane4 up Plane5 down
****************************************************************************************/
namespace Matrix
{
	namespace Primitive
	{
		class Math::VSMatrix3X3;
		class VSLine3;
		class VSRay3;
		class VSRectangle3;
		class VSSegment3;
		class MATRIX_PRIMITIVE_API VSOBB3
		{
		private:
			Matrix::Math::VSVector3	m_A[3];		// 3����
			Matrix::Math::VSVector3	m_Center;	// ���ĵ�
			VSREAL		m_fA[3];	// 3������ĳ���
		public:


			VSOBB3();
			~VSOBB3();
			//����AABB
			VSOBB3(const Matrix::Math::VSVector3 A[3], VSREAL fA[3], const Matrix::Math::VSVector3& Center);
			VSOBB3(const Matrix::Math::VSVector3& A0, const Matrix::Math::VSVector3& A1, const Matrix::Math::VSVector3& A2,
				VSREAL fA0, VSREAL fA1, VSREAL fA2,
				const Matrix::Math::VSVector3& Center);
			//ͨ���㼯�Ϲ���AABB
			void CreateOBB(const Matrix::Math::VSVector3* const pPointArray, unsigned int uiPointNum);
			//�ϲ�AABB
			VSOBB3 MergeOBB(const VSOBB3& OBB)const;
			//ȡ��6��ƽ��
			void GetPlane(VSPlane3 pPlanes[6])const;
			//ȡ��8����
			void GetPoint(Matrix::Math::VSVector3 Point[8])const;
			//ȡ��6������
			void GetRectangle(VSRectangle3 Rectangle[6])const;
			//��ñ任��OBB�±任������������OBB��ͬһ������ϵ��
			void GetTransform(Matrix::Math::VSMatrix3X3W& m)const;
			//�õ������
			bool GetParameter(const Matrix::Math::VSVector3& Point, VSREAL fOBBParameter[3])const;
			//�ø�����OBB�ͱ任����������OBB
			void Transform(const VSOBB3& OBB, const Matrix::Math::VSMatrix3X3W& Mat);
			VSAABB3 GetAABB() const;
			/*********************************** inline *************************************/
			inline void Set(const Matrix::Math::VSVector3 A[3], VSREAL fA[3], const Matrix::Math::VSVector3& Center);
			inline void Set(const Matrix::Math::VSVector3& A0, const Matrix::Math::VSVector3& A1, const Matrix::Math::VSVector3& A2,
				VSREAL fA0, VSREAL fA1, VSREAL fA2,
				const Matrix::Math::VSVector3& Center);

			inline void GetA(Matrix::Math::VSVector3 A[3])const;
			inline void GetfA(VSREAL fA[3])const;
			inline const Matrix::Math::VSVector3& GetCenter()const;
			//���ݲ������ص�
			inline Matrix::Math::VSVector3 GetParameterPoint(VSREAL fOBBParameter[3])const;
			inline Matrix::Math::VSVector3 GetParameterPoint(VSREAL fOBBParameter0, VSREAL fOBBParameter1, VSREAL fOBBParameter2)const;


			//	/*************************************����************************************************/
			//	//���OBB����
			//	VSREAL SquaredDistance(const Matrix::Math::VSVector3& Point, VSREAL fOBBParameter[3])const;
			//	//ֱ�ߺ�OBB����
			//	VSREAL SquaredDistance(const VSLine3& Line, VSREAL fOBBParameter[3], VSREAL& fLineParameter)const;
			//	//���ߺ�OBB����
			//	VSREAL SquaredDistance(const VSRay3& Ray, VSREAL fOBBParameter[3], VSREAL& fRayParameter)const;
			//	//�߶κ�OBB����
			//	VSREAL SquaredDistance(const VSSegment3& Segment, VSREAL fOBBParameter[3], VSREAL& fSegmentParameter)const;

			//	//�����κ�OBB����
			//	VSREAL SquaredDistance(const VSTriangle3& Triangle, VSREAL OBBParameter[3],
			//		VSREAL TriangleParameter[3])const;

			//	//���κ�OBB����
			//	VSREAL SquaredDistance(const VSRectangle3& Rectangle, VSREAL OBBParameter[3],
			//		VSREAL RectangleParameter[2])const;
			//	//OBB��OBB����
			//	VSREAL SquaredDistance(const VSOBB3& OBB, VSREAL OBB1Parameter[3],
			//		VSREAL OBB2Parameter[3])const;

			//	//OBB����ľ���
			//	VSREAL Distance(const VSSphere3& Sphere, VSREAL fOBBParameter[3], Matrix::Math::VSVector3& SpherePoint)const;

			//	//OBB��ƽ�����
			//	VSREAL Distance(const VSPlane3& Plane, Matrix::Math::VSVector3& OBBPoint, Matrix::Math::VSVector3& PlanePoint)const;

			//	//����κ�OBB����
			//	VSREAL SquaredDistance(const VSPolygon3& Polygon,
			//		VSREAL OBBParameter[3], int& IndexTriangle,
			//		VSREAL TriangleParameter[3])const;
			//	/********************************RelationWith******************************************/
			//	//���OBBλ�ù�ϵ
			//	//VSIN VSOUT VSON
			//	int RelationWith(const Matrix::Math::VSVector3& Point)const;
			//	//����ֱ����OBBλ�ù�ϵ
			//	//VSNOINTERSECT VSNTERSECT
			//	int RelationWith(const VSLine3& Line, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//	//����������OBBλ�ù�ϵ
			//	//VSNOINTERSECT VSNTERSECT
			//	int RelationWith(const VSRay3& Ray, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//	//�����߶���OBBλ�ù�ϵ
			//	//VSNOINTERSECT VSNTERSECT VSIN
			//	int RelationWith(const VSSegment3& Segment, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//	//����ƽ���OBBλ�ù�ϵ
			//	//VSFRONT VSBACK VSINTERSECT
			//	int RelationWith(const VSPlane3& Plane)const;
			//	//������������OBBλ�ù�ϵ
			//	//VSNOINTERSECT VSINTERSECT VSIN
			//	int RelationWith(const VSTriangle3& Triangle)const;

			//	//���κ�OBBλ�ù�ϵ
			//	//VSNOINTERSECT VSINTERSECT VSIN
			//	int RelationWith(const VSRectangle3& Rectangle)const;

			//	//OBB��OBBλ�ù�ϵ
			//	//VSNOINTERSECT VSINTERSECT
			//	int RelationWith(const VSOBB3& OBB)const;

			//	//OBB��Բλ�ù�ϵ
			//	//VSNOINTERSECT VSINTERSECT
			//	int RelationWith(const VSSphere3& Sphere)const;
			//private:
			//	/*void OBBProj(const VSOBB3 &OBB, const Matrix::Math::VSVector3 &vcV,
			//		VSREAL *pfMin, VSREAL *pfMax)const;
			//	void TriProj(const Matrix::Math::VSVector3 &v0, const Matrix::Math::VSVector3 &v1,
			//		const Matrix::Math::VSVector3 &v2, const Matrix::Math::VSVector3 &vcV,
			//		VSREAL *pfMin, VSREAL *pfMax)const;

			//	void Face (int i0, int i1, int i2, Matrix::Math::VSVector3 Pnt,
			//				Matrix::Math::VSVector3 Dir, Matrix::Math::VSVector3 PmE,
			//				VSREAL& rfSqrDistance,VSREAL &fLParam)const;
			//	void CaseNoZeros (Matrix::Math::VSVector3& Pnt,
			//					const Matrix::Math::VSVector3& Dir, VSREAL& rfSqrDistance,VSREAL &fLParam)const;
			//	void Case0 (int i0, int i1, int i2, Matrix::Math::VSVector3& Pnt,
			//				const Matrix::Math::VSVector3& Dir, VSREAL& rfSqrDistance,VSREAL &fLParam)const;

			//	void Case00 (int i0, int i1, int i2,
			//					Matrix::Math::VSVector3& Pnt, const Matrix::Math::VSVector3& Dir,  VSREAL& rfSqrDistance,VSREAL &fLParam)const;
			//	void Case000 (Matrix::Math::VSVector3& Pnt, VSREAL& rfSqrDistance)const;*/
		};

#include "VSOBB3.inl"
	}
}