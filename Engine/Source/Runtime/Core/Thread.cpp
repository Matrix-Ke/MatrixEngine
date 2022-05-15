#include "Thread.h"
#include <process.h>

using namespace Matrix::Core;

MTXThread::MTXThread() : mThread(NULL), mPriority(Normal), mStackSize(0), mThreadName(NULL)
{
	MX_ENGINE_ASSERT(!IsRunning());
	//CreateThread: ϵͳ�ᴴ��һ���߳��ں˶�������߳��ں˶������̱߳������һ����С�����ݽṹ������ϵͳ��������ݽṹ�������̡߳�
	//security_attibutes: �����ʹ���߳��ں�Ĭ�ϰ�ȫ���ԣ�����NULL��
	//cbStackSize:  ָ���߳�ջʹ�ö��ٵ�ַ�ռ䣬�����0�� �ͻ�Ԥ��һ�����򣬲�������/STACK������������ָ���Ĵ洢���������洢����
	//��ʵ���ӽ���ʹ�ã� _beginthreadex, ��ʹ��CreateThreads����Ϊ����ı�׼c/c++����Ϊ���߳�Ӧ�ó������ơ� ȫ�ֵı����ᵼ�³�������
	mThread = ::CreateThread(0, mStackSize, ThreadProc, this, CREATE_SUSPENDED, NULL);
	//mThread = (HANDLE)_beginthreadex(0, mStackSize, ThreadProc, this, CREATE_SUSPENDED, NULL);
	MX_ENGINE_ASSERT(mThread);
	mThreadState = TS_SUSPEND;
	SetPriority(mPriority);
	mStopEvent.Create(true);
	mStopEvent.Reset();

}

Matrix::Core::MTXThread::~MTXThread()
{
	if (IsRunning())
	{
		//Terminatethread���ɱ���̡߳�ɱ�������̡߳� ExitThread���Լ������Լ�(����ϵͳ��������߳�ʹ�õ����в���ϵͳ��Դ������c++��Դ�����Ǳ����٣�
		//TerminateThread�������첽�ģ����������˲��������߳��Ѿ���ֹ�ˣ��̵߳��ں˶���ʹ�ü�����ݼ���
		TerminateThread(mThread, 0);
	}
	if (mThread)
	{
		CloseHandle(mThread);
	}
}

void Matrix::Core::MTXThread::SetPriority(const Priority& p)
{
	int nPriority = THREAD_PRIORITY_NORMAL;

	if (p == Low)
		nPriority = THREAD_PRIORITY_BELOW_NORMAL;
	else if (p == Normal)
		nPriority = THREAD_PRIORITY_NORMAL;
	else if (p == High)
		nPriority = THREAD_PRIORITY_ABOVE_NORMAL;

	SetThreadPriority(mThread, nPriority);
}

void Matrix::Core::MTXThread::Start()
{
	if (mThreadState == TS_SUSPEND)
	{
		ResumeThread((HANDLE)mThread);
		mThreadState = TS_START;
	}
}

void Matrix::Core::MTXThread::Suspend()
{
	if (mThreadState == TS_START)
	{
		SuspendThread((HANDLE)mThread);
		mThreadState = TS_SUSPEND;
	}
}

bool Matrix::Core::MTXThread::IsRunning() const
{
	if (NULL != mThread)
	{
		DWORD exitCode = 0;
		if (GetExitCodeThread(mThread, &exitCode))
		{
			if (STILL_ACTIVE == exitCode)
			{
				return true;
			}
		}
	}
	//ͨ��exitCode���ж��̵߳�״̬��
	return false;
}

void Matrix::Core::MTXThread::Sleep(DWORD dwMillseconds)
{
	::Sleep(dwMillseconds);
}

bool Matrix::Core::MTXThread::IsStopTrigger()
{
	return mStopEvent.IsTrigger();
}

void Matrix::Core::MTXThread::Stop()
{
	if (mThreadState == TS_START)
	{
		MX_ENGINE_ASSERT(this->IsRunning());
		MX_ENGINE_ASSERT(NULL != mThread);

		mStopEvent.Trigger();
		mThreadState = TS_STOP;
		// wait for the thread to terminate
		WaitForSingleObject(mThread, INFINITE);
		CloseHandle(mThread);
		mThread = NULL;
	}
}

void Matrix::Core::MTXThread::SetThreadName(const char* name)
{
	//strcpy_sֻ�����ַ������ƣ����������������ַ�������֮�⣬���Ḵ���ַ����Ľ�����'\0'
	//strlen()����������ַ�������Ϊ��Ч���ȣ��Ȳ������ַ���ĩβ������ ��\0����
	//sizeof()����������ĳ��Ȱ����ַ���ĩβ�Ľ����� ��\0����
	//���ں����ڲ�ʹ��sizeof()����ɺ������βδ�����ַ�����ĳ���ʱ���õ��Ľ��Ϊָ��ĳ��ȣ��ȶ�Ӧ�������ֽ������������ַ����ĳ��ȣ��˴�һ��ҪС�ġ�
	//char* a = MATRIX_NEW char[100];
	// update the Windows thread name so that it shows up correctly
	// in the Debugger
	struct THREADNAME_INFO
	{
		DWORD dwType;     // must be 0x1000
		LPCSTR szName;    // pointer to name (in user address space)
		DWORD dwThreadID; // thread ID (-1 = caller thread)
		DWORD dwFlags;    // reserved for future use, must be zero
	};

	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = name;
	info.dwThreadID = ::GetCurrentThreadId();
	info.dwFlags = 0;
	__try
	{
		RaiseException(0x406D1388, 0, sizeof(info) / sizeof(DWORD), (ULONG_PTR*)&info);
	}
	__except (EXCEPTION_CONTINUE_EXECUTION)
	{
	}

	//mThreadName = MATRIX_NEW char;
}

const TCHAR* Matrix::Core::MTXThread::GetThreadName()
{
	return nullptr;
}

DWORD THREAD_CALLBACK Matrix::Core::MTXThread::ThreadProc(void* t)
{
	return 0;
}

