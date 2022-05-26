#pragma once
#include "Pointer.h"
#include "Container/String.h"
#include "Container/Array.h "

//#include "Map.h"
//#include "Vector2.h"
//#include "Vector3.h"
//#include "Vector3W.h"
//#include "Matrix3X3.h"
//#include "Matrix3X3W.h"
//#include "Quat.h"
//#include "AABB3.h"
//#include "Sphere3.h"
//#include "OBB3.h"
//#include "Rect2.h"
//#include "Line3.h"
//#include "Ray3.h"
//#include "Segment3.h"
//#include "Rectangle3.h"
//#include "Triangle3.h"
//#include "Plane3.h"
//#include "Transform.h"
//һ���ڲ�ʹ�õĴ�object��̳еģ���Ҫ�������Եģ���������rtti���������ԣ�VSTYPE_MARCO
//���������ڲ���object��̳еģ�֧��������Ϊ��λ��ʵ�����л�

//�Զ������ͣ������Ҫ֧���Զ�������л���Ҫ��CUSTOMTYPE_MARCO  ���������������ԣ�
//����������԰汾�����Լ�Ҫ�ƶ���
namespace Matrix
{
#define DEFINE_TYPE(TypeName)              \
     template <typename T>                  \
     struct TIs##TypeName##Type             \
     {                                      \
         enum                               \
         {                                  \
             Value = false                  \
         };                                 \
     };                                     \
     template <typename T>                  \
     struct TIs##TypeName##PointerType      \
     {                                      \
         enum                               \
         {                                  \
             Value = false                  \
         };                                 \
     };                                     \
     template <typename T>                  \
     struct TIs##TypeName##SmartPointerType \
     {                                      \
         enum                               \
         {                                  \
             Value = false                  \
         };                                 \
     };
#define DEFINE_TYPE_INSTANCE(TypeName, ClassName)                      \
     class ClassName;                                                   \
     template <>                                                        \
     struct TIs##TypeName##Type<ClassName>                              \
     {                                                                  \
         enum                                                           \
         {                                                              \
             Value = true                                               \
         };                                                             \
     };                                                                 \
     template <>                                                        \
     struct TIs##TypeName##PointerType<ClassName *>                     \
     {                                                                  \
         enum                                                           \
         {                                                              \
             Value = true                                               \
         };                                                             \
     };                                                                 \
     template <>                                                        \
     struct TIs##TypeName##PointerType<const ClassName *>               \
     {                                                                  \
         enum                                                           \
         {                                                              \
             Value = true                                               \
         };                                                             \
     };                                                                 \
     template <>                                                        \
     struct TIs##TypeName##SmartPointerType<VSPointer<ClassName>>       \
     {                                                                  \
         enum                                                           \
         {                                                              \
             Value = true                                               \
         };                                                             \
     };                                                                 \
     template <>                                                        \
     struct TIs##TypeName##SmartPointerType<const VSPointer<ClassName>> \
     {                                                                  \
         enum                                                           \
         {                                                              \
             Value = true                                               \
         };                                                             \
     };

	// custom type
	DEFINE_TYPE(Custom)
#define CUSTOMTYPE_MARCO(ClassName) \
     DEFINE_TYPE_INSTANCE(Custom, ClassName)

		// vs type
		DEFINE_TYPE(VS)
#define VSTYPE_MARCO(ClassName) \
     DEFINE_TYPE_INSTANCE(VS, ClassName)

		template <typename T>
	struct TIsVSEnumType
	{
		enum
		{
			Value = false
		};
	};
#define VSENUMTYPE_MARCO(ClassName) \
     template <>                     \
     struct TIsVSEnumType<ClassName> \
     {                               \
         enum                        \
         {                           \
             Value = true            \
         };                          \
     };

	// cache resource
	DEFINE_TYPE(VSCacheResource)
#define DECLARE_CACHE_RESOURCE_TYPE(ClassName) \
     DEFINE_TYPE_INSTANCE(VSCacheResource, ClassName)

		DECLARE_CACHE_RESOURCE_TYPE(VSTextureCache)
	DECLARE_CACHE_RESOURCE_TYPE(VSShaderMapCache)


	//�����̬���ͱ�ʾ������Դ����Ҫ����������ļ���һ���� VSObject ��Ҫ���������Դ������ʱ���������Դ·��
	template <typename T>
	struct TIsVSResourceProxyType
	{
		enum
		{
			Value = false
		};
	};
	template <typename T>
	struct TIsVSResourceProxyPointerType
	{
		enum
		{
			Value = false
		};
	};
	template <class T>
	class VSResourceProxy;
	template <typename T>
	struct TIsVSResourceProxyType<VSResourceProxy<T>>
	{
		enum
		{
			Value = true
		};
	};
	template <typename T>
	struct TIsVSResourceProxyPointerType<VSPointer<VSResourceProxy<T>>>
	{
		enum
		{
			Value = true
		};
	};

	// string
	template <typename T>
	struct TIsVSStringType
	{
		enum
		{
			Value = false
		};
	};
	template <>
	struct TIsVSStringType<Container::MString>
	{
		enum
		{
			Value = true
		};
	};

	// name
	template <typename T>
	struct TIsVSUsedNameType
	{
		enum
		{
			Value = false
		};
	};
	class VSUsedName;
	template <>
	struct TIsVSUsedNameType<VSUsedName>
	{
		enum
		{
			Value = true
		};
	};



	//// Archive on need Loop Container::MArray
	//template <typename T>
	//struct TIsNoNeedLoop
	//{
	//	enum
	//	{
	//		Value = IS_ENUM(T) || TIsArithmeticType<T>::Value
	//	};
	//};
	//template <>
	//struct TIsNoNeedLoop<VSVector3W>
	//{
	//	enum
	//	{
	//		Value = true
	//	};
	//};
	//template <>
	//struct TIsNoNeedLoop<VSVector3>
	//{
	//	enum
	//	{
	//		Value = true
	//	};
	//};
	//template <>
	//struct TIsNoNeedLoop<VSVector2>
	//{
	//	enum
	//	{
	//		Value = true
	//	};
	//};
	//template <>
	//struct TIsNoNeedLoop<VSMatrix3X3W>
	//{
	//	enum
	//	{
	//		Value = true
	//	};
	//};
	//template <>
	//struct TIsNoNeedLoop<VSMatrix3X3>
	//{
	//	enum
	//	{
	//		Value = true
	//	};
	//};
	//template <>
	//struct TIsNoNeedLoop<VSQuat>
	//{
	//	enum
	//	{
	//		Value = true
	//	};
	//};
	//template <>
	//struct TIsNoNeedLoop<VSAABB3>
	//{
	//	enum
	//	{
	//		Value = true
	//	};
	//};
	//template <>
	//struct TIsNoNeedLoop<VSSphere3>
	//{
	//	enum
	//	{
	//		Value = true
	//	};
	//};
	//template <>
	//struct TIsNoNeedLoop<VSOBB3>
	//{
	//	enum
	//	{
	//		Value = true
	//	};
	//};
	//template <>
	//struct TIsNoNeedLoop<VSRect2>
	//{
	//	enum
	//	{
	//		Value = true
	//	};
	//};
	//template <>
	//struct TIsNoNeedLoop<VSLine3>
	//{
	//	enum
	//	{
	//		Value = true
	//	};
	//};
	//template <>
	//struct TIsNoNeedLoop<VSRay3>
	//{
	//	enum
	//	{
	//		Value = true
	//	};
	//};
	//template <>
	//struct TIsNoNeedLoop<VSSegment3>
	//{
	//	enum
	//	{
	//		Value = true
	//	};
	//};
	//template <>
	//struct TIsNoNeedLoop<VSRectangle3>
	//{
	//	enum
	//	{
	//		Value = true
	//	};
	//};
	//template <>
	//struct TIsNoNeedLoop<VSTriangle3>
	//{
	//	enum
	//	{
	//		Value = true
	//	};
	//};
	//template <>
	//struct TIsNoNeedLoop<VSPlane3>
	//{
	//	enum
	//	{
	//		Value = true
	//	};
	//};



	//template <typename T>
	//struct TIsNeedGC
	//{
	//	enum
	//	{
	//		Value = TIsVSPointerType<T>::Value ||
	//		TIsVSSmartPointerType<T>::Value ||
	//		TIsCustomType<T>::Value ||
	//		TIsVSType<T>::Value
	//	};
	//};
	//template <typename T>
	//struct TIsNeedGC<Container::MArray<T>>
	//{
	//	enum
	//	{
	//		Value = TIsNeedGC<T>::Value
	//	};
	//};
	//template <typename T>
	//struct TIsNeedGC<Container::MArrayOrder<T>>
	//{
	//	enum
	//	{
	//		Value = TIsNeedGC<T>::Value
	//	};
	//};

	//template <typename Key, typename Value>
	//struct TIsNeedGC<Container::MMapOrder<Key, Value>>
	//{
	//	enum
	//	{
	//		Value = TIsNeedGC<Key>::Value || TIsNeedGC<Value>::Value
	//	};
	//};
	//template <typename Key, typename Value>
	//struct TIsNeedGC<Container::MMap<Key, Value>>
	//{
	//	enum
	//	{
	//		Value = TIsNeedGC<Key>::Value || TIsNeedGC<Value>::Value
	//	};
	//};
}
