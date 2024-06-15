#include "NotepadWindow.h"
#include <fstream>
#include <sstream>

NotepadWindow::NotepadWindow() {
    // Initialize GTK
    gtk_init(0, nullptr);

    // Create main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Simple Notepad");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);

    // Create vertical box container
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create menu bar
    menu_bar = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(vbox), menu_bar, FALSE, FALSE, 0);

    // Create File menu
    file_menu = gtk_menu_new();

    GtkWidget *file_menu_item = gtk_menu_item_new_with_label("File");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu_item), file_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), file_menu_item);

    GtkWidget *new_item = gtk_menu_item_new_with_label("New");
    g_signal_connect(new_item, "activate", G_CALLBACK(on_menu_file_new), this);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), new_item);

    GtkWidget *open_item = gtk_menu_item_new_with_label("Open");
    g_signal_connect(open_item, "activate", G_CALLBACK(on_menu_file_open), this);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), open_item);

    GtkWidget *save_item = gtk_menu_item_new_with_label("Save");
    g_signal_connect(save_item, "activate", G_CALLBACK(on_menu_file_save), this);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), save_item);

    GtkWidget *save_as_item = gtk_menu_item_new_with_label("Save As");
    g_signal_connect(save_as_item, "activate", G_CALLBACK(on_menu_file_save_as), this);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), save_as_item);

    GtkWidget *quit_item = gtk_menu_item_new_with_label("Quit");
    g_signal_connect(quit_item, "activate", G_CALLBACK(on_menu_file_quit), this);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), quit_item);

    // Create Help menu
    help_menu = gtk_menu_new();

    GtkWidget *help_menu_item = gtk_menu_item_new_with_label("Help");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_menu_item), help_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), help_menu_item);

    GtkWidget *about_item = gtk_menu_item_new_with_label("About");
    g_signal_connect(about_item, "activate", G_CALLBACK(on_menu_help_about), this);
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), about_item);

    // Create TextView inside a ScrolledWindow
    scrolled_window = gtk_scrolled_window_new(nullptr, nullptr);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

    text_view = gtk_text_view_new();
    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    // Create FileChooserDialog
    file_chooser_dialog = gtk_file_chooser_dialog_new("Choose a file", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN,
                                                      "_Cancel", GTK_RESPONSE_CANCEL,
                                                      "_Open", GTK_RESPONSE_OK, nullptr);
}

NotepadWindow::~NotepadWindow() {
    gtk_widget_destroy(window);
}

void NotepadWindow::show() {
    gtk_widget_show_all(window);
    gtk_main();
}

void NotepadWindow::on_menu_file_new(GtkWidget *widget, gpointer data) {
    NotepadWindow *self = static_cast<NotepadWindow*>(data);
    gtk_text_buffer_set_text(self->text_buffer, "", -1);
}

void NotepadWindow::on_menu_file_open(GtkWidget *widget, gpointer data) {
    NotepadWindow *self = static_cast<NotepadWindow*>(data);
    gint result = gtk_dialog_run(GTK_DIALOG(self->file_chooser_dialog));
    if (result == GTK_RESPONSE_OK) {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(self->file_chooser_dialog));
        std::ifstream file(filename);
        std::stringstream buffer;
        buffer << file.rdbuf();
        gtk_text_buffer_set_text(self->text_buffer, buffer.str().c_str(), -1);
        g_free(filename);
    }
    gtk_widget_hide(self->file_chooser_dialog);
}

void NotepadWindow::on_menu_file_save(GtkWidget *widget, gpointer data) {
    // Implement save functionality here
}

void NotepadWindow::on_menu_file_save_as(GtkWidget *widget, gpointer data) {
    NotepadWindow *self = static_cast<NotepadWindow*>(data);
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(self->window), GTK_FILE_CHOOSER_ACTION_SAVE,
                                                    "_Cancel", GTK_RESPONSE_CANCEL,
                                                    "_Save", GTK_RESPONSE_OK, nullptr);

    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_OK) {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        std::ofstream file(filename);
        GtkTextIter start, end;
        gtk_text_buffer_get_bounds(self->text_buffer, &start, &end);
        char *text = gtk_text_buffer_get_text(self->text_buffer, &start, &end, FALSE);
        file << text;
        g_free(text);
        g_free(filename);
    }
    gtk_widget_destroy(dialog);
}

void NotepadWindow::on_menu_file_quit(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

void NotepadWindow::on_menu_help_about(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(((NotepadWindow*)data)->window),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               "About Simple Notepad");
    gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), "A simple Notepad application using GTK+.");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
