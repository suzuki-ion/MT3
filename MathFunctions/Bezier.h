#include "Vector3.h"

Vector3 Bezier(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, const float t) noexcept;

void DrawBezier(
    const Vector3 &p0, const Vector3 &p1, const Vector3 &p2,
    const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix,
    const unsigned int color, const int division = 100
) noexcept;