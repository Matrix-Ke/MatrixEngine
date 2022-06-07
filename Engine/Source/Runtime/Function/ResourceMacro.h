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
    Core::MSynchronize ClassName::ms_LoadResourceCriticalSection;                                                 \
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
    \ public : constexpr static unsigned int ms_uiResourceAbility = ResourceAbility;                         \
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
    static Core::MSynchronize ms_LoadResourceCriticalSection;                                                \
    static bool RegisterGCResourceSet();                                                                     \
    static bool ms_bRegisterGCResource;                                                                      \
    friend class InCacheType;                                                                                \
    typedef InCacheType CacheType;                                                                           \
    Container::MString GetCacheFilePath() const                                                              \
    {                                                                                                        \
        VSFileName FileName(m_ResourceName.GetString());                                                     \
        Container::MString PathAndName;                                                                      \
        bool bFind = FileName.GetPathAndName(PathAndName);                                                   \
        MATRIX_ENGINE_ASSERT(bFind)                                                                          \
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
        Container::MString Path = Container::MString(ms_CachePath) + GetCurPlatformName() + _T("/");     \
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

#define GET_SHADER_MAP(Name)                       \
    GET_SHADER_MAP_INNER(Name##VertexShaderMap);   \
    GET_SHADER_MAP_INNER(Name##PixelShaderMap);    \
    GET_SHADER_MAP_INNER(Name##GeometryShaderMap); \
    GET_SHADER_MAP_INNER(Name##HullShaderMap);     \
    GET_SHADER_MAP_INNER(Name##DomainShaderMap);   \
    GET_SHADER_MAP_INNER(Name##ComputeShaderMap);

}
