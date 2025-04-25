#include "CollisionFunctions.h"
#include "Vector3.h"
#include "Sphere.h"
#include "Lines.h"
#include "Plane.h"
#include "Triangle.h"
#include "AABB.h"
#include <algorithm>
#include <cmath>

namespace CollisionFunctions {

bool IsCollision(const Sphere &sphere1, const Sphere &sphere2) noexcept {
    // 球の中心間の距離を求める
    const float distance = (sphere1.center - sphere2.center).Length();
    // 球の半径の和と距離を比較する
    return distance <= (sphere1.radius + sphere2.radius);
}

bool IsCollision(const Sphere &sphere, const Plane &plane) noexcept {
    // 球の中心から平面までの距離kを求める
    const float k = plane.normal.Dot(sphere.center) - plane.distance;
    // 球の半径と平面までの距離を比較する
    return std::abs(k) <= sphere.radius;
}

bool IsCollision(const Plane &plane, const Line &line) noexcept {
    // 法線と線の内積を求める
    const float dot = plane.normal.Dot(line.diff);
    // 0なら平行で衝突していない
    if (dot == 0.0f) {
        return false;
    }
    return true;
}

bool IsCollision(const Plane &plane, const Ray &ray) noexcept {
    // 法線と線の内積を求める
    const float dot = plane.normal.Dot(ray.diff);
    // 0なら平行で衝突していない
    if (dot == 0.0f) {
        return false;
    }
    // tを求める
    const float t = (plane.distance - plane.normal.Dot(ray.origin)) / dot;
    // tの値によって衝突しているかを判断する
    return t >= 0.0f;
}

bool IsCollision(const Plane &plane, const Segment &segment) noexcept {
    // 法線と線の内積を求める
    const float dot = plane.normal.Dot(segment.diff);
    // 0なら平行で衝突していない
    if (dot == 0.0f) {
        return false;
    }
    // tを求める
    const float t = (plane.distance - plane.normal.Dot(segment.origin)) / dot;
    // tの値によって衝突しているかを判断する
    return t >= 0.0f && t <= 1.0f;
}

bool IsCollision(const Triangle &triangle, const Line &line) noexcept {
    // 三角形から作られた平面を求める
    Plane plane(triangle.vertices[0], triangle.vertices[1], triangle.vertices[2]);
    // 平面と線の媒介変数tを求める
    const float t = (plane.distance - plane.normal.Dot(line.origin)) / plane.normal.Dot(line.diff);
    // tの値によって衝突しているかを判断する
    if (t == 0.0f) {
        return false;
    }
    // 衝突点pを求める
    const Vector3 p = line.origin + line.diff * t;
    // 各辺を結んだベクトルと、頂点と衝突点pを結んだベクトルのクロス積を取る
    Vector3 v01 = triangle.vertices[1] - triangle.vertices[0];
    Vector3 v12 = triangle.vertices[2] - triangle.vertices[1];
    Vector3 v20 = triangle.vertices[0] - triangle.vertices[2];
    Vector3 v0p = p - triangle.vertices[0];
    Vector3 v1p = p - triangle.vertices[1];
    Vector3 v2p = p - triangle.vertices[2];
    Vector3 cross01 = v01.Cross(v1p);
    Vector3 cross12 = v12.Cross(v2p);
    Vector3 cross20 = v20.Cross(v0p);
    // すべての小三角形のクロス積と法線が同じ方向を向いていたら衝突
    return cross01.Dot(plane.normal) >= 0.0f &&
        cross12.Dot(plane.normal) >= 0.0f &&
        cross20.Dot(plane.normal) >= 0.0f;
}

bool IsCollision(const Triangle &triangle, const Ray &ray) noexcept {
    // 三角形から作られた平面を求める
    Plane plane(triangle.vertices[0], triangle.vertices[1], triangle.vertices[2]);
    // 平面と線の媒介変数tを求める
    const float t = (plane.distance - plane.normal.Dot(ray.origin)) / plane.normal.Dot(ray.diff);
    // tの値によって衝突しているかを判断する
    if (t == 0.0f || t < 0.0f) {
        return false;
    }
    // 衝突点pを求める
    const Vector3 p = ray.origin + ray.diff * t;
    // 各辺を結んだベクトルと、頂点と衝突点pを結んだベクトルのクロス積を取る
    Vector3 v01 = triangle.vertices[1] - triangle.vertices[0];
    Vector3 v12 = triangle.vertices[2] - triangle.vertices[1];
    Vector3 v20 = triangle.vertices[0] - triangle.vertices[2];
    Vector3 v0p = p - triangle.vertices[0];
    Vector3 v1p = p - triangle.vertices[1];
    Vector3 v2p = p - triangle.vertices[2];
    Vector3 cross01 = v01.Cross(v1p);
    Vector3 cross12 = v12.Cross(v2p);
    Vector3 cross20 = v20.Cross(v0p);
    // すべての小三角形のクロス積と法線が同じ方向を向いていたら衝突
    return cross01.Dot(plane.normal) >= 0.0f &&
        cross12.Dot(plane.normal) >= 0.0f &&
        cross20.Dot(plane.normal) >= 0.0f;
}

bool IsCollision(const Triangle &triangle, const Segment &segment) noexcept {
    // 三角形から作られた平面を求める
    Plane plane(triangle.vertices[0], triangle.vertices[1], triangle.vertices[2]);
    // 平面と線の媒介変数tを求める
    const float t = (plane.distance - plane.normal.Dot(segment.origin)) / plane.normal.Dot(segment.diff);
    // tの値によって衝突しているかを判断する
    if (t == 0.0f || t < 0.0f || t > 1.0f) {
        return false;
    }
    // 衝突点pを求める
    const Vector3 p = segment.origin + segment.diff * t;
    // 各辺を結んだベクトルと、頂点と衝突点pを結んだベクトルのクロス積を取る
    Vector3 v01 = triangle.vertices[1] - triangle.vertices[0];
    Vector3 v12 = triangle.vertices[2] - triangle.vertices[1];
    Vector3 v20 = triangle.vertices[0] - triangle.vertices[2];
    Vector3 v0p = p - triangle.vertices[0];
    Vector3 v1p = p - triangle.vertices[1];
    Vector3 v2p = p - triangle.vertices[2];
    Vector3 cross01 = v01.Cross(v1p);
    Vector3 cross12 = v12.Cross(v2p);
    Vector3 cross20 = v20.Cross(v0p);
    // すべての小三角形のクロス積と法線が同じ方向を向いていたら衝突
    return cross01.Dot(plane.normal) >= 0.0f &&
        cross12.Dot(plane.normal) >= 0.0f &&
        cross20.Dot(plane.normal) >= 0.0f;
}

bool IsCollision(const AABB &aabb1, const AABB &aabb2) noexcept {
    return
        (aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
        (aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
        (aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z);
}

bool IsCollision(const AABB &aabb, const Sphere &sphere) noexcept {
    // 最近接点を求める
    Vector3 closestPoint(
        std::clamp(sphere.center.x, aabb.min.x, aabb.max.x),
        std::clamp(sphere.center.y, aabb.min.y, aabb.max.y),
        std::clamp(sphere.center.z, aabb.min.z, aabb.max.z)
    );
    // 最近接点と球の中心との距離を求める
    const float distance = (closestPoint - sphere.center).Length();
    // 球の半径と距離を比較する
    return distance <= sphere.radius;
}

} // namespace CollisionFunctions