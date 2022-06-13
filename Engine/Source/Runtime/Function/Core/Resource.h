#pragma once
#include "ResourceMacro.h"
#include "Core/ObjName.h"
#include "Core/Object.h"
#include "Core/StreamingType.h"

#include "Container/Array.h"

namespace Matrix
{
    class MStream;
    class MATRIX_FUNCTION_API VSResourceInterface
    {
    public:
        VSResourceInterface();
        virtual ~VSResourceInterface() = 0;
        virtual const VSUsedName &GetResourceName() const
        {
            ENGINE_ASSERT(false);
            return VSUsedName::ms_cNULL;
        }
        virtual void SetResourceName(const VSUsedName &ResourceName){};
        virtual bool IsCanSave()
        {
            return true;
        }
    };
    enum // resource ability
    {
        RA_NONE = 0x00,
        RA_ASYN_LOAD = 0x01,
        RA_ASYN_POSTLOAD = 0x02,
        RA_ENABLE_GC = 0x04,
        RA_NEED_CACHE = 0x08,
    };

    class MATRIX_FUNCTION_API VSResource : public VSResourceInterface
    {
    public:
        enum // Resource Type
        {
            RT_TEXTURE,
            RT_SKELECTON_MODEL,
            RT_STATIC_MODEL,
            RT_ACTION,
            RT_MATERIAL,
            RT_POSTEFFECT,
            RT_ANIMTREE,
            RT_ACTOR,
            RT_MAP,
            RT_FONTTYPE,
            RT_MAX
        };
        VSResource();
        virtual ~VSResource() = 0;
        virtual const VSUsedName &GetResourceName() const
        {
            return m_ResourceName;
        }
        virtual void SetResourceName(const VSUsedName &ResourceName)
        {
            m_ResourceName = ResourceName;
        }
        virtual unsigned int GetCurStreamLevel() const
        {
            return 1;
        }
        virtual MObject *CreateToStreamObject(unsigned int uiWantSteamLevel, const VSCacheResource *pCacheResouce) const
        {
            return NULL;
        }
        virtual void StreamEnd(MObject *pStreamResource)
        {
        }

    protected:
        VSUsedName m_ResourceName;
    };

    class MATRIX_FUNCTION_API VSResourceProxyBase : public VSReference, public Core::MemoryObject, public VSStreamingType
    {
    public:
        VSResourceProxyBase();
        virtual ~VSResourceProxyBase() = 0;
        virtual unsigned int GetResourceAbility() = 0;
        inline bool IsLoaded()
        {
            return m_bIsLoaded;
        }
        inline const VSUsedName &GetResourceName()
        {
            return m_ResourceName;
        }
        virtual unsigned int GetResourceType() = 0;
        virtual void OnLoadEvent() = 0;
        void LoadEvent()
        {
            for (unsigned int i = 0; i < m_LoadedEventObject.GetNum(); i++)
            {
                m_LoadedEventObject[i].Key->LoadedEvent(this, m_LoadedEventObject[i].Value);
            }
            m_LoadedEventObject.Destroy();
        }
        void AddLoadEventObject(MObject *pObject, void *Data = NULL)
        {
            if (!pObject)
            {
                return;
            }
            if (m_bIsLoaded == false)
            {
                m_LoadedEventObject.AddElement(pObject, Data);
            }
            else
            {
                pObject->LoadedEvent(this, Data);
            }
        }
        void *DeleteLoadEventObject(MObject *pObject)
        {
            void *pData = NULL;
            if (!m_bIsLoaded)
            {
                unsigned int i = m_LoadedEventObject.Find(pObject);
                if (i != m_LoadedEventObject.GetNum())
                {
                    pData = m_LoadedEventObject[i].Value;
                    m_LoadedEventObject.Erase(i);
                }
            }
            return pData;
        }

    protected:
        Container::MMap<MObject *, void *> m_LoadedEventObject;
        bool m_bIsLoaded;
        VSUsedName m_ResourceName;
        void Loaded()
        {
            m_bIsLoaded = true;
            OnLoadEvent();
            LoadEvent();
        }
        void SetResourceName(const VSUsedName &ResourceName)
        {
            m_ResourceName = ResourceName;
        }
    };
    DECLARE_Ptr(VSResourceProxyBase);
    class MATRIX_FUNCTION_API VSCacheResource : public MObject, public VSResourceInterface
    {
    public:
        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL_NO_CLASS_FACTORY;
        VSCacheResource();
        virtual ~VSCacheResource() = 0;
        virtual bool SetCacheResource(MObject *pOwner) { return true; }
        virtual bool SetStreamResouce(VSResourceProxyBase *pOwner) { return true; }

    public:
        constexpr static bool ms_bEnableAsynPostLoad = false;
        RESOURCE_PATH(, )
        static Container::MString GetCachePath()
        {
            return Container::MString::ms_StringNULL;
        }
    };
    DECLARE_Ptr(VSCacheResource);
    VSTYPE_MARCO(VSCacheResource);
    template <class T>
    class VSResourceProxy : public VSResourceProxyBase
    {
    public:
        VSResourceProxy();
        virtual ~VSResourceProxy();
        T *GetResource();
        friend class VSResourceManager;
        template <typename T>
        friend class VSTResourceJob;
        virtual unsigned int GetResourceAbility();
        virtual unsigned int GetResourceType();
        virtual void OnLoadEvent();
        virtual unsigned int GetCurStreamLevel() const;
        virtual const MObject *CreateToStreamObject(const VSCacheResource *pCacheResouce);
        virtual void SetStreamJob();
        virtual void StreamEnd();
        void SetNewResource(VSPointer<T> pResource);
        static VSResourceProxy<T> *Create(T *pResource);

    protected:
        VSPointer<T> m_pResource;
        VSPointer<T> m_pPreResource;
    };
    template <class T>
    VSResourceProxy<T> *VSResourceProxy<T>::Create(T *pResource)
    {
        VSResourceProxy<T> *pProxy = MX_NEW VSResourceProxy<T>();
        pProxy->SetResourceName(pResource->GetResourceName());
        pProxy->SetNewResource(pResource);
        pProxy->Loaded();
        return pProxy;
    }
    template <class T>
    VSResourceProxy<T>::VSResourceProxy()
    {
        m_bIsLoaded = false;
        m_pPreResource = (T *)T::GetDefault();
        m_pResource = NULL;
    }
    template <class T>
    VSResourceProxy<T>::~VSResourceProxy()
    {
        m_pPreResource = NULL;
        m_pResource = NULL;
    }
    template <class T>
    void VSResourceProxy<T>::SetNewResource(VSPointer<T> pResource)
    {
        m_pResource = pResource;
        m_pResource->SetResourceName(m_ResourceName);
    }
    template <class T>
    unsigned int VSResourceProxy<T>::GetResourceAbility()
    {
        return T::ms_uiResourceAbility;
    }
    template <class T>
    unsigned int VSResourceProxy<T>::GetCurStreamLevel() const
    {
        return m_pResource->GetCurStreamLevel();
    }
    template <class T>
    void VSResourceProxy<T>::StreamEnd()
    {
        if (m_pToStreamObject)
        {
            m_pResource->StreamEnd(m_pToStreamObject);
        }
        VSResourceProxyBase::StreamEnd();
    }
    template <class T>
    const MObject *VSResourceProxy<T>::CreateToStreamObject(const VSCacheResource *pCacheResouce)
    {
        m_pToStreamObject = m_pResource->CreateToStreamObject(m_uiWantStreamLevel, pCacheResouce);
        ToEndStream();
        return m_pToStreamObject;
    }
    template <class T>
    void VSResourceProxy<T>::SetStreamJob()
    {
        VSStreamingType::SetStreamJob();
        if (m_StreamState == SS_STREAMING)
        {
            VSASYNLoadManager::ms_pASYNLoadManager->AddStreamResourceJob(this);
        }
    }
    template <class T>
    void VSResourceProxy<T>::OnLoadEvent()
    {
        ENGINE_ASSERT(m_pResource && m_uiMaxLevel == 1);
        m_uiMaxLevel = m_pResource->GetCurStreamLevel();
        ToReadyStream();
    }
    template <class T>
    T *VSResourceProxy<T>::GetResource()
    {
        if (m_bIsLoaded)
        {
            return m_pResource;
        }
        else
        {
            return m_pPreResource;
        }
    }
    template <class T>
    unsigned int VSResourceProxy<T>::GetResourceType()
    {
        return GetResource()->GetResourceType();
    }

    class VSResourceControl
    {
    public:
        VSResourceControl(unsigned int uiGCMaxTimeCount);
        virtual ~VSResourceControl();
        virtual void GCResource() = 0;
        virtual bool IsReleseAll() = 0;
        virtual void ClearAll() = 0;
        static void AddNeedGCResource(VSResourceControl *pGCResource)
        {
            GetNeedGCResource().AddElement(pGCResource);
        }
        static void AddResourceRtti(VSRtti *pResourceRtti)
        {
            GetResourceRtti().AddElement(pResourceRtti);
        }
        static void GCAllResource()
        {
            for (auto Temp : GetNeedGCResource())
            {
                Temp->GCResource();
            }
        }
        static bool IsAllRelese()
        {
            for (auto Temp : GetNeedGCResource())
            {
                if (!Temp->IsReleseAll())
                {
                    return false;
                }
            }
            return true;
        }
        static void AllClear()
        {
            for (auto Temp : GetNeedGCResource())
            {
                Temp->ClearAll();
            }
        }
        static bool IsResourceType(VSRtti &Rtti)
        {
            for (unsigned int i = 0; i < GetResourceRtti().GetNum(); i++)
            {
                if (Rtti.IsSameType(*(GetResourceRtti()[i])))
                {
                    return true;
                }
            }
            return false;
        }
        static void AddDefaultResource(VSResourceProxyBase **ppDefaultResource)
        {
            GetDefaultResource().AddElement(ppDefaultResource);
        }
        static bool IsDefaultResource(VSResourceProxyBase *pResourceProxy)
        {
            if (!pResourceProxy)
            {
                return false;
            }
            for (auto &Temp : GetDefaultResource())
            {
                VSResourceProxyBase *pTempResourceProxy = (*Temp);
                if (!pTempResourceProxy)
                {
                    continue;
                }
                else if (pResourceProxy == pTempResourceProxy)
                {
                    return true;
                }
            }
            return false;
        }

    protected:
        static Container::MArray<VSResourceProxyBase **> &GetDefaultResource()
        {
            static Container::MArray<VSResourceProxyBase **> ms_DefaultResource;
            return ms_DefaultResource;
        }
        static Container::MArray<VSResourceControl *> &GetNeedGCResource()
        {
            static Container::MArray<VSResourceControl *> ms_NeedGCResource;
            return ms_NeedGCResource;
        }
        static Container::MArray<VSRtti *> &GetResourceRtti()
        {
            static Container::MArray<VSRtti *> ms_ResourceRtti;
            return ms_ResourceRtti;
        }
        Container::MArray<unsigned int> m_TimeCount;
        unsigned int m_uiGCMaxTimeCount;
    };
    template <class T>
    class VSResourceArrayControl : public VSResourceControl
    {
    public:
        VSResourceArrayControl(unsigned int uiGCMaxTimeCount = 5000);
        ~VSResourceArrayControl();
        bool AddResource(const T &R);
        bool DeleteResource(const T &R);
        virtual void GCResource();
        virtual bool IsReleseAll();
        virtual void ClearAll();
        T GetResource(unsigned int i);
        void ClearTimeCount(unsigned int i);
        unsigned int GetResourceNum();

    protected:
        Container::MArrayOrder<T> m_ResourceArray;
    };
    template <class T>
    VSResourceArrayControl<T>::VSResourceArrayControl(unsigned int uiGCMaxTimeCount)
        : VSResourceControl(uiGCMaxTimeCount)
    {
    }
    template <class T>
    VSResourceArrayControl<T>::~VSResourceArrayControl()
    {
    }
    template <class T>
    T VSResourceArrayControl<T>::GetResource(unsigned int i)
    {
        if (i >= m_ResourceArray.GetNum())
        {
            return NULL;
        }

        return m_ResourceArray[i];
    }
    template <class T>
    unsigned int VSResourceArrayControl<T>::GetResourceNum()
    {
        return m_ResourceArray.GetNum();
    }
    template <class T>
    void VSResourceArrayControl<T>::ClearTimeCount(unsigned int i)
    {
        m_TimeCount[i] = 0;
    }
    template <class T>
    bool VSResourceArrayControl<T>::AddResource(const T &R)
    {
        m_ResourceArray.AddElement(R);
        m_TimeCount.AddElement(0);
        return true;
    }
    template <class T>
    bool VSResourceArrayControl<T>::DeleteResource(const T &R)
    {
        unsigned int i = m_ResourceArray.FindElement(R);
        if (i == m_ResourceArray.GetNum())
        {
            return false;
        }
        else
        {
            m_ResourceArray.Erase(i);
            m_TimeCount.Erase(i);
        }
        return true;
    }
    template <class T>
    void VSResourceArrayControl<T>::GCResource()
    {
        unsigned int i = 0;
        while (i < m_ResourceArray.GetNum())
        {
            if (m_ResourceArray[i]->GetRef() == 1)
            {
                m_TimeCount[i]++;
                if (m_TimeCount[i] > m_uiGCMaxTimeCount)
                {
                    //  gc one resource once,then return
                    m_ResourceArray.Erase(i);
                    m_TimeCount.Erase(i);
                    break;
                }
                else
                {
                    i++;
                }
            }
            else
            {
                m_TimeCount[i] = 0;
                i++;
            }
        }
    }
    template <class T>
    bool VSResourceArrayControl<T>::IsReleseAll()
    {
        return m_ResourceArray.GetNum() == 0;
    }
    template <class T>
    void VSResourceArrayControl<T>::ClearAll()
    {
        m_ResourceArray.Clear();
    }
    template <class KEY, class VALUE>
    class VSResourceSet : public VSResourceControl
    {
    protected:
        Container::MMapOrder<KEY, VALUE> m_Resource;

    public:
        VSResourceSet(unsigned int uiGCMaxTimeCount = 5000);
        ~VSResourceSet();
        //写在每个加载资源函数里面的，如果存在这个资源，则返回这个资源指针，否则在加载资源函数里面创建这个资源
        VALUE CheckIsHaveTheResource(const KEY &Key);

        bool AddResource(const KEY &Key, VALUE pObject);
        //写在每个资源的析构函数里面
        bool DeleteResource(const KEY &Key);

        unsigned int GetResourceNum();

        virtual bool IsReleseAll();
        virtual void ClearAll();
        const Container::MapElement<KEY, VALUE> *GetResource(unsigned int i);
        virtual void GCResource();
        unsigned int GetResourceIndexByKey(const KEY &Key) const;
    };
    template <class KEY, class VALUE>
    class VSProxyResourceSet : public VSResourceSet<KEY, VALUE>
    {
    public:
        VSProxyResourceSet(unsigned int uiGCMaxTimeCount = 5000);
        ~VSProxyResourceSet();
        //资源垃圾回收的代码。遍历所有资源，如果这种类型的资源能够回收，它已经加载完毕，
        //而且没有其他对象引用，那么就判断时间计数。若时间计数大于 m_uiGCMaxTimeCount，就把这个资源代理释放掉；否则，就把时间计数清零
        virtual void GCResource();
    };
    template <class KEY, class VALUE>
    unsigned int VSResourceSet<KEY, VALUE>::GetResourceIndexByKey(const KEY &Key) const
    {

        unsigned int i = m_Resource.Find(Key);
        return i;
    }
    template <class KEY, class VALUE>
    void VSResourceSet<KEY, VALUE>::GCResource()
    {
        unsigned int i = 0;
        while (i < m_Resource.GetNum())
        {
            const Container::MapElement<KEY, VALUE> &Resource = m_Resource[i];
            if (Resource.Value->GetRef() == 1)
            {
                m_TimeCount[i]++;
                if (m_TimeCount[i] > m_uiGCMaxTimeCount)
                {
                    //  gc one resource once,then return
                    m_Resource.Erase(i);
                    m_TimeCount.Erase(i);
                    break;
                }
                else
                {
                    i++;
                }
            }
            else
            {
                m_TimeCount[i] = 0;
                i++;
            }
        }
    }
    template <class KEY, class VALUE>
    VSResourceSet<KEY, VALUE>::VSResourceSet(unsigned int uiGCMaxTimeCount)
        : VSResourceControl(uiGCMaxTimeCount)
    {
        m_Resource.Clear();
    }
    template <class KEY, class VALUE>
    VSResourceSet<KEY, VALUE>::~VSResourceSet()
    {
        m_Resource.Clear();
    }
    template <class KEY, class VALUE>
    VALUE VSResourceSet<KEY, VALUE>::CheckIsHaveTheResource(const KEY &Key)
    {
        unsigned int i = m_Resource.Find(Key);
        if (i == m_Resource.GetNum())
            return NULL;
        // Clear TimeCout
        m_TimeCount[i] = 0;
        return m_Resource[i].Value;
    }

    template <class KEY, class VALUE>
    bool VSResourceSet<KEY, VALUE>::AddResource(const KEY &Key, VALUE pObject)
    {
        if (!pObject)
            return 0;

        m_Resource.AddElement(Key, pObject);
        m_TimeCount.AddElement(0);

        return 1;
    }
    template <class KEY, class VALUE>
    bool VSResourceSet<KEY, VALUE>::DeleteResource(const KEY &Key)
    {

        unsigned int i = m_Resource.Find(Key);
        if (i == m_Resource.GetNum())
            return false;
        m_Resource.Erase(i);
        m_TimeCount.Erase(i);
        return true;
    }

    template <class KEY, class VALUE>
    unsigned int VSResourceSet<KEY, VALUE>::GetResourceNum()
    {
        return m_Resource.GetNum();
    }

    template <class KEY, class VALUE>
    bool VSResourceSet<KEY, VALUE>::IsReleseAll()
    {
        return !m_Resource.GetNum();
    }
    template <class KEY, class VALUE>
    void VSResourceSet<KEY, VALUE>::ClearAll()
    {
        m_Resource.Clear();
    }
    template <class KEY, class VALUE>
    const Container::MapElement<KEY, VALUE> *VSResourceSet<KEY, VALUE>::GetResource(unsigned int i)
    {
        ENGINE_ASSERT(i < m_Resource.GetNum());
        if (i >= m_Resource.GetNum())
        {
            return NULL;
        }
        return &m_Resource[i];
    }

    template <class KEY, class VALUE>
    VSProxyResourceSet<KEY, VALUE>::VSProxyResourceSet(unsigned int uiGCMaxTimeCount)
        : VSResourceSet<KEY, VALUE>(uiGCMaxTimeCount)
    {
    }
    template <class KEY, class VALUE>
    VSProxyResourceSet<KEY, VALUE>::~VSProxyResourceSet()
    {
    }
    template <class KEY, class VALUE>
    void VSProxyResourceSet<KEY, VALUE>::GCResource()
    {
        unsigned int i = 0;
        while (i < m_Resource.GetNum())
        {
            const Container::MapElement<KEY, VALUE> &Resource = m_Resource[i];
            if ((Resource.Value->GetResourceAbility() & RA_ENABLE_GC) && Resource.Value->IsLoaded() && Resource.Value->GetRef() == 1)
            {
                m_TimeCount[i]++;
                if (m_TimeCount[i] > m_uiGCMaxTimeCount)
                {
                    m_Resource.Erase(i);
                    m_TimeCount.Erase(i);
                }
                else
                {
                    i++;
                }
            }
            else
            {
                m_TimeCount[i] = 0;
                i++;
            }
        }
    }
}
