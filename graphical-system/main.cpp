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

    _move_up_btn = (GtkButton*)gtk_builder_get_object(GTK_BUILDER(builder), "move_up");
    _move_down_btn = (GtkButton*)gtk_builder_get_object(GTK_BUILDER(builder), "move_down");
    _move_left_btn = (GtkButton*)gtk_builder_get_object(GTK_BUILDER(builder), "move_left");
    _move_right_btn = (GtkButton*)gtk_builder_get_object(GTK_BUILDER(builder), "move_right");
    _step_size = (GtkSpinButton*)gtk_builder_get_object(GTK_BUILDER(builder), "step_size");

    _obj_name_view =(GtkTreeView*)gtk_builder_get_object(GTK_BUILDER(builder), "obj_name_view");
    _name_list = GTK_LIST_STORE(gtk_tree_view_get_model(_obj_name_view));
    _obj_coord_view = (GtkTreeView*)gtk_builder_get_object(GTK_BUILDER(builder), "coord_treeview");
    _coord_list = GTK_LIST_STORE(gtk_tree_view_get_model(_obj_coord_view));

    _viewport = new ViewPort(0, 0, 500, 500);

    /* List of the world objects */
    _display_file = DisplayFile();

    /* Initializes the text viewer */
    _text_view = (GtkTextView*)gtk_builder_get_object(GTK_BUILDER(builder), "log_box");
    gtk_builder_connect_signals(GTK_BUILDER(builder), NULL);
    gtk_widget_show_all(_window);

    gtk_main();
    delete _viewport;

    return 0;
}

