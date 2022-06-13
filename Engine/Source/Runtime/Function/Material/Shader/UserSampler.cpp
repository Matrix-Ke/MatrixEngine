#include "UserSampler.h"
#include "ResourceManager.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSUserSampler, MObject)
BEGIN_ADD_PROPERTY(VSUserSampler, MObject)
REGISTER_PROPERTY(m_uiTexType, TexType, VSProperty::F_SAVE_LOAD_CLONE)
REGISTER_PROPERTY(m_Name, Name, VSProperty::F_SAVE_LOAD_CLONE)
REGISTER_PROPERTY(m_uiRegisterIndex, RegisterIndex, VSProperty::F_SAVE_LOAD_CLONE)
REGISTER_PROPERTY(m_uiRegisterNum, RegisterNum, VSProperty::F_SAVE_LOAD_CLONE)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSUserSampler)
IMPLEMENT_INITIAL_END
VSUserSampler::VSUserSampler()
{
    m_uiTexType = VSTexture::TT_2D;
    m_pTextureArray.Clear();
    m_uiRegisterNum = 1;
}
VSUserSampler::~VSUserSampler()
{
    m_pTextureArray.Clear();
}
VSUserSampler::VSUserSampler(const VSUsedName &Name, unsigned int uiTexType, unsigned int uiRegisterIndex, unsigned int uiRegisterNum)
{
    m_Name = Name;
    m_uiTexType = uiTexType;
    m_uiRegisterIndex = uiRegisterIndex;
    m_uiRegisterNum = uiRegisterNum;
    m_pTextureArray.SetBufferNum(uiRegisterNum);
}
bool VSUserSampler::PostLoad(MStream *pStream)
{
    m_pTextureArray.SetBufferNum(m_uiRegisterNum);
    return true;
}
bool VSUserSampler::PostClone(MObject *pObjectSrc)
{
    m_pTextureArray.SetBufferNum(m_uiRegisterNum);
    return true;
}
