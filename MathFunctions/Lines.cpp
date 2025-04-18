#include "Lines.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include <Novice.h>

void Line::Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const {
    Vector3 start = origin.Transform(viewProjectionMatrix).Transform(viewportMatrix);
    Vector3 end = (origin + diff).Transform(viewProjectionMatrix).Transform(viewportMatrix);
    Novice::DrawLine(
        static_cast<int>(start.x),
        static_cast<int>(start.y),
        static_cast<int>(end.x),
        static_cast<int>(end.y),
        color);
}

void Ray::Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const {
    Vector3 start = origin.Transform(viewProjectionMatrix).Transform(viewportMatrix);
    Vector3 end = (origin + diff).Transform(viewProjectionMatrix).Transform(viewportMatrix);
    Novice::DrawLine(
        static_cast<int>(start.x),
        static_cast<int>(start.y),
        static_cast<int>(end.x),
        static_cast<int>(end.y),
        color);
}

void Segment::Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int color) const {
    Vector3 start = origin.Transform(viewProjectionMatrix).Transform(viewportMatrix);
    Vector3 end = (origin + diff).Transform(viewProjectionMatrix).Transform(viewportMatrix);
    Novice::DrawLine(
        static_cast<int>(start.x),
        static_cast<int>(start.y),
        static_cast<int>(end.x),
        static_cast<int>(end.y),
        color);
}