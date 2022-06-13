#include "SkyLight.h"
#include "Core/GraphicInclude.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSSkyLight, VSIndirectLight)
BEGIN_ADD_PROPERTY(VSSkyLight, VSIndirectLight)
REGISTER_PROPERTY(m_UpColor, UpColor, VSProperty::F_SAVE_LOAD_CLONE | VSProperty::F_REFLECT_NAME)
REGISTER_PROPERTY(m_DownColor, DownColor, VSProperty::F_SAVE_LOAD_CLONE | VSProperty::F_REFLECT_NAME)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSSkyLight)
IMPLEMENT_INITIAL_END
VSSkyLight::VSSkyLight()
{
    m_UpColor = Math::ColorRGBA(1.0f, 1.0f, 1.0f, 1.0f);
    m_DownColor = Math::ColorRGBA(1.0f, 1.0f, 1.0f, 1.0f);
}
VSSkyLight::~VSSkyLight()
{
}