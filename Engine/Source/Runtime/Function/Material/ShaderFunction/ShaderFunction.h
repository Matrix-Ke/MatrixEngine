#pragma once
#include "Core/Object.h"
#include "Core/PutNode.h"
#include "Core/Meta/ObjName.h"
#include "Container/BitArray.h"
#include "Material/Shader/ShaderKey.h"
namespace Matrix
{
	class VSMaterial;
	class MStream;
	class VSShaderMainFunction;
	class MATRIX_FUNCTION_API VSShaderFunction : public MObject
	{
		// RTTI
		DECLARE_RTTI;
		DECLARE_INITIAL_NO_CLASS_FACTORY;

	public:
		virtual ~VSShaderFunction() = 0;

	protected:
		VSUsedName m_ShowName;
		VSShaderFunction(const VSUsedName& ShowName, VSMaterial* pMaterial);
		VSShaderFunction();
		Container::MArray<VSInputNode*> m_pInput;
		Container::MArray<VSOutputNode*> m_pOutput;
		VSMaterial* m_pOwner;
		bool m_bIsVisited;
		inline void SetOwner(VSMaterial* pOwner)
		{
			ENGINE_ASSERT(pOwner);
			m_pOwner = pOwner;
		}

	public:
		friend class VSMaterial;
		virtual bool IsHaveOutput()
		{
			if (m_pOutput.GetNum() > 0)
			{
				return m_pOutput[0]->IsConnection();
			}
			return false;
		}
		virtual void ResetInShaderName(MaterialShaderPara& MSPara) = 0;   
		/*
		GetInputValueString 函数的作用是让图形节点的输入变成临时变量，然后等于连接它的图形节点的输出。里进行了一些容错的处理，
		如果图形节点的输入和连接它的图形节点的输出类型不同，则会进行一个转换
		*/
		virtual bool GetInputValueString(Container::MString& OutString, MaterialShaderPara& MSPara) const;
		virtual bool GetOutputValueString(Container::MString& OutString, MaterialShaderPara& MSPara) const;
		virtual bool GetFunctionString(Container::MString& OutString, MaterialShaderPara& MSPara) const = 0;
		//GetShaderTreeString 函数递归就可以得到整个表达式的代码
		bool GetShaderTreeString(Container::MString& OutString, MaterialShaderPara& MSPara);
		bool ClearShaderTreeStringFlag();

		VSInputNode* GetInputNode(unsigned int uiNodeID) const;
		VSInputNode* GetInputNode(const Container::MString& NodeName) const;
		inline unsigned int GetInputNodeNum() const
		{
			return m_pInput.GetNum();
		}
		VSOutputNode* GetOutputNode(unsigned int uiNodeID) const;
		VSOutputNode* GetOutputNode(const Container::MString& NodeName) const;
		inline unsigned int GetOutputNodeNum() const
		{
			return m_pOutput.GetNum();
		}
		inline const VSUsedName& GetShowName() const
		{
			return m_ShowName;
		}

		Container::MString GetValueEqualString(const VSOutputNode* pOutputNode, const VSInputNode* pInputNode) const;

		virtual bool IsValidNodeToThis(VSShaderFunction* pShaderFunction, MaterialShaderPara& MSPara);

		virtual bool CheckChildNodeValidToThis(Container::MArray<VSShaderFunction*>& NoValidShaderFunctionArray, MaterialShaderPara& MSPara);

		virtual bool GetAllChildNode(Container::MArray<VSShaderFunction*>& ChildNodeArray, MaterialShaderPara& MSPara);

		virtual bool CheckChildNodeValidAll(Container::MMap<VSShaderFunction*, Container::MArray<VSShaderFunction*>>& NoValidMap, MaterialShaderPara& MSPara);

		virtual bool HaveThisChild(VSShaderFunction* pShaderFunction, MaterialShaderPara& MSPara);

		virtual void GetNoLightFunctionParentNode(Container::MArray<VSShaderFunction*>& ChildNodeArray, MaterialShaderPara& MSPara);

		virtual bool ResetValueType(MaterialShaderPara& MSPara);
	};
	DECLARE_Ptr(VSShaderFunction);
	VSTYPE_MARCO(VSShaderFunction);
}
