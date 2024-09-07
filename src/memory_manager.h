#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <unistd.h>    
#include <sys/types.h> 

// Estrutura que representa o gerenciador de memória
typedef struct MemoryManager {
    pid_t pid; // PID do processo ao qual estamos anexados
} MemoryManager;


MemoryManager* MemoryManager_new(pid_t pid);

void MemoryManager_delete(MemoryManager* mm);


int MemoryManager_openProcess(MemoryManager* mm);

/
int MemoryManager_writeInt(MemoryManager* mm, void* address, int value);

#endif /* MEMORY_MANAGER_H */
