#pragma once
#include "Core.h"

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
		//__int64Ҳ��һ�ֻ����������ͣ���΢����virtual C++�����������һ�ֻ����������ͣ�������C++��׼�淶��Э�ᣩ�ﶨ���һ�ֻ�����������
		//unsigned long long  8�ֽ�����
		unsigned long long  mOneSecondTicks; // һ���ڵĵδ����
		unsigned long long  mTimeTickStartCounts;// ��ʼ�δ����ֵ
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


