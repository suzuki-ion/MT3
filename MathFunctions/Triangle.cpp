#include "Triangle.h"
#include "Lines.h"
#include "Plane.h"
#include <Novice.h>

bool Triangle::IsCollision(const Line &line) const noexcept {
    // 三角形から作られた平面を求める
    Plane plane(vertices[0], vertices[1], vertices[2]);
    // 平面と線の媒介変数tを求める
    const float t = (plane.distance - plane.normal.Dot(line.origin)) / plane.normal.Dot(line.diff);
    // tの値によって衝突しているかを判断する
    if (t == 0.0f) {
        return false;
    }
    // 衝突点pを求める
    const Vector3 p = line.origin + line.diff * t;
    // 各辺を結んだベクトルと、頂点と衝突点pを結んだベクトルのクロス積を取る
    Vector3 v01 = vertices[1] - vertices[0];
    Vector3 v12 = vertices[2] - vertices[1];
    Vector3 v20 = vertices[0] - vertices[2];
    Vector3 v0p = p - vertices[0];
    Vector3 v1p = p - vertices[1];
    Vector3 v2p = p - vertices[2];
    Vector3 cross01 = v01.Cross(v1p);
    Vector3 cross12 = v12.Cross(v2p);
    Vector3 cross20 = v20.Cross(v0p);
    // すべての小三角形のクロス積と法線が同じ方向を向いていたら衝突
    return cross01.Dot(plane.normal) >= 0.0f &&
        cross12.Dot(plane.normal) >= 0.0f &&
        cross20.Dot(plane.normal) >= 0.0f;
}

bool Triangle::IsCollision(const Ray &ray) const noexcept {
    // 三角形から作られた平面を求める
    Plane plane(vertices[0], vertices[1], vertices[2]);
    // 平面と線の媒介変数tを求める
    const float t = (plane.distance - plane.normal.Dot(ray.origin)) / plane.normal.Dot(ray.diff);
    // tの値によって衝突しているかを判断する
    if (t == 0.0f || t < 0.0f) {
        return false;
    }
    // 衝突点pを求める
    const Vector3 p = ray.origin + ray.diff * t;
    // 各辺を結んだベクトルと、頂点と衝突点pを結んだベクトルのクロス積を取る
    Vector3 v01 = vertices[1] - vertices[0];
    Vector3 v12 = vertices[2] - vertices[1];
    Vector3 v20 = vertices[0] - vertices[2];
    Vector3 v0p = p - vertices[0];
    Vector3 v1p = p - vertices[1];
    Vector3 v2p = p - vertices[2];
    Vector3 cross01 = v01.Cross(v1p);
    Vector3 cross12 = v12.Cross(v2p);
    Vector3 cross20 = v20.Cross(v0p);
    // すべての小三角形のクロス積と法線が同じ方向を向いていたら衝突
    return cross01.Dot(plane.normal) >= 0.0f &&
        cross12.Dot(plane.normal) >= 0.0f &&
        cross20.Dot(plane.normal) >= 0.0f;
}

bool Triangle::IsCollision(const Segment &segment) const noexcept {
    // 三角形から作られた平面を求める
    Plane plane(vertices[0], vertices[1], vertices[2]);
    // 平面と線の媒介変数tを求める
    const float t = (plane.distance - plane.normal.Dot(segment.origin)) / plane.normal.Dot(segment.diff);
    // tの値によって衝突しているかを判断する
    if (t == 0.0f || t < 0.0f || t > 1.0f) {
        return false;
    }
    // 衝突点pを求める
    const Vector3 p = segment.origin + segment.diff * t;
    // 各辺を結んだベクトルと、頂点と衝突点pを結んだベクトルのクロス積を取る
    Vector3 v01 = vertices[1] - vertices[0];
    Vector3 v12 = vertices[2] - vertices[1];
    Vector3 v20 = vertices[0] - vertices[2];
    Vector3 v0p = p - vertices[0];
    Vector3 v1p = p - vertices[1];
    Vector3 v2p = p - vertices[2];
    Vector3 cross01 = v01.Cross(v1p);
    Vector3 cross12 = v12.Cross(v2p);
    Vector3 cross20 = v20.Cross(v0p);
    // すべての小三角形のクロス積と法線が同じ方向を向いていたら衝突
    return cross01.Dot(plane.normal) >= 0.0f &&
        cross12.Dot(plane.normal) >= 0.0f &&
        cross20.Dot(plane.normal) >= 0.0f;
}

void Triangle::Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const noexcept {
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

