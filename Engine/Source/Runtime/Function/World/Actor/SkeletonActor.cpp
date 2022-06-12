#include "SkeletonActor.h"
#include "GraphicInclude.h"
#include "Stream.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSSkeletonActor, VSActor)
BEGIN_ADD_PROPERTY(VSSkeletonActor, VSActor)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSSkeletonActor)
IMPLEMENT_INITIAL_END
VSSkeletonActor::VSSkeletonActor()
{
}
VSSkeletonActor::~VSSkeletonActor()
{
}
void VSSkeletonActor::CreateDefaultComponentNode()
{
    m_pNode = VSNodeComponent::CreateComponent<VSSkeletonMeshComponent>();
}
