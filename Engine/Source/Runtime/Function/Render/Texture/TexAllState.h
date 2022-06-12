#pragma once
#include "Texture.h"
#include "Resource.h"
#include "SamplerState.h"
#include "String.h"
namespace Matrix
{
    class MStream;
    class MATRIX_FUNCTION_API VSTexAllState : public MObject, public VSResource
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;

    public:
        virtual ~VSTexAllState();
        VSTexAllState();
        DECLARE_INITIAL

        static bool InitialDefaultState();
        static bool TerminalDefaultState();

        void SetTexture(VSTexture *pTexture);
        inline VSTexture *GetTexture() const
        {
            return m_pTex;
        }
        virtual unsigned int GetCurStreamLevel() const;

    protected:
        VSTexturePtr m_pTex;
        VSSamplerDesc m_SamplerDesc;
        VSSamplerStatePtr m_pSamplerState;
        bool m_bSRGB;
        bool m_bNormal;
        bool m_bMip;
        unsigned int m_uiArraySize;
        unsigned int m_uiFormatType;
        unsigned int m_uiWidth;
        unsigned int m_uiHeight;
        unsigned int m_uiLength;
        Container::MArray<unsigned char> m_SourceData;

    protected:
        static VSPointer<VSTexAllState> ms_pOrenNayarLookUpTable;

    public:
        friend class VSResourceManager;
        friend class VSRenderer;
        inline bool GetSRGB() const
        {
            return m_bSRGB;
        }
        inline unsigned int GetWidth() const
        {
            return m_uiWidth;
        }
        inline unsigned int GetHeight() const
        {
            return m_uiHeight;
        }
        inline unsigned int GetLength() const
        {
            return m_uiLength;
        }
        inline unsigned int GetArraySize() const
        {
            return m_uiArraySize;
        }
        inline unsigned int GetFormatType() const
        {
            return m_uiFormatType;
        }
        void SetSRGBEable(bool bEnable);

        static const VSTexAllState *GetOrenNayarLookUpTable()
        {
            return ms_pOrenNayarLookUpTable;
        }
        void SetSamplerState(VSSamplerState *pSamplerState)
        {
            if (!pSamplerState)
            {
                pSamplerState = (VSSamplerState *)VSSamplerState::GetDefault();
            }
            if (m_pSamplerState != pSamplerState)
            {
                m_pSamplerState = pSamplerState;
                m_SamplerDesc = pSamplerState->GetSamplerDesc();
            }
        }
        DECLARE_RESOURCE(VSTexAllState, RA_ASYN_LOAD | RA_ASYN_POSTLOAD | RA_ENABLE_GC | RA_NEED_CACHE, RT_TEXTURE, TEXTURE, Resource / Texture, VSTextureCache)
        const VSSamplerState *GetSamplerState() const
        {
            return m_pSamplerState;
        }
        virtual bool BeforeSave(MStream *pStream);
        virtual bool PostLoad(MStream *pStream);
        virtual bool PostClone(MObject *pObjectSrc);
        virtual bool IsCanSave()
        {
            if (!m_SourceData.GetNum())
            {
                return false;
            }
            return true;
        }
        virtual MObject *CreateToStreamObject(unsigned int uiWantSteamLevel, const VSCacheResource *pCacheResouce) const;
        virtual void StreamEnd(MObject *pStreamResource);
    };
    DECLARE_Ptr(VSTexAllState);
    DECLARE_Proxy(VSTexAllState);
    VSTYPE_MARCO(VSTexAllState);
}
