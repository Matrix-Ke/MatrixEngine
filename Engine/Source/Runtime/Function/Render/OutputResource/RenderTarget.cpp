#include "RenderTarget.h"
#include "Render/Buffer/VertexFormat.h"
#include "Core/GraphicInclude.h"
#include "Render/Texture/2DTexture.h"
//#include "Render/Texture/2DTextureArray.h"
#include "Render/Texture/3DTexture.h"
#include "Render/Texture/CubeTexture.h"

using namespace Matrix;
IMPLEMENT_RTTI(VSRenderTarget, VSOutputResource)
BEGIN_ADD_PROPERTY(VSRenderTarget, VSOutputResource)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSRenderTarget)
IMPLEMENT_INITIAL_END
VSRenderTarget::VSRenderTarget()
{
	m_uiWidth = 512;
	m_uiHeight = 512;
	m_uiFormatType = VSRenderer::SFT_A8R8G8B8;
	m_uiMulSample = VSRenderer::MS_NONE;
	m_pCreateBy = NULL;
	m_bUsed = false;
	m_pLockData = NULL;
	m_uiFirst = 0;
	m_uiLevel = 0;
	m_uiArraySize = 1;
}
VSRenderTarget::VSRenderTarget(unsigned int uiWidth, unsigned int uiHeight,
	unsigned int uiFormatType, unsigned int uiMulSample, bool CPURead)
{
	m_uiWidth = uiWidth;
	m_uiHeight = uiHeight;
	m_uiFormatType = uiFormatType;
	m_uiMulSample = uiMulSample;
	m_pCreateBy = NULL;
	m_uiLevel = 0;
	m_uiFirst = 0;
	m_bUsed = false;
	m_bIsStatic = !CPURead;
	m_uiLockFlag = CPURead ? VSInheritBind::LF_READONLY : VSInheritBind::LF_NOOVERWRITE;
	m_pLockData = NULL;
	m_uiArraySize = 1;
}
VSRenderTarget::VSRenderTarget(VS2DTexture* pCreateBy, unsigned int uiMulSample, unsigned int uiLevel, bool CPURead)
{

	m_uiFirst = 0;
	m_uiFormatType = pCreateBy->GetFormatType();
	m_uiMulSample = uiMulSample;
	m_pCreateBy = pCreateBy;
	m_uiLevel = uiLevel;
	m_uiWidth = pCreateBy->GetWidth(m_uiLevel);
	m_uiHeight = pCreateBy->GetHeight(m_uiLevel);
	m_bUsed = false;
	m_bIsStatic = !CPURead;
	m_uiLockFlag = CPURead ? VSInheritBind::LF_READONLY : VSInheritBind::LF_NOOVERWRITE;
	m_pLockData = NULL;
	m_uiArraySize = 1;
	if (!pCreateBy->SetOutput(this))
	{
		ENGINE_ASSERT(0);
	}
}
VSRenderTarget::VSRenderTarget(VS2DTextureArray* pCreateBy, unsigned int uiMulSample, unsigned int uiLevel,
	unsigned int First, unsigned int uiArraySize, bool CPURead)
{
	if (pCreateBy->GetTexType() == VSTexture::TT_CUBE && uiArraySize > VSCubeTexture::F_MAX)
	{
		m_uiArraySize = VSCubeTexture::F_MAX;
	}

	m_uiFirst = First;

	m_uiFormatType = pCreateBy->GetFormatType();
	m_uiMulSample = uiMulSample;
	m_pCreateBy = pCreateBy;
	m_uiLevel = uiLevel;
	m_uiWidth = pCreateBy->GetWidth(m_uiLevel);
	m_uiHeight = pCreateBy->GetHeight(m_uiLevel);
	m_bUsed = false;
	m_bIsStatic = !CPURead;
	m_uiLockFlag = CPURead ? VSInheritBind::LF_READONLY : VSInheritBind::LF_NOOVERWRITE;
	m_pLockData = NULL;
	m_uiArraySize = uiArraySize;
	if (!pCreateBy->SetOutput(this))
	{
		ENGINE_ASSERT(0);
	}
}
VSRenderTarget::VSRenderTarget(VS3DTexture* pCreateBy, unsigned int uiMulSample, unsigned int uiLevel,
	unsigned int First, unsigned int uiArraySize, bool CPURead)
{
	m_uiFirst = First;
	m_uiFormatType = pCreateBy->GetFormatType();
	m_uiMulSample = uiMulSample;
	m_pCreateBy = pCreateBy;
	m_uiLevel = uiLevel;
	m_uiWidth = pCreateBy->GetWidth(m_uiLevel);
	m_uiHeight = pCreateBy->GetHeight(m_uiLevel);
	m_bUsed = false;
	m_bIsStatic = !CPURead;
	m_uiLockFlag = CPURead ? VSInheritBind::LF_READONLY : VSInheritBind::LF_NOOVERWRITE;
	m_pLockData = NULL;
	m_uiArraySize = uiArraySize;
	if (!pCreateBy->SetOutput(this))
	{
		ENGINE_ASSERT(0);
	}
}
VSRenderTarget::~VSRenderTarget()
{
	ReleaseResource();
	m_pCreateBy = NULL;
}
bool VSRenderTarget::OnLoadResource(VSResourceIdentifier*& pID)
{

	if (!m_pUser->OnLoadRenderTarget(this, pID))
		return 0;
	return 1;
}
void* VSRenderTarget::Lock()
{
	if (m_pLockData)
	{
		return NULL;
	}

	m_pLockData = m_pUser->Lock(this);

	return m_pLockData;
}
void VSRenderTarget::UnLock()
{
	if (!m_pLockData)
	{
		return;
	}

	m_pUser->UnLock(this);

	m_pLockData = NULL;
}