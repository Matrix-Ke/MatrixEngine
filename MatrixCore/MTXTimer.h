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
		bool mUselargeTime; // ʹ�����ʱ���־
		__int64  mOneSecondTicks; // һ���ڵĵδ����
		__int64  mTimeTickStartCounts;// ��ʼ�δ����ֵ
		unsigned  long long  mTimeStart; // timeGettime��ʼʱ��
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



