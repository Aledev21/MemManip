#include <gtk/gtk.h>
#include "memory_manager.h"
#include "list_process.h"

static MemoryManager *mm = NULL;

static void on_process_selected(pid_t pid, gpointer user_data) {
    GtkWidget *label = GTK_WIDGET(user_data);

    if (!GTK_IS_LABEL(label)) {
        g_print("Error: user_data is not a GtkLabel.\n");
        return;
    }

    gchar *text = g_strdup_printf("Selected Process: PID=%d", pid);
    gtk_label_set_text(GTK_LABEL(label), text);
    g_free(text);

    // Configura mm para o processo selecionado
    if (mm != NULL) {
        MemoryManager_delete(mm);
    }
    mm = MemoryManager_new(pid);
    if (mm == NULL) {
        g_print("Failed to create MemoryManager.\n");
        return;
    }
}


static void on_row_selected(GtkListBox *listbox, GtkListBoxRow *row, gpointer user_data) {
    GtkWidget *label = gtk_bin_get_child(GTK_BIN(row));

    if (!GTK_IS_LABEL(label)) {
        g_print("Error: The selected row does not contain a GtkLabel.\n");
        return;
    }

    gchar *pid_str = gtk_label_get_text(GTK_LABEL(label));
    pid_t pid = (pid_t)atoi(pid_str);

    on_process_selected(pid, user_data);
}


static void fill_process_listbox(GtkWidget *listbox, gpointer user_data) {
    gtk_container_foreach(GTK_CONTAINER(listbox), (GtkCallback)gtk_widget_destroy, NULL);

    // Lista os processos e adiciona ao listbox
    void process_callback(pid_t pid, gpointer data) {
        GtkWidget *listbox = GTK_WIDGET(data);
        gchar *pid_str = g_strdup_printf("%d", pid);
        GtkWidget *row = gtk_list_box_row_new();
        GtkWidget *label = gtk_label_new(pid_str);
        gtk_container_add(GTK_CONTAINER(row), label);
        gtk_list_box_insert(GTK_LIST_BOX(listbox), row, -1);
        g_free(pid_str);
    }

    list_processes(process_callback, listbox);
}


static void on_button_list_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *listbox = GTK_WIDGET(user_data);
    fill_process_listbox(listbox, gtk_widget_get_parent(GTK_WIDGET(button)));
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

    GtkWidget *listbox = gtk_list_box_new();
    gtk_box_pack_start(GTK_BOX(box), listbox, TRUE, TRUE, 0);

    GtkWidget *button_list = gtk_button_new_with_label("List Processes");
    gtk_box_pack_start(GTK_BOX(box), button_list, FALSE, FALSE, 0);

    g_signal_connect(button_list, "clicked", G_CALLBACK(on_button_list_clicked), listbox);
    g_signal_connect(listbox, "row-activated", G_CALLBACK(on_row_selected), label);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
