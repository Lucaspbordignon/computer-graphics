#ifndef UTILS_HPP
#define UTILS_HPP

#include <list>
#include <iostream>
#include "Object.hpp"
#include "ViewPort.hpp"

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

ViewPort* _viewport;
std::list<Object*> _display_file;
std::vector<Coordinate> _coordinates_storage;


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

        /* Returning TRUE to avoide another call of the function */
        return TRUE;
    }

    gboolean draw(GtkWidget* widget, cairo_t* cr)
    {
        /* Redraw a cairo context */
        _viewport->draw_all_objects(cr, _display_file);
        return FALSE;
    }

    void add_coordinate()
    {
        auto x = gtk_spin_button_get_value(_new_obj_x);
        auto y = gtk_spin_button_get_value(_new_obj_y);
        auto coord = Coordinate(x, y);
    
        _coordinates_storage.push_back(coord);
        print("Coordinate saved.\n");
    }

    void add_line(std::string name)
    {
        /* Inserts a line to the display file */
        auto line = new Line(name, LINE);
        line->add_coordinates(_coordinates_storage);
        _display_file.push_back(line);
    }

    void add_polygon(std::string name)
    {
        /* Inserts a polygon to the display file */
        auto polygon = new Polygon(name, POLYGON);
        polygon->add_coordinates(_coordinates_storage);
        _display_file.push_back(polygon);
    }

    void add_point(std::string name)
    {
        /* Inserts a point to the display file */
        auto point = new Point(name, POINT);
        point->add_coordinates(_coordinates_storage[0]);
        _display_file.push_back(point);
    }

    void zoom_in()
    {
        _viewport->zoom_in();
        gtk_widget_queue_draw(_draw_area);
    }

    void zoom_out()
    {
        _viewport->zoom_out();
        gtk_widget_queue_draw(_draw_area);
    }

    void move_up()
    {
        auto value = gtk_spin_button_get_value(_step_size);
        _viewport->move(UP, value);
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

    void create_object_button(GtkButton* button, GtkEntry* obj_name)
    {
        auto name = gtk_entry_get_text(obj_name);

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
        print("Object with created and added to display file.\n");
    }
}

#endif // UTILS_HPP
