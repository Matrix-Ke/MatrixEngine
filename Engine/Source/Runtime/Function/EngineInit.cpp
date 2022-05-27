#include "EngineInit.h"
#include "Meta/Object.h"

#include "Container/String.h"
//#include "VSGraphicInclude.h"


using namespace Matrix;

Container::MArray<EngineInit::Element>* EngineInit::ms_pInitialArray = NULL;
Container::MArray<EngineInit::Element>* EngineInit::ms_pTerminalArray = NULL;

Container::MArray<FunctionProperty>* EngineInit::ms_pInitialPropertyArray = NULL;
Container::MArray<Function>* EngineInit::ms_pTerminalPropertyArray = NULL;

unsigned int EngineInit::ms_uiInitialObject = 0;
unsigned int EngineInit::ms_uiTerminalObject = 0;

//#include "VSResourceManager.h"

void EngineInit::AddInitialPropertyFunction(FunctionProperty Func)
{
	if (!Func)
		return;
	if (!ms_pInitialPropertyArray)
	{
		ms_pInitialPropertyArray = MX_NEW Container::MArray<FunctionProperty>;
	}
	ms_pInitialPropertyArray->AddElement(Func);
}
void EngineInit::AddTerminalPropertyFunction(Function Func)
{
	if (!Func)
		return;
	if (!ms_pTerminalPropertyArray)
	{
		ms_pTerminalPropertyArray = MX_NEW Container::MArray<Function>;
	}
	ms_pTerminalPropertyArray->AddElement(Func);
}
void EngineInit::AddInitialFunction(Function Func)
{
	AddInitialFunction(Func, NULL);
}
void EngineInit::AddInitialFunction(Function Func, VSPriority* pPriority)
{
	if (!Func)
		return;
	if (!ms_pInitialArray)
	{
		ms_pInitialArray = MX_NEW Container::MArray<Element>;
	}
	Element e;
	e.Func = Func;
	e.pPriority = pPriority;
	ms_pInitialArray->AddElement(e);

}
void EngineInit::AddTerminalFunction(Function Func)
{
	AddTerminalFunction(Func, NULL);
}
void EngineInit::AddTerminalFunction(Function Func, VSPriority* pPriority)
{
	if (!Func)
		return;
	if (!ms_pTerminalArray)
	{
		ms_pTerminalArray = MX_NEW Container::MArray<Element>;
	}
	Element e;
	e.Func = Func;
	e.pPriority = pPriority;
	ms_pTerminalArray->AddElement(e);

}
bool EngineInit::Initialize()
{
	//Set Dir
	TCHAR CurDirTemp[256];
	Core::MXGetCurrentDirectory(CurDirTemp);
	Container::MString  DirString = CurDirTemp;
	Container::MString ExeExeFolderName = Core::MXGetExeFolderName();
	Container::MString Temp1 = _T("\\") + ExeExeFolderName;
	if (DirString.RemoveSubString(Temp1, -1))
	{
		Core::MXSetCurrentDirectory(DirString.GetBuffer());
	}
	else
	{
		Temp1 = _T("/") + ExeExeFolderName;
		if (DirString.RemoveSubString(Temp1, -1))
		{
			Core::MXSetCurrentDirectory(DirString.GetBuffer());
		}
	}
	//
	for (unsigned int i = 0; i < ms_pInitialPropertyArray->GetNum(); i++)
	{
		/*(*( (*ms_pInitialArray)[i].Func ))();*/

		if (!(*((*ms_pInitialPropertyArray)[i]))(NULL))
		{
			MATRIX_ENGINE_ASSERT(0);
			return 0;
		}
	}

	//类静态初始化函数，执行根据依赖的优先级。先对ms_pInitialArray进行priority排序。
	ms_pInitialArray->Sort(0, ms_pInitialArray->GetNum() - 1, PriorityCompare());
	for (unsigned int i = 0; i < ms_pInitialArray->GetNum(); i++)
	{
		/*(*( (*ms_pInitialArray)[i].Func ))();*/

		if (!(*((*ms_pInitialArray)[i].Func))())
		{
			MATRIX_ENGINE_ASSERT(0);
			return 0;
		}
	}


	ms_pInitialArray->Clear();
	ENGINE_DELETE(ms_pInitialArray);

	//为了方便快速地管理所有对象，添加一个新的类，并创建实例作为 VSObject 的静态成员
	ms_uiInitialObject = VSObject::GetObjectManager().GetObjectNum();


	ms_pInitialPropertyArray->Clear();
	ENGINE_DELETE(ms_pInitialPropertyArray);
	return 1;
}
bool EngineInit::Terminate()
{

	ms_pTerminalArray->Sort(0, ms_pTerminalArray->GetNum(), PriorityCompare());

	ms_uiTerminalObject = VSObject::GetObjectManager().GetObjectNum();

	for (int i = ms_pTerminalArray->GetNum() - 1; i >= 0; i--)
	{
		/*Function fun = NULL;
		fun = (*ms_pTerminalArray)[i].Func;
		(*fun)();
		//(*( (*ms_pTerminalArray)[i].Func ))();*/
		if (!(*((*ms_pTerminalArray)[i].Func))())
		{
			MATRIX_ENGINE_ASSERT(0);
			return 0;
		}

	}
	ms_pTerminalArray->Clear();
	ENGINE_DELETE(ms_pTerminalArray);

	for (unsigned int i = 0; i < ms_pTerminalPropertyArray->GetNum(); i++)
	{

		if (!(*((*ms_pTerminalPropertyArray)[i]))())
		{
			MATRIX_ENGINE_ASSERT(0);
			return 0;
		}
	}
	ms_pTerminalPropertyArray->Clear();
	ENGINE_DELETE(ms_pTerminalPropertyArray);

	//todo list engine GC
	//VSResourceManager::GCObject();
	//VSResourceManager::RunAllGCTask();
	//MATRIX_ENGINE_ASSERT(VSResourceManager::IsReleaseAll());


	VSFastObjectManager& Temp = VSObject::GetObjectManager();
	ms_uiTerminalObject = VSObject::GetObjectManager().GetObjectNum();
	MATRIX_ENGINE_ASSERT(ms_uiTerminalObject == 0);
	return 1;

}