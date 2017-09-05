#ifndef CLIPPING_HPP
#define CLIPPING_HPP

#include "Object.hpp"
#include "Frame.hpp"
#include <algorithm>

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
        Clipper() {};

        void clip_2d_point(Point* point);
        Line* clip_2d_line(Line* line, LINE_CLIPPING_METHOD method = COHEEN_SUTHERLAND);
        void clip_2d_polygon(Polygon* polygon);
        std::vector<Coordinate> liang_barsky(Line* line);
    private:
        Frame _window;
        Line* coheen_sutherland(Line* line);
        REGION_CODE get_region_code(Coordinate coord);
        //Line* liang_barsky(Line* line);
};

#endif // CLIPPING_HPP
