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
    CURVE,
    OBJECT_3D
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
        Coordinate(float x, float y, float z = 0):
            _x(x),
            _y(y),
            _z(z) {}
        virtual ~Coordinate() {};

        float x() {return _x;}
        float y() {return _y;}
        float z() {return _z;}

    private:
        float _x, _y, _z;
};

class Object
{
    public:
        Object() {}
        Object(std::string name, OBJECT_TYPE type):
            _name(name),
            _type(type) {}
        virtual ~Object() {};
        virtual void add_coordinates(float x, float y, float z=0, COORDINATE_TYPE type=WORLD);
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
        Line(std::string name):
            Object(name, LINE) {}
        ~Line() {}
};

class Polygon: public Object
{
    public:
        Polygon(std::string name):
            Object(name, POLYGON) {}
        ~Polygon() {}
};

class Point: public Object
{
    public:
        Point(std::string name):
            Object(name, POINT) {}
        ~Point() {}
};

class Object_3d: public Object
{
    public:
        Object_3d(std::string name):
            Object(name, OBJECT_3D) {}
        ~Object_3d() {}

        std::vector<Polygon*> get_faces();
        void add_faces(std::vector<Polygon*>);

    public:
        std::vector<Polygon*> _faces;
    
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
