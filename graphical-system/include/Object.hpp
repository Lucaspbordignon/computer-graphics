#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <string>
#include <vector>
#include <math.h>

enum OBJECT_TYPE
{
    LINE,
    POLYGON,
    POINT,
    CURVE
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

enum ZOOM_TYPE
{
    IN,
    OUT
};

class Coordinate
{
    public:
        Coordinate() {};
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
        Object() {}
        Object(std::string name, OBJECT_TYPE type):
            _name(name),
            _type(type) {}
        virtual ~Object() {};
        virtual void add_coordinates(float x, float y, COORDINATE_TYPE type);
        virtual void add_coordinates(Coordinate coord, COORDINATE_TYPE type);
        virtual void add_coordinates(std::vector<Coordinate>, COORDINATE_TYPE type);
        Coordinate center_point();
        void update_coordinate(Coordinate coord, int pos);
        OBJECT_TYPE type() {return _type;}
        std::string name() {return _name;}
        std::vector<Coordinate> world_coordinate() {return _world_coordinates;}
        std::vector<Coordinate> window_coordinate() {return _window_coordinates;}

    private:
        std::string _name;
        OBJECT_TYPE _type;
        std::vector<Coordinate> _world_coordinates;
        std::vector<Coordinate> _window_coordinates;
};


class Line: public Object
{
    public:
        Line(std::string name, OBJECT_TYPE type):
            Object(name, type) {}
        ~Line() {}
};

class Polygon: public Object
{
    public:
        Polygon(std::string name, OBJECT_TYPE type):
            Object(name, type) {}
        ~Polygon() {}
};

class Point: public Object
{
    public:
        Point(std::string name, OBJECT_TYPE type):
            Object(name, type) {}
        ~Point() {}
};

class Curve: public Object
{
    public:
        Curve(std::string name, OBJECT_TYPE type):
            Object(name, type),
            _step(1e-3) {}
        Curve(std::string name, std::vector<Coordinate> points):
            Object(name, CURVE),
            _step(1e-3) {
                add_coordinates(points, WORLD);
            }
        virtual ~Curve() {};
        virtual Coordinate get_point(float t, int i) {};
        std::vector<Line*> get_segments();
        void set_segments(std::vector<Line*> segments);
        virtual std::vector<Line*> generate_segments();

    protected:
        float _step;

    private:
        std::vector<Line*> _segments;
};

class Bezier: public Curve
{
    public:
        Bezier(std::string name):
            Curve(name, CURVE) {}
        Bezier(std::string name, std::vector<Coordinate> points):
            Curve(name, points) {}
        ~Bezier() {}
        Coordinate get_point(float t, int i);
    private:
        float bezier(float, float, float, float, float);
};

class Spline: public Curve
{
    public:
        Spline(std::string name):
            Curve(name, CURVE) {}
        Spline(std::string name, std::vector<Coordinate> points):
            Curve(name, points) {}
        ~Spline() {}
        Coordinate get_point(float t, int i = 0);
    private:
        float spline(float, float, float, float, float);
};

#endif // OBJECTS_HPP
