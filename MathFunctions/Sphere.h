#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"

struct Sphere {
    Sphere() : center{ 0.0f, 0.0f, 0.0f }, radius(1.0f) {}
    Sphere(const Vector3 &center, float radius) :
        center(center), radius(radius)
    {}
    Sphere(const Sphere &sphere) :
        center(sphere.center), radius(sphere.radius)
    {}

    void SetCenter(const Vector3 &setCenter) {
        center = setCenter;
    }
    void SetRadius(float setRadius) {
        radius = setRadius;
    }

    const Vector3 &GetCenter() const {
        return center;
    }
    float GetRadius() const {
        return radius;
    }

    void Draw(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, const unsigned int kSubdivision, const unsigned int color);

    Vector3 center;
    float radius;
};