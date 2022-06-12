#pragma once
#include "Resource.h"
#include "Renderer.h"
namespace Matrix
{
    DECLARE_Ptr(VSShader);
    DECLARE_Ptr(VSShaderKey);
    typedef VSMapOrder<VSShaderKey, VSShaderPtr> VSShaderSet;
    class MATRIX_FUNCTION_API VSShaderMapCache : public VSCacheResource
    {
        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL
        DECLARE_CACHE_RESOURCE(CacheShader, Resource / Shader, Cache / Shader, true, false)
    public:
        VSShaderMapCache() {}
        ~VSShaderMapCache() {}
        VSMapOrder<VSUsedName, VSShaderSet> m_ShaderMap;
    };
    DECLARE_Ptr(VSShaderMapCache);
    VSTYPE_MARCO(VSShaderMapCache);
    class MATRIX_FUNCTION_API VSShaderMap
    {

    public:
        VSShaderMap(VSString ShaderMapName);
        ~VSShaderMap();

    protected:
        VSMapOrder<VSUsedName, VSShaderSet> m_ShaderMap;

    public:
        VSMapOrder<VSUsedName, VSShaderSet> &GetShaderMap()
        {
            return m_ShaderMap;
        }
        void SetShader(const VSUsedName &Name, const VSShaderKey &Key, VSShader *pShader);
        VSShaderSet *GetShaderSet(const VSUsedName &Name);
        void DeleteShaderSet(const VSUsedName &Name);
        VSShader *GetShader(const VSUsedName &Name, const VSShaderKey &Key);
        void DeleteShader(const VSUsedName &Name, const VSShaderKey &Key);
        void Clear()
        {
            m_ShaderMap.Clear();
        }
        void GCResource()
        {
        }
        bool IsReleseAll()
        {
            return (!m_ShaderMap.GetNum());
        }
        VSString m_ShaderMapName;
    };

}
