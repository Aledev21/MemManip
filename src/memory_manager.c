#include "memory_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <errno.h>



MemoryManager* MemoryManager_new(pid_t pid)
{
    MemoryManager* mm = (MemoryManager*)malloc(sizeof(MemoryManager));
    if (mm != NULL)
    {
        mm->pid = pid;
    }
    return mm;
}

void MemoryManager_delete(MemoryManager* mm)
{
    free(mm);
}

int MemoryManager_openProcess(MemoryManager* mm)
{
    if (ptrace(PTRACE_ATTACH, mm->pid, NULL, NULL) == -1)
    {
        perror("Error attaching to process");
        return 0;
    }
    
    printf("Attached to process with PID: %d\n", mm->pid);
    
    return 1;
}

int MemoryManager_writeInt(MemoryManager* mm, void* address, int value)
{
    long data = value;
    if (ptrace(PTRACE_POKETEXT, mm->pid, address, data) == -1)
    {
        perror("Error writing to process memory");
        return 0;
    }
    
    printf("Wrote value %d to address %p\n", value, address);
    
    return 1;
}
