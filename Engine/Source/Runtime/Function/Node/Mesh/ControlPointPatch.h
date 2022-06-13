#pragma once
#include "Node/Mesh/MeshData.h"

namespace Matrix
{

    class MATRIX_FUNCTION_API VSControlPointPatch : public VSMeshData
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        VSControlPointPatch();
        virtual ~VSControlPointPatch();

        virtual unsigned int GetTotalNum() const;
        virtual unsigned int GetMeshDataType() { return MDT_TRIANGLE; }
        virtual unsigned int GetActiveNum() const;
        virtual unsigned int GetGirdNum(unsigned int uiInputNum) const;
    };
    DECLARE_Ptr(VSControlPointPatch);
    VSTYPE_MARCO(VSControlPointPatch);

}
