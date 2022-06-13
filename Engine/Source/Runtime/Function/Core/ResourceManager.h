#pragma once
#include "ResourceMacro.h"
#include "Core/Config.h"
#include "Resource.h"
#include "Material/Shader/ShaderKey.h"
#include "Render/Buffer/VertexFormat.h"
#include "Material/Shader/ShaderMap.h"
#include "Render/Texture/CubeTexture.h"

#include "Render/Texture/1DTexture.h"
#include "Render/Texture/2DTexture.h"
#include "Render/Texture/3DTexture.h"
#include "Render/Buffer/BufferResource.h"
#include "Node/Mesh/MeshData.h"
#include "Asyn/ASYNLoader.h"

#include "Platform/Synchronize.h"
#include "Container/Delegate.h"


namespace Matrix
{
	class VSDataBuffer;
	class VSFont;
	class VSShaderProgram;
	class VSVertexBuffer;
	class VSDynamicBufferGeometry;
	class VSGeometry;
	class VSName;
	class VSCaptureTexAllState;
	class VSActor;
	class VSSceneMap;

	DECLARE_Ptr(VSTexAllState);
	DECLARE_Ptr(VSName);
	DECLARE_Ptr(VSVShader);
	DECLARE_Ptr(VSPShader);
	DECLARE_Ptr(VSGShader);
	DECLARE_Ptr(VSHShader);
	DECLARE_Ptr(VSDShader);
	DECLARE_Ptr(VSSkeletonMeshNode);
	DECLARE_Ptr(VSStaticMeshNode);
	DECLARE_Ptr(VSAnimSet);
	DECLARE_Ptr(VSMaterial);
	DECLARE_Ptr(VSFont);
	DECLARE_Ptr(VSVertexFormat);
	DECLARE_Ptr(VSAnimTree);
	DECLARE_Ptr(VSAnim);
	DECLARE_Ptr(VSBufferResource);
	DECLARE_Ptr(VSDVGeometry);


	DECLARE_Ptr(VSPostEffectSet);

	DECLARE_Proxy(VSTexAllState);
	DECLARE_Proxy(VSMaterial);
	DECLARE_Proxy(VSAnim);
	DECLARE_Proxy(VSFont);
	DECLARE_Proxy(VSStaticMeshNode);
	DECLARE_Proxy(VSSkeletonMeshNode);
	DECLARE_Proxy(VSPostEffectSet);
	DECLARE_Proxy(VSAnimTree);
	DECLARE_Proxy(VSActor);
	DECLARE_Proxy(VSSceneMap);


	DECLARE_Ptr(VSRenderTarget);
	DECLARE_Ptr(VSDepthStencil);
	DECLARE_Ptr(VSUnorderAccess);
	DECLARE_Ptr(VSBlendState);
	DECLARE_Ptr(VSDepthStencilState);
	DECLARE_Ptr(VSRasterizerState);
	DECLARE_Ptr(VSSamplerState);
	DECLARE_Ptr(VSDynamicBufferGeometry);
	DECLARE_Ptr(VSInstanceGeometry);
	class VSBlendDesc;
	class VSDepthStencilDesc;
	class VSRasterizerDesc;
	class VSSamplerDesc;
	class VSGCTask;

	struct DynamicBufferIndex
	{
		VSVertexFormatPtr pVertexFormat;
		unsigned int uiMeshDataType;
		DynamicBufferIndex()
		{
			pVertexFormat = NULL;
			uiMeshDataType = 0;
		}
		DynamicBufferIndex& operator=(const DynamicBufferIndex& DBI)
		{
			pVertexFormat = DBI.pVertexFormat;
			uiMeshDataType = DBI.uiMeshDataType;
			return *this;
		}
	};

	bool operator==(const DynamicBufferIndex& DBI1, const DynamicBufferIndex& DBI2);
	bool operator>(const DynamicBufferIndex& DBI1, const DynamicBufferIndex& DBI2);
	bool operator<(const DynamicBufferIndex& DBI1, const DynamicBufferIndex& DBI2);

	typedef Container::DelegateEvent<void(void)> DelayUpdateObjectOneFrame;
	typedef Container::DelegateEvent<void(VSREAL)> DelayUpdateObject;
	typedef Container::DelegateEvent<void(void)> DelayUpdateNoTimeObject;

	class MATRIX_FUNCTION_API VSResourceManager
	{
	public:
		VSResourceManager();
		~VSResourceManager();

	public:
		struct TextureBindInfoType
		{
			unsigned int uiFirst;
			unsigned int uiArraySize;
		};
		enum CompressType
		{
			CT_NONE,
			CT_BC1,
			CT_BC2,
			CT_BC3,
			CT_BC4,
			CT_BC5,
			CT_MAX
		};

		// PRIORITY
		DECLARE_PRIORITY
		// initial
		DECLARE_INITIAL_ONLY
		static VSName* CreateName(const TCHAR* pChar);
		static VSName* CreateName(const Container::MString& String);

		static void LoadDefaultDeviceResource(unsigned int RenderTypeAPI);
		static bool IsReleaseAll();
		static void CacheResource();
		static void DeleteMapResource(const TCHAR* pFileName);
		static void DeleteAllMapResource();

		template <typename T>
		static VSResourceProxy<T>* LoadASYNResource(const TCHAR* pFileName, bool IsAsyn)
		{
			if (!pFileName)
			{
				return NULL;
			}
			VSFileName FileName = pFileName;
			Container::MString Extension;
			VSUsedName ResourceName;
			if (FileName.GetExtension(Extension))
			{
				if (Extension != T::ms_FileSuffix)
				{
					return NULL;
				}
				else
				{
					ResourceName = FileName;
					FileName = T::ms_ResourcePath + FileName;
				}
			}
			else
			{
				ResourceName = FileName + T::ms_PointFileSuffix;
				FileName = T::ms_ResourcePath + FileName + T::ms_PointFileSuffix;
			}
			Core::MSynchronize::Locker Temp(T::ms_LoadResourceCriticalSection);
			VSPointer<VSResourceProxy<T>> pResourceR = NULL;
			//判断资源是否存在
			pResourceR = (VSResourceProxy<T> *)T::GetASYNResourceSet().CheckIsHaveTheResource(ResourceName);
			if (pResourceR)
			{
				return pResourceR;
			}
			pResourceR = MX_NEW VSResourceProxy<T>();

			pResourceR->SetResourceName(ResourceName);

			T::GetASYNResourceSet().AddResource(ResourceName, pResourceR);
			//如果是异步加载
			if (IsAsyn && VSConfig::ms_EnableAsynLoad && (pResourceR->GetResourceAbility() & RA_ASYN_LOAD))
			{
				ENGINE_ASSERT(VSASYNLoadManager::ms_pASYNLoadManager);
				VSASYNLoadManager::ms_pASYNLoadManager->AddResource(pResourceR, FileName);
			}
			else
			{
				T* pResource = LoadResource<T>(FileName.GetBuffer());
				if (pResource)
				{
					pResourceR->SetNewResource(pResource);
					if (pResourceR->GetResourceAbility() & RA_NEED_CACHE)
					{
						T::CacheType* pCacheResouce = LoadResource<T::CacheType>(pResource->GetCacheFilePath().GetBuffer());
						ENGINE_ASSERT(pCacheResouce);
						pCacheResouce->SetCacheResource(pResource);
						ENGINE_DELETE(pCacheResouce);
					}
					pResourceR->Loaded();
				}
				else
				{
					ENGINE_ASSERT(0);
				}
			}
			return pResourceR;
		}

		//内部管理resource
		GET_INNER_RESOURCE_SET(VertexFormat);
		GET_INNER_RESOURCE_SET(Name);
		GET_INNER_RESOURCE_SET(BlendState);
		GET_INNER_RESOURCE_SET(DepthStencilState);
		GET_INNER_RESOURCE_SET(RasterizerState);
		GET_INNER_RESOURCE_SET(SamplerState);

		// for custom material
		GET_SHADER_MAP(Custom);
		GET_SHADER_MAP(Material); ////  one shader map to one material tree
		GET_SHADER_MAP(Indirect);
		GET_SHADER_MAP(NormalDepth);
		GET_SHADER_MAP(CubShadow);
		GET_SHADER_MAP(VolumeShadow);
		GET_SHADER_MAP(Shadow);
		GET_SHADER_MAP(DualParaboloidShadow);
		GET_SHADER_MAP(PreZ);
		GET_SHADER_MAP(Inner); // one shader map all material tree

		static class VSInstanceGeometry* GetDynamicInstanceGeometry(VSMeshData* pSourceMeshData, VSMaterialR* pMaterial);
		static VSDVGeometry* GetDVGeometry(VSVertexFormat* pVertexFormat, unsigned int MeshDataType, unsigned int VertexNum);

		template <class T>
		static VSTexAllState* Create2DTexture(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiFormatType, unsigned int uiMipLevel, T* pBuffer, bool bSRGB = false);
		template <class T>
		static VSTexAllState* Create1DTexture(unsigned int uiWidth, unsigned int uiFormatType, unsigned int uiMipLevel, T* pBuffer, bool bSRGB = false);
		template <class T>
		static VSTexAllState* CreateCubTexture(unsigned int uiWidth, unsigned int uiFormatType, unsigned int uiMipLevel, T* pBuffer, bool bSRGB = false);
		template <class T>
		static VSTexAllState* Create3DTexture(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiLength, unsigned int uiFormatType, unsigned int uiMipLevel, T* pBuffer, bool bSRGB = false);
		static VSCaptureTexAllState* CreateCaptureTexture(const Container::MString& ViewFamilyName, unsigned int uiMipLevel = 1);

		static VSTexAllState* Load2DTexture(const TCHAR* pFileName, VSSamplerStatePtr pSamplerState, CompressType uiCompressType, bool bIsNormal, bool bSRGB, bool bMip);
		static VS2DTexture* CreateTextureCache(void* SourceData, unsigned int uiWidth, unsigned int uiHeight, unsigned int uiFormatType, bool bIsNormal, bool bSRGB, bool bMip);

		static VSVertexFormat* LoadVertexFormat(VSVertexBuffer* pVertexBuffer, Container::MArray<VSVertexFormat::VERTEXFORMAT_TYPE>* pFormatArray = NULL);
		static VSVShader* CreateVShader(MaterialShaderPara& MSPara, unsigned int uiShaderID);
		static VSPShader* CreatePShader(MaterialShaderPara& MSPara, unsigned int uiShaderID);
		static VSGShader* CreateGShader(MaterialShaderPara& MSPara, unsigned int uiShaderID);
		static VSHShader* CreateHShader(MaterialShaderPara& MSPara, unsigned int uiShaderID);
		static VSDShader* CreateDShader(MaterialShaderPara& MSPara, unsigned int uiShaderID);
		static VSBlendState* CreateBlendState(const VSBlendDesc& BlendDesc);
		static VSDepthStencilState* CreateDepthStencilState(const VSDepthStencilDesc& DepthStencilDesc);
		static VSRasterizerState* CreateRasterizerState(const VSRasterizerDesc& RasterizerDesc);
		static VSSamplerState* CreateSamplerState(const VSSamplerDesc& SamplerDesc);

		// RenderTarget
		static VSRenderTarget* CreateRenderTarget(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiFormatType,
			unsigned int uiMulSample, bool CPURead = false);
		static VSRenderTarget* CreateRenderTarget(VS2DTexture* pCreateBy, unsigned int uiMulSample = 0, unsigned int uiLevel = 0, bool CPURead = false);
		static VSRenderTarget* CreateRenderTarget(VS2DTextureArray* pCreateBy, unsigned int uiMulSample = 0, unsigned int uiLevel = 0, unsigned int First = 0, unsigned int uiArraySize = 1, bool CPURead = false);
		static VSRenderTarget* CreateRenderTarget(VS3DTexture* pCreateBy, unsigned int uiMulSample = 0, unsigned int uiLevel = 0, unsigned int First = 0, unsigned int uiArraySize = 1, bool CPURead = false);
		//取得满足条件的，并且没有再使用的RT，为了节省显存空间，一般这种RT和texture绑定的，并且贴图miplevel都是1
		static VSRenderTarget* GetRenderTarget(unsigned int uiWidth, unsigned int uiHeight,
			unsigned int uiFormatType, unsigned int uiMulSample, bool TextureUse = true, bool CPURead = false);
		static bool GetCubRenderTarget(unsigned int uiWidth, unsigned int uiFormatType,
			unsigned int uiMulSample, VSRenderTarget* OutRT[VSCubeTexture::F_MAX], bool CPURead = false);
		static bool Get2DTextureArrayRenderTarget(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiFormatType,
			unsigned int uiMulSample, Container::MArray<TextureBindInfoType>& TextureBindInfo, Container::MArray<VSRenderTarget*>& RTArray, bool CPURead = false);
		static bool Get3DTextureRenderTarget(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiFormatType,
			unsigned int uiMulSample, Container::MArray<TextureBindInfoType>& TextureBindInfo, Container::MArray<VSRenderTarget*>& RTArray, bool CPURead = false);

		// DepthStencil
		static VSDepthStencil* CreateDepthStencil(unsigned int uiWidth, unsigned int uiHeight,
			unsigned int uiMulSample, unsigned int uiFormatType, bool CPURead = false);
		static VSDepthStencil* CreateDepthStencil(VS2DTexture* pCreateBy, unsigned int uiMulSample = 0, unsigned int uiLevel = 0, bool CPURead = false);
		static VSDepthStencil* CreateDepthStencil(VS2DTextureArray* pCreateBy, unsigned int uiMulSample = 0, unsigned int uiLevel = 0, unsigned int First = 0, unsigned int uiArraySize = 1, bool CPURead = false);
		static VSDepthStencil* CreateDepthStencil(VS3DTexture* pCreateBy, unsigned int uiMulSample = 0, unsigned int uiLevel = 0, unsigned int First = 0, unsigned int uiArraySize = 1, bool CPURead = false);
		static VSDepthStencil* GetDepthStencil(unsigned int uiWidth, unsigned int uiHeight,
			unsigned int uiFormatType, unsigned int uiMulSample, bool TextureUse = false, bool CPURead = false);
		static bool GetCubDepthStencil(unsigned int uiWidth, unsigned int uiFormatType,
			unsigned int uiMulSample, VSDepthStencil* OutDS[VSCubeTexture::F_MAX], bool CPURead = false);
		static bool Get2DTextureArrayDepthStencil(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiFormatType,
			unsigned int uiMulSample, Container::MArray<TextureBindInfoType>& TextureBindInfo, Container::MArray<VSDepthStencil*>& DSArray, bool CPURead = false);
		static bool Get3DTextureDepthStencil(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiFormatType,
			unsigned int uiMulSample, Container::MArray<TextureBindInfoType>& TextureBindInfo, Container::MArray<VSDepthStencil*>& DSArray, bool CPURead = false);

		// UnorderAccess Buffer
		static VSUnorderAccess* CreateBufferUnorderAccess(unsigned int uiNum, unsigned int uiDT, unsigned int uiStructStride = 0, bool CPURead = false);
		static VSUnorderAccess* CreateBufferUnorderAccess(VSBufferResource* pCreateBy, bool CPURead = false);
		static VSUnorderAccess* GetBufferUnorderAccess(unsigned int uiNum, unsigned int uiDT, unsigned int uiStructStride = 0, bool BufferResource = true, bool CPURead = false);

		// UnorderAccess Texture
		static VSUnorderAccess* CreateTextureUnorderAccess(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiFormatType, bool CPURead = false);
		static VSUnorderAccess* CreateTextureUnorderAccess(VS2DTexture* pCreateBy, unsigned int uiLevel = 0, bool CPURead = false);
		static VSUnorderAccess* CreateTextureUnorderAccess(VS2DTextureArray* pCreateBy, unsigned int uiLevel = 0, unsigned int First = 0, unsigned int uiArraySize = 1, bool CPURead = false);
		static VSUnorderAccess* CreateTextureUnorderAccess(VS3DTexture* pCreateBy, unsigned int uiLevel = 0, unsigned int First = 0, unsigned int uiArraySize = 1, bool CPURead = false);
		static VSUnorderAccess* GetTextureUnorderAccess(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiFormatType, bool TextureUse = false, bool CPURead = false);
		static bool GetCubeUnorderAccess(unsigned int uiWidth, unsigned int uiFormatType, VSUnorderAccess* OutUA[VSCubeTexture::F_MAX], bool CPURead = false);
		static bool Get2DTextureArrayUnorderAccess(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiFormatType, Container::MArray<TextureBindInfoType>& TextureBindInfo, Container::MArray<VSUnorderAccess*>& UAArray, bool CPURead = false);
		static bool Get3DTextureUnorderAccess(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiFormatType, Container::MArray<TextureBindInfoType>& TextureBindInfo, Container::MArray<VSUnorderAccess*>& UAArray, bool CPURead = false);

		// Source - Target
		static VSAnim* CreateAdditiveAnim(VSAnim* pSourceAnim, VSAnim* pTargetAnim, VSAnimR* pBlendAnimR);
		static VSAnim* CreateAdditiveAnim(VSAnim* pSourceAnim, VSAnim* pTargetAnim, VSAnimR* pBlendAnimR, VSREAL fTargetTime = 0.0f);
		static VSAnim* CreateAdditiveAnim(VSAnim* pSourceAnim, VSAnim* pTargetAnim, VSAnimR* pBlendAnimR, VSREAL fSourceTime = 0.0f, VSREAL fTargetTime = 0.0f);
		static VSAnim* CreateAnim(VSAnim* pSourceAnim, VSREAL fSourceTime = 0.0f);

	public:
		template <typename T>
		static bool SaveResouce(T* pResource, const TCHAR* PathName, bool bSaveResourcePath = false)
		{
			if (!pResource)
			{
				return false;
			}
			if (!pResource->IsCanSave())
			{
				return false;
			}
			MStream SaveStream;
			SaveStream.SetStreamFlag(MStream::AT_REGISTER);
			SaveStream.ArchiveAll(pResource);
			Container::MString ResourceName = PathName;
			ResourceName += T::ms_PointFileSuffix;
			Container::MString FileName = T::ms_ResourcePath + ResourceName;
			if (!TIsVSCacheResourceType<T>::Value)
			{
				VSResource* pTemp = (VSResource*)pResource;
				pTemp->SetResourceName(ResourceName);
			}
			return SaveStream.Save(bSaveResourcePath ? FileName.GetBuffer() : PathName);
		}
		template <typename T>
		static bool SaveResouce(VSPointer<T>& pResource, const TCHAR* PathName, bool bSaveResourcePath = false)
		{
			return SaveResouce(pResource.GetObject(), PathName, bSaveResourcePath);
		}
		template <class T>
		static void DisableOutputResource(T*& pOutputResource)
		{
			ReleaseOutputResource(pOutputResource);
			if (pOutputResource->GetOutputType() == VSOutputResource::OT_BUFFER_UNORDER_ACCESS)
			{
				VSBufferResource* pBufferResource = (VSBufferResource*)pOutputResource->GetCreateBy();
				if (pBufferResource)
				{
					pBufferResource->ClearAllSlot();
				}
			}
			else
			{
				VSTexture* pTexture = (VSTexture*)pOutputResource->GetCreateBy();
				if (pTexture)
				{
					pTexture->ClearAllSlot();
				}
			}

			pOutputResource = NULL;
		}
		template <class T>
		static void DisableOutputResource(VSPointer<T>& pOutputResource)
		{
			T* pTempOutputResource = pOutputResource;
			DisableOutputResource(pTempOutputResource);
			pOutputResource = NULL;
		}
		template <class T>
		static void DisableOutputReousrceArray(Container::MArray<T*>& OutputReousrceArray)
		{
#if _DEBUG
			if (!CheckOutputResourceArrayIsValid(OutputReousrceArray))
			{
				ENGINE_ASSERT(0);
			}
#endif
			ReleaseOutputResourceArray(OutputReousrceArray);
			VSTexture* pTexture = (VSTexture*)OutputReousrceArray[0]->GetCreateBy();
			if (pTexture)
			{
				pTexture->ClearAllSlot();
			}
			for (unsigned int i = 0; i < RTArray.GetNum(); i++)
			{
				OutputReousrceArray[i] = NULL;
			}
		}
		template <class T>
		static void DisableOutputReousrceArray(Container::MArray<VSPointer<T>>& OutputReousrceArray)
		{
			Container::MArray<T*> OutputReousrceArrayTemp;
			for (unsigned int i = 0; i < OutputReousrceArray.GetNum(); i++)
			{
				OutputReousrceArrayTemp[i] = OutputReousrceArray[i];
			}
			DisableOutputReousrceArray(OutputReousrceArrayTemp);
			for (unsigned int i = 0; i < OutputReousrceArray.GetNum(); i++)
			{
				OutputReousrceArray[i] = NULL;
			}
		}
		// help function
		template <class T>
		static bool GetNextMipData(const T* pInData, unsigned int uiInDataWidth, unsigned int uiInDataHeight, T* pOutData, unsigned int uiChannel);
		template <class T>
		static bool GetNextMipData(const T* pInData, unsigned int uiInDataWidth, unsigned int uiInDataHeight, unsigned int uiInDataLenght, T* pOutData, unsigned int uiChannel);

	public:
		static DelayUpdateObjectOneFrame& GetDelayUpdateObjectOneFrame()
		{
			static DelayUpdateObjectOneFrame s_DelayUpdateObjectOneFrame;
			return s_DelayUpdateObjectOneFrame;
		}
		static DelayUpdateObject& GetDelayUpdateObject()
		{
			static DelayUpdateObject s_DelayUpdateObject;
			return s_DelayUpdateObject;
		}
		static DelayUpdateNoTimeObject& GetDelayUpdateNoTimeObject()
		{
			static DelayUpdateNoTimeObject s_DelayUpdateNoTimeObject;
			return s_DelayUpdateNoTimeObject;
		}
		static void DelayUpdate(VSREAL fTime)
		{
			GetDelayUpdateObjectOneFrame()();
			GetDelayUpdateObjectOneFrame().Reset();
			GetDelayUpdateObject()(fTime);
			GetDelayUpdateNoTimeObject()();
			ms_SaveDelete.Clear();
		}
		/*
		 GC规则：
		默认从MX_NEW创建的OBJECT 不参与GC，所以不会被GC掉，要自己管理。
		只有从Object GetInstance 创建出来的才参与GC，如果想要不参与GC请调用AddRootObject。
		把指针加入属性表，保证要参与GC的Object可以访问的到，否则就会被GC掉。
		*/
		static void GC();
		static void AddRootObject(MObject* p);
		static void DeleteRootObject(MObject* p);
		static void AddGCObject(MObject* p);
		static void GCObject();

		//GPU skin
		static unsigned int GetGpuSkinBoneNum()
		{
			return ms_uiGpuSkinBoneNum;
		}
		static unsigned int GetGpuMorphTargetNum()
		{
			return ms_uiGpuMorphTargetNum;
		}
		static unsigned int GetGpuMorphTextureSize()
		{
			return ms_uiGpuMorphTextureSize;
		}
		static unsigned int GetSimpleInstanceAnimFloat4Num()
		{
			return ms_uiSimpleInstanceAnimFloat4Num;
		}
		static unsigned int GetLerpSimpleInstanceAnim()
		{
			return ms_bLerpSimpleInstanceAnim;
		}
		static bool DrawSkeleton()
		{
			return ms_bDrawSkeleton;
		}
		static bool GetActiveDebugDraw()
		{
			return ms_bActiveDebugDraw;
		}
		static bool IsCacheShader()
		{
			return ms_bIsCacheShader;
		}

		static bool ms_bRenderThread;
		static bool ms_bUpdateThread;
		static unsigned int ms_CurRenderAPIType;

	protected:
		static Core::MCriticalSection ms_NameCri;
		static VSResourceProxyBase* LoadResource(const TCHAR* pFileName, bool IsAsyn);
		template <typename T>
		static T* LoadResource(const TCHAR* pFileName)
		{
			if (!pFileName)
			{

				return NULL;
			}
			MStream LoadStream;
			LoadStream.Load(pFileName);
			T* pResource = (T*)LoadStream.GetObjectByRtti(T::ms_Type);
			if (!pResource)
			{
				return NULL;
			}
			return pResource;
		}

	protected:
		friend class MStream;
		friend class VSAsynStream;
		friend class VSWorld;
		//每帧形成一个GCtask， 这样就形成一个链表
		static VSGCTask* ms_pCurGCTask;
		static VSGCTask* ms_pEndGCTask;
		static void RunAllGCTask();                                            //如果游戏结束还没有释放完毕，则全部都释放掉
		static void RunGCTask();                                               //运行每帧来释放 MObject 对象
		static void AddCanGCObject(Container::MArray<MObject*>& CanGCObject); //添加本帧要释放的 MObject 对象
		static Container::MArray<MObject*> ms_pRootObject;
		static Container::MArrayOrder<MObject*> ms_pGCObject;

	protected:
		static unsigned int ms_uiGpuSkinBoneNum;
		static bool ms_bDrawSkeleton;
		static bool ms_bActiveDebugDraw;
		static unsigned int ms_uiGpuMorphTargetNum;
		static unsigned int ms_uiGpuMorphTextureSize;
		static unsigned int ms_uiSimpleInstanceAnimFloat4Num;
		static bool ms_bLerpSimpleInstanceAnim;
		static bool ms_bIsCacheShader;

	private:
		static bool InitialDefaultState();
		static bool TerminalDefaultState();
		static void InitCacheShader(unsigned int RenderTypeAPI);
		static bool CacheShader();
		static bool CheckTextureBindInfo(Container::MArray<TextureBindInfoType>& TextureBindInfo);
		static bool CheckTextureBindInfo(Container::MArray<TextureBindInfoType>& TextureBindInfo, VSTextureOutputInfo* pTextureOutputInfo);
		static VSRenderTarget* GetRenderTargetTexture(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiFormatType, unsigned int uiMulSample, bool CPURead = false);
		static VSRenderTarget* GetRenderTargetNoTexture(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiFormatType, unsigned int uiMulSample, bool CPURead = false);
		static VSDepthStencil* GetDepthStencilNoTexture(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiFormatType, unsigned int uiMulSample, bool CPURead = false);
		static VSDepthStencil* GetDepthStencilTexture(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiFormatType, unsigned int uiMulSample, bool CPURead = false);
		static VSUnorderAccess* GetUnorderAccessNoBuffer(unsigned int uiNum, unsigned int uiDT, unsigned int uiStructStride = 0, bool CPURead = false);
		static VSUnorderAccess* GetUnorderAccessBuffer(unsigned int uiNum, unsigned int uiDT, unsigned int uiStructStride = 0, bool CPURead = false);
		static VSUnorderAccess* GetUnorderAccessNoTexture(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiFormatType, bool CPURead = false);
		static VSUnorderAccess* GetUnorderAccessTexture(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiFormatType, bool CPURead = false);
		static VSResourceArrayControl<VSInstanceGeometryPtr>& GetDynamicInstanceGeometryArray()
		{
			static VSResourceArrayControl<VSInstanceGeometryPtr> s_DynamicInstanceGeometryArray;
			return s_DynamicInstanceGeometryArray;
		}
		static VSResourceSet<DynamicBufferIndex, VSDVGeometryPtr>& GetDVGeometryArray()
		{
			static VSResourceSet<DynamicBufferIndex, VSDVGeometryPtr> s_DVGeometryArray;
			return s_DVGeometryArray;
		}
		static Container::MArray<VSDynamicBufferGeometryPtr> ms_SaveDelete;
		static VSResourceArrayControl<VSRenderTargetPtr>& GetRenderTargetArray()
		{
			static VSResourceArrayControl<VSRenderTargetPtr> s_RenderTargetArray;
			return s_RenderTargetArray;
		}
		static VSResourceArrayControl<VSDepthStencilPtr>& GetDepthStencilArray()
		{
			static VSResourceArrayControl<VSDepthStencilPtr> s_RenderTargetArray;
			return s_RenderTargetArray;
		}
		static VSResourceArrayControl<VSUnorderAccessPtr>& GetUnorderAccessArray()
		{
			static VSResourceArrayControl<VSUnorderAccessPtr> s_UnorderAccessArray;
			return s_UnorderAccessArray;
		}
		static VSResourceArrayControl<VSRenderTargetPtr>& GetRenderTargetBufferArray()
		{
			static VSResourceArrayControl<VSRenderTargetPtr> s_RenderTargetBufferArray;
			return s_RenderTargetBufferArray;
		}
		static VSResourceArrayControl<VSDepthStencilPtr>& GetDepthStencilBufferArray()
		{
			static VSResourceArrayControl<VSDepthStencilPtr> s_RenderTargetBufferArray;
			return s_RenderTargetBufferArray;
		}
		static VSResourceArrayControl<VSUnorderAccessPtr>& GetUnorderAccessBufferArray()
		{
			static VSResourceArrayControl<VSUnorderAccessPtr> s_UnorderAccessBufferArray;
			return s_UnorderAccessBufferArray;
		}

		template <class T>
		static void ReleaseOutputResource(T* pOutputResource)
		{
			if (pOutputResource)
			{
				ENGINE_ASSERT(pOutputResource->m_bUsed == true);
				pOutputResource->m_bUsed = false;
			}
		}
		template <class T>
		static bool CheckOutputResourceArrayIsValid(Container::MArray<T*>& OutputResourceArray)
		{
			if (OutputResourceArray.GetNum() == 0 || OutputResourceArray[0])
			{
				return false;
			}
			VSTexture* pCreatBy = (VSTexture*)OutputResourceArray[0]->GetCreateBy();
			if (!pCreatBy)
			{
				return false;
			}
			unsigned int uiMaxRT = OutputResourceArray[0]->GetFirst() + OutputResourceArray[0]->GetArraySize();
			unsigned int uiArrayNum = 0;
			unsigned int uiUsedNum = 0;
			for (unsigned int i = 0; i < OutputResourceArray.GetNum(); i++)
			{
				if (!OutputResourceArray[i])
				{
					return false;
				}
				if (pCreatBy != OutputResourceArray[i]->GetCreateBy())
				{
					return false;
				}
				if (OutputResourceArray[i]->m_bUsed)
				{
					uiUsedNum++;
				}
				unsigned int ArrayNumIndex = OutputResourceArray[i]->GetArraySize();
				unsigned int MaxRTIndex = OutputResourceArray[i]->GetFirst() + ArrayNumIndex;
				uiArrayNum += ArrayNumIndex;
				if (MaxRTIndex > uiMaxRT)
				{
					uiMaxRT = MaxRTIndex;
				}
			}
			if (uiMaxRT != uiArrayNum || uiUsedNum != OutputResourceArray.GetNum())
			{
				return false;
			}
			if (pCreatBy->GetTexType() == VSTexture::TT_2DARRAY)
			{
				if (uiArrayNum != pCreatBy->GetArraySize())
				{
					return false;
				}
			}
			else if (pCreatBy->GetTexType() == VSTexture::TT_3D)
			{
				if (uiArrayNum != pCreatBy->GetLength(0))
				{
					return false;
				}
			}
			return true;
		}
		template <class T>
		static void ReleaseOutputResourceArray(Container::MArray<T*>& OutputResourceArray)
		{
			for (unsigned int i = 0; i < OutputResourceArray.GetNum(); i++)
			{
				OutputResourceArray[i]->m_bUsed = false;
			}
		}
	};

#include "ResourceManager.inl"

}
