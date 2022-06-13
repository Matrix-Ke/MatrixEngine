#pragma once
#include "Material.h"
#include "Shader.h"
#include "PShader.h"
#include "GShader.h"
#include "DShader.h"
#include "HShader.h"
#include "Node/NodeComponent/Light/Light.h"
#include "ResourceManager.h"
namespace Matrix
{
#define ms_LightShadowMatrix ms_ViewProjectMatrix
    class MATRIX_FUNCTION_API VSShaderStringFactory
    {
    public:
        static Container::MString ms_TextureInputCoordValue[UV_LEVEL];
        static Container::MString ms_PSOutputColorValue;
        static Container::MString ms_PSOutputColorValue1;

        static Container::MString ms_InputVertexID;
        static Container::MString ms_InputColor[2];
        static Container::MString ms_InputProjectZ;
        static Container::MString ms_InputLocalNormal;

        static Container::MString ms_InputLocalBinormal;
        static Container::MString ms_InputLocalTangent;
        static Container::MString ms_InputLocalPos;
        static Container::MString ms_InputWorldPos;
        static Container::MString ms_InputTessellationValue;
        static Container::MString ms_InputInstancePos[3];

        static Container::MString ms_InputInstanceAnimData;
        static Container::MString ms_InputInstanceAnimNum;

        static Container::MArray<Container::MString> ms_InputMaterialInstance;

        static VSUsedName ms_PSConstantShadowResource[MAX_DYNAMIC_LIGHT];
        static VSUsedName ms_PSConstantLightFunResource[MAX_DYNAMIC_LIGHT];
        static VSUsedName ms_PSOrenNayarLookUpTableResource;
        enum
        {
            SS_Shadow = VSEngineFlag::SS_SHARE_2L_B1 - 1,
            SS_LightFun = VSEngineFlag::SS_SHARE_2L_B0 - 1,
            SS_OrenNayarLookUpTable = VSEngineFlag::SS_SHARE_3L_W - 1,
        };

        static VSUsedName ms_VSMorphVDataResource;
        static VSUsedName ms_VSMorphNDataResource;
        static VSUsedName ms_VSMorphTDataResource;
        static VSUsedName ms_VSMorphBDataResource;

        static VSUsedName ms_VSAnimDataResource;

        static VSUsedName ms_PSColorBufferResource;
        static VSUsedName ms_PSDepthNormalBufferResource;

        static VSUsedName ms_ViewProjectMatrix;
        static VSUsedName ms_ViewMatrix;
        static VSUsedName ms_BoneMatrix;
        static VSUsedName ms_WorldMatrix;
        static VSUsedName ms_ProjectMatrix;

        static VSUsedName ms_MorphData; // x is Layer , y is Num
        static VSUsedName ms_MorphValue;

        static VSUsedName ms_AnimAllInfo; // x is bone Num, y is AnimDataTextureWidth,z is AnimDataTextureHeight

        static VSUsedName ms_LightWorldPos;
        static VSUsedName ms_LightWorldDirection;

        static VSUsedName ms_WorldNormal;
        static VSUsedName ms_VertexWorldNormal;

        static VSUsedName ms_ViewNormal;
        static VSUsedName ms_VertexViewNormal;

        static VSUsedName ms_TessellationValue;

        static VSUsedName ms_WorldPos;
        static VSUsedName ms_ViewPos;
        static VSUsedName ms_ProjectPos;

        static VSUsedName ms_ViewWorldDir;
        static VSUsedName ms_CameraWorldPos;

        static VSUsedName ms_LightColor;
        static VSUsedName ms_LightSpecular;
        static VSUsedName ms_LightDir;
        static VSUsedName ms_LightName[VSLight::LT_MAX];
        static VSUsedName ms_LightNameTemp[VSLight::LT_MAX];

        static VSUsedName ms_FarZ;
        static VSUsedName ms_PointLightRange;

        static VSUsedName ms_InvRTWidth;

        static VSUsedName ms_SkyLightUpColor;
        static VSUsedName ms_SkyLightDownColor;

        static VSUsedName ms_ShareSampler[VSEngineFlag::ms_uiShaderSamplerNum];
        static unsigned int ms_uiShareSamplerRegisterID[VSEngineFlag::ms_uiShaderSamplerNum];
        static unsigned int GetMaxShareSamplerRegisterID();

        static void AddShaderSamplerRegisterID(VSShader *pShader, unsigned int uiTexRegisterID, unsigned int ShareSamplerType);
        static unsigned int ms_uiCreateVShaderNum;
        static unsigned int ms_uiCreatePShaderNum;
        static unsigned int ms_uiCreateGShaderNum;
        static unsigned int ms_uiCreateHShaderNum;
        static unsigned int ms_uiCreateDShaderNum;

        static unsigned int ms_ShaderValueIndex;

        // Create Shader

        static bool CreateVShaderString(VSVShader *pVShader, MaterialShaderPara &MSPara, unsigned int uiShaderID, Container::MString &VShaderString
#if _DEBUG
                                        ,
                                        Container::MString &OutShaderFileName);
#else
        );
#endif
        static bool CreatePShaderString(VSPShader *pPShader, MaterialShaderPara &MSPara, unsigned int uiShaderID, Container::MString &PShaderString
#if _DEBUG
                                        ,
                                        Container::MString &OutShaderFileName);
#else
        );
#endif

        static bool CreateGShaderString(VSGShader *pGShader, MaterialShaderPara &MSPara, unsigned int uiShaderID, Container::MString &GShaderString
#if _DEBUG
                                        ,
                                        Container::MString &OutShaderFileName);
#else
        );
#endif
        static bool CreateHShaderString(VSHShader *pHShader, MaterialShaderPara &MSPara, unsigned int uiShaderID, Container::MString &HShaderString
#if _DEBUG
                                        ,
                                        Container::MString &OutShaderFileName);
#else
        );
#endif
        static bool CreateDShaderString(VSDShader *pDShader, MaterialShaderPara &MSPara, unsigned int uiShaderID, Container::MString &DShaderString
#if _DEBUG
                                        ,
                                        Container::MString &OutShaderFileName);
#else
        );
#endif

    protected:
        static void ClearAllString();
#if _DEBUG
        static void OutPutShaderLog(MaterialShaderPara &MSPara, unsigned int uiShaderID,
                                    const Container::MString &ShaderCode, Container::MString &OutShaderTextName);
#endif
    };

}
