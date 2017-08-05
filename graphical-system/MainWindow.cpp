#include "MainWindow.hpp"
#include "Handlers.hpp"


MainWindow::MainWindow(GtkBuilder &builder)
{
    gtkBuilder = &builder;

    /* Adding glade file */
    gtk_builder_add_from_file(&builder, GUI_FILE, NULL);
    
    /* Creates and connects the widgets to the main window */
    _window = GTK_WIDGET(gtk_builder_get_object( &builder, "main_window"));
    _draw_area = GTK_WIDGET(gtk_builder_get_object( &builder, "draw_area"));

    gtk_builder_connect_signals(gtkBuilder, _draw_area);

    gtk_widget_show_all(_window);
}

void MainWindow::insert_point()
{}
