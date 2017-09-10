
#ifndef EDGE_HPP
#define EDGE_HPP

#include "Object.hpp"

class Edge
{
    public:
        Edge(Coordinate v1, Coordinate v2) :
            _v1(v1), _v2(v2) {}
        Edge(float x1, float y1, float x2, float y2) :
            _v1(Coordinate(x1, y1)),
            _v2(Coordinate(x2, y2)) {}
        virtual ~Edge() {}

        Coordinate v1() { return _v1; }
        Coordinate v2() { return _v2; }

    private:
        Coordinate _v1;
        Coordinate _v2;
};

#endif // EDGE_HPP