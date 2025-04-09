#pragma once
#include <stdexcept>
#include <cmath>

struct Matrix4x4 {
    // ��ʂɌĂяo�����ł��낤�f�t�H���g�R���X�g���N�^�͌y�ʉ��̂��߉������Ȃ��悤�ɂ��Ă���
    Matrix4x4() noexcept = default;
    constexpr Matrix4x4(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33) noexcept
        : m{
            {m00, m01, m02, m03},
            {m10, m11, m12, m13},
            {m20, m21, m22, m23},
            {m30, m31, m32, m33}
        }
    {}

    // �s�񎮌v�Z�p��2x2�s��
    struct Matrix2x2 {
        constexpr Matrix2x2(float m00, float m01, float m10, float m11) noexcept
            : m{
                {m00, m01},
                {m10, m11}
            }
        {}

        constexpr float Determinant() const noexcept {
            return m[0][0] * m[1][1] - m[0][1] * m[1][0];
        }

    private:
        float m[2][2];
    };

    // �s�񎮌v�Z�p��3x3�s��
    struct Matrix3x3 {
        constexpr Matrix3x3(
            float m00, float m01, float m02,
            float m10, float m11, float m12,
            float m20, float m21, float m22) noexcept
            : m{
                {m00, m01, m02},
                {m10, m11, m12},
                {m20, m21, m22}
            }
        {}

        constexpr float Determinant() const noexcept {
            float c00 = Matrix2x2(m[1][1], m[1][2], m[2][1], m[2][2]).Determinant();
            float c01 = -(Matrix2x2(m[1][0], m[1][2], m[2][0], m[2][2]).Determinant());
            float c02 = Matrix2x2(m[1][0], m[1][1], m[2][0], m[2][1]).Determinant();
            return m[0][0] * c00 + m[0][1] * c01 + m[0][2] * c02;
        }

    private:
        float m[3][3];
    };

    Matrix4x4 &operator+=(const Matrix4x4 &mat) noexcept {
        // �����ł����x���҂����߂Ƀ��[�v�ł͂Ȃ��W�J����
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
    Matrix4x4 &operator-=(const Matrix4x4 &mat) noexcept {
        // �����ł����x���҂����߂Ƀ��[�v�ł͂Ȃ��W�J����
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
    Matrix4x4 &operator*=(const float scalar) noexcept {
        // �����ł����x���҂����߂Ƀ��[�v�ł͂Ȃ��W�J����
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
    Matrix4x4 &operator*=(const Matrix4x4 &mat) noexcept {
        *this = *this * mat;
        return *this;
    }

    constexpr const Matrix4x4 operator+(const Matrix4x4 &mat) const noexcept {
        // �����ł����x���҂����߂Ƀ��[�v�ł͂Ȃ��W�J����
        return Matrix4x4(
            m[0][0] + mat.m[0][0], m[0][1] + mat.m[0][1], m[0][2] + mat.m[0][2], m[0][3] + mat.m[0][3],
            m[1][0] + mat.m[1][0], m[1][1] + mat.m[1][1], m[1][2] + mat.m[1][2], m[1][3] + mat.m[1][3],
            m[2][0] + mat.m[2][0], m[2][1] + mat.m[2][1], m[2][2] + mat.m[2][2], m[2][3] + mat.m[2][3],
            m[3][0] + mat.m[3][0], m[3][1] + mat.m[3][1], m[3][2] + mat.m[3][2], m[3][3] + mat.m[3][3]
        );
    }
    constexpr const Matrix4x4 operator-(const Matrix4x4 &mat) const noexcept {
        // �����ł����x���҂����߂Ƀ��[�v�ł͂Ȃ��W�J����
        return Matrix4x4(
            m[0][0] - mat.m[0][0], m[0][1] - mat.m[0][1], m[0][2] - mat.m[0][2], m[0][3] - mat.m[0][3],
            m[1][0] - mat.m[1][0], m[1][1] - mat.m[1][1], m[1][2] - mat.m[1][2], m[1][3] - mat.m[1][3],
            m[2][0] - mat.m[2][0], m[2][1] - mat.m[2][1], m[2][2] - mat.m[2][2], m[2][3] - mat.m[2][3],
            m[3][0] - mat.m[3][0], m[3][1] - mat.m[3][1], m[3][2] - mat.m[3][2], m[3][3] - mat.m[3][3]
        );
    }
    constexpr const Matrix4x4 operator*(const float scalar) const noexcept {
        // �����ł����x���҂����߂Ƀ��[�v�ł͂Ȃ��W�J����
        return Matrix4x4(
            m[0][0] * scalar, m[0][1] * scalar, m[0][2] * scalar, m[0][3] * scalar,
            m[1][0] * scalar, m[1][1] * scalar, m[1][2] * scalar, m[1][3] * scalar,
            m[2][0] * scalar, m[2][1] * scalar, m[2][2] * scalar, m[2][3] * scalar,
            m[3][0] * scalar, m[3][1] * scalar, m[3][2] * scalar, m[3][3] * scalar
        );
    }
    constexpr const Matrix4x4 operator*(const Matrix4x4 &mat) const noexcept {
        // �����ł����x���҂����߂Ƀ��[�v�ł͂Ȃ��W�J����
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

    /// @brief �P�ʍs����擾����
    /// @return �P�ʍs��
    [[nodiscard]] inline static constexpr const Matrix4x4 Identity() noexcept {
        return Matrix4x4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }
    /// @brief �]�u�s����擾����
    /// @return �]�u�s��
    [[nodiscard]] inline static constexpr const Matrix4x4 Transpose(const Matrix4x4 &mat) noexcept {
        return Matrix4x4(
            mat.m[0][0], mat.m[1][0], mat.m[2][0], mat.m[3][0],
            mat.m[0][1], mat.m[1][1], mat.m[2][1], mat.m[3][1],
            mat.m[0][2], mat.m[1][2], mat.m[2][2], mat.m[3][2],
            mat.m[0][3], mat.m[1][3], mat.m[2][3], mat.m[3][3]
        );
    }
    /// @brief �s�񎮂��v�Z����
    /// @return �s��
    [[nodiscard]] constexpr const float Determinant() const noexcept {
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
    /// @brief �t�s����v�Z����
    /// @return �t�s��
    [[nodiscard]] inline const Matrix4x4 Inverse() const {
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

    float m[4][4];
};

inline constexpr const Matrix4x4 operator*(const float scalar, const Matrix4x4 &mat) noexcept {
    return mat * scalar;
}

