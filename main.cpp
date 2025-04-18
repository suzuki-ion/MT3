#include <Novice.h>
#include <imgui.h>
#include "MathFunctions/Vector3.h"
#include "MathFunctions/Matrix4x4.h"
#include "MathFunctions/AffineMatrix.h"
#include "MathFunctions/RenderingPipeline.h"
#include "MathFunctions/ScreenPrintf.h"
#include "MathFunctions/DrawGrid.h"
#include "MathFunctions/Sphere.h"
#include "MathFunctions/Lines.h"

float kWinWidth = 1280.0f;
float kWinHeight = 720.0f;
const char kWindowTitle[] = "LE2A_12_スズキ_イオン_MT3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
    Novice::Initialize(kWindowTitle, static_cast<int>(kWinWidth), static_cast<int>(kWinHeight));

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//--------- 変数 ---------//

    AffineMatrix cameraMatrix;
    Vector3 cameraTranslate = { 0.0f, 0.0f, -8.0f };
    Vector3 cameraRotate = { 0.3f, 0.0f, 0.0f };
    cameraMatrix.SetTranslate(cameraTranslate);
    cameraMatrix.SetRotate(cameraRotate);
    cameraMatrix.SetScale({ 1.0f, 1.0f, 1.0f });

    Segment segment{
        { -2.0f, -1.0f, 0.0f },
        { 3.0f, 2.0f, 2.0f }
    };
    Vector3 point = { -1.5f, 0.6f, 0.6f };
    Vector3 projection = (point - segment.origin).Projection(segment.diff);
    Vector3 closestPoint = point.ClosestPoint(segment);
    Sphere pointSphere{ point, 0.01f };
    Sphere closestPointSphere{ point.ClosestPoint(segment), 0.01f };
	
    Matrix4x4 worldMatrix;
	Matrix4x4 viewMatrix;
    Matrix4x4 projectionMatrix;
    Matrix4x4 wvpMatrix;
    Matrix4x4 viewportMatrix;
    
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
        ImGui::DragFloat3("Point", &point.x, 0.1f);
        ImGui::DragFloat3("SegmentOrigin", &segment.origin.x, 0.1f);
        ImGui::DragFloat3("SegmentDiff", &segment.diff.x, 0.1f);
        ImGui::InputFloat3("Projection", &projection.x, "%f.3f", ImGuiInputTextFlags_ReadOnly);
        ImGui::End();

        // 正射影ベクトルと最近接点を求める
        projection = (point - segment.origin).Projection(segment.diff);
        closestPoint = point.ClosestPoint(segment);
        pointSphere.SetCenter(point);
        closestPointSphere.SetCenter(closestPoint);

        // 各種行列の計算
		cameraMatrix.SetTranslate(cameraTranslate);
        cameraMatrix.SetRotate(cameraRotate);
		worldMatrix.MakeAffine({1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f});
        viewMatrix = cameraMatrix.InverseScale() * cameraMatrix.InverseRotate() * cameraMatrix.InverseTranslate();
        projectionMatrix = MakePerspectiveFovMatrix(0.45f, kWinWidth / kWinHeight, 0.1f, 100.0f);
        wvpMatrix = worldMatrix * (viewMatrix * projectionMatrix);
        viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, kWinWidth, kWinHeight, 0.0f, 1.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

        VectorScreenPrintf(0, 0, Vector3(0.0f).Transform(cameraMatrix.translateMatrix), "Camera Position");
        DrawGrid(wvpMatrix, viewportMatrix, 2.0f, 16);
        pointSphere.Draw(wvpMatrix, viewportMatrix, 16, RED);
        closestPointSphere.Draw(wvpMatrix, viewportMatrix, 16, BLACK);
        segment.Draw(wvpMatrix, viewportMatrix, WHITE);

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
