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

#ifndef HELIOS_MAT4_H
#define HELIOS_MAT4_H

#include <vec3.h>

class Mat4 {
private:
    float data[4][4] = {{1.0, 0.0, 0.0, 0.0},
                        {0.0, 1.0, 0.0, 0.0},
                        {0.0, 0.0, 1.0, 0.0},
                        {0.0, 0.0, 0.0, 1.0}};

public:
    Mat4() = default;

    Mat4(float m00, float m01, float m02, float m03,
         float m10, float m11, float m12, float m13,
         float m20, float m21, float m22, float m23,
         float m30, float m31, float m32, float m33);

    Mat4(const Mat4 &mat);

    void set_row_vector(float x, float y, float z, float w, unsigned int row_idx);

    void set_column_vector(float x, float y, float z, float w, unsigned int column_idx);

    void translate(float x, float y, float z);

    void translate(const Vec3 &position);

    void scale(float x, float y, float z);

    void scale(const Vec3 &scale);

    void set_identity();

    float determinant() const;

    void transpose();

    Mat4 transposed() const;

    Mat4 adjoint() const;

    Mat4 inverse() const;

    inline float *operator[](const unsigned int index)
    { return data[index]; }

    inline const float *operator[](const unsigned int index) const
    { return data[index]; }

    friend Mat4 operator*(const Mat4 &mat1, const Mat4 &mat2);

    friend Mat4 operator*(Mat4 &mat, float scalar);

    inline void operator=(const Mat4 &mat2)
    {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                data[i][j] = mat2.data[i][j];
            }
        }
    }
};

inline Mat4 operator*(const Mat4 &mat1, const Mat4 &mat2)
{
    Mat4 res;

    res.data[0][0] = mat1.data[0][0] * mat2.data[0][0] + mat1.data[0][1] * mat2.data[1][0]
                     + mat1.data[0][2] * mat2.data[2][0] + mat1.data[0][3] * mat2.data[3][0];

    res.data[0][1] = mat1.data[0][0] * mat2.data[0][1] + mat1.data[0][1] * mat2.data[1][1]
                     + mat1.data[0][2] * mat2.data[2][1] + mat1.data[0][3] * mat2.data[3][1];

    res.data[0][2] = mat1.data[0][0] * mat2.data[0][2] + mat1.data[0][1] * mat2.data[1][2]
                     + mat1.data[0][2] * mat2.data[2][2] + mat1.data[0][3] * mat2.data[3][2];

    res.data[0][3] = mat1.data[0][0] * mat2.data[0][3] + mat1.data[0][1] * mat2.data[1][3]
                     + mat1.data[0][2] * mat2.data[2][3] + mat1.data[0][3] * mat2.data[3][3];


    res.data[1][0] = mat1.data[1][0] * mat2.data[0][0] + mat1.data[1][1] * mat2.data[1][0]
                     + mat1.data[1][2] * mat2.data[2][0] + mat1.data[1][3] * mat2.data[3][0];

    res.data[1][1] = mat1.data[1][0] * mat2.data[0][1] + mat1.data[1][1] * mat2.data[1][1]
                     + mat1.data[1][2] * mat2.data[2][1] + mat1.data[1][3] * mat2.data[3][1];

    res.data[1][2] = mat1.data[1][0] * mat2.data[0][2] + mat1.data[1][1] * mat2.data[1][2]
                     + mat1.data[1][2] * mat2.data[2][2] + mat1.data[1][3] * mat2.data[3][2];

    res.data[1][3] = mat1.data[1][0] * mat2.data[0][3] + mat1.data[1][1] * mat2.data[1][3]
                     + mat1.data[1][2] * mat2.data[2][3] + mat1.data[1][3] * mat2.data[3][3];


    res.data[2][0] = mat1.data[2][0] * mat2.data[0][0] + mat1.data[2][1] * mat2.data[1][0]
                     + mat1.data[2][2] * mat2.data[2][0] + mat1.data[2][3] * mat2.data[3][0];

    res.data[2][1] = mat1.data[2][0] * mat2.data[0][1] + mat1.data[2][1] * mat2.data[1][1]
                     + mat1.data[2][2] * mat2.data[2][1] + mat1.data[2][3] * mat2.data[3][1];

    res.data[2][2] = mat1.data[2][0] * mat2.data[0][2] + mat1.data[2][1] * mat2.data[1][2]
                     + mat1.data[2][2] * mat2.data[2][2] + mat1.data[2][3] * mat2.data[3][2];

    res.data[2][3] = mat1.data[2][0] * mat2.data[0][3] + mat1.data[2][1] * mat2.data[1][3]
                     + mat1.data[2][2] * mat2.data[2][3] + mat1.data[2][3] * mat2.data[3][3];


    res.data[3][0] = mat1.data[3][0] * mat2.data[0][0] + mat1.data[3][1] * mat2.data[1][0]
                     + mat1.data[3][2] * mat2.data[2][0] + mat1.data[3][3] * mat2.data[3][0];

    res.data[3][1] = mat1.data[3][0] * mat2.data[0][1] + mat1.data[3][1] * mat2.data[1][1]
                     + mat1.data[3][2] * mat2.data[2][1] + mat1.data[3][3] * mat2.data[3][1];

    res.data[3][2] = mat1.data[3][0] * mat2.data[0][2] + mat1.data[3][1] * mat2.data[1][2]
                     + mat1.data[3][2] * mat2.data[2][2] + mat1.data[3][3] * mat2.data[3][2];

    res.data[3][3] = mat1.data[3][0] * mat2.data[0][3] + mat1.data[3][1] * mat2.data[1][3]
                     + mat1.data[3][2] * mat2.data[2][3] + mat1.data[3][3] * mat2.data[3][3];

    return res;
}

inline Mat4 operator*(Mat4 &mat, float scalar)
{
    Mat4 res;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res[i][j] = mat.data[i][j] * scalar;
        }
    }

    return res;
}

#endif //HELIOS_MAT4_H
