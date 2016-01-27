#include "mat4.h"


Mat4::Mat4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20,
           float m21, float m22, float m23, float m30, float m31, float m32, float m33)
{
    data[0][0] = m00;
    data[0][1] = m01;
    data[0][2] = m02;
    data[0][3] = m03;

    data[1][0] = m10;
    data[1][1] = m11;
    data[1][2] = m12;
    data[1][3] = m13;

    data[2][0] = m20;
    data[2][1] = m21;
    data[2][2] = m22;
    data[2][3] = m23;

    data[3][0] = m30;
    data[3][1] = m31;
    data[3][2] = m32;
    data[3][3] = m33;
}

Mat4::Mat4(const Mat4 &mat)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] = mat.data[i][j];
        }
    }
}

void Mat4::set_row_vector(float x, float y, float z, float w, unsigned int row_idx)
{
    data[row_idx][0] = x;
    data[row_idx][1] = y;
    data[row_idx][2] = z;
    data[row_idx][3] = w;
}

void Mat4::set_column_vector(float x, float y, float z, float w, unsigned int column_idx)
{
    data[0][column_idx] = x;
    data[1][column_idx] = y;
    data[2][column_idx] = z;
    data[3][column_idx] = w;
}

void Mat4::translate(float x, float y, float z)
{
    Mat4 translation_mat(1.0f, 0.0f, 0.0f, x,
                         0.0f, 1.0f, 0.0f, y,
                         0.0f, 0.0f, 1.0f, z,
                         0.0f, 0.0f, 0.0f, 1.0f);

    *this = *this * translation_mat;
}

void Mat4::translate(const Vec3 &position)
{
    Mat4 translation_mat(1.0f, 0.0f, 0.0f, position.x,
                         0.0f, 1.0f, 0.0f, position.y,
                         0.0f, 0.0f, 1.0f, position.z,
                         0.0f, 0.0f, 0.0f, 1.0f);

    *this = *this * translation_mat;
}


void Mat4::scale(float x, float y, float z)
{
    Mat4 scale_mat(x, 0.0f, 0.0f, 0.0f,
                   0.0f, y, 0.0f, 0.0f,
                   0.0f, 0.0f, z, 0.0f,
                   0.0f, 0.0f, 0.0f, 1.0f);

    *this = *this * scale_mat;
}

void Mat4::scale(const Vec3 &scale)
{
    Mat4 scale_mat(scale.x, 0.0f, 0.0f, 0.0f,
                   0.0f, scale.y, 0.0f, 0.0f,
                   0.0f, 0.0f, scale.z, 0.0f,
                   0.0f, 0.0f, 0.0f, 1.0f);

    *this = *this * scale_mat;
}


void Mat4::set_identity()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            i == j ? data[i][j] = 1.0 : data[i][j] = 0.0;
        }
    }
}

float Mat4::determinant() const
{
    float det11 = data[1][1] * (data[2][2] * data[3][3] - data[3][2] * data[2][3]) -
                  data[1][2] * (data[2][1] * data[3][3] - data[3][1] * data[2][3]) +
                  data[1][3] * (data[2][1] * data[3][2] - data[3][1] * data[2][2]);

    float det12 = data[1][0] * (data[2][2] * data[3][3] - data[3][2] * data[2][3]) -
                  data[1][2] * (data[2][0] * data[3][3] - data[3][0] * data[2][3]) +
                  data[1][3] * (data[2][0] * data[3][2] - data[3][0] * data[2][2]);

    float det13 = data[1][0] * (data[2][1] * data[3][3] - data[3][1] * data[2][3]) -
                  data[1][1] * (data[2][0] * data[3][3] - data[3][0] * data[2][3]) +
                  data[1][3] * (data[2][0] * data[3][1] - data[3][0] * data[2][1]);

    float det14 = data[1][0] * (data[2][1] * data[3][2] - data[3][1] * data[2][2]) -
                  data[1][1] * (data[2][0] * data[3][2] - data[3][0] * data[2][2]) +
                  data[1][2] * (data[2][0] * data[3][1] - data[3][0] * data[2][1]);

    return data[0][0] * det11 - data[0][1] * det12 + data[0][2] * det13 - data[0][3] * det14;
}


void Mat4::transpose()
{
    int column_offset = 1;

    for (int i = 0; i < 3; i++) {

        for (int j = 0; j < 4 - column_offset; j++) {
            float tmp = data[i][j + column_offset];
            data[i][j + column_offset] = data[j + column_offset][i];
            data[j + column_offset][i] = tmp;
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
    coefficient[0][0] = data[1][1] * (data[3][3] * data[2][2] - data[2][3] * data[3][2]) -
                        data[1][2] * (data[3][3] * data[2][1] - data[2][3] * data[3][1]) +
                        data[1][3] * (data[3][2] * data[2][1] - data[2][2] * data[3][1]);

    coefficient[0][1] = data[1][0] * (data[3][3] * data[2][2] - data[2][3] * data[3][2]) -
                        data[1][2] * (data[2][0] * data[3][3] - data[2][3] * data[3][0]) +
                        data[1][3] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]);

    coefficient[0][2] = data[1][0] * (data[3][3] * data[2][1] - data[2][3] * data[3][1]) -
                        data[1][1] * (data[3][3] * data[2][0] - data[2][3] * data[3][0]) +
                        data[1][3] * (data[3][1] * data[2][0] - data[2][1] * data[3][0]);

    coefficient[0][3] = data[1][0] * (data[3][2] * data[2][1] - data[2][2] * data[3][1]) -
                        data[1][1] * (data[3][2] * data[2][0] - data[2][2] * data[3][0]) +
                        data[1][2] * (data[3][1] * data[2][0] - data[2][1] * data[3][0]);
    /* ------------------------------------------------------------------------------------------------- */

    /* Row 1 ------------------------------------------------------------------------------------------- */
    coefficient[1][0] = data[0][1] * (data[3][3] * data[2][2] - data[2][3] * data[3][2]) -
                        data[0][2] * (data[3][3] * data[2][1] - data[2][3] * data[3][1]) +
                        data[0][3] * (data[3][2] * data[2][1] - data[2][2] * data[3][1]);

    coefficient[1][1] = data[0][0] * (data[3][3] * data[2][2] - data[2][3] * data[3][2]) -
                        data[0][2] * (data[3][3] * data[2][0] - data[2][3] * data[3][0]) +
                        data[0][3] * (data[3][2] * data[2][0] - data[2][2] * data[3][0]);

    coefficient[1][2] = data[0][0] * (data[3][3] * data[2][1] - data[2][3] * data[3][1]) -
                        data[0][1] * (data[3][3] * data[2][0] - data[2][3] * data[3][0]) +
                        data[0][3] * (data[3][1] * data[2][0] - data[2][1] * data[3][0]);

    coefficient[1][3] = data[0][0] * (data[3][2] * data[2][1] - data[2][2] * data[3][1]) -
                        data[0][1] * (data[3][2] * data[2][0] - data[2][2] * data[3][0]) +
                        data[0][2] * (data[3][1] * data[2][0] - data[2][1] * data[3][0]);
    /* ------------------------------------------------------------------------------------------------- */

    /* Row 2 ------------------------------------------------------------------------------------------- */
    coefficient[2][0] = data[0][1] * (data[3][3] * data[1][2] - data[1][3] * data[3][2]) -
                        data[0][2] * (data[3][3] * data[1][1] - data[1][3] * data[3][1]) +
                        data[0][3] * (data[3][2] * data[1][1] - data[1][2] * data[3][1]);

    coefficient[2][1] = data[0][0] * (data[3][3] * data[1][2] - data[1][3] * data[3][2]) -
                        data[0][2] * (data[3][3] * data[1][0] - data[1][3] * data[3][0]) +
                        data[0][3] * (data[3][2] * data[1][0] - data[1][2] * data[3][0]);

    coefficient[2][2] = data[0][0] * (data[3][3] * data[1][1] - data[1][3] * data[3][1]) -
                        data[0][1] * (data[3][3] * data[1][0] - data[1][3] * data[3][0]) +
                        data[0][3] * (data[3][1] * data[1][0] - data[1][1] * data[3][0]);

    coefficient[2][3] = data[0][0] * (data[3][2] * data[1][1] - data[1][2] * data[3][1]) -
                        data[0][1] * (data[3][2] * data[1][0] - data[1][2] * data[3][0]) +
                        data[0][2] * (data[3][1] * data[1][0] - data[1][1] * data[3][0]);
    /* ------------------------------------------------------------------------------------------------- */

    /* Row 3 ------------------------------------------------------------------------------------------- */
    coefficient[3][0] = data[0][1] * (data[2][3] * data[1][2] - data[1][3] * data[2][2]) -
                        data[0][2] * (data[2][3] * data[1][1] - data[1][3] * data[2][1]) +
                        data[0][3] * (data[2][2] * data[1][1] - data[1][2] * data[2][1]);

    coefficient[3][1] = data[0][0] * (data[2][3] * data[1][2] - data[1][3] * data[2][2]) -
                        data[0][2] * (data[2][3] * data[1][0] - data[1][3] * data[2][0]) +
                        data[0][3] * (data[2][2] * data[1][0] - data[1][2] * data[2][0]);

    coefficient[3][2] = data[0][0] * (data[2][3] * data[1][3] - data[1][3] * data[2][1]) -
                        data[0][1] * (data[2][3] * data[1][0] - data[1][3] * data[2][0]) +
                        data[0][3] * (data[2][1] * data[1][0] - data[1][1] * data[2][0]);

    coefficient[3][3] = data[0][0] * (data[2][2] * data[1][1] - data[1][2] * data[2][1]) -
                        data[0][1] * (data[2][2] * data[1][0] - data[1][2] * data[2][0]) +
                        data[0][2] * (data[2][1] * data[1][0] - data[1][1] * data[2][0]);
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
