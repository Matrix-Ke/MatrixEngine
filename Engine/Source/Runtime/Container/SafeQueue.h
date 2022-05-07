#pragma once
#include "Queue.h"
#include "Core/Synchronize.h"
namespace Matrix
{
	namespace Container
	{
		template <class T, class MTXMemManagerClass = DefaultContainerMemoryAllocator>
		class MTXSafeQueue : public MTXMemObject
		{
		public:

			MTXSafeQueue(bool bUnique = false);
			~MTXSafeQueue();
			void Enqueue(const T& Element);
			void Dequeue(T& Element);
			void GetTop(T& Element);
			void Clear();
			void Erase(const T& Element);
			bool IsEmpty();

			bool TryEnqueue(const T& Element);
			bool TryDequeue(T& Element);
			bool TryGetTop(T& Element);
			bool TryErase(const T& Element);
			bool TryIsEmpty();
		protected:
			MTXQueue<T, MTXMemManagerClass> m_Queue;
			MTXCriticalSection m_CriticalSec;

		private:

		};
		template <class T, class MTXMemManagerClass>
		MTXSafeQueue<T, MTXMemManagerClass>::~MTXSafeQueue()
		{

		}

		template <class T, class MTXMemManagerClass>
		MTXSafeQueue<T, MTXMemManagerClass>::MTXSafeQueue(bool bUnique)
		{
		}
		template <class T, class MTXMemManagerClass>
		void MTXSafeQueue<T, MTXMemManagerClass>::Clear()
		{
			MTXCriticalSection::Locker Temp(m_CriticalSec);
			m_Queue.Clear();
		}

		template <class T, class MTXMemManagerClass>
		void MTXSafeQueue<T, MTXMemManagerClass>::Enqueue(const T& Element)
		{
			MTXCriticalSection::Locker Temp(m_CriticalSec);
			m_Queue.Enqueue(Element);
		}
		template <class T, class MTXMemManagerClass>
		bool MTXSafeQueue<T, MTXMemManagerClass>::TryEnqueue(const T& Element)
		{
			bool bLocked = m_CriticalSec.TryLock();
			if (bLocked)
			{
				m_Queue.Enqueue(Element);
				m_CriticalSec.Unlock();
			}
			return bLocked;
		}
		template <class T, class MTXMemManagerClass>
		void MTXSafeQueue<T, MTXMemManagerClass>::GetTop(T& Element)
		{
			MTXCriticalSection::Locker Temp(m_CriticalSec);
			m_Queue.GetTop(Element);
		}
		template <class T, class MTXMemManagerClass>
		bool MTXSafeQueue<T, MTXMemManagerClass>::TryGetTop(T& Element)
		{
			bool bLocked = m_CriticalSec.TryLock();
			if (bLocked)
			{
				bLocked = m_Queue.GetTop(Element);
				m_CriticalSec.Unlock();
			}
			return bLocked;
		}
		template <class T, class MTXMemManagerClass>
		void MTXSafeQueue<T, MTXMemManagerClass>::Dequeue(T& Element)
		{
			MTXCriticalSection::Locker Temp(m_CriticalSec);
			m_Queue.Dequeue(Element);
		}
		template <class T, class MTXMemManagerClass>
		bool MTXSafeQueue<T, MTXMemManagerClass>::TryDequeue(T& Element)
		{
			bool bLocked = m_CriticalSec.TryLock();
			if (bLocked)
			{
				bLocked = m_Queue.Dequeue(Element);
				m_CriticalSec.Unlock();
			}
			return bLocked;
		}
		template <class T, class MTXMemManagerClass>
		void MTXSafeQueue<T, MTXMemManagerClass>::Erase(const T& Element)
		{
			MTXCriticalSection::Locker Temp(m_CriticalSec);
			m_Queue.Erase(Element);
		}
		template <class T, class MTXMemManagerClass>
		bool MTXSafeQueue<T, MTXMemManagerClass>::TryErase(const T& Element)
		{
			bool bLocked = m_CriticalSec.TryLock();
			if (bLocked)
			{
				m_Queue.Erase(Element);
				m_CriticalSec.Unlock();
			}
			return bLocked;
		}
		template <class T, class MTXMemManagerClass>
		bool MTXSafeQueue<T, MTXMemManagerClass>::IsEmpty()
		{
			MTXCriticalSection::Locker Temp(m_CriticalSec);
			bool bEmpty = false;
			if (m_Queue.GetNum() == 0)
			{
				bEmpty = true;
			}
			return bEmpty;

		}
		template <class T, class MTXMemManagerClass>
		bool MTXSafeQueue<T, MTXMemManagerClass>::TryIsEmpty()
		{
			bool bLocked = m_CriticalSec.TryLock();
			bool bEmpty = false;
			if (bLocked)
			{
				if (m_Queue.GetNum() == 0)
				{
					bEmpty = true;
				}
				m_CriticalSec.Unlock();
			}
			return bEmpty;

		}
	}
}
