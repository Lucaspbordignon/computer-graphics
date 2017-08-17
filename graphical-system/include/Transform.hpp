#ifndef TRANSFORMATION_HPP
#define TRANSFORMATION_HPP

#include "Object.hpp"

typedef std::vector<std::vector<float>> Matrix;

/** 
 * Given 2 multi-dimensional arrays, applies the scalar
 * product between them.
 */
float** dot_product(const Matrix matrix_a, const Matrix matrix_b)
{
    auto matrix_b_rows = matrix_b.size();
    auto matrix_b_cols = matrix_b.front().size(); 
    auto matrix_a_lines = matrix_a.size();
    float** matrix_final;

    for (auto i = 0u; i < matrix_a_lines; ++i)
        for (auto j = 0u; j < matrix_b_cols; ++j) {
            matrix_final[i][j] = 0;
            for (auto k = 0u; k < matrix_b_rows; ++k) {
                matrix_final[i][j] += matrix_a[i][k] * matrix_b[k][j];
            }
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
    Matrix tranformation = {
        {1, 0, 0},
        {0, 1, 0},
        {dx, dy, 1}
    };

    for (auto i = 0u; i < obj->coordinate().size(); ++i) {
        auto coord = obj->coordinate()[i];
        auto coord_matrix = Matrix{{coord.x(), coord.y(), 1.0}};
        auto transf_coord = dot_product(coord_matrix, tranformation);
        //obj->update_coordinate(Coordinate(transf_coord[0][0], transf_coord[0][1]), i);
    }
}


#endif // TRANSFORMATION_HPP
