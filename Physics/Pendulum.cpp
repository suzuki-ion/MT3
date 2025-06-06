#include "Pendulum.h"
#include "MathFunctions/Lines.h"
#include "MathFunctions/Sphere.h"
#include <cmath>

void Pendulum::CalculateAngle(const float deltaTime) {
    angularAcceleration = (-9.8f / length) * std::sin(angle);
    angularVelocity += angularAcceleration * deltaTime;
    angle += angularVelocity * deltaTime;

    bob.x = anchor.x + std::sin(angle) * length;
    bob.y = anchor.y - std::cos(angle) * length;
    bob.z = anchor.z;
}

void Pendulum::Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const {
    Line line{ anchor, bob - anchor };
    line.Draw(viewProjectionMatrix, viewportMatrix, color);
    Sphere sphere{ bob, 0.1f };
    sphere.Draw(viewProjectionMatrix, viewportMatrix, 16, color);
}
