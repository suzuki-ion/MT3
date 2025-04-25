#pragma once
#include "Vector3.h"

struct Sphere;
struct Line;
struct Ray;
struct Segment;

/// @brief 軸平行境界箱
struct AABB {
    AABB() noexcept = default;
    AABB(const Vector3 &min, const Vector3 &max) noexcept;
    AABB(const AABB &aabb) noexcept;

    /// @brief minとmaxを正しくする
    void Sort() noexcept;

    /// @brief AABBとの衝突判定
    /// @param aabb 衝突判定を行うAABB
    /// @return 衝突しているかどうか
    [[nodiscard]] bool IsCollision(const AABB &aabb) const;

    /// @brief 球との衝突判定
    /// @param sphere 衝突判定を行う球
    /// @return 衝突しているかどうか
    [[nodiscard]] bool IsCollision(const Sphere &sphere) const;

    /// @brief 直線との衝突判定
    /// @param line 衝突判定を行う直線
    /// @return 衝突しているかどうか
    [[nodiscard]] bool IsCollision(const Line &line) const;

    /// @brief 半直線との衝突判定
    /// @param ray 衝突判定を行う半直線
    /// @return 衝突しているかどうか
    [[nodiscard]] bool IsCollision(const Ray &ray) const;

    /// @brief 線分との衝突判定
    /// @param segment 衝突判定を行う線分
    /// @return 衝突しているかどうか
    [[nodiscard]] bool IsCollision(const Segment &segment) const;

    /// @brief AABBを描画する
    /// @param viewProjectionMatrix ビュー投影行列
    /// @param viewportMatrix ビューポート行列
    /// @param color 色
    void Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const;

    Vector3 min;
    Vector3 max;
};