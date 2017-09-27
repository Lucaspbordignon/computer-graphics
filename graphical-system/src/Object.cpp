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

float Curve::bezier(float t, float p1n, float p2n, float p3n, float p4n)
{
    float t3 = pow(t, 3);
    float t2 = pow(t, 2);

    return (p1n * (-1 * t3 + 3 * t2 - 3 * t + 1)) + 
           (p2n * (3 * t3 - 6 * t2 + 3 * t)) +
           (p3n * (-3 * t3 + 3 * t2)) +
           (p4n * t3);
}

Coordinate Curve::get_point(float t)
{
    // ISSUE: Coordinates are normalized only after a call to the clipping
    //          method.

    auto p = window_coordinate();
    auto x = bezier(t, p[0].x(), p[1].x(), p[2].x(), p[3].x());
    auto y = bezier(t, p[0].y(), p[1].y(), p[2].y(), p[3].y());
    return Coordinate(x, y);
}

std::vector<Line> Curve::get_segments()
{
    std::vector<Line> segments;
    if (_segments.empty()) {
        for (auto t = 0.1; t < 1; t += _step) {
            Coordinate p1 = get_point(t);
            Coordinate p2 = get_point(t + _step);

            Line line = Line("Curve segment", LINE);
            line.add_coordinates({p1, p2}, WORLD);
            segments.push_back(line);
        }
    }

    return segments;
}
