#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <string>

enum OBJECT_TYPE
{
    LINE,
    POLYGON,
    POINT
};

struct Coordinate
{
    float x, y;
    Coordinate(float x, float y): x(x), y(y) {}
};

class Object
{
    public:
        Object(std::string name, OBJECT_TYPE type, float x, float y):
            _name(name),
            _type(type),
            _coordinate(Coordinate(x, y)) {}
        virtual ~Object() {};
        virtual OBJECT_TYPE type() {return _type;}
        std::string name() {return _name;}
        Coordinate coordinate() {return _coordinate;}

    private:
        std::string _name;
        OBJECT_TYPE _type;
        Coordinate _coordinate;
};

class Line: public Object
{
    public:
        Line(std::string name, OBJECT_TYPE type, float x, float y):
            Object(name, type, x, y) {}
        ~Line() {}
};

class Polygon: public Object
{
    public:
        Polygon(std::string name, OBJECT_TYPE type, float x, float y):
            Object(name, type, x, y) {}
        ~Polygon() {}
};

class Point: public Object
{
    public:
        Point(std::string name, OBJECT_TYPE type, float x, float y):
            Object(name, type, x, y) {}
        ~Point() {}
};

#endif // OBJECTS_HPP
