#include "Matrix4x4.h"
#include "Vector3.h"

constexpr float Matrix4x4::Matrix2x2::Determinant() const noexcept {
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

constexpr float Matrix4x4::Matrix3x3::Determinant() const noexcept {
    float c00 = Matrix2x2(m[1][1], m[1][2], m[2][1], m[2][2]).Determinant();
    float c01 = -(Matrix2x2(m[1][0], m[1][2], m[2][0], m[2][2]).Determinant());
    float c02 = Matrix2x2(m[1][0], m[1][1], m[2][0], m[2][1]).Determinant();
    return m[0][0] * c00 + m[0][1] * c01 + m[0][2] * c02;
}

Matrix4x4 &Matrix4x4::operator+=(const Matrix4x4 &mat) noexcept {
    // 少しでも速度を稼ぐためにループではなく展開する
    m[0][0] += mat.m[0][0];
    m[0][1] += mat.m[0][1];
    m[0][2] += mat.m[0][2];
    m[0][3] += mat.m[0][3];

    m[1][0] += mat.m[1][0];
    m[1][1] += mat.m[1][1];
    m[1][2] += mat.m[1][2];
    m[1][3] += mat.m[1][3];

    m[2][0] += mat.m[2][0];
    m[2][1] += mat.m[2][1];
    m[2][2] += mat.m[2][2];
    m[2][3] += mat.m[2][3];

    m[3][0] += mat.m[3][0];
    m[3][1] += mat.m[3][1];
    m[3][2] += mat.m[3][2];
    m[3][3] += mat.m[3][3];

    return *this;
}

Matrix4x4 &Matrix4x4::operator-=(const Matrix4x4 &mat) noexcept {
    // 少しでも速度を稼ぐためにループではなく展開する
    m[0][0] -= mat.m[0][0];
    m[0][1] -= mat.m[0][1];
    m[0][2] -= mat.m[0][2];
    m[0][3] -= mat.m[0][3];

    m[1][0] -= mat.m[1][0];
    m[1][1] -= mat.m[1][1];
    m[1][2] -= mat.m[1][2];
    m[1][3] -= mat.m[1][3];

    m[2][0] -= mat.m[2][0];
    m[2][1] -= mat.m[2][1];
    m[2][2] -= mat.m[2][2];
    m[2][3] -= mat.m[2][3];

    m[3][0] -= mat.m[3][0];
    m[3][1] -= mat.m[3][1];
    m[3][2] -= mat.m[3][2];
    m[3][3] -= mat.m[3][3];

    return *this;
}

Matrix4x4 &Matrix4x4::operator*=(const float scalar) noexcept {
    // 少しでも速度を稼ぐためにループではなく展開する
    m[0][0] *= scalar;
    m[0][1] *= scalar;
    m[0][2] *= scalar;
    m[0][3] *= scalar;

    m[1][0] *= scalar;
    m[1][1] *= scalar;
    m[1][2] *= scalar;
    m[1][3] *= scalar;

    m[2][0] *= scalar;
    m[2][1] *= scalar;
    m[2][2] *= scalar;
    m[2][3] *= scalar;

    m[3][0] *= scalar;
    m[3][1] *= scalar;
    m[3][2] *= scalar;
    m[3][3] *= scalar;

    return *this;
}

Matrix4x4 &Matrix4x4::operator*=(const Matrix4x4 &mat) noexcept {
    *this = *this * mat;
    return *this;
}

constexpr const Matrix4x4 Matrix4x4::operator+(const Matrix4x4 &mat) const noexcept {
    // 少しでも速度を稼ぐためにループではなく展開する
    return Matrix4x4(
        m[0][0] + mat.m[0][0], m[0][1] + mat.m[0][1], m[0][2] + mat.m[0][2], m[0][3] + mat.m[0][3],
        m[1][0] + mat.m[1][0], m[1][1] + mat.m[1][1], m[1][2] + mat.m[1][2], m[1][3] + mat.m[1][3],
        m[2][0] + mat.m[2][0], m[2][1] + mat.m[2][1], m[2][2] + mat.m[2][2], m[2][3] + mat.m[2][3],
        m[3][0] + mat.m[3][0], m[3][1] + mat.m[3][1], m[3][2] + mat.m[3][2], m[3][3] + mat.m[3][3]
    );
}

constexpr const Matrix4x4 Matrix4x4::operator-(const Matrix4x4 &mat) const noexcept {
    // 少しでも速度を稼ぐためにループではなく展開する
    return Matrix4x4(
        m[0][0] - mat.m[0][0], m[0][1] - mat.m[0][1], m[0][2] - mat.m[0][2], m[0][3] - mat.m[0][3],
        m[1][0] - mat.m[1][0], m[1][1] - mat.m[1][1], m[1][2] - mat.m[1][2], m[1][3] - mat.m[1][3],
        m[2][0] - mat.m[2][0], m[2][1] - mat.m[2][1], m[2][2] - mat.m[2][2], m[2][3] - mat.m[2][3],
        m[3][0] - mat.m[3][0], m[3][1] - mat.m[3][1], m[3][2] - mat.m[3][2], m[3][3] - mat.m[3][3]
    );
}

constexpr const Matrix4x4 Matrix4x4::operator*(const float scalar) const noexcept {
    // 少しでも速度を稼ぐためにループではなく展開する
    return Matrix4x4(
        m[0][0] * scalar, m[0][1] * scalar, m[0][2] * scalar, m[0][3] * scalar,
        m[1][0] * scalar, m[1][1] * scalar, m[1][2] * scalar, m[1][3] * scalar,
        m[2][0] * scalar, m[2][1] * scalar, m[2][2] * scalar, m[2][3] * scalar,
        m[3][0] * scalar, m[3][1] * scalar, m[3][2] * scalar, m[3][3] * scalar
    );
}

constexpr const Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &mat) const noexcept {
    // 少しでも速度を稼ぐためにループではなく展開する
    return Matrix4x4(
        m[0][0] * mat.m[0][0] + m[0][1] * mat.m[1][0] + m[0][2] * mat.m[2][0] + m[0][3] * mat.m[3][0],
        m[0][0] * mat.m[0][1] + m[0][1] * mat.m[1][1] + m[0][2] * mat.m[2][1] + m[0][3] * mat.m[3][1],
        m[0][0] * mat.m[0][2] + m[0][1] * mat.m[1][2] + m[0][2] * mat.m[2][2] + m[0][3] * mat.m[3][2],
        m[0][0] * mat.m[0][3] + m[0][1] * mat.m[1][3] + m[0][2] * mat.m[2][3] + m[0][3] * mat.m[3][3],
        m[1][0] * mat.m[0][0] + m[1][1] * mat.m[1][0] + m[1][2] * mat.m[2][0] + m[1][3] * mat.m[3][0],
        m[1][0] * mat.m[0][1] + m[1][1] * mat.m[1][1] + m[1][2] * mat.m[2][1] + m[1][3] * mat.m[3][1],
        m[1][0] * mat.m[0][2] + m[1][1] * mat.m[1][2] + m[1][2] * mat.m[2][2] + m[1][3] * mat.m[3][2],
        m[1][0] * mat.m[0][3] + m[1][1] * mat.m[1][3] + m[1][2] * mat.m[2][3] + m[1][3] * mat.m[3][3],
        m[2][0] * mat.m[0][0] + m[2][1] * mat.m[1][0] + m[2][2] * mat.m[2][0] + m[2][3] * mat.m[3][0],
        m[2][0] * mat.m[0][1] + m[2][1] * mat.m[1][1] + m[2][2] * mat.m[2][1] + m[2][3] * mat.m[3][1],
        m[2][0] * mat.m[0][2] + m[2][1] * mat.m[1][2] + m[2][2] * mat.m[2][2] + m[2][3] * mat.m[3][2],
        m[2][0] * mat.m[0][3] + m[2][1] * mat.m[1][3] + m[2][2] * mat.m[2][3] + m[2][3] * mat.m[3][3],
        m[3][0] * mat.m[0][0] + m[3][1] * mat.m[1][0] + m[3][2] * mat.m[2][0] + m[3][3] * mat.m[3][0],
        m[3][0] * mat.m[0][1] + m[3][1] * mat.m[1][1] + m[3][2] * mat.m[2][1] + m[3][3] * mat.m[3][1],
        m[3][0] * mat.m[0][2] + m[3][1] * mat.m[1][2] + m[3][2] * mat.m[2][2] + m[3][3] * mat.m[3][2],
        m[3][0] * mat.m[0][3] + m[3][1] * mat.m[1][3] + m[3][2] * mat.m[2][3] + m[3][3] * mat.m[3][3]
    );
}

inline constexpr const Matrix4x4 operator*(const float scalar, const Matrix4x4 &mat) noexcept {
    return mat * scalar;
}

inline constexpr const Matrix4x4 Matrix4x4::Identity() noexcept {
    return Matrix4x4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

constexpr const Matrix4x4 Matrix4x4::Transpose() noexcept {
    return Matrix4x4(
        m[0][0], m[1][0], m[2][0], m[3][0],
        m[0][1], m[1][1], m[2][1], m[3][1],
        m[0][2], m[1][2], m[2][2], m[3][2],
        m[0][3], m[1][3], m[2][3], m[3][3]
    );
}

constexpr const float Matrix4x4::Determinant() const noexcept {
    float c00 = Matrix3x3(
        m[1][1], m[1][2], m[1][3],
        m[2][1], m[2][2], m[2][3],
        m[3][1], m[3][2], m[3][3]).Determinant();
    float c01 = -(Matrix3x3(
        m[1][0], m[1][2], m[1][3],
        m[2][0], m[2][2], m[2][3],
        m[3][0], m[3][2], m[3][3]).Determinant());
    float c02 = Matrix3x3(
        m[1][0], m[1][1], m[1][3],
        m[2][0], m[2][1], m[2][3],
        m[3][0], m[3][1], m[3][3]).Determinant();
    float c03 = -(Matrix3x3(
        m[1][0], m[1][1], m[1][2],
        m[2][0], m[2][1], m[2][2],
        m[3][0], m[3][1], m[3][2]).Determinant());
    return (m[0][0] * c00) + (m[0][1] * c01) + (m[0][2] * c02) + (m[0][3] * c03);
}

inline const Matrix4x4 Matrix4x4::Inverse() const {
    float c00 = Matrix3x3(
        m[1][1], m[1][2], m[1][3],
        m[2][1], m[2][2], m[2][3],
        m[3][1], m[3][2], m[3][3]).Determinant();
    float c01 = -(Matrix3x3(
        m[1][0], m[1][2], m[1][3],
        m[2][0], m[2][2], m[2][3],
        m[3][0], m[3][2], m[3][3]).Determinant());
    float c02 = Matrix3x3(
        m[1][0], m[1][1], m[1][3],
        m[2][0], m[2][1], m[2][3],
        m[3][0], m[3][1], m[3][3]).Determinant();
    float c03 = -(Matrix3x3(
        m[1][0], m[1][1], m[1][2],
        m[2][0], m[2][1], m[2][2],
        m[3][0], m[3][1], m[3][2]).Determinant());

    float c10 = -(Matrix3x3(
        m[0][1], m[0][2], m[0][3],
        m[2][1], m[2][2], m[2][3],
        m[3][1], m[3][2], m[3][3]).Determinant());
    float c11 = Matrix3x3(
        m[0][0], m[0][2], m[0][3],
        m[2][0], m[2][2], m[2][3],
        m[3][0], m[3][2], m[3][3]).Determinant();
    float c12 = -(Matrix3x3(
        m[0][0], m[0][1], m[0][3],
        m[2][0], m[2][1], m[2][3],
        m[3][0], m[3][1], m[3][3]).Determinant());
    float c13 = Matrix3x3(
        m[0][0], m[0][1], m[0][2],
        m[2][0], m[2][1], m[2][2],
        m[3][0], m[3][1], m[3][2]).Determinant();

    float c20 = Matrix3x3(
        m[0][1], m[0][2], m[0][3],
        m[1][1], m[1][2], m[1][3],
        m[3][1], m[3][2], m[3][3]).Determinant();
    float c21 = -(Matrix3x3(
        m[0][0], m[0][2], m[0][3],
        m[1][0], m[1][2], m[1][3],
        m[3][0], m[3][2], m[3][3]).Determinant());
    float c22 = Matrix3x3(
        m[0][0], m[0][1], m[0][3],
        m[1][0], m[1][1], m[1][3],
        m[3][0], m[3][1], m[3][3]).Determinant();
    float c23 = -(Matrix3x3(
        m[0][0], m[0][1], m[0][2],
        m[1][0], m[1][1], m[1][2],
        m[3][0], m[3][1], m[3][2]).Determinant());

    float c30 = -(Matrix3x3(
        m[0][1], m[0][2], m[0][3],
        m[1][1], m[1][2], m[1][3],
        m[2][1], m[2][2], m[2][3]).Determinant());
    float c31 = Matrix3x3(
        m[0][0], m[0][2], m[0][3],
        m[1][0], m[1][2], m[1][3],
        m[2][0], m[2][2], m[2][3]).Determinant();
    float c32 = -(Matrix3x3(
        m[0][0], m[0][1], m[0][3],
        m[1][0], m[1][1], m[1][3],
        m[2][0], m[2][1], m[2][3]).Determinant());
    float c33 = Matrix3x3(
        m[0][0], m[0][1], m[0][2],
        m[1][0], m[1][1], m[1][2],
        m[2][0], m[2][1], m[2][2]).Determinant();

    float det = 1.0f / (m[0][0] * c00 + m[0][1] * c01 + m[0][2] * c02 + m[0][3] * c03);

    return Matrix4x4(
        c00 * det, c10 * det, c20 * det, c30 * det,
        c01 * det, c11 * det, c21 * det, c31 * det,
        c02 * det, c12 * det, c22 * det, c32 * det,
        c03 * det, c13 * det, c23 * det, c33 * det
    );
}

Matrix4x4 Matrix4x4::MakeTranslate(const Vector3 &translate) noexcept {
    return Matrix4x4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        translate.x, translate.y, translate.z, 1.0f
    );
}

Matrix4x4 Matrix4x4::MakeScale(const Vector3 &scale) noexcept {
    return Matrix4x4(
        scale.x, 0.0f, 0.0f, 0.0f,
        0.0f, scale.y, 0.0f, 0.0f,
        0.0f, 0.0f, scale.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

Matrix4x4 Matrix4x4::MakeRotate(const Vector3 &rotate) noexcept {
    return MakeRotateX(rotate.x) * MakeRotateY(rotate.y) * MakeRotateZ(rotate.z);
}

Matrix4x4 Matrix4x4::MakeRotate(const float radianX, const float radianY, const float radianZ) noexcept {
    return MakeRotateX(radianX) * MakeRotateY(radianY) * MakeRotateZ(radianZ);
}

Matrix4x4 Matrix4x4::MakeRotateX(const float radian) noexcept {
    return Matrix4x4(
        1.0f,   0.0f,               0.0f,               0.0f,
        0.0f,   std::cos(radian),   std::sin(radian),   0.0f,
        0.0f,   -std::sin(radian),  std::cos(radian),   0.0f,
        0.0f,   0.0f,               0.0f,               1.0f
    );
}

Matrix4x4 Matrix4x4::MakeRotateY(const float radian) noexcept {
    return Matrix4x4(
        std::cos(radian),   0.0f,   -std::sin(radian),  0.0f,
        0.0f,               1.0f,   0.0f,               0.0f,
        std::sin(radian),   0.0f,   std::cos(radian),   0.0f,
        0.0f,               0.0f,   0.0f,               1.0f
    );
}

Matrix4x4 Matrix4x4::MakeRotateZ(const float radian) noexcept {
    return Matrix4x4(
        std::cos(radian),   std::sin(radian),   0.0f,   0.0f,
        -std::sin(radian),  std::cos(radian),   0.0f,   0.0f,
        0.0f,               0.0f,               1.0f,   0.0f,
        0.0f,               0.0f,               0.0f,   1.0f
    );
}

