#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <Windows.h>

typedef struct {
    
    HANDLE hProcess;

    DWORD pid;

} MemoryManager;

MemoryManager* MemoryManager_new(DWORD pid);

void MemoryManager_delete(MemoryManager* mm);

int MemoryManager_openProcess(MemoryManager* mm);

int MemoryManager_writeInt(MemoryManager* mm, LPVOID address, int value);

#endif 
