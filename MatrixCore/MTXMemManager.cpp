#include "pch.h"
#include "MTXMemManager.h"

using namespace Matrix;

#if _DEBUG
#include <DbgHelp.h>
#include <DbgHelp.h>
typedef BOOL
(WINAPI
	* tFSymInitializeW)(
		_In_ HANDLE hProcess,
		_In_opt_ PCWSTR UserSearchPath,
		_In_ BOOL fInvadeProcess
		);
typedef BOOL
(WINAPI
	* tFSymGetLineFromAddr64)
	(
		IN  HANDLE                  hProcess,
		IN  DWORD64                 qwAddr,
		OUT PDWORD                  pdwDisplacement,
		OUT PIMAGEHLP_LINE64        Line64
		);

typedef DWORD
(WINAPI
	* tFSymGetOptions)
	(
		VOID
		);

typedef DWORD
(WINAPI
	* tFSymSetOptions)
	(
		IN DWORD   SymOptions
		);
static tFSymGetLineFromAddr64 fnSymGetLineFromAddr64 = NULL;
static tFSymGetOptions fnSymGetOptions = NULL;
static tFSymSetOptions fnSymSetOptions = NULL;
static tFSymInitializeW fnSymInitializeW = NULL;
static HMODULE s_DbgHelpLib = NULL;


bool Matrix::MTXDebugMem::InitDbgHelpLib()
{
	TCHAR szDbgName[MAX_PATH];
	GetModuleFileName(NULL, szDbgName, MAX_PATH);
	TCHAR* p = (TCHAR*)MTXCsrchr(szDbgName, _T('\\'));
	if (p)
		*p = 0;
	MTXStrcat(szDbgName, MAX_PATH, _T("\\dbghelp.dll"));

	// 查找当前目录的DLL
	s_DbgHelpLib = LoadLibrary(szDbgName);
	//根据代码地址调用 fnSymGetLineFromAddr64 函数就可以获得堆栈代码所在文件的行数和所在文件的名称。
	//一旦出现内存泄露，就可以准确地找到泄漏的整个调用过程。用这种方法查找内存泄露时最好用 Debug 模式
	fnSymGetLineFromAddr64 = (tFSymGetLineFromAddr64)GetProcAddress(s_DbgHelpLib, "SymGetLineFromAddr64");
	fnSymGetOptions = (tFSymGetOptions)GetProcAddress(s_DbgHelpLib, "SymGetOptions");
	fnSymSetOptions = (tFSymSetOptions)GetProcAddress(s_DbgHelpLib, "SymSetOptions");
	fnSymInitializeW = (tFSymInitializeW)GetProcAddress(s_DbgHelpLib, "SymInitializeW");
	DWORD SymOpts = fnSymGetOptions();

	SymOpts |= SYMOPT_LOAD_LINES;
	SymOpts |= SYMOPT_FAIL_CRITICAL_ERRORS;
	SymOpts |= SYMOPT_DEFERRED_LOADS;
	SymOpts |= SYMOPT_EXACT_SYMBOLS;

	// This option allows for undecorated names to be handled by the symbol engine.
	SymOpts |= SYMOPT_UNDNAME;

	// Disable by default as it can be very spammy/slow.  Turn it on if you are debugging symbol look-up!
	//		SymOpts |= SYMOPT_DEBUG;

	// Not sure these are important or desirable
	//		SymOpts |= SYMOPT_ALLOW_ABSOLUTE_SYMBOLS;
	//		SymOpts |= SYMOPT_CASE_INSENSITIVE;

	fnSymSetOptions(SymOpts);
	bool Temp = fnSymInitializeW(GetCurrentProcess(), NULL, true);
	return Temp;
}

void* Matrix::MTXDebugMem::Allocate(USIZE_TYPE uiSize, USIZE_TYPE uiAlignment, bool bIsArray)
{

	//申请的总空间
	unsigned int uiExtendedSize = sizeof(Block) + sizeof(unsigned int) + uiSize + sizeof(unsigned int);
	char* pcAddr = (char*)malloc(uiExtendedSize);
	if (!pcAddr)
		return NULL;
	//填写 Block 信息
	Block* pBlock = (Block*)pcAddr;
	pBlock->mSize = uiSize;
	pBlock->mbArray = bIsArray;

	bool bAlignment = (uiAlignment > 0) ? true : false;
	pBlock->mbAlignment = bAlignment;
	//插入节点
	InsertBlock(pBlock);
	pcAddr += sizeof(Block);
	//填写头标识
	unsigned int* pBeginMask = (unsigned int*)(pcAddr);
	*pBeginMask = BEGIN_MASK;
	pcAddr += sizeof(unsigned int);
	//填写尾标识
	unsigned int* pEndMask = (unsigned int*)(pcAddr + uiSize);
	*pEndMask = END_MASK;

	return (void*)pcAddr;
}

void MTXDebugMem::Deallocate(char* pcAddr, USIZE_TYPE uiAlignment, bool bIsArray)
{
	if (!pcAddr)
	{
		return;
	}
	//判断头标识
	pcAddr -= sizeof(unsigned int);
	unsigned int* pBeginMask = (unsigned int*)(pcAddr);
	MTXENGINE_ASSERT(*pBeginMask == BEGIN_MASK);
	pcAddr -= sizeof(Block);
	Block* pBlock = (Block*)pcAddr;

	MTXENGINE_ASSERT(pBlock->mbArray == bIsArray);
	bool bAlignment = (uiAlignment > 0) ? true : false;
	MTXENGINE_ASSERT(pBlock->mbAlignment == bAlignment);
	//判断尾标识
	unsigned int* pEndMask = (unsigned int*)(pcAddr + sizeof(Block) + sizeof(unsigned int) + pBlock->mSize);
	MTXENGINE_ASSERT(*pEndMask == END_MASK);
	//删除节点
	RemoveBlock(pBlock);
	free(pcAddr);
}

void Matrix::MTXDebugMem::InsertBlock(Block* pBlock)
{
	//插入判断尾部存在与否
	if (pTail)
	{
		pBlock->pPrev = pTail;
		pBlock->pNext = 0;
		pTail->pNext = pBlock;
		pTail = pBlock;
	}
	else
	{
		pBlock->pPrev = 0;
		pBlock->pNext = 0;
		//头尾指针一致
		pHead = pBlock;
		pTail = pBlock;
	}
}

void Matrix::MTXDebugMem::RemoveBlock(Block* pBlock)
{
	//移除时候判断头指针存在与否
	//链表指针的操作逻辑都是从pre到next先建立指向关系，然后再做删除操作。
	if (pBlock->pPrev)
	{
		pBlock->pPrev->pNext = pBlock->pNext;
	}
	else
	{
		pHead = pBlock->pNext;
	}
	if (pBlock->pNext)
	{
		pBlock->pNext->pPrev = pBlock->pPrev;
	}
	else
	{
		pTail = pBlock->pPrev;
	}

}

bool Matrix::MTXDebugMem::GetFileAndLine(const void* pAddress, TCHAR szFile[MAX_PATH], int& line)
{
	IMAGEHLP_LINE64 Line;
	Line.SizeOfStruct = sizeof(Line);
	MTXMemset(&Line, 0, sizeof(Line));
	DWORD Offset = 0;
	//通过 fnSymGetLineFromAddr64 得到 IMAGEHLP_LINE64 的 FileName，
	//进而得到函数调用所在行数和文件名，pAddress 是函数地址
	if (fnSymGetLineFromAddr64(GetCurrentProcess(), (DWORD64)pAddress, &Offset, &Line))
	{
#ifdef  _UNICODE
		MTXMbsToWcs(szFile, MAX_PATH, Line.FileName, MAX_PATH);
#else
		VSStrCopy(szFile, MAX_PATH, Line.FileName);
#endif
		line = Line.LineNumber;

		return true;
	}
	else
	{
		DWORD error = GetLastError();
		// 		if (error == 487)
		// 		{
		// 			VSOutputDebugString(_T("No debug info in current module\n"));
		// 		}
		// 		else if (error == 126)
		// 		{
		// 			VSOutputDebugString(_T("Debug info in current module has not loaded\n"));
		// 		}
		// 		else 
		// 		{
		// 			VSOutputDebugString(_T("SymGetLineFromAddr64 failed\n"));
		// 		}
		return false;
	}
}



#endif