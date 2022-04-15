#include "pch.h"
#include "MTXMemManager.h"

using namespace Matrix;


Matrix::MTXMemManager::MTXMemManager()
{
}

Matrix::MTXMemManager::~MTXMemManager()
{
}

MTXCriticalSection  MTXMemManager::msMemLock;

Matrix::MTXCMem::MTXCMem()
{
}

Matrix::MTXCMem::~MTXCMem()
{
}

void* Matrix::MTXCMem::Allocate(USIZE_TYPE uiSize, USIZE_TYPE uiAlignment, bool bIsArray)
{
	MTXCriticalSection::Locker Temp(msMemLock);
	if (uiAlignment == 0)
	{
		return malloc(uiSize);

	}
	else
	{
		//变分配器默认行为（默认是提供32-byte或者64-byte对齐）
		return _aligned_malloc(uiSize, uiAlignment);
	}
	return NULL;
}

void Matrix::MTXCMem::Deallocate(char* pcAddr, USIZE_TYPE uiAlignment, bool bIsArray)
{
	MTXCriticalSection::Locker Temp(msMemLock);
	if (uiAlignment == 0)
	{
		free(pcAddr);
	}
	else
	{
		_aligned_free(pcAddr);
	}
}

#if !_DEBUG && !_WIN64
Matrix::MTXMemWin32::MTXMemWin32()
{
	//PageSize = 0;
	SYSTEM_INFO  SI;
	//得到 32 位 Windows 系统页面大小，《Windows 核心编程》里面提到，这个一般由 CPU 来决定，
	//但 Intel 和 AMD 的大部分 CPU 是 4KB 
	GetSystemInfo(&SI);
	PageSize = SI.dwPageSize;
	//pagesize首位为1其他位需要为0；
	MTXENGINE_ASSERT(!(PageSize & (PageSize - 1)));

	//初始化Pool table
	OsTable.FirstPool = NULL;
	OsTable.ExhaustedPool = NULL;
	OsTable.BlockSize = 0;

	PoolTable[0].FirstPool = NULL;
	PoolTable[0].ExhaustedPool = NULL;
	PoolTable[0].BlockSize = 8;

	//blocksize 逐步增长 
	for (DWORD i = 1; i < 5; i++)
	{
		PoolTable[i].FirstPool = NULL;
		PoolTable[i].ExhaustedPool = NULL;
		PoolTable[i].BlockSize = (8 << ((i + 1) >> 2)) + (2 << i);
	}
	for (DWORD i = 5; i < POOL_CATEGORY; i++)
	{
		PoolTable[i].FirstPool = NULL;
		PoolTable[i].ExhaustedPool = NULL;
		PoolTable[i].BlockSize = (4 + ((i + 7) & 3)) << (1 + ((i + 7) >> 2));
	}

	//建立从 0～32768字节映射到 PoolTable 的表
	//为了快速查找到要分配的内存位于哪个 PoolTable 中，UnrealEngine 建立了一个索引用来快速查找。42 个 PoolTable 的
	//TableSize 基本上包含了 1～32 768 字节内存空间的管理，其中PoolTable0 管理 1～8 字节，PoolTable1 管理 9～12 字节，以此
	//类推，PoolTable41 管理（28672 + 1）～32 768 字节。这样索引就可以很容易建立出来
	for (DWORD i = 0; i < POOL_MAX; i++)
	{
		DWORD Index;
		for (Index = 0; PoolTable[Index].BlockSize < i; Index++);
		MTXENGINE_ASSERT(Index < POOL_CATEGORY);
		//每一个pooltable内的blocksize都必须要大于i （i就是申请内存的大小, 即申请内存的大小不能超过table的blocksize） 
		MemSizeToPoolTable[i] = &PoolTable[Index];
	}
	for (DWORD i = 0; i < 32; i++)
	{
		//清空 32 个一级索引
		PoolIndirect[i] = NULL;
	}
	//判断是否数据对应的上
	MTXENGINE_ASSERT(POOL_MAX - 1 == PoolTable[POOL_CATEGORY - 1].BlockSize);
}

Matrix::MTXMemWin32::~MTXMemWin32()
{
}



void* Matrix::MTXMemWin32::Allocate(USIZE_TYPE uiSize, USIZE_TYPE uiAlignment, bool bIsArray)
{
	//内存锁，防止两个线程同时申请内存
	MTXCriticalSection::Locker   Temp(msMemLock);
	FFreeMem* Free;
	//大于pool_MAX大内存采用操作系统的内存分配
	if (uiSize < POOL_MAX)
	{
		// 根据申请内存的大小找到相关的内存table
		FPoolTable* Table = MemSizeToPoolTable[uiSize];
		MTXENGINE_ASSERT(uiSize < Table->BlockSize);
		FPoolInfo* Pool = Table->FirstPool;
		if (!Pool)
		{
			//创建 PoolInfo创建内存池,，每个 PoolInfo 管理 64KB = 65532  内存,
			//根据当前 PoolTable 管理每个单元大小，计算出总块数
			DWORD Blocks = 65536 / Table->BlockSize;
			DWORD Bytes = Blocks * Table->BlockSize;
			MTXENGINE_ASSERT(Blocks >= 1);
			MTXENGINE_ASSERT(Blocks * Table->BlockSize <= Bytes);

			//分配内存，一共从  Windows 系统申请 3 类内存， 这个是第一类，申请 PoolInfo，即使 Bytes 小于 64KB，
			//按照page单位（64KB）分配, 分配类型: MEM_COMMIT 为指定地址空间提交物理内存。这个函数初始化内在为零
			//试图提交已提交的内存页不会导致函数失败。这意味着您可以在不确定当前页的当前提交状态的情况下提交一系列页面。
			//如果尚未保留内存页，则设置此值会导致函数同时保留并提交内存页。
			Free = (FFreeMem*)VirtualAlloc(NULL, Bytes, MEM_COMMIT, PAGE_READWRITE); //分配一块block
			if (!Free)
			{
				return NULL;
			}

			//通过一级索引查找二级索引, 左移27保留高5位
			FPoolInfo*& Indirect = PoolIndirect[((DWORD)Free >> 27)];
			if (!Indirect)
			{
				//将分配好的内存引用到PoolIndirect中
				Indirect = CreateIndirect();
			}
			//根据二级索引找到对应的 PoolInfo 
			Pool = &Indirect[((DWORD)Free >> 16) & 2047];

			//连接到对应 PoolTable 
			Pool->Link(Table->FirstPool);
			Pool->Mem = (BYTE*)Free;
			Pool->Bytes = Bytes;
			Pool->OsBytes = Align(Bytes, PageSize);
			Pool->Owner = Table;
			Pool->Taken = 0;
			Pool->FirstMem = Free;

			//Create first free item
			Free->Blocks = Blocks;
			Free->Next = NULL;
		}

		// Pick first available block and unlink it.
		Pool->Taken++;
		MTXENGINE_ASSERT(Pool->FirstMem);
		MTXENGINE_ASSERT(Pool->FirstMem->Blocks > 0);
		Free = (FFreeMem*)((BYTE*)Pool->FirstMem + --Pool->FirstMem->Blocks * Table->BlockSize);
		if (Pool->FirstMem->Blocks == 0)
		{
			//FreeMem blocks之间的链接
			Pool->FirstMem = Pool->FirstMem->Next;
			if (!Pool->FirstMem)
			{
				// poolinfo所指向的block满了就将其移入ExhaustedPool
				Pool->Unlink();
				Pool->Link(Table->ExhaustedPool);
			}
		}

	}
	else
	{
		//大的内存采用操作系统自身的
		INT AlignedSize = Align(uiSize, PageSize);
		Free = (FFreeMem*)VirtualAlloc(NULL, AlignedSize, MEM_COMMIT, PAGE_READWRITE);
		if (!Free)
		{
			return NULL;
		}
		FPoolInfo*& Indirect = PoolIndirect[(DWORD)Free >> 27];
		if (!Indirect)
		{
			Indirect = CreateIndirect();
		}
		//init pool
		FPoolInfo* Pool = &Indirect[((DWORD)Free >> 16) & 2047];
		Pool->Mem = (BYTE*)Free;
		Pool->Bytes = uiSize;
		Pool->OsBytes = AlignedSize;
		Pool->Owner = &OsTable;
	}
	return Free;
}

void Matrix::MTXMemWin32::Deallocate(char* pcAddr, USIZE_TYPE uiAlignment, bool bIsArray)
{
	MTXCriticalSection::Locker  Temp(msMemLock);
	MTXENGINE_ASSERT(pcAddr);
	if (!pcAddr)
	{
		return;
	}
	//通过二维数组找到对应的PoolInfo
	FPoolInfo* Pool = &PoolIndirect[(DWORD)pcAddr >> 27][((DWORD)pcAddr >> 16) & 2047];
	MTXENGINE_ASSERT(Pool->Bytes != 0);
	if (Pool->Owner != &OsTable)
	{
		if (!Pool->FirstMem)
		{
			//FirstMem为null， 此pool已经满了，切换到可用的pool列表
			Pool->Unlink();
			Pool->Link(Pool->Owner->FirstPool);
		}

		// Free a pooled allocation.
		FFreeMem* Free = (FFreeMem*)pcAddr;
		Free->Blocks = 1;
		Free->Next = Pool->FirstMem;

		Pool->FirstMem = Free;
		MTXENGINE_ASSERT(Pool->Taken >= 1);
		if (--Pool->Taken == 0)
		{
			// Free the OS memory.
			Pool->Unlink();
			VirtualFree(Pool->Mem, 0, MEM_RELEASE);
			Pool->Mem = NULL;
		}
	}
	else
	{
		// Free an OS allocation.
		VirtualFree(pcAddr, 0, MEM_RELEASE);
		Pool->Mem = NULL;
	}
}

MTXMemWin32::FPoolInfo* Matrix::MTXMemWin32::CreateIndirect()
{
	//二级索引为空，则创建二级索引，2048 个 PoolInfo 正好是 64KB 
	//这是第二类，分配的内存正好是 32 位 Windows 系统的一个分配粒度
	FPoolInfo* Indirect = (FPoolInfo*)VirtualAlloc(NULL, 2048 * sizeof(FPoolInfo), MEM_COMMIT, PAGE_READWRITE);
	if (!Indirect)
	{
		return NULL;
	}
	return Indirect;
}

#elif _DEBUG
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


Matrix::MTXDebugMem::MTXDebugMem()
{
	mNumNewCalls = 0;
	mNumDeleteCalls = 0;

	mNumBlocks = 0;
	mNumBytes = 0;
	mMaxNumBytes = 0;
	mMaxNumBlocks = 0;

	pHead = NULL;
	pTail = NULL;

	for (unsigned int i = 0; i < RECORD_NUM; i++)
	{
		mSizeRecord[i] = 0;
	}
}

Matrix::MTXDebugMem::~MTXDebugMem()
{
	//动态加载dbghelp.dll
	InitDbgHelpLib();
	PrintInfo();
	FreeDbgHelpLib();

	FreeLeakMem();
}

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
	MTXENGINE_ASSERT(s_DbgHelpLib);
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

void Matrix::MTXDebugMem::FreeLeakMem()
{
	Block* pBlock = pHead;
	while (pBlock)
	{
		Block* Temp = pBlock;
		pBlock = pBlock->pNext;
		//free((void*)Temp);
		//todo : 此处应该使用MTXCMem::Deallocate()函数是否更好。 使用free不是很合适
		MMemObject::GetCMemManager().Deallocate((char*)pBlock, pBlock->mbAlignment, pBlock->mbArray);
	}
}

void Matrix::MTXDebugMem::PrintInfo()
{
	MTXOutputDebugString(_T("#########################  begin print leak mem  ######################\n"));
	MTXOutputDebugString(_T("Max Byte Num: %d\n"), mMaxNumBytes);
	MTXOutputDebugString(_T("Max Block Num: %d\n"), mMaxNumBlocks);
	MTXOutputDebugString(_T("Total Size: %d\n"), mNumBytes);
	MTXOutputDebugString(_T("Block Num: %d\n"), mNumBlocks);
	MTXOutputDebugString(_T("New Call: %d\n"), mNumNewCalls);
	MTXOutputDebugString(_T("Delete Call: %d\n"), mNumDeleteCalls);

	if (pHead)
	{
		MTXOutputDebugString(_T("Memory Leak:\n"));
	}
	else
	{
		MTXOutputDebugString(_T("No Memory Leak\n"));
	}
	Block* pBlock = pHead;
	static unsigned int uiLeakNum = 0;
	while (pBlock)
	{

		uiLeakNum++;
		MTXOutputDebugString(_T("$$$$$$$$$$$$$$$$  Leak %d  $$$$$$$$$$$$$$$$$\n"), uiLeakNum);
		MTXOutputDebugString(_T("Size: %d\n"), pBlock->mSize);
		MTXOutputDebugString(_T("Is Array:%d\n"), pBlock->mbArray);
#if WINDOWS_PLATFORM
		TCHAR szFile[MAX_PATH];
		int	  line;
		for (unsigned int i = 0; i < pBlock->mStackInfoNum; i++)
		{

			if (!GetFileAndLine(pBlock->pStackAddr[i], szFile, line))
			{
				break;
			}
			MTXOutputDebugString(_T("%s(%d)\n"), szFile, line);

		}
#endif
		MTXOutputDebugString(_T("$$$$$$$$$$$$$$$$$ Leak %d  $$$$$$$$$$$$$$$$$$$\n"), uiLeakNum);
		pBlock = pBlock->pNext;
	}
	MTXOutputDebugString(_T("leak block total num : %d\n"), uiLeakNum);

	MTXOutputDebugString(_T("#########################  end print leak mem  ######################\n"));
}

void Matrix::MTXDebugMem::FreeDbgHelpLib()
{
	if (s_DbgHelpLib != NULL)
	{
		FreeLibrary(s_DbgHelpLib);
		s_DbgHelpLib = NULL;
	}

	fnSymGetLineFromAddr64 = NULL;
	fnSymGetOptions = NULL;
	fnSymSetOptions = NULL;
	fnSymInitializeW = NULL;

}

void* Matrix::MTXDebugMem::Allocate(USIZE_TYPE uiSize, USIZE_TYPE uiAlignment, bool bIsArray)
{
	MTXCriticalSection::Locker   Temp(msMemLock);
	MTXENGINE_ASSERT(uiSize);
	mNumNewCalls++;

	//申请的总空间
	USIZE_TYPE extendedSize = sizeof(Block) + sizeof(unsigned int) + uiSize + sizeof(unsigned int);
	char* pcAddr = (char*)MMemObject::GetCMemManager().Allocate(extendedSize, uiAlignment, bIsArray);
	MTXENGINE_ASSERT(pcAddr);
	//填写 Block 信息
	Block* pBlock = (Block*)pcAddr;
	pBlock->mSize = uiSize;
	pBlock->mbArray = bIsArray;

	bool bAlignment = (uiAlignment > 0) ? true : false;
	pBlock->mbAlignment = bAlignment;
	pBlock->mStackInfoNum = 0;

	//获取当前函数的调用栈函数
#if WINDOWS_PLATFORM	
	PVOID WinBackTrace[CALLSTACK_NUM];
	short NumFrames = RtlCaptureStackBackTrace(0, CALLSTACK_NUM, WinBackTrace, NULL);

#if _WIN64
	NumFrames -= 6;
#else
	NumFrames -= 7;
#endif
	for (short i = 1; i < NumFrames; i++)
	{
		pBlock->pStackAddr[i - 1] = WinBackTrace[i];
		pBlock->mStackInfoNum++;
	}
#endif

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

	//todo list
	mNumBlocks++;
	mNumBytes += (unsigned int)uiSize;
	if (mNumBytes > mMaxNumBytes)
	{
		mMaxNumBytes = mNumBytes;
	}
	if (mNumBlocks > mMaxNumBlocks)
	{
		mMaxNumBlocks = mMaxNumBlocks;
	}

	//uiSize 是这次申请的字节数，上面这段代码会根据 uiSize 落到 2n的哪个范围内来做统计。
	//如果申请 15 字节，i 等于 4 的时候，uiTwoPowerI 等于 16，15 小于 16，它落在 23和 24之间，
	//这样就可以统计出以 2 为基数不同大小内存的分配情况
	unsigned int uiTwoPowerI = 1;
	int i;
	for (i = 0; i <= RECORD_NUM - 2; i++, uiTwoPowerI <<= 1)
	{
		if (uiSize <= uiTwoPowerI)
		{
			mSizeRecord[i]++;
			break;
		}
	}
	if (i == RECORD_NUM - 1)
	{
		mSizeRecord[i]++;
	}

	return (void*)pcAddr;
}

void MTXDebugMem::Deallocate(char* pcAddr, USIZE_TYPE uiAlignment, bool bIsArray)
{
	MTXCriticalSection::Locker  Temp(msMemLock);
	//调用 delete 的次数统计
	mNumDeleteCalls++;
	MTXENGINE_ASSERT(pcAddr);

	//判断头标识
	pcAddr -= sizeof(unsigned int);
	unsigned int* pBeginMask = (unsigned int*)(pcAddr);
	MTXENGINE_ASSERT(*pBeginMask == BEGIN_MASK);
	pcAddr -= sizeof(Block);
	Block* pBlock = (Block*)pcAddr;

	MTXENGINE_ASSERT(pBlock->mbArray == bIsArray);
	MTXENGINE_ASSERT(mNumBlocks > 0 && mNumBytes >= pBlock->mSize);
	bool bAlignment = (uiAlignment > 0) ? true : false;
	MTXENGINE_ASSERT(pBlock->mbAlignment == bAlignment);
	//判断尾标识
	unsigned int* pEndMask = (unsigned int*)(pcAddr + sizeof(Block) + sizeof(unsigned int) + pBlock->mSize);
	MTXENGINE_ASSERT(*pEndMask == END_MASK);

	//更新统计数据
	mNumBlocks--;
	mNumBytes -= (unsigned int)pBlock->mSize;

	//删除节点
	RemoveBlock(pBlock);
	//free(pcAddr);
	MMemObject::GetCMemManager().Deallocate(pcAddr, uiAlignment, bIsArray);
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
		return false;
	}
}

#else
#endif

Matrix::MMemObject::MMemObject()
{

}

Matrix::MMemObject::~MMemObject()
{
}

MTXMemManager& Matrix::MMemObject::GetMemManager()
{
#if !_DEBUG  && !_WIN64
	static MTXMemWin32  g_MemManager;
#elif _DEBUG
	static MTXDebugMem  g_MemManager;
#else
	static MTXMemWin64  g_MemManager;
#endif // !_DEBUG  && !_WIN64
	return g_MemManager;
}

MTXMemManager& Matrix::MMemObject::GetCMemManager()
{
	static  MTXCMem  g_MemManager;
	return g_MemManager;
}