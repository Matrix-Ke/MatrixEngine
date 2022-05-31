#include "Stream.h"
#include "Property.h"
#include "Object.h"
//#include "GraphicInclude.h"
#include "ResourceManager.h"
#include "Config.h"

using namespace Matrix;
unsigned int MStream::ms_uiCurVersion = 0;
/********************************************************************************/
unsigned int MStream::GetStrDistUse(const Container::MString& Str)
{
	return sizeof(int) + (unsigned int)Str.GetLength() * sizeof(TCHAR);
}
/********************************************************************************/
unsigned int MStream::GetStrDistUse(const TCHAR* pCh)
{
	return sizeof(int) + (unsigned int)Core::MXStrLen(pCh) * sizeof(TCHAR);
}
/********************************************************************************/
MStream::MStream(DWORD dwFlag)
{
	m_pObjectArray.Clear();
	m_pmLoadMap.Clear();
	m_pmVSTypeLoadMap.Clear();
	m_pcCurBufPtr = NULL;
	m_pcBuffer = NULL;
	m_uiBufferSize = 0;
	m_dwFlag = dwFlag;
	m_bLoadUseGC = false;
}
/********************************************************************************/
MStream::~MStream()
{

	m_pObjectArray.Clear();
	m_pcCurBufPtr = NULL;
}
/********************************************************************************/
bool MStream::Read(void* pvBuffer, unsigned int uiSize)
{

	if (!pvBuffer || !m_pcBuffer)
		return 0;

	if (unsigned int(m_pcCurBufPtr + uiSize - m_pcBuffer) > m_uiBufferSize)
		return 0;

	Core::MXMemcpy(pvBuffer, m_pcCurBufPtr, uiSize);

	m_pcCurBufPtr += uiSize;
	return 1;
}
/********************************************************************************/
bool MStream::Write(const void* pvBuffer, unsigned int uiSize)
{
	if (!pvBuffer || !m_pcBuffer)
		return 0;

	if (unsigned int(m_pcCurBufPtr + uiSize - m_pcBuffer) > m_uiBufferSize)
		return 0;

	Core::MXMemcpy(m_pcCurBufPtr, pvBuffer, uiSize);

	m_pcCurBufPtr += uiSize;
	return 1;
}
/********************************************************************************/
bool MStream::ReadString(Container::MString& String)
{
	unsigned int uiBufferSize = 0;
	unsigned int uiStrLen = 0;
	//在stirng存储中先是存储长度，所以解析的时候先解析出size
	if (!Read(&uiBufferSize, sizeof(unsigned int)))
		return 0;

	if (!uiBufferSize)
	{
		return 1;
	}
	char* pCh = 0;
	pCh = MX_NEW char[uiBufferSize];
	if (!Read(pCh, uiBufferSize))
	{
		ENGINE_DELETEA(pCh);
		return 0;
	}
	if (HasAnyFlag(UNICODE_FLAG))
	{
		uiStrLen = uiBufferSize >> 1;
		String.SetTCHARBufferNum(uiStrLen);
#ifdef _UNICODE
		Core::MXMemcpy(String.GetBuffer(), pCh, uiBufferSize);
#else
		Core::MXWcsToMbs(String.GetBuffer(), uiStrLen, (wchar_t*)pCh, uiStrLen);
#endif
	}
	else
	{
		uiStrLen = uiBufferSize;
		String.SetTCHARBufferNum(uiStrLen);
#ifdef _UNICODE
		Core::MXMbsToWcs((wchar_t*)String.GetBuffer(), uiStrLen, pCh, uiStrLen);
#else
		Core::MXMemcpy(String.GetBuffer(), pCh, uiBufferSize);
#endif
	}
	ENGINE_DELETEA(pCh);

	return 1;
}
/********************************************************************************/
bool MStream::WriteString(const Container::MString& String)
{
	unsigned int uiBufferLen = String.GetLength() * sizeof(TCHAR);
	if (!Write(&uiBufferLen, sizeof(unsigned int)))
		return 0;
	if (!Write(String.GetBuffer(), uiBufferLen))
		return 0;
	return 1;
}
bool MStream::RegisterReachableObject(MObject* pObject)
{
	if (pObject->IsHasFlag(MObject::OF_REACH))
	{
		return false;
	}
	pObject->SetFlag(MObject::OF_REACH);
	pObject->ClearFlag(MObject::OF_UNREACH);

	return 1;
}
bool MStream::RegisterPostLoadObject(MObject* pObject)
{
	for (unsigned int i = 0; i < (unsigned int)m_pPostLoadObject.GetNum(); i++)
	{
		if (m_pPostLoadObject[i] == pObject)
		{
			return 0;
		}
	}
	m_pPostLoadObject.AddElement((MObject*)pObject);
	return true;
}

/********************************************************************************/
bool MStream::RegisterObject(MObject* pObject)
{
	MATRIX_ENGINE_ASSERT(pObject);
	if (!pObject)
		return 0;

	for (unsigned int i = 0; i < (unsigned int)m_pObjectArray.GetNum(); i++)
	{
		if (m_pObjectArray[i] == pObject)
		{
			return 0;
		}
	}
	m_pObjectArray.AddElement((MObject*)pObject);

	return 1;
}
/********************************************************************************/
MObject* MStream::GetVSTypeMapValue(MObject* pKey) const
{
	unsigned int i = m_pmVSTypeLoadMap.Find(pKey);
	if (i == m_pmVSTypeLoadMap.GetNum())
		return NULL;

	return m_pmVSTypeLoadMap[i].Value;
}
/********************************************************************************/
const MObject* MStream::GetLoadMapValue(unsigned int uiKey) const
{
	unsigned int i = m_pmLoadMap.Find(uiKey);
	if (i == m_pmLoadMap.GetNum())
		return NULL;

	return m_pmLoadMap[i].Value;
}
unsigned int MStream::GetSaveMapValue(MObject* Key) const
{
	unsigned int i = m_pmSaveMap.Find(Key);
	if (i == m_pmSaveMap.GetNum())
		return 0;

	return m_pmSaveMap[i].Value;
}
/********************************************************************************/
const MObject* MStream::GetObjectByRtti(const VSRtti& Rtti)
{
	MObject* pObject = NULL;
	for (unsigned int i = 0; i < m_pObjectArray.GetNum(); i++)
	{
		if ((m_pObjectArray[i]->GetType()).IsSameType(Rtti))
		{
			pObject = m_pObjectArray[i];
			break;
		}
	}
	if (pObject == NULL)
	{
		for (unsigned int i = 0; i < m_pObjectArray.GetNum(); i++)
		{
			if ((m_pObjectArray[i]->GetType()).IsDerived(Rtti))
			{

				pObject = m_pObjectArray[i];
				break;
			}
		}
	}
	for (unsigned int i = 0; i < m_pObjectArray.GetNum(); i++)
	{
		MObject* p = m_pObjectArray[i];
		MATRIX_ENGINE_ASSERT(p != NULL);
		if (p)
		{
			p->ClearFlag(MObject::OF_REACH);
			p->SetFlag(MObject::OF_UNREACH);
		}
	}
	if (pObject)
	{
		MStream GCCollectStream;
		GCCollectStream.SetStreamFlag(MStream::AT_LOAD_OBJECT_COLLECT_GC);
		GCCollectStream.ArchiveAll(pObject);

		Container::MArray<MObject*> CanGCObject;
		for (unsigned int i = 0; i < m_pObjectArray.GetNum();)
		{
			MObject* p = m_pObjectArray[i];
			if (p->IsHasFlag(MObject::OF_UNREACH))
			{
				CanGCObject.AddElement(p);
				m_pObjectArray.Erase(i);
			}
			else
			{
				i++;
			}
		}
		//todo  GC
		//VSResourceManager::AddCanGCObject(CanGCObject);
	}
	else
	{
		GetObjectFailed();
	}
	if (pObject)
	{
		m_uiStreamFlag = AT_POSTLOAD;
		ArchiveAll(pObject);
	}
	return pObject;
}
void MStream::GetObjectFailed()
{
	if (m_pObjectArray.GetNum())
	{
		//todo  GC
		//VSResourceManager::AddCanGCObject(m_pObjectArray);
		m_pObjectArray.Clear();
	}
}
bool MStream::GetAllResourceObject(Container::MArray<MObject*>& ObjectArray)
{
	ObjectArray.Clear();
	for (unsigned int i = 0; i < m_pObjectArray.GetNum(); i++)
	{
		if (VSResourceControl::IsResourceType(m_pObjectArray[i]->GetType()))
		{

			ObjectArray.AddElement(m_pObjectArray[i]);
		}
	}
	if (ObjectArray.GetNum() > 0)
	{
		for (unsigned int i = 0; i < m_pObjectArray.GetNum(); i++)
		{
			MObject* p = m_pObjectArray[i];
			MATRIX_ENGINE_ASSERT(p != NULL);
			if (p)
			{
				p->ClearFlag(MObject::OF_REACH);
				p->SetFlag(MObject::OF_UNREACH);
			}
		}

		MStream GCCollectStream;
		GCCollectStream.SetStreamFlag(MStream::AT_LOAD_OBJECT_COLLECT_GC);
		for (unsigned int i = 0; i < ObjectArray.GetNum(); i++)
		{
			GCCollectStream.ArchiveAll(ObjectArray[i]);
		}

		Container::MArray<MObject*> CanGCObject;
		for (unsigned int i = 0; i < m_pObjectArray.GetNum();)
		{
			MObject* p = m_pObjectArray[i];
			if (p->IsHasFlag(MObject::OF_UNREACH))
			{
				CanGCObject.AddElement(p);
				m_pObjectArray.Erase(i);
			}
			else
			{
				i++;
			}
		}
		//todo  GC
		//VSResourceManager::AddCanGCObject(CanGCObject);
		m_uiStreamFlag = AT_POSTLOAD;
		for (unsigned int i = 0; i < ObjectArray.GetNum(); i++)
		{
			ArchiveAll(ObjectArray[i]);
		}
		return 1;
	}
	else
	{
		GetObjectFailed();
		return 0;
	}
}
/********************************************************************************/
bool MStream::GetObjectArrayByRtti(const VSRtti& Rtti, Container::MArray<MObject*>& ObjectArray, bool IsDerivedFrom)
{
	ObjectArray.Clear();
	for (unsigned int i = 0; i < m_pObjectArray.GetNum(); i++)
	{
		if ((m_pObjectArray[i]->GetType()).IsSameType(Rtti) || ((m_pObjectArray[i]->GetType()).IsDerived(Rtti) && IsDerivedFrom))
		{

			ObjectArray.AddElement(m_pObjectArray[i]);
		}
	}
	if (ObjectArray.GetNum() > 0)
	{
		for (unsigned int i = 0; i < m_pObjectArray.GetNum(); i++)
		{
			MObject* p = m_pObjectArray[i];
			MATRIX_ENGINE_ASSERT(p != NULL);
			if (p)
			{
				p->ClearFlag(MObject::OF_REACH);
				p->SetFlag(MObject::OF_UNREACH);
			}
		}

		MStream GCCollectStream;
		GCCollectStream.SetStreamFlag(MStream::AT_LOAD_OBJECT_COLLECT_GC);
		for (unsigned int i = 0; i < ObjectArray.GetNum(); i++)
		{
			GCCollectStream.ArchiveAll(ObjectArray[i]);
		}

		Container::MArray<MObject*> CanGCObject;
		for (unsigned int i = 0; i < m_pObjectArray.GetNum();)
		{
			MObject* p = m_pObjectArray[i];
			if (p->IsHasFlag(MObject::OF_UNREACH))
			{
				CanGCObject.AddElement(p);
				m_pObjectArray.Erase(i);
			}
			else
			{
				i++;
			}
		}
		//todo  GC
		//VSResourceManager::AddCanGCObject(CanGCObject);

		m_uiStreamFlag = AT_POSTLOAD;
		for (unsigned int i = 0; i < ObjectArray.GetNum(); i++)
		{
			ArchiveAll(ObjectArray[i]);
		}

		return 1;
	}
	else
	{
		GetObjectFailed();
		return 0;
	}
}
/*******************************************************************************

									new version

*******************************************************************************/
unsigned int MStream::SizeOfResource(VSResourceProxyBasePtr& Resource)
{
	unsigned int uiSize = 0;
	bool IsNone = true;
	if (Resource && !VSResourceControl::IsDefaultResource(Resource))
	{
		IsNone = false;
	}
	uiSize += sizeof(bool);
	if (!IsNone)
	{

		const Container::MString& FileName = Resource->GetResourceName().GetString();
		uiSize += GetStrDistUse(FileName);
	}

	return uiSize;
}
bool MStream::WriteResource(VSResourceProxyBasePtr& Resource)
{
	bool IsNone = true;
	if (Resource && !VSResourceControl::IsDefaultResource(Resource))
	{
		IsNone = false;
	}
	Write(&IsNone, sizeof(bool));
	if (!IsNone)
	{

		const Container::MString& FileName = Resource->GetResourceName().GetString();
		WriteString(FileName);
	}

	return true;
}

bool MStream::ReadResource(VSResourceProxyBasePtr& Resource)
{

	//todo ReadResource
	//bool IsNone = true;
	//Read(&IsNone, sizeof(bool));
	//if (IsNone == false)
	//{
	//	Container::MString Name;
	//	ReadString(Name);
	//	Resource = VSResourceManager::LoadResource(Name.GetBuffer(), HasAnyFlag(ASYN_LOAD_FLAG));
	//	if (!Resource)
	//	{
	//		MATRIX_ENGINE_ASSERT(0);
	//		return false;
	//	}
	//}

	return true;
}
bool MStream::ArchiveAll(MObject* pObject)
{
	if (!pObject)
	{
		return false;
	}

	if (m_uiStreamFlag == AT_REGISTER)
	{
		//如果没有注册将进行递归注册
		if (RegisterObject(pObject))
		{
			VSRtti& Rtti = pObject->GetType();
			for (unsigned int j = 0; j < Rtti.GetPropertyNum(); j++)
			{
				VSProperty* pProperty = Rtti.GetProperty(j);
				if (pProperty->GetFlag() & VSProperty::F_SAVE_LOAD)
				{
					pProperty->Archive(*this, pObject);
				}
			}
		}
	}
	else if (m_uiStreamFlag == AT_POSTLOAD)
	{
		if (RegisterPostLoadObject(pObject))
		{

			VSRtti& Rtti = pObject->GetType();
			for (unsigned int j = 0; j < Rtti.GetPropertyNum(); j++)
			{
				VSProperty* pProperty = Rtti.GetProperty(j);
				if (pProperty->GetFlag() & VSProperty::F_SAVE_LOAD)
				{
					pProperty->Archive(*this, pObject);
				}
			}
			pObject->PostLoad(this);
		}
	}
	else if (m_uiStreamFlag == AT_OBJECT_COLLECT_GC)
	{
		if (RegisterReachableObject(pObject))
		{
			VSRtti& Rtti = pObject->GetType();
			for (unsigned int j = 0; j < Rtti.GetPropertyNum(); j++)
			{
				VSProperty* pProperty = Rtti.GetProperty(j);
				if (!(pProperty->GetFlag() & VSProperty::F_NO_USE_GC))
				{
					pProperty->Archive(*this, pObject);
				}
			}
		}
	}
	else if (m_uiStreamFlag == AT_LOAD_OBJECT_COLLECT_GC)
	{
		if (RegisterReachableObject(pObject))
		{
			VSRtti& Rtti = pObject->GetType();
			for (unsigned int j = 0; j < Rtti.GetPropertyNum(); j++)
			{
				VSProperty* pProperty = Rtti.GetProperty(j);
				pProperty->Archive(*this, pObject);
			}
		}
	}
	else if (m_uiStreamFlag == AT_CLEAR_OBJECT_PROPERTY_GC)
	{
		VSRtti& Rtti = pObject->GetType();
		for (unsigned int j = 0; j < Rtti.GetPropertyNum(); j++)
		{
			VSProperty* pProperty = Rtti.GetProperty(j);
			if (!(pProperty->GetFlag() & VSProperty::F_NO_USE_GC))
			{
				pProperty->Archive(*this, pObject);
			}
		}
	}
	return true;
}
bool MStream::LoadFromBuffer(unsigned char* pBuffer, unsigned int uiSize)
{

	if (!pBuffer || !uiSize)
	{
		return false;
	}
	//加载之前必须清楚m_pObjectArray，因为后续利用objecTable生成object需要放入m_pObjectArray中。
	m_pObjectArray.Clear();
	m_pmLoadMap.Clear();
	m_pcCurBufPtr = NULL;
	m_uiBufferSize = 0;

	//都加载到内存中
	m_uiBufferSize = uiSize;
	m_pcBuffer = pBuffer;

	m_pcCurBufPtr = m_pcBuffer;

	Container::MArray<ObjectTableType> ObjectTable;
	//加载版本号
	Read(&m_uiVersion, sizeof(unsigned int));
	//加载物体个数
	unsigned int iObjectNum = 0;
	Read(&iObjectNum, sizeof(unsigned int));

	ObjectTable.SetBufferNum(iObjectNum);
	// Object Table
	for (unsigned int i = 0; i < iObjectNum; i++)
	{
		MObject* pObject = 0;
		//读取指针
		if (!Read(&ObjectTable[i].m_uiGUID, sizeof(unsigned int)))
		{
			return 0;
		}
		//读取RTTI
		if (!ReadString(ObjectTable[i].m_RttiName))
		{
			return 0;
		}
		//todo list
		VSConfig::GetClassReplace(ObjectTable[i].m_RttiName);

		if (!Read(&ObjectTable[i].m_uiObjectPropertySize, sizeof(unsigned int)))
		{
			return 0;
		}

		if (!Read(&ObjectTable[i].m_uiObjectPropertyNum, sizeof(unsigned int)))
		{
			return 0;
		}
	}

	// create object 并将object数量注册到 m_pObjectArray 中。
	for (unsigned int i = 0; i < iObjectNum; i++)
	{
		MObject* pObject = NULL;
		if (m_bLoadUseGC)
		{
			pObject = MObject::GetInstance(ObjectTable[i].m_RttiName);
		}
		else
		{
			pObject = MObject::GetNoGCInstance(ObjectTable[i].m_RttiName);
		}
		//创建空对象

		if (!pObject)
		{
			continue;
		}

		//创建加载映射表
		m_pmLoadMap.AddElement(ObjectTable[i].m_uiGUID, pObject);
		//将每个 MObject 对象注册到 m_pObjectArray 里面，
		RegisterObject(pObject);
	}

	// load object property table
	for (unsigned int i = 0; i < iObjectNum; i++)
	{
		ObjectTable[i].m_ObjectPropertyTable.SetBufferNum(ObjectTable[i].m_uiObjectPropertyNum);
		Container::MMapOrder<unsigned int, unsigned int>* pPropertyReplace = NULL;
		VSConfig::GetPropertyReplace(ObjectTable[i].m_RttiName, pPropertyReplace);
		for (unsigned int j = 0; j < ObjectTable[i].m_uiObjectPropertyNum; j++)
		{

			Read(&ObjectTable[i].m_ObjectPropertyTable[j].m_uiNameID, sizeof(unsigned int));
			if (pPropertyReplace)
			{
				VSConfig::GetPropertyReplace(pPropertyReplace, ObjectTable[i].m_ObjectPropertyTable[j].m_uiNameID);
			}
			Read(&ObjectTable[i].m_ObjectPropertyTable[j].m_uiOffset, sizeof(unsigned int));
		}
		m_pcCurBufPtr += ObjectTable[i].m_uiObjectPropertySize;
	}

	m_uiStreamFlag = AT_LOAD;
	// load object property
	//需要将object的RTTI中的Property信息与文件读取的序列化property信息进行匹配
	for (unsigned int i = 0; i < m_pObjectArray.GetNum(); i++)
	{
		VSRtti& Rtti = m_pObjectArray[i]->GetType();
		unsigned int uiTableID = i;
		for (unsigned int j = 0; j < Rtti.GetPropertyNum(); j++)
		{
			VSProperty* pProperty = Rtti.GetProperty(j);
			if (pProperty->GetFlag() & VSProperty::F_SAVE_LOAD)
			{
				for (unsigned int k = 0; k < ObjectTable[uiTableID].m_ObjectPropertyTable.GetNum(); k++)
				{
					if (pProperty->GetName().GetNameCode() == ObjectTable[uiTableID].m_ObjectPropertyTable[k].m_uiNameID)
					{
						m_pcCurBufPtr = m_pcBuffer + ObjectTable[uiTableID].m_ObjectPropertyTable[k].m_uiOffset;
						pProperty->Archive(*this, m_pObjectArray[i]);
						break;
					}
				}
			}
		}
	}

	//处理连接 处理指针指向和 MObject 对象中内容的复制。
	m_uiStreamFlag = AT_LINK;
	//必须从后往前遍历，因为register的过程是递归的深度注册，所以从后往前link保证子节点先完成，然后父亲节点完成。
	for (int i = m_pObjectArray.GetNum() - 1; i >= 0; i--)
	{
		VSRtti& Rtti = m_pObjectArray[i]->GetType();
		for (unsigned int j = 0; j < Rtti.GetPropertyNum(); j++)
		{
			VSProperty* pProperty = Rtti.GetProperty(j);
			if (pProperty->GetFlag() & VSProperty::F_SAVE_LOAD)
			{
				pProperty->Archive(*this, m_pObjectArray[i]);
			}
		}
	}
	m_pcBuffer = NULL;
	return 1;
}
bool MStream::Load(const TCHAR* const pcFileName)
{
	Core::File* pFile = MX_NEW Core::File();
	if (!pFile)
	{
		return 0;
	}

	//打开文件
	if (!pFile->Open(pcFileName, Core::File::OM_RB))
	{
		ENGINE_DELETE(pFile);
		return 0;
	}

	//都加载到内存中
	unsigned int uiBufferSize = pFile->GetFileSize();
	unsigned char* pBuffer = MX_NEW unsigned char[uiBufferSize];
	if (!pBuffer)
	{
		ENGINE_DELETE(pFile);
		return 0;
	}
	if (!pFile->Read(pBuffer, uiBufferSize, 1))
	{
		ENGINE_DELETE(pFile);
		return 0;
	}
	ENGINE_DELETE(pFile);

	if (!LoadFromBuffer(pBuffer, uiBufferSize))
	{
		ENGINE_DELETEA(pBuffer);
		return false;
	}
	ENGINE_DELETEA(pBuffer);

	return 1;
}
bool MStream::Save(const TCHAR* const pcFileName)
{
	unsigned int iObjectNum = m_pObjectArray.GetNum();
	m_uiBufferSize = 0;

	//版本号
	m_uiBufferSize += sizeof(unsigned int);
	//物体个数空间
	m_uiBufferSize += sizeof(unsigned int);

	Container::MArray<ObjectTableType> ObjectTable;
	ObjectTable.SetBufferNum(iObjectNum);
	m_pmSaveMap.Clear();
	// object table
	for (unsigned int i = 0; i < m_pObjectArray.GetNum(); i++)
	{
		//求取objectable结构数据长度
		// guid 
		m_uiBufferSize += sizeof(unsigned int);

		ObjectTable[i].m_uiGUID = i + 1;

		m_pmSaveMap.AddElement(m_pObjectArray[i], ObjectTable[i].m_uiGUID);

		// rtti name
		m_uiBufferSize += GetStrDistUse(m_pObjectArray[i]->GetType().GetName());

		ObjectTable[i].m_RttiName = m_pObjectArray[i]->GetType().GetName();

		// object property size
		m_uiBufferSize += sizeof(unsigned int);

		// object property num
		m_uiBufferSize += sizeof(unsigned int);
	}
	//objectContent过后就是存储propertytable内容
	unsigned int uiObjectContentAddr = m_uiBufferSize;

	//切换Flag
	m_uiStreamFlag = AT_SIZE;
	// object property size
	for (unsigned int i = 0; i < m_pObjectArray.GetNum(); i++)
	{
		ObjectTable[i].m_uiOffset = m_uiBufferSize;

		VSRtti& Rtti = m_pObjectArray[i]->GetType();
		ObjectTable[i].m_ObjectPropertyTable.SetBufferNum(Rtti.GetPropertyNum());

		ObjectTable[i].m_uiObjectPropertyNum = 0;

		for (unsigned int j = 0; j < Rtti.GetPropertyNum(); j++)
		{
			VSProperty* pProperty = Rtti.GetProperty(j);

			if (pProperty->GetFlag() & VSProperty::F_SAVE_LOAD)
			{
				//存放名字 ID 空间大小
				m_uiBufferSize += sizeof(unsigned int);
				//取得属性名字
				ObjectTable[i].m_ObjectPropertyTable[j].m_PropertyName = pProperty->GetName().GetString();
				ObjectTable[i].m_ObjectPropertyTable[j].m_uiNameID = pProperty->GetName().GetNameCode();
				//存放偏移量大小
				m_uiBufferSize += sizeof(unsigned int);
				//计算需要save的属性个数
				ObjectTable[i].m_uiObjectPropertyNum++;
			}
		}

		ObjectTable[i].m_uiObjectPropertyTableSize = m_uiBufferSize - ObjectTable[i].m_uiOffset;

		for (unsigned int j = 0; j < Rtti.GetPropertyNum(); j++)
		{
			VSProperty* pProperty = Rtti.GetProperty(j);

			if (pProperty->GetFlag() & VSProperty::F_SAVE_LOAD)
			{
				ObjectTable[i].m_ObjectPropertyTable[j].m_uiOffset = m_uiBufferSize;

				m_uiArchivePropertySize = 0;

				pProperty->Archive(*this, m_pObjectArray[i]);

				ObjectTable[i].m_ObjectPropertyTable[j].m_uiSize = m_uiArchivePropertySize;

				m_uiBufferSize += m_uiArchivePropertySize;
			}
		}

		ObjectTable[i].m_uiObjectPropertySize = m_uiBufferSize - ObjectTable[i].m_uiObjectPropertyTableSize - ObjectTable[i].m_uiOffset;
	}

	//预留执行breforeSave ，继承自 MObject 的类都可以重载这个函数
	for (unsigned int i = 0; i < m_pObjectArray.GetNum(); i++)
	{
		m_pObjectArray[i]->BeforeSave(this);
	}

	ENGINE_DELETEA(m_pcBuffer);

	//申请空间
	m_pcBuffer = MX_NEW unsigned char[m_uiBufferSize];
	if (!m_pcBuffer)
	{
		return 0;
	}
	m_pcCurBufPtr = m_pcBuffer;

	m_uiVersion = ms_uiCurVersion;
	//存储版本号
	Write(&m_uiVersion, sizeof(unsigned int));

	//存储物体个数
	Write(&iObjectNum, sizeof(unsigned int));

	// OBJECT TABLE
	for (unsigned int i = 0; i < m_pObjectArray.GetNum(); i++)
	{
		// addr
		if (!Write(&ObjectTable[i].m_uiGUID, sizeof(unsigned int)))
		{
			ENGINE_DELETEA(m_pcBuffer);
			return 0;
		}

		// rtti name
		if (!WriteString(ObjectTable[i].m_RttiName))
		{
			ENGINE_DELETEA(m_pcBuffer);
			return 0;
		}

		Write(&ObjectTable[i].m_uiObjectPropertySize, sizeof(unsigned int));

		Write(&ObjectTable[i].m_uiObjectPropertyNum, sizeof(unsigned int));
	}

	// OBJECT PROPERTY
	m_uiStreamFlag = AT_SAVE;
	for (unsigned int i = 0; i < m_pObjectArray.GetNum(); i++)
	{

		VSRtti& Rtti = m_pObjectArray[i]->GetType();
		for (unsigned int j = 0; j < Rtti.GetPropertyNum(); j++)
		{
			VSProperty* pProperty = Rtti.GetProperty(j);

			if (pProperty->GetFlag() & VSProperty::F_SAVE_LOAD)
			{

				Write(&ObjectTable[i].m_ObjectPropertyTable[j].m_uiNameID, sizeof(unsigned int));
				Write(&ObjectTable[i].m_ObjectPropertyTable[j].m_uiOffset, sizeof(unsigned int));
			}
		}

		for (unsigned int j = 0; j < Rtti.GetPropertyNum(); j++)
		{
			VSProperty* pProperty = Rtti.GetProperty(j);
			if (pProperty->GetFlag() & VSProperty::F_SAVE_LOAD)
			{
				pProperty->Archive(*this, m_pObjectArray[i]);
			}
		}
	}
	//预留PostSave
	for (unsigned int i = 0; i < m_pObjectArray.GetNum(); i++)
	{
		m_pObjectArray[i]->PostSave(this);
	}

	Core::File* pFile = MX_NEW Core::File();
	if (!pFile)
	{
		ENGINE_DELETEA(m_pcBuffer);
		return 0;
	}
	//打开文件
	if (!pFile->Open(pcFileName, Core::File::OM_WB))
	{
		ENGINE_DELETE(pFile);
		ENGINE_DELETEA(m_pcBuffer);
		return 0;
	}

	if (!pFile->Write(m_pcBuffer, m_uiBufferSize, 1))
	{
		ENGINE_DELETE(pFile);
		ENGINE_DELETEA(m_pcBuffer);
		return 0;
	}
	ENGINE_DELETE(pFile);
	ENGINE_DELETEA(m_pcBuffer);
	return 1;
}