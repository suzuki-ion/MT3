#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"

struct Sphere;
struct Line;
struct Ray;
struct Segment;

struct Plane {
    Plane() : normal{ 0.0f, 0.0f, 0.0f }, distance(0.0f) {}
    Plane(const Vector3 &normal, float distance) :
        normal(normal), distance(distance)
    {}
    Plane(const Vector3 &normal, const Vector3 &point) :
        normal(normal), distance(normal.Dot(point))
    {}
    Plane(const Vector3 &a, const Vector3 &b, const Vector3 &c) :
        normal((b - a).Cross(c - b).Normalize()),
        distance(normal.Dot(a))
    {}
    Plane(const Plane &plane) :
        normal(plane.normal), distance(plane.distance)
    {}

    /// @brief 法線と平面上の点から平面を設定する
    /// @param n 法線ベクトル
    /// @param point 平面上の点
    void Set(const Vector3 &n, const Vector3 &p) noexcept;

    /// @biref 3点で構成される平面を設定する
    /// @param a 平面上の点a
    /// @param b 平面上の点b
    /// @param c 平面上の点c
    void Set(const Vector3 &a, const Vector3 &b, const Vector3 &c) noexcept;

    /// @brief 平面と球の衝突判定
    /// @param sphere 衝突判定を行う球
    /// @return 衝突しているかどうか
    bool IsCollision(const Sphere &sphere) const;

    /// @brief 平面と線分の衝突判定
    /// @param line 衝突判定を行う線分
    /// @return 衝突しているかどうか
    bool IsCollision(const Line &line) const;

    /// @brief 平面と線分の衝突判定
    /// @param ray 衝突判定を行う線分
    /// @return 衝突しているかどうか
    bool IsCollision(const Ray &ray) const;

    /// @brief 平面と線分の衝突判定
    /// @param segment 衝突判定を行う線分
    /// @return 衝突しているかどうか
    bool IsCollision(const Segment &segment) const;

    /// @brief 平面を描画する
    /// @param viewProjectionMatrix ビュー投影行列
    /// @param viewportMatrix ビューポート行列
    /// @param color 色
    void Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const;
    
    // 法線ベクトル
    Vector3 normal;
    // 距離
    float distance;
};