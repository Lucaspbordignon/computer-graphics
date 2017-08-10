#include "ViewPort.hpp"


/**
 * Draws all the objects of a display file on a drawing area. The display file
 * is a linked list.
 */
void ViewPort::draw_all_objects(cairo_t* cr, const std::list<Object*>& display_file)
{
    if(display_file.empty())
        return;

    for(auto i = display_file.begin(); i != display_file.end(); ++i)
        draw_object(*i, cr);
}

/**
 * Draw a given object, applying the right method based on the type of
 * the object.
 */
void ViewPort::draw_object(Object* object, cairo_t* cr)
{
    switch(object->type())
    {
        case LINE:
            draw_line(object, cr);
            break;
        case POLYGON:
            draw_polygon(object, cr);
            break;
        case POINT:
            draw_point(object, cr);
            break;
    }
}

/**
 * Applies a viewport transformation on a give pair of coordinates
 */
Coordinate ViewPort::viewport_transform(Coordinate& coord)
{
    auto width = _x_max - _x_min;
    auto height = _y_max - _y_min;

    auto x_vp = ((coord.x() - _window.get_x_min()) / (_window.get_x_max() - _window.get_x_min())) * width;
    auto y_vp = (1 - (coord.y() - _window.get_y_min()) / (_window.get_y_max() - _window.get_y_min())) * height;
    return Coordinate(x_vp, y_vp);
}

/**
 * Given an object of type line, collects the coordinates and print it on the
 * viewport.
 */
void ViewPort::draw_line(Object* object, cairo_t* cr)
{
    auto coordinates = object->coordinate();
    Coordinate first_coord = coordinates[0];
    Coordinate second_coord = coordinates[1];

    cairo_move_to(cr, first_coord.x(), first_coord.y());
    cairo_line_to(cr, second_coord.x(), second_coord.y()); 
    cairo_stroke(cr);
}

/*
 * Given an object of type polygon, take the coordinates, and draw the a
 * polygon on the viewport.
 */
void ViewPort::draw_polygon(Object* object, cairo_t* cr)
{
    auto coordinates = object->coordinate();
    Coordinate first_coord = coordinates[0];

    cairo_move_to(cr, first_coord.x(), first_coord.y());
    for (auto i = 0u; i < coordinates.size(); ++i) {
        auto actual_coord = coordinates[i];
        cairo_line_to(cr, actual_coord.x(), actual_coord.y());
    }
    
    cairo_close_path(cr);
    cairo_stroke(cr);
}

/*
 * Given an object of type point, take a coordinate, draw a small circle around
 * it, a shows it on the viewport.
 */
void ViewPort::draw_point(Object* object, cairo_t* cr)
{
    auto coordinates = object->coordinate();
    Coordinate first_coord = coordinates[0];

    cairo_arc(cr, first_coord.x(), first_coord.y(), 3, 0, 2*M_PI);
    cairo_fill(cr);
}