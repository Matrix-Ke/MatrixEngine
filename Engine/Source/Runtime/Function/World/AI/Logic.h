#pragma once
#include "Platform/MemoryManager.h"
#include "Core/Meta/ObjName.h"

//��Ϣ����: ʵ�� A Ҫ��ĳ����Ϣ���͸�ʵ�� B��ʵ�� A ����Ϣ���͵�һ���м�վ��Ȼ���м�վ����ʵ�� B���ٷ��͸�ʵ�� B������м�վ�������磬����֪������ʵ��

namespace Matrix
{
	struct VSLOGIC_INPUT_EVENT
	{
		unsigned int uiInputType;
		unsigned int uiEvent;
		unsigned int uiKey;
		int x;
		int y;
		int z;
	};

	struct VSMessage
	{
		VSMessage()
		{
		}
		~VSMessage()
		{
		}
		VSUsedName Sender;//������ʵ�������
		VSUsedName Receiver;//������ʵ�������
		unsigned int MessageType;//��Ϣ����
		double DispatchTime;//�ɷ���ʱ��
		void* pData; //����
		unsigned int uiDataSize;
	};
}
