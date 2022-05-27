#pragma once
#include "Core.h"
//�����߳�ͬ�����ƿ��Բο���windows���ı�̵���桷
//��matrix����������ĵ���: Doc/�߳�ͬ������
namespace Matrix
{
	namespace Core
	{
		class MATRIX_CORE_API MSynchronize
		{
		public:
			MSynchronize() {};
			virtual ~MSynchronize() {};
			virtual void* GetHandle() = 0;

			enum MyEnum
			{
				WF_OBJECT0 = 0,
				WF_TIMEOUT = 256,
				WF_FAILED = 0xFFFFFFFF
			};
			static unsigned int WaitAll(MSynchronize** pSynchornize, unsigned int uiNum, bool bWaitAll, DWORD dwMilliseconds = (DWORD)-1);

			static void MXSafeOutputDebugString(const TCHAR* pString, ...);
		};

		class MATRIX_CORE_API MCriticalSection
		{
		private:
			// windows api
			CRITICAL_SECTION mCriticalSection;

		public:
			MCriticalSection()
			{
				InitializeCriticalSection(&mCriticalSection);
				//���ڽ��߳��л����ȴ�״̬�Ŀ����ϴ����Ϊ����߹ؼ��ε����ܣ�Microsoft����ת���ϲ����ؼ����У�
				//����EnterCriticalSection()������һ����ת������ѭ��������һ��ʱ��ŻὫ�߳��л����ȴ�״̬,��ת����һ������Ϊ4000��
				SetCriticalSectionSpinCount(&mCriticalSection, 4000);
			}
			~MCriticalSection()
			{
				DeleteCriticalSection(&mCriticalSection);
			}

			inline void Lock(void)
			{
				// Spin first before entering critical section, causing ring-0 transition and context switch.
				EnterCriticalSection(&mCriticalSection);
			}
			inline bool TryLock()
			{
				return TryEnterCriticalSection(&mCriticalSection);
			}

			inline void Unlock(void)
			{
				LeaveCriticalSection(&mCriticalSection);
			}

			class Locker
			{
			private:
				MCriticalSection& mCriticalSection;

			public:
				Locker(MCriticalSection& inCriticalSection) : mCriticalSection(inCriticalSection)
				{
					mCriticalSection.Lock();
				}
				~Locker()
				{
					mCriticalSection.Unlock();
				}
			};
		};

		class MATRIX_CORE_API MXSemaphore : public MSynchronize
		{
		public:
			MXSemaphore(unsigned int uCount, unsigned int maxCount);
			virtual ~MXSemaphore();

			virtual void Enter();
			virtual void Leave(unsigned int uiReleaseCount);
			virtual void* GetHandle()
			{
				return mSemaphore;
			}

		protected:
			void* mSemaphore;
			unsigned int mMaxCount;
		};

		class MATRIX_CORE_API MXMutex : public MSynchronize
		{
			//�������ں˶�������ȷ��һ�̶߳�ռ��һ����Դ�ķ��ʣ� ���������ں˶���
			//������һ�������Զ���̷߳��ʵ�ͬһ�ڴ����б�����
		public:
			MXMutex();
			virtual ~MXMutex();

			virtual void Enter();
			virtual void Leave();
			virtual void* GetHandle()
			{
				return mMutex;
			}

		protected:
			void* mMutex;
		};

		class MATRIX_CORE_API MXEvent : public MSynchronize
		{
			//�¼�����һ��ʹ�ü����� һ��������ʾ�Զ����û����ֶ����õ�boolֵ���Լ�һ��������ʾ�¼���û�б�������boolֵ��
			//�¼��Ĵ�����ʾһ�������Ѿ���ɡ�
			//�ֶ��¼��������� �ȴ����¼��������̶߳�����ɿɵ��ȣ� �Զ������¼��������� ֻ��һ�����ڵȴ����¼����̱߳�ɿɵ���״̬��
			//һ����;�� ��һ���߳�ִ�г�ʼ��������Ȼ���ٴ�����һ���̣߳�����ִ��ʣ�µĹ���
		protected:
			void* mEvent;

		public:
			virtual void* GetHandle()
			{
				return mEvent;
			}
			MXEvent();
			virtual ~MXEvent();

			// Waits for the event to be signaled before returning
			virtual void Lock();

			// Triggers the event so any waiting threads are allowed access
			virtual void unLock();

			// Creates the event. Manually reset events stay triggered until reset.
			// Named events share the same underlying event.
			// @param bIsManualReset Whether the event requires manual reseting or not
			// @param InName Whether to use a commonly shared event or not. If so this is the name of the event to share.
			// @return Returns TRUE if the event was created, FALSE otherwise
			virtual bool Create(bool bIsManualReset = FALSE, const TCHAR* InName = NULL);

			// Triggers the event so any waiting threads are activated
			virtual void Trigger(void);

			// Resets the event to an untriggered (waitable) state
			virtual void Reset(void);

			// Triggers the event and resets the triggered state NOTE: This behaves
			// differently for auto-reset versus manual reset events. All threads
			// are released for manual reset events and only one is for auto reset
			virtual void Pulse(void);

			// Waits for the event to be triggered
			//@param WaitTime Time in milliseconds to wait before abandoning the event
			//(DWORD)-1 is treated as wait infinite
			//@return TRUE if the event was signaled, FALSE if the wait timed out
			virtual bool Wait(DWORD WaitTime = (DWORD)-1);

			virtual bool IsTrigger();
		};

		//�̱߳��ش洢(TLS) ��һ�ַ����������Ķ��߳̽����е�ÿ���߳̿���ʹ�����ַ����������Դ洢�߳��ض������ݵ�λ�á�
		//�����Ҫ��һ���߳��ڲ��ĸ����������ö��ܷ��ʡ��������̲߳��ܷ��ʵı���������Ϊstatic memory local to a thread �ֲ߳̾���̬������������Ҫ�µĻ�����ʵ�֡������TLS��
		class MXTlsValue
		{
		public:
			MXTlsValue();
			~MXTlsValue();

			enum
			{
				MAX_THREAD_VALUE = 256,
			};
			void SetThreadValue(void* pValue);
			//���Ϊ����δ��������
			void* GetThreadValue();

		protected:
			// mSlot��tls��ʼ��ʱ�ͽ��з��䡣
			unsigned int mSlot = 0XFFFFFFFF;
			class StackMemoryManager* pThreadValue[MAX_THREAD_VALUE];
			unsigned int mThreadValueNum = 0;
			MCriticalSection mCriticalSection;
		};
	}
}
