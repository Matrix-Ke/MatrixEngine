#include "Function/EngineInit.h"
#include "Function/Meta/Rtti.h"
#include "Function/Meta/Pointer.h"
#include "Function/Meta/Property.h"

using namespace Matrix;

typedef bool (*Function)();
Function function_name;

class classname
{

	/********************************************************************************/
//#define DECLARE_RTTI 
public:
	virtual VSRtti& GetType()const { return ms_Type; }
	static VSRtti ms_Type;
public:
	static  VSPriority ms_Priority;

	/********************************************************************************/
//#define DECLARE_INITIAL_NO_CLASS_FACTORY   
public:
	static bool RegisterMainFactory();

public:
	static bool ms_bRegisterMainFactory;
	static bool InitialProperty(VSRtti*);
	static bool TerminalProperty();


	//附加项
	int* varName;
};
//#define DECLARE_Ptr(ClassName) 
class ClassName;
typedef VSPointer<ClassName>  ClassNamePtr;

/********************************************************************************/
//#define IMPLEMENT_RTTI_NoParent_NoCreateFun(classname)
VSRtti classname::ms_Type(_T("classname"), NULL, NULL);
VSPriority classname::ms_Priority;

/********************************************************************************/
//#define IMPLEMENT_INITIAL_NO_CLASS_FACTORY_BEGIN(classname)                          
static bool gs_bStreamRegistered_classname = classname::RegisterMainFactory();
bool classname::ms_bRegisterMainFactory = false;
bool classname::RegisterMainFactory()
{
	if (!ms_bRegisterMainFactory)
	{
		/********************************************************************************/
//#define IMPLEMENT_INITIAL_NO_CLASS_FACTORY_END             
		EngineInit::AddInitialPropertyFunction(InitialProperty);
		EngineInit::AddTerminalPropertyFunction(TerminalProperty);
		ms_bRegisterMainFactory = true;
	}
	return ms_bRegisterMainFactory;
}

/********************************************************************************/
//#define BEGIN_ADD_PROPERTY_ROOT(classname)    
bool classname::TerminalProperty()
{
	ms_Type.ClearProperty();
	return true;
}
bool classname::InitialProperty(VSRtti* pRtti)
{
	classname* dummyPtr = NULL;
	VSProperty* activeProperty = NULL;
	if (!pRtti)
	{
		pRtti = &ms_Type;
	}

	/********************************************************************************/
//#define REGISTER_PROPERTY(varName,reflectName,flag)  //REGISTER_PROPERTY(m_uiFlag, Flag, VSProperty::F_CLONE);
	{
		activeProperty = PropertyCreator::GetAutoPropertyCreator(dummyPtr->varName).CreateProperty(
			_T("reflectName"), *pRtti, (unsigned int)((char*)&(dummyPtr->varName) - (char*)dummyPtr), VSProperty::F_CLONE);
		pRtti->AddProperty(activeProperty);
	}

	/********************************************************************************/
//#define END_ADD_PROPERTY 
	return true;
}

/*********************************  Profiler相关宏定义  ***********************************************/
//#define DECLEAR_NOCLEAR_COUNT_PROFILENODE(Name, ParentName) VSNoClearCountProfilerNode CountProfilerNode_##Name(_T(#Name), _T(#ParentName));



//通过模板特化来进行类型推导， 
//#define DEFINE_TYPE(TypeName)              
template <typename T>
struct TIsTypeNameType
{
	enum
	{
		Value = false
	};
};
template <typename T>
struct TIsTypeNamePointerType
{
	enum
	{
		Value = false
	};
};
template <typename T>
struct TIsTypeNameSmartPointerType
{
	enum
	{
		Value = false
	};
};


//			DEFINE_TYPE(VS)     //vs type
//#define VSTYPE_MARCO(ClassName) \
			     //DEFINE_TYPE_INSTANCE(VS, ClassName)
			//#define DEFINE_TYPE_INSTANCE(TypeName, ClassName)                      
class ClassName;
template <>
struct TIsTypeNameType<ClassName>
{
	enum
	{
		Value = true
	};
};
template <>
struct TIsTypeNamePointerType<ClassName*>
{
	enum
	{
		Value = true
	};
};
template <>
struct TIsTypeNamePointerType<const ClassName*>
{
	enum
	{
		Value = true
	};
};
template <>
struct TIsTypeNameSmartPointerType<VSPointer<ClassName>>
{
	enum
	{
		Value = true
	};
};
template <>
struct TIsTypeNameSmartPointerType<const VSPointer<ClassName>>
{
	enum
	{
		Value = true
	};
};