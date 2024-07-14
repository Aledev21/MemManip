#include "memory_mannager.h"
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