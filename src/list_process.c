#include "list_process.h"
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

void list_processes(ProcessSelectedCallback callback, gpointer user_data) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("/proc");
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && atoi(entry->d_name) != 0) {
            pid_t pid = atoi(entry->d_name);
            char filename[512];
            snprintf(filename, sizeof(filename), "/proc/%d/cmdline", pid);

            FILE *fp = fopen(filename, "r");
            if (fp != NULL) {
                char cmdline[256];
                if (fgets(cmdline, sizeof(cmdline), fp)) {
                    cmdline[strcspn(cmdline, "\n")] = '\0';
                    callback(pid, cmdline, user_data); // Passa o PID e o comando do processo
                }
                fclose(fp); 
            }
        }
    }

    closedir(dir);
}