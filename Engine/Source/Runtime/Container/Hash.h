#pragma once
#include "Container.h"
#include "BinaryTree.h"
#include "Array.h"
#include "Math.h"
#include "List.h"
namespace Matrix
{
	namespace Container
	{
		template <class HashType, class MTXMemManagerClass = DefaultContainerMemoryAllocator>
		class MTXHash : public MContainer<HashType, MTXMemManagerClass>
		{
		public:
			MTXHash()
			{
			}
			template <typename T>
			void AddElement(const T& Element)
			{
				unsigned int HashID = GetTypeHash(Element) % m_Hash.GetNum();
				m_Hash[HashID].AddElement(Element);
			}
			template <typename T>
			bool Erase(const T& Element)
			{
				unsigned int HashID = GetTypeHash(Element) % m_Hash.GetNum();
				return m_Hash[HashID].Erase(Element);
			}
			template <typename T>
			bool Has(const T& Element)const
			{
				unsigned int HashID = GetTypeHash(Element) % m_Hash.GetNum();
				return m_Hash[HashID].Has(Element);
			}
			template <typename T>
			const T* FindElement(const T& Element)const
			{
				unsigned int HashID = GetTypeHash(Element) % m_Hash.GetNum();
				return m_Hash[HashID].FindElement(Element);
			}
			HashType* GetHashTarget(unsigned int HashID)
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
				MTXENGINE_ASSERT(uiHashNum);
				m_Hash.SetBufferNum(uiHashNum);
			}
		protected:
			MArray<HashType, MTXMemManagerClass> m_Hash;
		};
		template <class T, class MTXMemManagerClass = DefaultContainerMemoryAllocator>
		class MTXHashTree : public MTXHash<MTXBinaryTree<T, MTXMemManagerClass>, MTXMemManagerClass>
		{
		public:
			MTXHashTree() :MTXHash<MTXBinaryTree<T, MTXMemManagerClass>, MTXMemManagerClass>()
			{
			}
			const MTXBinaryTreeNode<T>* Find(const T& Element)const
			{
				unsigned int HashID = GetTypeHash(Element) % m_Hash.GetNum();
				return &m_Hash[HashID].Find(Element);
			}
			template<class N>
			void PreProcess(N& Process)
			{
				for (unsigned int i = 0; i < m_Hash.GetNum(); i++)
				{
					m_Hash[i].PreProcess(Process);
				}
			}
			template<class N>
			void PostProcess(N& Process)
			{
				for (unsigned int i = 0; i < m_Hash.GetNum(); i++)
				{
					m_Hash[i].PostProcess(Process);
				}
			}
			template<class N>
			void MiddleProcess(N& Process)
			{
				for (unsigned int i = 0; i < m_Hash.GetNum(); i++)
				{
					m_Hash[i].MiddleProcess(Process);
				}
			}
		};
		template <class T, class MTXMemManagerClass = DefaultContainerMemoryAllocator>
		class MTXHashList : public MTXHash<MTXList<T, MTXMemManagerClass>, MTXMemManagerClass>
		{
		public:
			MTXHashList() :MTXHash<MTXList<T, MTXMemManagerClass>, MTXMemManagerClass>()
			{

			}
			const ListElement<T>* Find(const T& Element)const
			{
				unsigned int HashID = GetTypeHash(Element) % m_Hash.GetNum();
				return &m_Hash[HashID].Find(Element);
			}
			inline void SetHashNum(unsigned int uiHashNum)
			{
				MTXENGINE_ASSERT(uiHashNum);
				m_Hash.SetBufferNum(uiHashNum);
				for (unsigned int i = 0; i < m_Hash.GetNum(); i++)
				{
					m_Hash[i].SetUnique(false);
				}
			}
			class MTXHashListIterator
			{
			public:
				MTXHashListIterator()
				{
					m_pOwner = NULL;
					m_iCurHashID = -1;
					m_pNode = NULL;
				}
				MTXHashListIterator(MTXHashList* InOwner)
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
				MTXHashListIterator(const MTXHashListIterator& Iterator)
				{
					m_pOwner = Iterator.m_pOwner;
					m_pNode = Iterator.m_pNode;
					m_iCurHashID = Iterator.m_iCurHashID;
				}
				~MTXHashListIterator()
				{
					Invald();
				}
				void operator= (const MTXHashListIterator& Iterator)
				{
					m_pNode = Iterator.m_pNode;
					m_pOwner = Iterator.m_pOwner;
					m_iCurHashID = Iterator.m_iCurHashID;
				}
				bool operator!= (const MTXHashListIterator& Iterator)
				{
					return (m_pNode != Iterator.m_pNode || m_pOwner != Iterator.m_pOwner || m_iCurHashID != Iterator.m_iCurHashID);
				}
				bool operator== (const MTXHashListIterator& Iterator)
				{
					return (m_pNode == Iterator.m_pNode && m_pOwner == Iterator.m_pOwner && m_iCurHashID == Iterator.m_iCurHashID);
				}

				void operator= (ListElement<T>* pNode)
				{
					m_pNode = pNode;
				}
				bool operator!= (ListElement<T>* pNode)
				{
					return (m_pNode != pNode);
				}
				bool operator== (ListElement<T>* pNode)
				{
					return (m_pNode == pNode);
				}

				MTXHashListIterator operator++()
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
				MTXHashListIterator operator++(int)
				{
					MTXHashListIterator Temp = *this;
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
				MTXHashListIterator operator--()
				{
					MTXHashListIterator Temp = *this;
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
				MTXHashListIterator operator--(int)
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
				T& operator*()
				{
					if (m_pNode)
					{
						return m_pNode->Element;
					}
					else
					{
						MTXENGINE_ASSERT(0);
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
				MTXHashList* m_pOwner;
				int m_iCurHashID;
				ListElement<T>* m_pNode;
			};
			MTXHashListIterator Begin()
			{
				return MTXHashListIterator(this);
			}
			MTXHashListIterator End()
			{
				return MTXHashListIterator();
			}
		};
	}
}
