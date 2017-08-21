#include "Object.hpp"

void Object::add_coordinates(float x, float y)
{
    _coordinates.push_back(Coordinate(x, y));
}

void Object::add_coordinates(Coordinate coord) 
{
    _coordinates.push_back(coord);
}
        
void Object::update_coordinate(Coordinate coord, int pos)
{
    _coordinates[pos] = coord;
}

Coordinate Object::center_point()
{
    auto n = _coordinates.size();
    float sum_x = 0;
    float sum_y = 0;

    for (auto i = 0u; i < n; ++i) {
        sum_x += _coordinates[i].x();
        sum_y += _coordinates[i].y();
    }
    return Coordinate((sum_x / n), (sum_y / n));
}
