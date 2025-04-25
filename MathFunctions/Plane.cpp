#include "Plane.h"
#include "CollisionFunctions.h"
#include <Novice.h>
#include <cmath>

void Plane::Set(const Vector3 &n, const Vector3 &p) noexcept {
    normal = n;
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
    return CollisionFunctions::IsCollision(sphere, *this);
}

bool Plane::IsCollision(const Line &line) const {
    return CollisionFunctions::IsCollision(*this, line);
}

bool Plane::IsCollision(const Ray &ray) const {
    return CollisionFunctions::IsCollision(*this, ray);
}

bool Plane::IsCollision(const Segment &segment) const {
    return CollisionFunctions::IsCollision(*this, segment);
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
