#include "Object.hpp"

void Object::add_coordinates(float x, float y, COORDINATE_TYPE type)
{
    if(type == WINDOW)
        return _window_coordinates.push_back(Coordinate(x, y));
    _world_coordinates.push_back(Coordinate(x, y));

}

void Object::add_coordinates(Coordinate coord, COORDINATE_TYPE type) 
{
    if(type == WINDOW)
        return _window_coordinates.push_back(coord);
    _world_coordinates.push_back(coord);
}

void Object::add_coordinates(std::vector<Coordinate> coord, COORDINATE_TYPE type)
{
    if(type == WINDOW){
        _window_coordinates = coord;
        return;
    }
    _world_coordinates = coord;
}
        
void Object::update_coordinate(Coordinate coord, int pos)
{
    _world_coordinates[pos] = coord;
}

Coordinate Object::center_point()
{
    auto n = _world_coordinates.size();
    float sum_x = 0;
    float sum_y = 0;

    for (auto i = 0u; i < n; ++i) {
        sum_x += _world_coordinates[i].x();
        sum_y += _world_coordinates[i].y();
    }
    return Coordinate((sum_x / n), (sum_y / n));
}

/**
 * Given a curve, returns a vector with all the small segmentes needed to draw
 * it on the viewport.
 */
std::vector<Line*> Curve::get_segments()
{
    if (_segments.empty())
        _segments = generate_segments();

    return _segments;
}

void Curve::set_segments(std::vector<Line*> segments)
{
    _segments = segments;
}

/**
 * Generates all the segments using blending functions (iterative method)
 */
std::vector<Line*> Curve::generate_segments()
{
    std::vector<Line*> segments;
    auto num_control_points = world_coordinate().size();

    for (auto index = 0; (index + 3) < num_control_points; ++index) {
        for (auto t = 1e-3; t < 1; t += _step) {
            Coordinate p1 = get_point(t, index);
            Coordinate p2 = get_point(t + _step, index);

            auto line = new Line("Curve segment", LINE);
            line->add_coordinates({p1, p2}, WORLD);
            segments.push_back(line);
        }
    }

    return segments;
}

/**
 * Gets a point of the bezier curve based on 4 control points.
 */
Coordinate Bezier::get_point(float t, int i)
{
    auto p = world_coordinate();
    auto x = bezier(t, p[i].x(), p[i + 1].x(), p[i + 2].x(), p[i + 3].x());
    auto y = bezier(t, p[i].y(), p[i + 1].y(), p[i + 2].y(), p[i + 3].y());
    return Coordinate(x, y);
}

/**
 * Applies the Bezier polynomial to find the coordinate of a curve.
 */
float Bezier::bezier(float t, float p1n, float p2n, float p3n, float p4n)
{
    float t3 = pow(t, 3);
    float t2 = pow(t, 2);

    return (t3 * (-1 * p1n + 3 * p2n - 3 * p3n + p4n)) + 
           (t2 * (3 * p1n - 6 * p2n + 3 * p3n)) +
           (t * (-3 * p1n + 3 * p2n)) +
           (p1n);
}

/**
 * Gets a point of the B-Spline curve based on 4 control points.
 */
Coordinate Spline::get_point(float t, int i)
{
    auto p = world_coordinate();
    auto x = spline(t, p[i].x(), p[i + 1].x(), p[i + 2].x(), p[i + 3].x());
    auto y = spline(t, p[i].y(), p[i + 1].y(), p[i + 2].y(), p[i + 3].y());
    return Coordinate(x, y);
}

/**
 * Applies the B-Spline polynomial to find the coordinate of a curve.
 */
float Spline::spline(float t, float p1n, float p2n, float p3n, float p4n)
{
    float t3 = pow(t, 3);
    float t2 = pow(t, 2);
    
    return ((t3 * (-1 * p1n + 3 * p2n - 3 * p3n + p4n)) + 
           (t2 * (3 * p1n - 6 * p2n + 3 * p3n)) +
           (t * (-3 * p1n + 3 * p3n)) +
           (1 * (p1n + 4 * p2n + p3n))) / 6;
}
