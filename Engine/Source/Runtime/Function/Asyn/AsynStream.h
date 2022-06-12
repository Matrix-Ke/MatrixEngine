#pragma once
#include "Stream.h"
namespace Matrix
{
    class MATRIX_FUNCTION_API VSAsynStream : public MStream
    {
    private:
        Container::MArray<ObjectTableType> m_ObjectTable;

    public:
        VSAsynStream();
        virtual bool LoadFromBuffer(unsigned char *pBuffer, unsigned int uiSize);
        void CreateAndRegisterObject();
        void LoadAndLinkOjbect();
        virtual bool ReadResource(VSResourceProxyBasePtr &Resource);
        virtual const MObject *GetObjectByRtti(const VSRtti &Rtti);
        template <typename T>
        friend class VSTResourceJob;
        template <typename CacheType>
        friend class VSCacheResourceJobBase;

    protected:
        void PostLoadObject(MObject *pPostLoadObject);
    };
}