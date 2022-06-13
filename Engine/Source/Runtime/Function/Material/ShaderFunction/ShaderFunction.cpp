#include "ShaderFunction.h"
#include "Material.h"
#include "ShaderStringFactory.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
#include "LightShaderFunction.h"
using namespace Matrix;
IMPLEMENT_RTTI_NoCreateFun(VSShaderFunction, MObject)
    IMPLEMENT_INITIAL_NO_CLASS_FACTORY_BEGIN(VSShaderFunction)
        IMPLEMENT_INITIAL_NO_CLASS_FACTORY_END
    BEGIN_ADD_PROPERTY(VSShaderFunction, MObject)
        REGISTER_PROPERTY(m_ShowName, ShowName, VSProperty::F_SAVE_LOAD_CLONE)
            REGISTER_PROPERTY(m_pOwner, Owner, VSProperty::F_SAVE_LOAD_CLONE)
                REGISTER_PROPERTY(m_pInput, Input, VSProperty::F_SAVE_LOAD_CLONE)
                    REGISTER_PROPERTY(m_pOutput, Output, VSProperty::F_SAVE_LOAD_CLONE)
                        END_ADD_PROPERTY
    VSShaderFunction::VSShaderFunction()
{
    m_pInput.Clear();
    m_pOutput.Clear();
    m_bIsVisited = 0;
    m_pOwner = NULL;
}
VSShaderFunction::VSShaderFunction(const VSUsedName &ShowName, VSMaterial *pMaterial)
{
    m_bIsVisited = 0;
    m_ShowName = ShowName;
    m_pInput.Clear();
    m_pOutput.Clear();
    ENGINE_ASSERT(pMaterial);
    m_pOwner = pMaterial;
    m_pOwner->AddShaderFunction(this);
}
VSShaderFunction::~VSShaderFunction()
{
    for (unsigned int i = 0; i < m_pInput.GetNum(); i++)
    {
        VSMAC_DELETE(m_pInput[i]);
    }
    for (unsigned int i = 0; i < m_pOutput.GetNum(); i++)
    {
        VSMAC_DELETE(m_pOutput[i]);
    }
    m_pOwner->DeleteShaderFunction(this);
}
bool VSShaderFunction::GetInputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const
{
    if (!VSRenderer::ms_pRenderer)
        return 0;
    Container::MString Temp;
    for (unsigned int i = 0; i < m_pInput.GetNum(); i++)
    {

        if (m_pInput[i]->GetValueType() == VSPutNode::VT_1)
        {
            OutString += VSRenderer::ms_pRenderer->Float() + _T(" "); /*_T("VSREAL ");*/
            Temp = VSRenderer::ms_pRenderer->FloatConst(_T("0"));
        }
        else if (m_pInput[i]->GetValueType() == VSPutNode::VT_2)
        {
            OutString += VSRenderer::ms_pRenderer->Float2() + _T(" ");      /*_T("float2 ");*/
            Temp = VSRenderer::ms_pRenderer->Float2Const(_T("0"), _T("0")); /*_T("float2(0,0)");*/
        }
        else if (m_pInput[i]->GetValueType() == VSPutNode::VT_3)
        {
            OutString += VSRenderer::ms_pRenderer->Float3() + _T(" ");               /*_T("float3 ");*/
            Temp = VSRenderer::ms_pRenderer->Float3Const(_T("0"), _T("0"), _T("0")); /*_T("float3(0,0,0)");*/
        }
        else if (m_pInput[i]->GetValueType() == VSPutNode::VT_4)
        {
            OutString += VSRenderer::ms_pRenderer->Float4() + _T(" ");                        /*_T("float4 ");*/
            Temp = VSRenderer::ms_pRenderer->Float4Const(_T("0"), _T("0"), _T("0"), _T("1")); /*_T("float4(0,0,0,1)");*/
        }
        else
        {
            ENGINE_ASSERT(0);
        }
        if (!m_pInput[i]->GetOutputLink())
        {
            OutString += m_pInput[i]->GetNodeName().GetString() + _T(" = ") + Temp + _T(";\n");
            continue;
        }
        // 		if(m_pInput[i]->GetValueType() != m_pInput[i]->GetOutputLink()->GetValueType())
        // 			return 0;
        OutString += GetValueEqualString(m_pInput[i]->GetOutputLink(), m_pInput[i]); /*m_pInput[i]->GetNodeName() + _T(" = ") + m_pInput[i]->GetOutputLink()->GetNodeName() + _T(";\n");*/
    }
    return 1;
}
Container::MString VSShaderFunction::GetValueEqualString(const VSOutputNode *pOutputNode, const VSInputNode *pInputNode) const
{
    if (!pInputNode || !pOutputNode)
        return Container::MString();
    unsigned int uiMaxElement = pInputNode->GetValueType();
    if (uiMaxElement == pOutputNode->GetValueType())
    {

        return pInputNode->GetNodeName().GetString() + _T(" = ") + pOutputNode->GetNodeName().GetString() + _T(";\n");
    }

    Container::MString OutString;
    OutString = pInputNode->GetNodeName().GetString() + _T(" = ");
    Container::MString Value[4];
    unsigned int Mask[4];
    Mask[0] = VSRenderer::VE_R;
    Mask[1] = VSRenderer::VE_G;
    Mask[2] = VSRenderer::VE_B;
    Mask[3] = VSRenderer::VE_A;
    for (unsigned int i = 0; i < 4; i++)
    {
        if (i > pOutputNode->GetValueType())
        {
            Value[i] = VSRenderer::GetValueElement(pOutputNode, Mask[pOutputNode->GetValueType()]);
        }
        else
        {
            Value[i] = VSRenderer::GetValueElement(pOutputNode, Mask[i]);
        }
    }
    if (pInputNode->GetValueType() == VSPutNode::VT_1)
    {
        OutString += VSRenderer::ms_pRenderer->FloatConst(Value[0]);
    }
    else if (pInputNode->GetValueType() == VSPutNode::VT_2)
    {
        OutString += VSRenderer::ms_pRenderer->Float2Const(Value[0], Value[1]);
    }
    else if (pInputNode->GetValueType() == VSPutNode::VT_3)
    {
        OutString += VSRenderer::ms_pRenderer->Float3Const(Value[0], Value[1], Value[2]);
    }
    else if (pInputNode->GetValueType() == VSPutNode::VT_4)
    {
        OutString += VSRenderer::ms_pRenderer->Float4Const(Value[0], Value[1], Value[2], Value[3]);
    }
    else
        return Container::MString();
    OutString += _T(";\n");
    return OutString;
}
bool VSShaderFunction::GetOutputValueString(Container::MString &OutString, MaterialShaderPara &MSPara) const
{
    if (!VSRenderer::ms_pRenderer)
        return 0;
    Container::MString Temp;
    for (unsigned int i = 0; i < m_pOutput.GetNum(); i++)
    {

        if (m_pOutput[i]->GetValueType() == VSPutNode::VT_1)
        {
            OutString += VSRenderer::ms_pRenderer->Float() + _T(" "); /*_T("VSREAL ");*/
            Temp = VSRenderer::ms_pRenderer->FloatConst(_T("0"));
        }
        else if (m_pOutput[i]->GetValueType() == VSPutNode::VT_2)
        {
            OutString += VSRenderer::ms_pRenderer->Float2() + _T(" "); /*_T("float2 ")*/
            ;
            Temp = VSRenderer::ms_pRenderer->Float2Const(_T("0"), _T("0")); /*_T("float2(0,0)");*/
        }
        else if (m_pOutput[i]->GetValueType() == VSPutNode::VT_3)
        {
            OutString += VSRenderer::ms_pRenderer->Float3() + _T(" ");               /*_T("float3 ");*/
            Temp = VSRenderer::ms_pRenderer->Float3Const(_T("0"), _T("0"), _T("0")); /*_T("float3(0,0,0)");*/
        }
        else if (m_pOutput[i]->GetValueType() == VSPutNode::VT_4)
        {
            OutString += VSRenderer::ms_pRenderer->Float4() + _T(" ");                        /*_T("float4 ");*/
            Temp = VSRenderer::ms_pRenderer->Float4Const(_T("0"), _T("0"), _T("0"), _T("1")); /*_T("float4(0,0,0,1)");*/
        }
        else
            return 0;

        OutString += m_pOutput[i]->GetNodeName().GetString() + _T(" = ") + Temp + _T(";\n");
    }
    return 1;
}
bool VSShaderFunction::GetShaderTreeString(Container::MString &OutString, MaterialShaderPara &MSPara)
{
    if (m_bIsVisited == 1)
        return 1;
    else
    {
        m_bIsVisited = 1;
        for (unsigned int i = 0; i < m_pInput.GetNum(); i++)
        {
            if (m_pInput[i]->GetOutputLink() == NULL)
                continue;
            else
            {
                ((VSShaderFunction *)m_pInput[i]->GetOutputLink()->GetOwner())->GetShaderTreeString(OutString, MSPara);
            }
        }
        if (!ResetValueType(MSPara))
        {
            return 0;
        }
        if (!GetInputValueString(OutString, MSPara))
            return 0;
        if (!GetOutputValueString(OutString, MSPara))
            return 0;
        if (!GetFunctionString(OutString, MSPara))
            return 0;
        return 1;
    }
}
bool VSShaderFunction::ClearShaderTreeStringFlag()
{
    if (m_bIsVisited == 0)
        return 1;
    else
    {
        m_bIsVisited = 0;
        for (unsigned int i = 0; i < m_pInput.GetNum(); i++)
        {
            if (m_pInput[i]->GetOutputLink() == NULL)
                continue;
            else
            {
                ((VSShaderFunction *)m_pInput[i]->GetOutputLink()->GetOwner())->ClearShaderTreeStringFlag();
            }
        }
        return 1;
    }
}
VSInputNode *VSShaderFunction::GetInputNode(unsigned int uiNodeID) const
{
    // ENGINE_ASSERT(uiNodeID < m_pInput.GetNum());
    if (uiNodeID >= m_pInput.GetNum())
    {
        return NULL;
    }
    return m_pInput[uiNodeID];
}
VSInputNode *VSShaderFunction::GetInputNode(const Container::MString &NodeName) const
{
    for (unsigned int i = 0; i < m_pInput.GetNum(); i++)
    {
        if (m_pInput[i]->GetNodeName() == NodeName)
            return m_pInput[i];
    }
    return NULL;
}

VSOutputNode *VSShaderFunction::GetOutputNode(unsigned int uiNodeID) const
{
    ENGINE_ASSERT(uiNodeID < m_pOutput.GetNum());
    return m_pOutput[uiNodeID];
}
VSOutputNode *VSShaderFunction::GetOutputNode(const Container::MString &NodeName) const
{
    for (unsigned int i = 0; i < m_pOutput.GetNum(); i++)
    {
        if (m_pOutput[i]->GetNodeName() == NodeName)
            return m_pOutput[i];
    }
    return NULL;
}
bool VSShaderFunction::IsValidNodeToThis(VSShaderFunction *pShaderFunction, MaterialShaderPara &MSPara)
{
    if (pShaderFunction == this)
    {
        return false;
    }
    return true;
}
bool VSShaderFunction::GetAllChildNode(Container::MArray<VSShaderFunction *> &ChildNodeArray, MaterialShaderPara &MSPara)
{

    for (unsigned int i = 0; i < m_pInput.GetNum(); i++)
    {
        if (m_pInput[i]->GetOutputLink())
        {
            VSShaderFunction *pOwner = (VSShaderFunction *)m_pInput[i]->GetOutputLink()->GetOwner();
            bool bFind = false;
            for (unsigned int j = 0; j < ChildNodeArray.GetNum(); j++)
            {
                if (ChildNodeArray[j] == pOwner)
                {
                    bFind = true;
                }
            }
            if (!bFind)
            {
                ChildNodeArray.AddElement(pOwner);
                pOwner->GetAllChildNode(ChildNodeArray, MSPara);
            }
        }
    }
    return ChildNodeArray.GetNum() > 0;
}
bool VSShaderFunction::CheckChildNodeValidToThis(Container::MArray<VSShaderFunction *> &NoValidShaderFunctionArray, MaterialShaderPara &MSPara)
{
    Container::MArray<VSShaderFunction *> ChildNodeArray;
    if (GetAllChildNode(ChildNodeArray, MSPara))
    {
        for (unsigned int i = 0; i < ChildNodeArray.GetNum(); i++)
        {
            if (!IsValidNodeToThis(ChildNodeArray[i], MSPara))
            {
                NoValidShaderFunctionArray.AddElement(ChildNodeArray[i]);
            }
        }
    }

    return NoValidShaderFunctionArray.GetNum() == 0;
}
bool VSShaderFunction::CheckChildNodeValidAll(Container::MMap<VSShaderFunction *, Container::MArray<VSShaderFunction *>> &NoValidMap, MaterialShaderPara &MSPara)
{
    Container::MArray<VSShaderFunction *> NoValidShaderFunctionArray;
    if (!CheckChildNodeValidToThis(NoValidShaderFunctionArray, MSPara))
    {
        NoValidMap.AddElement(this, NoValidShaderFunctionArray);
    }
    for (unsigned int i = 0; i < m_pInput.GetNum(); i++)
    {
        if (m_pInput[i]->GetOutputLink())
        {
            VSShaderFunction *pOwner = (VSShaderFunction *)m_pInput[i]->GetOutputLink()->GetOwner();
            if (pOwner == this)
            {
                ENGINE_ASSERT(0);
                return false;
            }
            pOwner->CheckChildNodeValidAll(NoValidMap, MSPara);
        }
    }

    return NoValidMap.GetNum() == 0;
}
bool VSShaderFunction::HaveThisChild(VSShaderFunction *pShaderFunction, MaterialShaderPara &MSPara)
{
    for (unsigned int i = 0; i < m_pInput.GetNum(); i++)
    {
        if (m_pInput[i]->GetOutputLink())
        {
            VSShaderFunction *pOwner = (VSShaderFunction *)m_pInput[i]->GetOutputLink()->GetOwner();
            if (pShaderFunction == pOwner)
            {
                return true;
            }
            else
            {
                if (pOwner->HaveThisChild(pShaderFunction, MSPara) == true)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
void VSShaderFunction::GetNoLightFunctionParentNode(Container::MArray<VSShaderFunction *> &NoLightFunctionParentNodeArray, MaterialShaderPara &MSPara)
{
    Container::MArray<VSShaderFunction *> ChildNodeArray;
    GetAllChildNode(ChildNodeArray, MSPara);

    bool bHaveLightNode = false;
    for (unsigned int i = 0; i < ChildNodeArray.GetNum(); i++)
    {
        VSShaderFunction *pShaderFunction = ChildNodeArray[i];
        if (pShaderFunction->GetType().IsSameType(VSLightDir::ms_Type) || pShaderFunction->GetType().IsSameType(VSLightColor::ms_Type) || pShaderFunction->GetType().IsSameType(VSLightSpecular::ms_Type))
        {
            bHaveLightNode = true;
            break;
        }
    }
    if (!bHaveLightNode)
    {
        if (GetType().IsSameType(VSLightDir::ms_Type) || GetType().IsSameType(VSLightColor::ms_Type) || GetType().IsSameType(VSLightSpecular::ms_Type))
        {
            return;
        }
        else
        {
            NoLightFunctionParentNodeArray.AddElement(this);
        }
        return;
    }
    for (unsigned int i = 0; i < m_pInput.GetNum(); i++)
    {
        if (m_pInput[i]->GetOutputLink())
        {
            VSShaderFunction *pOwner = (VSShaderFunction *)m_pInput[i]->GetOutputLink()->GetOwner();
            if (pOwner)
            {
                pOwner->GetNoLightFunctionParentNode(NoLightFunctionParentNodeArray, MSPara);
            }
        }
    }
}
bool VSShaderFunction::ResetValueType(MaterialShaderPara &MSPara)
{
    return true;
}
