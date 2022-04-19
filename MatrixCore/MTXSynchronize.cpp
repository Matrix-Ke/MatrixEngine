#include "pch.h"
#include "MTXSynchronize.h"
#include "MTXMemManager.h"

using namespace Matrix;
MTXCriticalSection gSafeOutputString;


unsigned int Matrix::MTXSynchronize::WaitAll(MTXSynchronize** pSynchronize, unsigned int uiNum, bool bWaitAll, DWORD dwMilliseconds)
{
	MTXENGINE_ASSERT(uiNum >= 1 && uiNum <= MAXIMUM_WAIT_OBJECTS);
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

void Matrix::MTXSynchronize::MTXSafeOutputDebugString(const TCHAR* pString, ...)
{
	MTXCriticalSection::Locker Temp(gSafeOutputString);
	char* pArgs;
	pArgs = (char*)&pString + sizeof(pString);
	//todo list: 了解如何设计日志系统
	_vstprintf_s(MatrixCore::msLogbuffer, LOG_BUFFER_SIZE, pString, pArgs);
	OutputDebugString(MatrixCore::msLogbuffer);
}


MTXSemaphore::MTXSemaphore(unsigned int uiCount, unsigned int maxCount)
{
	MTXENGINE_ASSERT(uiCount <= maxCount);
	//
	mSemaphore = CreateSemaphore(NULL, uiCount, maxCount, NULL);

	mMaxCount = maxCount;
}

Matrix::MTXSemaphore::~MTXSemaphore()
{
	BOOL closed = CloseHandle((HANDLE)mSemaphore);
	MTXENGINE_ASSERT(closed);
	mSemaphore = NULL;
}

void Matrix::MTXSemaphore::Enter()
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
	MTXENGINE_ASSERT(result);
}

void Matrix::MTXSemaphore::Leave(unsigned int uiReleaseCount)
{
	BOOL released = ReleaseSemaphore(HANDLE(mSemaphore), uiReleaseCount, NULL);
}

Matrix::MTXMutex::MTXMutex()
{
	mMutex = CreateMutex(NULL, FALSE, NULL);
	MTXENGINE_ASSERT(mMutex);
}

Matrix::MTXMutex::~MTXMutex()
{
	BOOL closed = CloseHandle((HANDLE)mMutex);
	MTXENGINE_ASSERT(closed);
	mMutex = NULL;
}

void Matrix::MTXMutex::Enter()
{
	// result:
	//   WAIT_ABANDONED (0x00000080)
	//   WAIT_OBJECT_0  (0x00000000), signaled
	//   WAIT_TIMEOUT   (0x00000102), [not possible with INFINITE]
	//   WAIT_FAILED    (0xFFFFFFFF), not signaled
	DWORD result = WaitForSingleObject((HANDLE)mMutex, INFINITE);
	MTXENGINE_ASSERT(result != WAIT_FAILED);

}

void Matrix::MTXMutex::Leave()
{
	BOOL  released = ReleaseMutex(HANDLE(mMutex));
	MTXENGINE_ASSERT(released);
}

Matrix::MTXEvent::MTXEvent()
{
	mEvent = NULL;
}

Matrix::MTXEvent::~MTXEvent()
{
	if (mEvent != NULL)
	{
		CloseHandle(mEvent);
	}
}

void Matrix::MTXEvent::Lock()
{
	WaitForSingleObject(mEvent, INFINITE);
}

void Matrix::MTXEvent::unLock()
{
	PulseEvent(mEvent);
}

bool Matrix::MTXEvent::Create(bool bManualReset, const TCHAR* InName)
{
	mEvent = CreateEvent(NULL, bManualReset, 0, InName);
	return mEvent != NULL;
}

void Matrix::MTXEvent::Trigger(void)
{
	SetEvent(mEvent);
}

void Matrix::MTXEvent::Reset(void)
{
	ResetEvent(mEvent);
}

void Matrix::MTXEvent::Pulse(void)
{
	PulseEvent(mEvent);
}

bool Matrix::MTXEvent::Wait(DWORD WaitTime)
{
	return WaitForSingleObject(mEvent, WaitTime) == WAIT_OBJECT_0;
}

bool Matrix::MTXEvent::IsTrigger()
{
	return Wait(0);
}

Matrix::MTXTlsValue::MTXTlsValue()
{
	MTXCriticalSection::Locker  lockgurad(mCriticalSection);
	mSlot = MTXTlsAlloc();
	MTXENGINE_ASSERT(mSlot != 0XFFFFFFFF);
}

Matrix::MTXTlsValue::~MTXTlsValue()
{
	MTXENGINE_ASSERT(mSlot != 0XFFFFFFFF);
	for (size_t i = 0; i < mThreadValueNum; i++)
	{
		MTXDelete(pThreadValue[i]);
	}
	MTXTlsFree(mSlot);
}

void Matrix::MTXTlsValue::SetThreadValue(void* pValue)
{
	MTXCriticalSection::Locker Temp(mCriticalSection);
	pThreadValue[mThreadValueNum] = (MTXStackMem*)pValue;
	mThreadValueNum++;
	MTXSetTlsValue(mSlot, pValue);
}

void* Matrix::MTXTlsValue::GetThreadValue()
{
	return MTXGetTlsValue(mSlot);
}


