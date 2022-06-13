#include "PShader.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSPShader, VSShader)
BEGIN_ADD_PROPERTY(VSPShader, VSShader)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSPShader)
IMPLEMENT_INITIAL_END
VSPointer<VSPShader> VSPShader::ms_Default;
VSPShader::VSPShader()
{
}
VSPShader::VSPShader(const TCHAR *pBuffer, const Container::MString &MainFunName, bool IsFromFile)
    : VSShader(pBuffer, MainFunName, IsFromFile)
{
}
VSPShader::VSPShader(const Container::MString &Buffer, const Container::MString &MainFunName, bool IsFromFile)
    : VSShader(Buffer, MainFunName, IsFromFile)
{
}
VSPShader::~VSPShader()
{
}

bool VSPShader::OnLoadResource(VSResourceIdentifier *&pID)
{
    ENGINE_ASSERT(m_pUser);

    if (!m_pUser->OnLoadPShaderProgram(this, pID))
        return 0;

    return 1;
}
