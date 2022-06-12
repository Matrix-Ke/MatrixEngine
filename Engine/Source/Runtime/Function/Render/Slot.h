#pragma once
#include "Graphic.h"
#include "Array.h"
namespace Matrix
{
    class MATRIX_FUNCTION_API VSSlot
    {
    public:
        VSSlot();
        ~VSSlot();

        Container::MArray<unsigned char> m_VSTexSlot;
        Container::MArray<unsigned char> m_PSTexSlot;
        Container::MArray<unsigned char> m_GSTexSlot;
        Container::MArray<unsigned char> m_DSTexSlot;
        Container::MArray<unsigned char> m_HSTexSlot;
        Container::MArray<unsigned char> m_CSTexSlot;
        void ClearAllSlot();
        bool HasAnySlot();
        bool m_bBindResourceUse;
        inline unsigned int GetOutputType() const
        {
            return m_uiOutputType;
        }

    protected:
        unsigned int m_uiOutputType;
    };
}