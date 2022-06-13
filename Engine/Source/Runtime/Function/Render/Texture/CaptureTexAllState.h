#pragma once
#include "TexAllState.h"
#include "ViewFamily.h"
#include "Render/Texture/CubeTexture.h"
namespace Matrix
{
    class MATRIX_FUNCTION_API VSCaptureTexAllState : public VSTexAllState
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;

        DECLARE_INITIAL
    public:
        VSCaptureTexAllState();

        virtual ~VSCaptureTexAllState();

        bool SetViewCapture(const Container::MString &ViewCaptureName);

        virtual bool PostLoad(MStream *pStream);
        virtual bool PostClone(MObject *pObjectSrc);
        virtual void ForceUpdate(bool OnlyUpdateOneTime);
        virtual void NotifyEndDraw();
        virtual bool BeforeSave(MStream *pStream);
        virtual bool PostSave(MStream *pStream);
        void SetMipLevel(unsigned int uiMipLevel);
        VSCaptureViewFamily *GetViewFamily();

    protected:
        Container::MString m_ViewCaptureName;
        bool m_bDynamic;
        VSTexturePtr m_pStaticTexture;
        unsigned int m_uiMipLevel;
        void CreateStaticTexture();
    };
    DECLARE_Ptr(VSCaptureTexAllState);
    VSTYPE_MARCO(VSCaptureTexAllState);
    DECLARE_Proxy(VSCaptureTexAllState);
}