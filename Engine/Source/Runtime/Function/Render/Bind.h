#pragma once
#include "Core/Object.h"

namespace Matrix
{

	/*
	*VSResourceIdentifier 类是一个虚基类，每个 API（D3D 或 OpenGL）层渲染资源都必须继承自它
	*/
	class MATRIX_FUNCTION_API VSResourceIdentifier
	{
	public:
		virtual ~VSResourceIdentifier()
		{ /**/
		}

	protected:
		VSResourceIdentifier()
		{ /**/
		}
	};



	class MStream;
	/*
	*  凡是和底层 API资源绑定的类都要继承自 VSBind, 是所有渲染资源的基类，它提供通用的接口
	*/
	class MATRIX_FUNCTION_API VSBind : public MObject
	{

		// RTTI
		DECLARE_RTTI;
		DECLARE_INITIAL_NO_CLASS_FACTORY;

	public:
		VSBind();
		virtual ~VSBind() = 0;
		//得到当前可以用的绑定资源
		virtual VSResourceIdentifier* GetIdentifier();
		//绑定资源的个数
		unsigned int GetInfoQuantity() const;

		static Container::MArray<VSBind*> ms_BindArray;

	protected:
		friend class VSRenderer;

		void Bind(VSResourceIdentifier* pID);

		struct INFO_TYPE
		{
			INFO_TYPE()
			{
				ID = NULL;
			}
			~INFO_TYPE()
			{
			}
			VSResourceIdentifier* ID;
		};
		Container::MArray<INFO_TYPE> m_InfoArray;

		VSRenderer* m_pUser;

	public:
		virtual bool LoadResource(VSRenderer* pRender);
		virtual bool ReleaseResource();

		bool IsBindResource() const
		{
			return m_InfoArray.GetNum() > 0;
		}

	protected:
		virtual bool OnLoadResource(VSResourceIdentifier*& pID) = 0;
		virtual bool OnReleaseResource(VSResourceIdentifier* pID);
	};

	DECLARE_Ptr(VSBind);
	VSTYPE_MARCO(VSBind);

}
