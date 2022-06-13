#include "Steer.h"
#include "Core/GraphicInclude.h"
using namespace Matrix;
IMPLEMENT_RTTI_NoCreateFun(VSSteerComponent, MObject)
    VSSteerComponent::VSSteerComponent()
{
    m_pSteer = NULL;
}
VSSteerComponent::~VSSteerComponent()
{
    m_pSteer = NULL;
}
IMPLEMENT_RTTI_NoCreateFun(VSSteer, MObject)
    VSSteer::VSSteer()
{
    m_pActor = NULL;
}
VSSteer::~VSSteer()
{
    m_pActor = NULL;
    m_ComponentArray.Clear();
}
Math::Vector3 VSSteer::Compute()
{
    Math::Vector3 Force;
    for (unsigned int i = 0; i < m_ComponentArray.GetNum(); i++)
    {
        if (!AddForce(Force, m_ComponentArray[i]->Compute() * m_ComponentArray[i]->m_fWeight))
        {
            return Force;
        }
    }
    return Force;
}
bool VSSteer::AddForce(Math::Vector3 &CurForce, Math::Vector3 &AddForce)
{
    VSREAL CurForceLen = CurForce.GetLength();
    VSREAL MaxDriverForce = GetOwner()->GetMaxDriverForce();
    VSREAL RemainForce = MaxDriverForce - CurForceLen;
    if (RemainForce <= 0.0f)
    {
        return false;
    }
    VSREAL AddForceLen = AddForce.GetLength();
    if (AddForceLen < RemainForce)
    {
        CurForce += AddForce;
    }
    else
    {
        AddForce.Normalize();
        CurForce += AddForce * RemainForce;
    }
    return true;
}