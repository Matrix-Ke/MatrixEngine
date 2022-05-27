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

		template <class T, class MMemManagerClass = Core::DefaultContainerMemoryAllocator>
		class MXList : public MContainer<ListElement<T>, MMemManagerClass>
		{
		public:
			MXList(bool bUnique = true);
			~MXList();

			void operator=(const MXList& Queue);

			inline unsigned int GetNum() const;

			void AddElement(const T& Element);

			bool GetAndEraseTail(T& Element);

			bool GetTail(T& Element);

			void Clear();

			bool Erase(const T& Element);

			bool Has(const T& Element) const;
			const ListElement<T>* Find(const T& Element) const;
			const T* FindElement(const T& Element) const;
			class MXListIterator
			{
			public:
				MXListIterator(ListElement<T>* pNode = NULL) : m_pNode(pNode)
				{
				}
				MXListIterator(const MXListIterator& Iterator)
				{
					m_pNode = Iterator.m_pNode;
				}
				~MXListIterator()
				{
					m_pNode = NULL;
				}
				inline void operator=(const MXListIterator& Iterator)
				{
					m_pNode = Iterator.m_pNode;
				}
				inline bool operator!=(const MXListIterator& Iterator)
				{
					return (m_pNode != Iterator.m_pNode);
				}
				inline bool operator==(const MXListIterator& Iterator)
				{
					return (m_pNode == Iterator.m_pNode);
				}

				inline MXListIterator operator++()
				{
					m_pNode = m_pNode->m_pNext;
					return (*this);
				}
				inline MXListIterator operator++(int)
				{
					_Tmp = *this;
					++* this;
					return (_Tmp);
				}
				inline MXListIterator operator--()
				{

					m_pNode = m_pNode->m_pFront;
					return (*this);
				}
				inline MXListIterator operator--(int)
				{
					_Tmp = *this;
					--* this;
					return (_Tmp);
				}
				inline T& operator*()
				{
					return m_pNode->Element;
				}
				inline T* operator->() const
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
			inline MXListIterator Begin() const
			{
				return MXListIterator(m_pHead);
			}
			inline MXListIterator End() const
			{
				return MXListIterator();
			}
			inline MXListIterator begin() const
			{
				return Begin();
			}
			inline MXListIterator end() const
			{
				return End();
			}
			inline MXListIterator Tail() const
			{
				return MXListIterator(m_pTail);
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
			bool m_bUnique;
		};
		template <class T, class MMemManagerClass>
		MXList<T, MMemManagerClass>::~MXList()
		{
			Clear();
		}

		template <class T, class MMemManagerClass>
		MXList<T, MMemManagerClass>::MXList(bool bUnique)
		{
			m_pHead = NULL;
			m_pTail = NULL;
			m_bUnique = bUnique;
			m_uiNum = 0;
		}
		template <class T, class MMemManagerClass>
		void MXList<T, MMemManagerClass>::Clear()
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
		template <class T, class MMemManagerClass>
		unsigned int MXList<T, MMemManagerClass>::GetNum() const
		{
			return m_uiNum;
		}
		template <class T, class MMemManagerClass>
		void MXList<T, MMemManagerClass>::operator=(const MXList& Queue)
		{
			m_bUnique = Queue.m_bUnique;
			ListElement<T>* pTemp = Queue.m_pHead;
			while (pTemp)
			{
				AddElement(pTemp->Element);
				pTemp = pTemp->m_pNext;
			}
		}
		template <class T, class MMemManagerClass>
		void MXList<T, MMemManagerClass>::AddElement(const T& Element)
		{
			if (m_bUnique)
			{
				if (Has(Element))
				{
					return;
				}
			}
			ListElement<T>* pElem = New(1);
			MX_NEW(pElem)
				ListElement<T>();
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
		template <class T, class MMemManagerClass>
		bool MXList<T, MMemManagerClass>::GetTail(T& Element)
		{
			if (!m_pTail)
			{
				return false;
			}
			Element = m_pTail->Element;
			return true;
		}
		template <class T, class MMemManagerClass>
		bool MXList<T, MMemManagerClass>::GetAndEraseTail(T& Element)
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
		template <class T, class MMemManagerClass>
		bool MXList<T, MMemManagerClass>::Erase(const T& Element)
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
						pTemp->m_pFront->m_pNext = NULL;
						;
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
		template <class T, class MMemManagerClass>
		bool MXList<T, MMemManagerClass>::Has(const T& Element) const
		{
			return (Find(Element) != NULL);
		}
		template <class T, class MMemManagerClass>
		const ListElement<T>* MXList<T, MMemManagerClass>::Find(const T& Element) const
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
		template <class T, class MMemManagerClass>
		const T* MXList<T, MMemManagerClass>::FindElement(const T& Element) const
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
