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
    _viewport = new ViewPort(gtk_widget_get_allocated_width(_draw_area),
                            gtk_widget_get_allocated_height(_draw_area)); 

    /* List of the world objects */
    _display_file = LinkedList<Object*>();

    gtk_builder_connect_signals(gtkBuilder, _draw_area);
    gtk_widget_show_all(_window);
}

void MainWindow::insert_line()
{
    _display_file.push_back(new Object("Linha", LINE, 100, 100));
}

void MainWindow::redraw(cairo_t* cr)
{
    _viewport->draw_all_objects(cr, &_display_file);
}
