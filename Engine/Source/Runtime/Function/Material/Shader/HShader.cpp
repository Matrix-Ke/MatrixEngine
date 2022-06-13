#include "HShader.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSHShader, VSShader)
BEGIN_ADD_PROPERTY(VSHShader, VSShader)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSHShader)
IMPLEMENT_INITIAL_END
VSPointer<VSHShader> VSHShader::ms_Default;
VSHShader::VSHShader()
{
}
VSHShader::~VSHShader()
{
}
VSHShader::VSHShader(const TCHAR *pBuffer, const Container::MString &MainFunName, bool IsFromFile)
    : VSShader(pBuffer, MainFunName, IsFromFile)
{
}
VSHShader::VSHShader(const Container::MString &Buffer, const Container::MString &MainFunName, bool IsFromFile)
    : VSShader(Buffer, MainFunName, IsFromFile)
{
}
bool VSHShader::OnLoadResource(VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(m_pUser);

    if (!m_pUser->OnLoadHShaderProgram(this, pID))
        return 0;

    return 1;
}