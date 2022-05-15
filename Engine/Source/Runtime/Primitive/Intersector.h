#pragma once
#include "Line3.h"
#include "Plane3.h"
#include "Triangle3.h"
#include "Triangle3.h"
#include "Sphere3.h"
#include "OBB3.h"
#include "AABB3.h"
#include "Polygon3.h"

namespace Matrix
{
	namespace Primitive
	{
		//设计基类预留设计
		template<typename primitive1, typename pritive2>
		class Intersector
		{
		public:

		};

		template<typename T2>
		class Intersector<Line3, T2>
		{
		public:
			int RelationWith(const Triangle3& Triangle, bool bCull, VSREAL& fLineParameter, VSREAL fTriangleParameter[3]) const
			{
			}
			/*----------------------------------------------------------------*/
		};









	}
}
