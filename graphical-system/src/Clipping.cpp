#include "Clipping.hpp"


/**
 * Applies the right clipping algorithm for all the elementos of a given
 * display file, returning a new one with the clipped objects.
 */
void Clipper::apply_clipping(DisplayFile& original_df, DisplayFile& clipped)
{
    clipped.clear();

    for(auto i = original_df.begin(); i != original_df.end(); ++i)
        switch((*i).type()) {
            case POINT:
            {
                Object* obj = &(*i);
                Point* point = (Point*) obj;
                clipped.push_back(clip_2d_point(*point));
                break;
            }
            case LINE:
            {
                Object* obj = &(*i);
                Line* line = (Line*) obj;
                clipped.push_back(clip_2d_line(*line));
                break;
            }
            case POLYGON:
            {
                Object* obj = &(*i);
                Polygon* pol = (Polygon*) obj;
                clipped.push_back(clip_2d_polygon(*pol));
                break;
            }
        }
}

/**
 * Applies the trivial algorithm of point clipping.
 */
Point Clipper::clip_2d_point(Point point)
{
   auto coord = point.world_coordinate()[0];

   if(coord.x() >= _window.get_x_min() && coord.x() <= _window.get_x_max())
       if(coord.y() >= _window.get_y_min() && coord.y() <= _window.get_y_max())
           return point;

   return Point(point.name(), POINT);
}

/**
 * Applies the line clipping algorithm, using a specific algorithm.
 */
Line Clipper::clip_2d_line(Line line, LINE_CLIPPING_METHOD method)
{
    switch(method) {
        case COHEEN_SUTHERLAND:
            return coheen_sutherland(line);
        case LIANG_BARSKY:
            return liang_barsky(line);
    }
}

Polygon Clipper::clip_2d_polygon(Polygon polygon)
{

}


/**
 * Applies the Coheen-Sutherland algorithm for line clipping.
 */
Line Clipper::coheen_sutherland(Line line)
{
    Line clipped = Line(line.name(), LINE);
    clipped.add_coordinates(line.world_coordinate()[0], WORLD);
    clipped.add_coordinates(line.world_coordinate()[1], WORLD);

    auto x1 = clipped.world_coordinate()[0].x();
    auto y1 = clipped.world_coordinate()[0].y();
    auto x2 = clipped.world_coordinate()[1].x();
    auto y2 = clipped.world_coordinate()[1].y();

    float m = (y2 - y1)/(x2 - x1);
    float x, y;

    while(true) {
        auto region_p1 = get_region_code(clipped.world_coordinate()[0]);
        auto region_p2 = get_region_code(clipped.world_coordinate()[1]);

        if ((region_p1 & region_p2) != 0) {
            return Line(line.name(), LINE);
        } else if (region_p1 == 0 && region_p2 == 0) {
            return clipped;
        } else {
            auto out = region_p1;

            if (region_p2 != 0) {
                out = region_p2;
            }


            if (out & C_LEFT) {
                x = _window.get_x_min();
                y = m * (_window.get_x_min() - x1) + y1;
            } else if (out & C_RIGHT) {
                x = _window.get_x_max();
                y = m * (_window.get_x_max() - x1) + y1;
            } else if (out & C_TOP) {
                x = x1 + 1/m * (_window.get_y_max() - y1);
                y = _window.get_y_max();
            } else if (out & C_BOTTOM) {
                x = x1 + 1/m * (_window.get_y_min() - y1);
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

/**
 * Applies the Liang-Barsky algorithm for line clipping.
 * (Liang, Y. D. and Barsky, B., "A New Concept and Method for Line Clipping",
 *  January 1984.)
 */
Line Clipper::liang_barsky(Line line)
{
    Line clipped = Line(line.name(), LINE);
    auto coord_1 = line.world_coordinate()[0];
    auto coord_2 = line.world_coordinate()[1];
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

    clipped.add_coordinates({coord_1, coord_2}, WORLD);
    return clipped;
}

REGION_CODE Clipper::get_region_code(Coordinate coord)
{
    auto x = coord.x();
    auto y = coord.y();

    auto code = C_INSIDE;

    if (x < _window.get_x_min()) {
        code = C_LEFT;
    } else if (x > _window.get_x_max()) {
        code = C_RIGHT;
    }

    if (y < _window.get_y_min()) {
        code = C_BOTTOM;
    } else if (y > _window.get_y_max()) {
        code = C_TOP;
    }

    return code;
}
