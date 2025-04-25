#include "Lines.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include "CollisionFunctions.h"
#include <Novice.h>

//==================================================
// 直線
//==================================================
#pragma region Line

bool Line::IsCollision(const Plane &plane) const {
    return CollisionFunctions::IsCollision(plane, *this);
}

bool Line::IsCollision(const Triangle &triangle) const {
    return CollisionFunctions::IsCollision(triangle, *this);
}

bool Line::IsCollision(const AABB &aabb) const {
    return CollisionFunctions::IsCollision(aabb, *this);
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

#pragma endregion

//==================================================
// 半直線
//==================================================
#pragma region Ray

bool Ray::IsCollision(const Plane &plane) const {
    return CollisionFunctions::IsCollision(plane, *this);
}

bool Ray::IsCollision(const Triangle &triangle) const {
    return CollisionFunctions::IsCollision(triangle, *this);
}

bool Ray::IsCollision(const AABB &aabb) const {
    return CollisionFunctions::IsCollision(aabb, *this);
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

#pragma endregion

//==================================================
// 線分
//==================================================
#pragma region Segment

bool Segment::IsCollision(const Plane &plane) const {
    return CollisionFunctions::IsCollision(plane, *this);
}

bool Segment::IsCollision(const Triangle &triangle) const {
    return CollisionFunctions::IsCollision(triangle, *this);
}

bool Segment::IsCollision(const AABB &aabb) const {
    return CollisionFunctions::IsCollision(aabb, *this);
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

#pragma endregion