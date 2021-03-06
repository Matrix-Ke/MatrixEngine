#pragma once
#include "Core.h"
#include <memory>
#include <mutex>

namespace Matrix
{
    namespace Core
    {
        //关于单例的其他实现方  式， 利用static关键字来实现
        template <typename T>
        class MXSingleton
        {
        public:
            static T &GetInstance()
            {
                static T instance;
                return instance;
            }
            //相关构造函数全部隐藏
            MXSingleton(const T &rhs) = delete;
            MXSingleton(const T &&rhs) = delete;
            void operator=(const T &rhs) = delete;

        protected:
            MXSingleton() = default;
            virtual ~MXSingleton() = default;
        };

        ////此种单例模式不是很好
        // template <typename T>
        // class MXSingleton
        //{
        //	static  T* mPtrSingleton;
        // public:
        //	MXSingleton()
        //	{
        //		MATRIX_ENGINE_ASSERT(!mPtrSingleton);
        //		mPtrSingleton = static_cast<T*>(this);
        //	}

        //	~MXSingleton()
        //	{
        //		MATRIX_ENGINE_ASSERT(mPtrSingleton);
        //		mPtrSingleton = NULL;
        //	}

        //	static T& GetInstance()
        //	{
        //		MATRIX_ENGINE_ASSERT(mPtrSingleton);
        //		return (*mPtrSingleton);
        //	}
        //	static T* GetInstancePtr()
        //	{
        //		return (mPtrSingleton);
        //	}

        //};

        // template <typename T>
        // T* MXSingleton<T>::mPtrSingleton = NULL;

        ////利用锁来实现，lazeySingleTon
        // template<typename T, bool is_thread_safe = true>
        // class LazySingleton
        //{
        // public:
        //	static T& GetInstance()
        //	{
        //		if (is_thread_safe == true)
        //		{
        //			if (mInstance == nullptr)
        //			{
        //				std::lock_guard<std::mutex>   LockGurad(mMutex);
        //				if (mInstance == nullptr)
        //				{
        //					mInstance = std::unique_ptr<T*>(MATRIX_NEW T);
        //				}
        //			}
        //			return *mInstance;
        //		}
        //		else
        //		{
        //			if (mInstance == nullptr)
        //			{
        //				mInstance = std::unique_ptr<T*>(MATRIX_NEW T);
        //			}
        //			return *mInstance;
        //		}
        //	}

        // protected:
        //	LazySingleton() = default;
        //	virtual ~LazySingleton() = default;
        // private:
        //	LazySingleton(const T&&) = delete;
        //	LazySingleton(const T& rhs) = delete;
        //	void operator =(const T& rhs) = delete;

        // private:
        //	std::unique_ptr<T*>   mInstance;
        //	//std::mutex   mMutexl;
        //	//std::lock_guard<std::mutex>  mLockMtx;
        //	static std::mutex    mMutex;

        //};
    }
}
