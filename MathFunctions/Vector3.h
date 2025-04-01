#pragma once
#include <stdexcept>
#include <cmath>

struct Vector3 {
public:
    // 大量に呼び出されるであろうデフォルトコンストラクタは軽量化のため何もしないようにしておく
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

    /// @brief ベクトルの内積を計算する
    /// @param vec 内積を計算するベクトル
    /// @return 内積
    [[nodiscard]] constexpr float Dot(const Vector3 &vec) const noexcept {
        return x * vec.x + y * vec.y + z * vec.z;
    }

    /// @brief ベクトルの外積を計算する
    /// @param vec 外積を計算するベクトル
    /// @return 外積
    [[nodiscard]] constexpr const Vector3 Cross(const Vector3 &vec) const noexcept {
        return Vector3(
            y * vec.z - z * vec.y,
            z * vec.x - x * vec.z,
            x * vec.y - y * vec.x
        );
    }

    /// @brief ベクトルの長さを計算する
    /// @return ベクトルの長さ
    [[nodiscard]] float Length() const noexcept {
        return std::sqrt(LengthSquared());
    }

    /// @brief ベクトルの長さの二乗を計算する
    /// @return ベクトルの長さの二乗
    [[nodiscard]] constexpr float LengthSquared() const noexcept {
        return Dot(*this);
    }

    /// @brief 要素がすべて0であるかを判定する
    /// @return true:すべての要素が0である false:それ以外
    [[nodiscard]] constexpr bool IsZero() const noexcept {
        return x == 0.0f && y == 0.0f && z == 0.0f;
    }

    /// @brief 要素がすべてNaNであるかを判定する
    /// @return true:すべての要素がNaNである false:それ以外
    [[nodiscard]] constexpr bool IsNaN() const noexcept {
        return std::isnan(x) || std::isnan(y) || std::isnan(z);
    }

    /// @brief ベクトルを正規化する
    /// @return 正規化されたベクトル
    [[nodiscard]] inline const Vector3 Normalize() const;

    /// @brief ベクトルを射影する
    /// @param vec 射影するベクトル
    /// @return 射影されたベクトル
    [[nodiscard]] inline constexpr const Vector3 Projection(const Vector3 &vec) const noexcept;
    
    /// @brief 垂線を求める
    /// @param vec 垂線を求めるベクトル
    /// @return 垂線
    [[nodiscard]] inline constexpr const Vector3 Rejection(const Vector3 &vec) const noexcept;

    /// @brief ベクトルを反射する
    /// @param normal 法線ベクトル
    /// @return 反射されたベクトル
    [[nodiscard]] inline constexpr const Vector3 Refrection(const Vector3 &normal) const noexcept;
    
    /// @brief ベクトルを反射する
    /// @param normal 法線ベクトル
    /// @param eta 屈折率
    /// @return 反射されたベクトル
    [[nodiscard]] inline constexpr const Vector3 Refrection(const Vector3 &normal, const float eta) const noexcept;

    /// @brief ベクトル間の距離を計算する
    /// @param vec 距離を計算するベクトル
    /// @return ベクトル間の距離
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