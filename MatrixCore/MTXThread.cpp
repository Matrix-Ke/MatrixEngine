//#include "pch.h"
//#include "MTXThread.h"
//#include <process.h>
//
//using namespace Matrix;
//
//MTXThread::MTXThread() : mThread(NULL), mPriority(Normal), mStackSize(0), mThreadName(NULL)
//{
//	MTXENGINE_ASSERT(!IsRunning());
//	//CreateThread: 系统会创建一个线程内核对象，这个线程内核对象不是线程本身而是一个较小的数据结构，操作系统用这个数据结构来管理线程。
//	//security_attibutes: 如果想使用线程内核默认安全属性，传入NULL。
//	//cbStackSize:  指定线程栈使用多少地址空间，如果是0， 就会预定一个区域，并根据由/STACK链接器，开关指定的存储量来调拨存储器。
//	//其实更加建议使用： _beginthreadex, 不使用CreateThreads是因为最早的标准c/c++不是为多线程应用程序而设计。 全局的变量会导致程序会出错。
//	mThread = ::CreateThread(0, mStackSize, ThreadProc, this, CREATE_SUSPENDED, NULL);
//	//mThread = (HANDLE)_beginthreadex(0, mStackSize, ThreadProc, this, CREATE_SUSPENDED, NULL);
//	MTXENGINE_ASSERT(mThread);
//	mThreadState = TS_SUSPEND;
//	SetPriority(mPriority);
//	mStopEvent.Create(true);
//	mStopEvent.Reset();
//
//}
//
//Matrix::MTXThread::~MTXThread()
//{
//	if (IsRunning())
//	{
//		//Terminatethread是由别的线程“杀死”该线程。 ExitThread是自己结束自己(操作系统会清理该线程使用的所有操作系统资源，但是c++资源并不是被销毁）
//		//TerminateThread函数是异步的，函数返回了并不代表线程已经终止了，线程的内核对象使用计数会递减。
//		TerminateThread(mThread, 0);
//	}
//	if (mThread)
//	{
//		CloseHandle(mThread);
//	}
//}
//
//void Matrix::MTXThread::SetPriority(const Priority& p)
//{
//	int nPriority = THREAD_PRIORITY_NORMAL;
//	int nPriority = THREAD_PRIORITY_NORMAL;
//
//	if (p == Low)
//		nPriority = THREAD_PRIORITY_BELOW_NORMAL;
//	else if (p == Normal)
//		nPriority = THREAD_PRIORITY_NORMAL;
//	else if (p == High)
//		nPriority = THREAD_PRIORITY_ABOVE_NORMAL;
//
//	SetThreadPriority(mThread, nPriority);
//}
//
//void Matrix::MTXThread::Start()
//{
//	if (mThreadState == TS_SUSPEND)
//	{
//		ResumeThread((HANDLE)mThread);
//		mThreadState = TS_START;
//	}
//}
//
//void Matrix::MTXThread::Suspend()
//{
//	if (mThreadState == TS_START)
//	{
//		SuspendThread((HANDLE)mThread);
//		mThreadState = TS_SUSPEND;
//	}
//}
//
//bool Matrix::MTXThread::IsRunning() const
//{
//	if (NULL != mThread)
//	{
//		DWORD exitCode = 0;
//		if (GetExitCodeThread(mThread, &exitCode))
//		{
//			if (STILL_ACTIVE == exitCode)
//			{
//				return true;
//			}
//		}
//		return false;
//	}
//}
//
//void Matrix::MTXThread::Sleep(DWORD dwMillseconds)
//{
//	::Sleep(dwMillseconds);
//}
//
//bool Matrix::MTXThread::IsStopTrigger()
//{
//	return mStopEvent.IsTrigger();
//}
//
//void Matrix::MTXThread::Stop()
//{
//	if (mThreadState == TS_START)
//	{
//		MTXENGINE_ASSERT(this->IsRunning());
//		MTXENGINE_ASSERT(NULL != mThread);
//
//		mStopEvent.Trigger();
//		mThreadState = TS_STOP;
//		// wait for the thread to terminate
//		WaitForSingleObject(mThread, INFINITE);
//		CloseHandle(mThread);
//		mThread = NULL;
//	}
//}
//
//void Matrix::MTXThread::SetThreadName(const char* name)
//{
//	//strcpy_s只用于字符串复制，并且它不仅复制字符串内容之外，还会复制字符串的结束符'\0'
//	//strlen()函数求出的字符串长度为有效长度，既不包含字符串末尾结束符 ‘\0’；
//	//sizeof()操作符求出的长度包含字符串末尾的结束符 ‘\0’；
//	//当在函数内部使用sizeof()求解由函数的形参传入的字符数组的长度时，得到的结果为指针的长度，既对应变量的字节数，而不是字符串的长度，此处一定要小心。
//	//char* a = new char[100];
//	// update the Windows thread name so that it shows up correctly
//	// in the Debugger
//	struct THREADNAME_INFO
//	{
//		DWORD dwType;     // must be 0x1000
//		LPCSTR szName;    // pointer to name (in user address space)
//		DWORD dwThreadID; // thread ID (-1 = caller thread)
//		DWORD dwFlags;    // reserved for future use, must be zero
//	};
//
//	THREADNAME_INFO info;
//	info.dwType = 0x1000;
//	info.szName = name;
//	info.dwThreadID = ::GetCurrentThreadId();
//	info.dwFlags = 0;
//	__try
//	{
//		RaiseException(0x406D1388, 0, sizeof(info) / sizeof(DWORD), (ULONG_PTR*)&info);
//	}
//	__except (EXCEPTION_CONTINUE_EXECUTION)
//	{
//	}
//
//	//mThreadName = new char;
//}
//
//const TCHAR* Matrix::MTXThread::GetThreadName()
//{
//	return nullptr;
//}
//
//DWORD THREAD_CALLBACK Matrix::MTXThread::ThreadProc(void* t)
//{
//	return 0;
//}
//
