#ifndef HELIOS_VEC3_H
#define HELIOS_VEC3_H

class Mat4;

class Vec3 {
public:
    float x = 0;
    float y = 0;
    float z = 0;

    Vec3() = default;

    Vec3(float x, float y, float z) : x(x), y(y), z(z)
    { }

    float length();

    float length_squared();

    void normalize();

    Vec3 normalized();

    void transform(const Mat4 &matrix);
};

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
inline Vec3 operator*(const Vec3 &vec, float scalar)
{
    return Vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

inline Vec3 operator*(float scalar, const Vec3 &vec)
{
    return Vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

inline Vec3 operator/(const Vec3 &vec, float scalar)
{
    return Vec3(vec.x / scalar, vec.y / scalar, vec.z / scalar);
}

inline Vec3 operator/(float scalar, const Vec3 &vec)
{
    return Vec3(vec.x / scalar, vec.y / scalar, vec.z / scalar);
}

inline Vec3 operator+(const Vec3 &vec, float scalar)
{
    return Vec3(vec.x + scalar, vec.y + scalar, vec.z + scalar);
}

inline void operator+=(Vec3 &vec, float scalar)
{
    vec.x += scalar;
    vec.y += scalar;
    vec.z += scalar;
}

inline void operator-=(Vec3 &vec, float scalar)
{
    vec.x -= scalar;
    vec.y -= scalar;
    vec.z -= scalar;
}

inline void operator*=(Vec3 &vec, float scalar)
{
    vec.x *= scalar;
    vec.y *= scalar;
    vec.z *= scalar;
}

inline void operator/=(Vec3 &vec, float scalar)
{
    vec.x /= scalar;
    vec.y /= scalar;
    vec.z /= scalar;
}
/* ----------------------------------------------------------------- */

/**
 * Binary operators -- Vector (op) Vector
 */
inline Vec3 operator+(const Vec3 &vec1, const Vec3 &vec2)
{
    return Vec3(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

inline Vec3 operator-(const Vec3 &vec1, const Vec3 &vec2)
{
    return Vec3(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}

inline Vec3 operator*(const Vec3 &vec1, const Vec3 &vec2)
{
    return Vec3(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
}

inline void operator+=(Vec3 &vec1, const Vec3 &vec2)
{
    vec1.x += vec2.x;
    vec1.y += vec2.y;
    vec1.z += vec2.z;
}

inline void operator-=(Vec3 &vec1, const Vec3 &vec2)
{
    vec1.x -= vec2.x;
    vec1.y -= vec2.y;
    vec1.z -= vec2.z;
}

inline void operator*=(Vec3 &vec1, const Vec3 &vec2)
{
    vec1.x *= vec2.x;
    vec1.y *= vec2.y;
    vec1.z *= vec2.z;
}

inline void operator/=(Vec3 &vec1, const Vec3 &vec2)
{
    vec1.x /= vec2.x;
    vec1.y /= vec2.y;
    vec1.z /= vec2.z;
}
/* ----------------------------------------------------------------- */

inline float dot(const Vec3 &vec1, const Vec3 &vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

inline Vec3 cross(const Vec3 &vec1, const Vec3 &vec2)
{
    return Vec3(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z,
                vec1.x * vec2.y - vec1.y * vec2.x);
}

inline Vec3 reflect(const Vec3 &vec, const Vec3 &normal)
{
    // use this so that we won't have to negate the result later normal - 2 * dot(vec, normal) * vec
    return vec - 2 * dot(vec, normal) * normal;
}

#endif //HELIOS_VEC3_H
