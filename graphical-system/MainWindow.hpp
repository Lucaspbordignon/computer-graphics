#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP
#define GUI_FILE "graphical_system.glade"

#include <gtk/gtk.h>

static cairo_surface_t* surface = NULL;

class MainWindow
{
    public:
        MainWindow(GtkBuilder &builder);
        void insert_point();

    private:
        cairo_surface_t* surface;
        GtkBuilder* gtkBuilder;
        GtkWidget* _window;
        GtkWidget* _draw_area;
};

#endif
