#include "Config.h"
#include "Rtti.h"
#include "Container/Match.h"
#include "./../EngineInit.h"

using namespace Matrix;
Container::MString VSConfig::ms_OutputShaderCodePath;
Container::MString VSConfig::ms_OutputLogPath;
Container::MString VSConfig::ms_TerrainPath;
Container::MString VSConfig::ms_ResourcePath;
bool VSConfig::ms_EnableAsynLoad = true;
bool VSConfig::ms_EnableAdvanceInstance = false;
VSREAL VSConfig::ms_LODScreenScale = 1.0f;
Container::MMapOrder<VSUsedName, VSUsedName> VSConfig::ms_ClassReplace;
Container::MMapOrder<VSUsedName, Container::MMapOrder<unsigned int, unsigned int>> VSConfig::ms_PropertyReplace;
VSConfig::CLASS_REPLACE_TYPE VSConfig::ms_ClassReplaceMap;
IMPLEMENT_PRIORITY(VSConfig)
IMPLEMENT_INITIAL_ONLY_BEGIN(VSConfig);
ADD_PRIORITY(VSRtti);
ADD_INITIAL_FUNCTION_WITH_PRIORITY(InitialDefaultState)
ADD_TERMINAL_FUNCTION(TerminalDefaultState)
IMPLEMENT_INITIAL_ONLY_END
bool VSConfig::TerminalDefaultState()
{
	return true;
}
bool VSConfig::InitialDefaultState()
{
	InitConfig();
	return true;
}
VSConfig::VSConfig()
{
}
VSConfig::~VSConfig()
{
}
void VSConfig::InitEnginePath()
{
	Container::MMatch Match;
	if (!Match.Open(_T("Resource\\EnginePath.txt")))
	{
		ENGINE_ASSERT(0);
		return;
	}

	// output
	if (!Match.Getline())
	{
		ENGINE_ASSERT(0);
		return;
	}

	if (Match.PatternMatch(_T("['OutputShaderCodePath'][s>0]")))
	{
		ms_OutputShaderCodePath = Match.pstrings[0];
	}

	if (!Match.Getline())
	{
		ENGINE_ASSERT(0);
		return;
	}

	if (Match.PatternMatch(_T("['OutputLogPath'][s>0]")))
	{
		ms_OutputLogPath = Match.pstrings[0];
	}

	// Terrain
	if (!Match.Getline())
	{
		ENGINE_ASSERT(0);
		return;
	}

	if (Match.PatternMatch(_T("['TerrainPath'][s>0]")))
	{
		ms_TerrainPath = Match.pstrings[0];
	}

	if (!Match.Getline())
	{
		ENGINE_ASSERT(0);
		return;
	}

	if (Match.PatternMatch(_T("['ResourcePath'][s>0]")))
	{
		ms_ResourcePath = Match.pstrings[0];
	}
}
void VSConfig::InitParamConfig()
{
	Container::MMatch Match;
	if (!Match.Open(_T("Resource\\Config.txt")))
		return;
	if (!Match.Getline())
	{
		ENGINE_ASSERT(0);
		return;
	}
	if (Match.PatternMatch(_T("['EnableAsynLoad'][s>0]")))
	{
		Container::MString TrueString = _T("true");
		ms_EnableAsynLoad = (Match.pstrings[0] == TrueString);
	}

	if (!Match.Getline())
	{
		ENGINE_ASSERT(0);
		return;
	}
	if (Match.PatternMatch(_T("['EnableAdvanceInstance'][s>0]")))
	{
		Container::MString TrueString = _T("true");
		ms_EnableAdvanceInstance = (Match.pstrings[0] == TrueString);
	}

	if (!Match.Getline())
	{
		ENGINE_ASSERT(0);
		return;
	}
	if (Match.PatternMatch(_T("['LODScreenScale'][f]")))
	{
		ms_LODScreenScale = Match.pfloats[0];
	}
}
void VSConfig::InitConfig()
{
	InitEnginePath();
	InitParamConfig();
	InitClassReplace();
}
void VSConfig::InitClassReplace()
{
	Container::MMatch Match;
	if (!Match.Open(_T("Resource\\ClassReplace.txt")))
		return;
	if (!Match.Getline())
	{
		return;
	} // end if
	while (Match.PatternMatch(_T("[s>1]")))
	{
		unsigned int ClassIndex = ms_ClassReplaceMap.AddElement(Match.pstrings[0], ClassReplaceType());
		if (!Match.Getline())
		{
			ENGINE_ASSERT(0);
		}
		if (Match.PatternMatch(_T("['{']")))
		{
			if (!Match.Getline())
			{
				ENGINE_ASSERT(0);
			}
			while (Match.PatternMatch(_T("[s>1]")))
			{
				ms_ClassReplaceMap[ClassIndex].Value.ReplaceClass.AddElement(Match.pstrings[0]);
				if (!Match.Getline())
				{
					ENGINE_ASSERT(0);
				}
			}
			if (Match.PatternMatch(_T("['[']")))
			{
				if (!Match.Getline())
				{
					ENGINE_ASSERT(0);
				} // end if
				while (Match.PatternMatch(_T("[s>1]")))
				{
					unsigned int PropertyIndex = ms_ClassReplaceMap[ClassIndex].Value.ProperyReplaceMap.AddElement(Match.pstrings[0], PropertyReplaceType());
					if (!Match.Getline())
					{
						ENGINE_ASSERT(0);
					}
					if (Match.PatternMatch(_T("['{']")))
					{
						if (!Match.Getline())
						{
							return;
						}
						while (Match.PatternMatch(_T("[s>1]")))
						{
							ms_ClassReplaceMap[ClassIndex].Value.ProperyReplaceMap[PropertyIndex].Value.ReplaceProperty.AddElement(Match.pstrings[0]);
							if (!Match.Getline())
							{
								return;
							}
						}
						if (!Match.PatternMatch(_T("['}']")))
						{
							ENGINE_ASSERT(0);
							return;
						}
						if (!Match.Getline())
						{
							ENGINE_ASSERT(0);
							return;
						}
					}
				}
				if (!Match.PatternMatch(_T("[']']")))
				{
					ENGINE_ASSERT(0);
				}
				if (!Match.Getline())
				{
					ENGINE_ASSERT(0);
				}
			}
			if (!Match.PatternMatch(_T("['}']")))
			{
				ENGINE_ASSERT(0);
			}
			Match.Getline();
		}
	}
	Inner_InitClassReplace();
}
void VSConfig::Inner_InitClassReplace()
{
	for (unsigned int i = 0; i < ms_ClassReplaceMap.GetNum(); i++)
	{
		VSUsedName ClassName = ms_ClassReplaceMap[i].Key;
		for (unsigned int j = 0; j < ms_ClassReplaceMap[i].Value.ReplaceClass.GetNum(); j++)
		{
			ms_ClassReplace.AddElement(ms_ClassReplaceMap[i].Value.ReplaceClass[j], ClassName);
		}
		if (ms_ClassReplaceMap[i].Value.ProperyReplaceMap.GetNum() > 0)
		{
			Container::MMapOrder<unsigned int, unsigned int> Temp;
			unsigned int ClassIndex = ms_PropertyReplace.AddElement(ClassName, Temp);
			for (unsigned int m = 0; m < ms_ClassReplaceMap[i].Value.ProperyReplaceMap.GetNum(); m++)
			{
				unsigned int PropertyID = ms_ClassReplaceMap[i].Value.ProperyReplaceMap[m].Key.GetNameCode();
				for (unsigned int n = 0; n < ms_ClassReplaceMap[i].Value.ProperyReplaceMap[m].Value.ReplaceProperty.GetNum(); n++)
				{
					ms_PropertyReplace[ClassIndex].Value.AddElement(ms_ClassReplaceMap[i].Value.ProperyReplaceMap[m].Value.ReplaceProperty[n].GetNameCode(), PropertyID);
				}
			}
		}
	}
	for (unsigned int i = 0; i < ms_PropertyReplace.GetNum(); i++)
	{
		const VSRtti* pRtti = VSRtti::GetRttiByName(ms_PropertyReplace[i].Key);
		const VSRtti* pBaseRtti = pRtti->GetBase();
		while (pBaseRtti)
		{
			unsigned int j = ms_PropertyReplace.Find(pBaseRtti->GetName());
			if (j != ms_PropertyReplace.GetNum() && ms_PropertyReplace[j].Value.GetNum())
			{
				ms_PropertyReplace[i].Value.AddElement(ms_PropertyReplace[j].Value, 0, ms_PropertyReplace[j].Value.GetNum() - 1);
			}
			pBaseRtti = pBaseRtti->GetBase();
		}
	}
}
bool VSConfig::GetPropertyReplace(Container::MString& ClassName, Container::MMapOrder<unsigned int, unsigned int>*& pPropertyReplace)
{
	VSUsedName Temp = ClassName;
	unsigned int i = ms_PropertyReplace.Find(Temp);
	if (i == ms_PropertyReplace.GetNum())
	{
		return false;
	}
	else
	{
		pPropertyReplace = &ms_PropertyReplace[i].Value;
		return true;
	}
}
bool VSConfig::GetClassReplace(Container::MString& ClassName)
{
	VSUsedName Temp = ClassName;
	unsigned int i = ms_ClassReplace.Find(Temp);
	if (i != ms_ClassReplace.GetNum())
	{
		ClassName = ms_ClassReplace[i].Value.GetString();
		return true;
	}
	return false;
}
bool VSConfig::GetPropertyReplace(Container::MMapOrder<unsigned int, unsigned int>* pPropertyReplace, unsigned int& NameID)
{
	unsigned int i = pPropertyReplace->Find(NameID);
	if (i != pPropertyReplace->GetNum())
	{
		NameID = (*pPropertyReplace)[i].Value;
		return true;
	}
	else
	{
		return false;
	}
}
