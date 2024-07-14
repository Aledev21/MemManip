#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <sys/types.h>
#endif

typedef struct {
    #ifdef _WIN32
    HANDLE hProcess;
    DWORD pid;
    #else
    
    /
    #endif
} MemoryManager;

MemoryManager* MemoryManager_new(DWORD pid);
void MemoryManager_delete(MemoryManager* mm);

#ifdef _WIN32
int MemoryManager_openProcess(MemoryManager* mm);
int MemoryManager_writeInt(MemoryManager* mm, LPVOID address, int value);
#else

int MemoryManager_openProcess(MemoryManager* mm);
int MemoryManager_writeInt(MemoryManager* mm, void* address, int value);
#endif

#endif 