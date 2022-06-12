#pragma once
#include "Core.h"

namespace Matrix
{
    namespace Core
    {
        class MATRIX_PLATFORM_API MXTimer
        {
        public:
            MXTimer();
            ~MXTimer();

            double GetGamePlayTime();
            void UpdateFPS();
            inline double GetFPS() { return mFPS; }
            static MXTimer *msPtrTimer;
            double GetDeltaTime() { return mDeltaTime; }
            int GetRandSeed();

        private:
            bool mUselargeTime; // 使用最大时间标志
            //__int64也是一种基本数据类型，是微软的virtual C++编译器定义的一种基本数据类型，而不是C++标准规范（协会）里定义的一种基本数据类型
            // unsigned long long  8字节整型
            unsigned long long mOneSecondTicks;      // 一秒内的滴答次数
            unsigned long long mTimeTickStartCounts; // 开始滴答计数值
            unsigned long long mTimeStart;           // timeGettime开始时间
            int mFrameCount;
            double mFPS;
            double mTime;
            double mLastFPStime;
            double mTimeSlice;
            double mDeltaTime;
            double mLastTime;
            void InitGameTime();
        };
    }
}
