#pragma once
#include "Container.h"
namespace Matrix
{
	namespace Container
	{
		template <class KEY, class VALUE, class MMemManagerClass = Core::DefaultContainerMemoryAllocator>
		class MMap : public MContainer<MapElement<KEY, VALUE>, MMemManagerClass>
		{
		public:
			enum
			{
				DEFAULT_GROWBY = 10
			};

			MMap(unsigned int uiGrowBy = DEFAULT_GROWBY);
			~MMap();

			void SetBufferNum(unsigned int uiBufferNum);

			void operator=(const MMap<KEY, VALUE, MMemManagerClass>& Map);

			inline unsigned int GetNum() const;

			inline unsigned int GetBufferNum() const;

			inline MapElement<KEY, VALUE>* GetBuffer() const;
			inline void SetGrowBy(unsigned int uiGrowBy);

			template <class KEY1, class VALUE1>
			unsigned int AddElement(const MapElement<KEY1, VALUE1>& Element);
			unsigned int AddElement(const KEY& Key, const VALUE& Value);

			template <class KEY1, class VALUE1, class MXMemManagerClass1>
			void AddElement(const MMap<KEY1, VALUE1, MXMemManagerClass1>& Map, unsigned int uiBegin, unsigned int uiEnd);

			MapElement<KEY, VALUE>& operator[](unsigned int i) const;

			void Clear();

			inline unsigned int GetSize() const;

			void Erase(unsigned int i);

			void Erase(unsigned int uiBegin, unsigned int uiEnd);

			template <class N>
			void Sort(unsigned int uiBegin, unsigned int uiEnd, N& Compare);
			template <class N>
			void SortAll(N& Compare);
			void Sort(unsigned int uiBegin, unsigned int uiEnd);
			void SortAll();
			unsigned int Find(const KEY& Key) const;

			unsigned int FindValueIndex(const VALUE& Value) const;

			void Destroy();

			class MXMapIterator
			{
			public:
				MXMapIterator(MapElement<KEY, VALUE>* pNode = NULL) : m_pNode(pNode)
				{
				}
				MXMapIterator(const MXMapIterator& Iterator)
				{
					m_pNode = Iterator.m_pNode;
				}
				~MXMapIterator() = default;
				inline void operator=(const MXMapIterator& Iterator)
				{
					m_pNode = Iterator.m_pNode;
				}
				inline bool operator!=(const MXMapIterator& Iterator)
				{
					return (m_pNode != Iterator.m_pNode);
				}
				inline bool operator==(const MXMapIterator& Iterator)
				{
					return (m_pNode == Iterator.m_pNode);
				}

				inline MXMapIterator operator++()
				{
					m_pNode++;
					return (*this);
				}
				inline MXMapIterator operator++(int)
				{
					MXMapIterator _Tmp = *this;
					++* this;
					return (_Tmp);
				}
				inline MXMapIterator operator--()
				{
					m_pNode--;
					return (*this);
				}
				inline MXMapIterator operator--(int)
				{
					MXMapIterator _Tmp = *this;
					--* this;
					return (_Tmp);
				}
				inline MapElement<KEY, VALUE>& operator*() const
				{
					return *m_pNode;
				}
				inline MapElement<KEY, VALUE>* operator->() const
				{
					return m_pNode;
				}

			protected:
				MapElement<KEY, VALUE>* m_pNode;
			};
			inline MXMapIterator Begin() const
			{
				return MXMapIterator(m_pBuffer);
			}
			inline MXMapIterator End() const
			{
				return MXMapIterator(m_pBuffer + GetNum());
			}
			inline MXMapIterator begin() const
			{
				return Begin();
			}
			inline MXMapIterator end() const
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

		template <class KEY, class VALUE, class MMemManagerClass = Core::DefaultContainerMemoryAllocator>
		class MMapOrder : public MMap<KEY, VALUE, MMemManagerClass>
		{
		public:
			MMapOrder(unsigned int uiGrowBy = DEFAULT_GROWBY);
			~MMapOrder();

			template <class KEY1, class VALUE1>
			unsigned int AddElement(const MapElement<KEY1, VALUE1>& Element);

			unsigned int AddElement(const KEY& Key, const VALUE& Value);

			template <class KEY1, class VALUE1, class MXMemManagerClass1>
			void AddElement(const MMap<KEY1, VALUE1, MXMemManagerClass1>& Map, unsigned int uiBegin, unsigned int uiEnd);

			unsigned int Find(const KEY& Key) const;

		protected:
			template <class KEY1, class VALUE1>
			unsigned int Process(unsigned int uiIndex0, unsigned int uiIndex1, const MapElement<KEY1, VALUE1>& Element);

			unsigned int FindElement(unsigned int uiIndex0, unsigned int uiIndex1, const KEY& Key) const;
		};

#include "Map.inl"
	}
}
