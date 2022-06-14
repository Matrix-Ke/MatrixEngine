#include "Render/Texture/2DTexture.h"
#include "Core/GraphicInclude.h"
#include "Render/OutputResource/RenderTarget.h"
using namespace Matrix;
IMPLEMENT_RTTI(VS2DTexture, VSTexture)
BEGIN_ADD_PROPERTY(VS2DTexture, VSTexture)
END_ADD_PROPERTY
IMPLEMENT_INITIAL_BEGIN(VS2DTexture)
IMPLEMENT_INITIAL_END

// bool VS2DTexture:: SaveToFile(TCHAR * pSaveName)
// {
//
// 	if(!m_uiHeight || !m_uiWidth)
// 		return 0;
//
// 	unsigned int uiHightSize = GetByteSize(0);
// 	if (!uiHightSize)
// 	{
// 		return false;
// 	}
// 	BITMAPFILEHEADER FileHeader;
// 	FileHeader.bfType = 0x4D42;
// 	FileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + uiHightSize;
// 	FileHeader.bfReserved1 = 0;
// 	FileHeader.bfReserved2 = 0;
// 	FileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
//
// 	BITMAPINFOHEADER InfoHeader;
// 	InfoHeader.biSize = sizeof(BITMAPINFOHEADER);
// 	InfoHeader.biWidth = m_uiWidth;
// 	InfoHeader.biHeight = m_uiHeight;
// 	InfoHeader.biPlanes = 1;
// 	InfoHeader.biBitCount = 32;
// 	InfoHeader.biCompression = 0;
// 	InfoHeader.biSizeImage =  uiHightSize;
// 	InfoHeader.biXPelsPerMeter = 0;
// 	InfoHeader.biYPelsPerMeter = 0;
// 	InfoHeader.biClrUsed = 0;
// 	InfoHeader.biClrImportant = 0;
//
//
//
//
// 	unsigned char *pBufferTemp = NULL,*pBuffer = NULL;					//临时缓冲区
// 	pBufferTemp = MX_NEW unsigned char[uiHightSize];
// 	pBuffer = GetBuffer(0);
// 	if(!pBufferTemp)
// 		return 0;
//
// 	unsigned int  bytes_per_line = m_uiWidth * 4;
// 	// 按行翻转
// 	for (unsigned int index=0; index < m_uiHeight; index++)
// 		VSMemcpy(&pBufferTemp[((m_uiHeight - 1) - index) * bytes_per_line],
// 		&pBuffer[index * bytes_per_line], bytes_per_line);
//
// 	VSFile * pFile = NULL;
// 	pFile = MX_NEW VSFile();
// 	if (!pFile)
// 	{
// 		return 0;
// 	}
//
// 	if(!pFile->Open(pSaveName,VSFile::OM_WB))
// 	{
// 		ENGINE_DELETE(pFile);
// 		return 0;
// 	}
// 	pFile->Write(&FileHeader,sizeof(BITMAPFILEHEADER),1);
// 	pFile->Write(&InfoHeader,sizeof(BITMAPINFOHEADER),1);
// 	pFile->Write(pBufferTemp,uiHightSize,1);
// 	ENGINE_DELETEA(pBufferTemp);
// 	ENGINE_DELETE(pFile);
// 	return 1;
// }
VS2DTexture::VS2DTexture(unsigned int uiWidth, unsigned int uiHeight,
                         unsigned int uiFormatType, unsigned int uiMipLevel, bool bIsStatic, bool bSRGB)
    : VSTexture(uiFormatType, uiWidth, uiHeight, 1, 1, uiMipLevel, bIsStatic, bSRGB)
{
    SetMipLevel();
    m_pOutputResource.SetBufferNum(m_uiMipLevel);
    for (unsigned int i = 0; i < m_uiMipLevel; i++)
    {
        m_pOutputResource[i] = NULL;
    }
}
VS2DTexture::~VS2DTexture()
{
}
VS2DTexture::VS2DTexture()
{
}
void VS2DTexture::SetMipLevel()
{
    if (m_uiMipLevel == 1)
    {
        return;
    }
    ENGINE_ASSERT(m_uiWidth && m_uiHeight);

    if (!IsTwoPower(m_uiWidth) || !IsTwoPower(m_uiHeight))
    {
        m_uiMipLevel = 1;
        ENGINE_ASSERT(0);
    }

    unsigned int uiWidthLevel = FastLog2(m_uiWidth);
    unsigned int uHeightLevel = FastLog2(m_uiHeight);

    unsigned int uiCurMipLevel = Max(uiWidthLevel, uHeightLevel) + 1;
    if (!m_uiMipLevel || uiCurMipLevel < m_uiMipLevel)
    {
        m_uiMipLevel = uiCurMipLevel;
    }
}
