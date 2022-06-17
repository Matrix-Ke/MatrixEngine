#pragma once
#include "Node/Node.h"

namespace Matrix
{
	class VSSocketNode;

	/*
	* VSNodeComponent 类主要管理插槽（socket），其他的和普通 VSNode 没什么区别，只不过作为一个过渡基类，
	一般情况下所有实体功能类都要从 VSNodeComponent 继承
	*/
	class MATRIX_FUNCTION_API VSNodeComponent : public VSNode
	{
		// PRIORITY

		// RTTI
		DECLARE_RTTI;
		DECLARE_INITIAL
	public:
		VSNodeComponent();
		virtual ~VSNodeComponent();

		friend class VSSocketNode;

		virtual bool IsNeedDraw()
		{
			return false;
		}
		template <typename T>
		static T* CreateComponent();
		virtual void PostCreate() {};
		virtual void OnDestroy();
		void AttachParentSocket(const VSUsedName& AttackSocketName);
		virtual bool PostLoad(MStream* pStream);
		virtual bool PostClone(MObject* pObjectSrc);
		virtual void UpdateTransform(double dAppTime);
		virtual void UpdateLightState(double dAppTime);
		virtual void UpdateCameraState(double dAppTime);
		virtual void GetStreamResource(Container::MArray<VSResourceProxyBase*>& pResourceProxy, StreamInformation_TYPE& StreamInformation) const;

	protected:
		virtual void UpdateNodeAll(double dAppTime);
		VSUsedName m_AttachSocketName;
		VSSocketNode* m_pAttachSocket;
	};
	DECLARE_Ptr(VSNodeComponent);
	VSTYPE_MARCO(VSNodeComponent);

	template <typename T>
	T* VSNodeComponent::CreateComponent()
	{

		if (T::ms_Type.IsDerived(VSNodeComponent::ms_Type))
		{
			T* Component = (T*)MObject::GetInstance<T>();
			Component->PostCreate();
			return Component;
		}
		else
		{
			return NULL;
		}
	}
}
