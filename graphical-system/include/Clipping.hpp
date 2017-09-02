#ifndef CLIPPING_HPP
#define CLIPPING_HPP

#include "Object.hpp"
#include "Frame.hpp"

enum LINE_CLIPPING_METHOD
{
    COHEEN_SUTHERLAND,
    LIANG_BARSKY
};

enum REGION_CODE
{
    INSIDE = 0,
    LEFT = 1,
    RIGHT = 2,
    BOTTOM = 4,
    TOP = 8
};

class Clipper
{
    public:
        Clipper(Frame window) : _window(window) {};
        virtual Clipper() {};

        void window(Frame window) : _window(window) {}

        void clip_2d_point(Point* point);
        void clip_2d_line(Line* line, LINE_CLIPPING_METHOD method = COHEEN_SUTHERLAND);
        void clip_2d_polygon(Polygon* polygon);
    private:
        Frame _window;

        void coheen_sutherland(Line* line);
        REGION_CODE get_region_code(Coordinate coord);
        void liang_barsky(Line* line);
}

#endif // CLIPPING_HPP