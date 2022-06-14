#include "World/Actor/StaticActor.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSStaticActor, VSActor)
BEGIN_ADD_PROPERTY(VSStaticActor, VSActor)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSStaticActor)
IMPLEMENT_INITIAL_END
VSStaticActor::VSStaticActor()
{
}
VSStaticActor::~VSStaticActor()
{
}
void VSStaticActor::CreateDefaultComponentNode()
{
    m_pNode = VSNodeComponent::CreateComponent<VSStaticMeshComponent>();
}
