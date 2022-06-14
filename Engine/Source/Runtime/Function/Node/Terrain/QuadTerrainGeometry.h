// #pragma once
// #include "Node/Terrain/CLodTerrainGeometry.h"
// namespace Matrix
// {
//     /*
//         |Z j
//         |
//        B|____C
//         |   /|
//         |  / |
//         | /  |
//        A|/___|D______X i
//     */
//     class MStream;
//     class MATRIX_FUNCTION_API VSQuadTerrainGeometry : public VSCLodTerrainGeometry
//     {
//         // PRIORITY

//         // RTTI
//         DECLARE_RTTI;
//         DECLARE_INITIAL
//     public:
//         VSQuadTerrainGeometry();
//         virtual ~VSQuadTerrainGeometry();

//     public:
//         virtual unsigned int GetTerrainGeometryType() { return TGT_QUAD; }
//         virtual void ComputeVariance(unsigned int uiCurLevel = 0);
//         virtual void LinkNeighbor();
//         virtual void ClearInfo();

//     protected:
//         enum
//         {
//             AT_ALL = 0x0000,
//             AT_NLEFT = 0x0001,
//             AT_NRIGHT = 0x0002,
//             AT_NTOP = 0x0004,
//             AT_NBOTTOM = 0x0008

//         };

//         virtual void Tessellate(const Math::Vector3 &CameraPos);
//         bool RecursiveComputeVariance(unsigned int uiLevel);
//         void RecursiveTessellate(const Math::Vector3 &CameraPos, unsigned int uiLevel, unsigned int A, unsigned int B,
//                                  unsigned int C, unsigned int D);
//         static inline void AddTriangle(VSUSHORT_INDEX *&pIndexData, unsigned int A, unsigned int B,
//                                        unsigned int C, unsigned int D, unsigned int uiATFlag, unsigned int &uiCurRenderTriNum);
//         virtual void UpdateOther(double dAppTime);

//     protected:
//         unsigned int m_uiCurLevel;
//         Container::MArray<VSREAL> m_Variance;
//     };
//     DECLARE_Ptr(VSQuadTerrainGeometry);
//     VSTYPE_MARCO(VSQuadTerrainGeometry);

// }
