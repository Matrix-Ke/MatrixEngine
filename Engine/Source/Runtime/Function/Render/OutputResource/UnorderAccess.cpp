#include "UnorderAccess.h"
#include "Core/GraphicInclude.h"
using namespace Matrix;
IMPLEMENT_RTTI_NoCreateFun(VSUnorderAccess, VSOutputResource)
    IMPLEMENT_INITIAL_NO_CLASS_FACTORY_BEGIN(VSUnorderAccess)
        IMPLEMENT_INITIAL_NO_CLASS_FACTORY_END
    BEGIN_ADD_PROPERTY(VSUnorderAccess, VSOutputResource)
END_ADD_PROPERTY
VSUnorderAccess::VSUnorderAccess()
{
}
VSUnorderAccess::~VSUnorderAccess()
{
}
