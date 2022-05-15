#pragma once
#include "Array.h"
namespace Matrix
{
    namespace Container
    {

        template <class T, class MXMemManagerClass = DefaultContainerMemoryAllocator>
        class MXStack
        {
        public:
            MXStack();
            ~MXStack();
            bool GetTop(T &Element);
            void Push(const T &Element);
            bool Pop(T &Element);
            unsigned int GetNum();
            void Clear();
            void Destroy();

        protected:
            MArray<T, MXMemManagerClass> m_Array;
        };
        template <class T, class MXMemManagerClass>
        MXStack<T, MXMemManagerClass>::MXStack()
        {
        }
        template <class T, class MXMemManagerClass>
        MXStack<T, MXMemManagerClass>::~MXStack()
        {
        }
        template <class T, class MXMemManagerClass>
        bool MXStack<T, MXMemManagerClass>::GetTop(T &Element)
        {
            if (m_Array.GetNum() == 0)
            {
                return false;
            }
            Element = m_Array[m_Array.GetNum() - 1];
            return true;
        }
        template <class T, class MXMemManagerClass>
        void MXStack<T, MXMemManagerClass>::Push(const T &Element)
        {
            m_Array.AddElement(Element);
        }
        template <class T, class MXMemManagerClass>
        bool MXStack<T, MXMemManagerClass>::Pop(T &Element)
        {
            if (m_Array.GetNum() == 0)
            {
                return false;
            }
            Element = m_Array[m_Array.GetNum() - 1];
            m_Array.Erase(m_Array.GetNum() - 1);
            return true;
        }
        template <class T, class MXMemManagerClass>
        unsigned int MXStack<T, MXMemManagerClass>::GetNum()
        {
            return m_Array.GetNum();
        }
        template <class T, class MXMemManagerClass>
        void MXStack<T, MXMemManagerClass>::Clear()
        {
            m_Array.Clear();
        }
        template <class T, class MXMemManagerClass>
        void MXStack<T, MXMemManagerClass>::Destroy()
        {
            m_Array.Destroy();
        }
    }
}
