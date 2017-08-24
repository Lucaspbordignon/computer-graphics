#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include <gtk/gtk.h>
#include <list>
#include <cmath>
#include "Object.hpp"
#include "Frame.hpp"


class ViewPort: public Frame
{
    public:
        ViewPort(float x_min, float y_min, float x_max, float y_max):
            Frame::Frame(x_min, y_min, x_max, y_max),
            _window(0, 0, x_max, y_max) {}
        void draw_all_objects(cairo_t* cr, const std::list<Object*>&);
        void draw_object(Object* object, cairo_t* cr);
        void zoom_in();
        void zoom_out();
        void move(DIRECTION direction, float step_size);
        Coordinate viewport_transform(Coordinate& coord);
        float window_center_x();
        float window_center_y();

    private:
        void draw_line(Object* object, cairo_t* cr);
        void draw_polygon(Object* object, cairo_t* cr);
        void draw_point(Object* object, cairo_t* cr);
        Frame _window;
};

#endif // VIEWPORT_HPP
