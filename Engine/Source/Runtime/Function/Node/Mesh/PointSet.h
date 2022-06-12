#pragma once
#include "MeshData.h"
#include "Vector3.h"
namespace Matrix
{
    class MATRIX_FUNCTION_API VSPointSet : public VSMeshData
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        VSPointSet();
        VSPointSet(const Math::Vector3 &Point, VSREAL fSize);
        virtual ~VSPointSet();
        bool CreateIndex();
        virtual unsigned int GetTotalNum() const;
        virtual unsigned int GetGirdNum(unsigned int uiInputNum) const;
    };
    DECLARE_Ptr(VSPointSet);
    VSTYPE_MARCO(VSPointSet);

}
