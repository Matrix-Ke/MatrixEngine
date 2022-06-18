#pragma once
#include "Render/Bind.h"
namespace Matrix
{
	class MStream;
	/*
	* 以通过 VSBlendDesc 来创建 VSBlendState
	*/
	class MATRIX_FUNCTION_API VSBlendDesc : public MObject
	{
		DECLARE_RTTI;
		DECLARE_INITIAL
	public:
		enum
		{
			MAX_RENDER_TARGET_NUM = 8
		};
		enum // Blend Parameter
		{
			BP_ZERO,
			BP_ONE,
			BP_SRCCOLOR,
			BP_INVSRCCOLOR,
			BP_SRCALPHA,
			BP_INVSRCALPHA,
			BP_DESTALPHA,
			BP_INVDESTALPHA,
			BP_DESTCOLOR,
			BP_INVDESTCOLOR,
			BP_MAX
		};
		enum // Blend OP
		{
			BO_ADD,
			BO_SUBTRACT,
			BO_REVSUBTRACT,
			BO_MIN_SRC_DEST,
			BO_MAX_SRC_DEST,
			BO_MAX

		};
		enum // Write Mask
		{
			WM_NONE = 0,
			WM_ALPHA = BIT(0),
			WM_RED = BIT(1),
			WM_Green = BIT(2),
			WM_BLUE = BIT(3),
			WM_ALL = 0X0F
		};
		VSBlendDesc()
		{
			bAlphaToCoverageEnable = false;
			bIndependentBlendEnable = false;
			for (unsigned int i = 0; i < MAX_RENDER_TARGET_NUM; i++)
			{
				bBlendEnable[i] = false;
				ucSrcBlend[i] = BP_ONE;
				ucDestBlend[i] = BP_ZERO;
				ucBlendOp[i] = BO_ADD;

				bAlphaBlendEnable[i] = false;
				ucSrcBlendAlpha[i] = BP_ONE;
				ucDestBlendAlpha[i] = BP_ZERO;
				ucBlendOpAlpha[i] = BO_ADD;
				ucWriteMask[i] = WM_ALL;
			}
			// 			fBlendFactor[0] = fBlendFactor[1] = fBlendFactor[2] = fBlendFactor[3] = 0.0f;
			// 			ucSampleMask = 0xffffffff;
		}
		~VSBlendDesc()
		{
		}
		bool bAlphaToCoverageEnable;
		bool bIndependentBlendEnable;
		// 		VSREAL			fBlendFactor[4];
		// 		unsigned int	ucSampleMask;
		bool bBlendEnable[MAX_RENDER_TARGET_NUM]; //是否开启颜色混合
		unsigned char ucSrcBlend[MAX_RENDER_TARGET_NUM]; //源混合因子
		unsigned char ucDestBlend[MAX_RENDER_TARGET_NUM]; //目标混合因子
		unsigned char ucBlendOp[MAX_RENDER_TARGET_NUM];//混合方式
		bool bAlphaBlendEnable[MAX_RENDER_TARGET_NUM]; //是否开启透明度混合
		unsigned char ucSrcBlendAlpha[MAX_RENDER_TARGET_NUM]; //透明度源混合因子
		unsigned char ucDestBlendAlpha[MAX_RENDER_TARGET_NUM]; //透明度目标混合因子
		unsigned char ucBlendOpAlpha[MAX_RENDER_TARGET_NUM]; //透明度混合方式
		unsigned char ucWriteMask[MAX_RENDER_TARGET_NUM];  //颜色写入标记

		bool IsBlendUsed(unsigned int uiChannal = 0) const
		{
			return (bBlendEnable[uiChannal] || bAlphaBlendEnable[uiChannal]);
		}
		void* GetCRC32Data(unsigned int& DataSize) const
		{
			DataSize = sizeof(VSBlendDesc) - sizeof(MObject);
			return (void*)&bAlphaToCoverageEnable;
		}
	};
	VSTYPE_MARCO(VSBlendDesc);

	/*
	VSBlendState 类和 DirectX 11 中的混合状态（blend state）类似，主要对透明度（alpha）和颜色进行混合，
	最多支持 8 个渲染目标，可以通过 VSBlendDesc 来创建 VSBlendState，
	*/
	class MATRIX_FUNCTION_API VSBlendState : public VSBind
	{
		// PRIORITY

		// RTTI
		DECLARE_RTTI;

	public:
		virtual ~VSBlendState();

	protected:
		VSBlendState();
		VSBlendDesc m_BlendDesc;

	protected:
		static VSPointer<VSBlendState> ms_Default;

	public:
		static const VSBlendState* GetDefault()
		{
			return ms_Default;
		}

	public:
		DECLARE_INITIAL

		static bool InitialDefaultState();
		static bool TerminalDefaultState();

	public:
		inline const VSBlendDesc& GetBlendDesc() const
		{
			return m_BlendDesc;
		}
		friend class VSResourceManager;

	protected:
		virtual bool OnLoadResource(VSResourceIdentifier*& pID);
	};
	DECLARE_Ptr(VSBlendState);
	VSTYPE_MARCO(VSBlendState);
}