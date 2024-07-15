#ifndef LIST_PROCESS_H
#define LIST_PROCESS_H

#include <gtk/gtk.h>
#include "memory_manager.h"

typedef void (*ProcessSelectedCallback)(pid_t pid, gpointer user_data);

void list_processes(ProcessSelectedCallback callback, gpointer user_data);

#endif 
