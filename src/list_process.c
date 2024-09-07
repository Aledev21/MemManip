#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include "list_process.h"

#ifndef DT_DIR
#define DT_DIR 4
#endif

void list_processes(ProcessSelectedCallback callback, gpointer user_data) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("/proc");
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        if (entry->d_type != DT_DIR)
            continue;

        pid_t pid = atoi(entry->d_name);
        if (pid <= 0)
            continue;

        char filename[512];
        snprintf(filename, sizeof(filename), "/proc/%d/cmdline", pid);

        FILE *fp = fopen(filename, "r");
        if (fp != NULL) {
            char cmdline[256];
            if (fgets(cmdline, sizeof(cmdline), fp)) {
                cmdline[strcspn(cmdline, "\n")] = '\0';
                callback(pid, user_data); // Chama a função de callback com o PID do processo
            }
            fclose(fp);
        }
    }

    closedir(dir);
}
