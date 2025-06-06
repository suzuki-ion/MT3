#pragma once
#include "MathFunctions/Vector3.h"

struct Pendulum {
    /// @brief 振り子の角度を計算する
    /// @param deltaTime 前回の更新からの経過時間
    void CalculateAngle(const float deltaTime);
    /// @brief 振り子を描画する
    /// @param viewProjectionMatrix ビュー投影行列
    /// @param viewportMatrix ビューポート行列
    /// @param color 色
    void Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const;

    // 支点の位置
    Vector3 anchor;
    // 振り子の先端位置
    Vector3 bob;
    // 振り子の長さ
    float length;
    // 振り子の角度
    float angle;
    // 振り子の角速度
    float angularVelocity;
    // 振り子の角加速度
    float angularAcceleration;
};