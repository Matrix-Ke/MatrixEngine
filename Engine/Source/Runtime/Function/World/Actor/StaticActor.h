#pragma once
#include "Actor.h"
#include "StaticMeshComponent.h"
namespace Matrix
{
    DECLARE_Proxy(VSStaticMeshNode);
    class MATRIX_FUNCTION_API VSStaticActor : public VSActor
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;

    public:
        friend class VSWorld;
        VSStaticActor();
        virtual ~VSStaticActor();
        DECLARE_INITIAL

        GET_TYPE_NODE(VSStaticMeshComponent)
        virtual void CreateDefaultComponentNode();
    };
    DECLARE_Ptr(VSStaticActor);
    VSTYPE_MARCO(VSStaticActor);
}
