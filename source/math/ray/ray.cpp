#include "ray.h"

void Ray::transform(const Mat4 &matrix)
{
    /**
     * We do not want to translate the direction of the ray so we set the translation
     * to 0.
     */
    Mat4 direction_matrix = matrix;
    direction_matrix[0][3] = direction_matrix[1][3] = direction_matrix[2][3] = 0.0f;

    origin.transform(matrix);
    direction.transform(direction_matrix);
    direction.normalize();
}
