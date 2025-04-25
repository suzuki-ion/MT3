#include "Plane.h"
#include "Sphere.h"
#include "Lines.h"
#include <Novice.h>

void Plane::Set(const Vector3 &n, const Vector3 &p) noexcept {
    this->normal = n;
    // 平面の距離を求める
    distance = n.Dot(p);
}

void Plane::Set(const Vector3 &a, const Vector3 &b, const Vector3 &c) noexcept {
    // 3点から法線ベクトルを求める
    normal = (b - a).Cross(c - b).Normalize();
    // 平面の距離を求める
    distance = normal.Dot(a);
}

bool Plane::IsCollision(const Sphere &sphere) const {
    // 球の中心から平面までの距離kを求める
    const float k = normal.Dot(sphere.center) - distance;
    // 球の半径と平面までの距離を比較する
    return std::abs(k) <= sphere.radius;
}

bool Plane::IsCollision(const Line &line) const {
    // 法線と線の内積を求める
    const float dot = normal.Dot(line.diff);
    // 0なら平行で衝突していない
    if (dot == 0.0f) {
        return false;
    }
    // tを求める
    const float t = (distance - normal.Dot(line.origin)) / dot;
    // tの値によって衝突しているかを判断する
    return t >= 0.0f && t <= 1.0f;
}

bool Plane::IsCollision(const Ray &ray) const {
    // 法線と線の内積を求める
    const float dot = normal.Dot(ray.diff);
    // 0なら平行で衝突していない
    if (dot == 0.0f) {
        return false;
    }
    // tを求める
    const float t = (distance - normal.Dot(ray.origin)) / dot;
    // tの値によって衝突しているかを判断する
    return t >= 0.0f;
}

bool Plane::IsCollision(const Segment &segment) const {
    // 法線と線の内積を求める
    const float dot = normal.Dot(segment.diff);
    // 0なら平行で衝突していない
    if (dot == 0.0f) {
        return false;
    }
    // tを求める
    const float t = (distance - normal.Dot(segment.origin)) / dot;
    // tの値によって衝突しているかを判断する
    return t >= 0.0f && t <= 1.0f;
}

void Plane::Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const {
    Vector3 center = normal * distance;
    
    Vector3 perpendiculars[4];
    perpendiculars[0] = normal.Perpendicular().Normalize();
    perpendiculars[1] = {
        -perpendiculars[0].x,
        -perpendiculars[0].y,
        -perpendiculars[0].z
    };
    perpendiculars[2] = normal.Cross(perpendiculars[0]);
    perpendiculars[3] = {
        -perpendiculars[2].x,
        -perpendiculars[2].y,
        -perpendiculars[2].z
    };

    Vector3 points[4];
    Vector3 extend;
    Vector3 point;
    for (int32_t index = 0; index < 4; index++) {
        extend = 2.0f * perpendiculars[index];
        point = center + extend;
        points[index] = point.Transform(viewProjectionMatrix).Transform(viewportMatrix);
    }

    Novice::DrawLine(
        static_cast<int>(points[0].x),
        static_cast<int>(points[0].y),
        static_cast<int>(points[2].x),
        static_cast<int>(points[2].y),
        color
    );
    Novice::DrawLine(
        static_cast<int>(points[2].x),
        static_cast<int>(points[2].y),
        static_cast<int>(points[1].x),
        static_cast<int>(points[1].y),
        color
    );
    Novice::DrawLine(
        static_cast<int>(points[1].x),
        static_cast<int>(points[1].y),
        static_cast<int>(points[3].x),
        static_cast<int>(points[3].y),
        color
    );
    Novice::DrawLine(
        static_cast<int>(points[3].x),
        static_cast<int>(points[3].y),
        static_cast<int>(points[0].x),
        static_cast<int>(points[0].y),
        color
    );
}
