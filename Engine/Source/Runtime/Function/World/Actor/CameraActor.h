#pragma once
#include "VSActor.h"
#include "VSCamera.h"
#include "VSPostEffectSet.h"
namespace Matrix
{
	class VSViewFamily;
	class MATRIX_FUNCTION_API VSViewFamliyInfo : public VSObject
	{
		//RTTI
		DECLARE_RTTI;
	public:
		DECLARE_INITIAL
		VSViewFamliyInfo();
		~VSViewFamliyInfo();
		VSArray<VSString> m_SceneMapName;
		unsigned int m_uiWidth;
		unsigned int m_uiHeight;
		unsigned int m_uiCaptureViewFamilyType;
		VSString	m_ViewFamilyName;
		VSPostEffectSetRPtr m_pPostEffect;
		VSViewFamily * m_pViewFamily;
		VSString	m_RenderMethodRTTIName;
		void GetScene();
	};
	DECLARE_Ptr(VSViewFamliyInfo);
	VSTYPE_MARCO(VSViewFamliyInfo);
	class  MATRIX_FUNCTION_API VSCameraActor : public VSActor
	{
		//PRIORITY

		//RTTI
		DECLARE_RTTI;
	public:
		VSCameraActor();
		virtual ~VSCameraActor();
		DECLARE_INITIAL

		VSArray<VSViewFamliyInfoPtr> m_ViewFamliyInfoArray;
		GET_TYPE_NODE(VSCamera)
		virtual void Update(double dAppTime);
		virtual void CreateDefaultComponentNode();
		void AddCustomCullPlane(const VSPlane3& P);
		void ClearCustomCullPlane();
	};
	DECLARE_Ptr(VSCameraActor);
	VSTYPE_MARCO(VSCameraActor);
}
