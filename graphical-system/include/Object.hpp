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
        Coordinate(float x, float y):
            _x(x),
            _y(y) {}
        virtual ~Coordinate() {};

        float x() {return _x;}
        float y() {return _y;}

    private:
        float _x, _y;
};

class Object
{
    public:
        Object(std::string name, OBJECT_TYPE type):
            _name(name),
            _type(type) {}
        virtual ~Object() {};
        virtual void add_coordinates(float x, float y)
            {_coordinates.push_back(Coordinate(x, y));}
        virtual void add_coordinates(Coordinate coord) 
            {_coordinates.push_back(coord);}
        virtual void update_coordinate(Coordinate coord, int pos)
            {_coordinates[pos] = coord;}
        OBJECT_TYPE type() {return _type;}
        std::string name() {return _name;}
        std::vector<Coordinate> coordinate() {return _coordinates;}

    protected:
        std::vector<Coordinate> _coordinates;

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
