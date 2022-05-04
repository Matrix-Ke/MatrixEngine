#include "Timer.h"
#include <mmsystem.h>
using namespace Matrix;


MTXTimer* MTXTimer::msPtrTimer = nullptr;
Matrix::MTXTimer::MTXTimer()
{
	InitGameTime();
	msPtrTimer = this;
}

Matrix::MTXTimer::~MTXTimer()
{

}

void Matrix::MTXTimer::InitGameTime()
{
	mFrameCount = 0;
	mFPS = 0;
	mTime = 0;
	mLastFPStime = 0;
	mTimeSlice = 0;
	mLastTime = 0;
	mDeltaTime = 0;

	if (QueryPerformanceFrequency((LARGE_INTEGER*)&mOneSecondTicks))
	{
		mUselargeTime = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&mTimeTickStartCounts);
	}
	else
	{
		mUselargeTime = false;
		mTimeStart = timeGetTime();
	}
}

double Matrix::MTXTimer::GetGamePlayTime()
{
	//返回当前时间，单位毫秒
	__int64  timecurrentCounts;
	if (mUselargeTime)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&timecurrentCounts);
		return ((timecurrentCounts - mTimeTickStartCounts) * (1.0 / mOneSecondTicks) * 1000.0);
	}
	else
	{
		return double((timeGetTime() - mTimeStart));  //timeGetTime函数返回的时间单位为毫秒
	}
}

void Matrix::MTXTimer::UpdateFPS()
{
	mTime = GetGamePlayTime() * 0.001;
	mDeltaTime = mTime - mLastTime;
	mLastTime = mTime;
	if (mTime - mLastFPStime > 1.0f)
	{
		mLastFPStime = mTime;
		//todo list...
		mFPS = mFrameCount;
		mFrameCount = 0;
	}
	else
	{
		mFrameCount++;
	}

}

int Matrix::MTXTimer::GetRandSeed()
{
	return ((LARGE_INTEGER*)mTimeTickStartCounts)->LowPart;
}


