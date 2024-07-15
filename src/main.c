#include <gtk/gtk.h>
#include "memory_manager.h"

static void button_clicked(GtkWidget *widget, gpointer data) {
    MemoryManager *mm = (MemoryManager *)data;
    pid_t pid = 1234;
    void *address = (void *)0x00401000;
    int value = 100;

    if (mm == NULL) {
        mm = MemoryManager_new(pid);
        if (mm == NULL) {
            g_print("Failed to create MemoryManager.\n");
            return;
        }
    }

    if (!MemoryManager_openProcess(mm)) {
        g_print("Failed to open process.\n");
        MemoryManager_delete(mm);
        return;
    }

    if (!MemoryManager_writeInt(mm, address, value)) {
        g_print("Failed to write in memory.\n");
        MemoryManager_delete(mm);
        return;
    }

    g_print("Value %d written to memory at address %p.\n", value, address);

    MemoryManager_delete(mm);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Memory Manager Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *button = gtk_button_new_with_label("Write Memory");
    MemoryManager *mm = NULL;

    g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), mm);

    gtk_container_add(GTK_CONTAINER(window), button);
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
