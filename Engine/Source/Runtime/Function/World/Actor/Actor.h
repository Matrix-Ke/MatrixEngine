#pragma once
#include "Core/Object.h"
#include "World/AI/Logic.h"

#include "Node/Node.h"
#include "Node/NodeComponent/NodeComponent.h"

#include "Math/Vector3.h"
#include "Math/Quat.h"
#include "Math/Transform.h"


#define GET_TYPE_NODE(nodeclass)   \
    friend class nodeclass;        \
    nodeclass *GetTypeNode() const \
    {                              \
        VSNode *pNode = m_pNode;   \
        return (nodeclass *)pNode; \
    }


namespace Matrix
{
	DECLARE_Ptr(VSFSM);
	DECLARE_Ptr(VSSteer);
	class VSSceneMap;

	class MATRIX_FUNCTION_API VSActor : public MObject, public VSResource
	{
		// RTTI
		DECLARE_RTTI;

	public:
		VSActor();
		virtual ~VSActor();

		DECLARE_INITIAL
	public:
		virtual void SetWorldPos(const Math::Vector3& Pos);
		virtual void SetWorldScale(const Math::Vector3& Scale);
		virtual void SetWorldRotate(const Math::Matrix3& Rotate);
		virtual void SetWorldTransform(const Math::VSTransform& WorldTransform);
		virtual void SetLocalPos(const Math::Vector3& Pos);
		virtual void SetLocalScale(const Math::Vector3& Scale);
		virtual void SetLocalRotate(const Math::Matrix3& Rotate);
		virtual void SetLocalTransform(const Math::VSTransform& LocalTransform);

		const Math::Vector3& GetWorldPos();
		const Math::Vector3& GetWorldScale();
		const Math::Matrix3& GetWorldRotate();
		const Math::VSTransform& GetWorldTransform();

		const Math::Vector3& GetLocalPos();
		const Math::Vector3& GetLocalScale();
		const Math::Matrix3& GetLocalRotate();
		const Math::VSTransform& GetLocalTransform();

		virtual void ProcessInput(unsigned int uiInputType, unsigned int uiEvent, unsigned int uiKey, int x, int y, int z);

		virtual bool HandleMessage(VSMessage& Message);

		VSNode* GetActorNode() const
		{
			return m_pNode;
		}

		Math::Vector3 GetVelocity() const
		{
			return m_Velocity;
		}
		VSREAL GetMaxVelocity() const
		{
			return m_fMaxVelocity;
		}
		VSREAL GetMaxDriverForce() const
		{
			return m_fMaxDriverForce;
		}

		virtual void Update(double dAppTime);
		virtual bool PostClone(MObject* pObjectSrc);
		friend class VSWorld;
		friend class VSSceneMap;

	protected:
		Math::Vector3 m_Velocity;
		VSREAL m_fMaxVelocity;
		VSREAL m_fMaxDriverForce;

		VSNodePtr m_pNode; //每个实体只有一个父组件——m_pNode，其他的组件都是 m_pNode 的子组件
		VSFSMPtr m_pFSM;
		VSSteerPtr m_pSteerPtr;

		VSActor* m_pOwner;

	public:
		VSUsedName m_ActorName;
		VSSceneMap* m_pSceneMap;

	public:
		virtual void OnDestory();
		VSActor* GetOwner();
		virtual void AddChildActor(VSActor* pActor);
		virtual void DeleteChildActor(VSActor* pActor);
		virtual VSActor* GetChildActor(unsigned int uiActorIndex);
		virtual void DeleteChildActor(unsigned int uiActorIndex);
		template <typename T>
		T* AddComponentNode(VSNodeComponent* pParent = NULL);
		template <typename T>
		void GetComponentNode(Container::MArray<T*>& Node);
		void DeleteComponentNode(VSNodeComponent* pComponent);
		void ChangeComponentNodeParent(VSNodeComponent* pSource, VSNode* pParent = NULL);
		void AddActorNodeToNode(VSActor* pActor, VSNodeComponent* pNode);

	protected:
		virtual void AddToSceneMap(VSSceneMap* pSceneMap);
		virtual void CreateDefaultComponentNode(); //world创建实体的时候调用构造默认父组件（world::CreateActor）

	protected:
		Container::MArray<VSActor*> m_ChildActor;

		Container::MArray<VSNodeComponentPtr> m_pNodeComponentArray; // not include root node
		DECLARE_RESOURCE(VSActor, RA_ASYN_LOAD | RA_ENABLE_GC, RT_ACTOR, ACTOR, Resource / Actor, VSCacheResource)
	};
	DECLARE_Ptr(VSActor);
	VSTYPE_MARCO(VSActor);
	DECLARE_Proxy(VSActor);
	template <typename T>
	T* VSActor::AddComponentNode(VSNodeComponent* pParent)
	{
		T* pNode = VSNodeComponent::CreateComponent<T>();
		if (pParent == NULL)
		{
			m_pNode->AddChild(pNode);
		}
		m_pNodeComponentArray.AddElement(pNode);
		return pNode;
	}
	template <typename T>
	void VSActor::GetComponentNode(Container::MArray<T*>& Node)
	{
		for (unsigned int i = 0; i < m_pNodeComponentArray.GetNum(); i++)
		{
			if (m_pNodeComponentArray[i]->GetType().IsSameType(T::GetType()))
			{
				Node.AddElement(m_pNodeComponentArray[i]);
			}
		}
	}
}
