#pragma once
#include "Vector3.h"

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
    [[nodiscard]] bool IsCollision(const AABB &aabb) const noexcept;

    /// @brief AABBを描画する
    /// @param viewProjectionMatrix ビュー投影行列
    /// @param viewportMatrix ビューポート行列
    /// @param color 色
    void Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const noexcept;

    Vector3 min;
    Vector3 max;
};