#include "AABB.h"
#include "Sphere.h"
#include "CollisionFunctions.h"
#include <algorithm>
#include <Novice.h>

AABB::AABB(const Vector3 &min, const Vector3 &max) noexcept {
    this->min = min;
    this->max = max;
}

AABB::AABB(const AABB &aabb) noexcept {
    this->min = aabb.min;
    this->max = aabb.max;
}

void AABB::Sort() noexcept {
    if (min.x > max.x) {
        std::swap(min.x, max.x);
    }
    if (min.y > max.y) {
        std::swap(min.y, max.y);
    }
    if (min.z > max.z) {
        std::swap(min.z, max.z);
    }
}

bool AABB::IsCollision(const AABB &aabb) const noexcept {
    return CollisionFunctions::IsCollision(*this, aabb);
}

bool AABB::IsCollision(const Sphere &sphere) const noexcept {
    return CollisionFunctions::IsCollision(*this, sphere);
}

void AABB::Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const noexcept {
    Vector3 vertices[8] = {
        { min.x, min.y, min.z },
        { max.x, min.y, min.z },
        { max.x, max.y, min.z },
        { min.x, max.y, min.z },
        { min.x, min.y, max.z },
        { max.x, min.y, max.z },
        { max.x, max.y, max.z },
        { min.x, max.y, max.z }
    };
    for (int i = 0; i < 8; i++) {
        vertices[i] = vertices[i].Transform(viewProjectionMatrix).Transform(viewportMatrix);
    }
    for (int i = 0; i < 4; i++) {
        Novice::DrawLine(
            static_cast<int>(vertices[i].x),
            static_cast<int>(vertices[i].y),
            static_cast<int>(vertices[(i + 1) % 4].x),
            static_cast<int>(vertices[(i + 1) % 4].y),
            color
        );
        Novice::DrawLine(
            static_cast<int>(vertices[i + 4].x),
            static_cast<int>(vertices[i + 4].y),
            static_cast<int>(vertices[((i + 1) % 4) + 4].x),
            static_cast<int>(vertices[((i + 1) % 4) + 4].y),
            color
        );
        Novice::DrawLine(
            static_cast<int>(vertices[i].x),
            static_cast<int>(vertices[i].y),
            static_cast<int>(vertices[i + 4].x),
            static_cast<int>(vertices[i + 4].y),
            color
        );
    }
}
