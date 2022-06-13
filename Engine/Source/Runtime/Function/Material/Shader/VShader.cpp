#include "Shader.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSVShader, VSShader)
BEGIN_ADD_PROPERTY(VSVShader, VSShader)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSVShader)
IMPLEMENT_INITIAL_END
VSPointer<VSVShader> VSVShader::ms_Default;
VSVShader::VSVShader()
{
}
VSVShader::~VSVShader()
{
}
VSVShader::VSVShader(const TCHAR *pBuffer, const Container::MString &MainFunName, bool IsFromFile)
    : VSShader(pBuffer, MainFunName, IsFromFile)
{
}
VSVShader::VSVShader(const Container::MString &Buffer, const Container::MString &MainFunName, bool IsFromFile)
    : VSShader(Buffer, MainFunName, IsFromFile)
{
}
bool VSVShader::OnLoadResource(VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(m_pUser);

    if (!m_pUser->OnLoadVShaderProgram(this, pID))
        return 0;

    return 1;
}