#include "Triangle.h"
#include "CollisionFunctions.h"
#include <Novice.h>

bool Triangle::IsCollision(const Line &line) const {
    return CollisionFunctions::IsCollision(*this, line);
}

bool Triangle::IsCollision(const Ray &ray) const {
    return CollisionFunctions::IsCollision(*this, ray);
}

bool Triangle::IsCollision(const Segment &segment) const {
    return CollisionFunctions::IsCollision(*this, segment);
}

void Triangle::Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const {
    Vector3 aScreen = vertices[0].Transform(viewProjectionMatrix).Transform(viewportMatrix);
    Vector3 bScreen = vertices[1].Transform(viewProjectionMatrix).Transform(viewportMatrix);
    Vector3 cScreen = vertices[2].Transform(viewProjectionMatrix).Transform(viewportMatrix);
    Novice::DrawLine(
        static_cast<int>(aScreen.x),
        static_cast<int>(aScreen.y),
        static_cast<int>(bScreen.x),
        static_cast<int>(bScreen.y),
        color
    );
    Novice::DrawLine(
        static_cast<int>(bScreen.x),
        static_cast<int>(bScreen.y),
        static_cast<int>(cScreen.x),
        static_cast<int>(cScreen.y),
        color
    );
    Novice::DrawLine(
        static_cast<int>(cScreen.x),
        static_cast<int>(cScreen.y),
        static_cast<int>(aScreen.x),
        static_cast<int>(aScreen.y),
        color
    );
}

