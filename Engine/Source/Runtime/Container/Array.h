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
            enum // Ĭ����������
            {
                DEFAULT_GROWBY = 10
            };
            MArray(unsigned int uiGrowBy = DEFAULT_GROWBY);
            ~MArray();
            MArray(const MArray<T, MemoryManagerClass> &Array);
            //����Ԫ�ظ���������ʼ��
            void SetBufferNum(unsigned int uiBufferNum);
            //��� uiBufferNum ��Ԫ�أ�û�г�ʼ��
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

            //��Compare == 0 ����
            template <class N>
            void Sort(unsigned int uiBegin, unsigned int uiEnd, N &Compare);
            template <class N>
            void SortAll(N &Compare);
            //��������
            void Sort(unsigned int uiBegin, unsigned int uiEnd);
            void SortAll();
            void Destroy();
            //���������Ҫע�⣺���T������ָ�룬����Element ��ָ�뵽����ָ�����ʽת������������ָ�����Ĵ���
            //�����ٹ����У�reference��1��1�����ԭ�������referenceΪ0��������ٶ��󣬵��³���
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
            T *m_pBuffer;               //�ռ��ַָ��
            unsigned int m_uiGrowBy;    //��������
            unsigned int m_uiCurUse;    //��ǰԪ�ظ���
            unsigned int m_uiBufferNum; //��ǰ�ܿռ����
            unsigned int m_uiAllocNum;  //��¼�������

        private:
        };
        //��������
        template <class T, class MemoryManagerClass = Core::DefaultContainerMemoryAllocator>
        class MArrayOrder : public MArray<T, MemoryManagerClass>
        {
        public:
            MArrayOrder(unsigned int uiGrowBy = DEFAULT_GROWBY);
            ~MArrayOrder();
            unsigned int AddElement(const T &Element);

            //���������Ҫע�⣺���T������ָ�룬����Element ��ָ�뵽����ָ�����ʽת������������ָ�����Ĵ���
            //�����ٹ����У�reference��1��1�����ԭ�������referenceΪ0��������ٶ��󣬵��³���
            unsigned int FindElement(const T &Element);

            void ReSort(unsigned int i);

        protected:
            unsigned int Process(unsigned int uiIndex0, unsigned int uiIndex1, const T &Element);

            unsigned int FindElement(unsigned int uiIndex0, unsigned int uiIndex1, const T &Element);
        };

#include "Array.inl"
    }
}
