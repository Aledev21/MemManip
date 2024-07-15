#include <gtk/gtk.h>
#include "memory_manager.h"
#include "list_process.h"

static MemoryManager *mm = NULL;

static void button_clicked(GtkWidget *widget, gpointer data) {
    pid_t pid = (pid_t)data;
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
        mm = NULL;
        return;
    }

    if (!MemoryManager_writeInt(mm, address, value)) {
        g_print("Failed to write in memory.\n");
        MemoryManager_delete(mm);
        mm = NULL;
        return;
    }

    g_print("Value %d written to memory at address %p.\n", value, address);
}

static void process_selected_callback(pid_t pid, gpointer user_data) {
    GtkWidget *button = GTK_WIDGET(user_data);

    gchar *label_text = g_strdup_printf("Selected Process: PID=%d", pid);
    gtk_button_set_label(GTK_BUTTON(button), label_text);
    g_free(label_text);

    g_signal_handlers_disconnect_by_func(button, G_CALLBACK(button_clicked), GUINT_TO_POINTER(pid));
    g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), GUINT_TO_POINTER(pid));
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Memory Manager Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(box), 10);
    gtk_container_add(GTK_CONTAINER(window), box);

    GtkWidget *label = gtk_label_new("Selected Process:");
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);

    GtkWidget *button_list = gtk_button_new_with_label("List Processes");
    gtk_box_pack_start(GTK_BOX(box), button_list, FALSE, FALSE, 0);

    GtkWidget *button_write = gtk_button_new_with_label("Write Memory");
    gtk_box_pack_start(GTK_BOX(box), button_write, FALSE, FALSE, 0);

    g_signal_connect(button_list, "clicked", G_CALLBACK(list_processes), process_selected_callback);
    g_signal_connect(button_write, "clicked", G_CALLBACK(button_clicked), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
