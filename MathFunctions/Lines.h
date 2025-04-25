#pragma once
#include "Vector3.h"

struct Matrix4x4;
struct Plane;
struct Triangle;

/// @brief 直線
struct Line {
    // 始点
    Vector3 origin;
    // 終点への差分ベクトル
    Vector3 diff;

    /// @brief 平面との衝突判定
    /// @param plane 衝突判定を行う平面
    /// @return 衝突しているかどうか
    [[nodiscard]] bool IsCollision(const Plane &plane) const;

    /// @brief 三角形との衝突判定
    /// @param triangle 衝突判定を行う三角形
    /// @return 衝突しているかどうか
    [[nodiscard]] bool IsCollision(const Triangle &triangle) const;

    /// @brief 線分を描画する
    /// @param viewProjectionMatrix ビュー投影行列
    /// @param viewportMatrix ビューポート行列
    /// @param color 色
    void Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const;
};

/// @brief 半直線
struct Ray {
    // 始点
    Vector3 origin;
    // 終点への差分ベクトル
    Vector3 diff;

    /// @brief 平面との衝突判定
    /// @param plane 衝突判定を行う平面
    /// @return 衝突しているかどうか
    [[nodiscard]] bool IsCollision(const Plane &plane) const;

    /// @brief 三角形との衝突判定
    /// @param triangle 衝突判定を行う三角形
    /// @return 衝突しているかどうか
    [[nodiscard]] bool IsCollision(const Triangle &triangle) const;

    /// @brief 線分を描画する
    /// @param viewProjectionMatrix ビュー投影行列
    /// @param viewportMatrix ビューポート行列
    /// @param color 色
    void Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const;
};

/// @brief 線分
struct Segment {
    // 始点
    Vector3 origin;
    // 終点への差分ベクトル
    Vector3 diff;

    /// @brief 平面との衝突判定
    /// @param plane 衝突判定を行う平面
    /// @return 衝突しているかどうか
    [[nodiscard]] bool IsCollision(const Plane &plane) const;

    /// @brief 三角形との衝突判定
    /// @param triangle 衝突判定を行う三角形
    /// @return 衝突しているかどうか
    [[nodiscard]] bool IsCollision(const Triangle &triangle) const;

    /// @brief 線分を描画する
    /// @param viewProjectionMatrix ビュー投影行列
    /// @param viewportMatrix ビューポート行列
    /// @param color 色
    void Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const;
};