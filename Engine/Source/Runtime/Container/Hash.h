#pragma once
#include "Container.h"
#include "BinaryTree.h"
#include "Array.h"
#include "List.h"
//#include "Platform/MemoryManager.h"

namespace Matrix
{
    namespace Container
    {
        template <class HashType, class MMemManagerClass = Core::DefaultContainerMemoryAllocator>
        class MHash : public MContainer<HashType, MMemManagerClass>
        {
        public:
            MHash()
            {
            }
            template <typename T>
            void AddElement(const T &Element)
            {
                unsigned int HashID = Math::GetTypeHash(Element) % m_Hash.GetNum();
                m_Hash[HashID].AddElement(Element);
            }
            template <typename T>
            bool Erase(const T &Element)
            {
                unsigned int HashID = Math::GetTypeHash(Element) % m_Hash.GetNum();
                return m_Hash[HashID].Erase(Element);
            }
            template <typename T>
            bool Has(const T &Element) const
            {
                unsigned int HashID = Math::GetTypeHash(Element) % m_Hash.GetNum();
                return m_Hash[HashID].Has(Element);
            }
            template <typename T>
            const T *FindElement(const T &Element) const
            {
                unsigned int HashID = Math::GetTypeHash(Element) % m_Hash.GetNum();
                return m_Hash[HashID].FindElement(Element);
            }
            HashType *GetHashTarget(unsigned int HashID)
            {
                if (HashID < m_Hash.GetNum())
                {
                    return &m_Hash[HashID];
                }
                else
                {
                    return NULL;
                }
            }
            inline void SetHashNum(unsigned int uiHashNum)
            {
                MATRIX_ENGINE_ASSERT(uiHashNum);
                m_Hash.SetBufferNum(uiHashNum);
            }

        protected:
            MArray<HashType, MMemManagerClass> m_Hash;
        };
        template <class T, class MMemManagerClass = Core::DefaultContainerMemoryAllocator>
        class MHashTree : public MHash<MXBinaryTree<T, MMemManagerClass>, MMemManagerClass>
        {
        public:
            MHashTree() : MHash<MXBinaryTree<T, MMemManagerClass>, MMemManagerClass>()
            {
            }
            const MBinaryTreeNode<T> *Find(const T &Element) const
            {
                unsigned int HashID = Math::GetTypeHash(Element) % m_Hash.GetNum();
                return &m_Hash[HashID].Find(Element);
            }
            template <class N>
            void PreProcess(N &Process)
            {
                for (unsigned int i = 0; i < m_Hash.GetNum(); i++)
                {
                    m_Hash[i].PreProcess(Process);
                }
            }
            template <class N>
            void PostProcess(N &Process)
            {
                for (unsigned int i = 0; i < m_Hash.GetNum(); i++)
                {
                    m_Hash[i].PostProcess(Process);
                }
            }
            template <class N>
            void MiddleProcess(N &Process)
            {
                for (unsigned int i = 0; i < m_Hash.GetNum(); i++)
                {
                    m_Hash[i].MiddleProcess(Process);
                }
            }
        };
        template <class T, class MMemManagerClass = Core::DefaultContainerMemoryAllocator>
        class MHashList : public MHash<MXList<T, MMemManagerClass>, MMemManagerClass>
        {
        public:
            MHashList() : MHash<MXList<T, MMemManagerClass>, MMemManagerClass>()
            {
            }
            const ListElement<T> *Find(const T &Element) const
            {
                unsigned int HashID = Math::GetTypeHash(Element) % m_Hash.GetNum();
                return &m_Hash[HashID].Find(Element);
            }
            inline void SetHashNum(unsigned int uiHashNum)
            {
                MATRIX_ENGINE_ASSERT(uiHashNum);
                m_Hash.SetBufferNum(uiHashNum);
                for (unsigned int i = 0; i < m_Hash.GetNum(); i++)
                {
                    m_Hash[i].SetUnique(false);
                }
            }
            class MHashListIterator
            {
            public:
                MHashListIterator()
                {
                    m_pOwner = NULL;
                    m_iCurHashID = -1;
                    m_pNode = NULL;
                }
                MHashListIterator(MHashList *InOwner)
                {
                    m_pOwner = InOwner;
                    if (InOwner)
                    {
                        m_iCurHashID = 0;
                        m_pNode = InOwner->m_Hash[m_iCurHashID].Begin().GetNode();
                    }
                    else
                    {
                        Invald();
                    }
                }
                MHashListIterator(const MHashListIterator &Iterator)
                {
                    m_pOwner = Iterator.m_pOwner;
                    m_pNode = Iterator.m_pNode;
                    m_iCurHashID = Iterator.m_iCurHashID;
                }
                ~MHashListIterator()
                {
                    Invald();
                }
                void operator=(const MHashListIterator &Iterator)
                {
                    m_pNode = Iterator.m_pNode;
                    m_pOwner = Iterator.m_pOwner;
                    m_iCurHashID = Iterator.m_iCurHashID;
                }
                bool operator!=(const MHashListIterator &Iterator)
                {
                    return (m_pNode != Iterator.m_pNode || m_pOwner != Iterator.m_pOwner || m_iCurHashID != Iterator.m_iCurHashID);
                }
                bool operator==(const MHashListIterator &Iterator)
                {
                    return (m_pNode == Iterator.m_pNode && m_pOwner == Iterator.m_pOwner && m_iCurHashID == Iterator.m_iCurHashID);
                }

                void operator=(ListElement<T> *pNode)
                {
                    m_pNode = pNode;
                }
                bool operator!=(ListElement<T> *pNode)
                {
                    return (m_pNode != pNode);
                }
                bool operator==(ListElement<T> *pNode)
                {
                    return (m_pNode == pNode);
                }

                MHashListIterator operator++()
                {
                    if (m_pNode)
                    {
                        m_pNode = m_pNode->m_pNext;
                        while (!m_pNode)
                        {
                            m_iCurHashID++;
                            if (m_iCurHashID == m_pOwner->m_Hash.GetNum())
                            {
                                Invald();
                                break;
                            }
                            m_pNode = m_pOwner->m_Hash[m_iCurHashID].Begin().GetNode();
                        }
                    }
                    return (*this);
                }
                MHashListIterator operator++(int)
                {
                    MHashListIterator Temp = *this;
                    if (m_pNode)
                    {
                        m_pNode = m_pNode->m_pNext;
                        while (!m_pNode)
                        {
                            m_iCurHashID++;
                            if (m_iCurHashID == m_pOwner->m_Hash.GetNum())
                            {
                                Invald();
                                break;
                            }
                            m_pNode = m_pOwner->m_Hash[m_iCurHashID].Begin().GetNode();
                        }
                    }
                    return Temp;
                }
                MHashListIterator operator--()
                {
                    MHashListIterator Temp = *this;
                    if (m_pNode)
                    {
                        m_pNode = m_pNode->m_pFront;
                        while (!m_pNode)
                        {
                            m_iCurHashID--;
                            if (m_iCurHashID == -1)
                            {
                                Invald();
                                break;
                            }
                            m_pNode = m_pOwner->m_Hash[m_iCurHashID].Begin().GetNode();
                        }
                    }
                    return Temp;
                }
                MHashListIterator operator--(int)
                {
                    if (m_pNode)
                    {
                        m_pNode = m_pNode->m_pFront;
                        while (!m_pNode)
                        {
                            m_iCurHashID--;
                            if (m_iCurHashID == -1)
                            {
                                Invald();
                                break;
                            }
                            m_pNode = m_pOwner->m_Hash[m_iCurHashID].Begin().GetNode();
                        }
                    }
                    return (*this);
                }
                bool IsValid()
                {
                    return (m_pNode != NULL);
                }
                T &operator*()
                {
                    if (m_pNode)
                    {
                        return m_pNode->Element;
                    }
                    else
                    {
                        MATRIX_ENGINE_ASSERT(0);
                        return m_pNode->Element;
                    }
                }

            protected:
                void Invald()
                {
                    m_pOwner = NULL;
                    m_iCurHashID = -1;
                    m_pNode = NULL;
                }
                MHashList *m_pOwner;
                int m_iCurHashID;
                ListElement<T> *m_pNode;
            };
            MHashListIterator Begin()
            {
                return MHashListIterator(this);
            }
            MHashListIterator End()
            {
                return MHashListIterator();
            }
        };
    }
}
