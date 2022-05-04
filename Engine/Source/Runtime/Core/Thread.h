#pragma once
#include "Core.h"
#include "Synchronize.h"


namespace Matrix
{
	//ֻ����һ���߳̿�������߳��࣬û���̰߳�ȫ�ԣ�2���߳�ͬʱ��������߳�����Щ�ط������
	class MATRIXCORE_API MTXThread
	{
	public:
		enum Priority
		{
			Low,
			Normal,
			High,
		};
		enum ThreadState
		{
			TS_START,
			TS_SUSPEND,
			TS_STOP,
		};
	public:
		MTXThread();
		// �̷߳����������� c++����ͨ����������������ȷ�����٣�������ϵͳ��ȷ�ͷ��߳�ջʹ�õ��ڴ棻��
		//����ϵͳ���̵߳��˳�����Ϊ�̺߳����ķ���ֵ��ϵͳ�����̵߳��ں˶����ʹ�ü���
		~MTXThread();

		void SetPriority(const Priority& p);
		Priority GetPriority() const;
		void SetStackSize(unsigned int uSize);
		unsigned int GetStackSize() const;

		void Start();
		void Suspend();

		bool IsRunning() const;
		static void Sleep(DWORD dwMillseconds);

		bool IsStopTrigger();
		void Stop();

	public:
		static void SetThreadName(const char* name);
		inline ThreadState GetThreadState()
		{
			return mThreadState;
		}
	public:
		virtual void Run() = 0;
		virtual const TCHAR* GetThreadName();

	private:
		//static unsigned  THREAD_CALLBACK ThreadProc(void* t);
		static DWORD  THREAD_CALLBACK ThreadProc(void* t);

	private:
		void* mThread;
		char* mThreadName;

		Priority mPriority;
		unsigned int mStackSize;

	protected:
		ThreadState mThreadState;
		MTXEvent mStopEvent;

	};
}



