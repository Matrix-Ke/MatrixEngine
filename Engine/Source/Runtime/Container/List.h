#pragma once
#include "Container.h"
namespace Matrix
{
	namespace Container
	{
		template <class T>
		struct ListElement
		{
		public:
			ListElement()
			{
				m_pNext = NULL;
				m_pFront = NULL;
			}
			~ListElement()
			{
				m_pNext = NULL;
				m_pFront = NULL;
			}
			T Element;
			ListElement* m_pNext;
			ListElement* m_pFront;
		};

		template <class T, class MTXMemManagerClass = DefaultContainerMemoryAllocator>
		class MTXList : public MContainer<ListElement<T>, MTXMemManagerClass>
		{
		public:

			MTXList(bool bUnique = true);
			~MTXList();

			void operator= (const MTXList& Queue);

			inline unsigned int GetNum()const;

			void AddElement(const T& Element);

			bool GetAndEraseTail(T& Element);

			bool GetTail(T& Element);

			void Clear();

			bool Erase(const T& Element);

			bool Has(const T& Element)const;
			const ListElement<T>* Find(const T& Element)const;
			const T* FindElement(const T& Element)const;
			class MTXListIterator
			{
			public:
				MTXListIterator(ListElement<T>* pNode = NULL) :m_pNode(pNode)
				{
				}
				MTXListIterator(const MTXListIterator& Iterator)
				{
					m_pNode = Iterator.m_pNode;
				}
				~MTXListIterator()
				{
					m_pNode = NULL;
				}
				inline void operator= (const MTXListIterator& Iterator)
				{
					m_pNode = Iterator.m_pNode;
				}
				inline bool operator!= (const MTXListIterator& Iterator)
				{
					return (m_pNode != Iterator.m_pNode);
				}
				inline bool operator== (const MTXListIterator& Iterator)
				{
					return (m_pNode == Iterator.m_pNode);
				}

				inline MTXListIterator operator++()
				{
					m_pNode = m_pNode->m_pNext;
					return (*this);
				}
				inline MTXListIterator operator++(int)
				{
					_Tmp = *this;
					++* this;
					return (_Tmp);
				}
				inline MTXListIterator operator--()
				{

					m_pNode = m_pNode->m_pFront;
					return (*this);
				}
				inline MTXListIterator operator--(int)
				{
					_Tmp = *this;
					--* this;
					return (_Tmp);
				}
				inline T& operator*()
				{
					return m_pNode->Element;
				}
				inline T* operator->()const
				{
					return &m_pNode->Element;
				}
				bool IsValid()
				{
					return (m_pNode != NULL);
				}
				ListElement<T>* GetNode() const
				{
					return m_pNode;
				}
			protected:
				ListElement<T>* m_pNode;

			};
			inline MTXListIterator Begin() const
			{
				return MTXListIterator(m_pHead);
			}
			inline MTXListIterator End() const
			{
				return MTXListIterator();
			}
			inline MTXListIterator begin() const
			{
				return Begin();
			}
			inline MTXListIterator end() const
			{
				return End();
			}
			inline MTXListIterator Tail() const
			{
				return MTXListIterator(m_pTail);
			}
			inline void SetUnique(bool bUnique)
			{
				Clear();
				m_bUnique = bUnique;
			}
		protected:

			ListElement<T>* m_pHead;
			ListElement<T>* m_pTail;
			unsigned int m_uiNum;
			bool	m_bUnique;
		};
		template <class T, class MTXMemManagerClass>
		MTXList<T, MTXMemManagerClass>::~MTXList()
		{
			Clear();
		}

		template <class T, class MTXMemManagerClass>
		MTXList<T, MTXMemManagerClass>::MTXList(bool bUnique)
		{
			m_pHead = NULL;
			m_pTail = NULL;
			m_bUnique = bUnique;
			m_uiNum = 0;
		}
		template <class T, class MTXMemManagerClass>
		void MTXList<T, MTXMemManagerClass>::Clear()
		{
			ListElement<T>* pTemp = m_pHead;
			while (pTemp)
			{
				ListElement<T>* pNext = pTemp->m_pNext;
				Delete(pTemp, 1);
				pTemp = pNext;
			}
			m_pHead = NULL;
			m_pTail = NULL;
			m_uiNum = 0;
		}
		template <class T, class MTXMemManagerClass>
		unsigned int MTXList<T, MTXMemManagerClass>::GetNum()const
		{
			return m_uiNum;
		}
		template <class T, class MTXMemManagerClass>
		void MTXList<T, MTXMemManagerClass>::operator= (const MTXList& Queue)
		{
			m_bUnique = Queue.m_bUnique;
			ListElement<T>* pTemp = Queue.m_pHead;
			while (pTemp)
			{
				AddElement(pTemp->Element);
				pTemp = pTemp->m_pNext;

			}
		}
		template <class T, class MTXMemManagerClass>
		void MTXList<T, MTXMemManagerClass>::AddElement(const T& Element)
		{
			if (m_bUnique)
			{
				if (Has(Element))
				{
					return;
				}
			}
			ListElement<T>* pElem = New(1);
			MX_NEW(pElem) ListElement<T>();
			pElem->Element = Element;
			pElem->m_pFront = m_pTail;
			pElem->m_pNext = NULL;
			if (!m_pHead)
			{
				m_pHead = pElem;
			}

			if (!m_pTail)
			{
				m_pTail = pElem;
			}
			else
			{
				m_pTail->m_pNext = pElem;
				m_pTail = pElem;
			}
			m_uiNum++;
		}
		template <class T, class MTXMemManagerClass>
		bool MTXList<T, MTXMemManagerClass>::GetTail(T& Element)
		{
			if (!m_pTail)
			{
				return false;
			}
			Element = m_pTail->Element;
			return true;
		}
		template <class T, class MTXMemManagerClass>
		bool MTXList<T, MTXMemManagerClass>::GetAndEraseTail(T& Element)
		{
			if (!m_pTail)
			{
				return false;
			}
			Element = m_pTail->Element;

			if (m_pTail == m_pHead)
			{
				Delete(m_pTail, 1);
				m_pTail = m_pHead = NULL;
			}
			else
			{
				m_pTail->m_pFront->m_pNext = NULL;
				ListElement<T>* pTemp = m_pTail;
				m_pTail = m_pTail->m_pFront;
				Delete(pTemp, 1);
			}

			m_uiNum--;
			return true;
		}
		template <class T, class MTXMemManagerClass>
		bool MTXList<T, MTXMemManagerClass>::Erase(const T& Element)
		{
			ListElement<T>* pTemp = m_pHead;
			bool bFind = false;
			while (pTemp)
			{
				if (pTemp->Element == Element)
				{
					if (!pTemp->m_pFront && !pTemp->m_pNext)
					{
						m_pHead = NULL;
						m_pTail = NULL;
					}
					else if (!pTemp->m_pFront)
					{
						pTemp->m_pNext->m_pFront = NULL;
					}
					else if (!pTemp->m_pNext)
					{
						pTemp->m_pFront->m_pNext = NULL;;
					}
					else
					{
						pTemp->m_pNext->m_pFront = pTemp->m_pFront;
						pTemp->m_pFront->m_pNext = pTemp->m_pNext;
					}
					bFind = true;
					Delete(pTemp, 1);
					m_uiNum--;
					if (!m_bUnique)
					{
						continue;
					}
					else
					{
						break;
					}

				}
				pTemp = pTemp->m_pNext;

			}
			return bFind;
		}
		template <class T, class MTXMemManagerClass>
		bool MTXList<T, MTXMemManagerClass>::Has(const T& Element)const
		{
			return (Find(Element) != NULL);
		}
		template <class T, class MTXMemManagerClass>
		const ListElement<T>* MTXList<T, MTXMemManagerClass>::Find(const T& Element)const
		{
			ListElement<T>* pTemp = m_pHead;
			while (pTemp)
			{
				if (pTemp->Element == Element)
				{
					return pTemp;
				}
				pTemp = pTemp->m_pNext;
			}
			return NULL;
		}
		template <class T, class MTXMemManagerClass>
		const T* MTXList<T, MTXMemManagerClass>::FindElement(const T& Element)const
		{
			ListElement<T>* pTemp = m_pHead;
			while (pTemp)
			{
				if (pTemp->Element == Element)
				{
					return &pTemp->Element;
				}
				pTemp = pTemp->m_pNext;
			}
			return NULL;
		}
	}
}
