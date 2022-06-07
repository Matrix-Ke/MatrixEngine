#include "ClassInfoObject.h"
#include "Function/Meta/Property.h"

#include "Function/EngineInit.h"


using namespace Matrix;
//实现RTTI
IMPLEMENT_RTTI(classname, MObject)
IMPLEMENT_INITIAL_BEGIN(classname)
ADD_INITIAL_FUNCTION_WITH_PRIORITY(InitialDefaultState)
ADD_TERMINAL_FUNCTION(TerminalDefaultState)
IMPLEMENT_INITIAL_END
//添加属性
BEGIN_ADD_PROPERTY(classname, MObject)
REGISTER_PROPERTY(mTestInt, TestInt, VSProperty::F_SAVE_LOAD_CLONE)
REGISTER_PROPERTY(mTestFloat, TestFloat, VSProperty::F_SAVE_LOAD_CLONE)
END_ADD_PROPERTY



Matrix::classname::classname()
{
	mTestInt = 555;
	mTestFloat = 555.f;
}

Matrix::classname::classname(int a, float b)
{
	mTestInt = a;
	mTestFloat = b;
}

Matrix::classname::~classname()
{
}

bool Matrix::classname::InitialDefaultState()
{
	return true;
}

bool Matrix::classname::TerminalDefaultState()
{
	return true;
}

bool Matrix::classname::Test()
{
	Core::MXSprintf(_T("classname function called\n"));
	return false;
}


//实现RTTI#DEFINATION_CLASS_INFO(classname)
VSRtti  ClassInfoObject::ms_Type(_T("ClassInfoObject"), NULL, NULL);
VSPriority ClassInfoObject::ms_Priority;


//实现初始化 #BEGINE_Implement_Initial_ClassInfo
bool ClassInfoObject::RegisterClassToMainFactory = RegisterClassInfoToEngineFactory();
bool ClassInfoObject::bRegistered = false;
ClassInfoObject* Matrix::ClassInfoObject::NewObject()
{
	return new ClassInfoObject();
}
bool Matrix::ClassInfoObject::RegisterClassInfoToEngineFactory()
{

	if (!bRegistered)
	{
		//添加Object属性初始化函数
		EngineInit::AddInitialPropertyFunction(InitialProperty);
		EngineInit::AddTerminalPropertyFunction(TerminalProperty);


		//添加object初始化状态函数#ADD_INITIAL_default_State(InitialDefaultState, TerminateDefaltState)
		EngineInit::AddInitialFunction(InitialDefaultState, &ms_Priority);
		EngineInit::AddTerminalFunction(TerminateDefaltState);
		//ADD_CLASSINFO_PRIORITY(classname)
		if (!ms_Priority.AddPriorityThan(&classname::ms_Priority))
		{
			return 0;
		}


		//#END__Implement_initial_ClassInfo
		bRegistered = true;
	}
	return bRegistered;
}




Matrix::ClassInfoObject::ClassInfoObject()
{
	//test Array
	this->mArrayInt.AddElement(2);
	this->mArrayInt.AddElement(4);
	this->mArrayInt.AddElement(5);
	this->mArrayInt.AddElement(7);
	//Test Int
	this->mInt = 999999;

	//Test Data
	this->mFloatDataNum = 4;
	this->mFloatData[0] = 1.0f;
	this->mFloatData[1] = 2.0f;
	this->mFloatData[2] = 3.0f;
	this->mFloatData[3] = 4.0f;

	//Test fixed Data
	this->mFixedFloatData[0] = 5.1f;
	this->mFixedFloatData[1] = 6.1f;
	this->mFixedFloatData[2] = 7.1f;
	this->mFixedFloatData[3] = 8.1f;

	//Test Custom Save Load
	this->mName = _T("ClassInfo");

	//Test Struct
	this->mTestStruct = TestStruct();

	//Test Object*
	this->mClassObject1 = MX_NEW  classname(111, 2222.f);

	//Test ObjectPtr
	this->mClassObject2 = MX_NEW  classname(3333, 44444.f);

	//Test Object
	this->mClassObject3 = classname(5555, 6666.f);

	//Test String
	this->mString = _T("string test in classinfo");

	//Test Enmu
	this->mEnum = ClassInfoObject::MyEnum::E3;
}

Matrix::ClassInfoObject::~ClassInfoObject()
{
}

bool Matrix::ClassInfoObject::InitialDefaultState()
{
	return false;
}
bool Matrix::ClassInfoObject::TerminateDefaltState()
{
	return false;
}

//#Begin_Register_Property
bool Matrix::ClassInfoObject::TerminalProperty()
{
	ms_Type.ClearProperty();
	return true;
}
bool Matrix::ClassInfoObject::InitialProperty(VSRtti* pRtti)
{
	ClassInfoObject* dummyPtr = NULL;
	VSProperty* activeProperty = NULL;
	VSRtti* pRttiTemp = pRtti;
	if (!pRtti)
	{
		pRtti = &ms_Type;
	}
	//需要递归添加父类的property
	__super::InitialProperty(pRtti);

	//#REGISTER_PROPERTY ...  有多种property，所以产生了多种宏定义
	{
		activeProperty = PropertyCreator::GetAutoPropertyCreator(dummyPtr->mInt).CreateProperty(
			_T("reflectName"), *pRtti, (unsigned int)((char*)&(dummyPtr->mInt) - (char*)dummyPtr), VSProperty::F_CLONE);
		pRtti->AddProperty(activeProperty);
	}

	//添加function


	//#define END_Register_Property 
	return true;
}



//bool Matrix::ClassInfoObject::Test()
//{
//	__super::Test();
//
//	return false;
//}


