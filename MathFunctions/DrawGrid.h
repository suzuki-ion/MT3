#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"

/// @brief グリッドを描画する
/// @param viewProjectionMatrix ビュー投影行列
/// @param viewportMatrix ビューポート行列
/// @param kGridHalfWidth グリッドの半分の幅
/// @param kSubdivision 分割数
void DrawGrid(
    const Matrix4x4 &viewProjectionMatrix,
    const Matrix4x4 &viewportMatrix,
    const float kGridHalfWidth,
    const unsigned int kSubdivision
);