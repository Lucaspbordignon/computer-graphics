#ifndef UTILS_HPP
#define UTILS_HPP

#include <list>
#include <cstring>
#include <gtk/gtk.h>
#include "Object.hpp"
#include "ViewPort.hpp"
#include "Transform.hpp"
#include "Clipping.hpp"

#define GUI_FILE "graphical_system.glade"


/* Global Variables */
static cairo_surface_t* surface = NULL;
GtkBuilder* builder;
GtkWidget* _window;
GtkWidget* _draw_area;
GtkTextView* _text_view;
GtkSpinButton* _new_obj_x;
GtkSpinButton* _new_obj_y;

/* Zoom buttons */
GtkButton* _zoom_in_btn;
GtkButton* _zoom_out_btn;

/* Move buttons */
GtkButton* _move_up_btn;
GtkButton* _move_down_btn;
GtkButton* _move_left_btn;
GtkButton* _move_right_btn;
GtkSpinButton* _step_size;

/* Visualization Lists */
GtkTreeView* _obj_name_view;
GtkTreeView* _obj_coord_view;
GtkListStore* _name_list;
GtkListStore* _coord_list;

/* Display widgets */
ViewPort* _viewport;
DisplayFile _display_file;
DisplayFile _clipped_objects;
std::vector<Coordinate> _coordinates_storage;
Clipper _clipper;


/**
 * Prints a message on the GUI console.
 */
void print(const char* message)
{
    GtkTextIter end;
    auto buffer = gtk_text_view_get_buffer(_text_view);
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_insert(buffer, &end, message, -1);
}


/* Callbacks */
extern "C" {

    void close_window()
    {
        /* Close the interface window */
        gtk_main_quit();
    }
    
    gboolean configure_event(GtkWidget* widget)
    {
        /* Creates a new surface */
        if(surface)
            cairo_surface_destroy(surface);

        surface = gdk_window_create_similar_surface (
                                        gtk_widget_get_window(widget),
                                        CAIRO_CONTENT_COLOR,
                                        gtk_widget_get_allocated_width(widget),
                                        gtk_widget_get_allocated_height(widget)
                                        );

        /* Creates a cairo context over the surface */
        cairo_t *cr = cairo_create(surface);
        cairo_paint(cr);
        cairo_destroy(cr);

        /* Returning TRUE to avoid another call of the function */
        return TRUE;
    }

    gboolean draw(GtkWidget* widget, cairo_t* cr)
    {
        /* Redraw a cairo context */
        if(_display_file.size()) {

            // TODO: Doing a test actually

            _clipper.apply_clipping(_display_file, _clipped_objects);
            normalize_coordinates(*(_viewport->window()), _clipped_objects);
            _viewport->draw_all_objects(cr, _clipped_objects);
        } else {
            normalize_coordinates(*(_viewport->window()), _display_file);
            _viewport->draw_all_objects(cr, _display_file);
        }
        return FALSE;
    }

    void add_coordinate()
    {
        auto x = gtk_spin_button_get_value(_new_obj_x);
        auto y = gtk_spin_button_get_value(_new_obj_y);
        auto coord = Coordinate(x, y);

        _coordinates_storage.push_back(coord);

        /* Creates a new entry on the tree view */
        GtkTreeIter it;
        gtk_list_store_append(_coord_list, &it);
        gtk_list_store_set(_coord_list, &it, 0, x, 1, y, -1);
    }

    void add_line(std::string name)
    {
        /* Inserts a line to the display file */
        auto line = new Line(name, LINE);
        line->add_coordinates(_coordinates_storage, WORLD);
        _display_file.push_back(line);

        /* Add the element to the list store */
        char aux[1024];
        strcpy(aux, name.c_str());
        GtkTreeIter it;
        gtk_list_store_append(_name_list, &it);
        gtk_list_store_set(_name_list, &it, 0, aux, 1, "LINE", -1);
    }

    void add_polygon(std::string name)
    {
        /* Inserts a polygon to the display file */
        auto polygon = new Polygon(name, POLYGON);
        polygon->add_coordinates(_coordinates_storage, WORLD);
        _display_file.push_back(polygon);
        
        /* Add the element to the list store */
        char aux[1024];
        strcpy(aux, name.c_str());
        GtkTreeIter it;
        gtk_list_store_append(_name_list, &it);
        gtk_list_store_set(_name_list, &it, 0, aux, 1, "POLYGON", -1);
    }

    void add_point(std::string name)
    {
        /* Inserts a point to the display file */
        auto point = new Point(name, POINT);
        point->add_coordinates(_coordinates_storage[0], WORLD);
        _display_file.push_back(point);

        /* Add the element to the list store */
        char aux[1024];
        strcpy(aux, name.c_str());
        GtkTreeIter it;
        gtk_list_store_append(_name_list, &it);
        gtk_list_store_set(_name_list, &it, 0, aux, 1, "POINT", -1);
    }

    void create_object_button(GtkButton* button, GtkEntry* obj_name)
    {
        auto name = gtk_entry_get_text(obj_name);
        if (name[0] == '\0') {
            print("Object not added. Insert a name to it!\n");
            return;
        }

        /* Detects the number of points and add it */
        switch(_coordinates_storage.size())
        {
            case 0:
                break;
            case 1:
                add_point(name);
                break;
            case 2:
                add_line(name);
                break;
            default:
                add_polygon(name);
                break;
        }

        /* Invalidates the actual draw to update the draw area */
        gtk_widget_queue_draw(_draw_area);
        _coordinates_storage.clear();
        gtk_list_store_clear(_coord_list);
        print("Object with created and added to display file.\n");
    }

    void zoom_in()
    {
        _viewport->zoom(IN, gtk_spin_button_get_value(_step_size));
        gtk_widget_queue_draw(_draw_area);
    }

    void zoom_out()
    {
        _viewport->zoom(OUT, gtk_spin_button_get_value(_step_size));
        gtk_widget_queue_draw(_draw_area);
    }

    void move_up()
    {
        _viewport->move(UP, gtk_spin_button_get_value(_step_size));
        gtk_widget_queue_draw(_draw_area);
    }

    void move_down()
    {
        _viewport->move(DOWN, gtk_spin_button_get_value(_step_size));
        gtk_widget_queue_draw(_draw_area);
    }

    void move_left()
    {
        _viewport->move(LEFT, gtk_spin_button_get_value(_step_size));
        gtk_widget_queue_draw(_draw_area);
    }

    void move_right()
    {
        _viewport->move(RIGHT, gtk_spin_button_get_value(_step_size));
        gtk_widget_queue_draw(_draw_area);
    }

    void transformation_dialog()
    {  
        GtkTreeModel* model;
        GtkTreeIter it;

        GtkTreeSelection* selection = gtk_tree_view_get_selection(_obj_name_view);
        if (gtk_tree_selection_get_selected(selection, &model, &it)) {
            auto transf_dialog = (GtkDialog*)gtk_builder_get_object(
                                    GTK_BUILDER(builder),
                                    "transformation_dialog");
            gtk_dialog_run(GTK_DIALOG(transf_dialog));
        } else {
            print("Object not selected. Select one to apply the transform!\n");
        }

    }

    void apply_transformation(GtkButton* btn, GtkWidget* widget)
    {
        GtkTreeModel* model;
        GtkTreeIter it;
        Object* obj;
        float x, y, ang;

        /* Gets the object to be transformed */
        GtkTreeSelection* selection = gtk_tree_view_get_selection(_obj_name_view);
        if (gtk_tree_selection_get_selected(selection, &model, &it)) {
            gchar *name;
            gtk_tree_model_get(model, &it, 0, &name, -1);

            // Get the object to be called
            obj = _display_file.get_object(name);
        }

        /* Gets the transformation options */
        GtkComboBoxText* combo_box = (GtkComboBoxText*)gtk_builder_get_object(
                                        GTK_BUILDER(builder),
                                        "transf_select");

        /* Gets the displacement data */
        auto transf_x = (GtkSpinButton*)gtk_builder_get_object(
                                        GTK_BUILDER(builder),
                                        "transf_x_coord");
        auto transf_y = (GtkSpinButton*)gtk_builder_get_object(
                                        GTK_BUILDER(builder),
                                        "transf_y_coord");
        auto transf_ang = (GtkSpinButton*)gtk_builder_get_object(
                                        GTK_BUILDER(builder),
                                        "transf_angle");
        x = gtk_spin_button_get_value(transf_x);
        y = gtk_spin_button_get_value(transf_y);
        ang = gtk_spin_button_get_value(transf_ang);

        auto selected = gtk_combo_box_text_get_active_text(combo_box);
        if(!strncmp(selected, "Rotate from origin", 24)){
            rotate_2d_object(obj, ang, 0, 0);
        } else if(!strncmp(selected, "Rotate from world center", 24)){
            x = _viewport->window_center_x(); 
            y = _viewport->window_center_y(); 
            rotate_2d_object(obj, ang, x, y);
        } else if(!strncmp(selected, "Rotate from coordinates", 24)){
            rotate_2d_object(obj, ang, x, y);
        } else if(!strncmp(selected, "Scaling", 8)){
            scale_2d_object(obj, x, y);
        } else if (!strncmp(selected, "Translation", 12)){
            translation_2d_object(obj, x, y);
        }

        /* Redraw and close popup */
        gtk_widget_queue_draw(_draw_area);
        gtk_widget_hide(widget);
    }

    void rotate_window(GtkButton* btn, GtkSpinButton* ang_button)
    {
        /* Set a specific angle to the window */
        auto ang = gtk_spin_button_get_value(ang_button);
        _viewport->window()->rotate(ang);
        gtk_widget_queue_draw(_draw_area);
    }
}

#endif // UTILS_HPP
