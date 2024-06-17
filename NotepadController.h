#ifndef NOTEPADCONTROLLER_H
#define NOTEPADCONTROLLER_H

#include <gtk/gtk.h>
#include "NotepadWindow.h"

class NotepadController {
    public:
        NotepadController();
        ~NotepadController();
        void on_new();
        void on_open();
        void on_save();
        void on_save_as();
        void on_quit();
        void on_about();

        NotepadWindow* get_view();

    private:
        NotepadWindow* view;
        std::string current_file;
        bool save_file(const std::string& filename);
        bool load_file(const std::string& filename);
};

#endif // NOTEPADCONTROLLER_H
