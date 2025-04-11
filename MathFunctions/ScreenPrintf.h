#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"

/// @brief Vector3の値を描画する
/// @param x 表示位置 X
/// @param y 表示位置 Y
/// @param vec 表示するVector3
void VectorScreenPrintf(int x, int y, const Vector3 &vec, const char *str);

/// @brief Matrix4x4の値を描画する
/// @param x 表示位置 X
/// @param y 表示位置 Y
/// @param mat 表示するMatrix4x4
void MatrixScreenPrintf(int x, int y, const Matrix4x4 &mat, const char *str);