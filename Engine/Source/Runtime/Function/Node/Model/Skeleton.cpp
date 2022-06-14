#include "Node/Model/Skeleton.h"
#include "Node/Model/BoneNode.h"
#include "Node/Mesh/LineSet.h"
#include "Node/Model/SkeletonMeshNode.h"
#include "Node/GeometryNode.h"
#include "Core/GraphicInclude.h"
#include "Render/SceneManager/ViewFamily.h"
#include "Render/DebugDraw.h"
#include "Core/Stream/Stream.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSSkeleton, VSNode)
VSREAL VSSkeleton::ms_fBoneAxisLength = 1.0f;
BEGIN_ADD_PROPERTY(VSSkeleton, VSNode)
REGISTER_PROPERTY(m_pBoneArray, BoneArray, VSProperty::F_SAVE_LOAD_CLONE)
REGISTER_PROPERTY(m_bIsDrawSkeleton, IsDrawSkeleton, VSProperty::F_SAVE_LOAD_CLONE | VSProperty::F_REFLECT_NAME)
REGISTER_PROPERTY(m_LocalBV, LocalAABB, VSProperty::F_SAVE_LOAD_CLONE)
REGISTER_PROPERTY(m_OriginLocalBV, OriginLocalBV, VSProperty::F_SAVE_LOAD_CLONE)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSSkeleton)
IMPLEMENT_INITIAL_END
VSSkeleton::VSSkeleton()
{
    m_pBoneArray.Clear();
    m_bIsStatic = 0;
    m_bIsDrawSkeleton = false;
}
VSSkeleton::~VSSkeleton()
{
    m_pBoneArray.Clear();
}

unsigned int VSSkeleton::GetBoneNum() const
{

    return m_pBoneArray.GetNum();
}
int VSSkeleton::GetBoneIndex(const VSUsedName &Name) const
{

    for (unsigned int i = 0; i < m_pBoneArray.GetNum(); i++)
    {
        if (m_pBoneArray[i]->m_cName == Name)
            return i;
    }
    return -1;
}
VSBoneNode *VSSkeleton::GetBoneNode(const VSUsedName &Name) const
{

    for (unsigned int i = 0; i < m_pBoneArray.GetNum(); i++)
    {
        if (m_pBoneArray[i]->m_cName == Name)
            return m_pBoneArray[i];
    }
    return NULL;
}
VSBoneNode *VSSkeleton::GetBoneNode(unsigned int i) const
{
    ENGINE_ASSERT(i < m_pBoneArray.GetNum());
    return m_pBoneArray[i];
}
void VSSkeleton::CreateBoneArray()
{
    m_pBoneArray.Clear();
    Container::MArray<VSBoneNode *> Temp;
    for (unsigned int i = 0; i < m_pChild.GetNum(); i++)
    {
        VSBoneNode *pBoneNode = DynamicCast<VSBoneNode>(m_pChild[i]);
        if (pBoneNode)
        {
            pBoneNode->GetAllBoneArray(Temp);
        }
    }
    for (unsigned int i = 0; i < Temp.GetNum(); i++)
    {
        VSBoneNode *pBoneNode = DynamicCast<VSBoneNode>(Temp[i]);
        m_pBoneArray.AddElement(pBoneNode);
    }
}
void VSSkeleton::LinkBoneArray()
{
    m_pBoneArray.Clear();
    Container::MArray<VSBoneNode *> Temp;
    for (unsigned int i = 0; i < m_pChild.GetNum(); i++)
    {
        VSBoneNode *pBoneNode = DynamicCast<VSBoneNode>(m_pChild[i]);
        if (pBoneNode)
        {

            pBoneNode->GetAllBoneArray(Temp);
        }
    }
    for (unsigned int i = 0; i < Temp.GetNum(); i++)
    {
        VSBoneNode *pBoneNode = DynamicCast<VSBoneNode>(Temp[i]);
        m_pBoneArray.AddElement(pBoneNode);
    }
}
void VSSkeleton::UpdateNoChild(double dAppTime)
{

    if (dAppTime > 0.0f)
    {
        UpdateController(dAppTime);
    }

    UpdateTransform(dAppTime);

    if (m_bIsChanged)
    {
        UpdateWorldBound(dAppTime);
    }
    m_bIsChanged = false;
}
void VSSkeleton::UpdateWorldBound(double dAppTime)
{
    m_WorldBV.Transform(m_LocalBV, m_World.GetCombine());
    if (m_pParent)
    {
        m_pParent->m_bIsChanged = true;
    }
}
void VSSkeleton::ComputeNodeVisibleSet(VSCuller &Culler, bool bNoCull, double dAppTime)
{

    UpdateView(Culler, dAppTime);
}
void VSSkeleton::UpdateView(VSCuller &Culler, double dAppTime)
{

    VSNode::UpdateView(Culler, dAppTime);

    if (Culler.GetCullerType() == VSCuller::CUT_MAIN)
    {
        Draw(Culler.GetCamera());
    }
}
void VSSkeleton::Draw(VSCamera *pCamera)
{
    if (!pCamera || !m_bIsDrawSkeleton)
    {
        return;
    }

    VSSkeletonMeshNode *pMesh = (VSSkeletonMeshNode *)m_pParent;
    ENGINE_ASSERT(pMesh);

    Math::Vector3 Dist = pCamera->GetWorldTranslate() - pMesh->GetWorldTranslate();
    ms_fBoneAxisLength = Dist.GetLength() * 0.05f;

    static Container::MArray<VSDebugDraw *> s_DebugDrawArray;
    s_DebugDrawArray.Clear();
    for (unsigned int i = 0; i < pCamera->GetViewFamilyNum(); i++)
    {
        VSViewFamily *pViewFamily = pCamera->GetViewFamily(i);
        if (pViewFamily)
        {
            VSSceneRenderMethod *pRM = pViewFamily->m_pSceneRenderMethod;
            VSDebugDraw *pDebugDraw = pRM->GetDebugDraw(pMesh->GetRenderGroup());
            if (pDebugDraw && pDebugDraw->m_bEnable)
            {
                s_DebugDrawArray.AddElement(pDebugDraw);
            }
        }
    }

    for (unsigned int i = 0; i < m_pBoneArray.GetNum(); i++)
    {
        VSBoneNode *pParent = DynamicCast<VSBoneNode>(m_pBoneArray[i]->GetParent());
        if (pParent)
        {
            Math::Vector3 P1 = m_pBoneArray[i]->GetWorldTranslate();

            Math::Vector3 P2 = m_pBoneArray[i]->GetParent()->GetWorldTranslate();
            for (unsigned int j = 0; j < s_DebugDrawArray.GetNum(); j++)
            {
                s_DebugDrawArray[j]->AddDebugLine(P1, P2, Math::ColorRGBA(1.0f, 1.0f, 1.0f, 1.0f).GetDWARGB(), false);
            }
        }
    }
    for (unsigned int i = 0; i < m_pBoneArray.GetNum(); i++)
    {
        Math::Vector3 Axis[3];
        Math::Matrix3 Rot = m_pBoneArray[i]->GetWorldRotate();
        Rot.GetUVN(Axis);
        Axis[0].Normalize();
        Axis[1].Normalize();
        Axis[2].Normalize();
        Math::Vector3 Pos = m_pBoneArray[i]->GetWorldTranslate();

        for (unsigned int j = 0; j < s_DebugDrawArray.GetNum(); j++)
        {
            s_DebugDrawArray[j]->AddDebugLine(Pos, Pos + Axis[0] * ms_fBoneAxisLength, Math::ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f).GetDWARGB(), false);
        }

        for (unsigned int j = 0; j < s_DebugDrawArray.GetNum(); j++)
        {
            s_DebugDrawArray[j]->AddDebugLine(Pos, Pos + Axis[1] * ms_fBoneAxisLength, Math::ColorRGBA(0.0f, 1.0f, 0.0f, 1.0f).GetDWARGB(), false);
        }

        for (unsigned int j = 0; j < s_DebugDrawArray.GetNum(); j++)
        {
            s_DebugDrawArray[j]->AddDebugLine(Pos, Pos + Axis[2] * ms_fBoneAxisLength, Math::ColorRGBA(0.0f, 0.0f, 1.0f, 1.0f).GetDWARGB(), false);
        }
    }
}
const Math::VSTransform &VSSkeleton::GetRootTransform()
{
    if (m_pChild.GetNum() > 0)
    {
        return m_pChild[0]->GetLocalTransform();
    }
    return Math::VSTransform::ms_Indetity;
}
void VSSkeleton::CreateLocalAABB()
{
    Math::Vector3 MinPos(VSMAX_REAL, VSMAX_REAL, VSMAX_REAL);
    Math::Vector3 MaxPos(VSMIN_REAL, VSMIN_REAL, VSMIN_REAL);
    Math::VSTransform SkeletonLocalT = GetLocalTransform();
    for (unsigned int j = 0; j < GetBoneNum(); j++)
    {
        VSBoneNode *pBone = GetBoneNode(j);
        if (pBone)
        {
            Math::Vector3 Pos = pBone->GetWorldTranslate() * SkeletonLocalT.GetCombineInverse();
            for (int t = 0; t < 3; t++)
            {
                if (MinPos.m[t] > Pos.m[t])
                {
                    MinPos.m[t] = Pos.m[t];
                }

                if (MaxPos.m[t] < Pos.m[t])
                {
                    MaxPos.m[t] = Pos.m[t];
                }
            }
        }
    }
    m_LocalBV.Set(MaxPos, MinPos);
    m_OriginLocalBV.Set(MaxPos, MinPos);
}