#ifndef WINDOW_HPP
#define WINDOW_HPP


class Frame {
    public:
        Frame(float x_min, float y_min, float x_max, float y_max):
            _x_min(x_min),
            _y_min(y_min),
            _x_max(x_max),
            _y_max(y_max) {}
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

    protected:
        float _x_min;
        float _y_min;
        float _x_max;
        float _y_max;
};

#endif // WINDOW_HPP
