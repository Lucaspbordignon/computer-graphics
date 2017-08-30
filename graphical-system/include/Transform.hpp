#ifndef TRANSFORMATION_HPP
#define TRANSFORMATION_HPP

#include "Object.hpp"
#include "Matrix.hpp"
#include "DisplayFile.hpp"


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

    for (auto i = 0u; i < obj->world_coordinate().size(); ++i) {
        auto coord = obj->world_coordinate()[i];
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

    for (auto i = 0u; i < obj->world_coordinate().size(); ++i) {
        auto coord = obj->world_coordinate()[i];
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

    for (auto i = 0u; i < obj->world_coordinate().size(); ++i) {
        auto coord = obj->world_coordinate()[i];
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
    float ang_in_rad = angle * (M_PI / 180.0);
    auto cos_angle = std::cos(ang_in_rad);
    auto sin_angle = std::sin(ang_in_rad);

    for (auto i = 0u; i < obj->world_coordinate().size(); ++i) {
        auto coord = obj->world_coordinate()[i];

        auto dx = coord.x() - x;
        auto dy = coord.y() - y;
        auto new_x = (dx * cos_angle) - (dy * sin_angle) + x;
        auto new_y = (dx * sin_angle) + (dy * cos_angle) + y;

        obj->update_coordinate(Coordinate(new_x, new_y), i);
    }
}

/**
 * Given an object and a matrix of normalization, applies it to the object
 * and save the normalized coordinates inside of it.
 */
void normalize(Object* obj, Matrix norm_mat)
{
    auto norm_coord = std::vector<Coordinate>();
    auto wrld_coord = obj->world_coordinate();

    for (auto& i : wrld_coord) {
      Matrix result = dot_product(Matrix({{i.x(), i.y(), 1}}), norm_mat);
      norm_coord.push_back(Coordinate(result[0][0], result[0][1]));
    }
    obj->add_coordinates(norm_coord, WINDOW);
}

/**
 * Applies the normalization of a NCS (Normalized Coordinate System) to
 * all the objects of a given display file. Rotations of the window may
 * occour.
 */
void normalize_coordinates(Frame window, DisplayFile& objects)
{
    float ang_in_rad = window.angle() * (M_PI / 180.0);
    auto wc_x = window.x_center();
    auto wc_y = window.y_center();
    auto m_scale = mat_scale(2/(window.get_x_max() - window.get_x_min()),
                             2/(window.get_y_max() - window.get_y_min()));
    
    auto normalization_mat = dot_product(mat_transfer(-wc_x, -wc_y),
                                         mat_rotate(-ang_in_rad));
    normalization_mat = dot_product(normalization_mat, m_scale); 

    for(auto obj = objects.begin(); obj != objects.end(); ++obj)
        normalize(*obj, normalization_mat);
}

#endif // TRANSFORMATION_HPP
