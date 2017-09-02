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

void Clipper::coheen_sutherland(Line* line)
{
    auto region_p1 = get_region_code(line->world_coordinate()[0]);
    auto region_p2 = get_region_code(line->world_coordinate()[1]);

    if (region_p1 & region_p2) {
        
    }
}

void Clipper::clip_2d_line(Line* line, LINE_CLIPPING_METHOD method)
{
    switch(method) {
        case COHEEN_SUTHERLAND:
            coheen_sutherland(line);
            break;
        case LIANG_BARSKY:
            liang_barsky(line);
            break;
        default:
            coheen_sutherland(line);
            break;
    }
}