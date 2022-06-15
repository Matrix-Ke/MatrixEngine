#include "Material/Shader/UserConstant.h"
#include "Core/ResourceManager.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSUserConstant, MObject)
BEGIN_ADD_PROPERTY(VSUserConstant, MObject)
REGISTER_PROPERTY(m_uiValueType, ValueType, VSProperty::F_SAVE_LOAD_CLONE)
REGISTER_PROPERTY(m_uiRegisterIndex, RegisterIndex, VSProperty::F_SAVE_LOAD_CLONE)
REGISTER_PROPERTY(m_uiRegisterNum, RegisterNum, VSProperty::F_SAVE_LOAD_CLONE)
REGISTER_PROPERTY(m_Name, Name, VSProperty::F_SAVE_LOAD_CLONE)
REGISTER_PROPERTY(m_NameInShader, NameInShader, VSProperty::F_SAVE_LOAD_CLONE)
REGISTER_PROPERTY(m_uiSize, Size, VSProperty::F_SAVE_LOAD_CLONE)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSUserConstant)
IMPLEMENT_INITIAL_END
VSUserConstant::VSUserConstant()
{
    m_pData = NULL;
    m_uiRegisterIndex = 0;
    m_uiValueType = VSMAX_UINT32;
    m_uiRegisterNum = 0;
    m_uiSize = 0;
}
VSUserConstant::VSUserConstant(const VSUsedName &Name, const VSUsedName &NameInShader, unsigned int uiSize,
                               unsigned int uiRegisterIndex, unsigned int uiRegisterNum, unsigned int uiValueType)
{
    ENGINE_ASSERT(uiValueType < VT_MAX && uiSize > 0 && uiRegisterNum > 0);
    m_Name = Name;
    m_uiValueType = uiValueType;
    m_uiSize = uiSize;
    m_pData = new unsigned char[m_uiSize];
    m_uiRegisterIndex = uiRegisterIndex;
    m_uiRegisterNum = uiRegisterNum;
    ENGINE_ASSERT(m_pData);
    Platform::MXMemset(m_pData, 0, m_uiSize);
    m_NameInShader = NameInShader;
}
VSUserConstant::VSUserConstant(const VSUsedName &Name,
                               unsigned int uiSize,
                               unsigned int uiRegisterIndex, unsigned int uiRegisterNum,
                               unsigned int uiValueType)
{
    ENGINE_ASSERT(uiValueType < VT_MAX && uiSize > 0 && uiRegisterNum > 0);
    m_Name = Name;
    m_uiValueType = uiValueType;
    m_uiSize = uiSize;
    m_pData = new unsigned char[m_uiSize];
    m_uiRegisterIndex = uiRegisterIndex;
    m_uiRegisterNum = uiRegisterNum;
    ENGINE_ASSERT(m_pData);
    Platform::MXMemset(m_pData, 0, m_uiSize);
    m_NameInShader = Name;
}
VSUserConstant::~VSUserConstant()
{
    ENGINE_DELETEA(m_pData);
}
bool VSUserConstant::PostLoad(MStream *pStream)
{
    ENGINE_DELETEA(m_pData);
    if (m_uiSize)
    {
        m_pData = MX_NEW unsigned char[m_uiSize];
        Platform::MXMemset(m_pData, 0, m_uiSize);
    }
    return true;
}
bool VSUserConstant::PostClone(MObject *pObjectSrc)
{
    ENGINE_DELETEA(m_pData);
    if (m_uiSize)
    {
        m_pData = MX_NEW unsigned char[m_uiSize];
        Platform::MXMemset(m_pData, 0, m_uiSize);
    }
    return true;
}
bool VSUserConstant::SetData(void *pElementData)
{
    ENGINE_ASSERT(pElementData);
    void *pDest = (unsigned char *)m_pData;
    Platform::MXMemcpy(pDest, pElementData, m_uiSize);

    return 1;
}
