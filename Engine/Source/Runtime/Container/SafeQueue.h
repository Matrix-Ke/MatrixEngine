#pragma once
#include "Queue.h"
#include "Core/Synchronize.h"
namespace Matrix
{
    namespace Container
    {
        template <class T, class MXMemManagerClass = DefaultContainerMemoryAllocator>
        class MXSafeQueue : public MXMemObject
        {
        public:
            MXSafeQueue(bool bUnique = false);
            ~MXSafeQueue();
            void Enqueue(const T &Element);
            void Dequeue(T &Element);
            void GetTop(T &Element);
            void Clear();
            void Erase(const T &Element);
            bool IsEmpty();

            bool TryEnqueue(const T &Element);
            bool TryDequeue(T &Element);
            bool TryGetTop(T &Element);
            bool TryErase(const T &Element);
            bool TryIsEmpty();

        protected:
            MXQueue<T, MXMemManagerClass> m_Queue;
            MXCriticalSection m_CriticalSec;

        private:
        };
        template <class T, class MXMemManagerClass>
        MXSafeQueue<T, MXMemManagerClass>::~MXSafeQueue()
        {
        }

        template <class T, class MXMemManagerClass>
        MXSafeQueue<T, MXMemManagerClass>::MXSafeQueue(bool bUnique)
        {
        }
        template <class T, class MXMemManagerClass>
        void MXSafeQueue<T, MXMemManagerClass>::Clear()
        {
            MXCriticalSection::Locker Temp(m_CriticalSec);
            m_Queue.Clear();
        }

        template <class T, class MXMemManagerClass>
        void MXSafeQueue<T, MXMemManagerClass>::Enqueue(const T &Element)
        {
            MXCriticalSection::Locker Temp(m_CriticalSec);
            m_Queue.Enqueue(Element);
        }
        template <class T, class MXMemManagerClass>
        bool MXSafeQueue<T, MXMemManagerClass>::TryEnqueue(const T &Element)
        {
            bool bLocked = m_CriticalSec.TryLock();
            if (bLocked)
            {
                m_Queue.Enqueue(Element);
                m_CriticalSec.Unlock();
            }
            return bLocked;
        }
        template <class T, class MXMemManagerClass>
        void MXSafeQueue<T, MXMemManagerClass>::GetTop(T &Element)
        {
            MXCriticalSection::Locker Temp(m_CriticalSec);
            m_Queue.GetTop(Element);
        }
        template <class T, class MXMemManagerClass>
        bool MXSafeQueue<T, MXMemManagerClass>::TryGetTop(T &Element)
        {
            bool bLocked = m_CriticalSec.TryLock();
            if (bLocked)
            {
                bLocked = m_Queue.GetTop(Element);
                m_CriticalSec.Unlock();
            }
            return bLocked;
        }
        template <class T, class MXMemManagerClass>
        void MXSafeQueue<T, MXMemManagerClass>::Dequeue(T &Element)
        {
            MXCriticalSection::Locker Temp(m_CriticalSec);
            m_Queue.Dequeue(Element);
        }
        template <class T, class MXMemManagerClass>
        bool MXSafeQueue<T, MXMemManagerClass>::TryDequeue(T &Element)
        {
            bool bLocked = m_CriticalSec.TryLock();
            if (bLocked)
            {
                bLocked = m_Queue.Dequeue(Element);
                m_CriticalSec.Unlock();
            }
            return bLocked;
        }
        template <class T, class MXMemManagerClass>
        void MXSafeQueue<T, MXMemManagerClass>::Erase(const T &Element)
        {
            MXCriticalSection::Locker Temp(m_CriticalSec);
            m_Queue.Erase(Element);
        }
        template <class T, class MXMemManagerClass>
        bool MXSafeQueue<T, MXMemManagerClass>::TryErase(const T &Element)
        {
            bool bLocked = m_CriticalSec.TryLock();
            if (bLocked)
            {
                m_Queue.Erase(Element);
                m_CriticalSec.Unlock();
            }
            return bLocked;
        }
        template <class T, class MXMemManagerClass>
        bool MXSafeQueue<T, MXMemManagerClass>::IsEmpty()
        {
            MXCriticalSection::Locker Temp(m_CriticalSec);
            bool bEmpty = false;
            if (m_Queue.GetNum() == 0)
            {
                bEmpty = true;
            }
            return bEmpty;
        }
        template <class T, class MXMemManagerClass>
        bool MXSafeQueue<T, MXMemManagerClass>::TryIsEmpty()
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
