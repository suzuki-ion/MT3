#pragma once

struct Sphere;
struct Line;
struct Ray;
struct Segment;
struct Plane;
struct Triangle;
struct AABB;

namespace CollisionFunctions {

/// @brief 球と球の衝突判定
/// @param sphere1 衝突判定を行う球1
/// @param sphere2 衝突判定を行う球2
/// @return 衝突しているかどうか
[[nodiscard]] bool IsCollision(const Sphere &sphere1, const Sphere &sphere2) noexcept;

/// @brief 球と平面の衝突判定
/// @param sphere 衝突判定を行う球
/// @param plane 衝突判定を行う平面
/// @return 衝突しているかどうか
[[nodiscard]] bool IsCollision(const Sphere &sphere, const Plane &plane) noexcept;

/// @brief 平面と直線の衝突判定
/// @param plane 衝突判定を行う平面
/// @param line 衝突判定を行う直線
/// @return 衝突しているかどうか
[[nodiscard]] bool IsCollision(const Plane &plane, const Line &line) noexcept;

/// @brief 平面と半直線の衝突判定
/// @param plane 衝突判定を行う平面
/// @param ray 衝突判定を行う半直線
/// @return 衝突しているかどうか
[[nodiscard]] bool IsCollision(const Plane &plane, const Ray &ray) noexcept;

/// @brief 平面と線分の衝突判定
/// @param plane 衝突判定を行う平面
/// @param segment 衝突判定を行う線分
/// @return 衝突しているかどうか
[[nodiscard]] bool IsCollision(const Plane &plane, const Segment &segment) noexcept;

/// @brief 三角形と直線の衝突判定
/// @param triangle 衝突判定を行う三角形
/// @param line 衝突判定を行う直線
/// @return 衝突しているかどうか
[[nodiscard]] bool IsCollision(const Triangle &triangle, const Line &line) noexcept;

/// @brief 三角形と半直線の衝突判定
/// @param triangle 衝突判定を行う三角形
/// @param ray 衝突判定を行う半直線
/// @return 衝突しているかどうか
[[nodiscard]] bool IsCollision(const Triangle &triangle, const Ray &ray) noexcept;

/// @brief 三角形と線分の衝突判定
/// @param triangle 衝突判定を行う三角形
/// @param segment 衝突判定を行う線分
/// @return 衝突しているかどうか
[[nodiscard]] bool IsCollision(const Triangle &triangle, const Segment &segment) noexcept;

/// @brief AABBとAABBの衝突判定
/// @param aabb1 衝突判定を行うAABB1
/// @param aabb2 衝突判定を行うAABB2
/// @return 衝突しているかどうか
[[nodiscard]] bool IsCollision(const AABB &aabb1, const AABB &aabb2) noexcept;

/// @brief AABBと球の衝突判定
/// @param aabb 衝突判定を行うAABB
/// @param sphere 衝突判定を行う球
/// @return 衝突しているかどうか
[[nodiscard]] bool IsCollision(const AABB &aabb, const Sphere &sphere) noexcept;

} // namespace CollisionFunctions