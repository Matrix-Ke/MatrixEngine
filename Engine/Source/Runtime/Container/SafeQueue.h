#pragma once
#include "Queue.h"
#include "Core/Synchronize.h"
namespace Matrix
{
	namespace Container
	{
		template <class T, class MMemManagerClass = Core::DefaultContainerMemoryAllocator>
		class MSafeQueue : public MXMemObject
		{
		public:
			MSafeQueue(bool bUnique = false);
			~MSafeQueue();
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
			MQueue<T, MMemManagerClass> m_Queue;
			MXCriticalSection m_CriticalSec;

		private:
		};
		template <class T, class MMemManagerClass>
		MSafeQueue<T, MMemManagerClass>::~MSafeQueue()
		{
		}

		template <class T, class MMemManagerClass>
		MSafeQueue<T, MMemManagerClass>::MSafeQueue(bool bUnique)
		{
		}
		template <class T, class MMemManagerClass>
		void MSafeQueue<T, MMemManagerClass>::Clear()
		{
			MXCriticalSection::Locker Temp(m_CriticalSec);
			m_Queue.Clear();
		}

		template <class T, class MMemManagerClass>
		void MSafeQueue<T, MMemManagerClass>::Enqueue(const T& Element)
		{
			MXCriticalSection::Locker Temp(m_CriticalSec);
			m_Queue.Enqueue(Element);
		}
		template <class T, class MMemManagerClass>
		bool MSafeQueue<T, MMemManagerClass>::TryEnqueue(const T& Element)
		{
			bool bLocked = m_CriticalSec.TryLock();
			if (bLocked)
			{
				m_Queue.Enqueue(Element);
				m_CriticalSec.Unlock();
			}
			return bLocked;
		}
		template <class T, class MMemManagerClass>
		void MSafeQueue<T, MMemManagerClass>::GetTop(T& Element)
		{
			MXCriticalSection::Locker Temp(m_CriticalSec);
			m_Queue.GetTop(Element);
		}
		template <class T, class MMemManagerClass>
		bool MSafeQueue<T, MMemManagerClass>::TryGetTop(T& Element)
		{
			bool bLocked = m_CriticalSec.TryLock();
			if (bLocked)
			{
				bLocked = m_Queue.GetTop(Element);
				m_CriticalSec.Unlock();
			}
			return bLocked;
		}
		template <class T, class MMemManagerClass>
		void MSafeQueue<T, MMemManagerClass>::Dequeue(T& Element)
		{
			MXCriticalSection::Locker Temp(m_CriticalSec);
			m_Queue.Dequeue(Element);
		}
		template <class T, class MMemManagerClass>
		bool MSafeQueue<T, MMemManagerClass>::TryDequeue(T& Element)
		{
			bool bLocked = m_CriticalSec.TryLock();
			if (bLocked)
			{
				bLocked = m_Queue.Dequeue(Element);
				m_CriticalSec.Unlock();
			}
			return bLocked;
		}
		template <class T, class MMemManagerClass>
		void MSafeQueue<T, MMemManagerClass>::Erase(const T& Element)
		{
			MXCriticalSection::Locker Temp(m_CriticalSec);
			m_Queue.Erase(Element);
		}
		template <class T, class MMemManagerClass>
		bool MSafeQueue<T, MMemManagerClass>::TryErase(const T& Element)
		{
			bool bLocked = m_CriticalSec.TryLock();
			if (bLocked)
			{
				m_Queue.Erase(Element);
				m_CriticalSec.Unlock();
			}
			return bLocked;
		}
		template <class T, class MMemManagerClass>
		bool MSafeQueue<T, MMemManagerClass>::IsEmpty()
		{
			MXCriticalSection::Locker Temp(m_CriticalSec);
			bool bEmpty = false;
			if (m_Queue.GetNum() == 0)
			{
				bEmpty = true;
			}
			return bEmpty;
		}
		template <class T, class MMemManagerClass>
		bool MSafeQueue<T, MMemManagerClass>::TryIsEmpty()
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
