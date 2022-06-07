//#pragma once
//#include "Function/FunctionCore.h"
//#include "Core/MemoryManager.h"
////#include "TexAllState.h"
////#include "MeshComponent.h"
//
//#include "EngineMath.h"
// namespace Matrix
//{
//	struct MATRIX_FUNCTION_API StreamElementType
//	{
//		Container::MArray<VSResourceProxyBase*> pResourceProxy;
//		bool bFree = true;
//		bool operator==(const StreamElementType& SET)
//		{
//			return true;
//		}
//	};
//	class MATRIX_FUNCTION_API VSStreamingManager : public Core::MemoryObject
//	{
//	public:
//		VSStreamingManager();
//		~VSStreamingManager();
//		static VSStreamingManager* ms_pStreamingManager;
//		void Update(double dAppTime);
//		static void GetStreamInfo(const VSAABB3& WorldAABB, StreamInformation_TYPE& StreamInformation);
//		StreamElementType& GetFreeSlot();
//		void ReleaseAllStream();
//
//	protected:
//		void GetStreamInfo();
//		void DispathStream();
//		VSList<StreamElementType> m_StreamObjectList;
//	};
//}
