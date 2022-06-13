#pragma once
#include "Renderer.h"
namespace Matrix
{
    class MATRIX_FUNCTION_API VSNullRenderer : public VSRenderer
    {
    public:
        VSNullRenderer();
        virtual ~VSNullRenderer();
        virtual int GetRendererType() const { return RAT_NULL; }
        virtual void ClearBuffers(unsigned int uiClearFlag);
        virtual void ClearBackBuffer();
        virtual void ClearZBuffer();
        virtual void ClearStencilBuffer();
        virtual void ClearBuffers();

        virtual void ClearBuffers(unsigned int uiClearFlag, int iXPos, int iYPos, int iWidth,
                                  int iHeight);
        virtual void ClearBackBuffer(int iXPos, int iYPos, int iWidth,
                                     int iHeight);
        virtual void ClearZBuffer(int iXPos, int iYPos, int iWidth,
                                  int iHeight);
        virtual void ClearStencilBuffer(int iXPos, int iYPos, int iWidth,
                                        int iHeight);
        virtual void ClearBuffers(int iXPos, int iYPos, int iWidth,
                                  int iHeight);

        virtual bool SetViewPort(VSViewPort *pViewPort = NULL);
        virtual bool UseWindow(int uiWindowID = -1);

        virtual bool CooperativeLevel();
        virtual bool BeginRendering();
        virtual bool EndRendering();

        virtual void DeviceLost();
        virtual void ResetDevice();
        virtual bool ChangeScreenSize(unsigned int uiWidth, unsigned int uiHeight, bool bWindow);
        virtual bool DrawMesh(VSGeometry *pGeometry, VSRenderState *pRenderState, VSVShader *pVShader, VSPShader *pPShader,
                              VSGShader *pGShader, VSHShader *pHShader, VSDShader *pDShader);
        virtual bool DrawScreen(SCREEN_QUAD_TYPE ScreenQuad[4]);
        virtual bool DrawScreen(SCREEN_QUAD_TYPE *pScreenBuffer, unsigned int uiVertexNum,
                                VSUSHORT_INDEX *pIndexBuffer, unsigned int uiIndexNum);
        virtual bool DrawScreenFont(SCREEN_FONT_TYPE *pScreenFontBuffer, unsigned int uiVertexNum,
                                    VSUSHORT_INDEX *pIndexBuffer, unsigned int uiIndexNum);
        virtual unsigned int SetBlendState(VSBlendState *pBlendState, bool bForceSet = false);
        virtual unsigned int SetDepthStencilState(VSDepthStencilState *pDepthStencilState, bool bForceSet = false);
        virtual unsigned int SetRasterizerState(VSRasterizerState *pRasterizerState, bool bForceSet = false);
        virtual void SetClipPlane(Container::MArray<VSPlane3> &Plane, bool bEnable);
        virtual void SetScissorRect(Container::MArray<VSRect2> &Rect, bool bEnable);

        virtual unsigned int SetVBuffer(VSVertexBuffer *pVBuffer, unsigned int uiStream = 0);
        virtual unsigned int SetIBuffer(VSIndexBuffer *pIBuffer);

        virtual unsigned int BeginQuery(VSQuery *pQuery);
        virtual unsigned int EndQuery(VSQuery *pQuery);

        virtual unsigned int SetPTexture(VSTexture *pTexture, unsigned int i);
        virtual unsigned int SetVTexture(VSTexture *pTexture, unsigned int i);
        virtual unsigned int SetGTexture(VSTexture *pTexture, unsigned int i);
        virtual unsigned int SetDTexture(VSTexture *pTexture, unsigned int i);
        virtual unsigned int SetHTexture(VSTexture *pTexture, unsigned int i);
        virtual unsigned int SetCTexture(VSTexture *pTexture, unsigned int i);
        virtual unsigned int SetCBufferResource(VSBufferResource *pBufferResource, unsigned int i);
        virtual unsigned int SetVBufferResource(VSBufferResource *pBufferResource, unsigned int i);
        virtual unsigned int SetPBufferResource(VSBufferResource *pBufferResource, unsigned int i);
        virtual unsigned int SetGBufferResource(VSBufferResource *pBufferResource, unsigned int i);
        virtual unsigned int SetHBufferResource(VSBufferResource *pBufferResource, unsigned int i);
        virtual unsigned int SetDBufferResource(VSBufferResource *pBufferResource, unsigned int i);
        virtual void Dispath(unsigned int uiThreadGroupCountX, unsigned int uiThreadGroupCountY,
                             unsigned int uiThreadGroupCountZ);

        virtual unsigned int SetPSamplerState(VSSamplerState *pSamplerState, unsigned int i, bool bForceSet = false);
        virtual unsigned int SetVSamplerState(VSSamplerState *pSamplerState, unsigned int i, bool bForceSet = false);
        virtual unsigned int SetGSamplerState(VSSamplerState *pSamplerState, unsigned int i, bool bForceSet = false);
        virtual unsigned int SetDSamplerState(VSSamplerState *pSamplerState, unsigned int i, bool bForceSet = false);
        virtual unsigned int SetHSamplerState(VSSamplerState *pSamplerState, unsigned int i, bool bForceSet = false);
        virtual unsigned int SetCSamplerState(VSSamplerState *pSamplerState, unsigned int i, bool bForceSet = false);

        virtual bool SetDepthStencilBuffer(VSDepthStencil *pDepthStencilBuffer);
        virtual bool EndDepthStencilBuffer(VSDepthStencil *pDepthStencilBuffer);
        virtual unsigned int GetTextureCompressLen(unsigned int uiLen);
        virtual const VSAdapterInfo *GetAdapterInfo(unsigned int &uiAdapterNum);

    protected:
        virtual void SetVShaderConstant(VSVShader *pShader);
        virtual void SetVShaderBindResource(VSVShader *pShader);
        virtual void SetPShaderConstant(VSPShader *pShader);
        virtual void SetPShaderBindResource(VSPShader *pShader);
        virtual void SetGShaderConstant(VSGShader *pShader);
        virtual void SetGShaderBindResource(VSGShader *pShader);
        virtual void SetDShaderConstant(VSDShader *pShader);
        virtual void SetDShaderBindResource(VSDShader *pShader);
        virtual void SetHShaderConstant(VSHShader *pShader);
        virtual void SetHShaderBindResource(VSHShader *pShader);
        virtual void SetCShaderConstant(VSCShader *pShader);
        virtual void SetCShaderBindResource(VSCShader *pShader);

        virtual bool SetVShaderProgram(VSVShader *pVShaderProgram);
        virtual bool SetPShaderProgram(VSPShader *pPShaderProgram);
        virtual bool SetGShaderProgram(VSGShader *pGShaderProgram);
        virtual bool SetDShaderProgram(VSDShader *pDShaderProgram);
        virtual bool SetHShaderProgram(VSHShader *pHShaderProgram);
        virtual bool SetCShaderProgram(VSCShader *pCShaderProgram);
        // Load Release
        virtual bool OnLoadVShaderProgram(VSVShader *pVShaderProgram, VSResourceIdentifier *&pID);

        virtual bool OnLoadPShaderProgram(VSPShader *pPShaderProgram, VSResourceIdentifier *&pID);

        virtual bool OnLoadGShaderProgram(VSGShader *pGShaderProgram, VSResourceIdentifier *&pID);

        virtual bool OnLoadDShaderProgram(VSDShader *pDShaderProgram, VSResourceIdentifier *&pID);

        virtual bool OnLoadHShaderProgram(VSHShader *pHShaderProgram, VSResourceIdentifier *&pID);

        virtual bool OnLoadCShaderProgram(VSCShader *pCShaderProgram, VSResourceIdentifier *&pID);

        virtual bool OnLoadTexture(VSTexture *pTexture, VSResourceIdentifier *&pID);

        virtual bool OnLoadDepthStencil(VSDepthStencil *pDepthStencil, VSResourceIdentifier *&pID);

        virtual bool OnLoadRenderTarget(VSRenderTarget *pRenderTarget, VSResourceIdentifier *&pID);

        virtual bool OnLoadUnorderAccess(VSBufferUnorderAccess *pUnorderAccess, VSResourceIdentifier *&pID);
        virtual bool OnLoadUnorderAccess(VSTextureUnorderAccess *pUnorderAccess, VSResourceIdentifier *&pID);

        virtual bool OnLoadVBufferData(VSVertexBuffer *pVBuffer, VSResourceIdentifier *&pID);

        virtual bool OnLoadVBufferFormat(VSVertexFormat *pVertexFormat, VSResourceIdentifier *&pID);

        virtual bool OnLoadIBuffer(VSIndexBuffer *pIBuffer, VSResourceIdentifier *&pID);

        virtual bool OnLoadSBuffer(VSBufferResource *pSBuffer, VSResourceIdentifier *&pID);

        virtual bool OnLoadBlendState(VSBlendState *pBlendState, VSResourceIdentifier *&pID);

        virtual bool OnLoadDepthStencilState(VSDepthStencilState *pDepthStencilState, VSResourceIdentifier *&pID);

        virtual bool OnLoadRasterizerState(VSRasterizerState *pRasterizerState, VSResourceIdentifier *&pID);

        virtual bool OnLoadSamplerState(VSSamplerState *pSamplerState, VSResourceIdentifier *&pID);

        virtual bool OnLoadQuery(VSQuery *pQuery, VSResourceIdentifier *&pID);

        virtual unsigned int SetVertexFormat(VSVertexFormat *pVertexFormat);

        virtual void *Lock(VSVertexBuffer *pVertexBuffer);
        virtual void UnLock(VSVertexBuffer *pVertexBuffer);

        virtual void *Lock(VSIndexBuffer *pIndexBuffer);
        virtual void UnLock(VSIndexBuffer *pIndexBuffer);

        virtual void *Lock(VSBufferResource *pStructBuffer);
        virtual void UnLock(VSBufferResource *pStructBuffer);

        virtual void *Lock(VSTexture *pTexture, unsigned int uiLevel, unsigned int uiFace);
        virtual void UnLock(VSTexture *pTexture, unsigned int uiLevel, unsigned int uiFace);

        virtual void *Lock(VSRenderTarget *pRenderTarget);
        virtual void UnLock(VSRenderTarget *pRenderTarget);

        virtual void *Lock(VSUnorderAccess *pUnorderAccess);
        virtual void UnLock(VSUnorderAccess *pUnorderAccess);

        virtual void *Lock(VSDepthStencil *pDepthStencil);
        virtual void UnLock(VSDepthStencil *pDepthStencil);

        virtual bool GetData(VSQuery *pQuery, void *pData, unsigned int uiSize);

        virtual bool CopyResourceBuffer(VS2DTexture *pSource, VSCubeTexture *pDest, unsigned int uiFace);

    public:
        // shader function
        virtual Container::MString TexColorBuffer(const VSColorBuffer *pColorBuffer) const;
        virtual Container::MString Tex2D(const VS2DTexSampler *p2DTexSampler, unsigned int uiShaderType) const;
        virtual Container::MString Tex1D(const VS1DTexSampler *p1DTexSampler, unsigned int uiShaderType) const;
        virtual Container::MString Mul(const VSMul *pMul) const;
        virtual Container::MString Div(const VSDiv *pDiv) const;
        virtual Container::MString Dot(const VSDot *pDot) const;
        virtual Container::MString Length(const VSLength *pLength) const;
        virtual Container::MString Sub(const VSSub *pSub) const;
        virtual Container::MString Add(const VSAdd *pAdd) const;
        virtual Container::MString MakeValue(const VSMakeValue *pMakeValue) const;
        virtual Container::MString Saturate(const VSSaturate *pSaturate) const;

        virtual Container::MString FloatByChannelNum(unsigned int ChannelNum) const;
        virtual Container::MString Float() const;
        virtual Container::MString Float2() const;
        virtual Container::MString Float3() const;
        virtual Container::MString Float4() const;
        virtual Container::MString Return() const;

        virtual Container::MString FloatConst(const Container::MString &Value1) const;
        virtual Container::MString Float2Const(const Container::MString &Value1, const Container::MString &Value2) const;
        virtual Container::MString Float3Const(const Container::MString &Value1,
                                     const Container::MString &Value2, const Container::MString &Value3) const;
        virtual Container::MString Float4Const(const Container::MString &Value1, const Container::MString &Value2,
                                     const Container::MString &Value3, const Container::MString &Value4) const;

        virtual void CustomPointLightUseString(Container::MString &PointLightUseString, Container::MString &PointAttenuationDivString);

        virtual void CustomSpotLightUseString(Container::MString &SpotLightUseString, Container::MString &SpotAttenuationDivString);

        virtual Container::MString GetDeclareValue(const Container::MString &ShowName, unsigned int uiValueType, unsigned int uiRegisterIndex) const;
        virtual Container::MString GetDeclareSampler(const Container::MString &ShowName, unsigned int SamplerType, unsigned int uiRegisterIndex, unsigned int SamplerSource) const;
        virtual void GetDeclareShareSampler(unsigned int SamplerSource, unsigned int uiRegisterIndex, Container::MString &OutString) const;
        // shader custom function
        virtual void CreateVInputDeclare(MaterialShaderPara &MSPara,
                                         Container::MString &OutString);
        virtual void CreateVOutputDeclare(MaterialShaderPara &MSPara,
                                          Container::MString &OutString);
        virtual void CreateVUserConstant(VSVShader *pVShader, MaterialShaderPara &MSPara,
                                         Container::MString &OutString);
        virtual void CreateVFunction(MaterialShaderPara &MSPara,
                                     Container::MString &OutString);

        virtual void SetMaterialVShaderConstant(MaterialShaderPara &MSPara, VSVShader *pVShader);

        virtual void CreatePInputDeclare(MaterialShaderPara &MSPara,
                                         Container::MString &OutString);
        virtual void CreatePOutputDeclare(MaterialShaderPara &MSPara,
                                          Container::MString &OutString);
        virtual void CreatePUserConstant(VSPShader *pPShader, MaterialShaderPara &MSPara,
                                         Container::MString &OutString);
        virtual void CreatePFunction(MaterialShaderPara &MSPara,
                                     Container::MString &OutString);

        virtual void SetMaterialPShaderConstant(MaterialShaderPara &MSPara, VSPShader *pPShader);

        virtual void CreateGInputDeclare(MaterialShaderPara &MSPara,
                                         Container::MString &OutString);
        virtual void CreateGOutputDeclare(MaterialShaderPara &MSPara,
                                          Container::MString &OutString);
        virtual void CreateGUserConstant(VSGShader *pGShader, MaterialShaderPara &MSPara,
                                         Container::MString &OutString);
        virtual void CreateGFunction(MaterialShaderPara &MSPara,
                                     Container::MString &OutString);
        virtual void SetMaterialGShaderConstant(MaterialShaderPara &MSPara, VSGShader *pGShader);

        virtual void CreateHInputDeclare(MaterialShaderPara &MSPara,
                                         Container::MString &OutString);
        virtual void CreateHOutputDeclare(MaterialShaderPara &MSPara,
                                          Container::MString &OutString);
        virtual void CreateHUserConstant(VSHShader *pHShader, MaterialShaderPara &MSPara,
                                         Container::MString &OutString);
        virtual void CreateHFunction(MaterialShaderPara &MSPara,
                                     Container::MString &OutString);
        virtual void SetMaterialHShaderConstant(MaterialShaderPara &MSPara, VSHShader *pHShader);

        virtual void CreateDInputDeclare(MaterialShaderPara &MSPara,
                                         Container::MString &OutString);
        virtual void CreateDOutputDeclare(MaterialShaderPara &MSPara,
                                          Container::MString &OutString);
        virtual void CreateDUserConstant(VSDShader *pDShader, MaterialShaderPara &MSPara,
                                         Container::MString &OutString);
        virtual void CreateDFunction(MaterialShaderPara &MSPara,
                                     Container::MString &OutString);
        virtual void SetMaterialDShaderConstant(MaterialShaderPara &MSPara, VSDShader *pDShader);

        virtual void GetIncludeShader(Container::MString &OutString);

        virtual void GetDynamicShader(Container::MString &OutString);

        virtual void SkyLight(const Container::MString &WorldNormal, const Container::MString &UpColor, const Container::MString &DownColor, const Container::MString &DiffuseColor, Container::MString &OutString);
        virtual void DirectionalLight(int iLightNum, const Container::MString &Diffuse, const Container::MString &Specular, const Container::MString &SpecularPow,
                                      const Container::MString &WorldNormal, const Container::MString &WorldCameraDir, Container::MArray<Container::MString> ShadowString,
                                      Container::MString &OutString) const;
        virtual void CustomDirectionalLight(int iLightNum, const Container::MString &CustomString, Container::MArray<Container::MString> ShadowString, Container::MString &OutString) const;

        virtual void OrenNayarDirectionalLight(int iLightNum, const Container::MString &Diffuse, const Container::MString &RoughnessSquared,
                                               const Container::MString &WorldNormal, const Container::MString &WorldCameraDir, bool bLookUpTable, Container::MArray<Container::MString> ShadowString,
                                               Container::MString &OutString) const;

        virtual void PointLight(int iLightNum, const Container::MString &Diffuse, const Container::MString &Specular, const Container::MString &SpecularPow,
                                const Container::MString &WorldPos, const Container::MString &WorldNormal, const Container::MString &WorldCameraDir, Container::MArray<Container::MString> ShadowString,
                                Container::MString &OutString) const;
        virtual void CustomPointLight(int iLightNum, const Container::MString &CustomString, const Container::MString &WorldPos, Container::MArray<Container::MString> ShadowString, Container::MString &OutString) const;

        virtual void OrenNayarPointLight(int iLightNum, const Container::MString &Diffuse, const Container::MString &RoughnessSquared,
                                         const Container::MString &WorldPos, const Container::MString &WorldNormal, const Container::MString &WorldCameraDir, bool bLookUpTable, Container::MArray<Container::MString> ShadowString,
                                         Container::MString &OutString) const;

        virtual void SpotLight(int iLightNum, const Container::MString &Diffuse, const Container::MString &Specular, const Container::MString &SpecularPow,
                               const Container::MString &WorldPos, const Container::MString &WorldNormal, const Container::MString &WorldCameraDir, Container::MArray<Container::MString> ShadowString,
                               Container::MString &OutString) const;
        virtual void CustomSpotLight(int iLightNum, const Container::MString &CustomString, const Container::MString &WorldPos, Container::MArray<Container::MString> ShadowString, Container::MString &OutString) const;
        virtual void OrenNayarSpotLight(int iLightNum, const Container::MString &Diffuse, const Container::MString &RoughnessSquared,
                                        const Container::MString &WorldPos, const Container::MString &WorldNormal, const Container::MString &WorldCameraDir, bool bLookUpTable, Container::MArray<Container::MString> ShadowString,
                                        Container::MString &OutString) const;

        virtual void LocalToWorldPos(const Container::MString &LocalPos, Container::MString &OutString) const;
        virtual void WorldToViewPos(const Container::MString &LocalPos, Container::MString &OutString) const;

        virtual void LocalToWorldNormal(const Container::MString &LocalNormal, Container::MString &OutString) const;

        virtual void WorldToViewNormal(const Container::MString &WorldNormal, Container::MString &OutString) const;

        virtual void GetWorldViewDir(Container::MString &OutString) const;

        virtual void TransProjPos(const Container::MString &Pos, const Container::MString &Matrix, Container::MString &OutString) const;
        virtual void BumpNormal(const Container::MString &TexNormal, Container::MString &OutString) const;

        virtual void ComputeDir(const Container::MString &Orgin, const Container::MString &End, Container::MString &OutString) const;
        virtual void ComputeLength(const Container::MString &Orgin, const Container::MString &End, Container::MString &OutString) const;
        virtual void ComputeBoneVector(const Container::MString &BoneIndex, const Container::MString &BoneWeight, const Container::MString &BoneVector,
                                       const Container::MString &U, const Container::MString &V, const Container::MString &N, Container::MString &OutString) const;
        virtual void ComputeBoneVector(const Container::MString &BoneIndex, const Container::MString &BoneWeight,
                                       const Container::MString &AnimDataResource, const Container::MString &AnimAllInfo,
                                       const Container::MString &AnimInstanceInfo, const Container::MString &AnimNum,
                                       const Container::MString &U, const Container::MString &V, const Container::MString &N, Container::MString &OutString) const;

        virtual void BoneTranPos(const Container::MString &LocalPos, const Container::MString &U, const Container::MString &V, const Container::MString &N, Container::MString &OutString) const;
        virtual void BoneTranNormal(const Container::MString &LocalNormal, const Container::MString &U, const Container::MString &V, const Container::MString &N, Container::MString &OutString) const;

        virtual void DecodeNormal1(const Container::MString &Normal, Container::MString &OutString) const;
        virtual void RecodeNormal1(const Container::MString &Normal, Container::MString &OutString) const;
        virtual void DecodeNormal2(const Container::MString &Normal, const Container::MString &Tengent, Container::MString &OutString) const;

        virtual void DecodeNormal3(const Container::MString &Normal, Container::MString &OutString) const;
        virtual void RecodeNormal3(const Container::MString &Normal, Container::MString &OutString) const;

        virtual void Reciprocal(const Container::MString &Value, Container::MString &OutString) const;
        virtual void Clip(const Container::MString &ClipValue, Container::MString &OutString) const;
        virtual void GreaterZeroPow(const Container::MString &Value, VSREAL Exp, Container::MString &OutString) const;
        virtual void SaturatePow(const Container::MString &Value, VSREAL Exp, Container::MString &OutString) const;
        virtual void Saturate(const Container::MString &Value, Container::MString &OutString) const;

        virtual void PointLightCubeShadow(const Container::MString &PointLightName, const Container::MString &CubeShadowSampler, const Container::MString &ViewMatrix,
                                          const Container::MString &WorldPos, Container::MString &OutString) const;

        virtual void PointLightCubeShadow(const Container::MString &PointLightName, const Container::MString &CubeShadowSampler,
                                          const Container::MString &WorldPos, Container::MString &OutString) const;

        virtual void PointLightVolumeShadow(const Container::MString &PointLightName, const Container::MString &VolumeShadowSampler,
                                            const Container::MString &WorldPos, Container::MString &OutString) const;

        virtual void PointLightDualParaboloidShadow(const Container::MString &PointLightName, const Container::MString &ShadowSampler,
                                                    const Container::MString &WorldPos, Container::MString &OutString) const;
        virtual void DirectionLightVolumeShadow(const Container::MString &DirLightName, const Container::MString &VolumeShadowSampler,
                                                const Container::MString &WorldPos, Container::MString &OutString) const;

        virtual void DirectionLightCSMShadow(const Container::MString &DirLightName, const Container::MString &ShadowSampler,
                                             const Container::MString &WorldPos, const Container::MString &ViewPos, const Container::MString &FarZ, Container::MString &OutString) const;

        virtual void DirectionLightShadow(const Container::MString &DirLightName, const Container::MString &ShadowSampler,
                                          const Container::MString &WorldPos, Container::MString &OutString) const;

        virtual void SpotLightShadow(const Container::MString &SpotLightName, const Container::MString &ShadowSampler,
                                     const Container::MString &WorldPos, Container::MString &OutString) const;

        virtual void TranLightToTemp(Container::MArray<VSLight *> LightArray, Container::MString &OutString) const;

        virtual void GetLightFunction(Container::MArray<VSLight *> LightArray, const Container::MString &WorldPos, Container::MString &OutString) const;

        virtual void EncodeReflect(const Container::MString &Mip, const Container::MString &Pow, Container::MString &OutString);

        virtual void DecodeReflect(const Container::MString &Mip, const Container::MString &Pow, const Container::MString &Value, Container::MString &OutString);
    };

}
