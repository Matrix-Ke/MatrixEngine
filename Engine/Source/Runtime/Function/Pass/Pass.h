#pragma once
#include "Core/Object.h"
#include "Material/Shader/ShaderMap.h"
#include "ShaderKey.h"
#include "PShader.h"
#include "Shader.h"
#include "GShader.h"
#include "DShader.h"
#include "HShader.h"
#include "CShader.h"
#include "Matrix3X3W.h"
namespace Matrix
{
    class VSSpatial;
    class VSCamera;
    class MATRIX_FUNCTION_API VSPass : public MObject
    {
        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL_NO_CLASS_FACTORY
        enum // pass type
        {
            PT_MATERIAL,
            PT_INDIRECT,
            PT_NORMALDEPTH,
            PT_PREZ,
            PT_POINT_CUBE_SHADOW,
            PT_SHADOW,
            PT_DUAL_PARABOLOID_SHADOW,

            PT_POINT_VOLUME_SHADOW,
            PT_DIRECT_VOLUME_SHADOW,

            PT_LIGHT_FUNCTION,
            PT_POSTEFFECT,
            PT_MAX
        };

    public:
        virtual ~VSPass() = 0;

    protected:
        VSPass();
        VSShaderSet *m_pVShaderSet;
        VSShaderKey m_VShaderkey;

        VSShaderSet *m_pPShaderSet;
        VSShaderKey m_PShaderkey;

        VSShaderSet *m_pGShaderSet;
        VSShaderKey m_GShaderkey;

        VSShaderSet *m_pHShaderSet;
        VSShaderKey m_HShaderkey;

        VSShaderSet *m_pDShaderSet;
        VSShaderKey m_DShaderkey;
        MaterialShaderPara MSPara;

    public:
        inline void SetDrawContent(VSMaterialInstance *pMaterialInstance, VSGeometry *pGeometry,
                                   VSCamera *pCamera, unsigned int uiPassId)
        {
            MSPara.pCamera = pCamera;
            MSPara.pGeometry = pGeometry;
            MSPara.pMaterialInstance = pMaterialInstance;
            MSPara.uiPassId = uiPassId;
            MSPara.uiPassType = GetPassType();
        }
        virtual bool Draw(VSRenderer *pRenderer) = 0;
        virtual unsigned int GetPassType() = 0;

        bool GetPShader(VSShaderMap &ShaderMap, const VSUsedName &Name);
        bool GetVShader(VSShaderMap &ShaderMap, const VSUsedName &Name);
        bool GetGShader(VSShaderMap &ShaderMap, const VSUsedName &Name);
        bool GetHShader(VSShaderMap &ShaderMap, const VSUsedName &Name);
        bool GetDShader(VSShaderMap &ShaderMap, const VSUsedName &Name);
    };
    DECLARE_Ptr(VSPass);
    VSTYPE_MARCO(VSPass);
}
