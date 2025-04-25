#pragma once
#include "AffineMatrix.h"

class Camera {
public:
    Camera() noexcept;
    Camera(const Vector3 &cameraTranslate, const Vector3 &cameraRotate, const Vector3 &cameraScale) noexcept;

    /// @brief カメラの行列を設定する
    /// @param cameraTranslate 平行移動
    /// @param cameraRotate 回転
    /// @param cameraScale 拡大縮小
    void SetCamera(const Vector3 &cameraTranslate, const Vector3 &cameraRotate, const Vector3 &cameraScale) noexcept;

    /// @brief カメラの平行移動行列を設定する
    /// @param cameraTranslate 平行移動
    void SetTranslate(const Vector3 &cameraTranslate) noexcept;

    /// @brief カメラの回転行列を設定する
    /// @param cameraRotate 回転
    void SetRotate(const Vector3 &cameraRotate) noexcept;

    /// @brief カメラの拡大縮小行列を設定する
    /// @param cameraScale 拡大縮小
    void SetScale(const Vector3 &cameraScale) noexcept;

    /// @brief 各行列を計算する
    void CalculateMatrix() noexcept;

    /// @brief カメラ行列を取得する
    /// @return カメラ行列
    [[nodiscard]] const AffineMatrix &GetCameraMatrix() const noexcept {
        return cameraMatrix_;
    }

    /// @brief ビュー行列を取得する
    /// @return ビュー行列
    [[nodiscard]] const Matrix4x4 &GetViewMatrix() const noexcept {
        return viewMatrix_;
    }

    /// @brief 投影行列を取得する
    /// @return 投影行列
    [[nodiscard]] const Matrix4x4 &GetProjectionMatrix() const noexcept {
        return projectionMatrix_;
    }

    /// @brief ビュー投影行列を取得する
    /// @return ビュー投影行列
    [[nodiscard]] const Matrix4x4 &GetWVPMatrix() const noexcept {
        return wvpMatrix_;
    }

    /// @brief ビューポート行列を取得する
    /// @return ビューポート行列
    [[nodiscard]] const Matrix4x4 &GetViewportMatrix() const noexcept {
        return viewportMatrix_;
    }

private:
    AffineMatrix cameraMatrix_;
    Matrix4x4 worldMatrix_;
    Matrix4x4 viewMatrix_;
    Matrix4x4 projectionMatrix_;
    Matrix4x4 wvpMatrix_;
    Matrix4x4 viewportMatrix_;
};