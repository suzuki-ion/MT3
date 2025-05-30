#include "Bezier.h"
#include "Lines.h"
#include "Sphere.h"

Vector3 Bezier(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, const float t) noexcept {
    Vector3 p01 = Lerp(p0, p1, t);
    Vector3 p12 = Lerp(p1, p2, t);
    return Lerp(p01, p12, t);
}

void DrawBezier(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color, const int division) noexcept {
    for (int i = 0; i < division; ++i) {
        const float t0 = static_cast<float>(i) / static_cast<float>(division);
        const float t1 = static_cast<float>(i + 1) / static_cast<float>(division);
        Vector3 bezier0 = Bezier(p0, p1, p2, t0);
        Vector3 bezier1 = Bezier(p0, p1, p2, t1);
        Segment segment = { bezier0, bezier1 - bezier0 };
        segment.Draw(viewProjectionMatrix, viewportMatrix, color);
    }
    Sphere sphere0(p0, 0.01f);
    Sphere sphere1(p1, 0.01f);
    Sphere sphere2(p2, 0.01f);
    sphere0.Draw(viewProjectionMatrix, viewportMatrix, 16, 0x000000FF);
    sphere1.Draw(viewProjectionMatrix, viewportMatrix, 16, 0x000000FF);
    sphere2.Draw(viewProjectionMatrix, viewportMatrix, 16, 0x000000FF);
}
