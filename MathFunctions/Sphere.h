#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"

struct Plane;

struct Sphere {
    Sphere() noexcept : center{ 0.0f, 0.0f, 0.0f }, radius(1.0f) {}
    Sphere(const Vector3 &center, float radius) noexcept :
        center(center), radius(radius)
    {}
    Sphere(const Sphere &sphere) noexcept :
        center(sphere.center), radius(sphere.radius)
    {}

    /// @brief 弾との衝突判定
    /// @param sphere 衝突判定を行う球
    /// @return 衝突しているかどうか
    [[nodiscard]] bool IsCollision(const Sphere &sphere) const;

    /// @brief 平面との衝突判定
    /// @param plane 衝突判定を行う平面
    /// @return 衝突しているかどうか
    [[nodiscard]] bool IsCollision(const Plane &plane) const;

    /// @brief 球を描画する
    /// @param viewProjectionMatrix ビュー投影行列
    /// @param viewportMatrix ビューポート行列
    /// @param kSubdivision 分割数
    /// @param color 色
    void Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int kSubdivision, const unsigned int color) const;

    Vector3 center;
    float radius;
};