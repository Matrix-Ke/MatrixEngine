#pragma once

namespace Matrix
{

#define RESOURCE_PATH(FileSuffix, DefaultPath)                            \
public:                                                                   \
    constexpr static TCHAR *ms_FileSuffix = _T(#FileSuffix);              \
    constexpr static TCHAR *ms_PointFileSuffix = _T(".") _T(#FileSuffix); \
    constexpr static TCHAR *ms_ResourcePath = _T(#DefaultPath) _T("/");

#define IMPLEMENT_RESOURCE(ClassName)                                                                             \
    VSPointer<ClassName> ClassName::ms_Default = NULL;                                                            \
    VSPointer<VSResourceProxy<ClassName>> ClassName::ms_DefaultResource = NULL;                                   \
    Platform::MCriticalSection ClassName::ms_LoadResourceCriticalSection;                                                 \
    static bool gs_bResourceRegistered_##ClassName = ClassName::RegisterGCResourceSet();                          \
    bool ClassName::ms_bRegisterGCResource = false;                                                               \
    bool ClassName::RegisterGCResourceSet()                                                                       \
    {                                                                                                             \
        if (!ms_bRegisterGCResource)                                                                              \
        {                                                                                                         \
            if (ClassName::ms_uiResourceAbility & RA_ENABLE_GC)                                                   \
            {                                                                                                     \
                VSResourceControl::AddNeedGCResource(&GetASYNResourceSet());                                      \
            }                                                                                                     \
            VSResourceControl::AddDefaultResource((VSResourceProxyBase **)ms_DefaultResource.GetObjectAddress()); \
            VSResourceControl::AddResourceRtti(&ClassName::ms_Type);                                              \
            ms_bRegisterGCResource = true;                                                                        \
        }                                                                                                         \
        return ms_bRegisterGCResource;                                                                            \
    }


#define DECLARE_RESOURCE(ClassName, ResourceAbility, ResourceType, FileSuffix, DefaultPath, InCacheType)     \
    RESOURCE_PATH(FileSuffix, DefaultPath)                                                                   \
protected:                                                                                                   \
    static VSPointer<ClassName> ms_Default;                                                                  \
    static VSPointer<VSResourceProxy<ClassName>> ms_DefaultResource;                                         \
    public : constexpr static unsigned int ms_uiResourceAbility = ResourceAbility;                           \
    constexpr static unsigned int ms_ResourceType = ResourceType;                                            \
    static unsigned int GetResourceType()                                                                    \
    {                                                                                                        \
        return ms_ResourceType;                                                                              \
    }                                                                                                        \
    static const ClassName *GetDefault()                                                                     \
    {                                                                                                        \
        return ms_Default;                                                                                   \
    }                                                                                                        \
    static const VSResourceProxy<ClassName> *GetDefaultResource()                                            \
    {                                                                                                        \
        return ms_DefaultResource;                                                                           \
    }                                                                                                        \
    static VSProxyResourceSet<VSUsedName, VSPointer<VSResourceProxy<ClassName>>> &GetASYNResourceSet()       \
    {                                                                                                        \
        static VSProxyResourceSet<VSUsedName, VSPointer<VSResourceProxy<ClassName>>> s_ASYN##ClassName##Set; \
        return s_ASYN##ClassName##Set;                                                                       \
    }                                                                                                        \
    static Platform::MCriticalSection ms_LoadResourceCriticalSection;                                        \
    static bool RegisterGCResourceSet();                                                                     \
    static bool ms_bRegisterGCResource;                                                                      \
    friend class InCacheType;                                                                                \
    typedef InCacheType CacheType;                                                                           \
    Container::MString GetCacheFilePath() const                                                              \
    {                                                                                                        \
        Container::MFileName FileName(m_ResourceName.GetString());                                           \
        Container::MString PathAndName;                                                                      \
        bool bFind = FileName.GetPathAndName(PathAndName);                                                   \
        ENGINE_ASSERT(bFind)                                                                                 \
        Container::MString Name;                                                                             \
        const TCHAR *Replace = _T("/");                                                                      \
        Name.ReplaceChars(PathAndName, Replace, '_');                                                        \
        Container::MString FullName = CacheType::GetCachePath();                                             \
        FullName += Name;                                                                                    \
        FullName += CacheType::ms_PointFileSuffix;                                                           \
        return FullName;                                                                                     \
    }

#define DECLARE_CACHE_RESOURCE(FileSuffix, DefaultPath, CachePath, HaveRendererPath, EnableAsynPostLoad) \
    RESOURCE_PATH(FileSuffix, DefaultPath)                                                               \
public:                                                                                                  \
    constexpr static bool ms_bEnableAsynPostLoad = EnableAsynPostLoad;                                   \
    constexpr static TCHAR *ms_CachePath = _T(#CachePath) _T("/");                                       \
    static Container::MString GetCachePath()                                                             \
    {                                                                                                    \
        Container::MString Path = Container::MString(ms_CachePath) + Platform::GetCurPlatformName() + _T("/");     \
        if (HaveRendererPath)                                                                            \
        {                                                                                                \
            Path += VSRenderer::ms_pRenderer->GetRenderTypeShaderPath();                                 \
        }                                                                                                \
        return Path;                                                                                     \
    }



#define DECLARE_Proxy(ClassName)                      \
    class ClassName;                                  \
    typedef VSResourceProxy<ClassName>##ClassName##R; \
    typedef VSPointer<VSResourceProxy<ClassName>>##ClassName##RPtr;

#define GET_INNER_RESOURCE_SET(ResourceName)                                             \
    static VSResourceSet<unsigned int, VS##ResourceName##Ptr> &Get##ResourceName##Set()  \
    {                                                                                    \
        static VSResourceSet<unsigned int, VS##ResourceName##Ptr> s_##ResourceName##Set; \
        return s_##ResourceName##Set;                                                    \
    }

#define GET_SHADER_MAP_INNER(ShaderMapName)                       \
    static VSShaderMap &Get##ShaderMapName()                      \
    {                                                             \
        static VSShaderMap s_##ShaderMapName(_T(#ShaderMapName)); \
        return s_##ShaderMapName;                                 \
    }

#define LOAD_SHADER_CACHE_INNER(ShaderMapName)                                                                        \
	{                                                                                                                     \
		MStream LoadStream;                                                                                              \
		Container::MString FileName = VSShaderMapCache::GetCachePath() + Get##ShaderMapName().m_ShaderMapName + Suffix;   \
		FileName += VSShaderMapCache::ms_PointFileSuffix;                                                                 \
		LoadStream.Load(FileName.GetBuffer());                                                                            \
		VSShaderMapCache* pShaderMapLoadSave = (VSShaderMapCache*)LoadStream.GetObjectByRtti(VSShaderMapCache::ms_Type); \
		if (pShaderMapLoadSave)                                                                                           \
		{                                                                                                                 \
			Get##ShaderMapName().GetShaderMap() = pShaderMapLoadSave->m_ShaderMap;                                        \
			ENGINE_DELETE(pShaderMapLoadSave);                                                                                 \
		}                                                                                                                 \
	}

#define SAVE_SHADER_CACHE_INNER(ShaderMapName)\
	{\
		MStream SaveStream;\
		SaveStream.SetStreamFlag(MStream::AT_REGISTER);\
		VSShaderMapCache * pShaderMapLoadSave = MX_NEW VSShaderMapCache();\
		pShaderMapLoadSave->m_ShaderMap = Get##ShaderMapName().GetShaderMap(); \
		SaveStream.ArchiveAll(pShaderMapLoadSave);\
		VSString FileName = VSShaderMapCache::GetCachePath() + Get##ShaderMapName().m_ShaderMapName + Suffix; \
		FileName += VSShaderMapCache::ms_PointFileSuffix;\
		SaveStream.Save(FileName.GetBuffer());\
		ENGINE_DELETE(pShaderMapLoadSave);\
	}

#define SAVE_SHADER_CACHE(Name)\
	SAVE_SHADER_CACHE_INNER(Name##VertexShaderMap);\
	SAVE_SHADER_CACHE_INNER(Name##PixelShaderMap);\
	SAVE_SHADER_CACHE_INNER(Name##GeometryShaderMap);\
	SAVE_SHADER_CACHE_INNER(Name##HullShaderMap);\
	SAVE_SHADER_CACHE_INNER(Name##DomainShaderMap);\
	SAVE_SHADER_CACHE_INNER(Name##ComputeShaderMap);


#define GET_SHADER_MAP(Name)\
		GET_SHADER_MAP_INNER(Name##VertexShaderMap);\
		GET_SHADER_MAP_INNER(Name##PixelShaderMap);\
		GET_SHADER_MAP_INNER(Name##GeometryShaderMap);\
		GET_SHADER_MAP_INNER(Name##HullShaderMap);\
		GET_SHADER_MAP_INNER(Name##DomainShaderMap);\
		GET_SHADER_MAP_INNER(Name##ComputeShaderMap);


#define LOAD_SHADER_CACHE(Name)                       \
		LOAD_SHADER_CACHE_INNER(Name##VertexShaderMap);   \
		LOAD_SHADER_CACHE_INNER(Name##PixelShaderMap);    \
		LOAD_SHADER_CACHE_INNER(Name##GeometryShaderMap); \
		LOAD_SHADER_CACHE_INNER(Name##HullShaderMap);     \
		LOAD_SHADER_CACHE_INNER(Name##DomainShaderMap);   \
		LOAD_SHADER_CACHE_INNER(Name##ComputeShaderMap);


#define CLEAR_SHADER_CACHE_INNER(ShaderMapName) Get##ShaderMapName().Clear();
#define CLEAR_SHADER_CACHE(Name)                       \
		CLEAR_SHADER_CACHE_INNER(Name##VertexShaderMap);   \
		CLEAR_SHADER_CACHE_INNER(Name##PixelShaderMap);    \
		CLEAR_SHADER_CACHE_INNER(Name##GeometryShaderMap); \
		CLEAR_SHADER_CACHE_INNER(Name##HullShaderMap);     \
		CLEAR_SHADER_CACHE_INNER(Name##DomainShaderMap);   \
		CLEAR_SHADER_CACHE_INNER(Name##ComputeShaderMap);



#define IS_RELEASE_ALL(MapName)        \
		if (!Get##MapName().IsReleseAll()) \
		{                                  \
			return false;                  \
		}

#define IS_RELEASE_ALL_SHADER(Name)          \
		IS_RELEASE_ALL(Name##VertexShaderMap);   \
		IS_RELEASE_ALL(Name##PixelShaderMap);    \
		IS_RELEASE_ALL(Name##GeometryShaderMap); \
		IS_RELEASE_ALL(Name##HullShaderMap);     \
		IS_RELEASE_ALL(Name##DomainShaderMap);   \
		IS_RELEASE_ALL(Name##ComputeShaderMap);


}
