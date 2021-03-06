#include "ViewPort.hpp"

ViewPort::ViewPort(float x_min, float y_min, float x_max, float y_max, float w_ratio)
{
    _x_min = x_min;
    _y_min = y_min;
    _x_max = x_max;
    _y_max = y_max;
    _window_ratio = w_ratio;

    _window = Frame(x_min + w_ratio, y_min + w_ratio,
                    x_max - w_ratio, y_max - w_ratio);
}

Frame ViewPort::window()
{
    return _window;
}

Frame* ViewPort::window_ptr()
{
    return &_window;
}

/**
 * Draws all the objects of a display file on a drawing area. The display file
 * is a linked list.
 */
void ViewPort::draw_all_objects(cairo_t* cr, const DisplayFile& display_file)
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
        case CURVE:
            draw_curve((Curve*)object, cr);
            break;
    }
}

/**
 * Applies a viewport transformation on a give pair of coordinates
 */
Coordinate ViewPort::viewport_transform(Coordinate& coord)
{
    auto width = _window.get_x_max() - _window.get_x_min();
    auto height = _window.get_y_max() - _window.get_y_min();

    /* Normalized transformation */
    auto x_vp = ((coord.x() - (-1)) / (1 - (-1))) * width;
    auto y_vp = (1 - (coord.y() - (-1)) / (1 - (-1))) * height;

    return Coordinate(x_vp + _window_ratio, y_vp + _window_ratio);
}

/**
 * Given an object of type line, collects the coordinates and print it on the
 * viewport.
 */
void ViewPort::draw_line(Object* object, cairo_t* cr)
{
    auto coordinates = object->window_coordinate();
    if (coordinates.size()) {
        Coordinate first_coord = viewport_transform(coordinates[0]);
        Coordinate second_coord = viewport_transform(coordinates[1]);

        cairo_move_to(cr, first_coord.x(), first_coord.y());
        cairo_line_to(cr, second_coord.x(), second_coord.y()); 
        cairo_stroke(cr);
    }
}

/**
 * Given an object of type polygon, take the coordinates, and draw the a
 * polygon on the viewport.
 */
void ViewPort::draw_polygon(Object* object, cairo_t* cr)
{
    auto coordinates = object->window_coordinate();
    if (coordinates.size()) {
        Coordinate first_coord = viewport_transform(coordinates[0]);

        cairo_move_to(cr, first_coord.x(), first_coord.y());
        for (auto i = 0u; i < coordinates.size(); ++i) {
            auto actual_coord = viewport_transform(coordinates[i]);
            cairo_line_to(cr, actual_coord.x(), actual_coord.y());
        }
        
        cairo_close_path(cr);
        cairo_stroke(cr);
    }
}

/**
 * Given an object of type point, take a coordinate, draw a small circle around
 * it, a shows it on the viewport.
 */
void ViewPort::draw_point(Object* object, cairo_t* cr)
{
    auto coordinates = object->window_coordinate();
    if (coordinates.size()) {
        Coordinate first_coord = viewport_transform(coordinates[0]);

        cairo_arc(cr, first_coord.x(), first_coord.y(), 3, 0, 2*M_PI);
        cairo_fill(cr);
    }
}

/**
 * Draw a Cubic Bezier Curve and shows it on the viewport. Using a variation
 * of 1e-3 from each line drawn.
 */
void ViewPort::draw_curve(Curve* object, cairo_t* cr)
{
    for (Line* line : object->get_segments()) {
        draw_line(line, cr);
    }
}

/**
 * Given a obejct of Frame, i.e. a window of the system, draws a border
 * arround the object.
 */
void ViewPort::draw_window_border(cairo_t* cr)
{
    auto x_min = _x_min + _window_ratio;
    auto y_min = _y_min + _window_ratio;
    auto x_max = _x_max - _window_ratio;
    auto y_max = _y_max - _window_ratio;
    
    cairo_move_to(cr, x_min, y_min);
    cairo_line_to(cr, x_max, y_min);
    cairo_line_to(cr, x_max, y_max);
    cairo_line_to(cr, x_min, y_max);
    cairo_line_to(cr, x_min, y_min);
    cairo_stroke(cr);
}

/**
 * Applies a zoom in or out at a given ratio.
 */
void ViewPort::zoom(ZOOM_TYPE type, float step_size)
{
    switch(type) {
        case IN:
            step_size = 1 - (step_size / 1000);
            _window.set_x_max(_window.get_x_max() * step_size);
            _window.set_x_min(_window.get_x_min() * step_size);
            _window.set_y_max(_window.get_y_max() * step_size);
            _window.set_y_min(_window.get_y_min() * step_size);
            break;
        case OUT:
            step_size = 1 + (step_size / 1000);
            _window.set_x_max(_window.get_x_max() * step_size);
            _window.set_x_min(_window.get_x_min() * step_size);
            _window.set_y_max(_window.get_y_max() * step_size);
            _window.set_y_min(_window.get_y_min() * step_size);
            break;
    }
}

void ViewPort::move(DIRECTION direction, float step_size)
{
    switch (direction) {
        case UP:
            _window.set_y_max(_window.get_y_max() + step_size);
            _window.set_y_min(_window.get_y_min() + step_size);
            break;
        case DOWN:
            _window.set_y_max(_window.get_y_max() - step_size);
            _window.set_y_min(_window.get_y_min() - step_size);
            break;
        case LEFT:
            _window.set_x_max(_window.get_x_max() - step_size);
            _window.set_x_min(_window.get_x_min() - step_size);
            break;
        case RIGHT:
            _window.set_x_max(_window.get_x_max() + step_size);
            _window.set_x_min(_window.get_x_min() + step_size);
            break;
    }
}

/**
 * Returns the postion, at the x axis, of the center of the window.
 */
float ViewPort::window_center_x()
{
    return _window.x_center();
}

/**
 * Returns the postion, at the y axis, of the center of the window.
 */
float ViewPort::window_center_y()
{
    return _window.y_center();
}
