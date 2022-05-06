#pragma once
#include "System/Core.h"
#include "System/MemoryManager.h"
#include "Container.h"
namespace Matrix
{
	namespace Container
	{
		template <class T>
		struct QueueElement
		{
		public:
			QueueElement()
			{
				m_pNext = NULL;
				m_pFront = NULL;
			}
			~QueueElement()
			{
				m_pNext = NULL;
				m_pFront = NULL;
			}
			T Element;
			QueueElement* m_pNext;
			QueueElement* m_pFront;
		};
		template <class T, class MTXMemManagerClass = DefaultContainerMemoryAllocator>
		class MTXQueue : public MContainer<QueueElement<T>, MTXMemManagerClass>
		{
		public:

			MTXQueue(bool bUnique = false);
			~MTXQueue();

			void operator= (const MTXQueue& Queue);

			inline unsigned int GetNum()const;

			void Enqueue(const T& Element);

			bool Dequeue(T& Element);

			bool GetTop(T& Element);

			void Clear();

			void Erase(const T& Element);

			bool Has(const T& Element);

		protected:

			QueueElement<T>* m_pHead;
			QueueElement<T>* m_pTail;
			unsigned int m_uiNum;
			bool	m_bUnique;


		private:

		};
		template <class T, class MTXMemManagerClass>
		MTXQueue<T, MTXMemManagerClass>::~MTXQueue()
		{
			Clear();
		}

		template <class T, class MTXMemManagerClass>
		MTXQueue<T, MTXMemManagerClass>::MTXQueue(bool bUnique)
		{
			m_pHead = NULL;
			m_pTail = NULL;
			m_bUnique = bUnique;
			m_uiNum = 0;
		}
		template <class T, class MTXMemManagerClass>
		void MTXQueue<T, MTXMemManagerClass>::Clear()
		{
			QueueElement<T>* pTemp = m_pHead;
			while (pTemp)
			{
				QueueElement<T>* pNext = pTemp->m_pNext;
				Delete(pTemp, 1);
				pTemp = pNext;
			}
			m_pHead = NULL;
			m_pTail = NULL;
			m_uiNum = 0;
		}
		template <class T, class MTXMemManagerClass>
		unsigned int MTXQueue<T, MTXMemManagerClass>::GetNum()const
		{
			return m_uiNum;
		}
		template <class T, class MTXMemManagerClass>
		void MTXQueue<T, MTXMemManagerClass>::operator= (const MTXQueue& Queue)
		{
			QueueElement<T>* pTemp = Queue.m_pHead;
			while (pTemp)
			{
				Enqueue(pTemp->Element);
				pTemp = pTemp->m_pNext;

			}
		}
		template <class T, class MTXMemManagerClass>
		void MTXQueue<T, MTXMemManagerClass>::Enqueue(const T& Element)
		{
			if (m_bUnique)
			{
				if (Has(Element))
				{
					return;
				}
			}
			QueueElement<T>* pElem = New(1);
			MATRIX_NEW(pElem) QueueElement<T>();
			pElem->Element = Element;
			pElem->m_pFront = NULL;
			pElem->m_pNext = m_pHead;
			if (m_pHead)
			{
				m_pHead->m_pFront = pElem;
			}
			m_pHead = pElem;
			if (!m_pTail)
			{
				m_pTail = pElem;
			}
			m_uiNum++;
		}
		template <class T, class MTXMemManagerClass>
		bool MTXQueue<T, MTXMemManagerClass>::GetTop(T& Element)
		{
			if (!m_pTail)
			{
				return false;
			}
			Element = m_pTail->Element;
			return true;
		}
		template <class T, class MTXMemManagerClass>
		bool MTXQueue<T, MTXMemManagerClass>::Dequeue(T& Element)
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
				QueueElement<T>* pTemp = m_pTail;
				m_pTail = m_pTail->m_pFront;
				Delete(pTemp, 1);
			}

			m_uiNum--;
			return true;
		}
		template <class T, class MTXMemManagerClass>
		void MTXQueue<T, MTXMemManagerClass>::Erase(const T& Element)
		{
			QueueElement<T>* pTemp = m_pHead;
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
						pTemp->m_pNext->m_pFront = pTemp->m_pFront;
					}
					else
					{
						pTemp->m_pNext->m_pFront = pTemp->m_pFront;
						pTemp->m_pFront->m_pNext = pTemp->m_pNext;
					}
					Delete(pTemp, 1);
					m_uiNum--;
					if (m_bUnique)
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
		}
		template <class T, class MTXMemManagerClass>
		bool MTXQueue<T, MTXMemManagerClass>::Has(const T& Element)
		{
			QueueElement<T>* pTemp = m_pHead;
			while (pTemp)
			{
				if (pTemp->Element == Element)
				{
					return true;
				}
				pTemp = pTemp->m_pNext;
			}
			return false;
		}
	}
}
