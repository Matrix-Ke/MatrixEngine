#pragma once
#include "Core/Object.h"
#include "Material/Shader/ShaderMap.h"
#include "Material/Shader/ShaderKey.h"
#include "Material/Shader/PShader.h"
#include "Material/Shader/Shader.h"
#include "Material/Shader/GShader.h"
#include "Material/Shader/DShader.h"
#include "Material/Shader/HShader.h"
#include "Material/Shader/CShader.h"
#include "Math/Matrix4.h"


namespace Matrix
{
	class VSSpatial;
	class VSCamera;
	class MATRIX_FUNCTION_API VSPass : public MObject
	{
		// RTTI
		DECLARE_RTTI;
		DECLARE_INITIAL_NO_CLASS_FACTORY
		enum // pass type
		{
			PT_MATERIAL, //材质光照
			PT_INDIRECT, //间接光
			PT_NORMALDEPTH, //深度和法线
			PT_PREZ,
			PT_POINT_CUBE_SHADOW, //点光源立方体阴影
			PT_SHADOW, //普通阴影
			PT_DUAL_PARABOLOID_SHADOW, //点光源双面阴影
			PT_POINT_VOLUME_SHADOW, //点光源阴影体
			PT_DIRECT_VOLUME_SHADOW, //方向光阴影体
			PT_LIGHT_FUNCTION, //光照投射
			PT_POSTEFFECT, //后期效果
			PT_MAX
		};

	public:
		virtual ~VSPass() = 0;

	protected:
		VSPass();
		VSShaderSet* m_pVShaderSet;
		VSShaderKey m_VShaderkey;

		VSShaderSet* m_pPShaderSet;
		VSShaderKey m_PShaderkey;

		VSShaderSet* m_pGShaderSet;
		VSShaderKey m_GShaderkey;

		VSShaderSet* m_pHShaderSet;
		VSShaderKey m_HShaderkey;

		VSShaderSet* m_pDShaderSet;
		VSShaderKey m_DShaderkey;
		MaterialShaderPara MSPara;

	public:
		inline void SetDrawContent(VSMaterialInstance* pMaterialInstance, VSGeometry* pGeometry,
			VSCamera* pCamera, unsigned int uiPassId)
		{
			MSPara.pCamera = pCamera;
			MSPara.pGeometry = pGeometry;
			MSPara.pMaterialInstance = pMaterialInstance;
			MSPara.uiPassId = uiPassId;
			MSPara.uiPassType = GetPassType();
		}
		virtual bool Draw(VSRenderer* pRenderer) = 0;
		virtual unsigned int GetPassType() = 0;
		/*
		GetXShader函数可以得到渲染用的着色器字节码
		*/
		bool GetPShader(VSShaderMap& ShaderMap, const VSUsedName& Name);
		bool GetVShader(VSShaderMap& ShaderMap, const VSUsedName& Name);
		bool GetGShader(VSShaderMap& ShaderMap, const VSUsedName& Name);
		bool GetHShader(VSShaderMap& ShaderMap, const VSUsedName& Name);
		bool GetDShader(VSShaderMap& ShaderMap, const VSUsedName& Name);
	};
	DECLARE_Ptr(VSPass);
	VSTYPE_MARCO(VSPass);
}
