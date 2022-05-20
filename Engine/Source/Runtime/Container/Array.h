#pragma once
#include "Container.h"
namespace Matrix
{
    namespace Container
    {
        template <class T, class MemoryManagerClass = Core::DefaultContainerMemoryAllocator>
        class MArray : public MContainer<T, MemoryManagerClass>
        {
        public:
            enum // 默认增长步幅
            {
                DEFAULT_GROWBY = 10
            };
            MArray(unsigned int uiGrowBy = DEFAULT_GROWBY);
            ~MArray();
            MArray(const MArray<T, MemoryManagerClass> &Array);
            //设置元素个数，并初始化
            void SetBufferNum(unsigned int uiBufferNum);
            //添加 uiBufferNum 个元素，没有初始化
            void AddBufferNum(unsigned int uiBufferNum);
            void operator=(const MArray<T, MemoryManagerClass> &Array);

            inline unsigned int GetNum() const;

            inline unsigned int GetBufferNum() const;

            inline T *GetBuffer() const;
            inline void SetGrowBy(unsigned int uiGrowBy);
            unsigned AddElement(const T &Element);
            template <class N, class MXMemManagerClassN>
            void AddElement(const MArray<N, MXMemManagerClassN> &Array, unsigned int uiBegin, unsigned int uiEnd);
            T &operator[](unsigned int i) const;

            void Clear();

            inline unsigned int GetSize() const;

            void Erase(unsigned int i);

            void Erase(unsigned int uiBegin, unsigned int uiEnd);

            //当Compare == 0 升序
            template <class N>
            void Sort(unsigned int uiBegin, unsigned int uiEnd, N &Compare);
            template <class N>
            void SortAll(N &Compare);
            //升序排序
            void Sort(unsigned int uiBegin, unsigned int uiEnd);
            void SortAll();
            void Destroy();
            //用这个函数要注意：如果T是智能指针，参数Element 从指针到智能指针的隐式转换，导致智能指针对象的创建
            //和销毁过程中，reference加1减1，如果原来对象的reference为0，则会销毁对象，导致出错
            unsigned int FindElement(const T &Element);
            void GetNoHaveElement(const MArray<T, MemoryManagerClass> &Array);

            class MArrayIterator
            {
            public:
                MArrayIterator(T *pNode = NULL) : m_pNode(pNode)
                {
                }
                MArrayIterator(const MArrayIterator &Iterator)
                {
                    m_pNode = Iterator.m_pNode;
                }
                ~MArrayIterator() = default;
                inline void operator=(const MArrayIterator &Iterator)
                {
                    m_pNode = Iterator.m_pNode;
                }
                inline bool operator!=(const MArrayIterator &Iterator)
                {
                    return (m_pNode != Iterator.m_pNode);
                }
                inline bool operator==(const MArrayIterator &Iterator)
                {
                    return (m_pNode == Iterator.m_pNode);
                }

                inline MArrayIterator operator++()
                {
                    m_pNode++;
                    return (*this);
                }
                inline MArrayIterator operator++(int)
                {
                    MArrayIterator _Tmp = *this;
                    ++*this;
                    return (_Tmp);
                }
                inline MArrayIterator operator--()
                {
                    m_pNode--;
                    return (*this);
                }
                inline MArrayIterator operator--(int)
                {
                    MArrayIterator _Tmp = *this;
                    --*this;
                    return (_Tmp);
                }
                inline T &operator*() const
                {
                    return *m_pNode;
                }
                inline T *operator->() const
                {
                    return m_pNode;
                }

            protected:
                T *m_pNode;
            };
            inline MArrayIterator Begin() const
            {
                return MArrayIterator(m_pBuffer);
            }
            inline MArrayIterator End() const
            {
                return MArrayIterator(m_pBuffer + GetNum());
            }
            inline MArrayIterator begin() const
            {
                return Begin();
            }
            inline MArrayIterator end() const
            {
                return End();
            }

        protected:
            T *m_pBuffer;               //空间地址指针
            unsigned int m_uiGrowBy;    //增长幅度
            unsigned int m_uiCurUse;    //当前元素个数
            unsigned int m_uiBufferNum; //当前总空间个数
            unsigned int m_uiAllocNum;  //记录分配次数

        private:
        };
        //有序数组
        template <class T, class MemoryManagerClass = Core::DefaultContainerMemoryAllocator>
        class MArrayOrder : public MArray<T, MemoryManagerClass>
        {
        public:
            MArrayOrder(unsigned int uiGrowBy = DEFAULT_GROWBY);
            ~MArrayOrder();
            unsigned int AddElement(const T &Element);

            //用这个函数要注意：如果T是智能指针，参数Element 从指针到智能指针的隐式转换，导致智能指针对象的创建
            //和销毁过程中，reference加1减1，如果原来对象的reference为0，则会销毁对象，导致出错
            unsigned int FindElement(const T &Element);

            void ReSort(unsigned int i);

        protected:
            unsigned int Process(unsigned int uiIndex0, unsigned int uiIndex1, const T &Element);

            unsigned int FindElement(unsigned int uiIndex0, unsigned int uiIndex1, const T &Element);
        };

#include "Array.inl"
    }
}
