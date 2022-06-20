#pragma once
#include "Render/OutputResource/OutputResource.h"
#include "Render/OutputResource/TextureOutputInfo.h"
#include "Render/Texture/Texture.h"
namespace Matrix
{
	/*
	* 渲染目标有两种使用方式。一种是绑定渲染目标和纹理，把数据复制到纹理中；另一种是将渲染目标单纯作为存储数据使用
	*
	*/
	class MATRIX_FUNCTION_API VSRenderTarget : public VSOutputResource, public VSTextureOutputInfo
	{

		// RTTI
		DECLARE_RTTI;
		DECLARE_INITIAL

	public:
		friend class VSResourceManager;
		virtual ~VSRenderTarget();
		virtual unsigned int GetOutputType() const { return OT_RENDER_TARGET; }
		virtual void* Lock();
		virtual void UnLock();

	protected:
		VSRenderTarget(unsigned int uiWidth, unsigned int uiHeight, unsigned int uiFormatType,
			unsigned int uiMulSample, bool CPURead = false);
		VSRenderTarget(class VS2DTexture* pCreateBy, unsigned int uiMulSample = VSRenderer::MS_NONE, unsigned int uiLevel = 0, bool CPURead = false);
		VSRenderTarget(class VS2DTextureArray* pCreateBy, unsigned int uiMulSample = VSRenderer::MS_NONE, unsigned int uiLevel = 0, unsigned int First = 0, unsigned int uiArraySize = 1, bool CPURead = false);
		VSRenderTarget(class VS3DTexture* pCreateBy, unsigned int uiMulSample = VSRenderer::MS_NONE, unsigned int uiLevel = 0, unsigned int First = 0, unsigned int uiArraySize = 1, bool CPURead = false);
		VSRenderTarget();

		virtual bool OnLoadResource(VSResourceIdentifier*& pID);
	};
	DECLARE_Ptr(VSRenderTarget);
	VSTYPE_MARCO(VSRenderTarget);
}
