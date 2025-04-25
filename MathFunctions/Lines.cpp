#include "Lines.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include "Plane.h"
#include <Novice.h>

bool Line::IsCollision(const Plane &plane) const {
    // 法線と線の内積を求める
    const float dot = plane.normal.Dot(diff);
    // 0なら平行で衝突していない
    if (dot == 0.0f) {
        return false;
    }
    // tを求める
    const float t = (plane.distance - plane.normal.Dot(origin)) / dot;
    // tの値によって衝突しているかを判断する
    return t >= 0.0f && t <= 1.0f;
}

void Line::Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const {
    Vector3 start = origin.Transform(viewProjectionMatrix).Transform(viewportMatrix);
    Vector3 end = (origin + diff).Transform(viewProjectionMatrix).Transform(viewportMatrix);
    Novice::DrawLine(
        static_cast<int>(start.x),
        static_cast<int>(start.y),
        static_cast<int>(end.x),
        static_cast<int>(end.y),
        color);
}

bool Ray::IsCollision(const Plane &plane) const {
    // 法線と線の内積を求める
    const float dot = plane.normal.Dot(diff);
    // 0なら平行で衝突していない
    if (dot == 0.0f) {
        return false;
    }
    // tを求める
    const float t = (plane.distance - plane.normal.Dot(origin)) / dot;
    // tの値によって衝突しているかを判断する
    return t >= 0.0f;
}

void Ray::Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const {
    Vector3 start = origin.Transform(viewProjectionMatrix).Transform(viewportMatrix);
    Vector3 end = (origin + diff).Transform(viewProjectionMatrix).Transform(viewportMatrix);
    Novice::DrawLine(
        static_cast<int>(start.x),
        static_cast<int>(start.y),
        static_cast<int>(end.x),
        static_cast<int>(end.y),
        color);
}

bool Segment::IsCollision(const Plane &plane) const {
    // 法線と線の内積を求める
    const float dot = plane.normal.Dot(diff);
    // 0なら平行で衝突していない
    if (dot == 0.0f) {
        return false;
    }
    // tを求める
    const float t = (plane.distance - plane.normal.Dot(origin)) / dot;
    // tの値によって衝突しているかを判断する
    return t >= 0.0f && t <= 1.0f;
}

void Segment::Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const {
    Vector3 start = origin.Transform(viewProjectionMatrix).Transform(viewportMatrix);
    Vector3 end = (origin + diff).Transform(viewProjectionMatrix).Transform(viewportMatrix);
    Novice::DrawLine(
        static_cast<int>(start.x),
        static_cast<int>(start.y),
        static_cast<int>(end.x),
        static_cast<int>(end.y),
        color);
}