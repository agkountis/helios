#ifndef HELIOS_VEC3_H
#define HELIOS_VEC3_H

class Vec3 {
public:
    double x = 0;
    double y = 0;
    double z = 0;

    Vec3() = default;

    Vec3(double x, double y, double z);

    double length();

    double length_squared();

    void normalize();

    Vec3 normalized();
};

inline double dot(const Vec3 &vec1, const Vec3 &vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

inline Vec3 cross(const Vec3 &vec1, const Vec3 &vec2)
{
    return Vec3(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.z);
}

/**
 * Unary operators
 */
inline Vec3 operator-(const Vec3 &vec)
{
    return Vec3(-vec.x, -vec.y, -vec.z);
}
/* ----------------------------------------------------------------- */

/**
 * Binary operators -- Vector (op) Scalar -- Scalar (op) Vector
 */
inline Vec3 operator*(const Vec3 &vec, double scalar)
{
    return Vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

inline Vec3 operator*(double scalar, const Vec3 &vec)
{
    return Vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

inline Vec3 operator/(const Vec3 &vec, double scalar)
{
    return Vec3(vec.x / scalar, vec.y / scalar, vec.z / scalar);
}

inline Vec3 operator/(double scalar, const Vec3 &vec)
{
    return Vec3(vec.x / scalar, vec.y / scalar, vec.z / scalar);
}

inline Vec3 operator+(const Vec3 &vec, double scalar)
{
    return Vec3(vec.x + scalar, vec.y + scalar, vec.z + scalar);
}
/* ----------------------------------------------------------------- */

/**
 * Binary operators -- Vector (op) Vector
 */
inline Vec3 operator+(const Vec3 &vec1, const Vec3 &vec2)
{
    return Vec3(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

inline Vec3 operator-(const Vec3 & vec1, const Vec3 &vec2)
{
    return Vec3(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}

#endif //HELIOS_VEC3_H
