#include "Camera.h"
#include "RenderingPipeline.h"

extern const float kWinWidth;
extern const float kWinHeight;

Camera::Camera() noexcept {
    cameraMatrix_.SetScale({ 1.0f, 1.0f, 1.0f });
    cameraMatrix_.SetRotate({ 0.0f, 0.0f, 0.0f });
    cameraMatrix_.SetTranslate({ 0.0f, 0.0f, 0.0f });
    worldMatrix_.MakeAffine({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
    CalculateMatrix();
}

Camera::Camera(const Vector3 &cameraTranslate, const Vector3 &cameraRotate, const Vector3 &cameraScale) noexcept {
    cameraMatrix_.SetScale(cameraScale);
    cameraMatrix_.SetRotate(cameraRotate);
    cameraMatrix_.SetTranslate(cameraTranslate);
    worldMatrix_.MakeAffine({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
    CalculateMatrix();
}

void Camera::SetCamera(const Vector3 &cameraTranslate, const Vector3 &cameraRotate, const Vector3 &cameraScale) noexcept {
    cameraMatrix_.SetTranslate(cameraTranslate);
    cameraMatrix_.SetRotate(cameraRotate);
    cameraMatrix_.SetScale(cameraScale);
}

void Camera::SetTranslate(const Vector3 &cameraTranslate) noexcept {
    cameraMatrix_.SetTranslate(cameraTranslate);
}

void Camera::SetRotate(const Vector3 &cameraRotate) noexcept {
    cameraMatrix_.SetRotate(cameraRotate);
}

void Camera::SetScale(const Vector3 &cameraScale) noexcept {
    cameraMatrix_.SetScale(cameraScale);
}

void Camera::CalculateMatrix() noexcept {
    viewMatrix_ = cameraMatrix_.InverseScale() * cameraMatrix_.InverseRotate() * cameraMatrix_.InverseTranslate();
    projectionMatrix_ = MakePerspectiveFovMatrix(0.45f, kWinWidth / kWinHeight, 0.1f, 100.0f);
    wvpMatrix_ = worldMatrix_ * (viewMatrix_ * projectionMatrix_);
    viewportMatrix_ = MakeViewportMatrix(0.0f, 0.0f, kWinWidth, kWinHeight, 0.0f, 1.0f);
}
