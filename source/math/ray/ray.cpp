/*
Helios-Ray - A powerful and highly configurable renderer
Copyright (C) 2016  Angelos Gkountis

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ray.h"

void Ray::transform(const Mat4 &matrix)
{
    /**
     * We do not want to translate the direction of the ray so we set the translation
     * to 0.
     */
    Mat4 direction_matrix = matrix;

    direction_matrix[0][3] = direction_matrix[1][3] = direction_matrix[2][3] =
    direction_matrix[3][0] = direction_matrix[3][1] = direction_matrix[3][2] = 0.0;

    direction_matrix[3][3] = 1.0;

    origin.transform(matrix);
    direction.transform(direction_matrix);
}
