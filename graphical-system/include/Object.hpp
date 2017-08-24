#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <string>
#include <vector>

enum OBJECT_TYPE
{
    LINE,
    POLYGON,
    POINT
};

enum COORDINATE_TYPE
{
    WORLD,
    WINDOW
};

enum DIRECTION
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Coordinate
{
    public:
        Coordinate(float x, float y, COORDINATE_TYPE type = WORLD):
            _x(x),
            _y(y),
            _type(type) {}
        virtual ~Coordinate() {};

        float x() {return _x;}
        float y() {return _y;}
        COORDINATE_TYPE type() {return _type;}

    private:
        float _x, _y;
        COORDINATE_TYPE type;
};

class Object
{
    public:
        Object(std::string name, OBJECT_TYPE type):
            _name(name),
            _type(type) {}
        virtual ~Object() {};
        virtual void add_coordinates(float x, float y, COORDINATE_TYPE type);
        virtual void add_corrdinates(Coordinate coord);
        void update_coordinate(Coordinate coord, int pos);
        Coordinate center_point();
        OBJECT_TYPE type() {return _type;}
        std::string name() {return _name;}
        std::vector<Coordinate> world_coordinate() {return _world_coordinates;}
        std::vector<Coordinate> window_coordinate() {return _window_coordinates;}

    protected:
        std::vector<Coordinate> _world_coordinates;
        std::vector<Coordinate> _window_coordinates;

    private:
        std::string _name;
        OBJECT_TYPE _type;
};


class Line: public Object
{
    public:
        Line(std::string name, OBJECT_TYPE type):
            Object(name, type) {}
        ~Line() {}
        void add_coordinates(std::vector<Coordinate> coord) 
        {
            for(auto i = coord.begin(); i != coord.end(); ++i)
                _coordinates.push_back(*i);
        }
};

class Polygon: public Object
{
    public:
        Polygon(std::string name, OBJECT_TYPE type):
            Object(name, type) {}
        ~Polygon() {}
        void add_coordinates(std::vector<Coordinate> coord) 
        {
            for(auto i = coord.begin(); i != coord.end(); ++i)
                _coordinates.push_back(*i);
        }
};

class Point: public Object
{
    public:
        Point(std::string name, OBJECT_TYPE type):
            Object(name, type) {}
        ~Point() {}
};

#endif // OBJECTS_HPP
