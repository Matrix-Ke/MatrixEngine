#include "Timer.h"
#include <mmsystem.h>
using namespace Matrix::Core;

MXTimer *MXTimer::msPtrTimer = nullptr;
Matrix::Core::MXTimer::MXTimer()
{
    InitGameTime();
    msPtrTimer = this;
}

Matrix::Core::MXTimer::~MXTimer()
{
}

void Matrix::Core::MXTimer::InitGameTime()
{
    mFrameCount = 0;
    mFPS = 0;
    mTime = 0;
    mLastFPStime = 0;
    mTimeSlice = 0;
    mLastTime = 0;
    mDeltaTime = 0;

    if (QueryPerformanceFrequency((LARGE_INTEGER *)&mOneSecondTicks))
    {
        mUselargeTime = true;
        QueryPerformanceCounter((LARGE_INTEGER *)&mTimeTickStartCounts);
    }
    else
    {
        mUselargeTime = false;
        mTimeStart = timeGetTime();
    }
}

double Matrix::Core::MXTimer::GetGamePlayTime()
{
    //���ص�ǰʱ�䣬��λ����
    __int64 timecurrentCounts;
    if (mUselargeTime)
    {
        QueryPerformanceCounter((LARGE_INTEGER *)&timecurrentCounts);
        return ((timecurrentCounts - mTimeTickStartCounts) * (1.0 / mOneSecondTicks) * 1000.0);
    }
    else
    {
        return double((timeGetTime() - mTimeStart)); // timeGetTime�������ص�ʱ�䵥λΪ����
    }
}

void Matrix::Core::MXTimer::UpdateFPS()
{
    mTime = GetGamePlayTime() * 0.001;
    mDeltaTime = mTime - mLastTime;
    mLastTime = mTime;
    if (mTime - mLastFPStime > 1.0f)
    {
        mLastFPStime = mTime;
        // todo list...
        mFPS = mFrameCount;
        mFrameCount = 0;
    }
    else
    {
        mFrameCount++;
    }
}

int Matrix::Core::MXTimer::GetRandSeed()
{
    return ((LARGE_INTEGER *)mTimeTickStartCounts)->LowPart;
}
