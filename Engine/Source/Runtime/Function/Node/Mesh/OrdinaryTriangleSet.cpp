#include "Node/Mesh/OrdinaryTriangleSet.h"
#include "Core/GraphicInclude.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSOrdinaryTriangleSet, VSTriangleSet)
BEGIN_ADD_PROPERTY(VSOrdinaryTriangleSet, VSTriangleSet)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSOrdinaryTriangleSet)
IMPLEMENT_INITIAL_END
VSOrdinaryTriangleSet::VSOrdinaryTriangleSet()
{
}
VSOrdinaryTriangleSet::VSOrdinaryTriangleSet(const Primitive::AABB3 &AABB)
{
    Math::Vector3 VertexData[8];
    AABB.GetPoint(VertexData);
    VSDataBuffer *pVertex = MX_NEW VSDataBuffer;
    pVertex->SetData(VertexData, 8, VSDataBuffer::DT_FLOAT32_3);
    m_pVertexBuffer = MX_NEW VSVertexBuffer(true);
    m_pVertexBuffer->SetData(pVertex, VSVertexFormat::VF_POSITION);
    VSUSHORT_INDEX Index[36];
    //前面的2个三角形
    Index[0] = 0;
    Index[1] = 1;
    Index[2] = 2;
    Index[3] = 0;
    Index[4] = 2;
    Index[5] = 3;

    //后面的2个三角形
    Index[6] = 4;
    Index[7] = 6;
    Index[8] = 5;
    Index[9] = 4;
    Index[10] = 7;
    Index[11] = 6;

    //右侧面的2个三角形
    Index[12] = 0;
    Index[13] = 3;
    Index[14] = 7;
    Index[15] = 0;
    Index[16] = 7;
    Index[17] = 4;
    //左侧面的2个三角形
    Index[18] = 1;
    Index[19] = 5;
    Index[20] = 6;
    Index[21] = 1;
    Index[22] = 6;
    Index[23] = 2;
    //顶面的2个三角形
    Index[24] = 0;
    Index[25] = 5;
    Index[26] = 1;
    Index[27] = 0;
    Index[28] = 4;
    Index[29] = 5;
    //底面的2个三角形
    Index[30] = 2;
    Index[31] = 6;
    Index[32] = 7;
    Index[33] = 2;
    Index[34] = 7;
    Index[35] = 3;

    VSDataBuffer *pIndexDataBuffer = MX_NEW VSDataBuffer;
    pIndexDataBuffer->SetData(Index, 36, VSDataBuffer::DT_USHORT);

    if (!m_pIndexBuffer)
    {
        m_pIndexBuffer = MX_NEW VSIndexBuffer();
    }

    m_pIndexBuffer->SetData(pIndexDataBuffer);
}
VSOrdinaryTriangleSet::VSOrdinaryTriangleSet(const Primitive::OBB3 &OBB)
{
    Math::Vector3 VertexData[8];
    OBB.GetPoint(VertexData);
    VSDataBuffer *pVertex = MX_NEW VSDataBuffer;
    pVertex->SetData(VertexData, 8, VSDataBuffer::DT_FLOAT32_3);
    m_pVertexBuffer = MX_NEW VSVertexBuffer(true);
    m_pVertexBuffer->SetData(pVertex, VSVertexFormat::VF_POSITION);
    VSUSHORT_INDEX Index[36];
    //前面的2个三角形
    Index[0] = 0;
    Index[1] = 1;
    Index[2] = 2;
    Index[3] = 0;
    Index[4] = 2;
    Index[5] = 3;

    //后面的2个三角形
    Index[6] = 4;
    Index[7] = 6;
    Index[8] = 5;
    Index[9] = 4;
    Index[10] = 7;
    Index[11] = 6;

    //右侧面的2个三角形
    Index[12] = 0;
    Index[13] = 3;
    Index[14] = 7;
    Index[15] = 0;
    Index[16] = 7;
    Index[17] = 4;
    //左侧面的2个三角形
    Index[18] = 1;
    Index[19] = 5;
    Index[20] = 6;
    Index[21] = 1;
    Index[22] = 6;
    Index[23] = 2;
    //顶面的2个三角形
    Index[24] = 0;
    Index[25] = 5;
    Index[26] = 1;
    Index[27] = 0;
    Index[28] = 4;
    Index[29] = 5;
    //底面的2个三角形
    Index[30] = 2;
    Index[31] = 6;
    Index[32] = 7;
    Index[33] = 2;
    Index[34] = 7;
    Index[35] = 3;

    VSDataBuffer *pIndexDataBuffer = MX_NEW VSDataBuffer;
    pIndexDataBuffer->SetData(Index, 36, VSDataBuffer::DT_USHORT);

    if (!m_pIndexBuffer)
    {
        m_pIndexBuffer = MX_NEW VSIndexBuffer();
    }

    m_pIndexBuffer->SetData(pIndexDataBuffer);
}
VSOrdinaryTriangleSet::VSOrdinaryTriangleSet(const Primitive::Plane3 &Plane)
{
    Math::Matrix4 Mat;
    Mat.CreateFromLookDir(Plane.GetPoint(), Plane.GetN());

    Math::Vector3 A0(Mat.M[0][0], Mat.M[0][1], Mat.M[0][2]);
    Math::Vector3 A1(Mat.M[1][0], Mat.M[1][1], Mat.M[1][2]);

    Math::Vector3 VertexData[4];
    VertexData[0] = Plane.GetPoint() + A0 * DRAW_MATH_ELEMENT_LENGTH + A1 * DRAW_MATH_ELEMENT_LENGTH;
    VertexData[1] = Plane.GetPoint() - A0 * DRAW_MATH_ELEMENT_LENGTH + A1 * DRAW_MATH_ELEMENT_LENGTH;
    VertexData[2] = Plane.GetPoint() - A0 * DRAW_MATH_ELEMENT_LENGTH - A1 * DRAW_MATH_ELEMENT_LENGTH;
    VertexData[3] = Plane.GetPoint() + A0 * DRAW_MATH_ELEMENT_LENGTH - A1 * DRAW_MATH_ELEMENT_LENGTH;

    VSDataBuffer *pVertex = MX_NEW VSDataBuffer;
    pVertex->SetData(VertexData, 4, VSDataBuffer::DT_FLOAT32_3);
    m_pVertexBuffer = MX_NEW VSVertexBuffer(true);
    m_pVertexBuffer->SetData(pVertex, VSVertexFormat::VF_POSITION);

    VSUSHORT_INDEX Index[6];

    Index[0] = 0;
    Index[1] = 1;
    Index[2] = 2;
    Index[3] = 0;
    Index[4] = 2;
    Index[5] = 3;

    VSDataBuffer *pIndexDataBuffer = MX_NEW VSDataBuffer;
    pIndexDataBuffer->SetData(Index, 6, VSDataBuffer::DT_USHORT);

    if (!m_pIndexBuffer)
    {
        m_pIndexBuffer = MX_NEW VSIndexBuffer();
    }

    m_pIndexBuffer->SetData(pIndexDataBuffer);
}
VSOrdinaryTriangleSet::VSOrdinaryTriangleSet(const VSTriangle3 &Triangle)
{
    Math::Vector3 VertexData[3];
    Triangle.GetPoint(VertexData);
    VSDataBuffer *pVertex = MX_NEW VSDataBuffer;
    pVertex->SetData(VertexData, 3, VSDataBuffer::DT_FLOAT32_3);
    m_pVertexBuffer = MX_NEW VSVertexBuffer(true);
    m_pVertexBuffer->SetData(pVertex, VSVertexFormat::VF_POSITION);

    VSUSHORT_INDEX Index[3];
    Index[0] = 0;
    Index[1] = 1;
    Index[2] = 2;
    VSDataBuffer *pIndexDataBuffer = MX_NEW VSDataBuffer;
    pIndexDataBuffer->SetData(Index, 3, VSDataBuffer::DT_USHORT);

    if (!m_pIndexBuffer)
    {
        m_pIndexBuffer = MX_NEW VSIndexBuffer();
    }

    m_pIndexBuffer->SetData(pIndexDataBuffer);
}
VSOrdinaryTriangleSet::VSOrdinaryTriangleSet(const VSRectangle3 &Rectangle)
{
    Math::Vector3 VertexData[4];
    Rectangle.GetPoint(VertexData);
    VSDataBuffer *pVertex = MX_NEW VSDataBuffer;
    pVertex->SetData(VertexData, 4, VSDataBuffer::DT_FLOAT32_3);
    m_pVertexBuffer = MX_NEW VSVertexBuffer(true);
    m_pVertexBuffer->SetData(pVertex, VSVertexFormat::VF_POSITION);

    VSUSHORT_INDEX Index[6];

    Index[0] = 0;
    Index[1] = 2;
    Index[2] = 1;
    Index[3] = 0;
    Index[4] = 3;
    Index[5] = 2;

    VSDataBuffer *pIndexDataBuffer = MX_NEW VSDataBuffer;
    pIndexDataBuffer->SetData(Index, 6, VSDataBuffer::DT_USHORT);

    if (!m_pIndexBuffer)
    {
        m_pIndexBuffer = MX_NEW VSIndexBuffer();
    }

    m_pIndexBuffer->SetData(pIndexDataBuffer);
}
VSOrdinaryTriangleSet::VSOrdinaryTriangleSet(const VSPolygon3 &Polyon)
{
    ENGINE_ASSERT(Polyon.GetpPoint() && Polyon.GetPointNum());

    VSDataBuffer *pVertex = MX_NEW VSDataBuffer;
    pVertex->SetData(Polyon.GetpPoint(), Polyon.GetPointNum(), VSDataBuffer::DT_FLOAT32_3);
    m_pVertexBuffer = MX_NEW VSVertexBuffer(true);
    m_pVertexBuffer->SetData(pVertex, VSVertexFormat::VF_POSITION);

    VSDataBuffer *pIndexDataBuffer = MX_NEW VSDataBuffer;
    pIndexDataBuffer->SetData(Polyon.GetpIndex(), Polyon.GetIndexNum(), VSDataBuffer::DT_USHORT);

    if (!m_pIndexBuffer)
    {
        m_pIndexBuffer = MX_NEW VSIndexBuffer();
    }

    m_pIndexBuffer->SetData(pIndexDataBuffer);
}
VSOrdinaryTriangleSet::VSOrdinaryTriangleSet(const Primitive::Sphere3 &Sphere)
{
    VSREAL LongitudeAngle = 10; //经度线上的划分角
    VSREAL LatitudeAngle = 10;  //维度线上的划分角

    VSREAL AnglePI = 180.0f;
    unsigned int LongitudeNum = 0;
    while (AnglePI > 0)
    {
        LongitudeNum++;
        AnglePI -= LongitudeAngle;
    }
    LongitudeNum++;
    unsigned int LatitudeNum = unsigned int(360.0f / LatitudeAngle) + 1;

    VSDataBuffer *pVertex = MX_NEW VSDataBuffer;
    pVertex->CreateEmptyBuffer(LongitudeNum * LatitudeNum, VSDataBuffer::DT_FLOAT32_3);

    Math::Vector3 *pVertexData = (Math::Vector3 *)pVertex->GetData();
    VSREAL i = 0;
    for (unsigned int k = 0; k < LongitudeNum; k++)
    {
        if (i > 180)
            i = 180;
        VSREAL iRadian = Math::AngleToRadian(i);
        for (VSREAL j = 0; j <= 360.0f; j = j + LatitudeAngle)
        {

            VSREAL jRadian = Math::AngleToRadian(j);
            pVertexData->x = Sphere.m_fRadius * SIN(iRadian) * COS(jRadian);
            pVertexData->z = Sphere.m_fRadius * SIN(iRadian) * SIN(jRadian);
            pVertexData->y = Sphere.m_fRadius * COS(iRadian);

            *pVertexData += Sphere.m_Center;
            pVertexData++;
        }
        i = i + LongitudeAngle;
    }
    m_pVertexBuffer = MX_NEW VSVertexBuffer(true);
    m_pVertexBuffer->SetData(pVertex, VSVertexFormat::VF_POSITION);

    VSDataBuffer *pIndexDataBuffer = MX_NEW VSDataBuffer;
    pIndexDataBuffer->CreateEmptyBuffer((LongitudeNum - 1) * LatitudeNum * 2 * 3, VSDataBuffer::DT_USHORT);
    VSUSHORT_INDEX *pIndexData = (VSUSHORT_INDEX *)pIndexDataBuffer->GetData();
    for (unsigned int i = 0; i < LongitudeNum - 1; i++)
    {
        unsigned int z_width_poly = i * LatitudeNum;
        unsigned int z_width = i * LatitudeNum;
        for (unsigned int j = 0; j < LatitudeNum; j++)
        {
            unsigned int z_width_x = z_width + j;
            unsigned int z_width_xX2 = (z_width_poly + j) * 2;
            if (j != LatitudeNum - 1)
            {
                pIndexData[z_width_xX2 * 3 + 0] = z_width_x;
                pIndexData[z_width_xX2 * 3 + 2] = z_width_x + LatitudeNum;
                pIndexData[z_width_xX2 * 3 + 1] = z_width_x + 1;

                pIndexData[(z_width_xX2 + 1) * 3 + 0] = z_width_x + 1 + LatitudeNum;
                pIndexData[(z_width_xX2 + 1) * 3 + 2] = z_width_x + 1;
                pIndexData[(z_width_xX2 + 1) * 3 + 1] = z_width_x + LatitudeNum;
            }
            else
            {
                pIndexData[z_width_xX2 * 3 + 0] = z_width_x;
                pIndexData[z_width_xX2 * 3 + 2] = z_width_x + LatitudeNum;
                pIndexData[z_width_xX2 * 3 + 1] = z_width_x - LatitudeNum + 1;

                pIndexData[(z_width_xX2 + 1) * 3 + 0] = z_width_x + 1;
                pIndexData[(z_width_xX2 + 1) * 3 + 2] = z_width_x - LatitudeNum + 1;
                pIndexData[(z_width_xX2 + 1) * 3 + 1] = z_width_x + LatitudeNum;
            }
        }
    }

    if (!m_pIndexBuffer)
    {
        m_pIndexBuffer = MX_NEW VSIndexBuffer();
    }

    m_pIndexBuffer->SetData(pIndexDataBuffer);
}
VSOrdinaryTriangleSet::~VSOrdinaryTriangleSet()
{
}
VSOrdinaryTriangleSet::VSOrdinaryTriangleSet(VSSurface3 *pSurface, VSSurface3Subdivision *pSubidvision)
{
    ENGINE_ASSERT(pSubidvision);
    ENGINE_ASSERT(pSurface);
    if (!pSubidvision->GetPoints())
    {
        pSubidvision->SetSurface(pSurface);
        bool bResult = pSubidvision->Subdivision();
        ENGINE_ASSERT(bResult);
    }
    VSDataBuffer *pVertex = MX_NEW VSDataBuffer;
    unsigned int Row = pSubidvision->GetRow();
    unsigned int Column = pSubidvision->GetColumn();
    pVertex->SetData(pSubidvision->GetPoints(), Row * Column, VSDataBuffer::DT_FLOAT32_3);

    m_pVertexBuffer = MX_NEW VSVertexBuffer(true);
    m_pVertexBuffer->SetData(pVertex, VSVertexFormat::VF_POSITION);

    VSDataBuffer *pIndexDataBuffer = MX_NEW VSDataBuffer;
    pIndexDataBuffer->CreateEmptyBuffer((Row - 1) * (Column - 1) * 2 * 3, VSDataBuffer::DT_USHORT);
    VSUSHORT_INDEX *pIndexData = (VSUSHORT_INDEX *)pIndexDataBuffer->GetData();

    for (unsigned int i = 0; i < Row - 1; i++)
    {
        unsigned int z_width_poly = i * (Column - 1);
        unsigned int z_width = i * Column;
        for (unsigned int j = 0; j < Column - 1; j++)
        {
            unsigned int z_width_x = z_width + j;
            unsigned int z_width_xX2 = (z_width_poly + j) * 2;
            pIndexData[z_width_xX2 * 3 + 0] = z_width_x;
            pIndexData[z_width_xX2 * 3 + 2] = z_width_x + Column;
            pIndexData[z_width_xX2 * 3 + 1] = z_width_x + 1;

            pIndexData[(z_width_xX2 + 1) * 3 + 0] = z_width_x + 1 + Column;
            pIndexData[(z_width_xX2 + 1) * 3 + 2] = z_width_x + 1;
            pIndexData[(z_width_xX2 + 1) * 3 + 1] = z_width_x + Column;
        }
    }

    if (!m_pIndexBuffer)
    {
        m_pIndexBuffer = MX_NEW VSIndexBuffer();
    }

    m_pIndexBuffer->SetData(pIndexDataBuffer);
}
