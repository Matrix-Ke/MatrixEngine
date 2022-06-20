#pragma once
#include "Core/Resource.h"
#include "Render/Renderer.h"
namespace Matrix
{
	DECLARE_Ptr(VSShader);
	DECLARE_Ptr(VSShaderKey);
	typedef Container::MMapOrder<VSShaderKey, VSShaderPtr> VSShaderSet;
	class MATRIX_FUNCTION_API VSShaderMapCache : public VSCacheResource
	{
		// RTTI
		DECLARE_RTTI;
		DECLARE_INITIAL
		DECLARE_CACHE_RESOURCE(CacheShader, Resource / Shader, Cache / Shader, true, false)

	public:
		VSShaderMapCache() {}
		~VSShaderMapCache() {}
		Container::MMapOrder<VSUsedName, VSShaderSet> m_ShaderMap;
	};
	DECLARE_Ptr(VSShaderMapCache);
	VSTYPE_MARCO(VSShaderMapCache);

	/*
	着色器映射（shader map）表是用来管理着色器和着色器键关系的集合;一段着色器代码可能根据不同的着色器键编译出很多个着色器字节码
	m_ShaderMap 中一个名字对应一个 VSShaderSet类，一般名字是着色器代码的文件名或者保证名字唯一即可。VSShaderSet 类里保存了所有着色器键对应的着色器字节码
	*/
	class MATRIX_FUNCTION_API VSShaderMap
	{

	public:
		VSShaderMap(Container::MString ShaderMapName);
		~VSShaderMap();

	protected:
		Container::MMapOrder<VSUsedName, VSShaderSet> m_ShaderMap;

	public:
		Container::MMapOrder<VSUsedName, VSShaderSet>& GetShaderMap()
		{
			return m_ShaderMap;
		}
		void SetShader(const VSUsedName& Name, const VSShaderKey& Key, VSShader* pShader);
		VSShaderSet* GetShaderSet(const VSUsedName& Name);
		void DeleteShaderSet(const VSUsedName& Name);
		VSShader* GetShader(const VSUsedName& Name, const VSShaderKey& Key);
		void DeleteShader(const VSUsedName& Name, const VSShaderKey& Key);
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
		Container::MString m_ShaderMapName;
	};

}
