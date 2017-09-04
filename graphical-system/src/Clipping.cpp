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

/**
 * Applies the Liang-Barsky algorithm for line clipping.
 * (Liang, Y. D. and Barsky, B., "A New Concept and Method for Line Clipping",
 *  January 1984.)
 */
std::vector<Coordinate> Clipper::liang_barsky(Line* line)
{
    auto coord_1 = line->world_coordinate()[0];
    auto coord_2 = line->world_coordinate()[1];
    auto r_zeta_1 = std::vector<float>();
    auto r_zeta_2 = std::vector<float>();

    std::vector<float> p = {
        -(coord_2.x() - coord_1.x()),
         (coord_2.x() - coord_1.x()),
        -(coord_2.y() - coord_1.y()),
         (coord_2.y() - coord_1.y())
    };

    std::vector<float> q = {
        coord_1.x() - _window.get_x_min(),
        _window.get_x_max() - coord_1.x(),
        coord_1.y() - _window.get_y_min(),
        _window.get_y_max() - coord_1.y()
    };


    for(auto i = 0; i < p.size(); ++i){
        if(p[i] < 0)
            r_zeta_1.push_back(q[i] / p[i]);
        else if (p[i] > 0)
            r_zeta_2.push_back(q[i] / p[i]);
    }

    /* Zeta 1 */
    auto max_r = *std::max_element(r_zeta_1.begin(), r_zeta_1.end());
    auto zeta_1 = std::max((float)0, max_r);

    if (zeta_1 > 0)
        coord_1 = Coordinate(
                    coord_1.x() + (zeta_1 * p[1]),
                    coord_1.y() + (zeta_1 * p[3]));

    /* Zeta 2 */
    auto min_r = *std::min_element(r_zeta_2.begin(), r_zeta_2.end());
    auto zeta_2 = std::min((float)1, min_r);
    
    if (zeta_2 < 1)
        coord_2 = Coordinate(
                    coord_2.x() + (zeta_2 * p[0]),
                    coord_2.y() + (zeta_2 * p[2]));

    return {coord_1, coord_2};
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
