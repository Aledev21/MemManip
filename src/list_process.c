#include "list_process.h"
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

void list_processes(ProcessSelectedCallback callback, gpointer user_data) 
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir("/proc");
    if (dir == NULL) 
    {
        perror("opendir");
        return;
    }
}