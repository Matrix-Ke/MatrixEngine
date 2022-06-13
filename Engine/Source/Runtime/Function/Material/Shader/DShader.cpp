#include "DShader.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSDShader, VSShader)
BEGIN_ADD_PROPERTY(VSDShader, VSShader)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSDShader)
IMPLEMENT_INITIAL_END
VSPointer<VSDShader> VSDShader::ms_Default;
VSDShader::VSDShader()
{
}
VSDShader::~VSDShader()
{
}
VSDShader::VSDShader(const TCHAR *pBuffer, const Container::MString &MainFunName, bool IsFromFile)
    : VSShader(pBuffer, MainFunName, IsFromFile)
{
}
VSDShader::VSDShader(const Container::MString &Buffer, const Container::MString &MainFunName, bool IsFromFile)
    : VSShader(Buffer, MainFunName, IsFromFile)
{
}
bool VSDShader::OnLoadResource(VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(m_pUser);

    if (!m_pUser->OnLoadDShaderProgram(this, pID))
        return 0;

    return 1;
}