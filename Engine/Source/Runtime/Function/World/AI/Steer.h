#pragma once
#include "World/Actor/Actor.h"
namespace Matrix
{

    class VSSteerComponent : public MObject
    {
        // RTTI
        DECLARE_RTTI;
        friend class VSSteer;

    public:
        VSSteerComponent();
        virtual ~VSSteerComponent() = 0;
        inline VSSteer *GetOwner() const
        {
            return m_pSteer;
        }
        //计算合力
        virtual Math::Vector3 Compute() = 0;

    protected:
        VSSteer *m_pSteer;
        unsigned int m_uiPrior;
        VSREAL m_fWeight;
    };
    DECLARE_Ptr(VSSteerComponent);

    class VSSteer : public MObject
    {
        // RTTI
        DECLARE_RTTI;

    public:
        friend class VSActor;
        VSSteer();
        virtual ~VSSteer();
        inline VSActor *GetOwner() const
        {
            return m_pActor;
        }

        template <class T>
        T *GetSteerComponent();
        template <class T>
        void AddSteerComponent(unsigned int uiPrior, VSREAL fWeight);

        template <class T>
        void DeleteSteerComponent();
        virtual Math::Vector3 Compute();

    protected:
        VSActor *m_pActor;
        Container::MArray<VSSteerComponentPtr> m_ComponentArray;
        bool AddForce(Math::Vector3 &CurForce, Math::Vector3 &AddForce);
        class PriorityCompare
        {
        public:
            inline bool operator()(VSSteerComponentPtr &e1, VSSteerComponentPtr &e2)
            {

                return e1->m_uiPrior <= e2->m_uiPrior;
            }
        };
    };
    DECLARE_Ptr(VSSteer);
    template <class T>
    void VSSteer::AddSteerComponent(unsigned int uiPrior, VSREAL fWeight)
    {
        if (!T::ms_Type.IsDerived(VSSteerComponent::ms_Type))
        {
            return;
        }
        for (unsigned int i = 0; i < m_ComponentArray.GetNum(); i++)
        {
            if (T::ms_Type.IsSameType(m_ComponentArray[i]->GetType()))
            {
                continue;
            }
        }
        T *pComponent = MX_NEW T();
        VSSteerComponent *pTemp = StaticCast<VSSteerComponent>(pComponent);
        pTemp->m_pSteer = this;
        pTemp->m_fWeight = fWeight;
        pTemp->m_uiPrior = uiPrior;
        m_ComponentArray.AddElement(pComponent);
        m_ComponentArray.SortAll(PriorityCompare())
    }
    template <class T>
    T *VSSteer::GetSteerComponent()
    {
        for (unsigned int i = 0; i < m_ComponentArray.GetNum(); i++)
        {
            if (T::ms_Type.IsSameType(m_ComponentArray[i]->GetType()))
            {
                return StaticCast<T>(m_ComponentArray[i]);
            }
        }
    }

    template <class T>
    void VSSteer::DeleteSteerComponent()
    {
        for (unsigned int i = 0; i < m_ComponentArray.GetNum(); i++)
        {
            if (T::ms_Type.IsSameType(m_ComponentArray[i]->GetType()))
            {
                m_ComponentArray[i] = NULL;
                m_ComponentArray.Erase(i);
                return;
            }
        }
    }
}
