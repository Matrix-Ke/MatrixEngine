#pragma once
#include "MTXCore.h"

namespace Matrix
{
	class MATRIXCORE_API MTXTimer
	{
	public:
		MTXTimer();
		~MTXTimer();

		double GetGamePlayTime();
		void UpdateFPS();
		inline double GetFPS() { return mFPS; }
		static MTXTimer* msPtrTimer;
		double GetDeltaTime() { return mDeltaTime; }
		int GetRandSeed();

	private:
		bool mUselargeTime; // 使用最大时间标志
		__int64  mOneSecondTicks; // 一秒内的滴答次数
		__int64  mTimeTickStartCounts;// 开始滴答计数值
		unsigned  long long  mTimeStart; // timeGettime开始时间
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



