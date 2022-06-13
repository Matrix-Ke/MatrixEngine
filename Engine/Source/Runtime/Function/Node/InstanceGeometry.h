#pragma once
#include "Core/Object.h"
#include "Node/Geometry.h"
namespace Matrix
{
    struct INSTANCE_DATA_TYPE
    {
        INSTANCE_DATA_TYPE(const Math::VSTransform &t, unsigned int uiMaterialParaNum = 0)
        {
            T = t;
            MaterialData.SetBufferNum(uiMaterialParaNum);
        }
        Math::VSTransform T;
        Container::MArray<Container::MArray<VSREAL>> MaterialData;
    };
    class MATRIX_FUNCTION_API VSInstanceGeometry : public VSGeometry
    {
        // PRIORITY
        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL
    protected:
        unsigned int m_uiMaxInstanceNum;
        VSVertexFormatPtr m_pVertexFormat;
        unsigned int m_uiInstanceSize;
        unsigned char *GetCurDataBufferAddr(unsigned int i);

        bool bHasUpdate = false;

        VSVertexBufferPtr m_InstanceBuffer;
        unsigned char *m_pInstanceDataBuffer;
        unsigned int m_uiInstanceNum;
        // use for Multhread render
        bool m_bReCreate;
        VSVertexBufferPtr m_PendingDeleteInstanceBuffer;
        unsigned char *m_pInstanceDataRenderBuffer;

    public:
        VSInstanceGeometry();

        virtual ~VSInstanceGeometry();
        void SetMaxInstanceBuffer(Container::MArray<VSVertexFormat::VERTEXFORMAT_TYPE> &FormatArray, unsigned int uiMaxNum);
        inline VSVertexBuffer *GetInstanceVertexBuffer() const
        {
            return m_InstanceBuffer;
        }
        inline VSVertexFormat *GetInstanceVertexFormat() const
        {
            return m_pVertexFormat;
        }
        virtual void UpdateGeometryBeforeDrawCall();

    public:
        void CreateInstanceBuffer(VSMeshData *pSourceMeshData, VSMaterialR *pMaterial);
        void ClearInstanceData();
        unsigned int GetInstanceNum();
        unsigned int AddInstance(const Primitive::AABB3 WorldBound, const Math::VSTransform &T, VSMaterialInstance *pMaterialInstance, Container::MArray<ANIM_INSTANCE_SHADER_DATA> *pAnimData = NULL);
        static bool InitialDefaultState();
        static bool TerminalDefaultState();
        inline bool IsUsed() const
        {
            return m_uiInstanceNum > 0;
        }
        void UpdateWorldInstanceBound();
        bool HaveSkinInstance();
        VSTexAllStatePtr m_AnimInstanceTexture;
        unsigned int m_uiBoneNum = 0;
    };
    DECLARE_Ptr(VSInstanceGeometry);
    VSTYPE_MARCO(VSInstanceGeometry);

}
