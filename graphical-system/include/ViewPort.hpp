#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include <gtk/gtk.h>
#include "Objects.hpp"
#include "LinkedList.hpp"

using namespace structures;

class ViewPort
{
    public:
        ViewPort(float width, float height):
            _width(width),
            _height(height) {}
        ~ViewPort() {}
        void draw_all_objects(cairo_t* cr, LinkedList<Object*>*);
        void draw_object(Object* object, cairo_t* cr);

    private:
        void draw_line(Object* object, cairo_t* cr);
        void draw_polygon(Object* object, cairo_t* cr);
        void draw_point(Object* object, cairo_t* cr);
        float _width;
        float _height;
};

#endif // VIEWPORT_HPP
