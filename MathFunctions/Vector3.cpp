#include "Vector3.h"
#include "Matrix4x4.h"
#include <cassert>

float Vector3::operator[](const int index) const noexcept {
    return (&x)[index];
}

float &Vector3::operator[](const int index) noexcept {
    return (&x)[index];
}

Vector3 &Vector3::operator=(const Vector3 &vec) noexcept {
    x = vec.x;
    y = vec.y;
    z = vec.z;
    return *this;
}

Vector3 &Vector3::operator+=(const Vector3 &vec) noexcept {
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

Vector3 &Vector3::operator-=(const Vector3 &vec) noexcept {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}

Vector3 &Vector3::operator*=(const float scalar) noexcept {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3 &Vector3::operator*=(const Vector3 &vec) noexcept {
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    return *this;
}

Vector3 &Vector3::operator/=(const float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

Vector3 &Vector3::operator/=(const Vector3 &vec) {
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;
    return *this;
}

inline constexpr const Vector3 operator-(const Vector3 &vec) noexcept {
    return Vector3(-vec.x, -vec.y, -vec.z);
}

inline constexpr const Vector3 operator+(const Vector3 &vec1, const Vector3 &vec2) noexcept {
    return Vector3(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

inline constexpr const Vector3 operator-(const Vector3 &vec1, const Vector3 &vec2) noexcept {
    return Vector3(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}

inline constexpr const Vector3 operator*(const Vector3 &vec, const float scalar) noexcept {
    return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

inline constexpr const Vector3 operator*(const float scalar, const Vector3 &vec) noexcept {
    return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

inline constexpr const Vector3 operator*(const Vector3 &vec1, const Vector3 &vec2) noexcept {
    return Vector3(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
}

inline constexpr const Vector3 operator/(const Vector3 &vec, const float scalar) {
    return vec * (1.0f / scalar);
}

inline constexpr const Vector3 operator/(const Vector3 &vec1, const Vector3 &vec2) {
    return Vector3(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z);
}

bool Vector3::operator==(const Vector3 &vec) const noexcept {
    return x == vec.x && y == vec.y && z == vec.z;
}

bool Vector3::operator!=(const Vector3 &vec) const noexcept {
    return x != vec.x || y != vec.y || z != vec.z;
}

constexpr float Vector3::Dot(const Vector3 &vec) const noexcept {
    return x * vec.x + y * vec.y + z * vec.z;
}

Vector3 Vector3::Cross(const Vector3 &vec) const noexcept {
    return Vector3(
        y * vec.z - z * vec.y,
        z * vec.x - x * vec.z,
        x * vec.y - y * vec.x
    );
}

float Vector3::Length() const noexcept {
    return std::sqrt(LengthSquared());
}

constexpr float Vector3::LengthSquared() const noexcept {
    return Dot(*this);
}

inline const Vector3 Vector3::Normalize() const {
    const float length = Length();
    if (length == 0.0f) {
        throw std::runtime_error("Vector3::Normalize() : Division by zero");
    }
    return *this / length;
}

inline constexpr const Vector3 Vector3::Projection(const Vector3 &vec) const noexcept {
    return vec * (Dot(vec) / vec.Dot(vec)) * vec;
}

inline constexpr const Vector3 Vector3::Rejection(const Vector3 &vec) const noexcept {
    return *this - Projection(vec);
}

inline constexpr const Vector3 Vector3::Refrection(const Vector3 &normal) const noexcept {
    return *this + (-2.0f * Dot(normal) * normal);
}

inline constexpr const Vector3 Vector3::Refrection(const Vector3 &normal, const float eta) const noexcept {
    const float cosTheta = Dot(normal);
    const float k = 1.0f - eta * eta * (1.0f - cosTheta * cosTheta);
    if (k < 0.0f) {
        return Vector3(0.0f);
    }
    return *this * eta + (eta * cosTheta - std::sqrt(k)) * normal;
}

inline float Vector3::Distance(const Vector3 &vec) const {
    return (vec - *this).Length();
}

Vector3 Vector3::Transform(const Matrix4x4 &mat) const noexcept {
    Vector3 result;
    result.x = x * mat.m[0][0] + y * mat.m[1][0] + z * mat.m[2][0] + 1.0f * mat.m[3][0];
    result.y = x * mat.m[0][1] + y * mat.m[1][1] + z * mat.m[2][1] + 1.0f * mat.m[3][1];
    result.z = x * mat.m[0][2] + y * mat.m[1][2] + z * mat.m[2][2] + 1.0f * mat.m[3][2];
    float w = x * mat.m[0][3] + y * mat.m[1][3] + z * mat.m[2][3] + 1.0f * mat.m[3][3];

    assert(w != 0.0f);

    result.x /= w;
    result.y /= w;
    result.z /= w;

    return result;
}

inline constexpr const Vector3 operator*(const Matrix4x4 &mat, const Vector3 &vec) noexcept {
    return Vector3(
        mat.m[0][0] * vec.x + mat.m[0][1] * vec.y + mat.m[0][2] * vec.z + mat.m[0][3],
        mat.m[1][0] * vec.x + mat.m[1][1] * vec.y + mat.m[1][2] * vec.z + mat.m[1][3],
        mat.m[2][0] * vec.x + mat.m[2][1] * vec.y + mat.m[2][2] * vec.z + mat.m[2][3]
    );
}

inline constexpr const Vector3 operator*(const Vector3 &vec, const Matrix4x4 &mat) noexcept {
    return Vector3(
        vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + mat.m[3][0],
        vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + mat.m[3][1],
        vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + mat.m[3][2]
    );
}