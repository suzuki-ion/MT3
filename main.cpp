#include <Novice.h>
#include <imgui.h>

//--------- ベクトル・行列 ---------//
#include "MathFunctions/Vector3.h"
#include "MathFunctions/Matrix4x4.h"
#include "MathFunctions/AffineMatrix.h"

//--------- 描画関数 ---------//
#include "MathFunctions/ScreenPrintf.h"
#include "MathFunctions/DrawGrid.h"

//--------- 図形 ---------//
#include "MathFunctions/Sphere.h"
#include "MathFunctions/Lines.h"
#include "MathFunctions/Plane.h"
#include "MathFunctions/Triangle.h"
#include "MathFunctions/AABB.h"

//--------- カメラ ---------//
#include "MathFunctions/Camera.h"

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

	AABB aabb1(
        { -0.5f, -0.5f, -0.5f },
		{ 0.0f, 0.0f, 0.0f }
	);
    AABB aabb2(
        { 0.2f, 0.2f, 0.2f },
        { 1.0f, 1.0f, 1.0f }
    );
    
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
        ImGui::DragFloat3("AABB1.Min", &aabb1.min.x, 0.1f);
        ImGui::DragFloat3("AABB1.Max", &aabb1.max.x, 0.1f);
        ImGui::DragFloat3("AABB2.Min", &aabb2.min.x, 0.1f);
        ImGui::DragFloat3("AABB2.Max", &aabb2.max.x, 0.1f);
        ImGui::End();

        // カメラの移動
        camera.MoveToMouse(0.005f, 0.01f, 0.1f);

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
        if (aabb1.IsCollision(aabb2)) {
            aabb1.Draw(camera.GetWVPMatrix(), camera.GetViewportMatrix(), RED);
        } else {
            aabb1.Draw(camera.GetWVPMatrix(), camera.GetViewportMatrix(), WHITE);
        }
        aabb2.Draw(camera.GetWVPMatrix(), camera.GetViewportMatrix(), WHITE);

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
