#pragma once
//#include "Core/Meta/ObjName.h"
//#include "Node/NodeComponent/Light/Light.h"

#include "Core/Meta/ObjName.h"
#include "Node/NodeComponent/Light/Light.h"

#include "Math/Vector4.h"

namespace Matrix
{
	class VSGeometry;
	class VSVertexBuffer;
	class MStream;
	DECLARE_Ptr(VSGeometry);
	DECLARE_Ptr(VSVertexBuffer);
	DECLARE_Ptr(VSMaterialInstance);
	DECLARE_Ptr(VSLight);

	struct MaterialShaderPara
	{
		MaterialShaderPara()
		{
			pGeometry = NULL;
			pShadowLight = NULL;
			pCamera = NULL;
			pMaterialInstance = NULL;
			LightArray.Clear();
			uiPassId = 0;
			uiCompileShaderType = VSEngineFlag::ST_MAX;
			bUseTessellation = false;
		}
		~MaterialShaderPara()
		{
			pGeometry = NULL;
			pShadowLight = NULL;
			pCamera = NULL;
			pMaterialInstance = NULL;
			LightArray.Clear();
			uiPassId = 0;
		}
		VSCamera* pCamera;
		VSMaterialInstance* pMaterialInstance;
		Container::MArray<VSLight*> LightArray;
		unsigned int uiPassId;
		unsigned int uiPassType;
		VSGeometry* pGeometry;
		VSLight* pShadowLight;
		Container::MString VSShaderPath;
		Container::MString PSShaderPath;
		Container::MString GSShaderPath;
		Container::MString HSShaderPath;
		Container::MString DSShaderPath;

		Container::MString VMainFunName;
		Container::MString PMainFunName;
		Container::MString GMainFunName;
		Container::MString HMainFunName;
		Container::MString DMainFunName;
		Math::ColorRGBA SkyLightUpColor;
		Math::ColorRGBA SkyLightDownColor;
		unsigned int uiCompileShaderType;
		bool bUseTessellation;
	};
	class MStream;
	class MATRIX_FUNCTION_API VSShaderKey : public MObject
	{

		DECLARE_RTTI;
		DECLARE_INITIAL
	public:
		VSShaderKey();
		~VSShaderKey();

	protected:
		Container::MMapOrder<VSUsedName, unsigned int> m_KeyMap;

	public:
		enum
		{

			MAX_LIGTH_TYPE_MASK = 3,
			MAX_LIGHT_TYPE_NUM = (1 << MAX_LIGTH_TYPE_MASK) - 1
		};
		bool IsHaveTheKey(const VSUsedName& Name, unsigned int& uiKeyId);
		void SetTheKey(const VSUsedName& Name, unsigned int Value);

	public:
		static bool InitialDefaultState();
		static bool TerminalDefaultState();

		static void SetMaterialVShaderKey(VSShaderKey* pKey, MaterialShaderPara& MSPara);

		static void SetMaterialPShaderKey(VSShaderKey* pKey, MaterialShaderPara& MSPara);

		static void SetMaterialGShaderKey(VSShaderKey* pKey, MaterialShaderPara& MSPara);

		static void SetMaterialHShaderKey(VSShaderKey* pKey, MaterialShaderPara& MSPara);

		static void SetMaterialDShaderKey(VSShaderKey* pKey, MaterialShaderPara& MSPara);
		struct ShadowKeyInfo
		{
			ShadowKeyInfo()
			{
				uiShadowNum = 0;
				uiVolumeShadowNum = 0;
				uiDualParaboloidShadowNum = 0;
				uiCSMShadowNum = 0;
			}
			unsigned int uiShadowNum;
			unsigned int uiVolumeShadowNum;
			unsigned int uiDualParaboloidShadowNum;
			unsigned int uiCSMShadowNum;
		};
		static unsigned int GenerateKey(const Container::MArray<VSLight*>& LightArray, ShadowKeyInfo ShadowInfo[VSLight::LT_MAX], unsigned int& uiLightFunctionKey);

		static unsigned int GetLightNum(unsigned int uiLightKey, unsigned int uiLightType);

		MATRIX_FUNCTION_API friend bool operator==(const VSShaderKey& Key1, const VSShaderKey& Key2);
		MATRIX_FUNCTION_API friend bool operator>(const VSShaderKey& Key1, const VSShaderKey& Key2);
		MATRIX_FUNCTION_API friend bool operator<(const VSShaderKey& Key1, const VSShaderKey& Key2);

		//ÖØÔØ=²Ù×÷·û
		void operator=(const VSShaderKey& ShaderKey);

		void GetDefine(Container::MMap<Container::MString, Container::MString>& Define);

		void Clear();
		static VSPointer<VSShaderKey> ms_NULLShaderKey;
	};
	VSTYPE_MARCO(VSShaderKey);
}
