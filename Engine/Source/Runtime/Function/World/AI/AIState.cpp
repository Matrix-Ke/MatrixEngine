#include "AIState.h"
#include "Actor.h"
#include "GraphicInclude.h"
using namespace Matrix;
IMPLEMENT_RTTI_NoCreateFun(VSAIState, VSObject) bool VSAIState::HandleMessage(VSMessage &Message)
{
    return true;
}
bool VSAIState::Update(double Time)
{
    for (unsigned int i = 0; i < m_pStateInputNode.GetNum(); i++)
    {
        if (m_pStateInputNode[i]->CheckState())
        {
            const VSOutputNode *pOutputNode = m_pStateInputNode[i]->GetOutputLink();
            if (!pOutputNode)
            {
                continue;
            }
            VSAIState *pState = DynamicCast<VSAIState>(pOutputNode->GetOwner());
            if (pState)
            {
                pState->m_pOwner->ChangeState(pState);
            }
            break;
        }
    }
    return true;
}