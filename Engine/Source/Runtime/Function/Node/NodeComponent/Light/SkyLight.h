#pragma once
#include "Light.h"
namespace Matrix
{

    class MStream;
    class MATRIX_FUNCTION_API VSSkyLight : public VSIndirectLight
    {
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        VSSkyLight();
        virtual ~VSSkyLight();
        VSColorRGBA m_UpColor;
        VSColorRGBA m_DownColor;
        virtual unsigned int GetLightType() const
        {
            return LT_SKY;
        }
    };
    DECLARE_Ptr(VSSkyLight);
    VSTYPE_MARCO(VSSkyLight);
}
