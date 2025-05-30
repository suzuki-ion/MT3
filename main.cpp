#include <Novice.h>
#include <imgui.h>

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

	Vector3 translates[3] = {
		{ 0.2f, 1.0f, 0.0f },
		{ 0.4f, 0.0f, 0.0f },
		{ 0.3f, 0.0f, 0.0f }
    };

	Vector3 rotates[3] = {
        { 0.0f, 0.0f, -6.8f },
        { 0.0f, 0.0f, -1.4f },
        { 0.0f, 0.0f, 0.0f }
    };

	Vector3 scales[3] = {
		{ 1.0f, 1.0f, 1.0f },
        { 1.0f, 1.0f, 1.0f },
        { 1.0f, 1.0f, 1.0f }
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
        ImGui::DragFloat3("translates[0]", &translates[0].x, 0.01f);
        ImGui::DragFloat3("rotates[0]", &rotates[0].x, 0.01f);
        ImGui::DragFloat3("scales[0]", &scales[0].x, 0.01f);
        ImGui::DragFloat3("translates[1]", &translates[1].x, 0.01f);
        ImGui::DragFloat3("rotates[1]", &rotates[1].x, 0.01f);
        ImGui::DragFloat3("scales[1]", &scales[1].x, 0.01f);
        ImGui::DragFloat3("translates[2]", &translates[2].x, 0.01f);
        ImGui::DragFloat3("rotates[2]", &rotates[2].x, 0.01f);
        ImGui::DragFloat3("scales[2]", &scales[2].x, 0.01f);
        ImGui::End();

        // カメラの移動
		if (!ImGui::IsAnyItemActive()) {
			camera.MoveToMouse(0.005f, 0.01f, 0.1f);
		}

        // 各種行列の計算
        camera.CalculateMatrix();

		// 描画用の行列の計算
		AffineMatrix localMatrix[3];
		localMatrix[0].SetSRT(scales[0], rotates[0], translates[0]);
        localMatrix[1].SetSRT(scales[1], rotates[1], translates[1]);
        localMatrix[2].SetSRT(scales[2], rotates[2], translates[2]);
        Matrix4x4 worldMatrix[3];
		worldMatrix[0] = localMatrix[0].GetWorldMatrix();
        worldMatrix[1] = localMatrix[1].GetWorldMatrix() * worldMatrix[0];
        worldMatrix[2] = localMatrix[2].GetWorldMatrix() * worldMatrix[1];

		Sphere sphere[3];
        sphere[0] = Sphere(Vector3().Transform(worldMatrix[0]), 0.05f);
        sphere[1] = Sphere(Vector3().Transform(worldMatrix[1]), 0.05f);
        sphere[2] = Sphere(Vector3().Transform(worldMatrix[2]), 0.05f);

		Segment segment[2] = {
            { sphere[0].center, sphere[1].center - sphere[0].center },
            { sphere[1].center, sphere[2].center - sphere[1].center }
        };

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

        VectorScreenPrintf(0, 0, camera.GetTranslate(), "Camera Position");
        VectorScreenPrintf(0, 32, camera.GetRotate(), "Camera Rotation");
        DrawGrid(camera.GetWVPMatrix(), camera.GetViewportMatrix(), 2.0f, 16);
        segment[0].Draw(camera.GetWVPMatrix(), camera.GetViewportMatrix(), 0xFFFFFFFF);
        segment[1].Draw(camera.GetWVPMatrix(), camera.GetViewportMatrix(), 0xFFFFFFFF);
        sphere[0].Draw(camera.GetWVPMatrix(), camera.GetViewportMatrix(), 16, 0xFF0000FF);
        sphere[1].Draw(camera.GetWVPMatrix(), camera.GetViewportMatrix(), 16, 0x00FF00FF);
        sphere[2].Draw(camera.GetWVPMatrix(), camera.GetViewportMatrix(), 16, 0x0000FFFF);

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
