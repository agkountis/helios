#include "mat4.h"


Mat4::Mat4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20,
           float m21, float m22, float m23, float m30, float m31, float m32, float m33)
{
    matrix[0][0] = m00;
    matrix[0][1] = m01;
    matrix[0][2] = m02;
    matrix[0][3] = m03;

    matrix[1][0] = m10;
    matrix[1][1] = m11;
    matrix[1][2] = m12;
    matrix[1][3] = m13;

    matrix[2][0] = m20;
    matrix[2][1] = m21;
    matrix[2][2] = m22;
    matrix[2][3] = m23;

    matrix[3][0] = m30;
    matrix[3][1] = m31;
    matrix[3][2] = m32;
    matrix[3][3] = m33;
}

Mat4::Mat4(const Mat4 &mat)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = mat.matrix[i][j];
        }
    }
}

void Mat4::set_row_vector(float x, float y, float z, float w, unsigned int row_idx)
{
    matrix[row_idx][0] = x;
    matrix[row_idx][1] = y;
    matrix[row_idx][2] = z;
    matrix[row_idx][3] = w;
}

void Mat4::set_column_vector(float x, float y, float z, float w, unsigned int column_idx)
{
    matrix[0][column_idx] = x;
    matrix[1][column_idx] = y;
    matrix[2][column_idx] = z;
    matrix[3][column_idx] = w;
}

void Mat4::translate(float x, float y, float z)
{
    matrix[0][3] += x;
    matrix[1][3] += y;
    matrix[2][3] += z;
}

void Mat4::translate(const Vec3 &position)
{
    matrix[0][3] += position.x;
    matrix[1][3] += position.y;
    matrix[2][3] += position.z;
}


void Mat4::scale(float x, float y, float z)
{
    matrix[0][0] *= x;
    matrix[1][1] *= y;
    matrix[2][2] *= z;
}

void Mat4::scale(const Vec3 &scale)
{
    matrix[0][0] *= scale.x;
    matrix[1][1] *= scale.y;
    matrix[2][2] *= scale.z;
}


void Mat4::set_identity()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            i == j ? matrix[i][j] = 1.0 : matrix[i][j] = 0.0;
        }
    }
}

float Mat4::determinant() const
{
    float det11 = matrix[1][1] * (matrix[2][2] * matrix[3][3] - matrix[3][2] * matrix[2][3]) -
                   matrix[1][2] * (matrix[2][1] * matrix[3][3] - matrix[3][1] * matrix[2][3]) +
                   matrix[1][3] * (matrix[2][1] * matrix[3][2] - matrix[3][1] * matrix[2][2]);

    float det12 = matrix[1][0] * (matrix[2][2] * matrix[3][3] - matrix[3][2] * matrix[2][3]) -
                   matrix[1][2] * (matrix[2][0] * matrix[3][3] - matrix[3][0] * matrix[2][3]) +
                   matrix[1][3] * (matrix[2][0] * matrix[3][2] - matrix[3][0] * matrix[2][2]);

    float det13 = matrix[1][0] * (matrix[2][1] * matrix[3][3] - matrix[3][1] * matrix[2][3]) -
                   matrix[1][1] * (matrix[2][0] * matrix[3][3] - matrix[3][0] * matrix[2][3]) +
                   matrix[1][3] * (matrix[2][0] * matrix[3][1] - matrix[3][0] * matrix[2][1]);

    float det14 = matrix[1][0] * (matrix[2][1] * matrix[3][2] - matrix[3][1] * matrix[2][2]) -
                   matrix[1][1] * (matrix[2][0] * matrix[3][2] - matrix[3][0] * matrix[2][2]) +
                   matrix[1][2] * (matrix[2][0] * matrix[3][1] - matrix[3][0] * matrix[2][1]);

    return matrix[0][0] * det11 - matrix[0][1] * det12 + matrix[0][2] * det13 - matrix[0][3] * det14;
}


void Mat4::transpose()
{
    int column_offset = 1;

    for (int i = 0; i < 3; i++) {

        for (int j = 0; j < 4 - column_offset; j++) {
            float tmp = matrix[i][j + column_offset];
            matrix[i][j + column_offset] = matrix[j + column_offset][i];
            matrix[j + column_offset][i] = tmp;
        }

        column_offset++;
    }
}

Mat4 Mat4::transposed() const
{
    Mat4 mat = *this;

    mat.transpose();

    return mat;
}

Mat4 Mat4::adjoint() const
{

    Mat4 coefficient;

    /* Row 0 ------------------------------------------------------------------------------------------- */
    coefficient[0][0] = matrix[1][1] * (matrix[3][3] * matrix[2][2] - matrix[2][3] * matrix[3][2]) -
                        matrix[1][2] * (matrix[3][3] * matrix[2][1] - matrix[2][3] * matrix[3][1]) +
                        matrix[1][3] * (matrix[3][2] * matrix[2][1] - matrix[2][2] * matrix[3][1]);

    coefficient[0][1] = matrix[1][0] * (matrix[3][3] * matrix[2][2] - matrix[2][3] * matrix[3][2]) -
                        matrix[1][2] * (matrix[2][0] * matrix[3][3] - matrix[2][3] * matrix[3][0]) +
                        matrix[1][3] * (matrix[2][0] * matrix[3][2] - matrix[2][2] * matrix[3][0]);

    coefficient[0][2] = matrix[1][0] * (matrix[3][3] * matrix[2][1] - matrix[2][3] * matrix[3][1]) -
                        matrix[1][1] * (matrix[3][3] * matrix[2][0] - matrix[2][3] * matrix[3][0]) +
                        matrix[1][3] * (matrix[3][1] * matrix[2][0] - matrix[2][1] * matrix[3][0]);

    coefficient[0][3] = matrix[1][0] * (matrix[3][2] * matrix[2][1] - matrix[2][2] * matrix[3][1]) -
                        matrix[1][1] * (matrix[3][2] * matrix[2][0] - matrix[2][2] * matrix[3][0]) +
                        matrix[1][2] * (matrix[3][1] * matrix[2][0] - matrix[2][1] * matrix[3][0]);
    /* ------------------------------------------------------------------------------------------------- */

    /* Row 1 ------------------------------------------------------------------------------------------- */
    coefficient[1][0] = matrix[0][1] * (matrix[3][3] * matrix[2][2] - matrix[2][3] * matrix[3][2]) -
                        matrix[0][2] * (matrix[3][3] * matrix[2][1] - matrix[2][3] * matrix[3][1]) +
                        matrix[0][3] * (matrix[3][2] * matrix[2][1] - matrix[2][2] * matrix[3][1]);

    coefficient[1][1] = matrix[0][0] * (matrix[3][3] * matrix[2][2] - matrix[2][3] * matrix[3][2]) -
                        matrix[0][2] * (matrix[3][3] * matrix[2][0] - matrix[2][3] * matrix[3][0]) +
                        matrix[0][3] * (matrix[3][2] * matrix[2][0] - matrix[2][2] * matrix[3][0]);

    coefficient[1][2] = matrix[0][0] * (matrix[3][3] * matrix[2][1] - matrix[2][3] * matrix[3][1]) -
                        matrix[0][1] * (matrix[3][3] * matrix[2][0] - matrix[2][3] * matrix[3][0]) +
                        matrix[0][3] * (matrix[3][1] * matrix[2][0] - matrix[2][1] * matrix[3][0]);

    coefficient[1][3] = matrix[0][0] * (matrix[3][2] * matrix[2][1] - matrix[2][2] * matrix[3][1]) -
                        matrix[0][1] * (matrix[3][2] * matrix[2][0] - matrix[2][2] * matrix[3][0]) +
                        matrix[0][2] * (matrix[3][1] * matrix[2][0] - matrix[2][1] * matrix[3][0]);
    /* ------------------------------------------------------------------------------------------------- */

    /* Row 2 ------------------------------------------------------------------------------------------- */
    coefficient[2][0] = matrix[0][1] * (matrix[3][3] * matrix[1][2] - matrix[1][3] * matrix[3][2]) -
                        matrix[0][2] * (matrix[3][3] * matrix[1][1] - matrix[1][3] * matrix[3][1]) +
                        matrix[0][3] * (matrix[3][2] * matrix[1][1] - matrix[1][2] * matrix[3][1]);

    coefficient[2][1] = matrix[0][0] * (matrix[3][3] * matrix[1][2] - matrix[1][3] * matrix[3][2]) -
                        matrix[0][2] * (matrix[3][3] * matrix[1][0] - matrix[1][3] * matrix[3][0]) +
                        matrix[0][3] * (matrix[3][2] * matrix[1][0] - matrix[1][2] * matrix[3][0]);

    coefficient[2][2] = matrix[0][0] * (matrix[3][3] * matrix[1][1] - matrix[1][3] * matrix[3][1]) -
                        matrix[0][1] * (matrix[3][3] * matrix[1][0] - matrix[1][3] * matrix[3][0]) +
                        matrix[0][3] * (matrix[3][1] * matrix[1][0] - matrix[1][1] * matrix[3][0]);

    coefficient[2][3] = matrix[0][0] * (matrix[3][2] * matrix[1][1] - matrix[1][2] * matrix[3][1]) -
                        matrix[0][1] * (matrix[3][2] * matrix[1][0] - matrix[1][2] * matrix[3][0]) +
                        matrix[0][2] * (matrix[3][1] * matrix[1][0] - matrix[1][1] * matrix[3][0]);
    /* ------------------------------------------------------------------------------------------------- */

    /* Row 3 ------------------------------------------------------------------------------------------- */
    coefficient[3][0] = matrix[0][1] * (matrix[2][3] * matrix[1][2] - matrix[1][3] * matrix[2][2]) -
                        matrix[0][2] * (matrix[2][3] * matrix[1][1] - matrix[1][3] * matrix[2][1]) +
                        matrix[0][3] * (matrix[2][2] * matrix[1][1] - matrix[1][2] * matrix[2][1]);

    coefficient[3][1] = matrix[0][0] * (matrix[2][3] * matrix[1][2] - matrix[1][3] * matrix[2][2]) -
                        matrix[0][2] * (matrix[2][3] * matrix[1][0] - matrix[1][3] * matrix[2][0]) +
                        matrix[0][3] * (matrix[2][2] * matrix[1][0] - matrix[1][2] * matrix[2][0]);

    coefficient[3][2] = matrix[0][0] * (matrix[2][3] * matrix[1][3] - matrix[1][3] * matrix[2][1]) -
                        matrix[0][1] * (matrix[2][3] * matrix[1][0] - matrix[1][3] * matrix[2][0]) +
                        matrix[0][3] * (matrix[2][1] * matrix[1][0] - matrix[1][1] * matrix[2][0]);

    coefficient[3][3] = matrix[0][0] * (matrix[2][2] * matrix[1][1] - matrix[1][2] * matrix[2][1]) -
                        matrix[0][1] * (matrix[2][2] * matrix[1][0] - matrix[1][2] * matrix[2][0]) +
                        matrix[0][2] * (matrix[2][1] * matrix[1][0] - matrix[1][1] * matrix[2][0]);
    /* ------------------------------------------------------------------------------------------------- */

    coefficient.transpose();

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

            if (i % 2)
                coefficient[i][j] = -coefficient[i][j];

            if (j % 2)
                coefficient[i][j] = -coefficient[i][j];
        }
    }

    return coefficient;
}

Mat4 Mat4::inverse() const
{
    Mat4 adj = adjoint();

    return adj * (1.0 / determinant());
}
