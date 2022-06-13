#pragma once
#include "MemManager.h"
#include "Math.h"
#include "Core/Object.h"
#include "Render/Buffer/BufferResource.h"
namespace Matrix
{
    class MStream;
    class MATRIX_FUNCTION_API VSUserBuffer : public MObject
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        VSUserBuffer(const VSUsedName &Name, unsigned int uiDataType, unsigned int uiRegisterIndex, unsigned int uiRegisterNum);
        virtual ~VSUserBuffer();

        inline unsigned int GetDataType() const
        {
            return m_uiDT;
        }

        inline const VSUsedName &GetName() const
        {
            return m_Name;
        }
        inline void SetBufferResource(VSBufferResource *pBufferResource, unsigned int uiIndex = 0)
        {
            if (uiIndex >= m_uiRegisterNum)
            {
                return;
            }
            m_pBufferResourceArray[uiIndex] = pBufferResource;
        }
        inline VSBufferResource *GetBufferResource(unsigned int uiIndex) const
        {
            return m_pBufferResourceArray[uiIndex];
        }
        inline unsigned int GetRegisterIndex() const
        {
            return m_uiRegisterIndex;
        }
        inline unsigned int GetRegisterNum() const
        {
            return m_uiRegisterNum;
        }
        virtual bool PostLoad(MStream *pStream);
        virtual bool PostClone(MObject *pObjectSrc);

    protected:
        friend class VSRenderer;
        VSUserBuffer();

    private:
        unsigned int m_uiDT;
        Container::MArray<VSBufferResourcePtr> m_pBufferResourceArray;
        VSUsedName m_Name;
        unsigned int m_uiRegisterIndex;
        unsigned int m_uiRegisterNum;
    };
    VSTYPE_MARCO(VSUserBuffer);
    DECLARE_Ptr(VSUserBuffer);
}
