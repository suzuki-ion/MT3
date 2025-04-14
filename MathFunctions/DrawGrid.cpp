#include "DrawGrid.h"
#include <Novice.h>

void DrawGrid(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const float kGridHalfWidth, const unsigned int kSubdivision) {
    const float kGridEvery = (kGridHalfWidth * 2.0f) / static_cast<float>(kSubdivision);
    for (unsigned int xIndex = 0; xIndex <= kSubdivision; xIndex++) {
        const float x = -kGridHalfWidth + (kGridEvery * static_cast<float>(xIndex));
        const Vector3 start = { x, 0.0f, -kGridHalfWidth };
        const Vector3 end = { x, 0.0f, kGridHalfWidth };
        const Vector3 startScreen = start.Transform(viewProjectionMatrix * viewportMatrix);
        const Vector3 endScreen = end.Transform(viewProjectionMatrix * viewportMatrix);
        // 原点のときは黒
        if (x == 0.0f) {
            Novice::DrawLine(
                static_cast<int>(startScreen.x),
                static_cast<int>(startScreen.y),
                static_cast<int>(endScreen.x),
                static_cast<int>(endScreen.y),
                0x000000FF
            );
        } else {
            Novice::DrawLine(
                static_cast<int>(startScreen.x),
                static_cast<int>(startScreen.y),
                static_cast<int>(endScreen.x),
                static_cast<int>(endScreen.y),
                0xAAAAAAFF
            );
        }
    }
    for (unsigned int zIndex = 0; zIndex <= kSubdivision; zIndex++) {
        const float z = -kGridHalfWidth + (kGridEvery * static_cast<float>(zIndex));
        const Vector3 start = { -kGridHalfWidth, 0.0f, z };
        const Vector3 end = { kGridHalfWidth, 0.0f, z };
        const Vector3 startScreen = start.Transform(viewProjectionMatrix * viewportMatrix);
        const Vector3 endScreen = end.Transform(viewProjectionMatrix * viewportMatrix);
        // 原点のときは黒
        if (z == 0.0f) {
            Novice::DrawLine(
                static_cast<int>(startScreen.x),
                static_cast<int>(startScreen.y),
                static_cast<int>(endScreen.x),
                static_cast<int>(endScreen.y),
                0x000000FF
            );
        } else {
            Novice::DrawLine(
                static_cast<int>(startScreen.x),
                static_cast<int>(startScreen.y),
                static_cast<int>(endScreen.x),
                static_cast<int>(endScreen.y),
                0xAAAAAAFF
            );
        }
    }
}
