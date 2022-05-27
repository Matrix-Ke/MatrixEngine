#pragma once
#include "Function/FunctionCore.h"
#include "PriorityMacro.h"

#include "Container/Array.h"

namespace Matrix
{
	// VSPriority ���ʾ���ȼ�����ά��һ����ʾ���ȼ���ֵ m_uiPriorityNum����ʼ��ʱ�����ֵΪ
	// 0��ֵԽ���ʾ���Խ�ࣻ�� 0 ֵ�ͱ�ʾ���ȼ��Ѿ����������Ҫ�����ˣ����κ�������ʱ��ֵҲ
	//�� 0��VSPriority �е� m_pPriorityThanList �����������������ʵ����ֱ��������ϵ�����ȼ��б�
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
		// 0�ȱ�ʾ���ȼ������Ҳ����û�����ȼ������m_pPriorityThanList�޳�Ա����ʾ������޼���
		//������Ҫ�������ȼ���
		unsigned int m_uiPriorityNum;
		Container::MArray<VSPriority*> m_pPriorityThanList;
	};

}
