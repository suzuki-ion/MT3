#include "ScreenPrintf.h"
#include <Novice.h>

void VectorScreenPrintf(int x, int y, const Vector3 &vec) {
    Novice::ScreenPrintf(x, y, "X:%.2f Y:%.2f Z:%.2f", vec.x, vec.y, vec.z);
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4 &mat) {
    Novice::ScreenPrintf(x, y, "%6.2f %6.2f %6.2f %6.2f", mat.m[0][0], mat.m[0][1], mat.m[0][2], mat.m[0][3]);
    Novice::ScreenPrintf(x, y + 16, "%6.2f %6.2f %6.2f %6.2f", mat.m[1][0], mat.m[1][1], mat.m[1][2], mat.m[1][3]);
    Novice::ScreenPrintf(x, y + 32, "%6.2f %6.2f %6.2f %6.2f", mat.m[2][0], mat.m[2][1], mat.m[2][2], mat.m[2][3]);
    Novice::ScreenPrintf(x, y + 48, "%6.2f %6.2f %6.2f %6.2f", mat.m[3][0], mat.m[3][1], mat.m[3][2], mat.m[3][3]);
}
