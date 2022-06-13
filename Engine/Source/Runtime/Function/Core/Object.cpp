#include "Core/Object.h"
#include "./../EngineInit.h"
#include "Core/Stream/Stream.h"
#include "Property.h"
//#include "Core/Profiler.h"

using namespace Matrix;

IMPLEMENT_RTTI_NoParent_NoCreateFun(MObject)
    Container::MMapOrder<VSUsedName, FactoryFunction> MObject::ms_ClassFactory;
IMPLEMENT_INITIAL_NO_CLASS_FACTORY_BEGIN(MObject)
IMPLEMENT_INITIAL_NO_CLASS_FACTORY_END
BEGIN_ADD_PROPERTY_ROOT(MObject)
REGISTER_PROPERTY(m_uiFlag, Flag, VSProperty::F_CLONE);
END_ADD_PROPERTY
// todo   profiler macro
// DECLEAR_NOCLEAR_COUNT_PROFILENODE(ObjectNum, )

VSFastObjectManager::VSFastObjectManager()
{
    m_uiObjectNum = 0;
    ObjectHashTree.SetHashNum(1000);
}
VSFastObjectManager::~VSFastObjectManager()
{
}
void VSFastObjectManager::AddObject(MObject *p)
{
    ENGINE_ASSERT(p);
    ObjectHashTree.AddElement(p);
    m_uiObjectNum++;
    // todo   profiler macro
    // ADD_COUNT_PROFILE(ObjectNum, 1)
}
void VSFastObjectManager::DeleteObject(MObject *p)
{
    ENGINE_ASSERT(p);
    ObjectHashTree.Erase(p);
    m_uiObjectNum--;
    // todo   profiler macro
    // ADD_COUNT_PROFILE(ObjectNum, -1)
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
    void operator()(Container::MBinaryTreeNode<T> *TreeNode)
    {
        TreeNode->Element->ClearFlag(MObject::OF_REACH);
        TreeNode->Element->SetFlag(MObject::OF_UNREACH);
    }
};
void VSFastObjectManager::PrepareForGC()
{
    ObjectHashTree.MiddleProcess(VSPrepareForGC<MObject *>());
}
MObject *MObject::CloneCreateObject(MObject *pObject)
{
    Container::MMap<MObject *, MObject *> CloneMap;
    MObject *pNewObject = _CloneCreateObject(pObject, CloneMap); //克隆完毕
    for (unsigned int i = 0; i < CloneMap.GetNum(); i++)
    {
        CloneMap[i].Value->PostClone(CloneMap[i].Key);
    }
    return pNewObject;
}
void MObject::CloneObject(MObject *pObjectSrc, MObject *pObjectDest)
{
    Container::MMap<MObject *, MObject *> CloneMap;
    _CloneObject(pObjectSrc, pObjectDest, CloneMap);
    for (unsigned int i = 0; i < CloneMap.GetNum(); i++)
    {
        CloneMap[i].Value->PostClone(CloneMap[i].Key);
    }
}
MObject *MObject::_CloneCreateObject(MObject *pObject, Container::MMap<MObject *, MObject *> &CloneMap)
{
    MObject *pNewObject = NULL;
    if (pObject)
    {
        unsigned int uiIndex = CloneMap.Find(pObject);
        //在克隆 MObject 对象表中没有创建这个对象
        if (uiIndex == CloneMap.GetNum())
        {
            VSRtti &SrcRtti = pObject->GetType();
            pNewObject = MObject::GetInstance(SrcRtti.GetName());
            //添加新创建的 MObject 对象映射关系
            CloneMap.AddElement(pObject, pNewObject);
            VSRtti &DestRtti = pNewObject->GetType();
            //遍历所有属性
            for (unsigned int i = 0; i < SrcRtti.GetPropertyNum(); i++)
            {
                VSProperty *pProperty = SrcRtti.GetProperty(i);
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
void MObject::_CloneObject(MObject *pObjectSrc, MObject *pObjectDest, Container::MMap<MObject *, MObject *> &CloneMap)
{
    if (!pObjectSrc)
    {
        return;
    }
    unsigned int uiIndex = CloneMap.Find(pObjectSrc);

    if (uiIndex == CloneMap.GetNum())
    {
        VSRtti &SrcRtti = pObjectSrc->GetType();
        VSRtti &DestRtti = pObjectDest->GetType();
        for (unsigned int i = 0; i < SrcRtti.GetPropertyNum(); i++)
        {
            VSProperty *pProperty = SrcRtti.GetProperty(i);
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
        ENGINE_ASSERT(0);
    }
}
/********************************************************************************/
MObject *MObject::GetNoGCInstance(const Container::MString &sRttiName)
{
    unsigned int i = ms_ClassFactory.Find(sRttiName);
    if (i == ms_ClassFactory.GetNum())
        return NULL;

    MObject *pObject = ms_ClassFactory[i].Value();
    return pObject;
}
MObject *MObject::GetInstance(const Container::MString &sRttiName)
{
    unsigned int i = ms_ClassFactory.Find(sRttiName);
    if (i == ms_ClassFactory.GetNum())
        return NULL;

    MObject *pObject = ms_ClassFactory[i].Value();

    // todo list VSResourceManager
    // VSResourceManager::AddGCObject(pObject);
    return pObject;
}
MObject *MObject::GetInstance(const VSRtti &Rtti)
{
    MObject *pObject = (Rtti.m_CreateFun)();
    // todo list VSResourceManager
    // VSResourceManager::AddGCObject(pObject);
    return pObject;
}
/********************************************************************************/
MObject::MObject()
{
    m_uiFlag = 0;
    GetObjectManager().AddObject(this);

} // end construct
MObject::MObject(const MObject &object)
{
    m_uiFlag = object.m_uiFlag;
    GetObjectManager().AddObject(this);
}
MObject &MObject::operator=(const MObject &object)
{
    m_uiFlag = object.m_uiFlag;
    return *this;
}
/********************************************************************************/

MObject::~MObject()
{
    GetObjectManager().DeleteObject(this);
} // end destruct

bool MObject::IsSameType(const MObject *pObject) const
{

    return pObject && GetType().IsSameType(pObject->GetType());

} // end IsSameType

/********************************************************************************/

bool MObject::IsDerived(const MObject *pObject) const
{
    return pObject && GetType().IsDerived(pObject->GetType());
} // IsDerived

/********************************************************************************/

bool MObject::IsSameType(const VSRtti &Type) const
{

    return GetType().IsSameType(Type);
} // IsSameType

/********************************************************************************/

bool MObject::IsDerived(const VSRtti &Type) const
{
    return GetType().IsDerived(Type);

} // IsDerived

// bool MObject::InitialDefaultState()
//{
//	return true;
// }
//
// bool MObject::TerminateDefaltState()
//{
//	return true;
// }
void MObject::LoadedEvent(VSResourceProxyBase *pResourceProxy, void *Data)
{
}
// todo list  GetStreamResource
// void MObject::GetStreamResource(Container::MArray<VSResourceProxyBase*>& pResourceProxy, StreamInformation_TYPE& StreamInformation) const
//{
// }
bool MObject::BeforeSave(MStream *pStream)
{
    return 1;
}
bool MObject::PostSave(MStream *pStream)
{
    return 1;
}
bool MObject::PostLoad(MStream *pStream)
{
    return 1;
}
bool MObject::PostClone(MObject *pObjectSrc)
{
    return 1;
}
void MObject::ValueChange(Container::MString &Name)
{
}
bool MObject::Process(VSUsedName &FunName, void *para, void *ret, int ParaNum)
{
    VSRtti &t = GetType();
    for (unsigned int i = 0; i < t.GetFunctionNum(); i++)
    {
        VSFunction *p = t.GetFunction(i);
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