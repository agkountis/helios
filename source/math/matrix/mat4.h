#ifndef HELIOS_MAT4_H
#define HELIOS_MAT4_H

#include <vec3.h>

class Mat4 {
private:
    double matrix[4][4] = {{1.0, 0.0, 0.0, 0.0},
                           {0.0, 1.0, 0.0, 0.0},
                           {0.0, 0.0, 1.0, 0.0},
                           {0.0, 0.0, 0.0, 1.0}};

public:
    Mat4() = default;

    Mat4(double m00, double m01, double m02, double m03,
         double m10, double m11, double m12, double m13,
         double m20, double m21, double m22, double m23,
         double m30, double m31, double m32, double m33);

    Mat4(const Mat4 &mat);

    void set_row_vector(double x, double y, double z, double w, unsigned int row_idx);

    void set_column_vector(double x, double y, double z, double w, unsigned int column_idx);

    void translate(double x, double y, double z);

    void translate(const Vec3 &position);

    void scale(double x, double y, double z);

    void scale(const Vec3 &scale);

    void set_identity();

    double determinant() const;

    void transpose();

    Mat4 transposed() const;

    Mat4 adjoint() const;

    Mat4 inverse() const;

    inline double *operator[](unsigned int i)
    { return matrix[i]; }

    friend Mat4 operator*(const Mat4 &mat1, const Mat4 &mat2);

    friend Mat4 operator*(Mat4 &mat, double scalar);

    inline void operator=(const Mat4 &mat2)
    {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j <  4; j++) {
                matrix[i][j] = mat2.matrix[i][j];
            }
        }
    }
};

inline Mat4 operator*(const Mat4 &mat1, const Mat4 &mat2)
{
    Mat4 res;

    res.matrix[0][0] = mat1.matrix[0][0] * mat2.matrix[0][0] + mat1.matrix[0][1] * mat2.matrix[1][0]
                       + mat1.matrix[0][2] * mat2.matrix[2][0] + mat1.matrix[0][3] * mat2.matrix[3][0];

    res.matrix[0][1] = mat1.matrix[0][0] * mat2.matrix[0][1] + mat1.matrix[0][1] * mat2.matrix[1][1]
                       + mat1.matrix[0][2] * mat2.matrix[2][1] + mat1.matrix[0][3] * mat2.matrix[3][1];

    res.matrix[0][2] = mat1.matrix[0][0] * mat2.matrix[0][2] + mat1.matrix[0][1] * mat2.matrix[1][2]
                       + mat1.matrix[0][2] * mat2.matrix[2][2] + mat1.matrix[0][3] * mat2.matrix[3][2];

    res.matrix[0][3] = mat1.matrix[0][0] * mat2.matrix[0][3] + mat1.matrix[0][1] * mat2.matrix[1][3]
                       + mat1.matrix[0][2] * mat2.matrix[2][3] + mat1.matrix[0][3] * mat2.matrix[3][3];


    res.matrix[1][0] = mat1.matrix[1][0] * mat2.matrix[0][0] + mat1.matrix[1][1] * mat2.matrix[1][0]
                       + mat1.matrix[1][2] * mat2.matrix[2][0] + mat1.matrix[1][3] * mat2.matrix[3][0];

    res.matrix[1][1] = mat1.matrix[1][0] * mat2.matrix[0][1] + mat1.matrix[1][1] * mat2.matrix[1][1]
                       + mat1.matrix[1][2] * mat2.matrix[2][1] + mat1.matrix[1][3] * mat2.matrix[3][1];

    res.matrix[1][2] = mat1.matrix[1][0] * mat2.matrix[0][2] + mat1.matrix[1][1] * mat2.matrix[1][2]
                       + mat1.matrix[1][2] * mat2.matrix[2][2] + mat1.matrix[1][3] * mat2.matrix[3][2];

    res.matrix[1][3] = mat1.matrix[1][0] * mat2.matrix[0][3] + mat1.matrix[1][1] * mat2.matrix[1][3]
                       + mat1.matrix[1][2] * mat2.matrix[2][3] + mat1.matrix[1][3] * mat2.matrix[3][3];


    res.matrix[2][0] = mat1.matrix[2][0] * mat2.matrix[0][0] + mat1.matrix[2][1] * mat2.matrix[1][0]
                       + mat1.matrix[2][2] * mat2.matrix[2][0] + mat1.matrix[2][3] * mat2.matrix[3][0];

    res.matrix[2][1] = mat1.matrix[2][0] * mat2.matrix[0][1] + mat1.matrix[2][1] * mat2.matrix[1][1]
                       + mat1.matrix[2][2] * mat2.matrix[2][1] + mat1.matrix[2][3] * mat2.matrix[3][1];

    res.matrix[2][2] = mat1.matrix[2][0] * mat2.matrix[0][2] + mat1.matrix[2][1] * mat2.matrix[1][2]
                       + mat1.matrix[2][2] * mat2.matrix[2][2] + mat1.matrix[2][3] * mat2.matrix[3][2];

    res.matrix[2][3] = mat1.matrix[2][0] * mat2.matrix[0][3] + mat1.matrix[2][1] * mat2.matrix[1][3]
                       + mat1.matrix[2][2] * mat2.matrix[2][3] + mat1.matrix[2][3] * mat2.matrix[3][3];


    res.matrix[3][0] = mat1.matrix[3][0] * mat2.matrix[0][0] + mat1.matrix[3][1] * mat2.matrix[1][0]
                       + mat1.matrix[3][2] * mat2.matrix[2][0] + mat1.matrix[3][3] * mat2.matrix[3][0];

    res.matrix[3][1] = mat1.matrix[3][0] * mat2.matrix[0][1] + mat1.matrix[3][1] * mat2.matrix[1][1]
                       + mat1.matrix[3][2] * mat2.matrix[2][1] + mat1.matrix[3][3] * mat2.matrix[3][1];

    res.matrix[3][2] = mat1.matrix[3][0] * mat2.matrix[0][2] + mat1.matrix[3][1] * mat2.matrix[1][2]
                       + mat1.matrix[3][2] * mat2.matrix[2][2] + mat1.matrix[3][3] * mat2.matrix[3][2];

    res.matrix[3][3] = mat1.matrix[3][0] * mat2.matrix[0][3] + mat1.matrix[3][1] * mat2.matrix[1][3]
                       + mat1.matrix[3][2] * mat2.matrix[2][3] + mat1.matrix[3][3] * mat2.matrix[3][3];

    return res;
}

inline Mat4 operator*(Mat4 &mat, double scalar)
{
    Mat4 res;
    for (int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            res[i][j] = mat.matrix[i][j] * scalar;
        }
    }

    return res;
}

#endif //HELIOS_MAT4_H
