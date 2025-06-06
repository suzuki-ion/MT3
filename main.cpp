#include <Novice.h>
#include <imgui.h>
#include <cmath>

//--------- ベクトル・行列 ---------//
#include "MathFunctions/Vector3.h"
#include "MathFunctions/Matrix4x4.h"
#include "MathFunctions/AffineMatrix.h"

//--------- 描画関数 ---------//
#include "MathFunctions/ScreenPrintf.h"
#include "MathFunctions/DrawGrid.h"
#include "MathFunctions/Bezier.h"

//--------- 図形 ---------//
#include "MathFunctions/Sphere.h"
#include "MathFunctions/Lines.h"
#include "MathFunctions/Plane.h"
#include "MathFunctions/Triangle.h"
#include "MathFunctions/AABB.h"

//--------- カメラ ---------//
#include "MathFunctions/Camera.h"

//--------- 物理 ---------//
#include "Physics/Ball.h"
#include "Physics/Spring.h"
#include "Physics/Pendulum.h"
#include "Physics/ConicalPendulum.h"

extern const float kWinWidth = 1280.0f;
extern const float kWinHeight = 720.0f;
const char kWindowTitle[] = "LE2A_12_スズキ_イオン_MT3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
    Novice::Initialize(kWindowTitle, static_cast<int>(kWinWidth), static_cast<int>(kWinHeight));

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//--------- 変数 ---------//

    Camera camera(
		{ 0.0f, 0.0f, -8.0f },
		{ 0.3f, 0.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f }
	);

	Plane plane;
    plane.normal = Vector3(-0.2f, 0.9f, -0.3f).Normalize();
    plane.distance = 0.0f;

    Ball ball;
    ball.position = { 0.8f, 1.2f, 0.3f };
    ball.acceleration = { 0.0f, -9.8f, 0.0f };
    ball.velocity = { 0.0f, 0.0f, 0.0f };
    ball.mass = 2.0f;
    ball.radius = 0.05f;
    ball.color = 0xFFFFFFFF;

    float deltaTime = 1.0f / 60.0f;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

        ImGui::Begin("window");
        if (ImGui::Button("Start")) {
			ball.position = { 0.8f, 1.2f, 0.3f };
			ball.acceleration = { 0.0f, -9.8f, 0.0f };
			ball.velocity = { 0.0f, 0.0f, 0.0f };
        }
        ImGui::End();

        ball.velocity += ball.acceleration * deltaTime;
        ball.position += ball.velocity * deltaTime;
        if (plane.IsCollision(Sphere(ball.position, ball.radius))) {
            Vector3 reflected = ball.velocity.Refrection(plane.normal);
            Vector3 projectToNormal = reflected.Projection(plane.normal);
            Vector3 movingDirection = reflected - projectToNormal;
			ball.velocity = projectToNormal * 0.8f + movingDirection;
        }

        // カメラの移動
		if (!ImGui::IsAnyItemActive()) {
			camera.MoveToMouse(0.005f, 0.01f, 0.1f);
		}

        // 各種行列の計算
        camera.CalculateMatrix();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

        VectorScreenPrintf(0, 0, camera.GetTranslate(), "Camera Position");
        VectorScreenPrintf(0, 32, camera.GetRotate(), "Camera Rotation");
        DrawGrid(camera.GetWVPMatrix(), camera.GetViewportMatrix(), 2.0f, 16);
        plane.Draw(camera.GetWVPMatrix(), camera.GetViewportMatrix(), 0xFFFFFFFF);
        Sphere(ball.position, ball.radius).Draw(
            camera.GetWVPMatrix(), camera.GetViewportMatrix(), 16, ball.color);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
