#pragma once
#include "MeshNode.h"
#include "GeometryNode.h"
namespace Matrix
{
    class VSGeometryNode;
    class VSSwitchNode;
    class MStream;
    class MATRIX_FUNCTION_API VSModelMeshNode : public VSMeshNode
    {
        // PRIORITY

        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL
    public:
        VSModelMeshNode();
        virtual ~VSModelMeshNode();

        virtual VSSwitchNode *GetLodNode() const;
        virtual VSGeometryNode *GetGeometryNode(unsigned int uiLodLevel);
        void SetUseMaterialInstance(unsigned int SubMeshID, unsigned int UsedID);
        virtual bool PostLoad(MStream *pStream);
        virtual bool PostClone(MObject *pObjectSrc);
        virtual void UpdateController(double dAppTime);
        void SetMorphData(const VSUsedName &ShowName, float fData);
        virtual bool SetDrawInstance(bool bDrawInstance);
        void ClearLodMesh();
        virtual void GetStreamResource(Container::MArray<VSResourceProxyBase *> &pResourceProxy, StreamInformation_TYPE &StreamInformation) const;

    protected:
        bool AddLODGeometryNode(VSGeometryNode *pGeoNode);
    };
    DECLARE_Ptr(VSModelMeshNode);
    VSTYPE_MARCO(VSModelMeshNode);
}
