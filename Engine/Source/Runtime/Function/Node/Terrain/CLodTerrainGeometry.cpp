#include "CLodTerrainGeometry.h"
#include "TerrainNode.h"
#include "TriangleSet.h"
#include "VertexBuffer.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
using namespace Matrix;
IMPLEMENT_RTTI_NoCreateFun(VSCLodTerrainGeometry, VSGeometry)
    IMPLEMENT_INITIAL_NO_CLASS_FACTORY_BEGIN(VSCLodTerrainGeometry)
        IMPLEMENT_INITIAL_NO_CLASS_FACTORY_END
    BEGIN_ADD_PROPERTY(VSCLodTerrainGeometry, VSGeometry)
        REGISTER_PROPERTY(m_pNeighbor[NT_LEFT], NeighborLeft, VSProperty::F_SAVE_LOAD_CLONE);
REGISTER_PROPERTY(m_pNeighbor[NT_RIGHT], NeighborRight, VSProperty::F_SAVE_LOAD_CLONE);
REGISTER_PROPERTY(m_pNeighbor[NT_TOP], NeighborTFop, VSProperty::F_SAVE_LOAD_CLONE);
REGISTER_PROPERTY(m_pNeighbor[NT_BOTTOM], NeighborBottom, VSProperty::F_SAVE_LOAD_CLONE);
REGISTER_PROPERTY(m_uiIndexXInTerrain, IndexXInTerrain, VSProperty::F_SAVE_LOAD_CLONE);
REGISTER_PROPERTY(m_uiIndexZInTerrain, IndexZInTerrain, VSProperty::F_SAVE_LOAD_CLONE);
END_ADD_PROPERTY
VSCLodTerrainGeometry::VSCLodTerrainGeometry()
{
    for (unsigned int i = 0; i < NT_MAX; i++)
    {
        m_pNeighbor[i] = NULL;
    }
    m_uiIndexXInTerrain = 0;
    m_uiIndexZInTerrain = 0;
    m_bIsStatic = false;
}
VSCLodTerrainGeometry::~VSCLodTerrainGeometry()
{
}
bool VSCLodTerrainGeometry::CreateMeshData(unsigned int uiIndexXInTerrain, unsigned int uiIndexZInTerrain,
                                           unsigned int uiTessellationLevel)
{

    VSTerrainNode *pTerrainNode = DynamicCast<VSTerrainNode>(m_pParent);
    ENGINE_ASSERT(pTerrainNode);

    VSDataBuffer *pVertexData = NULL;
    pVertexData = MX_NEW VSDataBuffer();
    unsigned int uiVertexLenght = (1 << uiTessellationLevel) + 1;
    if (!pVertexData->CreateEmptyBuffer(uiVertexLenght * uiVertexLenght, VSDataBuffer::DT_FLOAT32_3))
    {
        return 0;
    }

    Math::Vector3 *pVer = (Math::Vector3 *)pVertexData->GetData();
    unsigned int uiBiasX = uiIndexXInTerrain * (1 << uiTessellationLevel);
    unsigned int uiBiasZ = uiIndexZInTerrain * (1 << uiTessellationLevel);
    for (unsigned int i = 0; i < uiVertexLenght; i++)
    {
        for (unsigned int j = 0; j < uiVertexLenght; j++)
        {
            unsigned int uiIndex = i * uiVertexLenght + j;
            pVer[uiIndex].x = 1.0f * (uiBiasX + i) * VSTerrainNode::WIDTH_SCALE;
            pVer[uiIndex].y = pTerrainNode->GetHeight(uiBiasX + i, uiBiasZ + j);
            pVer[uiIndex].z = 1.0f * (uiBiasZ + j) * VSTerrainNode::WIDTH_SCALE;
        }
    }

    VSVertexBuffer *pVertexBuffer = NULL;
    pVertexBuffer = MX_NEW VSVertexBuffer(true);
    pVertexBuffer->SetMemType(VSMemBind::MT_BOTH);
    ENGINE_ASSERT(pVertexBuffer);

    pVertexBuffer->SetData(pVertexData, VSVertexFormat::VF_POSITION);

    unsigned int uiCurRenderTriNum = (uiVertexLenght - 1) * (uiVertexLenght - 1) * 2 * 3;

    VSIndexBuffer *pIndexBuffer = NULL;
    pIndexBuffer = MX_NEW VSIndexBuffer(uiCurRenderTriNum);
    pIndexBuffer->SetMemType(VSMemBind::MT_BOTH);
    ENGINE_ASSERT(pIndexBuffer);

    // test mul thread render
    if (GetTerrainGeometryType() == TGT_ROAM)
    {
        pIndexBuffer->SetStatic(false, true);
    }
    else
    {
        pIndexBuffer->SetStatic(false);
    }

    pIndexBuffer->SetLockFlag(VSInheritBind::LF_DISCARD);

    VSTriangleSet *pMeshData = NULL;
    pMeshData = MX_NEW VSTriangleSet();

    if (!pMeshData)
    {
        return 0;
    }

    pMeshData->SetVertexBuffer(pVertexBuffer);
    pMeshData->SetIndexBuffer(pIndexBuffer);
    SetMeshData(pMeshData);
    m_uiIndexXInTerrain = uiIndexXInTerrain;
    m_uiIndexZInTerrain = uiIndexZInTerrain;
    return 1;
}
bool VSCLodTerrainGeometry::AddNeighbor(VSCLodTerrainGeometry *pTerrainGemetry, unsigned int uiNeighbor)
{
    ENGINE_ASSERT(pTerrainGemetry && uiNeighbor < NT_MAX);

    VSTerrainNode *pTerrainNode = DynamicCast<VSTerrainNode>(m_pParent);
    ENGINE_ASSERT(pTerrainNode);

    ENGINE_ASSERT(m_pNeighbor[uiNeighbor] == NULL);

    m_pNeighbor[uiNeighbor] = pTerrainGemetry;

    return 1;
}
void VSCLodTerrainGeometry::UpdateView(VSCuller &Culler, double dAppTime)
{
    VSGeometry::UpdateView(Culler, dAppTime);
    VSCamera *pCamera = Culler.GetCamera();
    ENGINE_ASSERT(pCamera);

    if (Culler.GetCullerType() == VSCuller::CUT_MAIN)
    {
        VSTerrainNode *pTerrainNode = DynamicCast<VSTerrainNode>(m_pParent);
        if (!pTerrainNode)
        {
            return;
        }
        Math::VSTransform Tran = pTerrainNode->GetWorldTransform();
        Math::Vector3 Loc = pCamera->GetWorldTranslate() * Tran.GetCombineInverse();

        Tessellate(Loc);
    }
}
