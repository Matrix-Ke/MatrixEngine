#pragma once
#include "Render/InheritBind.h"
namespace Matrix
{

	class MATRIX_FUNCTION_API VSMemBind : public VSInheritBind
	{

		// RTTI
		DECLARE_RTTI;
		DECLARE_INITIAL_NO_CLASS_FACTORY;

	public:
		enum // Mem Type
		{
			MT_BOTH, //保留内存和显存数据
			MT_RAM, //保留内存数据
			MT_VRAM, //保留显存数据,一旦设置了 MT_VRAM，在帧末就会判断内存占用情况并清空内存
			MT_MAX
		};

		VSMemBind(unsigned int uiMemType = MT_VRAM);
		virtual ~VSMemBind() = 0;

		virtual VSResourceIdentifier* GetIdentifier();
		//如果此资源需要lock，并且是多线程渲染，为了有效利用多线效率，lock函数如果在主线程使用请设置bmulthreadUse为true
				/*
		SetStatic 函数表示资源是否可以动态更新。如果此资源在主线程和渲染线程中都需要更新，
		就会为它创建绑定两个 API 层的资源，并将其加入全局动态双缓存资源列表 ms_DynamicTwoBindArray。m_uiSwapChainNum 表示绑定 API 层的资源个数
		*/
		virtual void SetStatic(bool bIsStatic, bool bMulThreadUse = false);
		void ExChange();

	protected:
		virtual void ClearInfo() = 0;

		unsigned int m_uiSwapChainNum; //m_uiSwapChainNum 表示绑定 API 层的资源个数; 在主线程和渲染线程
		unsigned int m_uiCurID;

		unsigned int m_uiMemType;

	public:
		virtual bool LoadResource(VSRenderer* pRender);
		virtual unsigned int GetByteSize() const = 0;

		inline void SetMemType(unsigned int uiMemType)
		{
			if (uiMemType < MT_MAX)
			{
				m_uiMemType = uiMemType;
			}
		}
		inline unsigned int GetMemType() const
		{
			return m_uiMemType;
		}
		inline unsigned int GetSwapChainNum() const
		{
			return m_uiSwapChainNum;
		}
	};
	DECLARE_Ptr(VSMemBind);
	VSTYPE_MARCO(VSMemBind);

}
