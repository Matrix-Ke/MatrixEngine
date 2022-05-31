#pragma once
#include "Function/EngineInit.h"
#include "Function/Meta/Rtti.h"
#include "Function/Meta/Object.h"
#include "Function/Meta/Priority.h"

namespace Matrix
{
	struct TestStruct
	{
		int m_sInt;
		float m_sFloat;
		TestStruct()
		{
			m_sInt = 1;
			m_sFloat = 4.0f;
		}
	};

	class classname : public MObject
	{
	public:
		classname();
		classname(int a, float b);
		~classname();
		//声明
		DECLARE_RTTI;
		//static VSRtti   ms_Type;
		//static VSPriority  ms_Priority;

		DECLARE_INITIAL;
		static bool InitialDefaultState();
		static bool TerminalDefaultState();

	public:
		virtual bool Test();
	public:
		int mTestInt;
		float  mTestFloat;
	};
	DECLARE_Ptr(classname);
	VSTYPE_MARCO(classname);


	class ClassInfoObject : public MObject
	{
	public:
		ClassInfoObject();
		~ClassInfoObject();
	public:
		//声明declare_classinfo
		static VSRtti   ms_Type;
		static VSPriority  ms_Priority; //声明初始化默认构造函数顺序

		//初始化默认类状态
		static bool InitialDefaultState();
		static bool TerminateDefaltState();

		//#define DECLARE_INITIAL    
		static bool RegisterClassToMainFactory; //利用静态成员变量初始化来调用初始化函数
		static bool bRegistered;
		static bool RegisterClassInfoToEngineFactory();
		static ClassInfoObject* NewObject(); //创建类默认对象
		static bool InitialProperty(VSRtti* pRtti); //Property
		static bool TerminalProperty();


	public:
		//virtual bool Test();

	public:
		int mInt;
		Container::MArray<int>   mArrayInt;
		float* mFloatData;
		unsigned mFloatDataNum;
		float    mFixedFloatData[4];

		TestStruct		mTestStruct;
		classname* mClassObject1;
		classnamePtr	mClassObject2;
		classname		mClassObject3;
		VSUsedName      mName;
		Container::MString	mString;

		enum MyEnum
		{
			E1,
			E2,
			E3,
			E_MAX
		};
		MyEnum   mEnum;
	};
	DECLARE_Ptr(ClassInfoObject)
	VSTYPE_MARCO(ClassInfoObject)

}
