#include "ViewPort.hpp"

void ViewPort::draw_all_objects(cairo_t* cr, LinkedList<Object*>* display_file)
{
    /* Only as a debug */
    cairo_move_to(cr, 100, 100);
    cairo_line_to(cr, 300, 300); 
    cairo_stroke(cr);

    if(display_file->empty())
        return;

    for(auto i = 0; i < display_file->size(); ++i) {
        Object* object = display_file->at(i);
        draw_object(object, cr);
    }
}

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

void ViewPort::draw_line(Object* object, cairo_t* cr)
{
    auto coordinates = object->coordinate();
    cairo_move_to(cr, 100, 100);
    cairo_line_to(cr, 300, 300); 
    cairo_stroke(cr);
}

void ViewPort::draw_polygon(Object* object, cairo_t* cr)
{}

void ViewPort::draw_point(Object* object, cairo_t* cr)
{}
