#include "memory_manager.h"
#include <stdio.h>

MemoryManager* MemoryManager_new(DWORD pid) 
{
    MemoryManager* mm = (MemoryManager*)malloc(sizeof(MemoryManager));
    if (mm != NULL) 
    {
        mm->pid = pid;
        mm->hProcess = NULL;
    }
    return mm;
}

void MemoryManager_delete(MemoryManager* mm)
{
    if (mm != NULL && mm -> hProcess != NULL)
    {
        CloseHandle(mm->hProcess);
    }
    free(mm)
}

int MemoryManager_openProcess(MemoryManager* mm)
{
    mm ->hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, mm ->pid);

    if (mm->hProcess == NULL) 
    {
        fprintf(stderr, "Error to open process. Code error: %lu\n", GetLastError())
        return (0);
    }
    return (1);
}

int MemoryManager_writeInt(memoryManager* mm, LPVOID address, int value {})
{
    if (!WriteProcessMemory(mm->hProcess, address, &value, sizeof(value),NULL))
    {
        fprintf(stderr, "Error to write in memory. Code error: %lu\n", GetLastError());
        
        Closehandle(mm->hProcess);

        return 0;
    }
    return 1;
}