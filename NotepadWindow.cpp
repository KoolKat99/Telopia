#include "NotepadWindow.h"
#include "NotepadController.h"

NotepadWindow::NotepadWindow(NotepadController* controller) : controller(controller) {
    // Initialize GTK
    gtk_init(NULL, NULL);

    // Create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Telopia Notepad");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // Create vertical box
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create menu bar
    menu_bar = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(vbox), menu_bar, FALSE, FALSE, 0);

    // Create File menu
    file_menu = gtk_menu_new();
    GtkWidget* file_menu_item = gtk_menu_item_new_with_label("File");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu_item), file_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), file_menu_item);

    // Create File menu items
    GtkWidget* new_item = gtk_menu_item_new_with_label("New");
    g_signal_connect(new_item, "activate", G_CALLBACK(on_menu_file_new), this);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), new_item);

    GtkWidget* open_item = gtk_menu_item_new_with_label("Open");
    g_signal_connect(open_item, "activate", G_CALLBACK(on_menu_file_open), this);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), open_item);

    GtkWidget* save_item = gtk_menu_item_new_with_label("Save");
    g_signal_connect(save_item, "activate", G_CALLBACK(on_menu_file_save), this);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), save_item);

    GtkWidget* save_as_item = gtk_menu_item_new_with_label("Save As");
    g_signal_connect(save_as_item, "activate", G_CALLBACK(on_menu_file_save_as), this);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), save_as_item);

    GtkWidget* quit_item = gtk_menu_item_new_with_label("Quit");
    g_signal_connect(quit_item, "activate", G_CALLBACK(on_menu_file_quit), this);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), quit_item);

    // Create Help menu
    help_menu = gtk_menu_new();
    GtkWidget* help_menu_item = gtk_menu_item_new_with_label("Help");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_menu_item), help_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), help_menu_item);

    // Create Help menu items
    GtkWidget* about_item = gtk_menu_item_new_with_label("About");
    g_signal_connect(about_item, "activate", G_CALLBACK(on_menu_help_about), this);
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), about_item);

    // Create text view
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);
    text_view = gtk_text_view_new();
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    // Connect delete event to quit
    g_signal_connect(window, "delete-event", G_CALLBACK(on_menu_file_quit), this);
}

NotepadWindow::~NotepadWindow() {
    // Nothing to do here
}

void NotepadWindow::show() {
    gtk_widget_show_all(window);
    gtk_main();
}

GtkTextBuffer* NotepadWindow::get_text_buffer() {
    return text_buffer;
}

void NotepadWindow::on_menu_file_new(GtkWidget *widget, gpointer data) {
    NotepadWindow* self = static_cast<NotepadWindow*>(data);
    self->controller->on_new();
}

void NotepadWindow::on_menu_file_open(GtkWidget *widget, gpointer data) {
    NotepadWindow* self = static_cast<NotepadWindow*>(data);
    self->controller->on_open();
}

void NotepadWindow::on_menu_file_save(GtkWidget *widget, gpointer data) {
    NotepadWindow* self = static_cast<NotepadWindow*>(data);
    self->controller->on_save();
}

void NotepadWindow::on_menu_file_save_as(GtkWidget *widget, gpointer data) {
    NotepadWindow* self = static_cast<NotepadWindow*>(data);
    self->controller->on_save_as();
}

void NotepadWindow::on_menu_file_quit(GtkWidget *widget, gpointer data) {
    NotepadWindow* self = static_cast<NotepadWindow*>(data);
    self->controller->on_quit();
}

void NotepadWindow::on_menu_help_about(GtkWidget *widget, gpointer data) {
    NotepadWindow* self = static_cast<NotepadWindow*>(data);
    self->controller->on_about();
}

GtkWidget* NotepadWindow::get_window() {
    return window;
}