#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include <gtk/gtk.h>
#include <list>
#include <cmath>
#include "Object.hpp"
#include "Frame.hpp"
#include "DisplayFile.hpp"


class ViewPort
{
    public:
        ViewPort(float x_min, float y_min, float x_max, float y_max);
        ~ViewPort() {}
        Frame* window();
        void draw_all_objects(cairo_t* cr, const DisplayFile&);
        void draw_object(Object object, cairo_t* cr);
        void zoom(ZOOM_TYPE, float);
        void move(DIRECTION direction, float step_size);
        Coordinate viewport_transform(Coordinate& coord);
        float window_center_x();
        float window_center_y();

    private:
        void draw_line(Object* object, cairo_t* cr);
        void draw_polygon(Object* object, cairo_t* cr);
        void draw_point(Object* object, cairo_t* cr);
        void draw_window_border(Frame*, cairo_t*);
        Frame _window;
        float _x_min, _y_min, _x_max, _y_max;
};

#endif // VIEWPORT_HPP
