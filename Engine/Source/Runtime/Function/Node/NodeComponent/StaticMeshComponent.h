// #pragma once
// #include "Node/NodeComponent/MeshComponent.h"
// namespace Matrix
// {

//     DECLARE_Ptr(VSStaticMeshNode);
//     DECLARE_Proxy(VSStaticMeshNode);
//     class MATRIX_FUNCTION_API VSStaticMeshComponent : public VSMeshComponent
//     {
//         // PRIORITY

//         // RTTI
//         DECLARE_RTTI;
//         DECLARE_INITIAL
//     public:
//         VSStaticMeshComponent();
//         virtual ~VSStaticMeshComponent();
//         void SetStaticMeshResource(VSStaticMeshNodeR *pStaticMeshResource);
//         VSStaticMeshNode *GetStaticMeshNode();
//         virtual void LoadedEvent(VSResourceProxyBase *pResourceProxy, void *Data = NULL);
//         virtual void PostCreate();
//         virtual bool BeforeSave(void *pData = NULL);
//         virtual bool PostLoad(MStream *pStream);

//     protected:
//         VSStaticMeshNodeRPtr m_pStaticMeshResource;
//     };
//     DECLARE_Ptr(VSStaticMeshComponent);
//     VSTYPE_MARCO(VSStaticMeshComponent);
// }
