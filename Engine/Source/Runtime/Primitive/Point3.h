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
			/********************************距离******************************************/
			//点和点距离
			VSREAL SquaredDistance(const Vector3& Point) const;
			//点到直线距离
			VSREAL SquaredDistance(const Line3& Line, VSREAL& fLineParameter)const;
			//点和射线距离
			VSREAL SquaredDistance(const Ray3& Ray, VSREAL& fRayParameter)const;
			//点和线段距离
			VSREAL SquaredDistance(const Segment3& Segment, VSREAL& fSegmentParameter)const;
			//点和三角形距离
			VSREAL SquaredDistance(const Triangle3& Triangle, VSREAL fTriangleParameter[3])const;
			//点和矩形距离
			VSREAL SquaredDistance(const Rectangle3& Rectangle, VSREAL fRectangleParameter[2])const;
			//点和OBB距离
			VSREAL SquaredDistance(const OBB3& OBB, VSREAL fOBBParameter[3])const;
			//点和球的距离
			VSREAL Distance(const Sphere3& Sphere, Vector3& SpherePoint)const;
			//点和平面距离
			VSREAL Distance(const Plane3& Plane, Vector3& PlanePoint)const;
			//点和AABB距离
			VSREAL SquaredDistance(const AABB3& AABB, VSREAL fAABBParameter[3])const;
			//点和多边形距离
			VSREAL SquaredDistance(const Polygon3& Polygon, int& IndexTriangle, VSREAL fTriangleParameter[3])const;
			/********************************RelationWith******************************************/
			//点和球位置关系
			//IT_In IT_Out IT_On
			int RelationWith(const Sphere3& Sphere)const;
			//点和平面位置关系
			//IT_Front IT_Back IT_On
			int RelationWith(const Plane3& Plane)const;
			//点和OBB位置关系
			//IT_In IT_Out IT_On
			int RelationWith(const OBB3& OBB)const;
			//点和AABB位置关系
			//IT_In IT_Out IT_On
			int RelationWith(const AABB3& AABB)const;
		};
	}
}