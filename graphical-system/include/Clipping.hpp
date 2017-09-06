#ifndef CLIPPING_HPP
#define CLIPPING_HPP

#include <algorithm>
#include "DisplayFile.hpp"
#include "Frame.hpp"

enum LINE_CLIPPING_METHOD
{
    COHEEN_SUTHERLAND,
    LIANG_BARSKY
};

enum REGION_CODE
{
    C_INSIDE = 0,
    C_LEFT = 1,
    C_RIGHT = 2,
    C_BOTTOM = 4,
    C_TOP = 8
};

class Clipper
{
    public:
        Clipper(Frame window) : _window(window) {};
        Clipper() {};

        void apply_clipping(DisplayFile&, DisplayFile&);
        Point clip_2d_point(Point* point);
        Line clip_2d_line(Line* line, LINE_CLIPPING_METHOD method = LIANG_BARSKY);
        Polygon clip_2d_polygon(Polygon* polygon);

    private:
        Frame _window;
        Line coheen_sutherland(Line* line);
        Line liang_barsky(Line* line);
        REGION_CODE get_region_code(Coordinate coord);
};

#endif // CLIPPING_HPP
