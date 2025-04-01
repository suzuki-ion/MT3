#pragma once
#include <stdexcept>
#include <cmath>

struct Vector3 {
public:
    // ��ʂɌĂяo�����ł��낤�f�t�H���g�R���X�g���N�^�͌y�ʉ��̂��߉������Ȃ��悤�ɂ��Ă���
    Vector3() noexcept = default;

    constexpr Vector3(float x, float y, float z) noexcept : x(x), y(y), z(z) {}
    explicit constexpr Vector3(float v) noexcept : x(v), y(v), z(v) {}
    Vector3(const Vector3 &vec) : x(vec.x), y(vec.y), z(vec.z) {}

    Vector3 &operator=(const Vector3 &vec) noexcept {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        return *this;
    }

    float operator[](const int index) const noexcept {
        return (&x)[index];
    }

    float &operator[](const int index) noexcept {
        return (&x)[index];
    }

    Vector3 &operator+=(const Vector3 &vec) noexcept {
        x += vec.x;
        y += vec.y;
        z += vec.z;
        return *this;
    }

    Vector3 &operator-=(const Vector3 &vec) noexcept {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;
        return *this;
    }

    Vector3 &operator*=(const float scalar) noexcept {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vector3 &operator*=(const Vector3 &vec) noexcept {
        x *= vec.x;
        y *= vec.y;
        z *= vec.z;
        return *this;
    }

    Vector3 &operator/=(const float scalar) {
        return *this *= (1.0f / scalar);
    }

    Vector3 &operator/=(const Vector3 &vec) {
        x /= vec.x;
        y /= vec.y;
        z /= vec.z;
        return *this;
    }

    bool operator==(const Vector3 &vec) const noexcept {
        return x == vec.x && y == vec.y && z == vec.z;
    }

    bool operator!=(const Vector3 &vec) const noexcept {
        return x != vec.x || y != vec.y || z != vec.z;
    }

    /// @brief �x�N�g���̓��ς��v�Z����
    /// @param vec ���ς��v�Z����x�N�g��
    /// @return ����
    [[nodiscard]] constexpr float Dot(const Vector3 &vec) const noexcept {
        return x * vec.x + y * vec.y + z * vec.z;
    }

    /// @brief �x�N�g���̊O�ς��v�Z����
    /// @param vec �O�ς��v�Z����x�N�g��
    /// @return �O��
    [[nodiscard]] constexpr const Vector3 Cross(const Vector3 &vec) const noexcept {
        return Vector3(
            y * vec.z - z * vec.y,
            z * vec.x - x * vec.z,
            x * vec.y - y * vec.x
        );
    }

    /// @brief �x�N�g���̒������v�Z����
    /// @return �x�N�g���̒���
    [[nodiscard]] float Length() const noexcept {
        return std::sqrt(LengthSquared());
    }

    /// @brief �x�N�g���̒����̓����v�Z����
    /// @return �x�N�g���̒����̓��
    [[nodiscard]] constexpr float LengthSquared() const noexcept {
        return Dot(*this);
    }

    /// @brief �v�f�����ׂ�0�ł��邩�𔻒肷��
    /// @return true:���ׂĂ̗v�f��0�ł��� false:����ȊO
    [[nodiscard]] constexpr bool IsZero() const noexcept {
        return x == 0.0f && y == 0.0f && z == 0.0f;
    }

    /// @brief �v�f�����ׂ�NaN�ł��邩�𔻒肷��
    /// @return true:���ׂĂ̗v�f��NaN�ł��� false:����ȊO
    [[nodiscard]] constexpr bool IsNaN() const noexcept {
        return std::isnan(x) || std::isnan(y) || std::isnan(z);
    }

    /// @brief �x�N�g���𐳋K������
    /// @return ���K�����ꂽ�x�N�g��
    [[nodiscard]] inline const Vector3 Normalize() const;

    /// @brief �x�N�g�����ˉe����
    /// @param vec �ˉe����x�N�g��
    /// @return �ˉe���ꂽ�x�N�g��
    [[nodiscard]] inline constexpr const Vector3 Projection(const Vector3 &vec) const noexcept;
    
    /// @brief ���������߂�
    /// @param vec ���������߂�x�N�g��
    /// @return ����
    [[nodiscard]] inline constexpr const Vector3 Rejection(const Vector3 &vec) const noexcept;

    /// @brief �x�N�g���𔽎˂���
    /// @param normal �@���x�N�g��
    /// @return ���˂��ꂽ�x�N�g��
    [[nodiscard]] inline constexpr const Vector3 Refrection(const Vector3 &normal) const noexcept;
    
    /// @brief �x�N�g���𔽎˂���
    /// @param normal �@���x�N�g��
    /// @param eta ���ܗ�
    /// @return ���˂��ꂽ�x�N�g��
    [[nodiscard]] inline constexpr const Vector3 Refrection(const Vector3 &normal, const float eta) const noexcept;

    /// @brief �x�N�g���Ԃ̋������v�Z����
    /// @param vec �������v�Z����x�N�g��
    /// @return �x�N�g���Ԃ̋���
    [[nodiscard]] inline float Distance(const Vector3 &vec) const;

    float x;
    float y;
    float z;
};

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
    const float cos_theta = Dot(normal);
    const float k = 1.0f - eta * eta * (1.0f - cos_theta * cos_theta);
    if (k < 0.0f) {
        return Vector3(0.0f);
    }
    return *this * eta + (eta * cos_theta - std::sqrt(k)) * normal;
}

inline float Vector3::Distance(const Vector3 &vec) const {
    return (vec - *this).Length();
}