#pragma once
#include "VSSwitchNode.h"
namespace Matrix
{
	class VSStream;
	class MATRIX_FUNCTION_API VSDLodTerrainSwitchNode : public VSSwitchNode
	{
		//PRIORITY
		
		//RTTI
		DECLARE_RTTI;
		DECLARE_INITIAL
	public:
		VSDLodTerrainSwitchNode(unsigned int uiIndexXInTerrain,unsigned int uiIndexZInTerrain);
		virtual ~VSDLodTerrainSwitchNode();

	public:

		virtual void UpdateView(VSCuller & Culler,double dAppTime);
		
	
	protected:
		VSDLodTerrainSwitchNode();
		unsigned int m_uiIndexXInTerrain;
		unsigned int m_uiIndexZInTerrain;
	};
	DECLARE_Ptr(VSDLodTerrainSwitchNode);
	VSTYPE_MARCO(VSDLodTerrainSwitchNode);
}
