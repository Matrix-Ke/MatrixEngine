#pragma once
#include "Core.h"
//关于线程同步机制可以参考《windows核心编程第五版》
//在matrix引擎中相关文档见: Doc/线程同步机制
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
				//由于将线程切换到等待状态的开销较大，因此为了提高关键段的性能，Microsoft将旋转锁合并到关键段中，
				//这样EnterCriticalSection()会先用一个旋转锁不断循环，尝试一段时间才会将线程切换到等待状态,旋转次数一般设置为4000。
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
			//互斥量内核对象用来确保一线程独占对一个资源的访问， 互斥量是内核对象，
			//互斥量一般用来对多个线程访问的同一内存块进行保护。
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
			//事件包含一个使用计数， 一个用来表示自动重置还是手动重置的bool值，以及一个用来表示事件有没有被触发的bool值。
			//事件的触发表示一个操作已经完成。
			//手动事件被触发： 等待该事件的所有线程都将变成可调度； 自动重置事件被触发： 只有一个正在等待该事件的线程变成可调度状态。
			//一般用途： 让一个线程执行初始化工作，然后再触发另一个线程，让他执行剩下的工作
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

		//线程本地存储(TLS) 是一种方法，给定的多线程进程中的每个线程可以使用这种方法分配用以存储线程特定的数据的位置。
		//如果需要在一个线程内部的各个函数调用都能访问、但其它线程不能访问的变量（被称为static memory local to a thread 线程局部静态变量），就需要新的机制来实现。这就是TLS。
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
			//如果为空则还未分配数据
			void* GetThreadValue();

		protected:
			// mSlot在tls初始化时就进行分配。
			unsigned int mSlot = 0XFFFFFFFF;
			class StackMemoryManager* pThreadValue[MAX_THREAD_VALUE];
			unsigned int mThreadValueNum = 0;
			MCriticalSection mCriticalSection;
		};
	}
}
