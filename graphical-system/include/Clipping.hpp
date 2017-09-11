#ifndef CLIPPING_HPP
#define CLIPPING_HPP

#include <algorithm>
#include "DisplayFile.hpp"
#include "Frame.hpp"
#include "Edge.hpp"

enum LINE_CLIPPING_METHOD
{
    COHEN_SUTHERLAND,
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

        void apply_clipping(Frame, DisplayFile&, DisplayFile&);
        Point clip_2d_point(Point point);
        Line clip_2d_line(Line line, LINE_CLIPPING_METHOD method = COHEN_SUTHERLAND);
        Polygon clip_2d_polygon(Polygon polygon);

    private:
        Frame _window;
        Line cohen_sutherland(Line line);
        Line liang_barsky(Line line);
        Polygon sutherland_hodgman(Polygon polygon);
        REGION_CODE get_region_code(Coordinate coord);
        bool is_inside(Coordinate coord, Edge edge);
};

#endif // CLIPPING_HPP
