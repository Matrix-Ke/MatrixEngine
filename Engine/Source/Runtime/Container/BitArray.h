#pragma once
#include "Container.h"
namespace Matrix
{
	namespace Container
	{
		template<class T>
		class MTXBit
		{
		public:
			enum
			{
				BYTE_SIZE = sizeof(T) * 8
			};
			MTXBit(const MTXBit<T>& Bit)
			{
				m_Member = Bit.m_Member;
			}
			MTXBit()
			{
				m_Member = 0;
			}
			bool operator[] (unsigned int uiIndex)
			{
				int bit = uiIndex % BYTE_SIZE;
				return (((m_Member & (1 << bit)) >> bit) == 1);
			}

			void operator= (const MTXBit<T>& Bit)
			{
				m_Member = Bit.m_Member;
			}
			void Set(unsigned int uiIndex, bool bValue)
			{

				int bit = uiIndex % BYTE_SIZE;


				if (bValue == true)

					m_Member = (m_Member | (1 << bit));
				else

					m_Member = (m_Member & (~(1 << bit)));
			}


			void ClearAll()
			{

				m_Member = 0;
			}


			void SetAll()
			{
				m_Member = 0xFFFFFFFF;
			}

			bool HasValue()
			{
				return m_Member > 0;
			}
			unsigned int GetNum()
			{
				return BYTE_SIZE;
			}
		protected:
			T m_Member;
		};
		class MTXBitArray
		{
		public:
			enum
			{
				BYTE_SIZE = sizeof(unsigned int) * 8
			};
			MTXBitArray(const MTXBitArray& BitArray)
			{
				ENGINE_DELETE(m_pBuffer);
				m_uiSize = BitArray.m_uiSize;
				m_pBuffer = MX_NEW unsigned int[m_uiSize];
				MTXMemcpy(m_pBuffer, BitArray.m_pBuffer, sizeof(unsigned int) * m_uiSize);
			}
			MTXBitArray(unsigned int uiSize = 0)
			{
				m_pBuffer = 0;
				m_uiSize = 0;
				Resize(uiSize);
			}

			~MTXBitArray()
			{
				ENGINE_DELETE(m_pBuffer);
			}


			void Resize(unsigned int uiSize)
			{
				if (uiSize == 0)
				{
					return;
				}
				unsigned int* pNewVector = 0;

				if (uiSize % BYTE_SIZE == 0)
					uiSize = uiSize / BYTE_SIZE;
				else
					uiSize = (uiSize / BYTE_SIZE) + 1;

				pNewVector = MX_NEW unsigned int[uiSize];

				MTXENGINE_ASSERT(pNewVector);

				MTXMemset(pNewVector, 0, uiSize * sizeof(unsigned int));
				unsigned int uiMin;
				if (uiSize < m_uiSize)
					uiMin = uiSize;
				else
					uiMin = m_uiSize;

				for (unsigned int uiIndex = 0; uiIndex < uiMin; uiIndex++)
					pNewVector[uiIndex] = m_pBuffer[uiIndex];

				m_uiSize = uiSize;

				ENGINE_DELETE(m_pBuffer);

				m_pBuffer = pNewVector;

			}


			bool operator[] (unsigned int uiIndex)
			{
				int cell = uiIndex / BYTE_SIZE;
				int bit = uiIndex % BYTE_SIZE;
				return (((m_pBuffer[cell] & (1 << bit)) >> bit) == 1);
			}

			void operator= (const MTXBitArray& BitArray)
			{
				m_uiSize = BitArray.m_uiSize;
				ENGINE_DELETE(m_pBuffer);
				m_pBuffer = MX_NEW unsigned int[m_uiSize];
				MTXMemcpy(m_pBuffer, BitArray.m_pBuffer, m_uiSize * sizeof(unsigned int));
			}
			void Set(unsigned int uiIndex, bool bValue)
			{
				int cell = uiIndex / BYTE_SIZE;

				int bit = uiIndex % BYTE_SIZE;


				if (bValue == true)

					m_pBuffer[cell] = (m_pBuffer[cell] | (1 << bit));
				else

					m_pBuffer[cell] = (m_pBuffer[cell] & (~(1 << bit)));
			}


			void ClearAll()
			{

				for (unsigned int uiIndex = 0; uiIndex < m_uiSize; uiIndex++)
					m_pBuffer[uiIndex] = 0;
			}


			void SetAll()
			{

				for (unsigned int uiIndex = 0; uiIndex < m_uiSize; uiIndex++)
					m_pBuffer[uiIndex] = 0xFFFFFFFF;
			}


			unsigned int Size()
			{
				return m_uiSize * BYTE_SIZE;
			}



			unsigned int GetCell(int uiIndex)
			{
				return m_pBuffer[uiIndex];
			}



			unsigned int* m_pBuffer;

			unsigned int m_uiSize;
		};
	}
}


