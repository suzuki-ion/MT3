#include <Novice.h>
#include <imgui.h>
#include "MathFunctions/Vector3.h"
#include "MathFunctions/Matrix4x4.h"
#include "MathFunctions/AffineMatrix.h"
#include "MathFunctions/ScreenPrintf.h"
#include "MathFunctions/DrawGrid.h"
#include "MathFunctions/Sphere.h"
#include "MathFunctions/Lines.h"
#include "MathFunctions/Plane.h"
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

    Vector3 cameraTranslate = { 0.0f, 0.0f, -8.0f };
    Vector3 cameraRotate = { 0.3f, 0.0f, 0.0f };
    Camera camera(cameraTranslate, cameraRotate, { 1.0f, 1.0f, 1.0f });

	Plane plane{
		{ 0.0f, 1.0f, 0.0f },
		1.0f
	};
    Segment segment{
        { -0.45f, 0.41f, 0.0f },
        { 1.0f, 0.58f, 0.0f }
    };
    
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
        ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.1f);
        ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.1f);
		ImGui::DragFloat3("Plane.Normal", &plane.normal.x, 0.1f);
		ImGui::DragFloat("Plane.Distance", &plane.distance, 0.1f);
        ImGui::DragFloat3("Segment.Origin", &segment.origin.x, 0.1f);
        ImGui::DragFloat3("Segment.Diff", &segment.diff.x, 0.1f);
        ImGui::End();

        // 各種行列の計算
        camera.SetTranslate(cameraTranslate);
        camera.SetRotate(cameraRotate);
        camera.CalculateMatrix();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

        VectorScreenPrintf(0, 0, Vector3(0.0f).Transform(camera.GetCameraMatrix().translateMatrix), "Camera Position");
        DrawGrid(camera.GetWVPMatrix(), camera.GetViewportMatrix(), 2.0f, 16);
        
        if (segment.IsCollision(plane)) {
            segment.Draw(camera.GetWVPMatrix(), camera.GetViewportMatrix(), RED);
        } else {
            segment.Draw(camera.GetWVPMatrix(), camera.GetViewportMatrix(), WHITE);
        }
        plane.Draw(camera.GetWVPMatrix(), camera.GetViewportMatrix(), WHITE);

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
