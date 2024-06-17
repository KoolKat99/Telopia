#ifndef NOTEPADWINDOW_H
#define NOTEPADWINDOW_H

//View

#include <gtk/gtk.h>
#include <iostream>

class NotepadController;  // Forward declaration

class NotepadWindow {
    public:
        NotepadWindow(NotepadController* controller);
        ~NotepadWindow();
        void show();
        GtkTextBuffer* get_text_buffer();
        GtkWidget* get_window();

    private:
        static void on_menu_file_new(GtkWidget *widget, gpointer data);
        static void on_menu_file_open(GtkWidget *widget, gpointer data);
        static void on_menu_file_save(GtkWidget *widget, gpointer data);
        static void on_menu_file_save_as(GtkWidget *widget, gpointer data);
        static void on_menu_file_quit(GtkWidget *widget, gpointer data);
        static void on_menu_help_about(GtkWidget *widget, gpointer data);

        NotepadController* controller;
        GtkWidget *window;
        GtkWidget *vbox;
        GtkWidget *menu_bar;
        GtkWidget *file_menu;
        GtkWidget *help_menu;
        GtkWidget *scrolled_window;
        GtkWidget *text_view;
        GtkTextBuffer *text_buffer;
        GtkWidget *file_chooser_dialog;
};

#endif // NOTEPADWINDOW_H

