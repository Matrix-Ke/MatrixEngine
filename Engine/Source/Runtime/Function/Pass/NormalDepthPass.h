#pragma once
#include "Pass/Pass.h"
namespace Matrix
{

    class MATRIX_FUNCTION_API VSNormalDepthPass : public VSPass
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;

    public:
        virtual ~VSNormalDepthPass();
        VSNormalDepthPass();

    public:
    protected:
        DECLARE_INITIAL
        static bool InitialDefaultState();
        static bool TerminalDefaultState();

    protected:
        VSRenderState m_RenderState;

    public:
        virtual bool Draw(VSRenderer *pRenderer);

        virtual unsigned int GetPassType()
        {
            return PT_NORMALDEPTH;
        }
    };
    DECLARE_Ptr(VSNormalDepthPass);
    VSTYPE_MARCO(VSNormalDepthPass);
}
