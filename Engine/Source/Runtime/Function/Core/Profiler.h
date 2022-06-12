//#pragma once
//#include "Function/FunctionCore.h"
//#include "InitialMacro.h"
//
//#include "Math/Vector4.h"
//#include "Container/String.h"
//#include "Container/Array.h"
//
//
//namespace Matrix
//{
//	class VSRenderer;
//	class VSProfilerNode;
//	struct ProfilerString
//	{
//		int iX;
//		int iY;
//		Math::ColorRGBA rColor;
//		Container::MString sText;
//	};
//	class MATRIX_FUNCTION_API VSProfiler
//	{
//	public:
//		DECLARE_INITIAL_ONLY
//		static void AddProfileNode(VSProfilerNode* pProfilerNode);
//		static void Draw();
//		static void Draw(VSRenderer* pRenderer);
//		static void GetProfilerNameString(const Container::MString& Name, unsigned int uiLayer, Container::MString& OutString);
//		static void ClearAll();
//		static unsigned int ms_uiCurCount;
//
//	protected:
//		static Container::MArray<VSProfilerNode*>& GetProfilerNode()
//		{
//			static Container::MArray<VSProfilerNode*> m_pProfilerNodes;
//			return m_pProfilerNodes;
//		}
//
//		static bool InitialDefaultState();
//		static Container::MArray<VSProfilerNode*> m_pRoot;
//		static TCHAR* ms_LayerFlag[10];
//	};
//
//	class MATRIX_FUNCTION_API VSProfilerNode
//	{
//	public:
//		VSProfilerNode(const TCHAR* Name = NULL, const TCHAR* ParentName = NULL);
//
//		virtual void Clear() = 0;
//		void AddChild(VSProfilerNode* pChild);
//		void Draw(unsigned int uiLayer);
//
//	protected:
//		virtual void OnDraw(unsigned int uiLayer) = 0;
//		friend class VSProfilerNodeTImer;
//		friend class VSProfiler;
//
//		VSProfilerNode* m_pParentNode;
//		Container::MArray<VSProfilerNode*> m_pChildNode;
//		Container::MString m_Name;
//		Container::MString m_ParentName;
//	};
//	class MATRIX_FUNCTION_API VSTimeProfilerNode : public VSProfilerNode
//	{
//	public:
//		class MATRIX_FUNCTION_API VSProfilerNodeTImer
//		{
//		public:
//			VSProfilerNodeTImer(VSTimeProfilerNode* pProfilerNode);
//			~VSProfilerNodeTImer();
//
//		protected:
//			VSTimeProfilerNode* m_pOwner;
//			VSREAL m_fBeginTime;
//		};
//		VSTimeProfilerNode(const TCHAR* Name = NULL, const TCHAR* ParentName = NULL);
//		virtual void Clear()
//		{
//			m_fProfilerTime = 0.0f;
//		}
//		virtual void OnDraw(unsigned int uiLayer);
//
//	protected:
//		VSREAL m_fProfilerTime;
//	};
//	class MATRIX_FUNCTION_API VSCountProfilerNode : public VSProfilerNode
//	{
//	public:
//		class MATRIX_FUNCTION_API VSProfilerNodeCounter
//		{
//		public:
//			VSProfilerNodeCounter(VSCountProfilerNode* pProfilerNode, int uiCount);
//		};
//		VSCountProfilerNode(const TCHAR* Name = NULL, const TCHAR* ParentName = NULL);
//		virtual void Clear()
//		{
//			m_uiCounter = 0;
//		}
//		virtual void OnDraw(unsigned int uiLayer);
//
//	protected:
//		int m_uiCounter;
//	};
//	class MATRIX_FUNCTION_API VSNoClearCountProfilerNode : public VSCountProfilerNode
//	{
//	public:
//		VSNoClearCountProfilerNode(const TCHAR* Name = NULL, const TCHAR* ParentName = NULL);
//		virtual void Clear()
//		{
//		}
//	};
//	class MATRIX_FUNCTION_API VSOnlyTimeProfilerNode : public VSProfilerNode
//	{
//	public:
//		class MATRIX_FUNCTION_API VSProfilerNodeOnlyTImer
//		{
//		public:
//			VSProfilerNodeOnlyTImer(VSOnlyTimeProfilerNode* pProfilerNode, VSREAL fProfilerTime);
//		};
//		VSOnlyTimeProfilerNode(const TCHAR* Name = NULL, const TCHAR* ParentName = NULL);
//		virtual void Clear()
//		{
//			m_fProfilerTime = 0.0f;
//		}
//		virtual void OnDraw(unsigned int uiLayer);
//
//	protected:
//		VSREAL m_fProfilerTime;
//	};
//#ifdef PROFILER
//#define EXTERN_TIME_PROFILENODE(Name) extern MATRIX_FUNCTION_API VSTimeProfilerNode TimeProfilerNode_##Name;
//#define DECLEAR_TIME_PROFILENODE(Name, ParentName) VSTimeProfilerNode TimeProfilerNode_##Name(_T(#Name), _T(#ParentName));
//#define ADD_TIME_PROFILE(Name) VSTimeProfilerNode::VSProfilerNodeTImer ProfilerNodeTimer_##Name(&TimeProfilerNode_##Name);
//
//#define EXTERN_COUNT_PROFILENODE(Name) extern MATRIX_FUNCTION_API VSCountProfilerNode CountProfilerNode_##Name;
//#define DECLEAR_COUNT_PROFILENODE(Name, ParentName) VSCountProfilerNode CountProfilerNode_##Name(_T(#Name), _T(#ParentName));
//#define EXTERN_NOCLEAR_COUNT_PROFILENODE(Name) extern MATRIX_FUNCTION_API VSNoClearCountProfilerNode CountProfilerNode_##Name;
//#define DECLEAR_NOCLEAR_COUNT_PROFILENODE(Name, ParentName) VSNoClearCountProfilerNode CountProfilerNode_##Name(_T(#Name), _T(#ParentName));
//#define ADD_COUNT_PROFILE(Name, Count) VSCountProfilerNode::VSProfilerNodeCounter ProfilerNodeCounter_##Name(&CountProfilerNode_##Name, Count);
//
//#define EXTERN_ONLYTIME_PROFILENODE(Name) extern MATRIX_FUNCTION_API VSOnlyTimeProfilerNode OnlyTimeProfilerNode_##Name;
//#define DECLEAR_ONLYTIME_PROFILENODE(Name, ParentName) VSOnlyTimeProfilerNode OnlyTimeProfilerNode_##Name(_T(#Name), _T(#ParentName));
//#define ADD_ONLYTIME_PROFILE(Name, fProfilerTime) VSOnlyTimeProfilerNode::VSProfilerNodeOnlyTImer ProfilerNodeOnlyTimer_##Name(&OnlyTimeProfilerNode_##Name, fProfilerTime);
//#else
//#define EXTERN_TIME_PROFILENODE(Name)
//#define DECLEAR_TIME_PROFILENODE(Name, ParentName)
//#define ADD_TIME_PROFILE(Name)
//
//#define EXTERN_COUNT_PROFILENODE(Name)
//#define EXTERN_NOCLEAR_COUNT_PROFILENODE(Name)
//#define DECLEAR_COUNT_PROFILENODE(Name, ParentName)
//#define DECLEAR_NOCLEAR_COUNT_PROFILENODE(Name, ParentName)
//#define ADD_COUNT_PROFILE(Name, Count)
//
//#define EXTERN_ONLYTIME_PROFILENODE(Name)
//#define DECLEAR_ONLYTIME_PROFILENODE(Name, ParentName)
//#define ADD_ONLYTIME_PROFILE(Name, fProfilerTime)
//#endif
//}