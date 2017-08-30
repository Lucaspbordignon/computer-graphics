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
