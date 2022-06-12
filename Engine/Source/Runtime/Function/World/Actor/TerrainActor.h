#pragma once
#include "Actor.h"
namespace Matrix
{

    class MATRIX_FUNCTION_API VSTerrainActor : public VSActor
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;

    public:
        VSTerrainActor();
        virtual ~VSTerrainActor() = 0;

        DECLARE_INITIAL_NO_CLASS_FACTORY
    };
    DECLARE_Ptr(VSTerrainActor);
    VSTYPE_MARCO(VSTerrainActor);

    class MATRIX_FUNCTION_API VSCLodTerrainActor : public VSTerrainActor
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;

    public:
        VSCLodTerrainActor();
        virtual ~VSCLodTerrainActor();
        DECLARE_INITIAL
        GET_TYPE_NODE(VSCLodTerrainNode)
        virtual void CreateDefaultComponentNode();
    };
    DECLARE_Ptr(VSCLodTerrainActor);
    VSTYPE_MARCO(VSCLodTerrainActor);

    class MATRIX_FUNCTION_API VSDLodTerrainActor : public VSTerrainActor
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;

    public:
        VSDLodTerrainActor();
        virtual ~VSDLodTerrainActor();
        DECLARE_INITIAL

        GET_TYPE_NODE(VSDLodTerrainNode)
        virtual void CreateDefaultComponentNode();
    };
    DECLARE_Ptr(VSDLodTerrainActor);
    VSTYPE_MARCO(VSDLodTerrainActor);

    class MATRIX_FUNCTION_API VSGPULodTerrainActor : public VSTerrainActor
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;

    public:
        VSGPULodTerrainActor();
        virtual ~VSGPULodTerrainActor();
        DECLARE_INITIAL

        GET_TYPE_NODE(VSGPULodTerrainNode)
        virtual void CreateDefaultComponentNode();
    };
    DECLARE_Ptr(VSGPULodTerrainActor);
    VSTYPE_MARCO(VSGPULodTerrainActor);

}