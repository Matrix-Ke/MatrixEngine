#pragma once
#include "Array.h"
namespace Matrix
{
	namespace Container
	{

		template <class T, class MMemManagerClass = Core::DefaultContainerMemoryAllocator>
		class MStack
		{
		public:
			MStack();
			~MStack();
			bool GetTop(T& Element);
			void Push(const T& Element);
			bool Pop(T& Element);
			unsigned int GetNum();
			void Clear();
			void Destroy();

		protected:
			MArray<T, MMemManagerClass> m_Array;
		};
		template <class T, class MMemManagerClass>
		MStack<T, MMemManagerClass>::MStack()
		{
		}
		template <class T, class MMemManagerClass>
		MStack<T, MMemManagerClass>::~MStack()
		{
		}
		template <class T, class MMemManagerClass>
		bool MStack<T, MMemManagerClass>::GetTop(T& Element)
		{
			if (m_Array.GetNum() == 0)
			{
				return false;
			}
			Element = m_Array[m_Array.GetNum() - 1];
			return true;
		}
		template <class T, class MMemManagerClass>
		void MStack<T, MMemManagerClass>::Push(const T& Element)
		{
			m_Array.AddElement(Element);
		}
		template <class T, class MMemManagerClass>
		bool MStack<T, MMemManagerClass>::Pop(T& Element)
		{
			if (m_Array.GetNum() == 0)
			{
				return false;
			}
			Element = m_Array[m_Array.GetNum() - 1];
			m_Array.Erase(m_Array.GetNum() - 1);
			return true;
		}
		template <class T, class MMemManagerClass>
		unsigned int MStack<T, MMemManagerClass>::GetNum()
		{
			return m_Array.GetNum();
		}
		template <class T, class MMemManagerClass>
		void MStack<T, MMemManagerClass>::Clear()
		{
			m_Array.Clear();
		}
		template <class T, class MMemManagerClass>
		void MStack<T, MMemManagerClass>::Destroy()
		{
			m_Array.Destroy();
		}
	}
}
