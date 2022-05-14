#pragma once
#include "Math/Vector3.h"
#include "Plane3.h"
#include "Triangle3.h"
#include "AABB3.h"

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
		class Math::Matrix3;
		class Line3;
		class Ray3;
		class Rectangle3;
		class Segment3;
		class MATRIX_PRIMITIVE_API OBB3
		{
		private:
			Matrix::Math::Vector3 m_A[3];   // 3����
			Matrix::Math::Vector3 m_Center; // ���ĵ�
			VSREAL m_fA[3];                   // 3������ĳ���
		public:
			OBB3();
			~OBB3();
			//����AABB
			OBB3(const Matrix::Math::Vector3 A[3], VSREAL fA[3], const Matrix::Math::Vector3& Center);
			OBB3(const Matrix::Math::Vector3& A0, const Matrix::Math::Vector3& A1, const Matrix::Math::Vector3& A2,
				VSREAL fA0, VSREAL fA1, VSREAL fA2,
				const Matrix::Math::Vector3& Center);
			//ͨ���㼯�Ϲ���AABB
			void CreateOBB(const Matrix::Math::Vector3* const pPointArray, unsigned int uiPointNum);
			//�ϲ�AABB
			OBB3 MergeOBB(const OBB3& OBB) const;
			//ȡ��6��ƽ��
			void GetPlane(Plane3 pPlanes[6]) const;
			//ȡ��8����
			void GetPoint(Matrix::Math::Vector3 Point[8]) const;
			//ȡ��6������
			void GetRectangle(Rectangle3 Rectangle[6]) const;
			//��ñ任��OBB�±任������������OBB��ͬһ������ϵ��
			void GetTransform(Matrix::Math::Matrix4& m) const;
			//�õ������
			bool GetParameter(const Matrix::Math::Vector3& Point, VSREAL fOBBParameter[3]) const;
			//�ø�����OBB�ͱ任����������OBB
			void Transform(const OBB3& OBB, const Matrix::Math::Matrix4& Mat);
			AABB3 GetAABB() const;
			/*********************************** inline *************************************/
			inline void Set(const Matrix::Math::Vector3 A[3], VSREAL fA[3], const Matrix::Math::Vector3& Center);
			inline void Set(const Matrix::Math::Vector3& A0, const Matrix::Math::Vector3& A1, const Matrix::Math::Vector3& A2,
				VSREAL fA0, VSREAL fA1, VSREAL fA2,
				const Matrix::Math::Vector3& Center);

			inline void GetA(Matrix::Math::Vector3 A[3]) const;
			inline void GetfA(VSREAL fA[3]) const;
			inline const Matrix::Math::Vector3& GetCenter() const;
			//���ݲ������ص�
			inline Matrix::Math::Vector3 GetParameterPoint(VSREAL fOBBParameter[3]) const;
			inline Matrix::Math::Vector3 GetParameterPoint(VSREAL fOBBParameter0, VSREAL fOBBParameter1, VSREAL fOBBParameter2) const;

			//	/*************************************����************************************************/
			//	//���OBB����
			//	VSREAL SquaredDistance(const Matrix::Math::Vector3& Point, VSREAL fOBBParameter[3])const;
			//	//ֱ�ߺ�OBB����
			//	VSREAL SquaredDistance(const Line3& Line, VSREAL fOBBParameter[3], VSREAL& fLineParameter)const;
			//	//���ߺ�OBB����
			//	VSREAL SquaredDistance(const Ray3& Ray, VSREAL fOBBParameter[3], VSREAL& fRayParameter)const;
			//	//�߶κ�OBB����
			//	VSREAL SquaredDistance(const Segment3& Segment, VSREAL fOBBParameter[3], VSREAL& fSegmentParameter)const;

			//	//�����κ�OBB����
			//	VSREAL SquaredDistance(const Triangle3& Triangle, VSREAL OBBParameter[3],
			//		VSREAL TriangleParameter[3])const;

			//	//���κ�OBB����
			//	VSREAL SquaredDistance(const Rectangle3& Rectangle, VSREAL OBBParameter[3],
			//		VSREAL RectangleParameter[2])const;
			//	//OBB��OBB����
			//	VSREAL SquaredDistance(const OBB3& OBB, VSREAL OBB1Parameter[3],
			//		VSREAL OBB2Parameter[3])const;

			//	//OBB����ľ���
			//	VSREAL Distance(const Sphere3& Sphere, VSREAL fOBBParameter[3], Matrix::Math::Vector3& SpherePoint)const;

			//	//OBB��ƽ�����
			//	VSREAL Distance(const Plane3& Plane, Matrix::Math::Vector3& OBBPoint, Matrix::Math::Vector3& PlanePoint)const;

			//	//����κ�OBB����
			//	VSREAL SquaredDistance(const Polygon3& Polygon,
			//		VSREAL OBBParameter[3], int& IndexTriangle,
			//		VSREAL TriangleParameter[3])const;
			//	/********************************RelationWith******************************************/
			//	//���OBBλ�ù�ϵ
			//	//VSIN VSOUT VSON
			//	int RelationWith(const Matrix::Math::Vector3& Point)const;
			//	//����ֱ����OBBλ�ù�ϵ
			//	//VSNOINTERSECT VSNTERSECT
			//	int RelationWith(const Line3& Line, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//	//����������OBBλ�ù�ϵ
			//	//VSNOINTERSECT VSNTERSECT
			//	int RelationWith(const Ray3& Ray, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//	//�����߶���OBBλ�ù�ϵ
			//	//VSNOINTERSECT VSNTERSECT VSIN
			//	int RelationWith(const Segment3& Segment, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//	//����ƽ���OBBλ�ù�ϵ
			//	//VSFRONT VSBACK VSINTERSECT
			//	int RelationWith(const Plane3& Plane)const;
			//	//������������OBBλ�ù�ϵ
			//	//VSNOINTERSECT VSINTERSECT VSIN
			//	int RelationWith(const Triangle3& Triangle)const;

			//	//���κ�OBBλ�ù�ϵ
			//	//VSNOINTERSECT VSINTERSECT VSIN
			//	int RelationWith(const Rectangle3& Rectangle)const;

			//	//OBB��OBBλ�ù�ϵ
			//	//VSNOINTERSECT VSINTERSECT
			//	int RelationWith(const OBB3& OBB)const;

			//	//OBB��Բλ�ù�ϵ
			//	//VSNOINTERSECT VSINTERSECT
			//	int RelationWith(const Sphere3& Sphere)const;
			// private:
			//	/*void OBBProj(const OBB3 &OBB, const Matrix::Math::Vector3 &vcV,
			//		VSREAL *pfMin, VSREAL *pfMax)const;
			//	void TriProj(const Matrix::Math::Vector3 &v0, const Matrix::Math::Vector3 &v1,
			//		const Matrix::Math::Vector3 &v2, const Matrix::Math::Vector3 &vcV,
			//		VSREAL *pfMin, VSREAL *pfMax)const;

			//	void Face (int i0, int i1, int i2, Matrix::Math::Vector3 Pnt,
			//				Matrix::Math::Vector3 Dir, Matrix::Math::Vector3 PmE,
			//				VSREAL& rfSqrDistance,VSREAL &fLParam)const;
			//	void CaseNoZeros (Matrix::Math::Vector3& Pnt,
			//					const Matrix::Math::Vector3& Dir, VSREAL& rfSqrDistance,VSREAL &fLParam)const;
			//	void Case0 (int i0, int i1, int i2, Matrix::Math::Vector3& Pnt,
			//				const Matrix::Math::Vector3& Dir, VSREAL& rfSqrDistance,VSREAL &fLParam)const;

			//	void Case00 (int i0, int i1, int i2,
			//					Matrix::Math::Vector3& Pnt, const Matrix::Math::Vector3& Dir,  VSREAL& rfSqrDistance,VSREAL &fLParam)const;
			//	void Case000 (Matrix::Math::Vector3& Pnt, VSREAL& rfSqrDistance)const;*/
		};

#include "OBB3.inl"
	}
}