#include "Sphere.h"
#include "Plane.h"
#include "CollisionFunctions.h"
#include <cmath>
#include <Novice.h>
#define M_PI (4.0f * std::atanf(1.0f))

bool Sphere::IsCollision(const Sphere &sphere) const {
    return CollisionFunctions::IsCollision(*this, sphere);
}

bool Sphere::IsCollision(const Plane &plane) const {
    return CollisionFunctions::IsCollision(*this, plane);
}

void Sphere::Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int kSubdivision, const unsigned int color) {
    const float kLonEvery = M_PI * 2.0f / static_cast<float>(kSubdivision);
    const float kLatEvery = M_PI / static_cast<float>(kSubdivision);
    
    // 緯度の方向に分割 -π/2 ～ π/2
    for (unsigned int latIndex = 0; latIndex <= kSubdivision; latIndex++) {
        const float lat = -M_PI / 2.0f + (kLatEvery * static_cast<float>(latIndex));
        // 経度の方向に分割 0 ～ 2π
        for (unsigned int lonIndex = 0; lonIndex <= kSubdivision; lonIndex++) {
            const float lon = lonIndex * kLonEvery;
            // world座標系でのa, b, cを求める
            Vector3 a;
            Vector3 b;
            Vector3 c;
            a.x = center.x + radius * std::cosf(lat) * std::cosf(lon);
            a.y = center.y + radius * std::sinf(lat);
            a.z = center.z + radius * std::cosf(lat) * std::sinf(lon);
            b.x = center.x + radius * std::cosf(lat + kLatEvery) * std::cosf(lon);
            b.y = center.y + radius * std::sinf(lat + kLatEvery);
            b.z = center.z + radius * std::cosf(lat + kLatEvery) * std::sinf(lon);
            c.x = center.x + radius * std::cosf(lat) * std::cosf(lon + kLonEvery);
            c.y = center.y + radius * std::sinf(lat);
            c.z = center.z + radius * std::cosf(lat) * std::sinf(lon + kLonEvery);
            // screen座標系に変換
            const Vector3 aScreen = a.Transform(viewProjectionMatrix * viewportMatrix);
            const Vector3 bScreen = b.Transform(viewProjectionMatrix * viewportMatrix);
            const Vector3 cScreen = c.Transform(viewProjectionMatrix * viewportMatrix);
            // ab, acで線を引く
            Novice::DrawLine(
                static_cast<int>(aScreen.x),
                static_cast<int>(aScreen.y),
                static_cast<int>(bScreen.x),
                static_cast<int>(bScreen.y),
                color
            );
            Novice::DrawLine(
                static_cast<int>(aScreen.x),
                static_cast<int>(aScreen.y),
                static_cast<int>(cScreen.x),
                static_cast<int>(cScreen.y),
                color
            );
        }
    }
}
