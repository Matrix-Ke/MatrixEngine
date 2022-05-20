#include "Map.h"
using namespace Matrix::Container;

template <class KEY, class VALUE, class MMemManagerClass>
MMap<KEY, VALUE, MMemManagerClass>::~MMap()
{
    Delete(m_pBuffer, m_uiCurUse);
}

template <class KEY, class VALUE, class MMemManagerClass>
MMap<KEY, VALUE, MMemManagerClass>::MMap(unsigned int uiGrowBy)
{
    MX_ENGINE_ASSERT(uiGrowBy);
    m_uiGrowBy = uiGrowBy;
    m_pBuffer = NULL;
    m_uiCurUse = 0;
    m_uiBufferNum = 0;
    m_uiAllocNum = 0;
}
template <class KEY, class VALUE, class MMemManagerClass>
void MMap<KEY, VALUE, MMemManagerClass>::SetBufferNum(unsigned int uiBufferNum)
{
    if (uiBufferNum != m_uiBufferNum)
    {
        Delete(m_pBuffer, m_uiCurUse);
        m_uiBufferNum = uiBufferNum;

        m_pBuffer = New(uiBufferNum);

        if (!m_pBuffer)
            return;
        m_uiCurUse = uiBufferNum;
        for (unsigned int i = 0; i < m_uiBufferNum; i++)
        {
            MX_NEW(m_pBuffer + i)
            MapElement<KEY, VALUE>();
        }
    }
}
template <class KEY, class VALUE, class MMemManagerClass>
void MMap<KEY, VALUE, MMemManagerClass>::AddBufferNum(unsigned int uiBufferNum)
{
    if (uiBufferNum)
    {
        //如果经常需要分配内存，就把m_uiGrowBy逐渐增长
        m_uiAllocNum++;
        m_uiGrowBy = m_uiAllocNum * m_uiGrowBy;

        MapElement<KEY, VALUE> *pBuffer = NULL;

        pBuffer = New(m_uiBufferNum + uiBufferNum);
        if (!pBuffer)
            return;

        if (m_pBuffer && m_uiCurUse)
        {
            for (unsigned int i = 0; i < m_uiCurUse; i++)
            {
                MX_NEW(pBuffer + i)
                MapElement<KEY, VALUE>(m_pBuffer[i]);
            }
        }
        Delete(m_pBuffer, m_uiCurUse);
        m_uiBufferNum = m_uiBufferNum + uiBufferNum;
        m_pBuffer = pBuffer;
    }
}
template <class KEY, class VALUE, class MMemManagerClass>
inline unsigned int MMap<KEY, VALUE, MMemManagerClass>::GetNum() const
{
    return m_uiCurUse;
}
template <class KEY, class VALUE, class MMemManagerClass>
inline unsigned int MMap<KEY, VALUE, MMemManagerClass>::GetBufferNum() const
{
    return m_uiBufferNum;
}
template <class KEY, class VALUE, class MMemManagerClass>
inline MapElement<KEY, VALUE> *MMap<KEY, VALUE, MMemManagerClass>::GetBuffer() const
{
    return m_pBuffer;
}
template <class KEY, class VALUE, class MMemManagerClass>
inline void MMap<KEY, VALUE, MMemManagerClass>::SetGrowBy(unsigned int uiGrowBy)
{
    m_uiGrowBy = uiGrowBy;
}
template <class KEY, class VALUE, class MMemManagerClass>
inline unsigned int MMap<KEY, VALUE, MMemManagerClass>::GetSize() const
{
    return sizeof(unsigned int) * 4 + sizeof(MapElement<KEY, VALUE> *) + sizeof(MapElement<KEY, VALUE>) * m_uiBufferNum;
}
template <class KEY, class VALUE, class MMemManagerClass>
unsigned int MMap<KEY, VALUE, MMemManagerClass>::AddElement(const KEY &Key, const VALUE &Value)
{
    if (Find(Key) != m_uiCurUse)
        return -1;
    if (m_uiCurUse == m_uiBufferNum)
    {
        AddBufferNum(m_uiGrowBy);
    }
    MapElement<KEY, VALUE> Element;
    Element.Key = Key;
    Element.Value = Value;
    MX_NEW(m_pBuffer + m_uiCurUse)
    MapElement<KEY, VALUE>(Element);
    m_uiCurUse++;
    return m_uiCurUse - 1;
}
template <class KEY, class VALUE, class MMemManagerClass>
template <class KEY1, class VALUE1>
unsigned int MMap<KEY, VALUE, MMemManagerClass>::AddElement(const MapElement<KEY1, VALUE1> &Element)
{
    if (Find(Element.Key) != m_uiCurUse)
        return -1;
    if (m_uiCurUse == m_uiBufferNum)
    {
        AddBufferNum(m_uiGrowBy);
    }
    MX_NEW(m_pBuffer + m_uiCurUse)
    MapElement<KEY, VALUE>(Element);
    m_uiCurUse++;
    return m_uiCurUse - 1;
}
template <class KEY, class VALUE, class MMemManagerClass>
template <class KEY1, class VALUE1, class MXMemManagerClass1>
void MMap<KEY, VALUE, MMemManagerClass>::AddElement(const MMap<KEY1, VALUE1, MXMemManagerClass1> &Map, unsigned int uiBegin, unsigned int uiEnd)
{
    MX_ENGINE_ASSERT(uiBegin <= uiEnd);

    MX_ENGINE_ASSERT(uiEnd < Map.GetNum());

    unsigned int iAddNum = uiEnd - uiBegin + 1;
    int iHaveNum = m_uiBufferNum - m_uiCurUse;

    int iNeedNum = iHaveNum - iAddNum;

    if (iNeedNum < 0)
    {
        if (m_uiGrowBy)
        {
            iNeedNum = -iNeedNum;
            if ((unsigned int)iNeedNum < m_uiGrowBy)
                AddBufferNum(m_uiGrowBy);
            else
            {
                AddBufferNum(iNeedNum);
            }
        }
        else
        {
            iAddNum = iHaveNum;
        }
    }

    for (unsigned int i = 0; i < iAddNum; i++)
    {
        AddElement(Map[uiBegin + i]);
    }
}
template <class KEY, class VALUE, class MMemManagerClass>
void MMap<KEY, VALUE, MMemManagerClass>::operator=(const MMap<KEY, VALUE, MMemManagerClass> &Map)
{
    if (m_uiBufferNum >= Map.GetNum())
    {
        Clear();
        m_uiCurUse = Map.GetNum();
        MapElement<KEY, VALUE> *pBuffer = Map.GetBuffer();
        for (unsigned int i = 0; i < m_uiCurUse; i++)
        {
            MX_NEW(m_pBuffer + i)
            MapElement<KEY, VALUE>(pBuffer[i]);
        }
    }
    else
    {
        Delete(m_pBuffer, m_uiCurUse);
        m_uiBufferNum = Map.GetBufferNum();

        m_uiCurUse = Map.GetNum();

        m_pBuffer = New(m_uiBufferNum);
        if (!m_pBuffer)
            return;
        MapElement<KEY, VALUE> *pBuffer = Map.GetBuffer();
        for (unsigned int i = 0; i < m_uiCurUse; i++)
        {
            MX_NEW(m_pBuffer + i)
            MapElement<KEY, VALUE>(pBuffer[i]);
        }
    }
    return;
}

template <class KEY, class VALUE, class MMemManagerClass>
void MMap<KEY, VALUE, MMemManagerClass>::Clear()
{

    for (unsigned int i = 0; i < m_uiCurUse; i++)
    {
        m_pBuffer[i].~MapElement<KEY, VALUE>();
    }

    m_uiCurUse = 0;
}
template <class KEY, class VALUE, class MMemManagerClass>
void MMap<KEY, VALUE, MMemManagerClass>::Destroy()
{
    Clear();
    // MXENGINE_DELETE(m_pBuffer);
    Delete(m_pBuffer, m_uiCurUse);
}
template <class KEY, class VALUE, class MMemManagerClass>
MapElement<KEY, VALUE> &MMap<KEY, VALUE, MMemManagerClass>::operator[](unsigned int i) const
{

    MX_ENGINE_ASSERT(i < m_uiBufferNum);
    return m_pBuffer[i];
}
template <class KEY, class VALUE, class MMemManagerClass>
void MMap<KEY, VALUE, MMemManagerClass>::Erase(unsigned int i)
{
    Erase(i, i);
}
template <class KEY, class VALUE, class MMemManagerClass>
void MMap<KEY, VALUE, MMemManagerClass>::Erase(unsigned int uiBegin, unsigned int uiEnd)
{
    MX_ENGINE_ASSERT(uiEnd < m_uiCurUse);

    MX_ENGINE_ASSERT(uiBegin <= uiEnd);

    unsigned int k;
    unsigned int uiMoveNum = m_uiCurUse - 1 - uiEnd;
    unsigned int uiMoveIndex;
    for (unsigned int uiDelete = uiBegin; uiDelete <= uiEnd; uiDelete++)
    {
        m_pBuffer[uiDelete].~MapElement<KEY, VALUE>();
    }
    for (k = 0; k < uiMoveNum; k++)
    {
        uiMoveIndex = uiEnd + k + 1;
        if (uiMoveIndex < m_uiCurUse)
        {
            MX_NEW(m_pBuffer + uiBegin + k)
            MapElement<KEY, VALUE>(m_pBuffer[uiMoveIndex]);
            m_pBuffer[uiMoveIndex].~MapElement<KEY, VALUE>();
        }
    }
    m_uiCurUse -= ((uiEnd - uiBegin) + 1);
}

template <class KEY, class VALUE, class MMemManagerClass>
template <class N>
void MMap<KEY, VALUE, MMemManagerClass>::Sort(unsigned int uiBegin, unsigned int uiEnd, N &Compare)
{
    MX_ENGINE_ASSERT(uiEnd < m_uiCurUse);
    MX_ENGINE_ASSERT(uiBegin <= uiEnd);

    //归并排序 复杂度 nlogn
    MapElement<KEY, VALUE> *pBuffer = New(uiEnd - uiBegin + 1);
    for (unsigned int i = 0; i < uiEnd - uiBegin + 1; i++)
    {
        MX_NEW(pBuffer + i)
        MapElement<KEY, VALUE>();
    }
    MergeSort(m_pBuffer + uiBegin, pBuffer, uiEnd - uiBegin + 1, Compare);
    Delete(pBuffer, uiEnd - uiBegin + 1);
    //	冒泡排序 复杂度 n(n+1)/2
    // 	for (unsigned int i = uiBegin ; i < uiEnd; i++)
    // 	{
    // 		for (unsigned int j = uiBegin ; j < uiEnd - uiBegin - i; j++)
    // 		{
    // 			if(Compare(m_pBuffer[j],m_pBuffer[j + 1]) == 0)
    // 			{
    // 				Swap(m_pBuffer[j],m_pBuffer[j + 1]);
    // 			}
    // 		}
    // 	}
}
template <class KEY, class VALUE, class MMemManagerClass>
template <class N>
void MMap<KEY, VALUE, MMemManagerClass>::SortAll(N &Compare)
{
    if (!m_uiCurUse)
    {
        return;
    }
    Sort(0, m_uiCurUse, N);
}
template <class KEY, class VALUE, class MMemManagerClass>
void MMap<KEY, VALUE, MMemManagerClass>::SortAll()
{
    if (!m_uiCurUse)
    {
        return;
    }
    Sort(0, m_uiCurUse);
}
template <class KEY, class VALUE, class MMemManagerClass>
void MMap<KEY, VALUE, MMemManagerClass>::Sort(unsigned int uiBegin, unsigned int uiEnd)
{
    MX_ENGINE_ASSERT(uiEnd < m_uiCurUse);
    MX_ENGINE_ASSERT(uiBegin <= uiEnd);
    //归并排序 复杂度 nlogn
    MapElement<KEY, VALUE> *pBuffer = New(uiEnd - uiBegin + 1);
    for (unsigned int i = 0; i < uiEnd - uiBegin + 1; i++)
    {
        MX_NEW(pBuffer + i)
        MapElement<KEY, VALUE>();
    }
    MergeSort(m_pBuffer + uiBegin, pBuffer, uiEnd - uiBegin + 1);
    Delete(pBuffer, uiEnd - uiBegin + 1);
    //	冒泡排序 复杂度 n(n+1)/2
    // 	for (unsigned int i = uiBegin ; i < uiEnd; i++)
    // 	{
    // 		for (unsigned int j = uiBegin ; j < uiEnd - uiBegin - i; j++)
    // 		{
    // 			if(m_pBuffer[j].Key > m_pBuffer[j + 1].Key)
    // 			{
    // 				Swap(m_pBuffer[j],m_pBuffer[j + 1]);
    // 			}
    // 		}
    // 	}
}

template <class KEY, class VALUE, class MMemManagerClass>
unsigned int MMap<KEY, VALUE, MMemManagerClass>::Find(const KEY &Key) const
{
    unsigned int i = 0;
    for (i = 0; i < m_uiCurUse; i++)
    {
        if (m_pBuffer[i].Key == Key)
        {
            break;
        }
    }
    return i;
}
template <class KEY, class VALUE, class MMemManagerClass>
unsigned int MMap<KEY, VALUE, MMemManagerClass>::FindValueIndex(const VALUE &Value) const
{
    unsigned int i = 0;
    for (i = 0; i < m_uiCurUse; i++)
    {
        if (m_pBuffer[i].Value == Value)
        {
            break;
        }
    }
    return i;
}
template <class KEY, class VALUE, class MMemManagerClass>
MXMapOrder<KEY, VALUE, MMemManagerClass>::~MXMapOrder()
{
}

template <class KEY, class VALUE, class MMemManagerClass>
MXMapOrder<KEY, VALUE, MMemManagerClass>::MXMapOrder(unsigned int uiGrowBy)
{
}
template <class KEY, class VALUE, class MMemManagerClass>
unsigned int MXMapOrder<KEY, VALUE, MMemManagerClass>::FindElement(unsigned int uiIndex0, unsigned int uiIndex1, const KEY &Key) const
{
    if (uiIndex0 == uiIndex1)
    {
        if (m_pBuffer[uiIndex0].Key == Key)
        {
            return uiIndex0;
        }
        else
        {
            return m_uiCurUse;
        }
    }
    else if (uiIndex1 - uiIndex0 == 1)
    {
        if (m_pBuffer[uiIndex0].Key == Key)
        {
            return uiIndex0;
        }
        else if (m_pBuffer[uiIndex1].Key == Key)
        {
            return uiIndex1;
        }
        else
        {
            return m_uiCurUse;
        }
    }
    else
    {
        unsigned int uiIndex = (uiIndex0 + uiIndex1) >> 1;
        if (m_pBuffer[uiIndex].Key == Key)
        {
            return uiIndex;
        }
        else if (m_pBuffer[uiIndex].Key > Key)
        {
            return FindElement(uiIndex0, uiIndex, Key);
        }
        else
        {
            return FindElement(uiIndex, uiIndex1, Key);
        }
    }
}
template <class KEY, class VALUE, class MMemManagerClass>
template <class KEY1, class VALUE1>
unsigned int MXMapOrder<KEY, VALUE, MMemManagerClass>::Process(unsigned int uiIndex0, unsigned int uiIndex1, const MapElement<KEY1, VALUE1> &Element)
{
    if (uiIndex0 == uiIndex1)
    {
        return uiIndex0;
    }
    else if (uiIndex1 - uiIndex0 == 1)
    {
        return uiIndex1;
    }
    else
    {
        unsigned int uiIndex = (uiIndex0 + uiIndex1) >> 1;
        if (m_pBuffer[uiIndex].Key == Element.Key)
        {
            return uiIndex;
        }
        else if (m_pBuffer[uiIndex].Key > Element.Key)
        {
            return Process(uiIndex0, uiIndex, Element);
        }
        else
        {
            return Process(uiIndex, uiIndex1, Element);
        }
    }
}
template <class KEY, class VALUE, class MMemManagerClass>
unsigned int MXMapOrder<KEY, VALUE, MMemManagerClass>::AddElement(const KEY &Key, const VALUE &Value)
{
    MapElement<KEY, VALUE> Element;
    Element.Key = Key;
    Element.Value = Value;
    return AddElement(Element);
}
template <class KEY, class VALUE, class MMemManagerClass>
template <class KEY1, class VALUE1>
unsigned int MXMapOrder<KEY, VALUE, MMemManagerClass>::AddElement(const MapElement<KEY1, VALUE1> &Element)
{
    if (Find(Element.Key) != m_uiCurUse)
        return -1;
    if (m_uiCurUse == m_uiBufferNum)
    {
        if (!m_uiGrowBy)
            return -1;
        AddBufferNum(m_uiGrowBy);
    }

    unsigned int uiIndex;
    if (m_uiCurUse == 0)
    {
        uiIndex = 0;
    }
    else if (m_uiCurUse == 1)
    {
        if (m_pBuffer[0].Key > Element.Key)
        {
            uiIndex = 0;
        }
        else
        {
            uiIndex = 1;
        }
    }
    else if (m_pBuffer[0].Key > Element.Key)
    {
        uiIndex = 0;
    }
    else if (Element.Key > m_pBuffer[m_uiCurUse - 1].Key)
    {
        uiIndex = m_uiCurUse;
    }
    else
    {
        uiIndex = Process(0, m_uiCurUse - 1, Element);
    }
    if (m_uiCurUse == uiIndex)
    {
        MX_NEW(m_pBuffer + uiIndex)
        MapElement<KEY, VALUE>(Element);
    }
    else
    {
        MX_NEW(m_pBuffer + m_uiCurUse)
        MapElement<KEY, VALUE>(m_pBuffer[m_uiCurUse - 1]);
        for (int i = (int)m_uiCurUse - 2; i >= (int)uiIndex; i--)
        {
            m_pBuffer[i + 1] = m_pBuffer[i];
        }
        m_pBuffer[uiIndex] = Element;
    }

    m_uiCurUse++;
    return uiIndex;
}
template <class KEY, class VALUE, class MMemManagerClass>
unsigned int MXMapOrder<KEY, VALUE, MMemManagerClass>::Find(const KEY &Key) const
{
    if (m_uiCurUse)
    {
        if (m_pBuffer[0].Key > Key)
        {
            return m_uiCurUse;
        }
        else if (Key > m_pBuffer[m_uiCurUse - 1].Key)
        {
            return m_uiCurUse;
        }
        else
        {
            return FindElement(0, m_uiCurUse - 1, Key);
        }
    }
    else
    {
        return m_uiCurUse;
    }
}
template <class KEY, class VALUE, class MMemManagerClass>
template <class KEY1, class VALUE1, class MXMemManagerClass1>
void MXMapOrder<KEY, VALUE, MMemManagerClass>::AddElement(const MMap<KEY1, VALUE1, MXMemManagerClass1> &Map, unsigned int uiBegin, unsigned int uiEnd)
{
    return MMap<KEY, VALUE, MMemManagerClass>::AddElement(Map, uiBegin, uiEnd);
}