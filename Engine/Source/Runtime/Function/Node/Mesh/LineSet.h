#pragma once
#include "MeshData.h"
namespace Matrix
{
    class MATRIX_FUNCTION_API VSLineSet : public VSMeshData
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        VSLineSet();
        virtual ~VSLineSet();
        enum // Line Type
        {
            LT_OPEN,
            LT_CLOSE,
            LT_SEGMENT,
            LT_MAX

        };
        bool CreateIndex(unsigned int uiLineType);
        virtual unsigned int GetTotalNum() const;

        virtual unsigned int GetActiveNum() const;

        virtual unsigned int GetGirdNum(unsigned int uiInputNum) const;
    };
    DECLARE_Ptr(VSLineSet);
    VSTYPE_MARCO(VSLineSet);

}