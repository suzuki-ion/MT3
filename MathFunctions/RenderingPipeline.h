﻿#pragma once
#include "Matrix4x4.h"

/// @brief 透視投影行列を生成する
/// @param fovY 画角 Y
/// @param aspectRatio アスペクト比
/// @param nearClip 近平面への距離
/// @param farClip 遠平面への距離
/// @return 透視投影行列
[[nodiscard]] Matrix4x4 MakePerspectiveFovMatrix(
    const float fovY,
    const float aspectRatio,
    const float nearClip,
    const float farClip) noexcept;

/// @brief 正射影行列を生成する
/// @param left 左端
/// @param top 上端
/// @param right 右端
/// @param bottom 下端
/// @param nearClip 近平面への距離
/// @param farClip 遠平面への距離
/// @return 正射影行列
[[nodiscard]] Matrix4x4 MakeOrthographicMatrix(
    const float left,
    const float top,
    const float right,
    const float bottom,
    const float nearClip,
    const float farClip) noexcept;

/// @brief ビューポート行列を生成する
/// @param left 左端
/// @param top 上端
/// @param width 幅
/// @param height 高さ
/// @param minDepth 最小深度
/// @param maxDepth 最大深度
/// @return ビューポート行列
[[nodiscard]] Matrix4x4 MakeViewportMatrix(
    const float left,
    const float top,
    const float width,
    const float height,
    const float minDepth,
    const float maxDepth) noexcept;

[[nodiscard]] Matrix4x4 MakeRenderingPipelineMatrix(
    const float fovY,
    const float aspectRatio,
    const float nearClip,
    const float farClip,
    const float left,
    const float top,
    const float width,
    const float height,
    const float minDepth,
    const float maxDepth) noexcept;