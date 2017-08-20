#ifndef TRANSFORMATION_HPP
#define TRANSFORMATION_HPP

#include "Object.hpp"
#include "Matrix.hpp"


/** 
 * Given 2 multi-dimensional arrays, applies the scalar
 * product between them.
 */
Matrix dot_product(const Matrix matrix_a, const Matrix matrix_b)
{
    Matrix matrix_final = Matrix(matrix_a.rows(), matrix_b.cols());

    for (auto i = 0u; i < matrix_a.rows(); ++i)
        for (auto j = 0u; j < matrix_b.cols(); ++j) 
            for (auto k = 0u; k < matrix_b.rows(); ++k) {
                matrix_final[i][j] += matrix_a[i][k] * matrix_b[k][j];
            }

    return matrix_final;
}

/**
 * Given a 2D vector of coordinates and a displacement vector, creates
 * the right matrices and applies the translations.
 *
 */
void translation_2d_object(Object* obj, float dx, float dy)
{
    Matrix transformation = Matrix({
        {1, 0, 0},
        {0, 1, 0},
        {dx, dy, 1}
    });

    for (auto i = 0u; i < obj->coordinate().size(); ++i) {
        auto coord = obj->coordinate()[i];
        auto coord_matrix = Matrix( {{coord.x(), coord.y(), 1.0}} );
        coord_matrix = dot_product(coord_matrix, transformation);
        obj->update_coordinate(Coordinate(coord_matrix[0][0], coord_matrix[0][1]), i);
    }
}

/**
 * Given an Object and a 2D vector of coordinates to scale,
 * creates the tranformation matrix and applies it to the object.
 */
void scale_2d_object(Object* obj, float sx, float sy)
{
    Matrix transformation = Matrix({
        {sx, 0, 0},
        {0, sy, 0},
        {0, 0, 1}
    });

    for (auto i = 0u; i < obj->coordinate().size(); ++i) {
        auto coord = obj->coordinate()[i];
        auto coord_matrix = Matrix( {{coord.x(), coord.y(), 1.0}} );
        coord_matrix = dot_product(coord_matrix, transformation);
        obj->update_coordinate(Coordinate(coord_matrix[0][0], coord_matrix[0][1]), i);
    }
}

void rotate_2d_object(Object* obj, float sx, float sy)
{}


#endif // TRANSFORMATION_HPP
