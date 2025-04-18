#include "Sphere.h"
#include "Plane.h"
#include <cmath>
#include <Novice.h>
#define M_PI (4.0f * std::atanf(1.0f))

bool Sphere::IsCollision(const Sphere &sphere) const {
    // 2つの球の中心間の距離を求める
    const float distance = (center - sphere.center).Length();
    // 2つの球の半径の合計よりもc-fの長さが短ければ衝突
    return distance < (radius + sphere.radius);
}

bool Sphere::IsCollision(const Plane &plane) const {
    // 球の中心から平面までの距離kを求める
    const float k = plane.normal.Dot(center) - plane.distance;
    // 球の半径と平面までの距離を比較する
    return std::abs(k) <= radius;
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
