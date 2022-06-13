#include "PEBeginFunction.h"
#include "Core/GraphicInclude.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSPEBeginFunction, VSPostEffectFunction)
BEGIN_ADD_PROPERTY(VSPEBeginFunction, VSPostEffectFunction)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSPEBeginFunction)
IMPLEMENT_INITIAL_END
VSPostEffectSceneRender *VSPEBeginFunction::CreateSceneRender()
{
    return NULL;
}
void VSPEBeginFunction::OnDraw(VSCuller &Culler, double dAppTime)
{
}
VSPEBeginFunction::VSPEBeginFunction(const VSUsedName &ShowName, VSPostEffectSet *pPostEffectSet)
    : VSPostEffectFunction(ShowName, pPostEffectSet)
{

    VSOutputNode *pOutNode = NULL;
    pOutNode = MX_NEW VSOutputNode(VSPutNode::PET_OUT, _T("OutColor"), this);
    ENGINE_ASSERT(pOutNode);
    m_pOutput.AddElement(pOutNode);
    m_pBeginTargetArray = NULL;
}
VSPEBeginFunction::~VSPEBeginFunction()
{
    m_pBeginTargetArray = NULL;
}
VSPEBeginFunction::VSPEBeginFunction()
{
    m_pBeginTargetArray = NULL;
}