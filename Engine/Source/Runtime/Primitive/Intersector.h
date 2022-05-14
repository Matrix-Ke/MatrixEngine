#pragma once

namespace Matirx
{
	namespace Primitive
	{
		class Intersector
		{
		public:
			//判断两个物体的位置关系的，通过其英文名称都可以判断出它们的具体含义
#define VSFRONT 0
#define VSBACK 1
#define VSON 2
#define VSCLIPPED 3
#define VSCULLED 4
#define VSVISIBLE 5
#define VSINTERSECT 3
#define VSOUT 4
#define VSIN 5
#define VSNOINTERSECT 6
//
		};
	}
}
