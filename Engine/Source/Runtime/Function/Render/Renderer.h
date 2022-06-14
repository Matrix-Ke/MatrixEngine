#pragma once
#include "Math/Vector2.h"
#include "Math/Vector4.h"
#include "Render/RenderState/RenderState.h"
#include "Render/RenderState/SamplerState.h"
#include "Material/Shader/ShaderKey.h"
#include "Node/NodeComponent/Camera.h"
#include "Core/Profiler.h"
namespace Matrix
{
	EXTERN_TIME_PROFILENODE(DrawMesh)
		EXTERN_COUNT_PROFILENODE(DrawPrimitiveNum)
		EXTERN_COUNT_PROFILENODE(DrawGeometryNum)
		class VSCamera;
	class VSBind;
	class VSFont;
	class VSCamera;
	class VSTexAllState;
	class VSGeometry;
	class VSSpatial;
	class VS2DTexture;
	class VS3DTexture;
	class VSMaterial;
	class VSMaterialInstance;
	class VSMeshData;
	class VS2DTexSampler;
	class VS1DTexSampler;
	class VSPutNode;
	class VSLight;
	class VSInstanceGeometry;
	class VSIndexBuffer;
	class VSBufferResource;
	class VSMaterialInstance;
	class VSMul;
	class VSLength;
	class VSDiv;
	class VSDot;
	class VSSub;
	class VSAdd;
	class VSColorBuffer;
	class VSMakeValue;
	class VSSaturate;
	class VSSlot;
	DECLARE_Ptr(VSDVGeometry);
	DECLARE_Ptr(VSTexture);
	DECLARE_Ptr(VSVertexFormat);
	DECLARE_Proxy(VSFont);
	typedef struct VSDISPLAYMODE_STURCT
	{
		UINT uiWidth; //显示分辨率
		UINT uiHeight;
		UINT uiRefreshRate; //刷新率
		UINT uiBitFormat;
		Container::MString StringExpress; //字符串表示
	} VSDisplayMode, * VSDisplayModePtr;

	typedef struct VSDEVICEINFO_STURCT
	{
		UINT uiMaxMultisample;
		UINT uiMaxTextureWidth;
		UINT uiMaxTextureHeight;
		UINT uiMaxUseClipPlane;
		UINT uiMaxTexture;
		UINT fMaxAnisotropy;
		UINT VertexShaderVersion;
		UINT PixelShaderVersion;
		UINT uiMaxRTNum;
	} VSDeviceInfo, * VSDeviceInfoPtr;

	typedef struct VSADAPTERINFO_STURCT
	{
		unsigned int m_uiAdapter;
		Container::MString AdapterName;
		Container::MArray<VSDisplayMode> DisplayMode;
		UINT uiDisplayModeNum;
		// HAL SW REF
		VSDeviceInfo DeviceInfo[3];
	} VSAdapterInfo, * VSAdapterInfoPtr;
	class MATRIX_FUNCTION_API VSRenderer
	{
	public:
		VSRenderer();
		virtual ~VSRenderer() = 0;
		friend class VSVertexBuffer;
		friend class VSVertexFormat;
		friend class VSDataBuffer;
		friend class VSDepthStencil;
		friend class VSTexture;
		friend class VSRenderTarget;
		friend class VSBufferUnorderAccess;
		friend class VSUnorderAccess;
		friend class VSTextureUnorderAccess;
		friend class VSIndexBuffer;
		friend class VSBufferResource;
		friend class VSCustomMaterial;
		friend class VSVShader;
		friend class VSPShader;
		friend class VSGShader;
		friend class VSDShader;
		friend class VSHShader;
		friend class VSCShader;
		friend class VSCubeTexture;
		friend class VSSamplerState;
		friend class VSQuery;
		friend class VSBlendState;
		friend class VSDepthStencilState;
		friend class VSRasterizerState;
		friend class VSRenderThreadSys;
		friend class VSBind;
		enum // Render API Type
		{
			RAT_NULL,
			RAT_DIRECTX9,
			RAT_DIRECTX11,
			RAT_MAX
		};
		enum // function return information
		{
			FRI_FAIL,
			FRI_SUCCESS,
			FRI_SAMERESOURCE
		};
		enum // Multisample
		{
			MS_NONE,
			MS_2,
			MS_4,
			MS_8,
			MS_16,
			MS_MAX
		};
		enum // Surface Format Type
		{
			SFT_A8R8G8B8,
			SFT_X8R8G8B8,
			SFT_D16,
			SFT_A32B32G32R32F,
			SFT_A16B16G16R16F,
			SFT_G16R16F,
			SFT_R16F,
			SFT_R32F,
			SFT_UNKNOWN,
			SFT_D24S8,
			SFT_G32R32F,
			SFT_R5G6B5,
			SFT_A8,
			SFT_G16R16,
			SFT_A16B16G16R16,
			SFT_R8,
			SFT_A8R8G8B8_S,
			SFT_G16R16_S,
			SFT_R16,
			SFT_A16B16G16R16_S,
			// Compress Type
			SFT_BC1,
			SFT_BC2,
			SFT_BC3,
			SFT_BC4,
			SFT_BC5,
			SFT_MAX
		};

		virtual int GetRendererType() const = 0;
		// 颜色 深度 模板 buffer
		inline void SetClearColor(const Math::ColorRGBA& ClearColor);
		inline const Math::ColorRGBA& GetClearColor() const;

		inline void SetClearDepth(VSREAL fClearDepth);
		inline VSREAL GetClearDepth() const;

		inline void SetClearStencil(unsigned int uiClearValue);
		inline unsigned int GetClearStencil() const;

		enum // Clear Flag
		{
			CF_NONE = 0,
			CF_COLOR = 1 << 0,
			CF_DEPTH = 1 << 1,
			CF_STENCIL = 1 << 2,
			CF_COLOR_DEPTH = CF_COLOR | CF_DEPTH,
			CF_COLOR_STENCIL = CF_COLOR | CF_STENCIL,
			CF_DEPTH_STENCIL = CF_DEPTH | CF_STENCIL,
			CF_USE_ALL = CF_COLOR | CF_DEPTH | CF_STENCIL
		};

		virtual void ClearBuffers(unsigned int uiClearFlag) = 0;
		virtual void ClearBackBuffer() = 0;
		virtual void ClearZBuffer() = 0;
		virtual void ClearStencilBuffer() = 0;
		virtual void ClearBuffers() = 0;

		virtual void ClearBuffers(unsigned int uiClearFlag, int iXPos, int iYPos, int iWidth,
			int iHeight) = 0;
		virtual void ClearBackBuffer(int iXPos, int iYPos, int iWidth,
			int iHeight) = 0;
		virtual void ClearZBuffer(int iXPos, int iYPos, int iWidth,
			int iHeight) = 0;
		virtual void ClearStencilBuffer(int iXPos, int iYPos, int iWidth,
			int iHeight) = 0;
		virtual void ClearBuffers(int iXPos, int iYPos, int iWidth,
			int iHeight) = 0;

		void DrawText(int iX, int iY, const DWORD rColor, const TCHAR* acText, ...);
		virtual bool SetViewPort(VSViewPort* pViewPort = NULL) = 0;

		void SetFont(VSFontR* pFont);

		virtual bool UseWindow(int uiWindowID = -1) = 0;

		virtual bool CooperativeLevel() = 0;
		virtual bool BeginRendering() = 0;
		virtual bool EndRendering() = 0;

		virtual void DeviceLost() = 0;
		virtual void ResetDevice() = 0;
		virtual bool ChangeScreenSize(unsigned int uiWidth, unsigned int uiHeight, bool bWindow) = 0;

		virtual const VSAdapterInfo* GetAdapterInfo(unsigned int& uiAdapterNum) = 0;
		static unsigned int GetBytesPerPixel(unsigned int uiFormatType);
		static unsigned int GetChannelPerPixel(unsigned int uiFormatType);
		static unsigned int GetMinDimension(unsigned int uiFormatType);
		static const Container::MString& GetVShaderProgramMain();
		static const Container::MString& GetPShaderProgramMain();
		static const Container::MString& GetGShaderProgramMain();
		static const Container::MString& GetHShaderProgramMain();
		static const Container::MString& GetDShaderProgramMain();

		inline unsigned int GetScreenWith() const;
		inline unsigned int GetScreenHeight() const;

		inline unsigned int GetCurAnisotropy() const;
		inline unsigned int GetCurMultisample() const;
		inline unsigned int GetMaxMultisample() const;
		inline unsigned int GetDepthStencilFormat() const;
		inline bool IsWindowed() const;
		inline unsigned int WindoweNum() const;
		inline unsigned int GetMaxTextureWidth() const;
		inline unsigned int GetMaxTextureHeight() const;

		inline unsigned int GetSuitableMultisample(unsigned int Multisample) const;
		inline unsigned int GetMaxUseClipPlane() const;
		inline unsigned int GetMaxBindResource(unsigned int uiShaderType) const;
		inline unsigned int GetMaxSampler(unsigned int uiShaderType) const;

		inline unsigned int GetBufferFormat() const;
		inline unsigned int GetMaxAnisotropy() const;

		inline unsigned int GetMaxRTNum() const;
		inline unsigned int GetMaxUAVNum() const;
		inline Container::MString GetAdapterName() const;

		inline unsigned int GetCurRTWidth() const;
		inline unsigned int GetCurRTHeight() const;
		inline unsigned int GetCurRTMultisampler() const;
		// Load Release
		bool LoadVShaderProgram(VSVShader* pVShaderProgram);
		bool ReleaseVShaderProgram(VSVShader* pVShaderProgram);

		bool LoadPShaderProgram(VSPShader* pPShaderProgram);
		bool ReleasePShaderProgram(VSPShader* pPShaderProgram);

		bool LoadGShaderProgram(VSGShader* pGShaderProgram);
		bool ReleaseGShaderProgram(VSGShader* pGShaderProgram);

		bool LoadDShaderProgram(VSDShader* pDShaderProgram);
		bool ReleaseDShaderProgram(VSDShader* pDShaderProgram);

		bool LoadHShaderProgram(VSHShader* pHShaderProgram);
		bool ReleaseHShaderProgram(VSHShader* pHShaderProgram);

		bool LoadCShaderProgram(VSCShader* pCShaderProgram);
		bool ReleaseCShaderProgram(VSCShader* pCShaderProgram);

		bool LoadTexture(VSTexture* pTexture);
		bool ReleaseTexture(VSTexture* pTexture);

		bool LoadBufferResource(VSBufferResource* pBufferResource);
		bool ReleaseBufferResource(VSBufferResource* pBufferResource);

		bool LoadVBuffer(VSVertexBuffer* pVBuffer);
		bool ReleaseVBuffer(VSVertexBuffer* pVBuffer);

		bool LoadIBuffer(VSIndexBuffer* pIBuffer);
		bool ReleaseIBuffer(VSIndexBuffer* pIBuffer);

		bool LoadDepthStencil(VSDepthStencil* pDepthStencil);
		bool ReleaseDepthStencil(VSDepthStencil* pDepthStencil);

		bool LoadRenderTarget(VSRenderTarget* pRenderTarget);
		bool ReleaseRenderTarget(VSRenderTarget* pRenderTarget);

		bool LoadUnorderAccess(VSUnorderAccess* pUnorderAccess);
		bool ReleaseUnorderAccess(VSUnorderAccess* pUnorderAccess);

		bool LoadBlendState(VSBlendState* pBlendState);
		bool ReleaseBlendState(VSBlendState* pBlendState);

		bool LoadDepthStencilState(VSDepthStencilState* pDepthStencilState);
		bool ReleaseDepthStencilState(VSDepthStencilState* pDepthStencilState);

		bool LoadRasterizerState(VSRasterizerState* pRasterizerState);
		bool ReleaseRasterizerState(VSRasterizerState* pRasterizerState);

		bool LoadSamplerState(VSSamplerState* pSamplerState);
		bool ReleaseSamplerState(VSSamplerState* pSamplerState);

		bool LoadQuery(VSQuery* pQuery);
		bool ReleaseQuery(VSQuery* pQuery);

		virtual bool DrawMesh(VSGeometry* pGeometry, VSRenderState* pRenderState, VSVShader* pVShader, VSPShader* pPShader,
			VSGShader* pGShader, VSHShader* pHShader, VSDShader* pDShader) = 0;
		struct SCREEN_QUAD_TYPE
		{
			Math::Vector4 Point;
			VSVector2 UV;
		};
		struct SCREEN_FONT_TYPE
		{
			Math::Vector4 Point;
			VSVector2 UV;
			DWORD Color;
		};
		virtual bool DrawScreen(SCREEN_QUAD_TYPE ScreenQuad[4]) = 0;
		virtual bool DrawScreen(SCREEN_QUAD_TYPE* pScreenBuffer, unsigned int uiVertexNum,
			VSUSHORT_INDEX* pIndexBuffer, unsigned int uiIndexNum) = 0;
		virtual bool DrawScreenFont(SCREEN_FONT_TYPE* pScreenFontBuffer, unsigned int uiVertexNum,
			VSUSHORT_INDEX* pIndexBuffer, unsigned int uiIndexNum) = 0;
		void SetUseState(VSRenderState& RenderState, unsigned int uiRenderStateInheritFlag);
		void ClearUseState();
		inline const VSRenderState& GetUseState() const
		{
			return m_UseState;
		}
		inline unsigned int GetRenderStateInheritFlag() const
		{
			return m_uiRenderStateInheritFlag;
		}
		void SetRenderState(VSRenderState& RenderState);
		virtual unsigned int SetBlendState(VSBlendState* pBlendState, bool bForceSet = false) = 0;
		virtual unsigned int SetDepthStencilState(VSDepthStencilState* pDepthStencilState, bool bForceSet = false) = 0;
		virtual unsigned int SetRasterizerState(VSRasterizerState* pRasterizerState, bool bForceSet = false) = 0;
		virtual void SetClipPlane(Container::MArray<VSPlane3>& Plane, bool bEnable) = 0;
		virtual void SetScissorRect(Container::MArray<VSRect2>& Rect, bool bEnable) = 0;

		virtual void SetPTexAllState(VSTexAllState* pTexAllState, unsigned int i);
		virtual void SetVTexAllState(VSTexAllState* pTexAllState, unsigned int i);
		virtual void SetGTexAllState(VSTexAllState* pTexAllState, unsigned int i);
		virtual void SetDTexAllState(VSTexAllState* pTexAllState, unsigned int i);
		virtual void SetHTexAllState(VSTexAllState* pTexAllState, unsigned int i);
		virtual void SetCTexAllState(VSTexAllState* pTexAllState, unsigned int i);

		virtual unsigned int SetVShader(VSVShader* pVShader);
		virtual unsigned int SetPShader(VSPShader* pPShader);
		virtual unsigned int SetGShader(VSGShader* pGShader);
		virtual unsigned int SetDShader(VSDShader* pDShader);
		virtual unsigned int SetHShader(VSHShader* pHShader);
		virtual unsigned int SetCShader(VSCShader* pCShader);

		virtual unsigned int SetVBuffer(VSVertexBuffer* pVBuffer, unsigned int uiStream = 0) = 0;
		virtual unsigned int SetIBuffer(VSIndexBuffer* pIBuffer) = 0;

		virtual unsigned int BeginQuery(VSQuery* pQuery) = 0;
		virtual unsigned int EndQuery(VSQuery* pQuery) = 0;

		virtual unsigned int SetPTexture(VSTexture* pTexture, unsigned int i) = 0;
		virtual unsigned int SetVTexture(VSTexture* pTexture, unsigned int i) = 0;
		virtual unsigned int SetGTexture(VSTexture* pTexture, unsigned int i) = 0;
		virtual unsigned int SetDTexture(VSTexture* pTexture, unsigned int i) = 0;
		virtual unsigned int SetHTexture(VSTexture* pTexture, unsigned int i) = 0;
		virtual unsigned int SetCTexture(VSTexture* pTexture, unsigned int i) = 0;
		virtual unsigned int SetCBufferResource(VSBufferResource* pBufferResource, unsigned int i) = 0;
		virtual unsigned int SetVBufferResource(VSBufferResource* pBufferResource, unsigned int i) = 0;
		virtual unsigned int SetPBufferResource(VSBufferResource* pBufferResource, unsigned int i) = 0;
		virtual unsigned int SetGBufferResource(VSBufferResource* pBufferResource, unsigned int i) = 0;
		virtual unsigned int SetHBufferResource(VSBufferResource* pBufferResource, unsigned int i) = 0;
		virtual unsigned int SetDBufferResource(VSBufferResource* pBufferResource, unsigned int i) = 0;

		virtual void Dispath(unsigned int uiThreadGroupCountX, unsigned int uiThreadGroupCountY,
			unsigned int uiThreadGroupCountZ) = 0;

		virtual unsigned int SetNormalMesh(VSGeometry* pGeometry);
		virtual unsigned int SetInstanceMesh(VSInstanceGeometry* pInstanceGeometry);

		virtual unsigned int SetPSamplerState(VSSamplerState* pSamplerState, unsigned int i, bool bForceSet = false) = 0;
		virtual unsigned int SetVSamplerState(VSSamplerState* pSamplerState, unsigned int i, bool bForceSet = false) = 0;
		virtual unsigned int SetGSamplerState(VSSamplerState* pSamplerState, unsigned int i, bool bForceSet = false) = 0;
		virtual unsigned int SetDSamplerState(VSSamplerState* pSamplerState, unsigned int i, bool bForceSet = false) = 0;
		virtual unsigned int SetHSamplerState(VSSamplerState* pSamplerState, unsigned int i, bool bForceSet = false) = 0;
		virtual unsigned int SetCSamplerState(VSSamplerState* pSamplerState, unsigned int i, bool bForceSet = false) = 0;

		virtual bool SetRenderTargets(VSRenderTarget* pRenderTargets[], unsigned int uiNum);
		virtual bool EndRenderTargets(VSRenderTarget* pRenderTargets[], unsigned int uiNum);
		virtual bool SetRenderTarget(VSRenderTarget* pRenderTarget, unsigned int i);
		virtual bool EndRenderTarget(VSRenderTarget* pRenderTarget, unsigned int i);
		virtual bool SetDepthStencilBuffer(VSDepthStencil* pDepthStencilBuffer) = 0;
		virtual bool EndDepthStencilBuffer(VSDepthStencil* pDepthStencilBuffer) = 0;
		virtual bool SetCSUnorderAccess(VSUnorderAccess* pUnorderAccess, unsigned int i);
		virtual bool EndCSUnorderAccess(VSUnorderAccess* pUnorderAccess, unsigned int i);
		virtual bool SetCSUnorderAccesses(VSUnorderAccess* pUnorderAccesses[], unsigned int uiNum);
		virtual bool EndCSUnorderAccesses(VSUnorderAccess* pUnorderAccesses[], unsigned int uiNum);

		virtual unsigned int GetTextureCompressLen(unsigned int uiLen) = 0;

		void SetVSResourceSlotUsed(VSSlot* pSlotResource, unsigned int uiSlot, bool b);
		void SetPSResourceSlotUsed(VSSlot* pSlotResource, unsigned int uiSlot, bool b);
		void SetGSResourceSlotUsed(VSSlot* pSlotResource, unsigned int uiSlot, bool b);
		void SetDSResourceSlotUsed(VSSlot* pSlotResource, unsigned int uiSlot, bool b);
		void SetHSResourceSlotUsed(VSSlot* pSlotResource, unsigned int uiSlot, bool b);
		void SetCSResourceSlotUsed(VSSlot* pSlotResource, unsigned int uiSlot, bool b);

		void RenderStateToDefault();

		void EnableBindResourceUsed(VSSlot* pSlotResource);
		void DisableBindResourceUsed(VSSlot* pSlotResource);

		bool CheckIsResourceCanSet(VSSlot* pSlotResource);
		struct ChildWindowInfo
		{
			HWND m_hHwnd;
			unsigned int m_uiWidth;
			unsigned int m_uiHeight;
			bool m_bDepth;
		};
		ChildWindowInfo* GetChildWindowInfo(int uiID);

		enum SupportFeatureType
		{
			SF_MulBufferSwtich,
			SF_GS,
			SF_MaterialValueInstance,
			SF_Tessellation,
			SF_MSBufferRead,
			SF_DepthStensilBufferRead,
			SF_DepthStensilToTexture,
			SF_BufferResource,
			SF_UnorderAccess,
			SF_CS,
			SF_ClearRange,
			SF_VertexIDInShader,
			SF_ShareSampler,
			SF_VShaderSampler,
			SF_AdvanceInstance,
			SF_NoPow2Texture,
			SF_MAX,
		};
		inline bool IsSupportFeature(SupportFeatureType SF) { return m_SupportFeature[SF]; }

	protected:
		bool m_SupportFeature[SupportFeatureType::SF_MAX];

		HWND m_hMainWindow; // 主窗口
		ChildWindowInfo* m_pChildWindowInfo;
		int m_iNumChildWindow; // 窗口个数
		int m_iCurWindowID;
		bool m_bIsRendering;

		Math::ColorRGBA m_ClearColor;
		VSREAL m_fClearDepth;
		unsigned int m_uiClearStencil;

		VSFontRPtr m_pFont;
		VSVertexFormatPtr m_pQuadVertexFormat;
		VSVertexFormatPtr m_pFontVertexFormat;
		VSVertexBuffer* m_pVertexBuffer[STREAM_LEVEL];
		VSIndexBuffer* m_pIndexBuffer;

		VSQuery* m_pQuery;

		Container::MArray<VSSlot*> m_pVTex;
		Container::MArray<VSSlot*> m_pPTex;
		Container::MArray<VSSlot*> m_pGTex;
		Container::MArray<VSSlot*> m_pDTex;
		Container::MArray<VSSlot*> m_pHTex;
		Container::MArray<VSSlot*> m_pCTex;

		VSVertexFormat* m_pVertexFormat;
		VSVShader* m_pVShader;
		VSPShader* m_pPShader;
		VSGShader* m_pGShader;
		VSDShader* m_pDShader;
		VSHShader* m_pHShader;
		VSCShader* m_pCShader;

		Container::MMap<unsigned int, VSTexAllState*> m_pTexAllStateBuffer;
		Container::MMap<unsigned int, VSBufferResource*> m_pBufferResource;

		Container::MArray<VSSamplerState*> m_pSamplerState[VSEngineFlag::ST_MAX];

		VSRenderState m_LocalRenderState;

		VSBlendState* m_pBlendState;
		VSDepthStencilState* m_pDepthStencilState;
		VSRasterizerState* m_pRasterizerState;
		bool m_bClipPlaneEnable;
		bool m_bScissorRectEnable;
		VSRenderState m_UseState;
		unsigned int m_uiRenderStateInheritFlag;

		enum // BACK_MACTH_TYPE
		{
			BMT_NONE = 0x00,
			BMT_RENDER_TARGET = 0x01,
		};
		unsigned int m_uiBackMacthType;
		virtual void SetVShaderConstant(VSVShader* pShader) = 0;
		virtual void SetVShaderBindResource(VSVShader* pShader);

		virtual void SetGShaderConstant(VSGShader* pShader) = 0;
		virtual void SetGShaderBindResource(VSGShader* pShader);

		virtual void SetDShaderConstant(VSDShader* pShader) = 0;
		virtual void SetDShaderBindResource(VSDShader* pShader);

		virtual void SetHShaderConstant(VSHShader* pShader) = 0;
		virtual void SetHShaderBindResource(VSHShader* pShader);

		virtual void SetPShaderConstant(VSPShader* pShader) = 0;
		virtual void SetPShaderBindResource(VSPShader* pShader);

		virtual void SetCShaderConstant(VSCShader* pShader) = 0;
		virtual void SetCShaderBindResource(VSCShader* pShader);

		virtual bool SetVShaderProgram(VSVShader* pVShaderProgram) = 0;
		virtual bool SetPShaderProgram(VSPShader* pPShaderProgram) = 0;
		virtual bool SetGShaderProgram(VSGShader* pGShaderProgram) = 0;
		virtual bool SetDShaderProgram(VSDShader* pDShaderProgram) = 0;
		virtual bool SetHShaderProgram(VSHShader* pHShaderProgram) = 0;
		virtual bool SetCShaderProgram(VSCShader* pCShaderProgram) = 0;
		// Load Release
		virtual bool OnLoadVShaderProgram(VSVShader* pVShaderProgram, VSResourceIdentifier*& pID) = 0;
		virtual bool OnReleaseResouce(VSResourceIdentifier* pResourceResourceIdentifier);

		virtual bool OnLoadPShaderProgram(VSPShader* pPShaderProgram, VSResourceIdentifier*& pID) = 0;

		virtual bool OnLoadGShaderProgram(VSGShader* pGShaderProgram, VSResourceIdentifier*& pID) = 0;

		virtual bool OnLoadDShaderProgram(VSDShader* pDShaderProgram, VSResourceIdentifier*& pID) = 0;

		virtual bool OnLoadHShaderProgram(VSHShader* pHShaderProgram, VSResourceIdentifier*& pID) = 0;

		virtual bool OnLoadCShaderProgram(VSCShader* pCShaderProgram, VSResourceIdentifier*& pID) = 0;

		virtual bool OnLoadTexture(VSTexture* pTexture, VSResourceIdentifier*& pID) = 0;

		virtual bool OnLoadDepthStencil(VSDepthStencil* pDepthStencil, VSResourceIdentifier*& pID) = 0;

		virtual bool OnLoadRenderTarget(VSRenderTarget* pRenderTarget, VSResourceIdentifier*& pID) = 0;

		virtual bool OnLoadUnorderAccess(VSBufferUnorderAccess* pUnorderAccess, VSResourceIdentifier*& pID) = 0;
		virtual bool OnLoadUnorderAccess(VSTextureUnorderAccess* pUnorderAccess, VSResourceIdentifier*& pID) = 0;

		virtual bool OnLoadVBufferData(VSVertexBuffer* pVBuffer, VSResourceIdentifier*& pID) = 0;

		virtual bool OnLoadVBufferFormat(VSVertexFormat* pVertexFormat, VSResourceIdentifier*& pID) = 0;

		virtual bool OnLoadIBuffer(VSIndexBuffer* pIBuffer, VSResourceIdentifier*& pID) = 0;

		virtual bool OnLoadSBuffer(VSBufferResource* pSBuffer, VSResourceIdentifier*& pID) = 0;

		virtual bool OnLoadBlendState(VSBlendState* pBlendState, VSResourceIdentifier*& pID) = 0;

		virtual bool OnLoadDepthStencilState(VSDepthStencilState* pDepthStencilState, VSResourceIdentifier*& pID) = 0;

		virtual bool OnLoadRasterizerState(VSRasterizerState* pRasterizerState, VSResourceIdentifier*& pID) = 0;

		virtual bool OnLoadSamplerState(VSSamplerState* pSamplerState, VSResourceIdentifier*& pID) = 0;

		virtual bool OnLoadQuery(VSQuery* pQuery, VSResourceIdentifier*& pID) = 0;

		virtual unsigned int SetVertexFormat(VSVertexFormat* pVertexFormat) = 0;

		virtual void* Lock(VSVertexBuffer* pVertexBuffer) = 0;
		virtual void UnLock(VSVertexBuffer* pVertexBuffer) = 0;

		virtual void* Lock(VSIndexBuffer* pIndexBuffer) = 0;
		virtual void UnLock(VSIndexBuffer* pIndexBuffer) = 0;

		virtual void* Lock(VSBufferResource* pStructBuffer) = 0;
		virtual void UnLock(VSBufferResource* pStructBuffer) = 0;

		virtual void* Lock(VSTexture* pTexture, unsigned int uiLevel, unsigned int uiFace) = 0;
		virtual void UnLock(VSTexture* pTexture, unsigned int uiLevel, unsigned int uiFace) = 0;

		virtual void* Lock(VSRenderTarget* pRenderTarget) = 0;
		virtual void UnLock(VSRenderTarget* pRenderTarget) = 0;

		virtual void* Lock(VSUnorderAccess* pUnorderAccess) = 0;
		virtual void UnLock(VSUnorderAccess* pUnorderAccess) = 0;

		virtual void* Lock(VSDepthStencil* pDepthStencil) = 0;
		virtual void UnLock(VSDepthStencil* pDepthStencil) = 0;

		virtual bool GetData(VSQuery* pQuery, void* pData, unsigned int uiSize) = 0;

		virtual bool CopyResourceBuffer(VS2DTexture* pSource, VSCubeTexture* pDest, unsigned int uiFace) = 0;

		bool SetDefaultValue();
		bool ReleaseDefaultValue();

		// shader
		inline static DWORD ShaderVersion(UINT Major, UINT Minor);
		virtual bool ReleaseBindObjectResource();

	protected:
		enum // device type
		{
			DT_HAL = 0,
			DT_REF = 1,
			DT_MAX
		};

		unsigned int m_uinAdapter;
		unsigned int m_uiDevType;
		Container::MString m_AdapterName;
		UINT m_uiScreenWidth;
		UINT m_uiScreenHeight;
		UINT m_uiCurRTWidth;
		UINT m_uiCurRTHeight;
		UINT m_uiBufferFormat;
		bool m_bWindowed;

		UINT m_uiDepthStencilFormat;
		UINT m_uiCurAnisotropy;
		UINT m_uiCurMultisample;
		UINT m_uiCurRTMultisample;
		DWORD m_dwMultisampleQuality;
		UINT m_uiMaxMultisample;
		UINT m_uiMaxTextureWidth;
		UINT m_uiMaxTextureHeight;

		UINT m_uiMaxUseClipPlane;

		UINT m_uiMaxBindResource[VSEngineFlag::ST_MAX];

		UINT m_uiMaxSampler[VSEngineFlag::ST_MAX];

		UINT m_uiMaxAnisotropy;

		UINT m_uiMaxRTNum;
		UINT m_uiMaxUAVNum;

		static Container::MString ms_ShaderProgramMain[VSEngineFlag::ST_MAX];

		static unsigned int ms_uiBytesPerPixel[SFT_MAX];
		static unsigned int ms_uiMinDimension[SFT_MAX];
		static unsigned int ms_uiChannelPerPixel[SFT_MAX];
		static SCREEN_QUAD_TYPE ms_FullScreen[4];
		static VSUSHORT_INDEX ms_FullScreenI[6];
		Container::MArray<SCREEN_FONT_TYPE> m_FontVertex;
		Container::MArray<VSUSHORT_INDEX> m_FontIndex;

		VSViewPort m_CurViewPort;

		static Container::MString ms_ShaderTypeString[VSRenderer::RAT_MAX];
		static Container::MString ms_ShaderTypePathString[VSRenderer::RAT_MAX];
		// shader string
	public:
		// shader function
		virtual Container::MString TexColorBuffer(const VSColorBuffer* pColorBuffer) const = 0;
		virtual Container::MString Tex2D(const VS2DTexSampler* p2DTexSampler, unsigned int uiShaderType) const = 0;
		virtual Container::MString Tex1D(const VS1DTexSampler* p1DTexSampler, unsigned int uiShaderType) const = 0;
		virtual Container::MString Mul(const VSMul* pMul) const = 0;
		virtual Container::MString Div(const VSDiv* pDiv) const = 0;
		virtual Container::MString Dot(const VSDot* pDot) const = 0;
		virtual Container::MString Length(const VSLength* pLength) const = 0;
		virtual Container::MString Sub(const VSSub* pSub) const = 0;
		virtual Container::MString Add(const VSAdd* pAdd) const = 0;
		virtual Container::MString MakeValue(const VSMakeValue* pMakeValue) const = 0;
		virtual Container::MString Saturate(const VSSaturate* pSaturate) const = 0;
		// shader key word
		enum // Float Index
		{
			FI_1,
			FI_2,
			FI_3,
			FI_4,
			FI_MAX

		};
		virtual Container::MString FloatByChannelNum(unsigned int ChannelNum) const = 0;
		Container::MString Float(unsigned int uiIndex) const;
		virtual Container::MString Float() const = 0;
		virtual Container::MString Float2() const = 0;
		virtual Container::MString Float3() const = 0;
		virtual Container::MString Float4() const = 0;
		virtual Container::MString Return() const = 0;

		virtual Container::MString FloatConst(const Container::MString& Value1) const = 0;
		virtual Container::MString Float2Const(const Container::MString& Value1, const Container::MString& Value2) const = 0;
		virtual Container::MString Float3Const(const Container::MString& Value1,
			const Container::MString& Value2, const Container::MString& Value3) const = 0;
		virtual Container::MString Float4Const(const Container::MString& Value1, const Container::MString& Value2,
			const Container::MString& Value3, const Container::MString& Value4) const = 0;

		virtual void CustomPointLightUseString(Container::MString& PointLightUseString, Container::MString& PointAttenuationDivString) = 0;

		virtual void CustomSpotLightUseString(Container::MString& SpotLightUseString, Container::MString& SpotAttenuationDivString) = 0;

		enum // Value Element
		{
			VE_NONE = 0,
			VE_A = BIT(0),
			VE_R = BIT(1),
			VE_G = BIT(2),
			VE_B = BIT(3),
			DF_ALL = 0X0F
		};
		static Container::MString GetValueElement(const VSPutNode* pPutNode,
			unsigned char uiVE);
		static Container::MString GetValueElement(const Container::MString& InputString,
			unsigned char uiVE);

		virtual void GetShareSamplerDeclare(class VSShader* pShader, Container::MString& OutString);

		virtual Container::MString GetDeclareValue(const Container::MString& ShowName, unsigned int uiValueType, unsigned int uiRegisterIndex) const = 0;
		virtual Container::MString GetDeclareSampler(const Container::MString& ShowName, unsigned int SamplerType, unsigned int uiRegisterIndex, unsigned int SamplerSource) const = 0;
		virtual void GetDeclareShareSampler(unsigned int SamplerSource, unsigned int uiRegisterIndex, Container::MString& OutString) const = 0;
		// shader custom function
		virtual void CreateVInputDeclare(MaterialShaderPara& MSPara,
			Container::MString& OutString) = 0;
		virtual void CreateVOutputDeclare(MaterialShaderPara& MSPara,
			Container::MString& OutString) = 0;
		virtual void CreateVUserConstant(VSVShader* pVShader, MaterialShaderPara& MSPara,
			Container::MString& OutString) = 0;
		virtual void CreateVFunction(MaterialShaderPara& MSPara,
			Container::MString& OutString) = 0;

		virtual void SetMaterialVShaderConstant(MaterialShaderPara& MSPara, VSVShader* pVShader) = 0;

		virtual void CreatePInputDeclare(MaterialShaderPara& MSPara,
			Container::MString& OutString) = 0;
		virtual void CreatePOutputDeclare(MaterialShaderPara& MSPara,
			Container::MString& OutString) = 0;
		virtual void CreatePUserConstant(VSPShader* pPShader, MaterialShaderPara& MSPara,
			Container::MString& OutString) = 0;
		virtual void CreatePFunction(MaterialShaderPara& MSPara,
			Container::MString& OutString) = 0;

		virtual void SetMaterialPShaderConstant(MaterialShaderPara& MSPara, VSPShader* pPShader) = 0;

		virtual void CreateGInputDeclare(MaterialShaderPara& MSPara,
			Container::MString& OutString) = 0;
		virtual void CreateGOutputDeclare(MaterialShaderPara& MSPara,
			Container::MString& OutString) = 0;
		virtual void CreateGUserConstant(VSGShader* pGShader, MaterialShaderPara& MSPara,
			Container::MString& OutString) = 0;
		virtual void CreateGFunction(MaterialShaderPara& MSPara,
			Container::MString& OutString) = 0;
		virtual void SetMaterialGShaderConstant(MaterialShaderPara& MSPara, VSGShader* pGShader) = 0;

		virtual void CreateHInputDeclare(MaterialShaderPara& MSPara,
			Container::MString& OutString) = 0;
		virtual void CreateHOutputDeclare(MaterialShaderPara& MSPara,
			Container::MString& OutString) = 0;
		virtual void CreateHUserConstant(VSHShader* pHShader, MaterialShaderPara& MSPara,
			Container::MString& OutString) = 0;
		virtual void CreateHFunction(MaterialShaderPara& MSPara,
			Container::MString& OutString) = 0;
		virtual void SetMaterialHShaderConstant(MaterialShaderPara& MSPara, VSHShader* pHShader) = 0;

		virtual void CreateDInputDeclare(MaterialShaderPara& MSPara,
			Container::MString& OutString) = 0;
		virtual void CreateDOutputDeclare(MaterialShaderPara& MSPara,
			Container::MString& OutString) = 0;
		virtual void CreateDUserConstant(VSDShader* pDShader, MaterialShaderPara& MSPara,
			Container::MString& OutString) = 0;
		virtual void CreateDFunction(MaterialShaderPara& MSPara,
			Container::MString& OutString) = 0;
		virtual void SetMaterialDShaderConstant(MaterialShaderPara& MSPara, VSDShader* pDShader) = 0;

		virtual void GetIncludeShader(Container::MString& OutString) = 0;

		virtual void GetDynamicShader(Container::MString& OutString) = 0;

		virtual void SkyLight(const Container::MString& WorldNormal, const Container::MString& UpColor, const Container::MString& DownColor, const Container::MString& DiffuseColor, Container::MString& OutString) = 0;
		virtual void DirectionalLight(int iLightNum, const Container::MString& Diffuse, const Container::MString& Specular, const Container::MString& SpecularPow,
			const Container::MString& WorldNormal, const Container::MString& WorldCameraDir, Container::MArray<Container::MString> ShadowString,
			Container::MString& OutString) const = 0;
		virtual void CustomDirectionalLight(int iLightNum, const Container::MString& CustomString, Container::MArray<Container::MString> ShadowString, Container::MString& OutString) const = 0;

		virtual void OrenNayarDirectionalLight(int iLightNum, const Container::MString& Diffuse, const Container::MString& RoughnessSquared,
			const Container::MString& WorldNormal, const Container::MString& WorldCameraDir, bool bLookUpTable, Container::MArray<Container::MString> ShadowString,
			Container::MString& OutString) const = 0;

		virtual void PointLight(int iLightNum, const Container::MString& Diffuse, const Container::MString& Specular, const Container::MString& SpecularPow,
			const Container::MString& WorldPos, const Container::MString& WorldNormal, const Container::MString& WorldCameraDir, Container::MArray<Container::MString> ShadowString,
			Container::MString& OutString) const = 0;
		virtual void CustomPointLight(int iLightNum, const Container::MString& CustomString, const Container::MString& WorldPos, Container::MArray<Container::MString> ShadowString, Container::MString& OutString) const = 0;

		virtual void OrenNayarPointLight(int iLightNum, const Container::MString& Diffuse, const Container::MString& RoughnessSquared,
			const Container::MString& WorldPos, const Container::MString& WorldNormal, const Container::MString& WorldCameraDir, bool bLookUpTable, Container::MArray<Container::MString> ShadowString,
			Container::MString& OutString) const = 0;

		virtual void SpotLight(int iLightNum, const Container::MString& Diffuse, const Container::MString& Specular, const Container::MString& SpecularPow,
			const Container::MString& WorldPos, const Container::MString& WorldNormal, const Container::MString& WorldCameraDir, Container::MArray<Container::MString> ShadowString,
			Container::MString& OutString) const = 0;
		virtual void CustomSpotLight(int iLightNum, const Container::MString& CustomString, const Container::MString& WorldPos, Container::MArray<Container::MString> ShadowString, Container::MString& OutString) const = 0;
		virtual void OrenNayarSpotLight(int iLightNum, const Container::MString& Diffuse, const Container::MString& RoughnessSquared,
			const Container::MString& WorldPos, const Container::MString& WorldNormal, const Container::MString& WorldCameraDir, bool bLookUpTable, Container::MArray<Container::MString> ShadowString,
			Container::MString& OutString) const = 0;

		virtual void LocalToWorldPos(const Container::MString& LocalPos, Container::MString& OutString) const = 0;
		virtual void WorldToViewPos(const Container::MString& LocalPos, Container::MString& OutString) const = 0;

		virtual void LocalToWorldNormal(const Container::MString& LocalNormal, Container::MString& OutString) const = 0;

		virtual void WorldToViewNormal(const Container::MString& WorldNormal, Container::MString& OutString) const = 0;

		virtual void GetWorldViewDir(Container::MString& OutString) const = 0;

		virtual void TransProjPos(const Container::MString& Pos, const Container::MString& Matrix, Container::MString& OutString) const = 0;
		virtual void BumpNormal(const Container::MString& TexNormal, Container::MString& OutString) const = 0;

		virtual void ComputeDir(const Container::MString& Orgin, const Container::MString& End, Container::MString& OutString) const = 0;
		virtual void ComputeLength(const Container::MString& Orgin, const Container::MString& End, Container::MString& OutString) const = 0;
		virtual void ComputeBoneVector(const Container::MString& BoneIndex, const Container::MString& BoneWeight, const Container::MString& BoneVector,
			const Container::MString& U, const Container::MString& V, const Container::MString& N, Container::MString& OutString) const = 0;
		virtual void ComputeBoneVector(const Container::MString& BoneIndex, const Container::MString& BoneWeight,
			const Container::MString& AnimDataResource, const Container::MString& AnimAllInfo,
			const Container::MString& AnimInstanceInfo, const Container::MString& AnimNum,
			const Container::MString& U, const Container::MString& V, const Container::MString& N, Container::MString& OutString) const = 0;

		virtual void BoneTranPos(const Container::MString& LocalPos, const Container::MString& U, const Container::MString& V, const Container::MString& N, Container::MString& OutString) const = 0;
		virtual void BoneTranNormal(const Container::MString& LocalNormal, const Container::MString& U, const Container::MString& V, const Container::MString& N, Container::MString& OutString) const = 0;

		virtual void DecodeNormal1(const Container::MString& Normal, Container::MString& OutString) const = 0;
		virtual void RecodeNormal1(const Container::MString& Normal, Container::MString& OutString) const = 0;
		virtual void DecodeNormal2(const Container::MString& Normal, const Container::MString& Tengent, Container::MString& OutString) const = 0;

		virtual void DecodeNormal3(const Container::MString& Normal, Container::MString& OutString) const = 0;
		virtual void RecodeNormal3(const Container::MString& Normal, Container::MString& OutString) const = 0;

		virtual void Reciprocal(const Container::MString& Value, Container::MString& OutString) const = 0;
		virtual void Clip(const Container::MString& Value, Container::MString& OutString) const = 0;
		virtual void GreaterZeroPow(const Container::MString& Value, VSREAL Exp, Container::MString& OutString) const = 0;
		virtual void SaturatePow(const Container::MString& Value, VSREAL Exp, Container::MString& OutString) const = 0;
		virtual void Saturate(const Container::MString& Value, Container::MString& OutString) const = 0;

		virtual void PointLightCubeShadow(const Container::MString& PointLightName, const Container::MString& CubeShadowSampler, const Container::MString& ViewMatrix,
			const Container::MString& WorldPos, Container::MString& OutString) const = 0;

		virtual void PointLightCubeShadow(const Container::MString& PointLightName, const Container::MString& CubeShadowSampler,
			const Container::MString& WorldPos, Container::MString& OutString) const = 0;

		virtual void PointLightVolumeShadow(const Container::MString& PointLightName, const Container::MString& VolumeShadowSampler,
			const Container::MString& WorldPos, Container::MString& OutString) const = 0;

		virtual void PointLightDualParaboloidShadow(const Container::MString& PointLightName, const Container::MString& ShadowSampler,
			const Container::MString& WorldPos, Container::MString& OutString) const = 0;
		virtual void DirectionLightVolumeShadow(const Container::MString& DirLightName, const Container::MString& VolumeShadowSampler,
			const Container::MString& WorldPos, Container::MString& OutString) const = 0;

		virtual void DirectionLightCSMShadow(const Container::MString& DirLightName, const Container::MString& ShadowSampler,
			const Container::MString& WorldPos, const Container::MString& ViewPos, const Container::MString& FarZ, Container::MString& OutString) const = 0;

		virtual void DirectionLightShadow(const Container::MString& DirLightName, const Container::MString& ShadowSampler,
			const Container::MString& WorldPos, Container::MString& OutString) const = 0;

		virtual void SpotLightShadow(const Container::MString& SpotLightName, const Container::MString& ShadowSampler,
			const Container::MString& WorldPos, Container::MString& OutString) const = 0;

		virtual void TranLightToTemp(Container::MArray<VSLight*> LightArray, Container::MString& OutString) const = 0;

		virtual void GetLightFunction(Container::MArray<VSLight*> LightArray, const Container::MString& WorldPos, Container::MString& OutString) const = 0;

		virtual void EncodeReflect(const Container::MString& Mip, const Container::MString& Pow, Container::MString& OutString) = 0;

		virtual void DecodeReflect(const Container::MString& Mip, const Container::MString& Pow, const Container::MString& Value, Container::MString& OutString) = 0;

	public:
		static VSRenderer* ms_pRenderer;
		static const Container::MString& GetRenderTypeShaderPath(unsigned int RenderTypeAPI);
		static const Container::MString& GetRenderTypeString(unsigned int RenderTypeAPI);
		const Container::MString& GetRenderTypeShaderPath() const;
		const Container::MString& GetRenderTypeString() const;
	};

#include "Renderer.inl"
}
