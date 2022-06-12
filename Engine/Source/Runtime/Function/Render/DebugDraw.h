#pragma once
#include "Reference.h"
#include "DynamicBufferGeometry.h"
namespace Matrix
{
    class MATRIX_FUNCTION_API VSDebugDraw : public VSReference, public VSMemObject
    {
        // Graph Debug
    public:
        VSDebugDraw();
        ~VSDebugDraw();
        void AddDebugLine(const Math::Vector3 &P1, const Math::Vector3 &P2, const DWORD &Color, bool bDepth);
        void AddDebugTriangle(const Math::Vector3 &P1, const Math::Vector3 &P2, const Math::Vector3 &P3,
                              const DWORD &Color, bool bDepth);
        void AddDebugLineAABB(const Primitive::AABB3 &AABB, const DWORD &Color, bool bDepth);
        void AddDebugLineSphere(const VSSphere3 &Sphere, const DWORD &Color, bool bDepth);
        void AddDebugLineOBB(const VSOBB3 &OBB, const DWORD &Color, bool bDepth);

        void AddDebugTriangleAABB(const Primitive::AABB3 &AABB, const DWORD &Color, bool bDepth);
        void AddDebugTriangleSphere(const VSSphere3 &Sphere, const DWORD &Color, bool bDepth);
        void AddDebugTriangleOBB(const VSOBB3 &OBB, const DWORD &Color, bool bDepth);
        bool m_bEnable;

    protected:
        struct DebugVertexType
        {
            Math::Vector3 Pos;
            DWORD Color;
        };
        Container::MArray<DebugVertexType> DepthDebugLineArray;
        Container::MArray<DebugVertexType> NoDepthDebugLineArray;

        VSMaterialRPtr m_pOnlyVertexColor;
        VSMaterialRPtr m_pOnlyVertexColorDisableDepth;
        VSVertexFormatPtr m_pDrawVertexFormat;

    public:
        void DrawDebugInfo(VSCamera *pCamera);
    };
    DECLARE_Ptr(VSDebugDraw);
}
