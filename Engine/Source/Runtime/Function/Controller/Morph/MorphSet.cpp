#include "MorphSet.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSMorph, MObject)
BEGIN_ADD_PROPERTY(VSMorph, MObject)
REGISTER_PROPERTY(m_pVertexBufferArray, pVertexBufferArray, VSProperty::F_SAVE_LOAD_CLONE)
REGISTER_PROPERTY(m_cName, MorphName, VSProperty::F_SAVE_LOAD_CLONE)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSMorph)
IMPLEMENT_INITIAL_END
VSMorph::VSMorph()
{
    m_pVertexBufferArray.Clear();
}
VSMorph::~VSMorph()
{
    m_pVertexBufferArray.Clear();
}

IMPLEMENT_RTTI(VSMorphSet, MObject)
BEGIN_ADD_PROPERTY(VSMorphSet, MObject)
REGISTER_PROPERTY(m_pMorphArray, MorphArray, VSProperty::F_SAVE_LOAD_CLONE)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSMorphSet)
IMPLEMENT_INITIAL_END
VSMorphSet::VSMorphSet()
{
    m_pMorphArray.Clear();
}
VSMorphSet::~VSMorphSet()
{
    m_pMorphArray.Clear();
}
bool VSMorphSet::AddMorph(VSMorph *pMorph)
{
    ENGINE_ASSERT(pMorph);
    if (m_pMorphArray.GetNum() != 0)
    {
        //是否存在
        for (unsigned int i = 0; i < m_pMorphArray.GetNum(); i++)
        {
            if (m_pMorphArray[i] == pMorph || m_pMorphArray[i]->m_cName == pMorph->m_cName)
                return 1;
        }
        // bufferNum 统一
        if (pMorph->GetBufferNum() != m_pMorphArray[0]->GetBufferNum())
        {
            return 0;
        }
        //分别对每个morph 的每个buffer进行校验
        for (unsigned int i = 0; i < pMorph->GetBufferNum(); i++)
        {
            if (pMorph->GetVertexNum(i))
            {
                for (unsigned int j = 0; j < m_pMorphArray.GetNum(); j++)
                {
                    if (m_pMorphArray[j]->GetVertexNum(i))
                    {
                        if (pMorph->GetVertexNum(i) == m_pMorphArray[j]->GetVertexNum(i))
                        {
                            break;
                        }
                        else
                        {
                            return 0;
                        }
                    }
                }
            }
        }
    }
    m_pMorphArray.AddElement(pMorph);
    m_AddMorphEvent();
    return 1;
}
unsigned int VSMorphSet::GetMorphIndex(const VSUsedName &MorphName) const
{
    for (unsigned int i = 0; i < m_pMorphArray.GetNum(); i++)
    {
        if (m_pMorphArray[i])
        {
            if (m_pMorphArray[i]->m_cName == MorphName)
                return i;
        }
    }
    return m_pMorphArray.GetNum();
}
VSMorph *VSMorphSet::GetMorph(const VSUsedName &MorphName) const
{
    for (unsigned int i = 0; i < m_pMorphArray.GetNum(); i++)
    {
        if (m_pMorphArray[i])
        {
            if (m_pMorphArray[i]->m_cName == MorphName)
                return m_pMorphArray[i];
        }
    }

    return NULL;
}
VSMorph *VSMorphSet::GetMorph(unsigned int i) const
{
    ENGINE_ASSERT(i < m_pMorphArray.GetNum());
    return m_pMorphArray[i];
}