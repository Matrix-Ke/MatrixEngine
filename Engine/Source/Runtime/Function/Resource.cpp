#include "Resource.h"
#include "Meta/Property.h"



using namespace Matrix;
VSResourceInterface::VSResourceInterface()
{
}
VSResourceInterface::~VSResourceInterface()
{
}
VSResource::VSResource()
{
}
VSResource::~VSResource()
{
}
IMPLEMENT_RTTI_NoCreateFun(VSCacheResource, MObject)
IMPLEMENT_INITIAL_NO_CLASS_FACTORY_BEGIN(VSCacheResource)
IMPLEMENT_INITIAL_NO_CLASS_FACTORY_END
BEGIN_ADD_PROPERTY(VSCacheResource, MObject)
END_ADD_PROPERTY
VSCacheResource::VSCacheResource()
{
}
VSCacheResource::~VSCacheResource()
{
}
VSResourceProxyBase::VSResourceProxyBase()
{
}
VSResourceProxyBase::~VSResourceProxyBase()
{
}
VSResourceControl::VSResourceControl(unsigned int uiGCMaxTimeCount)
{
	m_uiGCMaxTimeCount = uiGCMaxTimeCount;
}
VSResourceControl::~VSResourceControl()
{
}
