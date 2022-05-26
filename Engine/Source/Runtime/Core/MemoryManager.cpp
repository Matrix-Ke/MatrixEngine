#include "MemoryManager.h"

using namespace Matrix::Core;

MXCriticalSection BaseMemoryManager::msMemLock = MXCriticalSection();

Matrix::Core::BaseMemoryManager::BaseMemoryManager()
{
}
Matrix::Core::BaseMemoryManager::~BaseMemoryManager()
{
}

void Matrix::Core::BaseMemoryManager::printInfo()
{
    printf_s("base MemoryManager has been called\n");
}

Matrix::Core::CMemoryManager::CMemoryManager()
{
}
Matrix::Core::CMemoryManager::~CMemoryManager()
{
}
void *Matrix::Core::CMemoryManager::Allocate(USIZE_TYPE uSize, USIZE_TYPE uiAlignment, bool bIsArray)
{
    MXCriticalSection::Locker Temp(msMemLock);
    if (uiAlignment == 0)
    {
        return malloc(uSize);
    }
    else
    {
        //�������Ĭ����Ϊ��Ĭ�����ṩ32-byte����64-byte���룩
        return _aligned_malloc(uSize, uiAlignment);
    }
    return NULL;
}
void Matrix::Core::CMemoryManager::Deallocate(char *pcAddr, USIZE_TYPE uiAlignment, bool bIsArray)
{
    MXCriticalSection::Locker Temp(msMemLock);
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
Matrix::Core::UEWin32MemoryAlloc::UEWin32MemoryAlloc()
{
    // PageSize = 0;
    SYSTEM_INFO SI;
    //�õ� 32 λ Windows ϵͳҳ���С����Windows ���ı�̡������ᵽ�����һ���� CPU ��������
    //�� Intel �� AMD �Ĵ󲿷� CPU �� 4KB
    GetSystemInfo(&SI);
    PageSize = SI.dwPageSize;
    // pagesize��λΪ1����λ��ҪΪ0��
    MATRIX_ENGINE_ASSERT(!(PageSize & (PageSize - 1)));

    //��ʼ��Pool table
    OsTable.FirstPool = NULL;
    OsTable.ExhaustedPool = NULL;
    OsTable.BlockSize = 0;

    PoolTable[0].FirstPool = NULL;
    PoolTable[0].ExhaustedPool = NULL;
    PoolTable[0].BlockSize = 8;

    // blocksize ������
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

    //������ 0��32768�ֽ�ӳ�䵽 PoolTable �ı�
    //Ϊ�˿��ٲ��ҵ�Ҫ������ڴ�λ���ĸ� PoolTable �У�UnrealEngine ������һ�������������ٲ��ҡ�42 �� PoolTable ��
    // TableSize �����ϰ����� 1��32 768 �ֽ��ڴ�ռ�Ĺ�������PoolTable0 ���� 1��8 �ֽڣ�PoolTable1 ���� 9��12 �ֽڣ��Դ�
    //���ƣ�PoolTable41 ����28672 + 1����32 768 �ֽڡ����������Ϳ��Ժ����׽�������
    for (DWORD i = 0; i < POOL_MAX; i++)
    {
        DWORD Index;
        for (Index = 0; PoolTable[Index].BlockSize < i; Index++)
            ;
        MATRIX_ENGINE_ASSERT(Index < POOL_CATEGORY);
        //ÿһ��pooltable�ڵ�blocksize������Ҫ����i ��i���������ڴ�Ĵ�С, �������ڴ�Ĵ�С���ܳ���table��blocksize��
        MemSizeToPoolTable[i] = &PoolTable[Index];
    }
    for (DWORD i = 0; i < 32; i++)
    {
        //��� 32 ��һ������
        PoolIndirect[i] = NULL;
    }
    //�ж��Ƿ����ݶ�Ӧ����
    MATRIX_ENGINE_ASSERT(POOL_MAX - 1 == PoolTable[POOL_CATEGORY - 1].BlockSize);
}

Matrix::Core::UEWin32MemoryAlloc::~UEWin32MemoryAlloc()
{
    //�ͷ�������ڴ��
    for (unsigned int i = 0; i < 32; i++)
    {
        for (unsigned int j = 0; j < 2048; j++)
        {
            if (PoolIndirect[i])
            {
                if (PoolIndirect[i][j].MemoryAddr)
                {
                    VirtualFree(PoolIndirect[i][j].MemoryAddr, 0, MEM_RELEASE);
                    PoolIndirect[i][j].MemoryAddr = NULL;
                }

                VirtualFree(PoolIndirect[i], 0, MEM_RELEASE);
                PoolIndirect[i] = NULL;
            }
        }
    }
}

void *Matrix::Core::UEWin32MemoryAlloc::Allocate(USIZE_TYPE uSize, USIZE_TYPE uiAlignment, bool bIsArray)
{
    //�ڴ�������ֹ�����߳�ͬʱ�����ڴ�
    MXCriticalSection::Locker Temp(msMemLock);
    FFreeBlock *Free;
    //����pool_MAX���ڴ���ò���ϵͳ���ڴ����
    if (uSize < POOL_MAX)
    {
        // ���������ڴ�Ĵ�С�ҵ���ص��ڴ�table
        FPoolTable *Table = MemSizeToPoolTable[uSize];
        MATRIX_ENGINE_ASSERT(uSize < Table->BlockSize);
        FPoolInfo *Pool = Table->FirstPool;
        if (!Pool)
        {
            //���� PoolInfo�����ڴ��,��ÿ�� PoolInfo ���� 64KB = 65532  �ڴ�,
            //���ݵ�ǰ PoolTable ����ÿ����Ԫ��С��������ܿ���
            DWORD Blocks = 65536 / Table->BlockSize;
            DWORD Bytes = Blocks * Table->BlockSize;
            MATRIX_ENGINE_ASSERT(Blocks >= 1);
            MATRIX_ENGINE_ASSERT(Blocks * Table->BlockSize <= Bytes);

            //�����ڴ棬һ����  Windows ϵͳ���� 3 ���ڴ棬 ����ǵ�һ�࣬���� PoolInfo����ʹ Bytes С�� 64KB��
            //����page��λ��64KB������, ��������: MEM_COMMIT Ϊָ����ַ�ռ��ύ�����ڴ档���������ʼ������Ϊ��
            //��ͼ�ύ���ύ���ڴ�ҳ���ᵼ�º���ʧ�ܡ�����ζ���������ڲ�ȷ����ǰҳ�ĵ�ǰ�ύ״̬��������ύһϵ��ҳ�档
            //�����δ�����ڴ�ҳ�������ô�ֵ�ᵼ�º���ͬʱ�������ύ�ڴ�ҳ��
            Free = (FFreeBlock *)VirtualAlloc(NULL, Bytes, MEM_COMMIT, PAGE_READWRITE); //����һ��block
            if (!Free)
            {
                return NULL;
            }

            //ͨ��һ���������Ҷ�������, ����27������5λ
            FPoolInfo *&Indirect = PoolIndirect[((DWORD)Free >> 27)];
            if (!Indirect)
            {
                //������õ��ڴ����õ�PoolIndirect��
                Indirect = CreateIndirect();
            }
            //���ݶ��������ҵ���Ӧ�� PoolInfo
            Pool = &Indirect[((DWORD)Free >> 16) & 2047];

            //���ӵ���Ӧ PoolTable
            Pool->Link(Table->FirstPool);
            Pool->MemoryAddr = (BYTE *)Free;
            Pool->Bytes = Bytes;
            Pool->OsBytes = Align(Bytes, PageSize);
            Pool->Owner = Table;
            Pool->Taken = 0;
            Pool->pAvailableBlock = Free;

            // Create first free item
            Free->Blocks = Blocks;
            Free->Next = NULL;
        }

        // Pick first available block and unlink it.
        Pool->Taken++;
        MATRIX_ENGINE_ASSERT(Pool->pAvailableBlock);
        MATRIX_ENGINE_ASSERT(Pool->pAvailableBlock->Blocks > 0);
        //�Ӻ���ǰ���ǿ�����������õ�λ��ַ�����FFreeBlocks���ݡ�
        Free = (FFreeBlock *)((BYTE *)Pool->pAvailableBlock + --Pool->pAvailableBlock->Blocks * Table->BlockSize);
        if (Pool->pAvailableBlock->Blocks == 0)
        {
            // FreeMem blocks֮�������
            Pool->pAvailableBlock = Pool->pAvailableBlock->Next;
            if (!Pool->pAvailableBlock)
            {
                // poolinfo��ָ���block���˾ͽ�������ExhaustedPool
                Pool->Unlink();
                Pool->Link(Table->ExhaustedPool);
            }
        }
    }
    else
    {
        //����ڴ���ò���ϵͳ�����
        INT AlignedSize = Align(uSize, PageSize);
        Free = (FFreeBlock *)VirtualAlloc(NULL, AlignedSize, MEM_COMMIT, PAGE_READWRITE);
        if (!Free)
        {
            return NULL;
        }
        FPoolInfo *&Indirect = PoolIndirect[(DWORD)Free >> 27];
        if (!Indirect)
        {
            Indirect = CreateIndirect();
        }
        // init pool
        FPoolInfo *Pool = &Indirect[((DWORD)Free >> 16) & 2047];
        Pool->MemoryAddr = (BYTE *)Free;
        Pool->Bytes = uSize;
        Pool->OsBytes = AlignedSize;
        Pool->Owner = &OsTable;
    }
    return Free;
}

void Matrix::Core::UEWin32MemoryAlloc::Deallocate(char *pcAddr, USIZE_TYPE uiAlignment, bool bIsArray)
{
    MXCriticalSection::Locker Temp(msMemLock);
    MATRIX_ENGINE_ASSERT(pcAddr);
    if (!pcAddr)
    {
        return;
    }
    //ͨ����ά�����ҵ���Ӧ��PoolInfo
    FPoolInfo *Pool = &PoolIndirect[(DWORD)pcAddr >> 27][((DWORD)pcAddr >> 16) & 2047];
    MATRIX_ENGINE_ASSERT(Pool->Bytes != 0);
    if (Pool->Owner != &OsTable)
    {
        if (!Pool->pAvailableBlock)
        {
            // pAvailableBlockΪnull�� ���ǵ�pool�ͷź��ǿ��Է���ģ���Ҫ��pool�л������õ�pool�б�����Ժ�ķ���
            Pool->Unlink();
            Pool->Link(Pool->Owner->FirstPool);
        }

        // Free a pooled allocation.
        FFreeBlock *Free = (FFreeBlock *)pcAddr;
        Free->Blocks = 1; //��ǰ FreeMem ֻ���� 1 ����Ԫ��
        //���ӵ� PoolInfo ��һ�����õ� pAvailableBlock
        Free->Next = Pool->pAvailableBlock;
        Pool->pAvailableBlock = Free;
        MATRIX_ENGINE_ASSERT(Pool->Taken >= 1);
        if (--Pool->Taken == 0)
        {
            // Free the OS memory.
            //����ͷź󣬷��� 16 ����Ԫ�����У������� PoolInfo �黹��32 λWindows ϵͳ�����Լ��޿����� 1 ����Ԫ��ռ�ã�15 ������
            Pool->Unlink();
            VirtualFree(Pool->MemoryAddr, 0, MEM_RELEASE);
            Pool->MemoryAddr = NULL;
        }
    }
    else
    {
        // Free an OS allocation.
        VirtualFree(pcAddr, 0, MEM_RELEASE);
        Pool->MemoryAddr = NULL;
    }
}

UEWin32MemoryAlloc::FPoolInfo *Matrix::Core::UEWin32MemoryAlloc::CreateIndirect()
{
    //��������Ϊ�գ��򴴽�����������2048 �� PoolInfo ������ 64KB
    //���ǵڶ��࣬������ڴ������� 32 λ Windows ϵͳ��һ����������
    FPoolInfo *Indirect = (FPoolInfo *)VirtualAlloc(NULL, 2048 * sizeof(FPoolInfo), MEM_COMMIT, PAGE_READWRITE);
    if (!Indirect)
    {
        return NULL;
    }
    return Indirect;
}

#elif _DEBUG
#include <DbgHelp.h>
#include <DbgHelp.h>
typedef BOOL(WINAPI
                 *tFSymInitializeW)(
    _In_ HANDLE hProcess,
    _In_opt_ PCWSTR UserSearchPath,
    _In_ BOOL fInvadeProcess);
typedef BOOL(WINAPI
                 *tFSymGetLineFromAddr64)(
    IN HANDLE hProcess,
    IN DWORD64 qwAddr,
    OUT PDWORD pdwDisplacement,
    OUT PIMAGEHLP_LINE64 Line64);

typedef DWORD(WINAPI
                  *tFSymGetOptions)(
    VOID);

typedef DWORD(WINAPI
                  *tFSymSetOptions)(
    IN DWORD SymOptions);
static tFSymGetLineFromAddr64 fnSymGetLineFromAddr64 = NULL;
static tFSymGetOptions fnSymGetOptions = NULL;
static tFSymSetOptions fnSymSetOptions = NULL;
static tFSymInitializeW fnSymInitializeW = NULL;
static HMODULE s_DbgHelpLib = NULL;

Matrix::Core::DebugMemoryAlloc::DebugMemoryAlloc()
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

Matrix::Core::DebugMemoryAlloc::~DebugMemoryAlloc()
{
    //��̬����dbghelp.dll
    InitDbgHelpLib();
    PrintInfo();
    FreeDbgHelpLib();

    FreeLeakMem();
}

bool Matrix::Core::DebugMemoryAlloc::InitDbgHelpLib()
{
    TCHAR szDbgName[MAX_PATH];
    GetModuleFileName(NULL, szDbgName, MAX_PATH);
    TCHAR *p = (TCHAR *)MXCsrchr(szDbgName, _T('\\'));
    if (p)
    {
        //��ȡ�ļ�·������
        *p = 0;
    }
    MXStrcat(szDbgName, MAX_PATH, _T("\\dbghelp.dll"));

    // ���ҵ�ǰĿ¼��DLL
    s_DbgHelpLib = LoadLibrary(szDbgName);
    MATRIX_ENGINE_ASSERT(s_DbgHelpLib);
    //���ݴ����ַ���� fnSymGetLineFromAddr64 �����Ϳ��Ի�ö�ջ���������ļ��������������ļ������ơ�
    //һ�������ڴ�й¶���Ϳ���׼ȷ���ҵ�й©���������ù��̡������ַ��������ڴ�й¶ʱ����� Debug ģʽ
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

void Matrix::Core::DebugMemoryAlloc::FreeLeakMem()
{
    Block *pBlock = pHead;
    while (pBlock)
    {
        Block *Temp = pBlock;
        pBlock = pBlock->pNext;
        free((void *)Temp);
        // todo : �˴�Ӧ��ʹMXCMemm::Deallocate()�����Ƿ����? �о�ʹ��free���Ǻܺ���
        // MMemObject::GetCMemManager().Deallocate((char *)Temp, pBlock->mbAlignment, pBlock->mbArray);
    }
}

void Matrix::Core::DebugMemoryAlloc::PrintInfo()
{
    MXOutputDebugString(_T("#########################  begin print leak mem  ######################\n"));
    MXOutputDebugString(_T("Max Byte Num: %d\n"), mMaxNumBytes);
    MXOutputDebugString(_T("Max Block Num: %d\n"), mMaxNumBlocks);
    MXOutputDebugString(_T("Total Size: %d\n"), mNumBytes);
    MXOutputDebugString(_T("Block Num: %d\n"), mNumBlocks);
    MXOutputDebugString(_T("New Call: %d\n"), mNumNewCalls);
    MXOutputDebugString(_T("Delete Call: %d\n"), mNumDeleteCalls);

    if (pHead)
    {
        MXOutputDebugString(_T("Memory Leak:\n"));
    }
    else
    {
        MXOutputDebugString(_T("No Memory Leak\n"));
    }
    Block *pBlock = pHead;
    static unsigned int uiLeakNum = 0;
    while (pBlock)
    {

        uiLeakNum++;
        MXOutputDebugString(_T("$$$$$$$$$$$$$$$$  Leak %d  $$$$$$$$$$$$$$$$$\n"), uiLeakNum);
        MXOutputDebugString(_T("Size: %d\n"), pBlock->mSize);
        MXOutputDebugString(_T("Is Array:%d\n"), pBlock->mbArray);
#if WINDOWS_PLATFORM
        TCHAR szFile[MAX_PATH];
        int line;
        for (unsigned int i = 0; i < pBlock->mStackInfoNum; i++)
        {

            if (!GetFileAndLine(pBlock->pStackAddr[i], szFile, line))
            {
                break;
            }
            MXOutputDebugString(_T("%s(%d)\n"), szFile, line);
        }
#endif
        MXOutputDebugString(_T("$$$$$$$$$$$$$$$$$ Leak %d  $$$$$$$$$$$$$$$$$$$\n"), uiLeakNum);
        pBlock = pBlock->pNext;
    }
    MXOutputDebugString(_T("leak block total num : %d\n"), uiLeakNum);

    MXOutputDebugString(_T("#########################  end print leak mem  ######################\n"));
}

void Matrix::Core::DebugMemoryAlloc::FreeDbgHelpLib()
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

void *Matrix::Core::DebugMemoryAlloc::Allocate(USIZE_TYPE uSize, USIZE_TYPE uiAlignment, bool bIsArray)
{
    MXCriticalSection::Locker Temp(msMemLock);
    MATRIX_ENGINE_ASSERT(uSize);
    mNumNewCalls++;

    //������ܿռ�
    USIZE_TYPE extendedSize = sizeof(Block) + sizeof(unsigned int) + uSize + sizeof(unsigned int);
    char *pcAddr = (char *)MemoryObject::GetCMemoryManager().Allocate(extendedSize, uiAlignment, bIsArray);
    MATRIX_ENGINE_ASSERT(pcAddr);
    //��д Block ��Ϣ
    Block *pBlock = (Block *)pcAddr;
    pBlock->mSize = uSize;
    pBlock->mbArray = bIsArray;

    bool bAlignment = (uiAlignment > 0) ? true : false;
    pBlock->mbAlignment = bAlignment;
    pBlock->mStackInfoNum = 0;

    //��ȡ��ǰ�����ĵ���ջ����
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

    //����ڵ�
    InsertBlock(pBlock);
    pcAddr += sizeof(Block);

    //��дͷ��ʶ
    unsigned int *pBeginMask = (unsigned int *)(pcAddr);
    *pBeginMask = BEGIN_MASK;
    pcAddr += sizeof(unsigned int);
    //��дβ��ʶ
    unsigned int *pEndMask = (unsigned int *)(pcAddr + uSize);
    *pEndMask = END_MASK;

    // todo list
    mNumBlocks++;
    mNumBytes += (unsigned int)uSize;
    //��¼����ֽ���������������
    if (mNumBytes > mMaxNumBytes)
    {
        mMaxNumBytes = mNumBytes;
    }
    if (mNumBlocks > mMaxNumBlocks)
    {
        mMaxNumBlocks = mNumBlocks;
    }

    // uSize �����������ֽ�����������δ������� uSize �䵽 2n���ĸ���Χ������ͳ�ơ�
    //������� 15 �ֽڣ�i ���� 4 ��ʱ��uiTwoPowerI ���� 16��15 С�� 16�������� 23�� 24֮�䣬
    //�����Ϳ���ͳ�Ƴ��� 2 Ϊ������ͬ��С�ڴ�ķ������
    unsigned int uiTwoPowerI = 1;
    int i;
    for (i = 0; i <= RECORD_NUM - 2; i++, uiTwoPowerI <<= 1)
    {
        if (uSize <= uiTwoPowerI)
        {
            mSizeRecord[i]++;
            break;
        }
    }
    if (i == RECORD_NUM - 1)
    {
        mSizeRecord[i]++;
    }

    return (void *)pcAddr;
}

void DebugMemoryAlloc::Deallocate(char *pcAddr, USIZE_TYPE uiAlignment, bool bIsArray)
{
    MXCriticalSection::Locker Temp(msMemLock);
    //���� delete �Ĵ���ͳ��
    mNumDeleteCalls++;
    MATRIX_ENGINE_ASSERT(pcAddr);

    //�ж�ͷ��ʶ
    pcAddr -= sizeof(unsigned int);
    unsigned int *pBeginMask = (unsigned int *)(pcAddr);
    MATRIX_ENGINE_ASSERT(*pBeginMask == BEGIN_MASK);
    pcAddr -= sizeof(Block);
    Block *pBlock = (Block *)pcAddr;

    MATRIX_ENGINE_ASSERT(pBlock->mbArray == bIsArray);
    MATRIX_ENGINE_ASSERT(mNumBlocks > 0 && mNumBytes >= pBlock->mSize);
    bool bAlignment = (uiAlignment > 0) ? true : false;
    MATRIX_ENGINE_ASSERT(pBlock->mbAlignment == bAlignment);
    //�ж�β��ʶ
    unsigned int *pEndMask = (unsigned int *)(pcAddr + sizeof(Block) + sizeof(unsigned int) + pBlock->mSize);
    MATRIX_ENGINE_ASSERT(*pEndMask == END_MASK);

    //����ͳ������
    mNumBlocks--;
    mNumBytes -= (unsigned int)pBlock->mSize;

    //ɾ���ڵ�
    RemoveBlock(pBlock);
    // free(pcAddr);
    MemoryObject::GetCMemoryManager().Deallocate(pcAddr, uiAlignment, bIsArray);
}

void Matrix::Core::DebugMemoryAlloc::InsertBlock(Block *pBlock)
{
    //�����ж�β���������
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
        //ͷβָ��һ��
        pHead = pBlock;
        pTail = pBlock;
    }
}

void Matrix::Core::DebugMemoryAlloc::RemoveBlock(Block *pBlock)
{
    //�Ƴ�ʱ���ж�ͷָ��������
    //����ָ��Ĳ����߼����Ǵ�pre��next�Ƚ���ָ���ϵ��Ȼ������ɾ��������
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

bool Matrix::Core::DebugMemoryAlloc::GetFileAndLine(const void *pAddress, TCHAR szFile[MAX_PATH], int &line)
{
    IMAGEHLP_LINE64 Line;
    Line.SizeOfStruct = sizeof(Line);
    MXMemset(&Line, 0, sizeof(Line));
    DWORD Offset = 0;
    //ͨ�� fnSymGetLineFromAddr64 �õ� IMAGEHLP_LINE64 �� FileName��
    //�����õ��������������������ļ�����pAddress �Ǻ�����ַ
    if (fnSymGetLineFromAddr64(GetCurrentProcess(), (DWORD64)pAddress, &Offset, &Line))
    {
#ifdef _UNICODE
        MXMbsToWcs(szFile, MAX_PATH, Line.FileName, MAX_PATH);
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
#if defined(_DEBUG)
#undef _DEBUG
#endif
#include <scalable_allocator.h>

Matrix::Core::Win64MemoryAlloc::Win64MemoryAlloc()
{
}
Matrix::Core::Win64MemoryAlloc::~Win64MemoryAlloc()
{
}

void *Matrix::Core::Win64MemoryAlloc::Allocate(USIZE_TYPE uSize, USIZE_TYPE uiAlignment, bool bIsArray)
{
    if (uiAlignment != 0)
    {
        uiAlignment = __max(uSize >= 16 ? (USIZE_TYPE)16 : (USIZE_TYPE)8, uiAlignment);
        return scalable_aligned_malloc(uSize, uiAlignment);
    }
    else
    {
        return scalable_malloc(uSize);
    }
}
void Matrix::Core::Win64MemoryAlloc::Deallocate(char *pcAddr, USIZE_TYPE uiAlignment, bool bIsArray)
{
    if (!pcAddr)
    {
        return;
    }
    if (uiAlignment != 0)
    {
        scalable_aligned_free(pcAddr);
    }
    else
    {
        scalable_free(pcAddr);
    }
}
#endif

Matrix::Core::StackMemoryManager::StackMemoryManager(USIZE_TYPE uiDefaultChunkSize)

{
    //Ĭ��size ��Ҫ���� FTaggedMemory ��С
    MATRIX_ENGINE_ASSERT(uiDefaultChunkSize > sizeof(FTaggedMemory));
    Top = NULL;
    End = NULL;
    DefaultChunkSize = uiDefaultChunkSize;
    TopChunk = NULL;
    UnusedChunks = NULL;
    NumMarks = 0;
}

Matrix::Core::StackMemoryManager::~StackMemoryManager()
{
    FreeChunks(NULL);
    while (UnusedChunks)
    {
        void *Old = UnusedChunks;
        UnusedChunks = UnusedChunks->Next;
        MemoryObject::GetMemoryManager().Deallocate((char *)Old, 0, true);
    }
    //�����Ƿ�ȡ���������
    MATRIX_ENGINE_ASSERT(NumMarks == 0);
}
void *Matrix::Core::StackMemoryManager::Allocate(USIZE_TYPE uSize, USIZE_TYPE uiAlignment, bool bIsArray)
{
    MATRIX_ENGINE_ASSERT(uSize >= 0);
    if (uiAlignment > 0)
    {
        MATRIX_ENGINE_ASSERT((uiAlignment & (uiAlignment - 1)) == 0);
    }

    MATRIX_ENGINE_ASSERT(Top <= End);
    MATRIX_ENGINE_ASSERT(NumMarks > 0);
    //�ӵ�ǰchunk�����ռ�
    BYTE *Result = Top;
    if (uiAlignment > 0)
    {
        //�ֽڶ���
        Result = (BYTE *)(((USIZE_TYPE)Top + (uiAlignment - 1)) & ~(uiAlignment - 1));
    }
    Top = Result + uSize;
    //������ǰchunk��С�� �����µ�Chunk
    if (Top > End)
    {
        //�����㹻�ֽڶ���Ŀռ�
        AllocateNewChunk(uSize + uiAlignment);
        Result = Top;
        if (uiAlignment > 0)
        {
            //�ֽڶ���
            Result = (BYTE *)(((USIZE_TYPE)Top + (uiAlignment - 1)) & ~(uiAlignment - 1));
        }
        //���� Top ָ��
        Top = Result + uSize;
    }
    return Result;
}
void Matrix::Core::StackMemoryManager::Deallocate(char *pcAddr, USIZE_TYPE uiAlignment, bool bIsArray)
{
}
void Matrix::Core::StackMemoryManager::Clear()
{
    FreeChunks(NULL);
}
BYTE *Matrix::Core::StackMemoryManager::AllocateNewChunk(USIZE_TYPE MinSize)
{
    FTaggedMemory *Chunk = NULL;
    for (FTaggedMemory **link = &UnusedChunks; *link; link = &(*link)->Next)
    {
        // Find existing chunk
        if ((*link)->DataSize >= (INT)MinSize)
        {
            Chunk = *link;
            *link = (*link)->Next;
            break;
        }
    }
    if (!Chunk)
    {
        // Create MATRIX_NEW chunk.

        USIZE_TYPE DataSize = max(MinSize, DefaultChunkSize - sizeof(FTaggedMemory));
        Chunk = (FTaggedMemory *)MemoryObject::GetMemoryManager().Allocate(DataSize + sizeof(FTaggedMemory), 0, true);
        Chunk->DataSize = DataSize;
    }

    Chunk->Next = TopChunk;
    TopChunk = Chunk;
    Top = Chunk->Data;
    End = Top + Chunk->DataSize;

    return Top;
}
void Matrix::Core::StackMemoryManager::FreeChunks(FTaggedMemory *NewTopChunk)
{
    //�ͷ� NewTopChunk �� TopChunk ������ Chunk
    //������ͷž��ǽ�topchunkָ���chunkת�Ƶ�unusedchunk���С�
    while (TopChunk != NewTopChunk)
    {
        FTaggedMemory *RemoveChunk = TopChunk;
        TopChunk = TopChunk->Next;
        RemoveChunk->Next = UnusedChunks;
        UnusedChunks = RemoveChunk;
    }
    //���� Top��End �� TopChunck
    Top = NULL;
    End = NULL;
    if (TopChunk)
    {
        Top = TopChunk->Data;
        End = Top + TopChunk->DataSize;
    }
}
Matrix::Core::MemoryObject::MemoryObject()
{
    //����Ҫ�����ڴ��ʼ����˳���ϵ�� stackmanagerʵ������heap memory���ڴ���䣬
    //��̬��������˳��������˳���෴�� ���Ƚ����ԭ��
    GetCMemoryManager();
    GetMemoryManager();
    GetStackMemoryManager();
}
Matrix::Core::MemoryObject::~MemoryObject()
{
}

StackMemoryManager &Matrix::Core::MemoryObject::GetStackMemoryManager()
{
    static MXTlsValue g_TlsValue;
    void *pTlsValue = g_TlsValue.GetThreadValue();
    if (!pTlsValue)
    {
        pTlsValue = MX_NEW StackMemoryManager();
        g_TlsValue.SetThreadValue(pTlsValue);
    }
    return *((StackMemoryManager *)pTlsValue);
}
BaseMemoryManager &Matrix::Core::MemoryObject::GetMemoryManager()
{
#if !_DEBUG && !_WIN64
    static UEWin32MemoryAlloc gMemManager;
#elif _DEBUG
    static DebugMemoryAlloc gMemManager;
#else
    static Win64MemoryAlloc gMemManager;
#endif // !_DEBUG  && !_WIN64
    return gMemManager;
}
BaseMemoryManager &Matrix::Core::MemoryObject::GetCMemoryManager()
{
    static CMemoryManager g_MemManager;
    return g_MemManager;
}
