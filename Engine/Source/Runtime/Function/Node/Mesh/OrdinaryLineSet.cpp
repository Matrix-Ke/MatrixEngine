#include "OrdinaryLineSet.h"
#include "Core/GraphicInclude.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSOrdinaryLineSet, VSLineSet)
BEGIN_ADD_PROPERTY(VSOrdinaryLineSet, VSLineSet)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSOrdinaryLineSet)
IMPLEMENT_INITIAL_END
VSOrdinaryLineSet::VSOrdinaryLineSet()
{
}
VSOrdinaryLineSet::~VSOrdinaryLineSet()
{
}
VSOrdinaryLineSet::VSOrdinaryLineSet(VSControlCurve3 *pControlCurve, VSCurve3Subdivision *pSubidvision)
{
    ENGINE_ASSERT(pSubidvision && pControlCurve);
    if (!pSubidvision->GetPoints())
    {
        pSubidvision->SetSubCurve(pControlCurve);
        pSubidvision->Subdivision();
    }
    VSDataBuffer *pVertex = MX_NEW VSDataBuffer;

    pVertex->SetData(pSubidvision->GetPoints(), pSubidvision->GetPointNum(), VSDataBuffer::DT_FLOAT32_3);

    m_pVertexBuffer = MX_NEW VSVertexBuffer(true);
    m_pVertexBuffer->SetData(pVertex, VSVertexFormat::VF_POSITION);

    bool bResult = CreateIndex(LT_OPEN);
    ENGINE_ASSERT(bResult);
}
VSOrdinaryLineSet::VSOrdinaryLineSet(const VSLine3 &Line)
{
    Math::Vector3 Verts[2];
    Verts[0] = Line.GetOrig() - Line.GetDir() * DRAW_MATH_ELEMENT_LENGTH;
    Verts[1] = Line.GetOrig() + Line.GetDir() * DRAW_MATH_ELEMENT_LENGTH;

    VSDataBuffer *pVertex = MX_NEW VSDataBuffer;

    pVertex->SetData(Verts, 2, VSDataBuffer::DT_FLOAT32_3);

    m_pVertexBuffer = MX_NEW VSVertexBuffer(true);
    m_pVertexBuffer->SetData(pVertex, VSVertexFormat::VF_POSITION);
    bool bResult = CreateIndex(LT_OPEN);
    ENGINE_ASSERT(bResult);
}
VSOrdinaryLineSet::VSOrdinaryLineSet(const VSRay3 &Ray)
{
    Math::Vector3 Verts[2];
    Verts[0] = Ray.GetOrig();
    Verts[1] = Verts[0] + Ray.GetDir() * DRAW_MATH_ELEMENT_LENGTH;
    VSDataBuffer *pVertex = MX_NEW VSDataBuffer;

    pVertex->SetData(Verts, 2, VSDataBuffer::DT_FLOAT32_3);

    m_pVertexBuffer = MX_NEW VSVertexBuffer(true);
    m_pVertexBuffer->SetData(pVertex, VSVertexFormat::VF_POSITION);
    bool bResult = CreateIndex(LT_OPEN);
    ENGINE_ASSERT(bResult);
}
VSOrdinaryLineSet::VSOrdinaryLineSet(const VSSegment3 &Segment)
{
    Math::Vector3 Verts[2];
    Verts[0] = Segment.GetOrig();
    Verts[1] = Segment.GetEnd();
    VSDataBuffer *pVertex = MX_NEW VSDataBuffer;

    pVertex->SetData(Verts, 2, VSDataBuffer::DT_FLOAT32_3);

    m_pVertexBuffer = MX_NEW VSVertexBuffer(true);
    m_pVertexBuffer->SetData(pVertex, VSVertexFormat::VF_POSITION);
    bool bResult = CreateIndex(LT_OPEN);
    ENGINE_ASSERT(bResult);
}
