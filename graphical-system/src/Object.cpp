#include "Object.hpp"
#include <math.h>

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
    return Coordinate(
        bezier(t, _p1.x(), _p2.x(), _p3.x(), _p4.x()),
        bezier(t, _p1.y(), _p2.y(), _p3.y(), _p4.y())
    );
}
