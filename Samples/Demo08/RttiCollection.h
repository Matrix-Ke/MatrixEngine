#include "Function/EngineInit.h"
//#include "Function/Meta/Priority.h"

using namespace Matrix;

typedef bool (*Function)();
Function InitialDefaultState;
Function TerminalDefaultState;

class classname
{

	//#define DECLARE_PRIORITY
public:
	static VSPriority ms_Priority;

	/********************************************************************************/
	//#define DECLARE_INITIAL_ONLY
public:
	static bool RegisterMainFactory();

public:
	static bool ms_bRegisterMainFactory;
};

/********************************************************************************/
//����priority
//#define IMPLEMENT_PRIORITY(classname)
VSPriority classname::ms_Priority;

/********************************************************************************/
//#define IMPLEMENT_INITIAL_ONLY_BEGIN(classname)
static bool gs_bStreamRegistered_classname = classname::RegisterMainFactory();
bool classname::ms_bRegisterMainFactory = false;
bool classname::RegisterMainFactory()
{
	if (!ms_bRegisterMainFactory)
	{
		/********************************************************************************/
		//#define ADD_INITIAL_FUNCTION_WITH_PRIORITY(function_name)  //ADD_INITIAL_FUNCTION_WITH_PRIORITY(InitialDefaultState)
		EngineInit::AddInitialFunction(InitialDefaultState, &ms_Priority);
		/********************************************************************************/
		//#define ADD_TERMINAL_FUNCTION(function_name)
		EngineInit::AddTerminalFunction(TerminalDefaultState);

		/********************************************************************************/
		//#define IMPLEMENT_INITIAL_ONLY_END
		ms_bRegisterMainFactory = true;
	}
	return ms_bRegisterMainFactory;
};
