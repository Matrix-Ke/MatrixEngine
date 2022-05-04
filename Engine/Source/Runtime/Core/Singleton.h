#pragma once
#include "Core.h"
#include <memory>
#include <mutex>

namespace Matrix
{
	//关于单例的其他实现方  式， 利用static关键字来实现 
	template <typename T>
	class MTXSingleton
	{
	public:
		static T& GetInstance()
		{
			static T instance;
			return instance;
		}
		//相关构造函数全部隐藏
		MTXSingleton(const T& rhs) = delete;
		MTXSingleton(const T&& rhs) = delete;
		void operator= (const T& rhs) = delete;

	protected:
		MTXSingleton() = default;
		virtual ~MTXSingleton() = default;
	};



	////此种单例模式不是很好
	//template <typename T>
	//class MTXSingleton
	//{
	//	static  T* mPtrSingleton;
	//public:
	//	MTXSingleton()
	//	{
	//		MTXENGINE_ASSERT(!mPtrSingleton);
	//		mPtrSingleton = static_cast<T*>(this);
	//	}

	//	~MTXSingleton()
	//	{
	//		MTXENGINE_ASSERT(mPtrSingleton);
	//		mPtrSingleton = NULL;
	//	}

	//	static T& GetInstance()
	//	{
	//		MTXENGINE_ASSERT(mPtrSingleton);
	//		return (*mPtrSingleton);
	//	}
	//	static T* GetInstancePtr()
	//	{
	//		return (mPtrSingleton);
	//	}

	//};

	//template <typename T>
	//T* MTXSingleton<T>::mPtrSingleton = NULL;





	////利用锁来实现，lazeySingleTon
	//template<typename T, bool is_thread_safe = true>
	//class LazySingleton
	//{
	//public:
	//	static T& GetInstance()
	//	{
	//		if (is_thread_safe == true)
	//		{
	//			if (mInstance == nullptr)
	//			{
	//				std::lock_guard<std::mutex>   LockGurad(mMutex);
	//				if (mInstance == nullptr)
	//				{
	//					mInstance = std::unique_ptr<T*>(new T);
	//				}
	//			}
	//			return *mInstance;
	//		}
	//		else
	//		{
	//			if (mInstance == nullptr)
	//			{
	//				mInstance = std::unique_ptr<T*>(new T);
	//			}
	//			return *mInstance;
	//		}
	//	}

	//protected:
	//	LazySingleton() = default;
	//	virtual ~LazySingleton() = default;
	//private:
	//	LazySingleton(const T&&) = delete;
	//	LazySingleton(const T& rhs) = delete;
	//	void operator =(const T& rhs) = delete;

	//private:
	//	std::unique_ptr<T*>   mInstance;
	//	//std::mutex   mMutexl;
	//	//std::lock_guard<std::mutex>  mLockMtx;
	//	static std::mutex    mMutex;

	//};

}

