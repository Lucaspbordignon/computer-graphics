#include <gtk/gtk.h>
#include "Utils.hpp"


int main(int argc, char** argv)
{

    /* Starts the application */
    gtk_init(&argc, &argv);
    
    builder = gtk_builder_new();

    /* Adding glade file */
    gtk_builder_add_from_file(builder, GUI_FILE, NULL);
    
    /* Creates and connects the widgets to the main window */
    _window = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(builder), "main_window"));
    _draw_area = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(builder), "draw_area"));

    /* Initialize the buttons and lists to capture coordinates */
    _new_obj_x = (GtkSpinButton*)gtk_builder_get_object(GTK_BUILDER(builder), "obj_x");
    _new_obj_y = (GtkSpinButton*)gtk_builder_get_object(GTK_BUILDER(builder), "obj_y"); 
    _zoom_in_btn = (GtkButton*)gtk_builder_get_object(GTK_BUILDER(builder), "zoom_in");
    _zoom_out_btn = (GtkButton*)gtk_builder_get_object(GTK_BUILDER(builder), "zoom_out");

    _viewport = new ViewPort(0, 0, 500, 500);

    /* List of the world objects */
    _display_file = std::list<Object*>();

    /* Initializes the text viewer */
    _text_view = (GtkTextView*)gtk_builder_get_object(GTK_BUILDER(builder), "log_box");
    gtk_builder_connect_signals(GTK_BUILDER(builder), NULL);
    gtk_widget_show_all(_window);

    gtk_main();

    return 0;
}

