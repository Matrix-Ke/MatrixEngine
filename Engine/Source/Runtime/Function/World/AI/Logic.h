#pragma once
#include "MemManager.h"
#include "Name.h"

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
		VSUsedName Sender;
		VSUsedName Receiver;
		unsigned int MessageType;
		double DispatchTime;
		void* pData;
		unsigned int uiDataSize;
	};
}
