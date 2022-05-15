#pragma once
#include "Plane3.h"
#include "Rectangle3.h"
#include "Math/CMathInterface.h"

/*
AABB��ԳƱ߽�У�3��������A1,A2,A3��Զƽ���ڵ�ǰ���������ᣬ������Ϊ��λ�����ᣬfA1,fA2,fA3Ϊ���᳤�ȣ������ڲ��ĵ㶼���Ա�ʾ��
a * A1 + b * A2 + c * A3 a,b,cΪ����������|a|<=fA1,|b|<=fA2,|c|<=fA3
*/
namespace Matrix
{
	namespace Primitive
	{
		class MATRIX_PRIMITIVE_API AABB3
		{
		private:
			static const Matrix::Math::Vector3 m_A[3]; // 3����
			Matrix::Math::Vector3 m_Center;            // ���ĵ�
			VSREAL m_fA[3];                              // 3������ĳ���
			Matrix::Math::Vector3 m_Max;               //����
			Matrix::Math::Vector3 m_Min;               //��С��
		public:
			AABB3();
			~AABB3();

			//ͨ���������С�㹹��AABB
			AABB3(const Matrix::Math::Vector3& Max, const Matrix::Math::Vector3& Min);
			//ͨ�����ĵ��3����İ볤�ȹ���AABB
			AABB3(const Matrix::Math::Vector3& Center, VSREAL fA0, VSREAL fA1, VSREAL fA2);
			AABB3(const Matrix::Math::Vector3& Center, VSREAL fA[3]);
			//ͨ���㼯�Ϲ���AABB
			void CreateAABB(const Matrix::Math::Vector3* const pPointArray, unsigned int uiPointNum);
			/*********************************** inline *************************************/
			//������Ӧ�Ĳ���
			inline void Set(const Matrix::Math::Vector3& Max, const Matrix::Math::Vector3& Min);
			inline void Set(const Matrix::Math::Vector3& Center, VSREAL fA0, VSREAL fA1, VSREAL fA2);
			inline void Set(const Matrix::Math::Vector3& Center, VSREAL fA[3]);
			//��ȡ��Ӧ�Ĳ���
			inline void GetfA(VSREAL fA[3]) const;
			inline const Matrix::Math::Vector3& GetCenter() const;
			inline Matrix::Math::Vector3 GetParameterPoint(VSREAL fAABBParameter[3]) const;
			inline Matrix::Math::Vector3 GetParameterPoint(VSREAL fAABBParameter0, VSREAL fAABBParameter1, VSREAL fAABBParameter2) const;
			inline const Matrix::Math::Vector3& GetMaxPoint() const;
			inline const Matrix::Math::Vector3& GetMinPoint() const;
			//�õ�AABB6��ƽ��
			void GetPlane(Plane3 pPlanes[6]) const;
			//�õ�AABB8����
			void GetPoint(Matrix::Math::Vector3 Point[8]) const;
			//�õ�AABB6������
			void GetRectangle(Rectangle3 Rectangle[6]) const;
			//����AABB��һ�㷵��AABB�Ĳ���
			bool GetParameter(const Matrix::Math::Vector3& Point, VSREAL fAABBParameter[3]) const;
			//�þ���任AABB
			void Transform(const AABB3& AABB,
				const Matrix::Math::Matrix4& m, bool bHasProject = false);
			//�ϲ�2��AABB
			AABB3 MergeAABB(const AABB3& AABB) const;
			void GetQuadAABB(AABB3 AABB[4]) const;
			void GetOctAABB(AABB3 AABB[8]) const;
			AABB3 GetMin(const AABB3& AABB) const;

			bool GetIntersect(AABB3& AABB, AABB3& OutAABB) const;

			/*************************************����************************************************/
			//���AABB����
			VSREAL SquaredDistance(const Matrix::Math::Vector3& Point, VSREAL fAABBParameter[3])const;
			//ֱ�ߺ�AABB����
			VSREAL SquaredDistance(const Line3& Line, VSREAL fAABBParameter[3], VSREAL& fLineParameter)const;
			//���ߺ�AABB����
			VSREAL SquaredDistance(const Ray3& Ray, VSREAL fAABBParameter[3], VSREAL& fRayParameter)const;
			//�߶κ�AABB����
			VSREAL SquaredDistance(const Segment3& Segment, VSREAL fAABBParameter[3], VSREAL& fSegmentParameter)const;

			//�����κ�AABB����
			VSREAL SquaredDistance(const Triangle3& Triangle, VSREAL AABBParameter[3],
				VSREAL TriangleParameter[3])const;

			//���κ�AABB����
			VSREAL SquaredDistance(const Rectangle3& Rectangle, VSREAL AABBParameter[3],
				VSREAL RectangleParameter[2])const;
			//AABB��AABB����
			VSREAL SquaredDistance(const AABB3& AABB, VSREAL AABB1Parameter[3],
				VSREAL AABB2Parameter[3])const;
			//AABB����ľ���
			VSREAL Distance(const Sphere3& Sphere, VSREAL fAABBParameter[3], Matrix::Math::Vector3& SpherePoint)const;

			//AABB��ƽ�����
			VSREAL Distance(const Plane3& Plane, Matrix::Math::Vector3& AABBPoint, Matrix::Math::Vector3& PlanePoint)const;

			//����κ�AABB����
			VSREAL SquaredDistance(const Polygon3& Polygon, VSREAL AABBParameter[3], int& IndexTriangle,
				VSREAL TriangleParameter[3])const;
			/********************************RelationWith******************************************/
			//���AABBλ�ù�ϵ
			//IT_In IT_Out IT_On
			int RelationWith(const Matrix::Math::Vector3& Point)const;
			//����ֱ����AABBλ�ù�ϵ
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const Line3& Line, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//����������AABBλ�ù�ϵ
			//IT_NoIntersect VSNTERSECT
			int RelationWith(const Ray3& Ray, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//�����߶���AABBλ�ù�ϵ
			//IT_NoIntersect VSNTERSECT IT_In
			int RelationWith(const Segment3& Segment, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//����ƽ���AABBλ�ù�ϵ
			//IT_Front IT_Back IT_Intersect
			int RelationWith(const Plane3& Plane)const;
			//�����κ�AABBλ�ù�ϵ
			//IT_NoIntersect IT_Intersect IT_In
			int RelationWith(const Triangle3& Triangle)const;
			//���κ�AABBλ�ù�ϵ
			//IT_NoIntersect IT_Intersect IT_In
			int RelationWith(const Rectangle3& Rectangle)const;

			//AABB��AABBλ�ù�ϵ
			//IT_NoIntersect IT_Intersect
			int RelationWith(const AABB3& AABB)const;

			//AABB��Բλ�ù�ϵ
			//IT_NoIntersect IT_Intersect
			int RelationWith(const Sphere3& Sphere)const;
		};

#include "AABB3.inl"
	}
};
