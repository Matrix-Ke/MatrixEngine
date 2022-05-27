#pragma once
#include "Function/FunctionCore.h"
#include "PriorityMacro.h"

#include "Container/Array.h"

namespace Matrix
{
	// VSPriority 类表示优先级，它维护一个表示优先级的值 m_uiPriorityNum。初始的时候这个值为
	// 0，值越大表示层次越多；非 0 值就表示优先级已经算出，不需要再算了；无任何依赖的时候值也
	//是 0。VSPriority 中的 m_pPriorityThanList 变量包含了与这个类实例有直接依赖关系的优先级列表，
	// template<class T>
	class MATRIX_FUNCTION_API VSPriority
	{
	public:
		VSPriority();
		VSPriority(unsigned int uiPriorityNum);
		~VSPriority();
		bool AddPriorityThan(VSPriority* pPriority);
		unsigned int GetPriorityNum();

		VSPriority& operator=(VSPriority& rPriority);
		bool operator==(VSPriority& rPriority);
		bool operator!=(VSPriority& rPriority);

		bool operator>(VSPriority& rPriority);
		bool operator<(VSPriority& rPriority);

		bool operator>=(VSPriority& rPriority);
		bool operator<=(VSPriority& rPriority);

	private:
		bool CheckIsCircle(const VSPriority* pChecked) const;
		unsigned int CheckPriorityNum();
		// 0既表示优先级别最大，也或者没有优先级。如果m_pPriorityThanList无成员，表示最大有限级别
		//否则需要计算优先级别
		unsigned int m_uiPriorityNum;
		Container::MArray<VSPriority*> m_pPriorityThanList;
	};

}
