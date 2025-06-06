#include "ConicalPendulum.h"
#include "MathFunctions/Lines.h"
#include "MathFunctions/Sphere.h"
#include <cmath>

void ConicalPendulum::CalculateAngle(const float deltaTime) {
    // 重力加速度
    static const float g = 9.8f;

    angularVelocity = std::sqrt(g / (length * std::cos(halfApexAngle)));
    angle += angularVelocity * deltaTime;

    float radius = std::sin(halfApexAngle) *length;
    float height = std::cos(halfApexAngle) * length;

    // 振り子の先端位置を計算
    bob.x = anchor.x + std::cos(angle) * radius;
    bob.y = anchor.y - height;
    bob.z = anchor.z - std::sin(angle) * radius;
}

void ConicalPendulum::Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const {
    Line line{ anchor, bob - anchor };
    line.Draw(viewProjectionMatrix, viewportMatrix, color);
    Sphere sphere{ bob, 0.1f };
    sphere.Draw(viewProjectionMatrix, viewportMatrix, 16, color);
}
