#include "StreamingType.h"
//#include "Asyn/RenderThread.h"
using namespace Matrix;
void VSStreamingType::ReleaseStreamObject()
{
	ENGINE_DELETE(m_pToStreamObject);
}