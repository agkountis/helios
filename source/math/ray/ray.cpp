#include "ray.h"

void Ray::transform(const Mat4 &matrix)
{
    /**
     * We do not want to translate the direction of the ray so we set the translation
     * to 0.
     */
    Mat4 direction_matrix = matrix;
    direction_matrix[3][0] = direction_matrix[3][1] = direction_matrix[3][2] = 0.0f;
//
//    origin.transform(matrix);
//    direction.transform(direction_matrix);
}
