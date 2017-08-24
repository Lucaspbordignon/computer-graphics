#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <cstdio>
#include <cmath>

class Matrix {
    public:
        Matrix(size_t, size_t);
        Matrix(std::vector<std::vector<float>>);
        ~Matrix() {};
        size_t rows() const;
        size_t cols() const;
        std::vector<float>& operator[](size_t);
        std::vector<float> operator[](size_t) const;
        void operator=(std::vector<std::vector<float>>);
        
    private:
        std::vector<std::vector<float>> _data;
};

#endif // MATRIX_HPP
