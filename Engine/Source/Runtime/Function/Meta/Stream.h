#pragma once
#include "Rtti.h"
#include "Pointer.h"
#include "Type.h"
#include "Resource.h"
#include "CustomArchiveObject.h"
#include "Object.h"

#include "Core/File.h"
#include "Container/Array.h"
#include "Container/Map.h"
#include "Container/String.h"


namespace Matrix
{
	DECLARE_Ptr(MObject);

	// 默认clone指针类型VSType property 都是会重新创建一个实例然后再拷贝数据，为了让不重新创建，添加property的时候，这个property不要加入VSProperty::F_CLONE标志
	//然后再postclone 函数中自己再重新设置 如果只是默认的值拷贝而非创建实例可以设置F_COPY
	template <typename T>
	void Copy(T& Dest, T& Src, Container::MMap<MObject*, MObject*>& CloneMap)
	{
		if (TIsVSResourceProxyPointerType<T>::Value)
		{
			Dest = Src;
		}
		else if (TIsVSPointerType<T>::Value)
		{
			MObject*& TempSrc = *(MObject**)(void*)&Src;
			MObject*& TempDest = *(MObject**)(void*)&Dest;
			TempDest = MObject::_CloneCreateObject(TempSrc, CloneMap);
		}
		else if (TIsVSType<T>::Value)
		{
			MObject* TempSrc = (MObject*)&Src;
			MObject* TempDest = (MObject*)&Dest;
			MObject::_CloneObject(TempSrc, TempDest, CloneMap);
		}
		else if (TIsVSSmartPointerType<T>::Value)
		{
			MObjectPtr& TempSrc = *(MObjectPtr*)(void*)&Src;
			MObjectPtr& TempDest = *(MObjectPtr*)(void*)&Dest;
			TempDest = MObject::_CloneCreateObject(TempSrc, CloneMap);
		}
		else if (TIsCustomType<T>::Value)
		{
			VSCustomArchiveObject* TempSrc = (VSCustomArchiveObject*)(void*)&Src;
			VSCustomArchiveObject* TempDest = (VSCustomArchiveObject*)(void*)&Dest;
			TempDest->CopyFrom(TempSrc, CloneMap);
		}
		else
		{
			Dest = Src;
		}
	}
	template <typename T, class VSMemManagerClass>
	void Copy(Container::MArray<T, VSMemManagerClass>& Dest, Container::MArray<T, VSMemManagerClass>& Src, Container::MMap<MObject*, MObject*>& CloneMap)
	{
		Dest.Clear();
		Dest.SetBufferNum(Src.GetNum());
		for (unsigned int i = 0; i < Src.GetNum(); i++)
		{
			Copy(Dest[i], Src[i], CloneMap);
		}
	}

	template <class Key, class Value, class VSMemManagerClass>
	void Copy(Container::MMap<Key, Value, VSMemManagerClass>& Dest, Container::MMap<Key, Value, VSMemManagerClass>& Src, Container::MMap<MObject*, MObject*>& CloneMap)
	{
		Dest.Clear();
		Dest.SetBufferNum(Src.GetNum());
		for (unsigned int i = 0; i < Src.GetNum(); i++)
		{
			Container::MapElement<Key, Value>& ElementSrc = Src[i];
			Container::MapElement<Key, Value>& ElementDest = Dest[i];
			Copy(ElementDest.Key, ElementSrc.Key, CloneMap);
			Copy(ElementDest.Value, ElementSrc.Value, CloneMap);
		}
	}

	//处理 MObject 对象的过程就是一个递归遍历的过程，可以访问到所有属性，所以根据不同需求，我们可以收集很多有用的信息
	class MATRIX_FUNCTION_API MStream
	{
	public:
		enum // Archive Type序列化类型
		{
			AT_SAVE, //保存
			AT_LOAD, //加载
			AT_LINK, //链接
			AT_REGISTER, //注册
			AT_SIZE, //计算存储数据大小
			AT_POSTLOAD, //后处理
			AT_OBJECT_COLLECT_GC,
			AT_CLEAR_OBJECT_PROPERTY_GC,
			AT_LOAD_OBJECT_COLLECT_GC,
		};

		enum
		{
			UNICODE_FLAG = BIT(0),
			ASYN_LOAD_FLAG = BIT(1)
		};

		template <class T>
		void Archive(T& Io)
		{
			if (m_uiStreamFlag == AT_LOAD)
			{

				if (TIsVSResourceProxyPointerType<T>::Value)
				{
					VSResourceProxyBasePtr& Temp = *(VSResourceProxyBasePtr*)(void*)&Io;
					ReadResource(Temp);
				}
				else if (TIsVSPointerType<T>::Value)
				{
					MObject*& Temp = *(MObject**)(void*)&Io;
					ReadObjectGUID(Temp);
				}
				else if (TIsVSType<T>::Value)
				{
					MObject* Key = (MObject*)&Io;
					MObject* Value = NULL;
					ReadObjectGUID(Value);
					m_pmVSTypeLoadMap.AddElement(Key, Value);
				}
				else if (TIsVSSmartPointerType<T>::Value)
				{
					MObjectPtr& Temp = *(MObjectPtr*)(void*)&Io;
					ReadObjectGUID(Temp);
				}
				else if (TIsVSStringType<T>::Value)
				{
					Container::MString& Temp = *(Container::MString*)(void*)&Io;
					ReadString(Temp);
				}
				else if (TIsCustomType<T>::Value)
				{
					VSCustomArchiveObject* Temp = (VSCustomArchiveObject*)(void*)&Io;
					if (Temp)
					{
						Temp->Archive(*this);
					}
				}
				else
				{
					Read((void*)&Io, sizeof(T));
				}
			}
			else if (m_uiStreamFlag == AT_SAVE)
			{
				if (TIsVSResourceProxyPointerType<T>::Value)
				{
					VSResourceProxyBasePtr& Temp = *(VSResourceProxyBasePtr*)(void*)&Io;
					WriteResource(Temp);
				}
				else if (TIsVSPointerType<T>::Value)
				{
					MObject*& Temp = *(MObject**)(void*)&Io;
					WriteObjectGUID(Temp);
				}
				else if (TIsVSSmartPointerType<T>::Value)
				{
					MObjectPtr& Temp = *(MObjectPtr*)(void*)&Io;
					WriteObjectGUID(Temp);
				}
				else if (TIsVSStringType<T>::Value)
				{
					Container::MString& Temp = *(Container::MString*)(void*)&Io;
					WriteString(Temp);
				}
				else if (TIsCustomType<T>::Value)
				{
					VSCustomArchiveObject* Temp = (VSCustomArchiveObject*)(void*)&Io;
					if (Temp)
					{
						Temp->Archive(*this);
					}
				}
				else if (TIsVSType<T>::Value)
				{
					MObject* Temp = (MObject*)&Io;
					WriteObjectGUID(Temp);
				}
				else
				{
					Write((void*)&Io, sizeof(T));
				}
			}
			else if (m_uiStreamFlag == AT_REGISTER || m_uiStreamFlag == AT_POSTLOAD)
			{
				if (TIsVSPointerType<T>::Value)
				{
					MObject*& Temp = *(MObject**)(void*)&Io;
					ArchiveAll(Temp);
				}
				else if (TIsVSSmartPointerType<T>::Value)
				{
					MObjectPtr& Temp = *(MObjectPtr*)(void*)&Io;
					ArchiveAll(Temp);
				}
				else if (TIsCustomType<T>::Value)
				{
					VSCustomArchiveObject* Temp = (VSCustomArchiveObject*)(void*)&Io;
					if (Temp)
					{
						Temp->Archive(*this);
					}
				}
				else if (TIsVSType<T>::Value)
				{
					MObject* Temp = (MObject*)&Io;
					ArchiveAll(Temp);
				}
			}
			else if (m_uiStreamFlag == AT_SIZE)
			{
				if (TIsVSResourceProxyPointerType<T>::Value)
				{
					VSResourceProxyBasePtr& Temp = *(VSResourceProxyBasePtr*)(void*)&Io;
					m_uiArchivePropertySize += SizeOfResource(Temp);
				}
				else if (TIsVSPointerType<T>::Value || TIsVSSmartPointerType<T>::Value || TIsVSType<T>::Value)
				{
					m_uiArchivePropertySize += 4;
				}
				else if (TIsVSStringType<T>::Value)
				{
					Container::MString& Temp = *(Container::MString*)(void*)&Io;
					m_uiArchivePropertySize += GetStrDistUse(Temp);
				}
				else if (TIsCustomType<T>::Value)
				{
					VSCustomArchiveObject* Temp = (VSCustomArchiveObject*)(void*)&Io;
					if (Temp)
					{
						Temp->Archive(*this);
					}
				}
				else
				{
					m_uiArchivePropertySize += sizeof(T);
				}
			}
			else if (m_uiStreamFlag == AT_OBJECT_COLLECT_GC || m_uiStreamFlag == AT_LOAD_OBJECT_COLLECT_GC)
			{
				if (TIsVSPointerType<T>::Value)
				{
					MObject*& Temp = *(MObject**)(void*)&Io;

					if (Temp)
					{
						if (Temp->IsHasFlag(MObject::OF_PendingKill))
						{
							Temp = NULL;
							return;
						}
						ArchiveAll(Temp);
					}
				}
				else if (TIsVSSmartPointerType<T>::Value)
				{
					MObjectPtr& Temp = *(MObjectPtr*)(void*)&Io;
					if (Temp)
					{
						if (Temp->IsHasFlag(MObject::OF_PendingKill))
						{
							Temp = NULL;
							return;
						}
						ArchiveAll(Temp);
					}
				}
				else if (TIsCustomType<T>::Value)
				{
					VSCustomArchiveObject* Temp = (VSCustomArchiveObject*)(void*)&Io;
					if (Temp)
					{
						Temp->Archive(*this);
					}
				}
				else if (TIsVSType<T>::Value)
				{
					MObject* Temp = (MObject*)&Io;
					ArchiveAll(Temp);
				}
			}
			else if (m_uiStreamFlag == AT_CLEAR_OBJECT_PROPERTY_GC)
			{
				if (TIsVSPointerType<T>::Value)
				{
					MObject*& Temp = *(MObject**)(void*)&Io;
					Temp = NULL;
				}
				else if (TIsVSSmartPointerType<T>::Value)
				{
					MObjectPtr& Temp = *(MObjectPtr*)(void*)&Io;
					MObject* LocalTemp = Temp;
					Temp = NULL;
					if (LocalTemp)
					{
						if (LocalTemp->IsHasFlag(MObject::OF_REACH))
						{
							LocalTemp->ClearFlag(MObject::OF_PendingKill);
						}
					}
				}
				else if (TIsCustomType<T>::Value)
				{
					VSCustomArchiveObject* Temp = (VSCustomArchiveObject*)(void*)&Io;
					if (Temp)
					{
						Temp->Archive(*this);
					}
				}
				else if (TIsVSType<T>::Value)
				{
					MObject* Temp = (MObject*)&Io;
					ArchiveAll(Temp);
				}
			}
			else if (m_uiStreamFlag == AT_LINK)
			{
				if (TIsVSPointerType<T>::Value)
				{
					MObject*& Temp = *(MObject**)(void*)&Io;
					LinkObjectPtr(Temp);
				}
				else if (TIsVSSmartPointerType<T>::Value)
				{
					MObjectPtr& Temp = *(MObjectPtr*)(void*)&Io;
					LinkObjectPtr(Temp);
				}
				else if (TIsVSType<T>::Value)
				{
					MObject* Key = (MObject*)&Io;
					MObject* Value = NULL;
					Value = GetVSTypeMapValue(Key);
					LinkObjectPtr(Value);
					MATRIX_ENGINE_ASSERT(Value);
					MObject::CloneObject(Value, Key);
					//unsigned int uiIndex = m_pObjectArray.FindElement(Value);
					//MATRIX_ENGINE_ASSERT(uiIndex < m_CopyUsed.GetNum());
					//m_CopyUsed[uiIndex] = true;
				}
				else if (TIsCustomType<T>::Value)
				{
					VSCustomArchiveObject* Temp = (VSCustomArchiveObject*)(void*)&Io;
					if (Temp)
					{
						Temp->Archive(*this);
					}
				}
			}
		}
		template <class T, class VSMemManagerClass>
		void Archive(Container::MArray<T, VSMemManagerClass>& Io)
		{
			if (m_uiStreamFlag == AT_LOAD)
			{
				unsigned int uiNum = 0;
				Archive(uiNum);
				Io.SetBufferNum(uiNum);
				if (TIsNoNeedLoop<T>::Value && uiNum)
				{
					Read(Io.GetBuffer(), sizeof(T) * uiNum);
				}
				else
				{
					for (unsigned int i = 0; i < uiNum; i++)
					{
						Archive(Io[i]);
					}
				}
			}
			else if (m_uiStreamFlag == AT_SAVE)
			{
				unsigned int uiNum = Io.GetNum();
				Archive(uiNum);
				if (TIsNoNeedLoop<T>::Value && uiNum)
				{
					Write(Io.GetBuffer(), sizeof(T) * uiNum);
				}
				else
				{
					for (unsigned int i = 0; i < uiNum; i++)
					{
						Archive(Io[i]);
					}
				}
			}
			else if (m_uiStreamFlag == AT_REGISTER || m_uiStreamFlag == AT_LINK || m_uiStreamFlag == AT_POSTLOAD || m_uiStreamFlag == AT_OBJECT_COLLECT_GC || m_uiStreamFlag == AT_LOAD_OBJECT_COLLECT_GC || m_uiStreamFlag == AT_CLEAR_OBJECT_PROPERTY_GC)
			{
				if (!TIsNeedGC<T>::Value)
				{
					return;
				}
				unsigned int uiNum = Io.GetNum();
				for (unsigned int i = 0; i < uiNum; i++)
				{
					Archive(Io[i]);
				}
			}
			else if (m_uiStreamFlag == AT_SIZE)
			{
				unsigned int uiNum = Io.GetNum();
				Archive(uiNum);
				if (TIsNoNeedLoop<T>::Value && uiNum)
				{
					m_uiArchivePropertySize += sizeof(T) * uiNum;
				}
				else
				{
					for (unsigned int i = 0; i < uiNum; i++)
					{
						Archive(Io[i]);
					}
				}
			}
		}

		template <class T, class VSMemManagerClass>
		void Archive(Container::MArrayOrder<T, VSMemManagerClass>& Io)
		{
			if (m_uiStreamFlag == AT_LOAD)
			{
				unsigned int uiNum = 0;
				Archive(uiNum);
				Io.SetBufferNum(uiNum);
				if (TIsNoNeedLoop<T>::Value && uiNum)
				{
					Read(Io.GetBuffer(), sizeof(T) * uiNum);
				}
				else
				{
					for (unsigned int i = 0; i < uiNum; i++)
					{
						Archive(Io[i]);
					}
				}
			}
			else if (m_uiStreamFlag == AT_SAVE)
			{
				unsigned int uiNum = Io.GetNum();
				Archive(uiNum);
				if (TIsNoNeedLoop<T>::Value && uiNum)
				{
					Write(Io.GetBuffer(), sizeof(T) * uiNum);
				}
				else
				{
					for (unsigned int i = 0; i < uiNum; i++)
					{
						Archive(Io[i]);
					}
				}
			}
			else if (m_uiStreamFlag == AT_REGISTER || m_uiStreamFlag == AT_LINK || m_uiStreamFlag == AT_POSTLOAD || m_uiStreamFlag == AT_OBJECT_COLLECT_GC || m_uiStreamFlag == AT_LOAD_OBJECT_COLLECT_GC || m_uiStreamFlag == AT_CLEAR_OBJECT_PROPERTY_GC)
			{
				if (!TIsNeedGC<T>::Value)
				{
					return;
				}
				unsigned int uiNum = Io.GetNum();
				for (unsigned int i = 0; i < uiNum; i++)
				{
					Archive(Io[i]);
				}
			}
			else if (m_uiStreamFlag == AT_SIZE)
			{
				unsigned int uiNum = Io.GetNum();
				Archive(uiNum);
				if (TIsNoNeedLoop<T>::Value && uiNum)
				{
					m_uiArchivePropertySize += sizeof(T) * uiNum;
				}
				else
				{
					for (unsigned int i = 0; i < uiNum; i++)
					{
						Archive(Io[i]);
					}
				}
			}
		}

		template <class Key, class Value, class VSMemManagerClass>
		void Archive(Container::MMap<Key, Value, VSMemManagerClass>& Io)
		{
			if (m_uiStreamFlag == AT_LOAD)
			{
				unsigned int uiNum = 0;
				Archive(uiNum);
				Io.SetBufferNum(uiNum);
				if (TIsNoNeedLoop<Key>::Value && TIsNoNeedLoop<Value>::Value && uiNum)
				{
					Read(Io.GetBuffer(), sizeof(Container::MapElement<Key, Value>) * uiNum);
				}
				else
				{
					for (unsigned int i = 0; i < uiNum; i++)
					{
						Container::MapElement<Key, Value>& Element = Io[i];
						Archive(Element.Key);
						Archive(Element.Value);
					}
				}
			}
			else if (m_uiStreamFlag == AT_SAVE)
			{
				unsigned int uiNum = Io.GetNum();
				Archive(uiNum);
				if (TIsNoNeedLoop<Key>::Value && TIsNoNeedLoop<Value>::Value && uiNum)
				{
					Write(Io.GetBuffer(), sizeof(Container::MapElement<Key, Value>) * uiNum);
				}
				else
				{
					for (unsigned int i = 0; i < uiNum; i++)
					{
						Container::MapElement<Key, Value>& Element = Io[i];
						Archive(Element.Key);
						Archive(Element.Value);
					}
				}
			}
			else if (m_uiStreamFlag == AT_REGISTER || m_uiStreamFlag == AT_LINK || m_uiStreamFlag == AT_POSTLOAD || m_uiStreamFlag == AT_OBJECT_COLLECT_GC || m_uiStreamFlag == AT_LOAD_OBJECT_COLLECT_GC || m_uiStreamFlag == AT_CLEAR_OBJECT_PROPERTY_GC)
			{
				if (!(TIsNeedGC<Key>::Value || TIsNeedGC<Value>::Value))
				{
					return;
				}
				unsigned int uiNum = Io.GetNum();
				for (unsigned int i = 0; i < uiNum; i++)
				{
					Container::MapElement<Key, Value>& Element = Io[i];
					if (TIsNeedGC<Key>::Value)
					{
						Archive(Element.Key);
					}
					if (TIsNeedGC<Value>::Value)
					{
						Archive(Element.Value);
					}
				}
			}
			else if (m_uiStreamFlag == AT_SIZE)
			{
				unsigned int uiNum = Io.GetNum();
				Archive(uiNum);
				if (TIsNoNeedLoop<Key>::Value && TIsNoNeedLoop<Value>::Value && uiNum)
				{
					m_uiArchivePropertySize += sizeof(Container::MapElement<Key, Value>) * uiNum;
				}
				else
				{
					for (unsigned int i = 0; i < uiNum; i++)
					{
						Container::MapElement<Key, Value>& Element = Io[i];
						Archive(Element.Key);
						Archive(Element.Value);
					}
				}
			}
		}

		template <class Key, class Value, class VSMemManagerClass>
		void Archive(Container::MMapOrder<Key, Value, VSMemManagerClass>& Io)
		{
			if (m_uiStreamFlag == AT_LOAD)
			{
				unsigned int uiNum = 0;
				Archive(uiNum);
				Io.SetBufferNum(uiNum);
				if (TIsNoNeedLoop<Key>::Value && TIsNoNeedLoop<Value>::Value && uiNum)
				{
					Read(Io.GetBuffer(), sizeof(Container::MapElement<Key, Value>) * uiNum);
				}
				else
				{
					for (unsigned int i = 0; i < uiNum; i++)
					{
						Container::MapElement<Key, Value>& Element = Io[i];
						Archive(Element.Key);
						Archive(Element.Value);
					}
				}
			}
			else if (m_uiStreamFlag == AT_SAVE)
			{
				unsigned int uiNum = Io.GetNum();
				Archive(uiNum);
				if (TIsNoNeedLoop<Key>::Value && TIsNoNeedLoop<Value>::Value && uiNum)
				{
					Write(Io.GetBuffer(), sizeof(Container::MapElement<Key, Value>) * uiNum);
				}
				else
				{
					for (unsigned int i = 0; i < uiNum; i++)
					{
						Container::MapElement<Key, Value>& Element = Io[i];
						Archive(Element.Key);
						Archive(Element.Value);
					}
				}
			}
			else if (m_uiStreamFlag == AT_REGISTER || m_uiStreamFlag == AT_LINK || m_uiStreamFlag == AT_POSTLOAD || m_uiStreamFlag == AT_OBJECT_COLLECT_GC || m_uiStreamFlag == AT_LOAD_OBJECT_COLLECT_GC || m_uiStreamFlag == AT_CLEAR_OBJECT_PROPERTY_GC)
			{
				if (!(TIsNeedGC<Key>::Value || TIsNeedGC<Value>::Value))
				{
					return;
				}
				unsigned int uiNum = Io.GetNum();
				for (unsigned int i = 0; i < uiNum; i++)
				{
					Container::MapElement<Key, Value>& Element = Io[i];
					if (TIsNeedGC<Key>::Value)
					{
						Archive(Element.Key);
					}
					if (TIsNeedGC<Value>::Value)
					{
						Archive(Element.Value);
					}
				}
			}
			else if (m_uiStreamFlag == AT_SIZE)
			{
				unsigned int uiNum = Io.GetNum();
				Archive(uiNum);
				if (TIsNoNeedLoop<Key>::Value && TIsNoNeedLoop<Value>::Value && uiNum)
				{
					m_uiArchivePropertySize += sizeof(Container::MapElement<Key, Value>) * uiNum;
				}
				else
				{
					for (unsigned int i = 0; i < uiNum; i++)
					{
						Container::MapElement<Key, Value>& Element = Io[i];
						Archive(Element.Key);
						Archive(Element.Value);
					}
				}
			}
		}
		bool WriteResource(VSResourceProxyBasePtr& Resource);

		virtual bool ReadResource(VSResourceProxyBasePtr& Resource);

		unsigned int SizeOfResource(VSResourceProxyBasePtr& Resource);
		unsigned int GetStreamFlag() const
		{
			return m_uiStreamFlag;
		}
		void SetStreamFlag(unsigned int uiStreamFlag)
		{
			m_uiStreamFlag = uiStreamFlag;
		}
		void AddBufferSize(unsigned int uiSize)
		{
			m_uiArchivePropertySize += uiSize;
		}

		struct ObjectPropertyTable
		{
			ObjectPropertyTable()
			{
				m_uiOffset = 0;
				m_uiSize = 0;
				m_uiNameID = 0;
			}
			Container::MString m_PropertyName; //当前 MObject 属性名字
			unsigned int m_uiOffset; //当前 MObject 属性距离首地址的偏移量
			unsigned int m_uiSize; //当前 MObject 属性大小
			unsigned int m_uiNameID; //当前 MObject 属性名字的 ID
		};

		struct ObjectTableType
		{
			ObjectTableType()
			{
				m_uiGUID = 0;
				m_uiOffset = 0;
				m_uiObjectPropertySize = 0;
				m_uiObjectPropertyTableSize = 0;
				m_uiObjectPropertyNum = 0;
			}
			unsigned int m_uiGUID; // 以 MObject 的地址作为唯一标识，恢复加载时指针的指向
			Container::MString m_RttiName; //MObject Rtti 的名字，加载的时候才知道创建的是什么对象
			unsigned int m_uiOffset; //ObjectPropertyTable距离首地址偏移
			unsigned int m_uiObjectPropertySize; //MObject 所有属性占用的空间大小
			unsigned int m_uiObjectPropertyNum;  //MObject 属性的个数
			unsigned int m_uiObjectPropertyTableSize; //ObjectPropertyTable 占用空间大小
			Container::MArray<ObjectPropertyTable> m_ObjectPropertyTable; //MObject 属性表数组
		};
		bool m_bLoadUseGC;

	protected:
		unsigned int m_uiStreamFlag;
		unsigned int m_uiArchivePropertySize;

	public:
		virtual bool Load(const TCHAR* const pcFileName);
		virtual bool Save(const TCHAR* const pcFileName);

		virtual bool LoadFromBuffer(unsigned char* pBuffer, unsigned int uiSize);

		//首先是要判断这个 MObject 对象有没有注册过。如果没有注册，则加入 m_pObjectArray 中；否则，这个递归处理就结束。接下来，遍历所有的属性
		bool ArchiveAll(MObject* pObject);

	public:
		//如果没有注册进去，就放入m_pObjectArray中
		bool RegisterObject(MObject* pObject);

		bool RegisterPostLoadObject(MObject* pObject);

		bool RegisterReachableObject(MObject* pObject);

		MStream(DWORD dwFlag = 0);
		~MStream();
		//此read 和 write 并非实际写入，都是操作内存，并非操作文件 
		bool Read(void* pvBuffer, unsigned int uiSize);
		bool Write(const void* pvBuffer, unsigned int uiSize);
		bool ReadString(Container::MString& str);
		bool WriteString(const Container::MString& str);

		static unsigned int GetStrDistUse(const Container::MString& Str);
		static unsigned int GetStrDistUse(const TCHAR* pCh);
		const MObject* GetLoadMapValue(unsigned int uiKey) const;
		unsigned int GetSaveMapValue(MObject* Key) const;
		MObject* GetVSTypeMapValue(MObject* pKey) const;
		virtual const MObject* GetObjectByRtti(const VSRtti& Rtti);
		bool GetObjectArrayByRtti(const VSRtti& Rtti, Container::MArray<MObject*>& ObjectArray, bool IsDerivedFrom = false);
		bool GetAllResourceObject(Container::MArray<MObject*>& ObjectArray);
		void GetObjectFailed();
		inline unsigned int GetVersion() const
		{
			return m_uiVersion;
		}

		static unsigned int GetCurVersion()
		{
			return ms_uiCurVersion;
		}

		inline bool HasAnyFlag(DWORD dwFlagsToCheck) const
		{
			return (m_dwFlag & dwFlagsToCheck) != 0;
		}
		template <class T>
		bool ReadObjectGUID(VSPointer<T>& Pointer);

		template <class T>
		bool WriteObjectGUID(const VSPointer<T>& Pointer);

		template <class T>
		bool LinkObjectPtr(VSPointer<T>& Pointer);

		template <class T>
		bool ReadObjectGUID(T*& pObject);

		template <class T>
		bool WriteObjectGUID(T* const& pObject);

		template <class T>
		bool LinkObjectPtr(T*& pObject);

	protected:
		unsigned char* m_pcCurBufPtr; //初始为m_pcBuffer， 随着write()写入逐渐递增。
		unsigned char* m_pcBuffer; //m_pcBuffer 是缓存的首地址， 是当前空闲空间的地址，在执行save()时候申请的空间，申请的内存大小为m_uiBufferSize。
		unsigned int m_uiBufferSize; //
		Container::MArray<MObject*> m_pObjectArray;
		Container::MArray<MObject*> m_pPostLoadObject;

		Container::MMap<unsigned int, MObject*> m_pmLoadMap;
		Container::MMap<MObject*, unsigned int> m_pmSaveMap;     //GUID 与 相关object的映射
		Container::MMap<MObject*, MObject*> m_pmVSTypeLoadMap;

		static unsigned int ms_uiCurVersion;
		unsigned int m_uiVersion;
		DWORD m_dwFlag;
	};

	template <class T>
	bool MStream::ReadObjectGUID(VSPointer<T>& Pointer)
	{
		unsigned int uiGUID = 0;
		if (!Read(&uiGUID, sizeof(unsigned int)))
			return 0;
		USIZE_TYPE Temp = Core::GUID32ToSizeType(uiGUID);
		Pointer.SetObject((T*)(Temp));
		return 1;
	}
	/********************************************************************************/
	template <class T>
	bool MStream::WriteObjectGUID(const VSPointer<T>& Pointer)
	{
		T* pP = Pointer;
		unsigned int uiGUID = GetSaveMapValue(pP);
		if (!Write(&uiGUID, sizeof(unsigned int)))
			return 0;
		return 1;
	}
	/********************************************************************************/
	template <class T>
	bool MStream::LinkObjectPtr(VSPointer<T>& Pointer)
	{
		unsigned int uiGUID = Core::SizeTypeToGUID32((USIZE_TYPE)Pointer.GetObject());

		Pointer.SetObject(NULL);

		Pointer = (T*)GetLoadMapValue(uiGUID);
		return 1;
	}
	/********************************************************************************/
	template <class T>
	bool MStream::ReadObjectGUID(T*& pObject)
	{
		unsigned int uiGUID = 0;
		if (!Read(&uiGUID, sizeof(unsigned int)))
			return 0;
		USIZE_TYPE Temp = Core::GUID32ToSizeType(uiGUID);
		pObject = (T*)(Temp);
		return 1;
	}
	/********************************************************************************/
	template <class T>
	bool MStream::WriteObjectGUID(T* const& pObject)
	{
		unsigned int uiGUID = GetSaveMapValue(pObject);
		if (!Write(&uiGUID, sizeof(unsigned int)))
			return 0;
		return 1;
	}
	/********************************************************************************/
	template <class T>
	bool MStream::LinkObjectPtr(T*& pObject)
	{
		unsigned int uiGUID = Core::SizeTypeToGUID32((USIZE_TYPE)pObject);
		pObject = (T*)GetLoadMapValue(uiGUID);
		return 1;
	}
}
