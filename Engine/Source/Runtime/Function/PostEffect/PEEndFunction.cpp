#include "PEEndFunction.h"
#include "Core/GraphicInclude.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSPEEndFunction, VSPostEffectFunction)
BEGIN_ADD_PROPERTY(VSPEEndFunction, VSPostEffectFunction)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSPEEndFunction)
IMPLEMENT_INITIAL_END
VSPostEffectSceneRender *VSPEEndFunction::CreateSceneRender()
{
    return NULL;
}
void VSPEEndFunction::OnDraw(VSCuller &Culler, double dAppTime)
{
    return;
}
VSPEEndFunction::VSPEEndFunction(const VSUsedName &ShowName, VSPostEffectSet *pPostEffectSet)
    : VSPostEffectFunction(ShowName, pPostEffectSet)
{

    VSInputNode *pInputNode = NULL;
    pInputNode = MX_NEW VSInputNode(VSPutNode::PET_IN, _T("InputColor"), this);
    ENGINE_ASSERT(pInputNode);
    m_pInput.AddElement(pInputNode);
}
VSPEEndFunction::~VSPEEndFunction()
{
}
VSPEEndFunction::VSPEEndFunction()
{
}