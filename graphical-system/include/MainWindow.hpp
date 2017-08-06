#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#define GUI_FILE "graphical_system.glade"

#include <gtk/gtk.h>
#include "ViewPort.hpp"
#include "LinkedList.hpp"

static cairo_surface_t* surface = NULL;

using namespace structures;

class MainWindow
{
    public:
        MainWindow(GtkBuilder &builder);
        void insert_line();
        void redraw(cairo_t* cr);

    private:
        cairo_surface_t* surface;
        GtkBuilder* gtkBuilder;
        GtkWidget* _window;
        GtkWidget* _draw_area;
        ViewPort* _viewport;
        LinkedList<Object*> _display_file;
};

#endif // MAIN_WINDOW_HPP
