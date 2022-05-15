#pragma once
#include "Core.h"
#include <memory>
#include <mutex>

namespace Matrix
{
	namespace Core
	{
		//���ڵ���������ʵ�ַ�  ʽ�� ����static�ؼ�����ʵ�� 
		template <typename T>
		class MTXSingleton
		{
		public:
			static T& GetInstance()
			{
				static T instance;
				return instance;
			}
			//��ع��캯��ȫ������
			MTXSingleton(const T& rhs) = delete;
			MTXSingleton(const T&& rhs) = delete;
			void operator= (const T& rhs) = delete;

		protected:
			MTXSingleton() = default;
			virtual ~MTXSingleton() = default;
		};



		////���ֵ���ģʽ���Ǻܺ�
		//template <typename T>
		//class MTXSingleton
		//{
		//	static  T* mPtrSingleton;
		//public:
		//	MTXSingleton()
		//	{
		//		MX_ENGINE_ASSERT(!mPtrSingleton);
		//		mPtrSingleton = static_cast<T*>(this);
		//	}

		//	~MTXSingleton()
		//	{
		//		MX_ENGINE_ASSERT(mPtrSingleton);
		//		mPtrSingleton = NULL;
		//	}

		//	static T& GetInstance()
		//	{
		//		MX_ENGINE_ASSERT(mPtrSingleton);
		//		return (*mPtrSingleton);
		//	}
		//	static T* GetInstancePtr()
		//	{
		//		return (mPtrSingleton);
		//	}

		//};

		//template <typename T>
		//T* MTXSingleton<T>::mPtrSingleton = NULL;





		////��������ʵ�֣�lazeySingleTon
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
}

