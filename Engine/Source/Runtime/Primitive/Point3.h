#include "Math/Vector3.h"

namespace Matrix
{
	class Matrix3;
	class Quat;
	class Ray3;
	class Line3;
	class Plane3;
	class Ray3;
	class Segment3;
	class Triangle3;
	class Rectangle3;
	class OBB3;
	class Sphere3;
	class AABB3;
	class Matrix4;
	class Polygon3;

	namespace Primitive
	{
		class Point3 : public  Math::Vector3
		{
		public:
			/********************************����******************************************/
			//��͵����
			VSREAL SquaredDistance(const Vector3& Point) const;
			//�㵽ֱ�߾���
			VSREAL SquaredDistance(const Line3& Line, VSREAL& fLineParameter)const;
			//������߾���
			VSREAL SquaredDistance(const Ray3& Ray, VSREAL& fRayParameter)const;
			//����߶ξ���
			VSREAL SquaredDistance(const Segment3& Segment, VSREAL& fSegmentParameter)const;
			//��������ξ���
			VSREAL SquaredDistance(const Triangle3& Triangle, VSREAL fTriangleParameter[3])const;
			//��;��ξ���
			VSREAL SquaredDistance(const Rectangle3& Rectangle, VSREAL fRectangleParameter[2])const;
			//���OBB����
			VSREAL SquaredDistance(const OBB3& OBB, VSREAL fOBBParameter[3])const;
			//�����ľ���
			VSREAL Distance(const Sphere3& Sphere, Vector3& SpherePoint)const;
			//���ƽ�����
			VSREAL Distance(const Plane3& Plane, Vector3& PlanePoint)const;
			//���AABB����
			VSREAL SquaredDistance(const AABB3& AABB, VSREAL fAABBParameter[3])const;
			//��Ͷ���ξ���
			VSREAL SquaredDistance(const Polygon3& Polygon, int& IndexTriangle, VSREAL fTriangleParameter[3])const;
			/********************************RelationWith******************************************/
			//�����λ�ù�ϵ
			//IT_In IT_Out IT_On
			int RelationWith(const Sphere3& Sphere)const;
			//���ƽ��λ�ù�ϵ
			//IT_Front IT_Back IT_On
			int RelationWith(const Plane3& Plane)const;
			//���OBBλ�ù�ϵ
			//IT_In IT_Out IT_On
			int RelationWith(const OBB3& OBB)const;
			//���AABBλ�ù�ϵ
			//IT_In IT_Out IT_On
			int RelationWith(const AABB3& AABB)const;
		};
	}
}