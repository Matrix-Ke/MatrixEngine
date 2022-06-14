// #include "EngineThread.h"
// #include "Material/Shader/UserConstant.h"
// #include "Render/Bind.h"

// using namespace Matrix;


// VSConstantBuffer::VSConstantBuffer()
// {
// 	m_uiCurBufferP = 0;
// 	m_Buffer.SetBufferNum(Constant_BUFFER_SIZE);
// }
// VSConstantBuffer::~VSConstantBuffer()
// {
// }
// unsigned char* VSConstantBuffer::Assign(unsigned int uiSize)
// {
// 	Platform::MCriticalSection::Locker Temp(m_Lock);
// 	unsigned char* pTemp = NULL;
// 	m_uiCurBufferP += uiSize;
// 	if (m_uiCurBufferP > Constant_BUFFER_SIZE)
// 	{
// 		ENGINE_ASSERT(0);
// 		return NULL;
// 	}

// 	pTemp = &m_Buffer[m_uiCurBufferP - uiSize];
// 	return pTemp;
// }
// unsigned char* VSConstantBuffer::Assign(unsigned int VTType, unsigned int uiRegisterNum)
// {
// 	unsigned int uiSize = 0;
// 	if (VTType == VSUserConstant::VT_FLOAT)
// 	{
// 		uiSize = sizeof(VSREAL) * 4 * uiRegisterNum;
// 	}
// 	else if (VTType == VSUserConstant::VT_INT)
// 	{
// 		uiSize = sizeof(int) * 4 * uiRegisterNum;
// 	}
// 	else if (VTType == VSUserConstant::VT_BOOL)
// 	{
// 		uiSize = sizeof(bool) * 4 * uiRegisterNum;
// 	}
// 	ENGINE_ASSERT(uiSize);
// 	return Assign(uiSize);
// }
// void VSConstantBuffer::Clear()
// {
// 	m_uiCurBufferP = NULL;
// }