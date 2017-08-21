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

/**
 * Given an Object and a certain angle (in degrees), applies a rotation
 * algorithm on it, rotation based on the origin.
 */
void rotate_2d_object(Object* obj, float angle)
{
    float ang_in_rad = angle * (M_PI / 180.0);
    Matrix transformation = Matrix({
        {std::cos(ang_in_rad), -std::sin(ang_in_rad), 0},        
        {std::sin(ang_in_rad), std::cos(ang_in_rad), 0},
        {0, 0, 1} 
    });

    for (auto i = 0u; i < obj->coordinate().size(); ++i) {
        auto coord = obj->coordinate()[i];
        auto coord_matrix = Matrix( {{coord.x(), coord.y(), 1.0}} );
        coord_matrix = dot_product(coord_matrix, transformation);
        obj->update_coordinate(Coordinate(coord_matrix[0][0], coord_matrix[0][1]), i);
    }
}

/**
 * Given an Object and a certain angle (in degrees), applies a rotation
 * algorithm on it. The rotation is centered at the point (x, y), so a
 * translation is made, then the rotation and a translation to the original
 * point is applied. All is made in a single matrix multiplication.
 */
void rotate_2d_object(Object* obj, float angle, float x, float y)
{
    // TODO: Fix this. The transformation is not right
    float ang_in_rad = angle * (M_PI / 180.0);
    auto cos_angle = std::cos(ang_in_rad);
    auto sin_angle = std::sin(ang_in_rad);

    for (auto i = 0u; i < obj->coordinate().size(); ++i) {
        auto coord = obj->coordinate()[i];
        auto coord_matrix = Matrix( {{coord.x(), coord.y(), 1.0}} );

        auto dx = coord.x() - x;
        auto dy = coord.y() - y;
        auto exp_x = (-dx * cos_angle) - (dy * sin_angle) + dx;
        auto exp_y = (-dx * cos_angle) - (dy * sin_angle) + dx;
        Matrix transformation = Matrix({
            {cos_angle, -sin_angle, 0},        
            {sin_angle, cos_angle, 0},
            {exp_x, exp_y, 1} 
        });

        coord_matrix = dot_product(coord_matrix, transformation);
        obj->update_coordinate(Coordinate(coord_matrix[0][0], coord_matrix[0][1]), i);
    }
}

#endif // TRANSFORMATION_HPP
