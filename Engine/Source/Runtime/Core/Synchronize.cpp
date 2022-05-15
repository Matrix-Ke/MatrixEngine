#include "Synchronize.h"
#include "MemoryManager.h"

using namespace Matrix::Core;
MTXCriticalSection gSafeOutputString;


unsigned int Matrix::Core::MTXSynchronize::WaitAll(MTXSynchronize** pSynchronize, unsigned int uiNum, bool bWaitAll, DWORD dwMilliseconds)
{
	MX_ENGINE_ASSERT(uiNum >= 1 && uiNum <= MAXIMUM_WAIT_OBJECTS);
	static HANDLE handle[MAXIMUM_WAIT_OBJECTS];
	for (unsigned int i = 0; i < uiNum; i++)
	{
		handle[i] = (HANDLE)pSynchronize[i]->GetHandle();
	}
	DWORD dw = WaitForMultipleObjects(uiNum, handle, bWaitAll, dwMilliseconds);
	switch (dw)
	{
	case WAIT_FAILED:
		return WF_FAILED;
	case WAIT_TIMEOUT:
		return WF_TIMEOUT;
	case WAIT_OBJECT_0:
		return WF_OBJECT0;

	}
	return WF_FAILED;
}

void Matrix::Core::MTXSynchronize::MTXSafeOutputDebugString(const TCHAR* pString, ...)
{
	MTXCriticalSection::Locker Temp(gSafeOutputString);
	char* pArgs;
	pArgs = (char*)&pString + sizeof(pString);
	//todo list: 了解如何设计日志系统
	_vstprintf_s(MatrixCore::msLogbuffer, LOG_BUFFER_SIZE, pString, pArgs);
	OutputDebugString(MatrixCore::msLogbuffer);
}


MTXSemaphore::MTXSemaphore(unsigned int uCount, unsigned int maxCount)
{
	MX_ENGINE_ASSERT(uCount <= maxCount);
	//
	mSemaphore = CreateSemaphore(NULL, uCount, maxCount, NULL);

	mMaxCount = maxCount;
}

Matrix::Core::MTXSemaphore::~MTXSemaphore()
{
	BOOL closed = CloseHandle((HANDLE)mSemaphore);
	MX_ENGINE_ASSERT(closed);
	mSemaphore = NULL;
}

void Matrix::Core::MTXSemaphore::Enter()
{
	//WAIT_OBJECT_0, 表示等待的对象有信号（对线程来说，表示执行结束）；
	//WAIT_TIMEOUT, 表示等待指定时间内，对象一直没有信号（线程没执行完）；
	//WAIT_ABANDONED 表示对象有信号，但还是不能执行  一般是因为未获取到锁或其他原因
	// result:
	//   WAIT_ABANDONED (0x00000080)
	//   WAIT_OBJECT_0  (0x00000000), signaled
	//   WAIT_TIMEOUT   (0x00000102), [not possible with INFINITE]
	//   WAIT_FAILED    (0xFFFFFFFF), not signaled
	DWORD result = WaitForSingleObject((HANDLE)mSemaphore, INFINITE);
	MX_ENGINE_ASSERT(result);
}

void Matrix::Core::MTXSemaphore::Leave(unsigned int uiReleaseCount)
{
	BOOL released = ReleaseSemaphore(HANDLE(mSemaphore), uiReleaseCount, NULL);
}

Matrix::Core::MTXMutex::MTXMutex()
{
	mMutex = CreateMutex(NULL, FALSE, NULL);
	MX_ENGINE_ASSERT(mMutex);
}

Matrix::Core::MTXMutex::~MTXMutex()
{
	BOOL closed = CloseHandle((HANDLE)mMutex);
	MX_ENGINE_ASSERT(closed);
	mMutex = NULL;
}

void Matrix::Core::MTXMutex::Enter()
{
	// result:
	//   WAIT_ABANDONED (0x00000080)
	//   WAIT_OBJECT_0  (0x00000000), signaled
	//   WAIT_TIMEOUT   (0x00000102), [not possible with INFINITE]
	//   WAIT_FAILED    (0xFFFFFFFF), not signaled
	DWORD result = WaitForSingleObject((HANDLE)mMutex, INFINITE);
	MX_ENGINE_ASSERT(result != WAIT_FAILED);

}

void Matrix::Core::MTXMutex::Leave()
{
	BOOL  released = ReleaseMutex(HANDLE(mMutex));
	MX_ENGINE_ASSERT(released);
}

Matrix::Core::MTXEvent::MTXEvent()
{
	mEvent = NULL;
}

Matrix::Core::MTXEvent::~MTXEvent()
{
	if (mEvent != NULL)
	{
		CloseHandle(mEvent);
	}
}

void Matrix::Core::MTXEvent::Lock()
{
	WaitForSingleObject(mEvent, INFINITE);
}

void Matrix::Core::MTXEvent::unLock()
{
	PulseEvent(mEvent);
}

bool Matrix::Core::MTXEvent::Create(bool bManualReset, const TCHAR* InName)
{
	mEvent = CreateEvent(NULL, bManualReset, 0, InName);
	return mEvent != NULL;
}

void Matrix::Core::MTXEvent::Trigger(void)
{
	SetEvent(mEvent);
}

void Matrix::Core::MTXEvent::Reset(void)
{
	ResetEvent(mEvent);
}

void Matrix::Core::MTXEvent::Pulse(void)
{
	PulseEvent(mEvent);
}

bool Matrix::Core::MTXEvent::Wait(DWORD WaitTime)
{
	return WaitForSingleObject(mEvent, WaitTime) == WAIT_OBJECT_0;
}

bool Matrix::Core::MTXEvent::IsTrigger()
{
	return Wait(0);
}

Matrix::Core::MTXTlsValue::MTXTlsValue()
{
	MTXCriticalSection::Locker  lockgurad(mCriticalSection);
	mSlot = MTXTlsAlloc();
	MX_ENGINE_ASSERT(mSlot != 0XFFFFFFFF);
}

Matrix::Core::MTXTlsValue::~MTXTlsValue()
{
	MX_ENGINE_ASSERT(mSlot != 0XFFFFFFFF);
	for (size_t i = 0; i < mThreadValueNum; i++)
	{
		ENGINE_DELETE(pThreadValue[i]);
	}
	MTXTlsFree(mSlot);
}

void Matrix::Core::MTXTlsValue::SetThreadValue(void* pValue)
{
	MTXCriticalSection::Locker Temp(mCriticalSection);
	pThreadValue[mThreadValueNum] = (StackMemoryManager*)pValue;
	mThreadValueNum++;
	MTXSetTlsValue(mSlot, pValue);
}

void* Matrix::Core::MTXTlsValue::GetThreadValue()
{
	return MTXGetTlsValue(mSlot);
}


