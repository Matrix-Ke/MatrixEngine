#pragma once
#include "ShaderFunction.h"
#include "RenderState.h"
#include "ShaderKey.h"
#include "Shader.h"
#include "PShader.h"
#include "GShader.h"
#include "HShader.h"
#include "DShader.h"
#include "CShader.h"
namespace Matrix
{
    class VSLight;
    DECLARE_Ptr(VSLight);
    class MATRIX_FUNCTION_API VSShaderMainFunction : public VSShaderFunction
    {
        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL_NO_CLASS_FACTORY;

    public:
        enum
        {
            SM_PHONE,
            SM_OREN_NAYAR,
            SM_MINNAERT,
            SM_STRAUSS,
            SM_SHIRLEY,
            SM_SCHLICK,
            SM_COOKTOORANCE,
            SM_ISOTROPICWARD,
            SM_ANISOTROPICWARD,
            SM_CUSTOM,
            SM_MAX
        };
        VSShaderMainFunction(const VSUsedName &ShowName, VSMaterial *pMaterial);
        virtual ~VSShaderMainFunction() = 0;
        virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const = 0;
        virtual bool GetNormalDepthString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual bool GetIndirectRenderString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual bool GetCubShadowString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual bool GetShadowString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual bool GetSDualParaboloidhadowString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual inline unsigned int GetSMType() const = 0;
        inline void SetSRGBWrite(unsigned char uiVESRGBWrite)
        {
            m_uiVESRGBWrite = uiVESRGBWrite;
        }
        inline unsigned char GetSRGBWrite() const
        {
            return m_uiVESRGBWrite;
        }
        virtual bool HasNormal() const
        {
            if (GetNormalNode()->GetOutputLink())
            {
                return true;
            }
            return false;
        }

        virtual VSInputNode *GetNormalNode() const = 0;
        virtual VSInputNode *GetWorldOffsetNode() const = 0;
        virtual VSInputNode *GetTessellationValueNode() const = 0;
        virtual VSInputNode *GetWorldDisplacementNode() const = 0;
        virtual VSInputNode *GetAlphaNode() const = 0;
        virtual VSInputNode *GetEmissiveNode() const = 0;
        virtual VSInputNode *GetDiffuseNode() const = 0;
        virtual VSInputNode *GetReflectMipNode() const = 0;
        virtual VSInputNode *GetReflectPowNode() const = 0;
        virtual bool GetPShaderTreeString(Container::MString &OutString, MaterialShaderPara &MSPara);
        virtual bool GetInputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual bool GetVShaderTreeString(Container::MString &OutString, MaterialShaderPara &MSPara);
        virtual bool GetDShaderTreeString(Container::MString &OutString, MaterialShaderPara &MSPara);
        inline VSRenderState &GetRenderState()
        {
            return m_RenderState;
        }
        inline void SetBlendState(VSBlendState *pBlendState)
        {
            m_RenderState.SetBlendState(pBlendState);
        }
        inline void SetDepthStencilState(VSDepthStencilState *pDepthStencilState)
        {
            m_RenderState.SetDepthStencilState(pDepthStencilState);
        }
        inline void SetRasterizerState(VSRasterizerState *pRasterizerState)
        {
            m_RenderState.SetRasterizerState(pRasterizerState);
        }
        inline void AddClipPlane(const VSPlane3 &Plane)
        {
            m_RenderState.AddPlane(Plane);
        }
        inline void AddScissorRect(const VSRect2 &Rect)
        {
            m_RenderState.AddRect(Rect);
        }
        virtual void SetGlobleValue(MaterialShaderPara &MSPara, VSVShader *pVShader, VSPShader *pPShader,
                                    VSGShader *pGShader, VSHShader *pHShader, VSDShader *pDShader) {}
        virtual void ResetInShaderName(MaterialShaderPara &MSPara) {}
        virtual void GetLightShadow(MaterialShaderPara &MSPara, Container::MArray<Container::MString> ShadowStringArray[VSLight::LT_MAX]) const;
        virtual bool IsValidNodeToThis(VSShaderFunction *pShaderFunction, MaterialShaderPara &MSPara);

        inline void SetAlphaTestValue(VSREAL AlphaTestValue)
        {
            m_fAlphaTestValue = AlphaTestValue;
        }
        virtual bool HasTessellation();

    protected:
        VSShaderMainFunction();
        unsigned char m_uiVESRGBWrite;
        enum // Value Use String
        {
            VUS_WORLD_POS = BIT(1),
            VUS_VIEW_POS = BIT(2) | VUS_WORLD_POS,
            VUS_PROJ_POS = BIT(3) | VUS_VIEW_POS,

            VUS_WORLD_NORMAL = BIT(4),
            VUS_VIEW_NORMAL = BIT(5) | VUS_WORLD_NORMAL,

            VUS_VIEW_WORLD_DIR = BIT(6),

            VUS_ALL = VUS_PROJ_POS | VUS_VIEW_NORMAL | VUS_VIEW_WORLD_DIR,
        };
        void GetValueUseDeclareString(Container::MString &OutString, unsigned int uiValueUseString, MaterialShaderPara &MSPara);
        VSRenderState m_RenderState;

        VSREAL m_fAlphaTestValue;

        void GetValueUseString(Container::MString &OutString, unsigned int uiValueUseString, MaterialShaderPara &MSPara);
        void GetAlphaTestString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        void GetSRGBWriteString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

        void GetNormalString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

        void GetWorldOffsetString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

        void GetAlphaString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

        void GetEmissiveString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

        void GetDiffuseString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

        void GetReflectMipString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

        void GetReflectPowString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

        void GetTessellationValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

        void GetWorldDisplacementString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

        bool GetNormalInputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

        bool GetAlphaInputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

        bool GetEmissiveInputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

        bool GetDiffuseInputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

        bool GetReflectMipInputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

        bool GetReflectPowInputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

        bool GetWorldOffsetInputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

        bool GetTessellationValueInputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

        bool GetWorldDisplacementInputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const;

    public:
        enum
        {
            OUT_COLOR,
            OUT_MAX

        };
    };
    DECLARE_Ptr(VSShaderMainFunction);
    VSTYPE_MARCO(VSShaderMainFunction);
}
