#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"

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