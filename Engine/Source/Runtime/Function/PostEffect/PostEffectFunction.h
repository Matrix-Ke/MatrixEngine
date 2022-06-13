#pragma once
#include "Core/Object.h"
#include "PutNode.h"
#include "Core/Meta/ObjName.h"
#include "SceneRender.h"
namespace Matrix
{
    class MStream;
    class MATRIX_FUNCTION_API VSPostEffectFunction : public MObject
    {
        // RTTI
        DECLARE_RTTI;
        DECLARE_INITIAL_NO_CLASS_FACTORY
    public:
        virtual ~VSPostEffectFunction() = 0;
        friend class VSPostEffectSet;

    protected:
        VSUsedName m_ShowName;
        VSPostEffectFunction(const VSUsedName &ShowName, VSPostEffectSet *pPostEffectSet);
        VSPostEffectFunction();
        Container::MArray<VSInputNode *> m_pInput;
        Container::MArray<VSOutputNode *> m_pOutput;
        VSPostEffectSet *m_pOwner;
        bool m_bIsVisited;
        inline void SetOwner(VSPostEffectSet *pOwner)
        {
            ENGINE_ASSERT(pOwner);
            m_pOwner = pOwner;
        }

        VSPostEffectSceneRenderPtr m_pPostEffectRender;

        virtual VSPostEffectSceneRender *CreateSceneRender() = 0;
        virtual void OnDraw(VSCuller &Culler, double dAppTime) = 0;

    public:
        friend class VSPostEffectSet;

        bool ClearFlag();

        VSInputNode *GetInputNode(unsigned int uiNodeID) const;
        VSInputNode *GetInputNode(const Container::MString &NodeName) const;

        VSOutputNode *GetOutputNode(unsigned int uiNodeID) const;
        VSOutputNode *GetOutputNode(const Container::MString &NodeName) const;

        inline const VSUsedName &GetShowName() const
        {
            return m_ShowName;
        }
        virtual VSRenderTarget *GetMainColorOutputRenderTarget()
        {
            if (m_pOutput.GetNum() > 0)
            {
                if (m_pOutput[0])
                {
                    return GetRenderTarget(m_pOutput[0]);
                }
            }
            return NULL;
        }
        virtual VSRenderTarget *GetMainColorInputRenderTarget()
        {
            if (m_pInput.GetNum() > 0)
            {
                if (m_pInput[0])
                {
                    return GetRenderTarget(m_pInput[0]);
                }
            }
            return NULL;
        }
        //取自己节点
        virtual VSRenderTarget *GetRenderTarget(const VSOutputNode *pPutNode)
        {
            for (unsigned int i = 0; i < m_pOutput.GetNum(); i++)
            {
                if (pPutNode == m_pOutput[i])
                {
                    return m_pPostEffectRender->GetRenderTarget(i);
                }
            }
            return NULL;
        }

        //取链接的那个节点
        virtual VSRenderTarget *GetRenderTarget(const VSInputNode *pPutNode)
        {
            if (pPutNode->GetOutputLink())
            {
                VSPostEffectFunction *pPostEffectFunc = (VSPostEffectFunction *)pPutNode->GetOutputLink()->GetOwner();
                if (pPostEffectFunc)
                {
                    if (pPostEffectFunc->m_bEnable)
                    {
                        VSRenderTarget *pRenderTarget = pPostEffectFunc->GetRenderTarget(pPutNode->GetOutputLink());
                        return pRenderTarget;
                    }
                    else
                    {
                        return pPostEffectFunc->GetMainColorInputRenderTarget();
                    }
                }
                else
                {
                    return NULL;
                }
            }
            else
            {
                return NULL;
            }
        }
        virtual void TryToDisableRT()
        {
            for (unsigned int i = 0; i < m_pInput.GetNum(); i++)
            {
                if (m_pInput[i]->GetOutputLink())
                {
                    VSPostEffectFunction *pPostEffectFunc = (VSPostEffectFunction *)m_pInput[i]->GetOutputLink()->GetOwner();
                    if (pPostEffectFunc)
                    {
                        pPostEffectFunc->TryToDisableRT();
                    }
                }
            }
            if (!m_pPostEffectRender)
            {
                return;
            }
            Container::MArray<VSPostEffectFunction *> Out;
            GetValidLinkOutputPostEffectFunction(Out);
            bool CanDisableRT = false;
            unsigned int k = 0;
            for (; k < Out.GetNum(); k++)
            {
                if (!Out[k]->m_bIsVisited)
                {
                    break;
                }
            }
            if (k == Out.GetNum())
            {
                CanDisableRT = true;
            }

            if (m_bEnable && CanDisableRT)
            {
                m_pPostEffectRender->DisableRT();
            }
        }
        virtual void DisableRT()
        {
            for (unsigned int i = 0; i < m_pInput.GetNum(); i++)
            {
                if (m_pInput[i]->GetOutputLink())
                {
                    VSPostEffectFunction *pPostEffectFunc = (VSPostEffectFunction *)m_pInput[i]->GetOutputLink()->GetOwner();
                    if (pPostEffectFunc)
                    {
                        pPostEffectFunc->TryToDisableRT();
                    }
                }
            }
        }
        virtual void Draw(VSCuller &Culler, double dAppTime)
        {
            if (m_bIsVisited == 1)
            {
                return;
            }
            m_bIsVisited = 1;

            for (unsigned int i = 0; i < m_pInput.GetNum(); i++)
            {
                if (m_pInput[i]->GetOutputLink())
                {
                    VSPostEffectFunction *pPostEffectFunc = (VSPostEffectFunction *)m_pInput[i]->GetOutputLink()->GetOwner();
                    if (pPostEffectFunc)
                    {
                        pPostEffectFunc->Draw(Culler, dAppTime);
                    }
                }
            }
            if (m_bEnable && m_pPostEffectRender)
            {
                m_pPostEffectRender->GetRT(m_pOwner->GetCurRTWidth(), m_pOwner->GetCurRTHeight());
                OnDraw(Culler, dAppTime);
                DisableRT();
            }
        }
        void VSPostEffectFunction::GetValidLinkOutputPostEffectFunction(Container::MArray<VSPostEffectFunction *> &Out)
        {
            for (unsigned int i = 0; i < m_pOutput.GetNum(); i++)
            {
                if (m_pOutput[i])
                {
                    for (unsigned int j = 0; j < m_pOutput[i]->GetInputNum(); j++)
                    {
                        VSInputNode *pInputNode = m_pOutput[i]->GetInputLink(j);
                        VSPostEffectFunction *pPostEffectFunction = (VSPostEffectFunction *)pInputNode->GetOwner();
                        if (pPostEffectFunction->m_bEnable)
                        {
                            Out.AddElement(pPostEffectFunction);
                        }
                        else
                        {
                            pPostEffectFunction->GetValidLinkOutputPostEffectFunction(Out);
                        }
                    }
                }
            }
        }

    public:
        bool m_bEnable;
    };
    DECLARE_Ptr(VSPostEffectFunction);
    VSTYPE_MARCO(VSPostEffectFunction);
#include "VSPostEffect.marc"
}