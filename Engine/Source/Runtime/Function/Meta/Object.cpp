#include "Object.h"
#include "./../EngineInit.h"
#include "Stream.h"
#include "Property.h"
//#include "Profiler.h"


using namespace Matrix;


IMPLEMENT_RTTI_NoParent_NoCreateFun(VSObject)
Container::MMapOrder<VSUsedName, FactoryFunction> VSObject::ms_ClassFactory;
IMPLEMENT_INITIAL_NO_CLASS_FACTORY_BEGIN(VSObject)
IMPLEMENT_INITIAL_NO_CLASS_FACTORY_END
BEGIN_ADD_PROPERTY_ROOT(VSObject)
REGISTER_PROPERTY(m_uiFlag, Flag, VSProperty::F_CLONE);
END_ADD_PROPERTY
//todo   profiler macro
//DECLEAR_NOCLEAR_COUNT_PROFILENODE(ObjectNum, )




VSFastObjectManager::VSFastObjectManager()
{
	m_uiObjectNum = 0;
	ObjectHashTree.SetHashNum(1000);
}
VSFastObjectManager::~VSFastObjectManager()
{
}
void VSFastObjectManager::AddObject(VSObject* p)
{
	MATRIX_ENGINE_ASSERT(p);
	ObjectHashTree.AddElement(p);
	m_uiObjectNum++;
	//todo   profiler macro
	//ADD_COUNT_PROFILE(ObjectNum, 1)
}
void VSFastObjectManager::DeleteObject(VSObject* p)
{
	MATRIX_ENGINE_ASSERT(p);
	ObjectHashTree.Erase(p);
	m_uiObjectNum--;
	//todo   profiler macro
	//ADD_COUNT_PROFILE(ObjectNum, -1)
}
bool VSFastObjectManager::IsClear()
{
	return m_uiObjectNum == 0;
}
unsigned int VSFastObjectManager::GetObjectNum()
{
	return m_uiObjectNum;
}
template <class T>
class VSPrepareForGC
{
public:
	VSPrepareForGC()
	{
	}
	~VSPrepareForGC() {}
	void operator()(Container::MBinaryTreeNode<T>* TreeNode)
	{
		TreeNode->Element->ClearFlag(VSObject::OF_REACH);
		TreeNode->Element->SetFlag(VSObject::OF_UNREACH);
	}
};
void VSFastObjectManager::PrepareForGC()
{
	ObjectHashTree.MiddleProcess(VSPrepareForGC<VSObject*>());
}
VSObject* VSObject::CloneCreateObject(VSObject* pObject)
{
	Container::MMap<VSObject*, VSObject*> CloneMap;
	VSObject* pNewObject = _CloneCreateObject(pObject, CloneMap); //克隆完毕
	for (unsigned int i = 0; i < CloneMap.GetNum(); i++)
	{
		CloneMap[i].Value->PostClone(CloneMap[i].Key);
	}
	return pNewObject;
}
void VSObject::CloneObject(VSObject* pObjectSrc, VSObject* pObjectDest)
{
	Container::MMap<VSObject*, VSObject*> CloneMap;
	_CloneObject(pObjectSrc, pObjectDest, CloneMap);
	for (unsigned int i = 0; i < CloneMap.GetNum(); i++)
	{
		CloneMap[i].Value->PostClone(CloneMap[i].Key);
	}
}
VSObject* VSObject::_CloneCreateObject(VSObject* pObject, Container::MMap<VSObject*, VSObject*>& CloneMap)
{
	VSObject* pNewObject = NULL;
	if (pObject)
	{
		unsigned int uiIndex = CloneMap.Find(pObject);
		//在克隆 VSObject 对象表中没有创建这个对象
		if (uiIndex == CloneMap.GetNum())
		{
			VSRtti& SrcRtti = pObject->GetType();
			pNewObject = VSObject::GetInstance(SrcRtti.GetName());
			//添加新创建的 VSObject 对象映射关系
			CloneMap.AddElement(pObject, pNewObject);
			VSRtti& DestRtti = pNewObject->GetType();
			//遍历所有属性
			for (unsigned int i = 0; i < SrcRtti.GetPropertyNum(); i++)
			{
				VSProperty* pProperty = SrcRtti.GetProperty(i);
				if (pProperty->GetFlag() & VSProperty::F_CLONE)
				{
					pProperty->CloneData(
						pObject, pNewObject, CloneMap);
				}
				else if (pProperty->GetFlag() & VSProperty::F_COPY)
				{
					pProperty->CopyData(pObject, pNewObject);
				}
			}
		}
		else
		{
			pNewObject = CloneMap[uiIndex].Value;
		}
	}
	return pNewObject;

}
void VSObject::_CloneObject(VSObject* pObjectSrc, VSObject* pObjectDest, Container::MMap<VSObject*, VSObject*>& CloneMap)
{
	if (!pObjectSrc)
	{
		return;
	}
	unsigned int uiIndex = CloneMap.Find(pObjectSrc);

	if (uiIndex == CloneMap.GetNum())
	{
		VSRtti& SrcRtti = pObjectSrc->GetType();
		VSRtti& DestRtti = pObjectDest->GetType();
		for (unsigned int i = 0; i < SrcRtti.GetPropertyNum(); i++)
		{
			VSProperty* pProperty = SrcRtti.GetProperty(i);
			if (pProperty->GetFlag() & VSProperty::F_CLONE)
			{
				pProperty->CloneData(pObjectSrc, pObjectDest, CloneMap);
			}
			else if (pProperty->GetFlag() & VSProperty::F_COPY)
			{
				pProperty->CopyData(pObjectSrc, pObjectDest);
			}
		}
	}
	else
	{
		MATRIX_ENGINE_ASSERT(0);
	}
}
/********************************************************************************/
VSObject* VSObject::GetNoGCInstance(const Container::MString& sRttiName)
{
	unsigned int i = ms_ClassFactory.Find(sRttiName);
	if (i == ms_ClassFactory.GetNum())
		return NULL;

	VSObject* pObject = ms_ClassFactory[i].Value();
	return pObject;
}
VSObject* VSObject::GetInstance(const Container::MString& sRttiName)
{
	unsigned int i = ms_ClassFactory.Find(sRttiName);
	if (i == ms_ClassFactory.GetNum())
		return NULL;

	VSObject* pObject = ms_ClassFactory[i].Value();

	//todo list VSResourceManager
	//VSResourceManager::AddGCObject(pObject);
	return pObject;
}
VSObject* VSObject::GetInstance(const VSRtti& Rtti)
{
	VSObject* pObject = (Rtti.m_CreateFun)();
	//todo list VSResourceManager
	//VSResourceManager::AddGCObject(pObject);
	return pObject;
}
/********************************************************************************/
VSObject::VSObject()
{
	m_uiFlag = 0;
	GetObjectManager().AddObject(this);

} // end construct
VSObject::VSObject(const VSObject& object)
{
	m_uiFlag = object.m_uiFlag;
	GetObjectManager().AddObject(this);
}
VSObject& VSObject::operator=(const VSObject& object)
{
	m_uiFlag = object.m_uiFlag;
	return *this;
}
/********************************************************************************/

VSObject::~VSObject()
{
	GetObjectManager().DeleteObject(this);
} // end destruct

bool VSObject::IsSameType(const VSObject* pObject) const
{

	return pObject && GetType().IsSameType(pObject->GetType());

} // end IsSameType

/********************************************************************************/

bool VSObject::IsDerived(const VSObject* pObject) const
{
	return pObject && GetType().IsDerived(pObject->GetType());
} // IsDerived

/********************************************************************************/

bool VSObject::IsSameType(const VSRtti& Type) const
{

	return GetType().IsSameType(Type);
} // IsSameType

/********************************************************************************/

bool VSObject::IsDerived(const VSRtti& Type) const
{
	return GetType().IsDerived(Type);

} // IsDerived

void VSObject::LoadedEvent(VSResourceProxyBase* pResourceProxy, void* Data)
{
}
//todo list  GetStreamResource
//void VSObject::GetStreamResource(Container::MArray<VSResourceProxyBase*>& pResourceProxy, StreamInformation_TYPE& StreamInformation) const
//{
//}
bool VSObject::BeforeSave(VSStream* pStream)
{
	return 1;
}
bool VSObject::PostSave(VSStream* pStream)
{
	return 1;
}
bool VSObject::PostLoad(VSStream* pStream)
{
	return 1;
}
bool VSObject::PostClone(VSObject* pObjectSrc)
{
	return 1;
}
void VSObject::ValueChange(Container::MString& Name)
{
}
bool VSObject::Process(VSUsedName& FunName, void* para, void* ret, int ParaNum)
{
	VSRtti& t = GetType();
	for (unsigned int i = 0; i < t.GetFunctionNum(); i++)
	{
		VSFunction* p = t.GetFunction(i);
		if (p->GetName() == FunName)
		{
			if (ParaNum == -1)
			{
				p->ObjectFun(this, p, para, ret);
				return true;
			}
			else if (p->GetPropertyNum() == ParaNum)
			{
				p->ObjectFun(this, p, para, ret);
				return true;
			}
		}
	}
	return false;
}