#include "Matrix.hpp"

Matrix::Matrix(size_t rows, size_t cols)
{
    std::vector<float> column(cols, 0);
    std::vector<std::vector<float>> mat(rows, column);
    _data = mat;
}

Matrix::Matrix(std::vector<std::vector<float>> mat)
{
    _data = mat;
}

size_t Matrix::rows() const
{
    return _data.size();
}

size_t Matrix::cols() const
{
    return _data.front().size();
}

std::vector<float>& Matrix::operator[](size_t i)
{
    return _data[i];
} 

std::vector<float> Matrix::operator[](size_t i) const
{
    return _data[i];
} 

void Matrix::operator=(std::vector<std::vector<float>> mat)
{
    _data = mat;
}

Matrix mat_transfer(float dx, float dy) {
    return Matrix({{1, 0, 0}, {0, 1, 0}, {dx, dy, 1}});
}

Matrix mat_scale(float sx, float sy) {
    return Matrix({{sx, 0, 0}, {0, sy, 0}, {0, 0, 1}});
}

Matrix mat_rotate(float a) {
    return Matrix({
            {std::cos(a), -std::sin(a), 0},
            {std::sin(a), std::cos(a), 0},
            {0, 0, 1}});
}
