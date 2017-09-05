#include "Clipping.hpp"

REGION_CODE Clipper::get_region_code(Coordinate coord)
{
    auto x = coord.x();
    auto y = coord.y();

    REGION_CODE code = INSIDE;

    if (x < _window.get_x_min()) {
        code = LEFT;
    } else if (x > _window.get_x_max()) {
        code = RIGHT;
    }

    if (y < _window.get_y_min()) {
        code = BOTTOM;
    } else if (y > _window.get_y_max()) {
        code = TOP;
    }

    return code;
}

Line* Clipper::coheen_sutherland(Line* line)
{
    Line clipped = Line(line->name(), LINE);
    clipped.add_coordinates(line->world_coordinate()[0]);
    clipped.add_coordinates(line->world_coordinate()[1]);
    while(true) {
        auto region_p1 = get_region_code(clipped.world_coordinate()[0]);
        auto region_p2 = get_region_code(clipped.world_coordinate()[1]);

        float x1 = clipped->world_coordinate()[0].x();
        float y1 = clipped->world_coordinate()[0].y();
        float x2 = clipped->world_coordinate()[1].x();
        float y2 = clipped->world_coordinate()[1].y();

        if (region_p1 | region_p2 == 0) {
            return &clipped;
        } else if (region_p1 & region_p2 != 0) {
            return 0;
        } else {
            auto out = region_p1;

            if (region_p2 != 0) {
                out = region_p2;
            }

            float m = (y2 - y1)/(x2 - x1);
            float x, y;

            if (out & LEFT) {
                x = _window.get_x_min();
                y = m * (_window.get_x_min() - x1) + y1;
            } else if (out & RIGHT) {
                x = _window.get_x_max();
                y = m * (_window.get_x_max() - x1) + y1;
            } else if (out & TOP) {
                x = x1 + 1/(m * (_window.get_y_max() - y1));
                y = _window.get_y_max();
            } else if (out & BOTTOM) {
                x = x1 + 1/(m * (_window.get_y_min() - y1));
                y = _window.get_y_min();
            }

            Coordinate coord = Coordinate(x, y);

            if (out == region_p1) {
                clipped.update_coordinate(coord, 0);
            } else {
                clipped.update_coordinate(coord, 1);
            }
        }
    }
}

Line* Clipper::clip_2d_line(Line* line, LINE_CLIPPING_METHOD method)
{
    switch(method) {
        case COHEEN_SUTHERLAND:
            return coheen_sutherland(line);
        case LIANG_BARSKY:
            return liang_barsky(line);
        default:
            return coheen_sutherland(line);
    }
}