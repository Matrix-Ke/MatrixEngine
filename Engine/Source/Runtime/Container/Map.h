#pragma once
#include "Container.h"
namespace Matrix
{
	namespace Container
	{
		template<class KEY, class VALUE, class MTXMemManagerClass = DefaultContainerMemoryAllocator>
		class MTXMap : public MContainer<MapElement<KEY, VALUE>, MTXMemManagerClass>
		{
		public:
			enum
			{
				DEFAULT_GROWBY = 10
			};

			MTXMap(unsigned int uiGrowBy = DEFAULT_GROWBY);
			~MTXMap();

			void SetBufferNum(unsigned int uiBufferNum);

			void operator= (const MTXMap<KEY, VALUE, MTXMemManagerClass>& Map);


			inline unsigned int GetNum()const;

			inline unsigned int GetBufferNum()const;

			inline MapElement<KEY, VALUE>* GetBuffer()const;
			inline void SetGrowBy(unsigned int uiGrowBy);

			template<class KEY1, class VALUE1>
			unsigned int AddElement(const MapElement<KEY1, VALUE1>& Element);
			unsigned int AddElement(const KEY& Key, const VALUE& Value);

			template<class KEY1, class VALUE1, class MTXMemManagerClass1>
			void AddElement(const MTXMap<KEY1, VALUE1, MTXMemManagerClass1>& Map, unsigned int uiBegin, unsigned int uiEnd);

			MapElement<KEY, VALUE>& operator[] (unsigned int i)const;

			void Clear();

			inline unsigned int GetSize()const;

			void Erase(unsigned int i);

			void Erase(unsigned int uiBegin, unsigned int uiEnd);

			template <class N>
			void Sort(unsigned int uiBegin, unsigned int uiEnd, N& Compare);
			template <class N>
			void SortAll(N& Compare);
			void Sort(unsigned int uiBegin, unsigned int uiEnd);
			void SortAll();
			unsigned int Find(const KEY& Key)const;

			unsigned int FindValueIndex(const VALUE& Value)const;

			void Destroy();


			class MTXMapIterator
			{
			public:
				MTXMapIterator(MapElement<KEY, VALUE>* pNode = NULL) :m_pNode(pNode)
				{
				}
				MTXMapIterator(const MTXMapIterator& Iterator)
				{
					m_pNode = Iterator.m_pNode;
				}
				~MTXMapIterator() = default;
				inline void operator= (const MTXMapIterator& Iterator)
				{
					m_pNode = Iterator.m_pNode;
				}
				inline bool operator!= (const MTXMapIterator& Iterator)
				{
					return (m_pNode != Iterator.m_pNode);
				}
				inline bool operator== (const MTXMapIterator& Iterator)
				{
					return (m_pNode == Iterator.m_pNode);
				}

				inline MTXMapIterator operator++()
				{
					m_pNode++;
					return (*this);
				}
				inline MTXMapIterator operator++(int)
				{
					MTXMapIterator _Tmp = *this;
					++* this;
					return (_Tmp);
				}
				inline MTXMapIterator operator--()
				{
					m_pNode--;
					return (*this);
				}
				inline MTXMapIterator operator--(int)
				{
					MTXMapIterator _Tmp = *this;
					--* this;
					return (_Tmp);
				}
				inline MapElement<KEY, VALUE>& operator*()const
				{
					return *m_pNode;
				}
				inline MapElement<KEY, VALUE>* operator->()const
				{
					return m_pNode;
				}
			protected:
				MapElement<KEY, VALUE>* m_pNode;

			};
			inline MTXMapIterator Begin() const
			{
				return MTXMapIterator(m_pBuffer);
			}
			inline MTXMapIterator End() const
			{
				return MTXMapIterator(m_pBuffer + GetNum());
			}
			inline MTXMapIterator begin() const
			{
				return Begin();
			}
			inline MTXMapIterator end() const
			{
				return End();
			}
		protected:
			void AddBufferNum(unsigned int uiBufferNum);
			MapElement<KEY, VALUE>* m_pBuffer;
			unsigned int m_uiGrowBy;
			unsigned int m_uiCurUse;
			unsigned int m_uiBufferNum;
			unsigned int m_uiAllocNum;
		};

		template<class KEY, class VALUE, class MTXMemManagerClass = DefaultContainerMemoryAllocator>
		class MTXMapOrder : public MTXMap<KEY, VALUE, MTXMemManagerClass>
		{
		public:
			MTXMapOrder(unsigned int uiGrowBy = DEFAULT_GROWBY);
			~MTXMapOrder();

			template<class KEY1, class VALUE1>
			unsigned int AddElement(const MapElement<KEY1, VALUE1>& Element);

			unsigned int AddElement(const KEY& Key, const VALUE& Value);

			template<class KEY1, class VALUE1, class MTXMemManagerClass1>
			void AddElement(const MTXMap<KEY1, VALUE1, MTXMemManagerClass1>& Map, unsigned int uiBegin, unsigned int uiEnd);

			unsigned int Find(const KEY& Key)const;

		protected:
			template<class KEY1, class VALUE1>
			unsigned int Process(unsigned int uiIndex0, unsigned int uiIndex1, const MapElement<KEY1, VALUE1>& Element);

			unsigned int FindElement(unsigned int uiIndex0, unsigned int uiIndex1, const KEY& Key)const;
		};
	}
}
