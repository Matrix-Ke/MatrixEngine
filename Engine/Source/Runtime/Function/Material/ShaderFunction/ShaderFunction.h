#pragma once
#include "Core/Object.h"
#include "PutNode.h"
#include "Core/Meta/ObjName.h"
#include "BitArray.h"
#include "ShaderKey.h"
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
        VSShaderFunction(const VSUsedName &ShowName, VSMaterial *pMaterial);
        VSShaderFunction();
        Container::MArray<VSInputNode *> m_pInput;
        Container::MArray<VSOutputNode *> m_pOutput;
        VSMaterial *m_pOwner;
        bool m_bIsVisited;
        inline void SetOwner(VSMaterial *pOwner)
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
        virtual void ResetInShaderName(MaterialShaderPara &MSPara) = 0;
        virtual bool GetInputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual bool GetOutputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const;
        virtual bool GetFunctionString(Container::MString &OutString, MaterialShaderPara &MSPara) const = 0;
        bool GetShaderTreeString(Container::MString &OutString, MaterialShaderPara &MSPara);
        bool ClearShaderTreeStringFlag();

        VSInputNode *GetInputNode(unsigned int uiNodeID) const;
        VSInputNode *GetInputNode(const Container::MString &NodeName) const;
        inline unsigned int GetInputNodeNum() const
        {
            return m_pInput.GetNum();
        }
        VSOutputNode *GetOutputNode(unsigned int uiNodeID) const;
        VSOutputNode *GetOutputNode(const Container::MString &NodeName) const;
        inline unsigned int GetOutputNodeNum() const
        {
            return m_pOutput.GetNum();
        }
        inline const VSUsedName &GetShowName() const
        {
            return m_ShowName;
        }

        Container::MString GetValueEqualString(const VSOutputNode *pOutputNode, const VSInputNode *pInputNode) const;

        virtual bool IsValidNodeToThis(VSShaderFunction *pShaderFunction, MaterialShaderPara &MSPara);

        virtual bool CheckChildNodeValidToThis(Container::MArray<VSShaderFunction *> &NoValidShaderFunctionArray, MaterialShaderPara &MSPara);

        virtual bool GetAllChildNode(Container::MArray<VSShaderFunction *> &ChildNodeArray, MaterialShaderPara &MSPara);

        virtual bool CheckChildNodeValidAll(Container::MMap<VSShaderFunction *, Container::MArray<VSShaderFunction *>> &NoValidMap, MaterialShaderPara &MSPara);

        virtual bool HaveThisChild(VSShaderFunction *pShaderFunction, MaterialShaderPara &MSPara);

        virtual void GetNoLightFunctionParentNode(Container::MArray<VSShaderFunction *> &ChildNodeArray, MaterialShaderPara &MSPara);

        virtual bool ResetValueType(MaterialShaderPara &MSPara);
    };
    DECLARE_Ptr(VSShaderFunction);
    VSTYPE_MARCO(VSShaderFunction);
}
