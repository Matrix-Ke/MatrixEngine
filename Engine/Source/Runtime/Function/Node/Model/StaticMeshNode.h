#pragma once
#include "Node/Model/ModelMeshNode.h"


namespace Matrix
{
	DECLARE_Proxy(VSStaticMeshNode);
	/*
	* VSStaticMeshNode 最后要放到 VStaticMeshComponent 里面才可以使用
	*/
	class MATRIX_FUNCTION_API VSStaticMeshNode : public VSModelMeshNode, public VSResource
	{
		// PRIORITY

		// RTTI
		DECLARE_RTTI;
		DECLARE_INITIAL
	public:
		VSStaticMeshNode();
		virtual ~VSStaticMeshNode();
		static bool InitialDefaultState();
		static bool TerminalDefaultState();
		/*
		AddLodMesh这个函数一般是要加上宏信息的，表示只在编辑器版本中才可以使用，非编辑器版本中是不应该使用的
		*/
		void AddLodMesh(VSStaticMeshNodeR* pStaticMeshResource);

		DECLARE_RESOURCE(VSStaticMeshNode, RA_ASYN_LOAD | RA_ENABLE_GC, RT_STATIC_MODEL, STMODEL, Resource / StaticMesh, VSCacheResource)
	};
	DECLARE_Ptr(VSStaticMeshNode);
	VSTYPE_MARCO(VSStaticMeshNode);
	DECLARE_Proxy(VSStaticMeshNode);
}
