#pragma once
#include "Container.h"
namespace Matrix
{
	namespace MContainer
	{
		template <class T, class MemoryManagerClass = DefaultContainerMemoryAllocator>
		class MArray : public MContainer<T, MemoryManagerClass>
		{
		public:
			enum
			{
				DEFAULT_GROWBY = 10
			};
			MArray(unsigned int uiGrowBy = DEFAULT_GROWBY);
			~MArray();
			MArray(const MArray<T, MemoryManagerClass>& Array);
			void SetBufferNum(unsigned int uiBufferNum);
			void AddBufferNum(unsigned int uiBufferNum);
			void operator= (const MArray<T, MemoryManagerClass>& Array);


			inline unsigned int GetNum()   const;

			inline unsigned int GetBufferNum()   const;

			inline T* GetBuffer()   const;
			inline void SetGrowBy(unsigned int uiGrowBy);
			unsigned  AddElement(const T& Element);
			template <class N, class MTXMemManagerClassN>
			void AddElement(const MArray<N, MTXMemManagerClassN>& Array, unsigned int uiBegin, unsigned int uiEnd);
			T& operator[] (unsigned int i)const;

			void Clear();

			inline unsigned int GetSize()   const;

			void Erase(unsigned int i);

			void Erase(unsigned int uiBegin, unsigned int uiEnd);

			//当Compare == 0 升序 
			template <class N>
			void Sort(unsigned int uiBegin, unsigned int uiEnd, N& Compare);
			template <class N>
			void SortAll(N& Compare);
			//升序排序
			void Sort(unsigned int uiBegin, unsigned int uiEnd);
			void SortAll();
			void Destroy();
			//用这个函数要注意：如果T是智能指针，参数Element 从指针到智能指针的隐式转换，导致智能指针对象的创建
			//和销毁过程中，reference加1减1，如果原来对象的reference为0，则会销毁对象，导致出错
			unsigned int FindElement(const T& Element);
			void GetNoHaveElement(const MArray<T, MemoryManagerClass>& Array);

			class MTXArrayIterator
			{
			public:
				MTXArrayIterator(T* pNode = NULL) :m_pNode(pNode)
				{
				}
				MTXArrayIterator(const MTXArrayIterator& Iterator)
				{
					m_pNode = Iterator.m_pNode;
				}
				~MTXArrayIterator() = default;
				inline void operator= (const MTXArrayIterator& Iterator)
				{
					m_pNode = Iterator.m_pNode;
				}
				inline bool operator!= (const MTXArrayIterator& Iterator)
				{
					return (m_pNode != Iterator.m_pNode);
				}
				inline bool operator== (const MTXArrayIterator& Iterator)
				{
					return (m_pNode == Iterator.m_pNode);
				}

				inline MTXArrayIterator operator++()
				{
					m_pNode++;
					return (*this);
				}
				inline MTXArrayIterator operator++(int)
				{
					MTXArrayIterator _Tmp = *this;
					++* this;
					return (_Tmp);
				}
				inline MTXArrayIterator operator--()
				{
					m_pNode--;
					return (*this);
				}
				inline MTXArrayIterator operator--(int)
				{
					MTXArrayIterator _Tmp = *this;
					--* this;
					return (_Tmp);
				}
				inline T& operator*()   const
				{
					return *m_pNode;
				}
				inline T* operator->()   const
				{
					return m_pNode;
				}
			protected:
				T* m_pNode;

			};
			inline MTXArrayIterator Begin()    const
			{
				return MTXArrayIterator(m_pBuffer);
			}
			inline MTXArrayIterator End()    const
			{
				return MTXArrayIterator(m_pBuffer + GetNum());
			}
			inline MTXArrayIterator begin()    const
			{
				return Begin();
			}
			inline MTXArrayIterator end()    const
			{
				return End();
			}
		protected:
			T* m_pBuffer;
			unsigned int m_uiGrowBy;
			unsigned int m_uiCurUse;
			unsigned int m_uiBufferNum;
			unsigned int m_uiAllocNum;


		private:

		};
		//有序数组
		template <class T, class MemoryManagerClass = DefaultContainerMemoryAllocator>
		class MTXArrayOrder : public MArray<T, MemoryManagerClass>
		{
		public:
			MTXArrayOrder(unsigned int uiGrowBy = DEFAULT_GROWBY);
			~MTXArrayOrder();
			unsigned int AddElement(const T& Element);

			//用这个函数要注意：如果T是智能指针，参数Element 从指针到智能指针的隐式转换，导致智能指针对象的创建
			//和销毁过程中，reference加1减1，如果原来对象的reference为0，则会销毁对象，导致出错
			unsigned int FindElement(const T& Element);

			void ReSort(unsigned int i);
		protected:

			unsigned int Process(unsigned int uiIndex0, unsigned int uiIndex1, const T& Element);

			unsigned int FindElement(unsigned int uiIndex0, unsigned int uiIndex1, const T& Element);
		};
#include "Array.inl"
	}
}
