#include "CShader.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSCShader, VSShader)
BEGIN_ADD_PROPERTY(VSCShader, VSShader)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSCShader)
IMPLEMENT_INITIAL_END
VSPointer<VSCShader> VSCShader::ms_Default;
VSCShader::VSCShader()
{
}
VSCShader::~VSCShader()
{
}
VSCShader::VSCShader(const TCHAR *pBuffer, const Container::MString &MainFunName, bool IsFromFile)
    : VSShader(pBuffer, MainFunName, IsFromFile)
{
}
VSCShader::VSCShader(const Container::MString &Buffer, const Container::MString &MainFunName, bool IsFromFile)
    : VSShader(Buffer, MainFunName, IsFromFile)
{
}
bool VSCShader::OnLoadResource(VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(m_pUser);

    if (!m_pUser->OnLoadCShaderProgram(this, pID))
        return 0;

    return 1;
}