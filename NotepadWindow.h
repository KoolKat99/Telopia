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
        GtkWidget *hbox;
        GtkWidget *menu_bar;

        //menu bar
        GtkWidget *file_menu;
        GtkWidget *edit_menu;
        GtkWidget *view_menu;
        GtkWidget *search_menu;
        GtkWidget *settings_menu;
        GtkWidget *help_menu;

        //menu bar items
        GtkWidget* file_menu_item;
        GtkWidget* new_item;
        GtkWidget* open_item;
        GtkWidget* save_item;
        GtkWidget* save_as_item;
        GtkWidget* quit_item;
        GtkWidget* edit_menu_item;
        GtkWidget* cut_item;
        GtkWidget* copy_item;
        GtkWidget* paste_item;


        //content section
        GtkWidget* explorer_content;
        GtkWidget *explorer_scrolled_window;
        GtkWidget *text_scrolled_window;
        GtkWidget *explorer_window;
        GtkWidget *text_view;
        GtkTextBuffer *text_buffer;
        GtkWidget *file_chooser_dialog;
};

#endif // NOTEPADWINDOW_H

