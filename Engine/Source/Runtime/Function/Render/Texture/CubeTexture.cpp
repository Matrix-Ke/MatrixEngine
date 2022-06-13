#include "Render/Texture/CubeTexture.h"
#include "Core/GraphicInclude.h"
#include "RenderTarget.h"
using namespace Matrix;
IMPLEMENT_RTTI(VSCubeTexture, VSTexture)
BEGIN_ADD_PROPERTY(VSCubeTexture, VSTexture)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VSCubeTexture)
IMPLEMENT_INITIAL_END
VSCubeTexture::VSCubeTexture(unsigned int uiWidth, unsigned int uiFormatType,
                             unsigned int uiMipLevel, bool bIsStatic, bool bSRGB)
    : VS2DTextureArray(uiWidth, uiWidth, uiFormatType, uiMipLevel, F_MAX, bIsStatic, bSRGB)
{
}
VSCubeTexture::~VSCubeTexture()
{
}
VSCubeTexture::VSCubeTexture()
{
}
