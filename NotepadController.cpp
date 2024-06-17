#include "NotepadController.h"
#include <fstream>
#include <iostream>

NotepadController::NotepadController() {
    view = new NotepadWindow(this);
}

NotepadController::~NotepadController() {
    delete view;
}

void NotepadController::on_new() {
    gtk_text_buffer_set_text(view->get_text_buffer(), "", -1);
    current_file.clear();
}

void NotepadController::on_open() {
    GtkWidget* dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(view->get_window()), GTK_FILE_CHOOSER_ACTION_OPEN,
        "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        load_file(filename);
        g_free(filename);
    }
    gtk_widget_destroy(dialog);
}

void NotepadController::on_save() {
    if (current_file.empty()) {
        on_save_as();
    } else {
        save_file(current_file);
    }
}

void NotepadController::on_save_as() {
    GtkWidget* dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(view->get_window()), GTK_FILE_CHOOSER_ACTION_SAVE,
        "_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, NULL);

    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        save_file(filename);
        current_file = filename;
        g_free(filename);
    }
    gtk_widget_destroy(dialog);
}

void NotepadController::on_quit() {
    gtk_main_quit();
}

void NotepadController::on_about() {
    GtkWidget* dialog = gtk_message_dialog_new(GTK_WINDOW(view->get_window()), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
        "Notepad\nVersion 1.0\n\nA simple GTK-based notepad application.");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

NotepadWindow* NotepadController::get_view() {
    return view;
}

bool NotepadController::save_file(const std::string& filename) {
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(view->get_text_buffer(), &start, &end);
    char* text = gtk_text_buffer_get_text(view->get_text_buffer(), &start, &end, FALSE);

    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Could not open file for writing: " << filename << std::endl;
        return false;
    }

    file << text;
    file.close();
    g_free(text);
    return true;
}

bool NotepadController::load_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open file for reading: " << filename << std::endl;
        return false;
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    gtk_text_buffer_set_text(view->get_text_buffer(), content.c_str(), -1);
    file.close();
    current_file = filename;
    return true;
}
