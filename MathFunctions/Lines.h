#pragma once
#include "Vector3.h"

struct Matrix4x4;

struct Line {
    // 始点
    Vector3 origin;
    // 終点への差分ベクトル
    Vector3 diff;

    /// @brief 線分を描画する
    /// @param viewProjectionMatrix ビュー投影行列
    /// @param viewportMatrix ビューポート行列
    /// @param color 色
    void Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const;
};

struct Ray {
    // 始点
    Vector3 origin;
    // 終点への差分ベクトル
    Vector3 diff;

    /// @brief 線分を描画する
    /// @param viewProjectionMatrix ビュー投影行列
    /// @param viewportMatrix ビューポート行列
    /// @param color 色
    void Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const;
};

struct Segment {
    // 始点
    Vector3 origin;
    // 終点への差分ベクトル
    Vector3 diff;

    /// @brief 線分を描画する
    /// @param viewProjectionMatrix ビュー投影行列
    /// @param viewportMatrix ビューポート行列
    /// @param color 色
    void Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const;
};