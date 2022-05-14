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
			Matrix::Math::Vector3 m_A[3];   // 3个轴
			Matrix::Math::Vector3 m_Center; // 中心点
			VSREAL m_fA[3];                   // 3个半轴的长度
		public:
			OBB3();
			~OBB3();
			//构造AABB
			OBB3(const Matrix::Math::Vector3 A[3], VSREAL fA[3], const Matrix::Math::Vector3& Center);
			OBB3(const Matrix::Math::Vector3& A0, const Matrix::Math::Vector3& A1, const Matrix::Math::Vector3& A2,
				VSREAL fA0, VSREAL fA1, VSREAL fA2,
				const Matrix::Math::Vector3& Center);
			//通过点集合构造AABB
			void CreateOBB(const Matrix::Math::Vector3* const pPointArray, unsigned int uiPointNum);
			//合并AABB
			OBB3 MergeOBB(const OBB3& OBB) const;
			//取得6个平面
			void GetPlane(Plane3 pPlanes[6]) const;
			//取得8个点
			void GetPoint(Matrix::Math::Vector3 Point[8]) const;
			//取得6个矩形
			void GetRectangle(Rectangle3 Rectangle[6]) const;
			//获得变换到OBB下变换矩阵，物体必须和OBB在同一个坐标系下
			void GetTransform(Matrix::Math::Matrix4& m) const;
			//得到点参数
			bool GetParameter(const Matrix::Math::Vector3& Point, VSREAL fOBBParameter[3]) const;
			//用给定的OBB和变换矩阵来构造OBB
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
			//根据参数返回点
			inline Matrix::Math::Vector3 GetParameterPoint(VSREAL fOBBParameter[3]) const;
			inline Matrix::Math::Vector3 GetParameterPoint(VSREAL fOBBParameter0, VSREAL fOBBParameter1, VSREAL fOBBParameter2) const;

			//	/*************************************距离************************************************/
			//	//点和OBB距离
			//	VSREAL SquaredDistance(const Matrix::Math::Vector3& Point, VSREAL fOBBParameter[3])const;
			//	//直线和OBB距离
			//	VSREAL SquaredDistance(const Line3& Line, VSREAL fOBBParameter[3], VSREAL& fLineParameter)const;
			//	//射线和OBB距离
			//	VSREAL SquaredDistance(const Ray3& Ray, VSREAL fOBBParameter[3], VSREAL& fRayParameter)const;
			//	//线段和OBB距离
			//	VSREAL SquaredDistance(const Segment3& Segment, VSREAL fOBBParameter[3], VSREAL& fSegmentParameter)const;

			//	//三角形和OBB距离
			//	VSREAL SquaredDistance(const Triangle3& Triangle, VSREAL OBBParameter[3],
			//		VSREAL TriangleParameter[3])const;

			//	//矩形和OBB距离
			//	VSREAL SquaredDistance(const Rectangle3& Rectangle, VSREAL OBBParameter[3],
			//		VSREAL RectangleParameter[2])const;
			//	//OBB和OBB距离
			//	VSREAL SquaredDistance(const OBB3& OBB, VSREAL OBB1Parameter[3],
			//		VSREAL OBB2Parameter[3])const;

			//	//OBB和球的距离
			//	VSREAL Distance(const Sphere3& Sphere, VSREAL fOBBParameter[3], Matrix::Math::Vector3& SpherePoint)const;

			//	//OBB和平面距离
			//	VSREAL Distance(const Plane3& Plane, Matrix::Math::Vector3& OBBPoint, Matrix::Math::Vector3& PlanePoint)const;

			//	//多边形和OBB距离
			//	VSREAL SquaredDistance(const Polygon3& Polygon,
			//		VSREAL OBBParameter[3], int& IndexTriangle,
			//		VSREAL TriangleParameter[3])const;
			//	/********************************RelationWith******************************************/
			//	//点和OBB位置关系
			//	//VSIN VSOUT VSON
			//	int RelationWith(const Matrix::Math::Vector3& Point)const;
			//	//测试直线与OBB位置关系
			//	//VSNOINTERSECT VSNTERSECT
			//	int RelationWith(const Line3& Line, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//	//测试射线与OBB位置关系
			//	//VSNOINTERSECT VSNTERSECT
			//	int RelationWith(const Ray3& Ray, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//	//测试线段与OBB位置关系
			//	//VSNOINTERSECT VSNTERSECT VSIN
			//	int RelationWith(const Segment3& Segment, unsigned int& Quantity, VSREAL& tNear, VSREAL& tFar)const;
			//	//测试平面和OBB位置关系
			//	//VSFRONT VSBACK VSINTERSECT
			//	int RelationWith(const Plane3& Plane)const;
			//	//测试三角形与OBB位置关系
			//	//VSNOINTERSECT VSINTERSECT VSIN
			//	int RelationWith(const Triangle3& Triangle)const;

			//	//矩形和OBB位置关系
			//	//VSNOINTERSECT VSINTERSECT VSIN
			//	int RelationWith(const Rectangle3& Rectangle)const;

			//	//OBB和OBB位置关系
			//	//VSNOINTERSECT VSINTERSECT
			//	int RelationWith(const OBB3& OBB)const;

			//	//OBB和圆位置关系
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