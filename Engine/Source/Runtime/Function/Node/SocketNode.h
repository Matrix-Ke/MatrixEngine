#pragma once
#include "Spatial.h"
namespace Matrix
{
    class MStream;
    class MATRIX_FUNCTION_API VSSocketNode : public VSSpatial
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        friend class VSNodeComponent;
        friend class VSSkeletonMeshNode;
        VSSocketNode();
        virtual ~VSSocketNode();
        virtual void UpdateWorldBound(double dAppTime){};

        virtual void ComputeNodeVisibleSet(VSCuller &Culler, bool bNoCull, double dAppTime){};
        virtual void ComputeVisibleSet(VSCuller &Culler, bool bNoCull, double dAppTime){};
        VSUsedName m_cName;

    protected:
        virtual void UpdateNodeAll(double dAppTime);
    };
    DECLARE_Ptr(VSSocketNode);
    VSTYPE_MARCO(VSSocketNode);
}
