#include "Node/Terrain/GPULodTerrainGeometry.h"
#include "Node/Terrain/GPULodTerrainNode.h"
#include "Node/Mesh/TriangleSet.h"
#include "Render/Buffer/VertexBuffer.h"
#include "Core/GraphicInclude.h"
#include "Node/Mesh/ControlPointPatch.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSGPULodTerrainGeometry, VSGeometry)
BEGIN_ADD_PROPERTY(VSGPULodTerrainGeometry, VSGeometry)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSGPULodTerrainGeometry)
IMPLEMENT_INITIAL_END
VSGPULodTerrainGeometry::VSGPULodTerrainGeometry()
{
}
VSGPULodTerrainGeometry::~VSGPULodTerrainGeometry()
{
}
VSGPULodTerrainNode *VSGPULodTerrainGeometry::GetParentTerrainNode() const
{
    if (m_pParent)
    {
        return (VSGPULodTerrainNode *)m_pParent->GetParent();
    }
    return NULL;
}
bool VSGPULodTerrainGeometry::CreateMesh(unsigned int uiTileNumX, unsigned int uiTileNumZ)
{
    VSGPULodTerrainNode *pTerrainNode = GetParentTerrainNode();

    VSDataBuffer *pVertexData = NULL;
    pVertexData = MX_NEW VSDataBuffer();
    if (!pVertexData->CreateEmptyBuffer((uiTileNumX + 1) * (uiTileNumZ + 1), VSDataBuffer::DT_FLOAT32_3))
    {
        return 0;
    }

    Math::Vector3 *pVer = (Math::Vector3 *)pVertexData->GetData();
    Math::Vector3 *pVerTemp = pVer;

    for (unsigned int i = 0; i < (uiTileNumX + 1); i++)
    {
        for (unsigned int j = 0; j < (uiTileNumZ + 1); j++)
        {
            unsigned int uiIndex = i * (uiTileNumZ + 1) + j;
            pVer[uiIndex].x = (i * 1.0f) / uiTileNumX;
            pVer[uiIndex].y = 0;
            pVer[uiIndex].z = (j * 1.0f) / uiTileNumZ;
            pVerTemp++;
        }
    }

    VSVertexBuffer *pVertexBuffer = NULL;
    pVertexBuffer = MX_NEW VSVertexBuffer(true);
    ENGINE_ASSERT(pVertexBuffer);

    pVertexBuffer->SetData(pVertexData, VSVertexFormat::VF_POSITION);

    VSDataBuffer *pIndexData = NULL;
    pIndexData = MX_NEW VSDataBuffer();
    ENGINE_ASSERT(pIndexData);

    if (!pIndexData->CreateEmptyBuffer(uiTileNumX * uiTileNumZ * 4, VSDataBuffer::DT_USHORT))
    {
        return 0;
    }

    VSUSHORT_INDEX *pIndex = (VSUSHORT_INDEX *)pIndexData->GetData();

    for (unsigned int i = 0; i < uiTileNumX; i++)
    {
        for (unsigned int j = 0; j < uiTileNumZ; j++)
        {
            *pIndex = i * uiTileNumZ + j;
            pIndex++;

            *pIndex = i * uiTileNumZ + j + 1;
            pIndex++;

            *pIndex = (i + 1) * uiTileNumZ + j;
            pIndex++;

            *pIndex = (i + 1) * uiTileNumZ + j + 1;
            pIndex++;
        }
    }

    VSIndexBuffer *pIndexBuffer = NULL;
    pIndexBuffer = MX_NEW VSIndexBuffer();
    ENGINE_ASSERT(pIndexBuffer);

    pIndexBuffer->SetData(pIndexData);

    VSControlPointPatch *pMeshData = NULL;
    pMeshData = MX_NEW VSControlPointPatch();

    ENGINE_ASSERT(pMeshData);

    pMeshData->SetVertexBuffer(pVertexBuffer);
    pMeshData->SetIndexBuffer(pIndexBuffer);
    SetMeshData(pMeshData);
    return 1;
}