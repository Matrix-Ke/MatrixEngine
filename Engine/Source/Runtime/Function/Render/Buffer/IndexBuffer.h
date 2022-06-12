#pragma once
#include "Object.h"
#include "MemBind.h"
#include "BindLockInterface.h"
#include "DataBuffer.h"
namespace Matrix
{
    class VSStream;
    class MATRIX_FUNCTION_API VSIndexBuffer : public VSMemBind, public VSBindLockInterface
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        virtual ~VSIndexBuffer();
        VSIndexBuffer();
        VSIndexBuffer(unsigned int uiNum, unsigned int uiDT = VSDataBuffer::DT_USHORT);
        bool SetData(VSDataBuffer *pData);

    public:
        virtual void *Lock();
        virtual void UnLock();

        virtual void ClearInfo();
        inline VSDataBuffer *GetIndexData() const { return m_pData; }

        unsigned int GetNum() const;
        virtual unsigned int GetByteSize() const;
        inline void *GetLockDataPtr() const
        {
            return m_pLockData;
        }
        inline unsigned int GetDataType() const
        {
            return m_uiDT;
        }

    protected:
        virtual bool OnLoadResource(VSResourceIdentifier *&pID);
        VSDataBufferPtr m_pData;
        unsigned int m_uiNum;
        unsigned int m_uiDT;
        void *m_pLockData;
    };
    DECLARE_Ptr(VSIndexBuffer);
    VSTYPE_MARCO(VSIndexBuffer);
}