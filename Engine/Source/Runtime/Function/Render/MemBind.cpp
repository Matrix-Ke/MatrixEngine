#include "Render/MemBind.h"
#include "Core/ResourceManager.h"
#include "Core/GraphicInclude.h"
#include "Asyn/RenderThread.h"
using namespace Matrix;
IMPLEMENT_RTTI_NoCreateFun(VSMemBind, VSInheritBind)
IMPLEMENT_INITIAL_NO_CLASS_FACTORY_BEGIN(VSMemBind)
IMPLEMENT_INITIAL_NO_CLASS_FACTORY_END
BEGIN_ADD_PROPERTY(VSMemBind, VSInheritBind)
REGISTER_PROPERTY(m_uiSwapChainNum, SwapChainNum, VSProperty::F_SAVE_LOAD_CLONE);
REGISTER_PROPERTY(m_uiMemType, MemType, VSProperty::F_SAVE_LOAD_CLONE);
END_ADD_PROPERTY
VSMemBind::VSMemBind(unsigned int uiMemType)
{
	m_uiSwapChainNum = 1;
	m_uiCurID = 0;

	m_uiMemType = uiMemType;
}
VSMemBind::~VSMemBind()
{
	if (!m_bIsStatic && m_uiSwapChainNum == 2)
	{
		if (VSResourceManager::ms_bRenderThread)
		{
			VSResourceManager::GetDelayUpdateNoTimeObject().RemoveMethod<VSMemBind, &VSMemBind::ExChange>(this);
		}
	}
}
VSResourceIdentifier* VSMemBind::GetIdentifier()
{
	if (!m_InfoArray.GetNum())
	{
		return NULL;
	}
	VSResourceIdentifier* pID = NULL;
	pID = m_InfoArray[m_uiCurID].ID;
	return pID;
}
void VSMemBind::SetStatic(bool bIsStatic, bool bMulThreadUse)
{
	if (!m_bIsStatic && m_uiSwapChainNum == 2)
	{
		if (VSResourceManager::ms_bRenderThread)
		{
			VSResourceManager::GetDelayUpdateNoTimeObject().RemoveMethod<VSMemBind, &VSMemBind::ExChange>(this);
		}
	}
	m_bIsStatic = bIsStatic;

	if (m_bIsStatic)
	{
		m_uiSwapChainNum = 1;
	}
	else
	{
		//在多线程渲染模式下，如需在主线程使用动态资源，这种资源必须渲染 API 支持才可以创建
		if (VSResourceManager::ms_bRenderThread && bMulThreadUse && VSRenderer::ms_pRenderer->IsSupportFeature(VSRenderer::SF_MulBufferSwtich))
		{

			m_uiSwapChainNum = 2;
			//并将其加入全局动态双缓存资源列表
			VSResourceManager::GetDelayUpdateNoTimeObject().AddMethod<VSMemBind, &VSMemBind::ExChange>(this);
		}
		else
		{
			m_uiSwapChainNum = 1;
		}
	}

	m_uiCurID = 0;
}
void VSMemBind::ExChange()
{
	if (!m_bIsStatic && m_uiSwapChainNum == 2)
	{
		m_uiCurID = (m_uiCurID + 1) % m_uiSwapChainNum;
	}
}
bool VSMemBind::LoadResource(VSRenderer* pRender)
{
	if (!pRender)
		return 0;
	//如果资源是纯内存资源，则直接返回
	if (m_uiMemType == MT_RAM)
	{
		return 1;
	}
	//表示资源创建完毕，直接返回
	if (m_uiSwapChainNum == m_InfoArray.GetNum())
		return 1;
	else
	{
		m_pUser = pRender;
		for (unsigned int i = 0; i < m_uiSwapChainNum; i++)
		{
			VSResourceIdentifier* pID = NULL;
			if (!OnLoadResource(pID))
				return 0;
			if (!pID)
				return 0;
			Bind(pID);
		}
		////对于非多线程，则资源创建完毕后直接清空内存数据
		ENQUEUE_LAMBDA_RENDER_COMMAND(ClearInfoCommand)
			([this]()
				{ ClearInfo(); });
		return 1;
	}
}