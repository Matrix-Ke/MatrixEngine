#include "GShader.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSGShader, VSShader)
BEGIN_ADD_PROPERTY(VSGShader, VSShader)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSGShader)
IMPLEMENT_INITIAL_END
VSPointer<VSGShader> VSGShader::ms_Default;
VSGShader::VSGShader()
{
}
VSGShader::~VSGShader()
{
}
VSGShader::VSGShader(const TCHAR *pBuffer, const Container::MString &MainFunName, bool IsFromFile)
    : VSShader(pBuffer, MainFunName, IsFromFile)
{
}
VSGShader::VSGShader(const Container::MString &Buffer, const Container::MString &MainFunName, bool IsFromFile)
    : VSShader(Buffer, MainFunName, IsFromFile)
{
}
bool VSGShader::OnLoadResource(VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(m_pUser);

    if (!m_pUser->OnLoadGShaderProgram(this, pID))
        return 0;

    return 1;
}