#pragma once
#include "Reference.h"
#include "Priority.h"
#include "CustomArchiveObject.h"
#include "InitialMacro.h"

#include "Container/String.h"

namespace Matrix
{
	class MATRIX_FUNCTION_API VSName : public VSReference, public Core::MemoryObject
	{
	public:
		friend class VSResourceManager;
		~VSName();
		explicit VSName(const TCHAR* pChar, unsigned int uiID);
		explicit VSName(const Container::MString& String, unsigned int uiID);

		inline const TCHAR* GetBuffer()const
		{
			return m_String.GetBuffer();
		}
		inline const Container::MString& GetString()const
		{
			return m_String;
		}
		inline unsigned int GetLength()const
		{
			return m_String.GetLength();
		}

		inline unsigned int GetID()const
		{
			return m_uiID;
		}

	protected:

		unsigned int m_uiID;
		Container::MString  m_String;

	};
	DECLARE_Ptr(VSName);


	class VSStream;
	class MATRIX_FUNCTION_API VSUsedName : public VSCustomArchiveObject
	{
		//PRIORITY
		DECLARE_PRIORITY
	public:
		~VSUsedName();
		VSUsedName();
		/*explicit */VSUsedName(const TCHAR* pChar);
		/*explicit */VSUsedName(const Container::MString& String);

		//����=������
		void operator =(const Container::MString& String);
		void operator =(const TCHAR* pChar);
		void operator =(const VSUsedName& Name);
		inline const TCHAR* GetBuffer()const
		{
			if (!m_pName)
			{
				return NULL;
			}
			return m_pName->GetBuffer();
		}
		inline const Container::MString& GetString()const
		{
			if (!m_pName)
			{
				return Container::MString::ms_StringNULL;
			}
			return m_pName->GetString();
		}
		inline unsigned int GetLength()const
		{
			if (!m_pName)
			{
				return 0;
			}
			return m_pName->GetLength();
		}
		inline unsigned int GetNameCode()const
		{
			if (!m_pName)
			{
				return 0;
			}
			return m_pName->GetID();
		}
		inline const Container::MString& operator *() const
		{
			return GetString();
		}

		MATRIX_FUNCTION_API friend bool operator >(const VSUsedName& Name1, const VSUsedName& Name2);

		MATRIX_FUNCTION_API friend bool operator <(const VSUsedName& Name1, const VSUsedName& Name2);

		//����==������
		MATRIX_FUNCTION_API friend bool operator ==(const VSUsedName& Name1, const VSUsedName& Name2);

		//����!=������
		MATRIX_FUNCTION_API friend bool operator !=(const VSUsedName& Name1, const VSUsedName& Name2);

		//����==������
		MATRIX_FUNCTION_API friend bool operator ==(const VSUsedName& Name, const Container::MString& String);

		//����!=������
		MATRIX_FUNCTION_API friend bool operator !=(const VSUsedName& Name, const Container::MString& String);

		//����==������
		MATRIX_FUNCTION_API friend bool operator ==(const VSUsedName& Name, const TCHAR* pChar);

		//����!=������
		MATRIX_FUNCTION_API friend bool operator !=(const VSUsedName& Name, const TCHAR* pChar);

		virtual void Archive(VSStream& Stream);
		virtual void CopyFrom(VSCustomArchiveObject*, Container::MMap<VSObject*, VSObject*>& CloneMap);
	protected:
		VSNamePtr m_pName;

		DECLARE_INITIAL_ONLY
		static bool InitialDefaultState();
		static bool TerminalDefaultState();
	public:
		//Shader key
		static VSUsedName ms_cPassID;
		static VSUsedName ms_cPreZBeUsedBone;
		static VSUsedName ms_cUseInstance;
		static VSUsedName ms_cUseTessellation;
		static VSUsedName ms_cGPUMorphTarget;
		static VSUsedName ms_cMaterialVertexFormat;
		static VSUsedName ms_cVolumeVertexFormat;
		static VSUsedName ms_cLightFunKey;
		static VSUsedName ms_cMaterialLightKey;
		static VSUsedName ms_cLighted;
		static VSUsedName ms_cCubShadowFov;
		static VSUsedName ms_cPointLightShadowNum;
		static VSUsedName ms_cPointLightVolumeShadowNum;
		static VSUsedName ms_cPointLightParaboloidShadowNum;
		static VSUsedName ms_cDirectionLightShadowNum;
		static VSUsedName ms_cDirectionLightVolumeShadowNum;
		static VSUsedName ms_cDirectionLightCSMShadowNum;
		static VSUsedName ms_cSpotLightShadowNum;
		static VSUsedName ms_cBlinnPhong;
		static VSUsedName ms_cSimpleAnimInstanceLerp;
		static VSUsedName ms_cOrenNayarLookUpTable;

		//Inner Shader
		static VSUsedName ms_cVolumeShadowShader;
		static VSUsedName ms_cLightFunShader;
		static VSUsedName ms_cPostEffectShader;
		static VSUsedName ms_cPreZShader;
		static VSUsedName ms_cHullShader;

		//Custom Shader
		static VSUsedName ms_cPostGray;
		static VSUsedName ms_cGammaCorrect;
		static VSUsedName ms_cPostScreenQuad;
		static VSUsedName ms_cPostSaturation;
		static VSUsedName ms_cOldPhoto;
		static VSUsedName ms_cGuassBlurH;
		static VSUsedName ms_cGuassBlurV;
		static VSUsedName ms_cFilter3X3;
		static VSUsedName ms_cBright;
		static VSUsedName ms_cTexAdd;
		static VSUsedName ms_cPostVolumeShadowMap;

		//Shader Parameter
		static VSUsedName ms_cPostInputTexture[POSTEFFECT_MAX_INPUT];
		static VSUsedName ms_cPostInv_Width;
		static VSUsedName ms_cPostInv_Height;
		static VSUsedName ms_cTexOffsetAndWeight;
		static VSUsedName ms_cWorldViewProjectMatrix;
		static VSUsedName ms_cProjectShadowMatrix;
		static VSUsedName ms_cViewProjectMatrix;
		static VSUsedName ms_cWorldMatrix;

		//Only Name
		static VSUsedName ms_cMainScene;
		static VSUsedName ms_cPositionInfo;
		static VSUsedName ms_cClearColor;
		static VSUsedName ms_cDepth;

		static VSUsedName ms_cNULL;
	};
	CUSTOMTYPE_MARCO(VSUsedName)

}
