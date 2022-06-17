#pragma once
#include "Core/Stream/StreamingType.h"
#include "FunctionCore.h"
#include "Platform/MemoryManager.h"
#include "Container/Array.h"
#include "Primitive/AABB3.h"

#include "Render/Texture/TexAllState.h"
#include "Node/NodeComponent/MeshComponent.h"


namespace Matrix
{
	struct MATRIX_FUNCTION_API StreamElementType
	{
		Container::MArray<VSResourceProxyBase*> pResourceProxy;
		bool bFree = true;
		bool operator==(const StreamElementType& SET)
		{
			return true;
		}
	};
	class MATRIX_FUNCTION_API VSStreamingManager : public Platform::MemoryAllcManager
	{
	public:
		VSStreamingManager();
		~VSStreamingManager();
		static VSStreamingManager* ms_pStreamingManager;
		void Update(double dAppTime);
		static void GetStreamInfo(const Primitive::AABB3& WorldAABB, StreamInformation_TYPE& StreamInformation);
		StreamElementType& GetFreeSlot();
		void ReleaseAllStream();

	protected:
		void GetStreamInfo();
		void DispathStream();
		Container::MList<StreamElementType> m_StreamObjectList;
	};
}
