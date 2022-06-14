// #pragma once
// #include "Node/Terrain/CLodTerrainGeometry.h"
// namespace Matrix
// {

//     /*
//                 A
//                  /\
//                 /  \
//               C/____\ B
//     顺时针排列，可见

//      |Z
//      |
//     A|____B
//      |   /|
//      |  / |
//      | /  |
//     C|/___|_______X

//     */
//     class MStream;
//     class MATRIX_FUNCTION_API VSRoamTerrainGeometry : public VSCLodTerrainGeometry
//     {
//         // PRIORITY

//         // RTTI
//         DECLARE_RTTI;
//         DECLARE_INITIAL
//     public:
//         VSRoamTerrainGeometry();
//         virtual ~VSRoamTerrainGeometry();

//     public:
//         virtual unsigned int GetTerrainGeometryType() { return TGT_ROAM; }
//         class VSTriTreeNode
//         {
//         public:
//             VSTriTreeNode *pBaseNeighbor;
//             VSTriTreeNode *pLeftNeighbor;
//             VSTriTreeNode *pRightNeighbor;
//             VSTriTreeNode *pLeftChild;
//             VSTriTreeNode *pRightChild;

//             VSRoamTerrainGeometry *pOwner;
//             VSTriTreeNode()
//             {
//                 pOwner = NULL;
//                 pBaseNeighbor = NULL;
//                 pLeftNeighbor = NULL;
//                 pRightNeighbor = NULL;
//                 pLeftChild = NULL;
//                 pRightChild = NULL;
//             }
//             inline void Clear()
//             {
//                 // pOwner = NULL;
//                 pBaseNeighbor = NULL;
//                 pLeftNeighbor = NULL;
//                 pRightNeighbor = NULL;
//                 pLeftChild = NULL;
//                 pRightChild = NULL;
//             }
//         };
//         virtual void ComputeVariance(unsigned int uiCurLevel = 0);
//         virtual void LinkNeighbor();
//         virtual void ClearInfo();

//     protected:
//         virtual void Tessellate(const Math::Vector3 &CameraPos);
//         VSREAL RecursiveComputeVariance(Container::MArray<VSREAL> &Variance, unsigned int uiIndex,
//                                         unsigned int A, unsigned int B, unsigned int C);
//         void RecursiveTessellate(VSTriTreeNode *pTri, const Math::Vector3 &CameraPos, Container::MArray<VSREAL> &Variance,
//                                  unsigned int uiIndex, unsigned int A, unsigned int B, unsigned int C);
//         void Split(VSTriTreeNode *pTri);
//         VSTriTreeNode *GetBuffer();

//         void RecursiveBuildRenderTriange(VSTriTreeNode *pTri,
//                                          unsigned int A, unsigned int B, unsigned int C, VSUSHORT_INDEX *&pIndexData, unsigned int &uiCurRenderTriNum);
//         virtual void UpdateOther(double dAppTime);

//         void TessellateEx(const Math::Vector3 &CameraPos, unsigned int uiLevel);
//         void ClearInfoEx();
//         void UpdateOtherEx(unsigned int uiLevel);

//     protected:
//         Container::MArray<VSREAL> m_Variance[2];
//         VSTriTreeNode m_TriTreeNode[2];
//         Container::MArray<VSTriTreeNode> m_TriBuffer;
//         unsigned int m_uiCurBufferNum;
//     };
//     DECLARE_Ptr(VSRoamTerrainGeometry);
//     VSTYPE_MARCO(VSRoamTerrainGeometry);
// }
