#pragma once
#include "Array.h"
namespace Matrix
{
	namespace Container
	{

		template <class T, class MTXMemManagerClass = DefaultContainerMemoryAllocator>
		class MTXStack
		{
		public:
			MTXStack();
			~MTXStack();
			bool GetTop(T& Element);
			void Push(const T& Element);
			bool Pop(T& Element);
			unsigned int GetNum();
			void Clear();
			void Destroy();
		protected:
			MArray<T, MTXMemManagerClass> m_Array;
		};
		template <class T, class MTXMemManagerClass>
		MTXStack<T, MTXMemManagerClass>::MTXStack()
		{
		}
		template <class T, class MTXMemManagerClass>
		MTXStack<T, MTXMemManagerClass>::~MTXStack()
		{

		}
		template <class T, class MTXMemManagerClass>
		bool MTXStack<T, MTXMemManagerClass>::GetTop(T& Element)
		{
			if (m_Array.GetNum() == 0)
			{
				return false;
			}
			Element = m_Array[m_Array.GetNum() - 1];
			return true;
		}
		template <class T, class MTXMemManagerClass>
		void MTXStack<T, MTXMemManagerClass>::Push(const T& Element)
		{
			m_Array.AddElement(Element);
		}
		template <class T, class MTXMemManagerClass>
		bool MTXStack<T, MTXMemManagerClass>::Pop(T& Element)
		{
			if (m_Array.GetNum() == 0)
			{
				return false;
			}
			Element = m_Array[m_Array.GetNum() - 1];
			m_Array.Erase(m_Array.GetNum() - 1);
			return true;
		}
		template <class T, class MTXMemManagerClass>
		unsigned int MTXStack<T, MTXMemManagerClass>::GetNum()
		{
			return m_Array.GetNum();
		}
		template <class T, class MTXMemManagerClass>
		void MTXStack<T, MTXMemManagerClass>::Clear()
		{
			m_Array.Clear();
		}
		template <class T, class MTXMemManagerClass>
		void MTXStack<T, MTXMemManagerClass>::Destroy()
		{
			m_Array.Destroy();
		}
	}
}
