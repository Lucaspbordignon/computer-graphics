#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Object.hpp"
#include "Edge.hpp"

class Frame : public Object {
    public:
        Frame() : Object("Window", POLYGON)
        {
            add_coordinates(-1, -1, WINDOW);
            add_coordinates(-1, 1, WINDOW);
            add_coordinates(1, -1, WINDOW);
            add_coordinates(1, 1, WINDOW);
        }

        Frame(float x_min, float y_min, float x_max, float y_max):
            Object("Window", POLYGON),
            _x_min(x_min),
            _y_min(y_min),
            _x_max(x_max),
            _y_max(y_max),
            _angle(0.0)
            {
                add_coordinates({
                        Coordinate(-1, -1),
                        Coordinate(-1, 1),
                        Coordinate(1, -1),
                        Coordinate(1, 1),
                        }, WINDOW);
                add_coordinates({
                        Coordinate(x_min, y_min),
                        Coordinate(x_min, y_max),
                        Coordinate(x_max, y_min),
                        Coordinate(x_max, y_max),
                        }, WORLD);
            }
        virtual ~Frame() {};
        
        // Getters and Setters
        float get_x_min() { return _x_min; }
        void set_x_min(float x_min) { _x_min = x_min; }

        float get_y_min() { return _y_min; }
        void set_y_min(float y_min) { _y_min = y_min; }

        float get_x_max() { return _x_max; }
        void set_x_max(float x_max) { _x_max = x_max; }

        float get_y_max() { return _y_max; }
        void set_y_max(float y_max) { _y_max = y_max; }

        float angle() { return _angle; }

        float x_center() { return (_x_min + _x_max)/2; }
        float y_center() { return (_y_min + _y_max)/2; }

        void rotate(float ang) { _angle +=  ang; }

        std::vector<Edge> edges() {
            return {
                Edge(_x_min, _y_min, _x_min, _y_max),
                Edge(_x_min, _y_max, _x_max, _y_max),
                Edge(_x_max, _y_max, _x_max, _y_min),
                Edge(_x_max, _y_min, _x_min, _y_min)
            };
        }

    private:
        float _x_min;
        float _y_min;
        float _x_max;
        float _y_max;
        float _angle;
};

#endif // WINDOW_HPP
