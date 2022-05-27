#pragma once
#include "Core.h"
#include "Synchronize.h"

namespace Matrix
{
    namespace Core
    {
        //只允许一个线程控制这个线程类，没有线程安全性，2个线程同时控制这个线程类有些地方会出错
        class MATRIX_CORE_API MXThread
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
            MXThread();
            // 线程返回清理工作： c++对象都通过其析构函数被正确的销毁；　操作系统正确释放线程栈使用的内存；　
            //操作系统把线程的退出码设为线程函数的返回值；系统减少线程的内核对象的使用计数
            ~MXThread();

            void SetPriority(const Priority &p);
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
            static void SetThreadName(const char *name);
            inline ThreadState GetThreadState()
            {
                return mThreadState;
            }

        public:
            virtual void Run() = 0;
            virtual const TCHAR *GetThreadName();

        private:
            // static unsigned  THREAD_CALLBACK ThreadProc(void* t);
            static DWORD THREAD_CALLBACK ThreadProc(void *t);

        private:
            void *mThread;
            char *mThreadName;

            Priority mPriority;
            unsigned int mStackSize;

        protected:
            ThreadState mThreadState;
            MXEvent mStopEvent;
        };
    }
}
