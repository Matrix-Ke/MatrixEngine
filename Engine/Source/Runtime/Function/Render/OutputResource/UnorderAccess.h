#pragma once
#include "OutputResource.h"
namespace Matrix
{
    class MATRIX_FUNCTION_API VSUnorderAccess : public VSOutputResource
    {
        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL_NO_CLASS_FACTORY
    public:
        virtual ~VSUnorderAccess();

    protected:
        VSUnorderAccess();
    };
    DECLARE_Ptr(VSUnorderAccess);
    VSTYPE_MARCO(VSUnorderAccess);
}
