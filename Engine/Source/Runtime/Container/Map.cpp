#include "Map.h"
using namespace Matrix::Container;


template<class KEY, class VALUE, class MTXMemManagerClass>
MTXMap<KEY, VALUE, MTXMemManagerClass>::~MTXMap()
{
	Delete(m_pBuffer, m_uiCurUse);
}

template<class KEY, class VALUE, class MTXMemManagerClass>
MTXMap<KEY, VALUE, MTXMemManagerClass>::MTXMap(unsigned int uiGrowBy)
{
	MTXENGINE_ASSERT(uiGrowBy);
	m_uiGrowBy = uiGrowBy;
	m_pBuffer = NULL;
	m_uiCurUse = 0;
	m_uiBufferNum = 0;
	m_uiAllocNum = 0;
}
template<class KEY, class VALUE, class MTXMemManagerClass>
void MTXMap<KEY, VALUE, MTXMemManagerClass>::SetBufferNum(unsigned int uiBufferNum)
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
			MATRIX_NEW(m_pBuffer + i) MapElement<KEY, VALUE>();
		}
	}

}
template<class KEY, class VALUE, class MTXMemManagerClass>
void MTXMap<KEY, VALUE, MTXMemManagerClass>::AddBufferNum(unsigned int uiBufferNum)
{
	if (uiBufferNum)
	{
		//如果经常需要分配内存，就把m_uiGrowBy逐渐增长
		m_uiAllocNum++;
		m_uiGrowBy = m_uiAllocNum * m_uiGrowBy;

		MapElement<KEY, VALUE>* pBuffer = NULL;

		pBuffer = New(m_uiBufferNum + uiBufferNum);
		if (!pBuffer)
			return;

		if (m_pBuffer && m_uiCurUse)
		{
			for (unsigned int i = 0; i < m_uiCurUse; i++)
			{
				MATRIX_NEW(pBuffer + i) MapElement<KEY, VALUE>(m_pBuffer[i]);
			}

		}
		Delete(m_pBuffer, m_uiCurUse);
		m_uiBufferNum = m_uiBufferNum + uiBufferNum;
		m_pBuffer = pBuffer;
	}

}
template<class KEY, class VALUE, class MTXMemManagerClass>
inline unsigned int MTXMap<KEY, VALUE, MTXMemManagerClass>::GetNum()const
{
	return m_uiCurUse;
}
template<class KEY, class VALUE, class MTXMemManagerClass>
inline unsigned int MTXMap<KEY, VALUE, MTXMemManagerClass>::GetBufferNum()const
{
	return m_uiBufferNum;
}
template<class KEY, class VALUE, class MTXMemManagerClass>
inline MapElement<KEY, VALUE>* MTXMap<KEY, VALUE, MTXMemManagerClass>::GetBuffer()const
{
	return m_pBuffer;
}
template<class KEY, class VALUE, class MTXMemManagerClass>
inline void MTXMap<KEY, VALUE, MTXMemManagerClass>::SetGrowBy(unsigned int uiGrowBy)
{
	m_uiGrowBy = uiGrowBy;
}
template<class KEY, class VALUE, class MTXMemManagerClass>
inline unsigned int MTXMap<KEY, VALUE, MTXMemManagerClass>::GetSize()const
{
	return sizeof(unsigned int) * 4 + sizeof(MapElement<KEY, VALUE> *) + sizeof(MapElement<KEY, VALUE>) * m_uiBufferNum;
}
template<class KEY, class VALUE, class MTXMemManagerClass>
unsigned int MTXMap<KEY, VALUE, MTXMemManagerClass>::AddElement(const KEY& Key, const VALUE& Value)
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
	MATRIX_NEW(m_pBuffer + m_uiCurUse) MapElement<KEY, VALUE>(Element);
	m_uiCurUse++;
	return m_uiCurUse - 1;
}
template<class KEY, class VALUE, class MTXMemManagerClass>
template<class KEY1, class VALUE1>
unsigned int MTXMap<KEY, VALUE, MTXMemManagerClass>::AddElement(const MapElement<KEY1, VALUE1>& Element)
{
	if (Find(Element.Key) != m_uiCurUse)
		return -1;
	if (m_uiCurUse == m_uiBufferNum)
	{
		AddBufferNum(m_uiGrowBy);
	}
	MATRIX_NEW(m_pBuffer + m_uiCurUse) MapElement<KEY, VALUE>(Element);
	m_uiCurUse++;
	return m_uiCurUse - 1;
}
template<class KEY, class VALUE, class MTXMemManagerClass>
template<class KEY1, class VALUE1, class MTXMemManagerClass1>
void MTXMap<KEY, VALUE, MTXMemManagerClass>::AddElement(const MTXMap<KEY1, VALUE1, MTXMemManagerClass1>& Map, unsigned int uiBegin, unsigned int uiEnd)
{
	MTXENGINE_ASSERT(uiBegin <= uiEnd);

	MTXENGINE_ASSERT(uiEnd < Map.GetNum());


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
template<class KEY, class VALUE, class MTXMemManagerClass>
void MTXMap<KEY, VALUE, MTXMemManagerClass>::operator= (const MTXMap<KEY, VALUE, MTXMemManagerClass>& Map)
{
	if (m_uiBufferNum >= Map.GetNum())
	{
		Clear();
		m_uiCurUse = Map.GetNum();
		MapElement<KEY, VALUE>* pBuffer = Map.GetBuffer();
		for (unsigned int i = 0; i < m_uiCurUse; i++)
		{
			MATRIX_NEW(m_pBuffer + i) MapElement<KEY, VALUE>(pBuffer[i]);
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
		MapElement<KEY, VALUE>* pBuffer = Map.GetBuffer();
		for (unsigned int i = 0; i < m_uiCurUse; i++)
		{
			MATRIX_NEW(m_pBuffer + i) MapElement<KEY, VALUE>(pBuffer[i]);
		}


	}
	return;
}

template<class KEY, class VALUE, class MTXMemManagerClass>
void MTXMap<KEY, VALUE, MTXMemManagerClass>::Clear()
{

	for (unsigned int i = 0; i < m_uiCurUse; i++)
	{
		m_pBuffer[i].~MapElement<KEY, VALUE>();
	}

	m_uiCurUse = 0;

}
template<class KEY, class VALUE, class MTXMemManagerClass>
void MTXMap<KEY, VALUE, MTXMemManagerClass>::Destroy()
{
	Clear();
	//MTXENGINE_DELETE(m_pBuffer);
	Delete(m_pBuffer, m_uiCurUse);
}
template<class KEY, class VALUE, class MTXMemManagerClass>
MapElement<KEY, VALUE>& MTXMap<KEY, VALUE, MTXMemManagerClass>::operator[] (unsigned int i)const
{

	MTXENGINE_ASSERT(i < m_uiBufferNum);
	return m_pBuffer[i];


}
template<class KEY, class VALUE, class MTXMemManagerClass>
void MTXMap<KEY, VALUE, MTXMemManagerClass>::Erase(unsigned int i)
{
	Erase(i, i);
}
template<class KEY, class VALUE, class MTXMemManagerClass>
void MTXMap<KEY, VALUE, MTXMemManagerClass>::Erase(unsigned int uiBegin, unsigned int uiEnd)
{
	MTXENGINE_ASSERT(uiEnd < m_uiCurUse);

	MTXENGINE_ASSERT(uiBegin <= uiEnd);

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
			MATRIX_NEW(m_pBuffer + uiBegin + k) MapElement<KEY, VALUE>(m_pBuffer[uiMoveIndex]);
			m_pBuffer[uiMoveIndex].~MapElement<KEY, VALUE>();
		}


	}
	m_uiCurUse -= ((uiEnd - uiBegin) + 1);
}

template<class KEY, class VALUE, class MTXMemManagerClass>
template <class N>
void MTXMap<KEY, VALUE, MTXMemManagerClass>::Sort(unsigned int uiBegin, unsigned int uiEnd, N& Compare)
{
	MTXENGINE_ASSERT(uiEnd < m_uiCurUse);
	MTXENGINE_ASSERT(uiBegin <= uiEnd);

	//归并排序 复杂度 nlogn
	MapElement<KEY, VALUE>* pBuffer = New(uiEnd - uiBegin + 1);
	for (unsigned int i = 0; i < uiEnd - uiBegin + 1; i++)
	{
		MATRIX_NEW(pBuffer + i) MapElement<KEY, VALUE>();
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
template<class KEY, class VALUE, class MTXMemManagerClass>
template <class N>
void MTXMap<KEY, VALUE, MTXMemManagerClass>::SortAll(N& Compare)
{
	if (!m_uiCurUse)
	{
		return;
	}
	Sort(0, m_uiCurUse, N);
}
template<class KEY, class VALUE, class MTXMemManagerClass>
void MTXMap<KEY, VALUE, MTXMemManagerClass>::SortAll()
{
	if (!m_uiCurUse)
	{
		return;
	}
	Sort(0, m_uiCurUse);
}
template<class KEY, class VALUE, class MTXMemManagerClass>
void MTXMap<KEY, VALUE, MTXMemManagerClass>::Sort(unsigned int uiBegin, unsigned int uiEnd)
{
	MTXENGINE_ASSERT(uiEnd < m_uiCurUse);
	MTXENGINE_ASSERT(uiBegin <= uiEnd);
	//归并排序 复杂度 nlogn
	MapElement<KEY, VALUE>* pBuffer = New(uiEnd - uiBegin + 1);
	for (unsigned int i = 0; i < uiEnd - uiBegin + 1; i++)
	{
		MATRIX_NEW(pBuffer + i) MapElement<KEY, VALUE>();
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

template<class KEY, class VALUE, class MTXMemManagerClass>
unsigned int MTXMap<KEY, VALUE, MTXMemManagerClass>::Find(const KEY& Key)const
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
template<class KEY, class VALUE, class MTXMemManagerClass>
unsigned int MTXMap<KEY, VALUE, MTXMemManagerClass>::FindValueIndex(const VALUE& Value)const
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
template<class KEY, class VALUE, class MTXMemManagerClass>
MTXMapOrder<KEY, VALUE, MTXMemManagerClass>::~MTXMapOrder()
{

}

template<class KEY, class VALUE, class MTXMemManagerClass>
MTXMapOrder<KEY, VALUE, MTXMemManagerClass>::MTXMapOrder(unsigned int uiGrowBy)
{


}
template<class KEY, class VALUE, class MTXMemManagerClass>
unsigned int MTXMapOrder<KEY, VALUE, MTXMemManagerClass>::FindElement(unsigned int uiIndex0, unsigned int uiIndex1, const KEY& Key)const
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
template<class KEY, class VALUE, class MTXMemManagerClass>
template<class KEY1, class VALUE1>
unsigned int MTXMapOrder<KEY, VALUE, MTXMemManagerClass>::Process(unsigned int uiIndex0, unsigned int uiIndex1, const MapElement<KEY1, VALUE1>& Element)
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
template<class KEY, class VALUE, class MTXMemManagerClass>
unsigned int MTXMapOrder<KEY, VALUE, MTXMemManagerClass>::AddElement(const KEY& Key, const VALUE& Value)
{
	MapElement<KEY, VALUE> Element;
	Element.Key = Key;
	Element.Value = Value;
	return AddElement(Element);
}
template<class KEY, class VALUE, class MTXMemManagerClass>
template<class KEY1, class VALUE1>
unsigned int MTXMapOrder<KEY, VALUE, MTXMemManagerClass>::AddElement(const MapElement<KEY1, VALUE1>& Element)
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
		MATRIX_NEW(m_pBuffer + uiIndex) MapElement<KEY, VALUE>(Element);

	}
	else
	{
		MATRIX_NEW(m_pBuffer + m_uiCurUse) MapElement<KEY, VALUE>(m_pBuffer[m_uiCurUse - 1]);
		for (int i = (int)m_uiCurUse - 2; i >= (int)uiIndex; i--)
		{
			m_pBuffer[i + 1] = m_pBuffer[i];

		}
		m_pBuffer[uiIndex] = Element;
	}

	m_uiCurUse++;
	return uiIndex;
}
template<class KEY, class VALUE, class MTXMemManagerClass>
unsigned int MTXMapOrder<KEY, VALUE, MTXMemManagerClass>::Find(const KEY& Key)const
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
template<class KEY, class VALUE, class MTXMemManagerClass>
template<class KEY1, class VALUE1, class MTXMemManagerClass1>
void MTXMapOrder<KEY, VALUE, MTXMemManagerClass>::AddElement(const MTXMap<KEY1, VALUE1, MTXMemManagerClass1>& Map, unsigned int uiBegin, unsigned int uiEnd)
{
	return MTXMap<KEY, VALUE, MTXMemManagerClass>::AddElement(Map, uiBegin, uiEnd);
}