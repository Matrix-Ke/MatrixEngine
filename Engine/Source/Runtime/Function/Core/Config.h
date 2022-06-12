#pragma once
#include "Object.h"

namespace Matrix
{
	struct PropertyReplaceType
	{
		Container::MArrayOrder<VSUsedName> ReplaceProperty;
	};
	struct ClassReplaceType
	{
		Container::MArrayOrder<VSUsedName> ReplaceClass;
		Container::MMapOrder<VSUsedName, PropertyReplaceType> ProperyReplaceMap;
	};
	class MATRIX_FUNCTION_API VSConfig
	{
		// PRIORITY
		DECLARE_PRIORITY
	public:
		VSConfig();
		~VSConfig();
		DECLARE_INITIAL_ONLY
		typedef Container::MMapOrder<VSUsedName, ClassReplaceType> CLASS_REPLACE_TYPE;

	private:
		static bool InitialDefaultState();
		static bool TerminalDefaultState();
		static void InitConfig();
		static void InitEnginePath();
		static void InitParamConfig();
		static void InitClassReplace();
		static void Inner_InitClassReplace();
		static CLASS_REPLACE_TYPE ms_ClassReplaceMap;
		static Container::MMapOrder<VSUsedName, VSUsedName> ms_ClassReplace;
		static Container::MMapOrder<VSUsedName, Container::MMapOrder<unsigned int, unsigned int>> ms_PropertyReplace;

	public:
		static bool ms_EnableAsynLoad;
		static bool ms_EnableAdvanceInstance;
		static Container::MString ms_OutputShaderCodePath;
		static Container::MString ms_OutputLogPath;
		static Container::MString ms_TerrainPath;
		static Container::MString ms_ResourcePath;
		static VSREAL ms_LODScreenScale;

		static bool GetPropertyReplace(Container::MString& ClassName, Container::MMapOrder<unsigned int, unsigned int>*& pPropertyReplace);
		static bool GetClassReplace(Container::MString& ClassName);
		static bool GetPropertyReplace(Container::MMapOrder<unsigned int, unsigned int>* pPropertyReplace, unsigned int& NameID);
	};
}
