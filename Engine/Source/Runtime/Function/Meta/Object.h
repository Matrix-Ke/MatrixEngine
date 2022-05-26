#pragma once

#include "Rtti.h"
#include "Rttimacro.h"
#include "ObjName.h"
#include "Reference.h"
#include "PropertyMarco.h"

#include "Core/MemoryManager.h"
#include "Container/Hash.h"
#include "Container/String.h"
#include "Container/Map.h"
#include "Container/List.h"

namespace  Matrix
{
	//namespace Function
	//{
	//using namespace Matrix::Container;
	class VSObject;
	typedef VSObject* (*FactoryFunction)();
	class VSRenderer;
	class VSResourceIdentifier;
	class VSStream;
	class VSResourceProxyBase;

	//VSFastObjectManager ������ MAX_OBJECT_NUM ��������������Ϊ 99 999��������
	//	��Ҳ�����޸ġ����ı���˼��ܼ򵥣����ǰ�����δ��ռ�õ� ID ��¼�� m_FreeTable ���棬��
	//	�����ʱ�򣨵��� VSObject ���캯������ m_FreeTable ����ĩ��ȡ��һ������ m_ObjectArray
	//	�����м�¼��Ӧ�� VSObject �������ͷŵ�ʱ�򣨵��� VSObject �����������黹�� m_FreeTable
	//	������ m_ObjectArray ������ɾ����Ӧ�� VSObject ����
	class VSFastObjectManager
	{
	public:
		VSFastObjectManager();
		~VSFastObjectManager();

		void AddObject(VSObject* p);
		void DeleteObject(VSObject* p);
		bool IsClear();
		void PrepareForGC();
		unsigned int GetObjectNum();
	protected:
		Container::MHashTree<VSObject*> ObjectHashTree;
		unsigned int m_uiObjectNum;
	};


	class MATRIX_FUNCTION_API VSObject :public VSReference, public Core::MemoryObject
	{
	public:

		friend class VSStream;
		friend class VSAsynStream;
		virtual ~VSObject() = 0;
		VSObject(const VSObject& object);
		VSObject& operator =(const VSObject& object);
		VSObject();

		//RTTI
		DECLARE_RTTI;
	public:
		bool IsSameType(const VSObject* pObject)const;
		bool IsDerived(const VSObject* pObject)const;
		bool IsSameType(const VSRtti& Type)const;
		bool IsDerived(const VSRtti& Type)const;

		DECLARE_INITIAL_NO_CLASS_FACTORY;

		//Stream
	public:
		static VSObject* GetInstance(const Container::MString& sRttiName);
		static VSObject* GetInstance(const VSRtti& Rtti);
		template<typename T>
		static T* GetInstance()
		{
			return (T*)GetInstance(T::ms_Type);
		}
		virtual bool BeforeSave(VSStream* pStream);
		virtual bool PostSave(VSStream* pStream);
		virtual bool PostLoad(VSStream* pStream);
	protected:
		static Container::MMapOrder<VSUsedName, FactoryFunction> ms_ClassFactory;
		static VSObject* GetNoGCInstance(const Container::MString& sRttiName);

	public:
		friend class VSFastObjectManager;
		static VSFastObjectManager& GetObjectManager()
		{
			static VSFastObjectManager ms_ObjectManager;
			return  ms_ObjectManager;
		}
		virtual void LoadedEvent(VSResourceProxyBase* pResourceProxy, void* Data = NULL);
		//todo list  GetStreamResource
		//virtual void GetStreamResource(Container::MArray<VSResourceProxyBase*>& pResourceProxy, StreamInformation_TYPE& StreamInformation)const;

		//debug
	public:
		//todo list ��־ϵͳ
		//bool DebugLevel(VSLog& log)const;
		//�ȼ�鵱ǰ��¡�� VSObject �����Ƿ񴴽�����û�д��������ȴ�����Ȼ����� VSObject ���������Բ���¡��
		//�ݹ������ֱ���������Դ�����ϡ���������Ѵ��������õ�ǰָ��ָ�������ɡ����п�¡�� VSObject ����� PostClone ���������Ĵ���
		static VSObject* _CloneCreateObject(VSObject* pObject, Container::MMap<VSObject*, VSObject*>& CloneMap);
		static void _CloneObject(VSObject* pObjectSrc, VSObject* pObjectDest, Container::MMap<VSObject*, VSObject*>& CloneMap);

		static VSObject* CloneCreateObject(VSObject* pObject);
		static void CloneObject(VSObject* pObjectSrc, VSObject* pObjectDest);

		virtual bool PostClone(VSObject* pObjectSrc);
		virtual void ValueChange(Container::MString& Name);
		bool Process(VSUsedName& FunName, void* para, void* ret = NULL, int ParaNum = -1);

		void CallVoidFun(VSUsedName& FunName)
		{
			Process(FunName, NULL);
		}
		template<class Type1>
		void CallVoidFun(VSUsedName& FunName, Type1& t1)
		{
			struct MyStruct
			{
				Type1 t1;
			}Temp;
			Temp.t1 = t1;
			Process(FunName, (void*)&Temp, NULL, 1);
		}
		template<class Type1, class Type2>
		void CallVoidFun(VSUsedName& FunName, Type1& t1, Type2& t2)
		{
			struct MyStruct
			{
				Type1 t1;
				Type2 t2;
			}Temp;
			Temp.t1 = t1;
			Temp.t2 = t2;
			Process(FunName, (void*)&Temp, NULL, 2);
		}

		template<class Type1, class Type2, class Type3>
		void CallVoidFun(VSUsedName& FunName, Type1& t1, Type2& t2, Type3& t3)
		{
			struct MyStruct
			{
				Type1 t1;
				Type2 t2;
				Type3 t3;
			}Temp;
			Temp.t1 = t1;
			Temp.t2 = t2;
			Temp.t3 = t3;
			Process(FunName, (void*)&Temp, NULL, 3);
		}

		template<class Type1, class Type2, class Type3, class Type4>
		void CallVoidFun(VSUsedName& FunName, Type1& t1, Type2& t2, Type3& t3, Type4& t4)
		{
			struct MyStruct
			{
				Type1 t1;
				Type2 t2;
				Type3 t3;
				Type4 t4;
			}Temp;
			Temp.t1 = t1;
			Temp.t2 = t2;
			Temp.t3 = t3;
			Temp.t4 = t4;
			Process(FunName, (void*)&Temp, NULL, 4);
		}
		template<class ReturnType>
		void CallFun(VSUsedName& FunName, ReturnType& ReturnValue)
		{
			Process(FunName, NULL, (void*)&ReturnValue);
		}
		template<class ReturnType, class Type1>
		void CallFun(VSUsedName& FunName, ReturnType& ReturnValue, Type1& t1)
		{
			struct MyStruct
			{
				Type1 t1;
			}Temp;
			Temp.t1 = t1;
			Process(FunName, (void*)&Temp, (void*)&ReturnValue, 1);
		}
		template<class ReturnType, class Type1, class Type2>
		void CallFun(VSUsedName& FunName, ReturnType& ReturnValue, Type1& t1, Type2& t2)
		{
			struct MyStruct
			{
				Type1 t1;
				Type2 t2;
			}Temp;
			Temp.t1 = t1;
			Temp.t2 = t2;
			Process(FunName, (void*)&Temp, (void*)&ReturnValue, 2);
		}

		template<class ReturnType, class Type1, class Type2, class Type3>
		void CallFun(VSUsedName& FunName, ReturnType& ReturnValue, Type1& t1, Type2& t2, Type3& t3)
		{
			struct MyStruct
			{
				Type1 t1;
				Type2 t2;
				Type3 t3;
			}Temp;
			Temp.t1 = t1;
			Temp.t2 = t2;
			Temp.t3 = t3;
			Process(FunName, (void*)&Temp, (void*)&ReturnValue, 3);
		}

		template<class ReturnType, class Type1, class Type2, class Type3, class Type4>
		void CallFun(VSUsedName& FunName, ReturnType& ReturnValue, Type1& t1, Type2& t2, Type3& t3, Type4& t4)
		{
			struct MyStruct
			{
				Type1 t1;
				Type2 t2;
				Type3 t3;
				Type4 t4;
			}Temp;
			Temp.t1 = t1;
			Temp.t2 = t2;
			Temp.t3 = t3;
			Temp.t4 = t4;
			Process(FunName, (void*)&Temp, (void*)&ReturnValue, 4);
		}
	public:
		enum //Object Flag
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
	DECLARE_Ptr(VSObject);
	VSTYPE_MARCO(VSObject);


	//����rtti��Ϣ���ж�̬����ת������ʵҲ���Բ����麯������ʽ�� �麯�����¼�˶�̬������Ϣ
	template <class T>
	T* StaticCast(VSObject* pkObj)
	{
		return (T*)pkObj;
	}
	template <class T>
	const T* StaticCast(const VSObject* pkObj)
	{
		return (const T*)pkObj;
	}
	template<class T>
	T* DynamicCast(VSObject* pObj)
	{
		return pObj && pObj->IsDerived(T::ms_Type) ? (T*)pObj : 0;
	}

	template<class T>
	const T* DynamicCast(const VSObject* pObj)
	{
		return pObj && pObj->IsDerived(T::ms_Type) ? (const T*)pObj : 0;
	}
	//}
}
