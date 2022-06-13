#include "NullRenderer.h"
#include "Core/GraphicInclude.h"
using namespace Matrix;
VSNullRenderer::VSNullRenderer()
{
}
VSNullRenderer::~VSNullRenderer()
{
    ReleaseDefaultValue();
}
void VSNullRenderer::ClearBuffers(unsigned int uiClearFlag)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::ClearBackBuffer()
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::ClearZBuffer()
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::ClearStencilBuffer()
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::ClearBuffers()
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::ClearBuffers(unsigned int uiClearFlag, int iXPos, int iYPos, int iWidth,
                                  int iHeight)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::ClearBackBuffer(int iXPos, int iYPos, int iWidth,
                                     int iHeight)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::ClearZBuffer(int iXPos, int iYPos, int iWidth,
                                  int iHeight)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::ClearStencilBuffer(int iXPos, int iYPos, int iWidth,
                                        int iHeight)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::ClearBuffers(int iXPos, int iYPos, int iWidth,
                                  int iHeight)
{
    ENGINE_ASSERT(0);
    return;
}
bool VSNullRenderer::SetViewPort(VSViewPort *pViewPort)
{
    ENGINE_ASSERT(0);
    return 0;
}
bool VSNullRenderer::UseWindow(int uiWindowID)
{
    ENGINE_ASSERT(0);
    return 0;
}

bool VSNullRenderer::CooperativeLevel()
{
    ENGINE_ASSERT(0);
    return 0;
}
bool VSNullRenderer::BeginRendering()
{
    ENGINE_ASSERT(0);
    return 0;
}
bool VSNullRenderer::EndRendering()
{
    ENGINE_ASSERT(0);
    return 0;
}

void VSNullRenderer::DeviceLost()
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::ResetDevice()
{
    ENGINE_ASSERT(0);
    return;
}
bool VSNullRenderer::ChangeScreenSize(unsigned int uiWidth, unsigned int uiHeight, bool bWindow)
{
    ENGINE_ASSERT(0);
    return 0;
}
bool VSNullRenderer::DrawMesh(VSGeometry *pGeometry, VSRenderState *pRenderState, VSVShader *pVShader, VSPShader *pPShader,
                              VSGShader *pGShader, VSHShader *pHShader, VSDShader *pDShader)
{
    ENGINE_ASSERT(0);
    return 0;
}
bool VSNullRenderer::DrawScreen(SCREEN_QUAD_TYPE ScreenQuad[4])
{
    ENGINE_ASSERT(0);
    return 0;
}
bool VSNullRenderer::DrawScreen(SCREEN_QUAD_TYPE *pScreenBuffer, unsigned int uiVertexNum,
                                VSUSHORT_INDEX *pIndexBuffer, unsigned int uiIndexNum)
{
    ENGINE_ASSERT(0);
    return 0;
}
bool VSNullRenderer::DrawScreenFont(SCREEN_FONT_TYPE *pScreenFontBuffer, unsigned int uiVertexNum,
                                    VSUSHORT_INDEX *pIndexBuffer, unsigned int uiIndexNum)
{
    ENGINE_ASSERT(0);
    return 0;
}
const VSAdapterInfo *VSNullRenderer::GetAdapterInfo(unsigned int &uiAdapterNum)
{
    ENGINE_ASSERT(0);
    return NULL;
}
unsigned int VSNullRenderer::SetBlendState(VSBlendState *pBlendState, bool bForceSet)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::SetDepthStencilState(VSDepthStencilState *pDepthStencilState, bool bForceSet)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::SetRasterizerState(VSRasterizerState *pRasterizerState, bool bForceSet)
{
    ENGINE_ASSERT(0);
    return 0;
}
void VSNullRenderer::SetClipPlane(Container::MArray<VSPlane3> &Plane, bool bEnable)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::SetScissorRect(Container::MArray<VSRect2> &Rect, bool bEnable)
{
    ENGINE_ASSERT(0);
    return;
}

unsigned int VSNullRenderer::SetVBuffer(VSVertexBuffer *pVBuffer, unsigned int uiStream)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::SetIBuffer(VSIndexBuffer *pIBuffer)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::BeginQuery(VSQuery *pQuery)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::EndQuery(VSQuery *pQuery)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::SetPTexture(VSTexture *pTexture, unsigned int i)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::SetVTexture(VSTexture *pTexture, unsigned int i)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::SetGTexture(VSTexture *pTexture, unsigned int i)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::SetDTexture(VSTexture *pTexture, unsigned int i)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::SetHTexture(VSTexture *pTexture, unsigned int i)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::SetCTexture(VSTexture *pTexture, unsigned int i)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::SetCBufferResource(VSBufferResource *pBufferResource, unsigned int i)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::SetVBufferResource(VSBufferResource *pBufferResource, unsigned int i)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::SetPBufferResource(VSBufferResource *pBufferResource, unsigned int i)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::SetGBufferResource(VSBufferResource *pBufferResource, unsigned int i)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::SetHBufferResource(VSBufferResource *pBufferResource, unsigned int i)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::SetDBufferResource(VSBufferResource *pBufferResource, unsigned int i)
{
    ENGINE_ASSERT(0);
    return 0;
}
void VSNullRenderer::Dispath(unsigned int uiThreadGroupCountX, unsigned int uiThreadGroupCountY,
                             unsigned int uiThreadGroupCountZ)
{
    ENGINE_ASSERT(0);
    return;
}
unsigned int VSNullRenderer::SetPSamplerState(VSSamplerState *pSamplerState, unsigned int i, bool bForceSet)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::SetVSamplerState(VSSamplerState *pSamplerState, unsigned int i, bool bForceSet)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::SetGSamplerState(VSSamplerState *pSamplerState, unsigned int i, bool bForceSet)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::SetDSamplerState(VSSamplerState *pSamplerState, unsigned int i, bool bForceSet)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::SetHSamplerState(VSSamplerState *pSamplerState, unsigned int i, bool bForceSet)
{
    ENGINE_ASSERT(0);
    return 0;
}
unsigned int VSNullRenderer::SetCSamplerState(VSSamplerState *pSamplerState, unsigned int i, bool bForceSet)
{
    ENGINE_ASSERT(0);
    return 0;
}

bool VSNullRenderer::SetDepthStencilBuffer(VSDepthStencil *pDepthStencilBuffer)
{
    ENGINE_ASSERT(0);
    return 0;
}
bool VSNullRenderer::EndDepthStencilBuffer(VSDepthStencil *pDepthStencilBuffer)
{
    ENGINE_ASSERT(0);
    return 0;
}
void VSNullRenderer::SetVShaderConstant(VSVShader *pShader)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::SetVShaderBindResource(VSVShader *pShader)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::SetPShaderConstant(VSPShader *pShader)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::SetPShaderBindResource(VSPShader *pShader)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::SetGShaderConstant(VSGShader *pShader)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::SetGShaderBindResource(VSGShader *pShader)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::SetDShaderConstant(VSDShader *pShader)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::SetDShaderBindResource(VSDShader *pShader)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::SetHShaderConstant(VSHShader *pShader)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::SetHShaderBindResource(VSHShader *pShader)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::SetCShaderConstant(VSCShader *pShader)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::SetCShaderBindResource(VSCShader *pShader)
{
    ENGINE_ASSERT(0);
    return;
}

bool VSNullRenderer::SetVShaderProgram(VSVShader *pVShaderProgram)
{
    ENGINE_ASSERT(0);
    return 0;
}
bool VSNullRenderer::SetPShaderProgram(VSPShader *pPShaderProgram)
{
    ENGINE_ASSERT(0);
    return 0;
}
bool VSNullRenderer::SetGShaderProgram(VSGShader *pGShaderProgram)
{
    ENGINE_ASSERT(0);
    return 0;
}
bool VSNullRenderer::SetDShaderProgram(VSDShader *pDShaderProgram)
{
    ENGINE_ASSERT(0);
    return 0;
}
bool VSNullRenderer::SetHShaderProgram(VSHShader *pHShaderProgram)
{
    ENGINE_ASSERT(0);
    return 0;
}
bool VSNullRenderer::SetCShaderProgram(VSCShader *pCShaderProgram)
{
    ENGINE_ASSERT(0);
    return 0;
}
// Load Release
bool VSNullRenderer::OnLoadVShaderProgram(VSVShader *pVShaderProgram, VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(0);
    return 0;
}

bool VSNullRenderer::OnLoadPShaderProgram(VSPShader *pPShaderProgram, VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(0);
    return 0;
}

bool VSNullRenderer::OnLoadGShaderProgram(VSGShader *pGShaderProgram, VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(0);
    return 0;
}

bool VSNullRenderer::OnLoadDShaderProgram(VSDShader *pDShaderProgram, VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(0);
    return 0;
}

bool VSNullRenderer::OnLoadHShaderProgram(VSHShader *pHShaderProgram, VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(0);
    return 0;
}

bool VSNullRenderer::OnLoadCShaderProgram(VSCShader *pCShaderProgram, VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(0);
    return 0;
}

bool VSNullRenderer::OnLoadTexture(VSTexture *pTexture, VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(0);
    return 0;
}

bool VSNullRenderer::OnLoadDepthStencil(VSDepthStencil *pDepthStencil, VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(0);
    return 0;
}

bool VSNullRenderer::OnLoadRenderTarget(VSRenderTarget *pRenderTarget, VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(0);
    return 0;
}

bool VSNullRenderer::OnLoadUnorderAccess(VSBufferUnorderAccess *pUnorderAccess, VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(0);
    return 0;
}
bool VSNullRenderer::OnLoadUnorderAccess(VSTextureUnorderAccess *pUnorderAccess, VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(0);
    return 0;
}

bool VSNullRenderer::OnLoadVBufferData(VSVertexBuffer *pVBuffer, VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(0);
    return 0;
}

bool VSNullRenderer::OnLoadVBufferFormat(VSVertexFormat *pVertexFormat, VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(0);
    return 0;
}

bool VSNullRenderer::OnLoadIBuffer(VSIndexBuffer *pIBuffer, VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(0);
    return 0;
}

bool VSNullRenderer::OnLoadSBuffer(VSBufferResource *pSBuffer, VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(0);
    return 0;
}

bool VSNullRenderer::OnLoadBlendState(VSBlendState *pBlendState, VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(0);
    return 0;
}

bool VSNullRenderer::OnLoadDepthStencilState(VSDepthStencilState *pDepthStencilState, VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(0);
    return 0;
}

bool VSNullRenderer::OnLoadRasterizerState(VSRasterizerState *pRasterizerState, VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(0);
    return 0;
}

bool VSNullRenderer::OnLoadSamplerState(VSSamplerState *pSamplerState, VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(0);
    return 0;
}

bool VSNullRenderer::OnLoadQuery(VSQuery *pQuery, VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(0);
    return 0;
}

unsigned int VSNullRenderer::SetVertexFormat(VSVertexFormat *pVertexFormat)
{
    ENGINE_ASSERT(0);
    return 0;
}

void *VSNullRenderer::Lock(VSVertexBuffer *pVertexBuffer)
{
    ENGINE_ASSERT(0);
    return NULL;
}
void VSNullRenderer::UnLock(VSVertexBuffer *pVertexBuffer)
{
    ENGINE_ASSERT(0);
    return;
}

void *VSNullRenderer::Lock(VSIndexBuffer *pIndexBuffer)
{
    ENGINE_ASSERT(0);
    return NULL;
}
void VSNullRenderer::UnLock(VSIndexBuffer *pIndexBuffer)
{
    ENGINE_ASSERT(0);
    return;
}

void *VSNullRenderer::Lock(VSBufferResource *pStructBuffer)
{
    ENGINE_ASSERT(0);
    return NULL;
}
void VSNullRenderer::UnLock(VSBufferResource *pStructBuffer)
{
    ENGINE_ASSERT(0);
    return;
}

void *VSNullRenderer::Lock(VSTexture *pTexture, unsigned int uiLevel, unsigned int uiFace)
{
    ENGINE_ASSERT(0);
    return NULL;
}
void VSNullRenderer::UnLock(VSTexture *pTexture, unsigned int uiLevel, unsigned int uiFace)
{
    ENGINE_ASSERT(0);
    return;
}

bool VSNullRenderer::CopyResourceBuffer(VS2DTexture *pSource, VSCubeTexture *pDest, unsigned int uiFace)
{
    ENGINE_ASSERT(0);
    return 0;
}

bool VSNullRenderer::GetData(VSQuery *pQuery, void *pData, unsigned int uiSize)
{
    ENGINE_ASSERT(0);
    return NULL;
};

void *VSNullRenderer::Lock(VSRenderTarget *pRenderTarget)
{
    ENGINE_ASSERT(0);
    return NULL;
};
void VSNullRenderer::UnLock(VSRenderTarget *pRenderTarget)
{
    ENGINE_ASSERT(0);
    return;
};

void *VSNullRenderer::Lock(VSUnorderAccess *pUnorderAccess)
{
    ENGINE_ASSERT(0);
    return NULL;
};
void VSNullRenderer::UnLock(VSUnorderAccess *pUnorderAccess)
{
    ENGINE_ASSERT(0);
    return;
};

void *VSNullRenderer::Lock(VSDepthStencil *pDepthStencil)
{
    ENGINE_ASSERT(0);
    return NULL;
};
void VSNullRenderer::UnLock(VSDepthStencil *pDepthStencil)
{
    ENGINE_ASSERT(0);
    return;
};

Container::MString VSNullRenderer::Tex2D(const VS2DTexSampler *p2DTexSampler, unsigned int uiShaderType) const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}
Container::MString VSNullRenderer::Tex1D(const VS1DTexSampler *p1DTexSampler, unsigned int uiShaderType) const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}
Container::MString VSNullRenderer::TexColorBuffer(const VSColorBuffer *pColorBuffer) const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}
Container::MString VSNullRenderer::Mul(const VSMul *pMul) const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}
Container::MString VSNullRenderer::Saturate(const VSSaturate *pSaturate) const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}
Container::MString VSNullRenderer::Div(const VSDiv *pDiv) const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}
Container::MString VSNullRenderer::Dot(const VSDot *pDot) const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}
Container::MString VSNullRenderer::Length(const VSLength *pLength) const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}
Container::MString VSNullRenderer::Sub(const VSSub *pSub) const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}
Container::MString VSNullRenderer::Add(const VSAdd *pAdd) const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}
Container::MString VSNullRenderer::MakeValue(const VSMakeValue *pMakeValue) const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}

Container::MString VSNullRenderer::FloatByChannelNum(unsigned int ChannelNum) const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}
Container::MString VSNullRenderer::Float() const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}
Container::MString VSNullRenderer::Float2() const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}
Container::MString VSNullRenderer::Float3() const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}
Container::MString VSNullRenderer::Float4() const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}
Container::MString VSNullRenderer::Return() const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}

Container::MString VSNullRenderer::GetDeclareValue(const Container::MString &ShowName, unsigned int uiValueType, unsigned int uiRegisterIndex) const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}
Container::MString VSNullRenderer::GetDeclareSampler(const Container::MString &ShowName, unsigned int SamplerType, unsigned int uiRegisterIndex, unsigned int SamplerSource) const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}
void VSNullRenderer::GetDeclareShareSampler(unsigned int SamplerSource, unsigned int uiRegisterIndex, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}
Container::MString VSNullRenderer::FloatConst(const Container::MString &Value1) const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}
Container::MString VSNullRenderer::Float2Const(const Container::MString &Value1, const Container::MString &Value2) const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}
Container::MString VSNullRenderer::Float3Const(const Container::MString &Value1,
                                               const Container::MString &Value2, const Container::MString &Value3) const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}
Container::MString VSNullRenderer::Float4Const(const Container::MString &Value1, const Container::MString &Value2,
                                               const Container::MString &Value3, const Container::MString &Value4) const
{
    ENGINE_ASSERT(0);
    return Container::MString::ms_StringNULL;
}

void VSNullRenderer::CustomPointLightUseString(Container::MString &PointLightUseString, Container::MString &PointAttenuationDivString)
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::CustomSpotLightUseString(Container::MString &SpotLightUseString, Container::MString &SpotAttenuationDivString)
{
    ENGINE_ASSERT(0);
    return;
}

// shader custom function
void VSNullRenderer::CreateVInputDeclare(MaterialShaderPara &MSPara,
                                         Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::CreateVOutputDeclare(MaterialShaderPara &MSPara,
                                          Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::CreateVUserConstant(VSVShader *pVShader, MaterialShaderPara &MSPara,
                                         Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::CreateVFunction(MaterialShaderPara &MSPara,
                                     Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::SetMaterialVShaderConstant(MaterialShaderPara &MSPara, VSVShader *pVShader)
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::CreatePInputDeclare(MaterialShaderPara &MSPara,
                                         Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::CreatePOutputDeclare(MaterialShaderPara &MSPara,
                                          Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::CreatePUserConstant(VSPShader *pPShader, MaterialShaderPara &MSPara,
                                         Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::CreatePFunction(MaterialShaderPara &MSPara,
                                     Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::SetMaterialPShaderConstant(MaterialShaderPara &MSPara, VSPShader *pPShader)
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::CreateGInputDeclare(MaterialShaderPara &MSPara,
                                         Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::CreateGOutputDeclare(MaterialShaderPara &MSPara,
                                          Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::CreateGUserConstant(VSGShader *pGShader, MaterialShaderPara &MSPara,
                                         Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::CreateGFunction(MaterialShaderPara &MSPara,
                                     Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::SetMaterialGShaderConstant(MaterialShaderPara &MSPara, VSGShader *pGShader)
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::CreateHInputDeclare(MaterialShaderPara &MSPara,
                                         Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::CreateHOutputDeclare(MaterialShaderPara &MSPara,
                                          Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::CreateHUserConstant(VSHShader *pHShader, MaterialShaderPara &MSPara,
                                         Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::CreateHFunction(MaterialShaderPara &MSPara,
                                     Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::SetMaterialHShaderConstant(MaterialShaderPara &MSPara, VSHShader *pHShader)
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::CreateDInputDeclare(MaterialShaderPara &MSPara,
                                         Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::CreateDOutputDeclare(MaterialShaderPara &MSPara,
                                          Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::CreateDUserConstant(VSDShader *pDShader, MaterialShaderPara &MSPara,
                                         Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::CreateDFunction(MaterialShaderPara &MSPara,
                                     Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::SetMaterialDShaderConstant(MaterialShaderPara &MSPara, VSDShader *pDShader)
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::GetIncludeShader(Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::GetDynamicShader(Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::SkyLight(const Container::MString &WorldNormal, const Container::MString &UpColor, const Container::MString &DownColor, const Container::MString &DiffuseColor, Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::DirectionalLight(int iLightNum, const Container::MString &Diffuse, const Container::MString &Specular, const Container::MString &SpecularPow,
                                      const Container::MString &WorldNormal, const Container::MString &WorldCameraDir, Container::MArray<Container::MString> ShadowString,
                                      Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::CustomDirectionalLight(int iLightNum, const Container::MString &CustomString, Container::MArray<Container::MString> ShadowString, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::OrenNayarDirectionalLight(int iLightNum, const Container::MString &Diffuse, const Container::MString &RoughnessSquared,
                                               const Container::MString &WorldNormal, const Container::MString &WorldCameraDir, bool bLookUpTable, Container::MArray<Container::MString> ShadowString,
                                               Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::PointLight(int iLightNum, const Container::MString &Diffuse, const Container::MString &Specular, const Container::MString &SpecularPow,
                                const Container::MString &WorldPos, const Container::MString &WorldNormal, const Container::MString &WorldCameraDir, Container::MArray<Container::MString> ShadowString,
                                Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::CustomPointLight(int iLightNum, const Container::MString &CustomString, const Container::MString &WorldPos, Container::MArray<Container::MString> ShadowString, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::OrenNayarPointLight(int iLightNum, const Container::MString &Diffuse, const Container::MString &RoughnessSquared,
                                         const Container::MString &WorldPos, const Container::MString &WorldNormal, const Container::MString &WorldCameraDir, bool bLookUpTable, Container::MArray<Container::MString> ShadowString,
                                         Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::SpotLight(int iLightNum, const Container::MString &Diffuse, const Container::MString &Specular, const Container::MString &SpecularPow,
                               const Container::MString &WorldPos, const Container::MString &WorldNormal, const Container::MString &WorldCameraDir, Container::MArray<Container::MString> ShadowString,
                               Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::CustomSpotLight(int iLightNum, const Container::MString &CustomString, const Container::MString &WorldPos, Container::MArray<Container::MString> ShadowString, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::OrenNayarSpotLight(int iLightNum, const Container::MString &Diffuse, const Container::MString &RoughnessSquared,
                                        const Container::MString &WorldPos, const Container::MString &WorldNormal, const Container::MString &WorldCameraDir, bool bLookUpTable, Container::MArray<Container::MString> ShadowString,
                                        Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::LocalToWorldPos(const Container::MString &LocalPos, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::WorldToViewPos(const Container::MString &LocalPos, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::LocalToWorldNormal(const Container::MString &LocalNormal, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::WorldToViewNormal(const Container::MString &WorldNormal, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::GetWorldViewDir(Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::TransProjPos(const Container::MString &Pos, const Container::MString &Matrix, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::BumpNormal(const Container::MString &TexNormal, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::ComputeDir(const Container::MString &Orgin, const Container::MString &End, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::ComputeLength(const Container::MString &Orgin, const Container::MString &End, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::ComputeBoneVector(const Container::MString &BoneIndex, const Container::MString &BoneWeight, const Container::MString &BoneVector,
                                       const Container::MString &U, const Container::MString &V, const Container::MString &N, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::ComputeBoneVector(const Container::MString &BoneIndex, const Container::MString &BoneWeight,
                                       const Container::MString &AnimDataResource, const Container::MString &AnimAllInfo,
                                       const Container::MString &AnimInstanceInfo, const Container::MString &AnimNum,
                                       const Container::MString &U, const Container::MString &V, const Container::MString &N, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::BoneTranPos(const Container::MString &LocalPos, const Container::MString &U, const Container::MString &V, const Container::MString &N, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::BoneTranNormal(const Container::MString &LocalNormal, const Container::MString &U, const Container::MString &V, const Container::MString &N, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::DecodeNormal1(const Container::MString &Normal, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::RecodeNormal1(const Container::MString &Normal, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::DecodeNormal2(const Container::MString &Normal, const Container::MString &Tengent, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::DecodeNormal3(const Container::MString &Normal, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::RecodeNormal3(const Container::MString &Normal, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::Reciprocal(const Container::MString &Value, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::Clip(const Container::MString &ClipValue, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::GreaterZeroPow(const Container::MString &Value, VSREAL Exp, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::SaturatePow(const Container::MString &Value, VSREAL Exp, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::Saturate(const Container::MString &Value, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::PointLightCubeShadow(const Container::MString &PointLightName, const Container::MString &CubeShadowSampler, const Container::MString &ViewMatrix,
                                          const Container::MString &WorldPos, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::PointLightCubeShadow(const Container::MString &PointLightName, const Container::MString &CubeShadowSampler,
                                          const Container::MString &WorldPos, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::PointLightVolumeShadow(const Container::MString &PointLightName, const Container::MString &VolumeShadowSampler,
                                            const Container::MString &WorldPos, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::PointLightDualParaboloidShadow(const Container::MString &PointLightName, const Container::MString &ShadowSampler,
                                                    const Container::MString &WorldPos, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}
void VSNullRenderer::DirectionLightVolumeShadow(const Container::MString &DirLightName, const Container::MString &VolumeShadowSampler,
                                                const Container::MString &WorldPos, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::DirectionLightCSMShadow(const Container::MString &DirLightName, const Container::MString &ShadowSampler,
                                             const Container::MString &WorldPos, const Container::MString &ViewPos, const Container::MString &FarZ, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::DirectionLightShadow(const Container::MString &DirLightName, const Container::MString &ShadowSampler,
                                          const Container::MString &WorldPos, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::SpotLightShadow(const Container::MString &SpotLightName, const Container::MString &ShadowSampler,
                                     const Container::MString &WorldPos, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::TranLightToTemp(Container::MArray<VSLight *> LightArray, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::GetLightFunction(Container::MArray<VSLight *> LightArray, const Container::MString &WorldPos, Container::MString &OutString) const
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::EncodeReflect(const Container::MString &Mip, const Container::MString &Pow, Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}

void VSNullRenderer::DecodeReflect(const Container::MString &Mip, const Container::MString &Pow, const Container::MString &Value, Container::MString &OutString)
{
    ENGINE_ASSERT(0);
    return;
}
unsigned int VSNullRenderer::GetTextureCompressLen(unsigned int uiLen)
{
    return Max((unsigned int)1, (unsigned int)(uiLen / 4));
}
