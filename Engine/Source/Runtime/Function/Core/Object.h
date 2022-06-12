#pragma once
#include "Function/EngineInit.h"
#include "Core/Meta/Rtti.h"
#include "Core/Meta/Rttimacro.h"
#include "Core/Meta/ObjName.h"
#include "Reference.h"

#include "Platform/MemoryManager.h"
#include "Container/Hash.h"
#include "Container/String.h"
#include "Container/Map.h"
#include "Container/List.h"

namespace Matrix
{
	// namespace Function
	//{
	// using namespace Matrix::Container;
	class MObject;
	typedef MObject* (*FactoryFunction)();
	class VSRenderer;
	class VSResourceIdentifier;
	class MStream;
	class VSResourceProxyBase;

	// VSFastObjectManager 最多管理 MAX_OBJECT_NUM 个对象，这里设置为 99 999，不够的
	//	话也可以修改。它的本质思想很简单，就是把所有未被占用的 ID 记录到 m_FreeTable 里面，在
	//	申请的时候（调用 MObject 构造函数）从 m_FreeTable 链表末端取出一个，在 m_ObjectArray
	//	数组中记录对应的 MObject 对象，在释放的时候（调用 MObject 析构函数）归还给 m_FreeTable
	//	链表，从 m_ObjectArray 数组中删除对应的 MObject 对象
	class VSFastObjectManager
	{
	public:
		VSFastObjectManager();
		~VSFastObjectManager();

		void AddObject(MObject* p);
		void DeleteObject(MObject* p);
		bool IsClear();
		void PrepareForGC();
		unsigned int GetObjectNum();

	protected:
		Container::MHashTree<MObject*> ObjectHashTree;
		unsigned int m_uiObjectNum;
	};

	class MATRIX_FUNCTION_API MObject : public VSReference, public Core::MemoryObject
	{
	public:
		friend class MStream;
		friend class VSAsynStream;
		virtual ~MObject() = 0;
		MObject(const MObject& object);
		MObject& operator=(const MObject& object);
		MObject();

		// RTTI
		DECLARE_RTTI;

	public:
		bool IsSameType(const MObject* pObject) const;
		bool IsDerived(const MObject* pObject) const;
		bool IsSameType(const VSRtti& Type) const;
		bool IsDerived(const VSRtti& Type) const;

		DECLARE_INITIAL_NO_CLASS_FACTORY;
		// static bool InitialDefaultState();
		// static bool TerminateDefaltState();

		// Stream
	public:
		static MObject* GetInstance(const Container::MString& sRttiName);
		static MObject* GetInstance(const VSRtti& Rtti);
		template <typename T>
		static T* GetInstance()
		{
			return (T*)GetInstance(T::ms_Type);
		}
		virtual bool BeforeSave(MStream* pStream);
		virtual bool PostSave(MStream* pStream);
		virtual bool PostLoad(MStream* pStream);

	protected:
		static Container::MMapOrder<VSUsedName, FactoryFunction> ms_ClassFactory;
		static MObject* GetNoGCInstance(const Container::MString& sRttiName);

	public:
		friend class VSFastObjectManager;
		static VSFastObjectManager& GetObjectManager()
		{
			static VSFastObjectManager ms_ObjectManager;
			return ms_ObjectManager;
		}
		virtual void LoadedEvent(VSResourceProxyBase* pResourceProxy, void* Data = NULL);
		// todo list  GetStreamResource
		// virtual void GetStreamResource(Container::MArray<VSResourceProxyBase*>& pResourceProxy, StreamInformation_TYPE& StreamInformation)const;

		// debug
	public:
		// todo list 日志系统
		// bool DebugLevel(VSLog& log)const;
		//先检查当前克隆的 MObject 对象是否创建，若没有创建，则先创建，然后遍历 MObject 的所有属性并克隆。
		//递归操作，直到所有属性处理完毕。如果对象已创建，则让当前指针指向它即可。所有克隆的 MObject 会调用 PostClone 来进行最后的处理。
		static MObject* _CloneCreateObject(MObject* pObject, Container::MMap<MObject*, MObject*>& CloneMap);
		static void _CloneObject(MObject* pObjectSrc, MObject* pObjectDest, Container::MMap<MObject*, MObject*>& CloneMap);

		static MObject* CloneCreateObject(MObject* pObject);
		static void CloneObject(MObject* pObjectSrc, MObject* pObjectDest);

		virtual bool PostClone(MObject* pObjectSrc);
		virtual void ValueChange(Container::MString& Name);
		bool Process(VSUsedName& FunName, void* para, void* ret = NULL, int ParaNum = -1);

		void CallVoidFun(VSUsedName& FunName)
		{
			Process(FunName, NULL);
		}
		template <class Type1>
		void CallVoidFun(VSUsedName& FunName, Type1& t1)
		{
			struct MyStruct
			{
				Type1 t1;
			} Temp;
			Temp.t1 = t1;
			Process(FunName, (void*)&Temp, NULL, 1);
		}
		template <class Type1, class Type2>
		void CallVoidFun(VSUsedName& FunName, Type1& t1, Type2& t2)
		{
			struct MyStruct
			{
				Type1 t1;
				Type2 t2;
			} Temp;
			Temp.t1 = t1;
			Temp.t2 = t2;
			Process(FunName, (void*)&Temp, NULL, 2);
		}

		template <class Type1, class Type2, class Type3>
		void CallVoidFun(VSUsedName& FunName, Type1& t1, Type2& t2, Type3& t3)
		{
			struct MyStruct
			{
				Type1 t1;
				Type2 t2;
				Type3 t3;
			} Temp;
			Temp.t1 = t1;
			Temp.t2 = t2;
			Temp.t3 = t3;
			Process(FunName, (void*)&Temp, NULL, 3);
		}

		template <class Type1, class Type2, class Type3, class Type4>
		void CallVoidFun(VSUsedName& FunName, Type1& t1, Type2& t2, Type3& t3, Type4& t4)
		{
			struct MyStruct
			{
				Type1 t1;
				Type2 t2;
				Type3 t3;
				Type4 t4;
			} Temp;
			Temp.t1 = t1;
			Temp.t2 = t2;
			Temp.t3 = t3;
			Temp.t4 = t4;
			Process(FunName, (void*)&Temp, NULL, 4);
		}
		template <class ReturnType>
		void CallFun(VSUsedName& FunName, ReturnType& ReturnValue)
		{
			Process(FunName, NULL, (void*)&ReturnValue);
		}
		template <class ReturnType, class Type1>
		void CallFun(VSUsedName& FunName, ReturnType& ReturnValue, Type1& t1)
		{
			struct MyStruct
			{
				Type1 t1;
			} Temp;
			Temp.t1 = t1;
			Process(FunName, (void*)&Temp, (void*)&ReturnValue, 1);
		}
		template <class ReturnType, class Type1, class Type2>
		void CallFun(VSUsedName& FunName, ReturnType& ReturnValue, Type1& t1, Type2& t2)
		{
			struct MyStruct
			{
				Type1 t1;
				Type2 t2;
			} Temp;
			Temp.t1 = t1;
			Temp.t2 = t2;
			Process(FunName, (void*)&Temp, (void*)&ReturnValue, 2);
		}

		template <class ReturnType, class Type1, class Type2, class Type3>
		void CallFun(VSUsedName& FunName, ReturnType& ReturnValue, Type1& t1, Type2& t2, Type3& t3)
		{
			struct MyStruct
			{
				Type1 t1;
				Type2 t2;
				Type3 t3;
			} Temp;
			Temp.t1 = t1;
			Temp.t2 = t2;
			Temp.t3 = t3;
			Process(FunName, (void*)&Temp, (void*)&ReturnValue, 3);
		}

		template <class ReturnType, class Type1, class Type2, class Type3, class Type4>
		void CallFun(VSUsedName& FunName, ReturnType& ReturnValue, Type1& t1, Type2& t2, Type3& t3, Type4& t4)
		{
			struct MyStruct
			{
				Type1 t1;
				Type2 t2;
				Type3 t3;
				Type4 t4;
			} Temp;
			Temp.t1 = t1;
			Temp.t2 = t2;
			Temp.t3 = t3;
			Temp.t4 = t4;
			Process(FunName, (void*)&Temp, (void*)&ReturnValue, 4);
		}

	public:
		enum // Object Flag
		{
			OF_REACH = 0x01,
			OF_UNREACH = 0x02,
			OF_PendingKill = 0x04,
			OF_GCObject = 0x08,
			OF_RootObject = 0x10,
			OF_MAX
		};
		inline void SetFlag(unsigned int uiFlag)
		{

			m_uiFlag |= uiFlag;
		}
		inline void ClearFlag(unsigned int uiFlag)
		{
			m_uiFlag &= ~uiFlag;
		}
		inline bool IsHasFlag(unsigned int uiFlag)
		{
			return (m_uiFlag & uiFlag) != 0;
		}
		unsigned int m_uiFlag;
		inline void DecreRef()
		{
			Core::MXLockedDecrement((long*)&m_iReference);
			if (!m_iReference)
			{
				if (IsHasFlag(OF_GCObject))
				{
					SetFlag(OF_PendingKill);
				}
				else
				{
					MX_DELETE this;
				}
			}
		}
	};
	DECLARE_Ptr(MObject);
	VSTYPE_MARCO(MObject);

	//根据rtti信息进行动态类型转化，其实也可以采用虚函数的形式。 虚函数表记录了动态类型信息
	template <class T>
	T* StaticCast(MObject* pkObj)
	{
		return (T*)pkObj;
	}
	template <class T>
	const T* StaticCast(const MObject* pkObj)
	{
		return (const T*)pkObj;
	}
	template <class T>
	T* DynamicCast(MObject* pObj)
	{
		return pObj && pObj->IsDerived(T::ms_Type) ? (T*)pObj : 0;
	}

	template <class T>
	const T* DynamicCast(const MObject* pObj)
	{
		return pObj && pObj->IsDerived(T::ms_Type) ? (const T*)pObj : 0;
	}
	//}
}
