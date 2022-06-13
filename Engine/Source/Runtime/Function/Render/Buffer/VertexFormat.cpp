#include "Render/Buffer/VertexFormat.h"
#include "VertexBuffer.h"
#include "Core/GraphicInclude.h"
#include "Core/Stream/Stream.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSVertexFormat, VSBind)
BEGIN_ADD_PROPERTY(VSVertexFormat, VSBind)
REGISTER_PROPERTY(m_uiVertexFormatCode, VertexFormatCode, VSProperty::F_SAVE_LOAD_CLONE)
REGISTER_PROPERTY(m_FormatArray, FormatArray, VSProperty::F_SAVE_LOAD_CLONE)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSVertexFormat)
IMPLEMENT_INITIAL_END
VSVertexFormat::~VSVertexFormat()
{
    ReleaseResource();
}
VSVertexFormat::VSVertexFormat()
{
}

bool VSVertexFormat::OnLoadResource(VSResourceIdentifier *&pID)
{
    if (!m_pUser->OnLoadVBufferFormat(this, pID))
        return 0;

    return 1;
}
