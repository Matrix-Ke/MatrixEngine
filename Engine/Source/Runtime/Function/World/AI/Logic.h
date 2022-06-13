#pragma once
#include "Platform/MemoryManager.h"
#include "Core/Meta/ObjName.h"

//消息机制: 实体 A 要把某种消息发送给实体 B，实体 A 把消息发送到一个中继站，然后中继站查找实体 B，再发送给实体 B。这个中继站就是世界，世界知道所有实体

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
		VSUsedName Sender;//发送者实体的名字
		VSUsedName Receiver;//接收者实体的名字
		unsigned int MessageType;//消息类型
		double DispatchTime;//派发的时间
		void* pData; //数据
		unsigned int uiDataSize;
	};
}
