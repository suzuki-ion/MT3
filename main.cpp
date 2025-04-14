#include <Novice.h>
#include "MathFunctions/Vector3.h"
#include "MathFunctions/Matrix4x4.h"
#include "MathFunctions/AffineMatrix.h"
#include "MathFunctions/RenderingPipeline.h"
#include "MathFunctions/ScreenPrintf.h"

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

	// クロス積の確認用
	Vector3 v1(1.2f, -3.9f, 2.5f);
    Vector3 v2(2.8f, 0.4f, -1.3f);

	const Vector3 kLocalVertices[3] = {
        Vector3(0.0f, 64.0f, 0.0f),
		Vector3(64.0f, -64.0f, 0.0f),
		Vector3(-64.0f, -64.0f, 0.0f)
	};
    Vector3 rotate = { 0.0f, 0.0f, 0.0f };
    Vector3 translate = { 0.0f, 0.0f, 256.0f };
    Vector3 cameraPosition = { 0.0f, 0.0f, 0.0f };

    Matrix4x4 worldMatrix;
    Matrix4x4 cameraMatrix;
	Matrix4x4 viewMatrix;
    Matrix4x4 projectionMatrix;
    Matrix4x4 wvpMatrix;
    Matrix4x4 viewportMatrix;
    Vector3 screenVertices[3];
    Vector3 ndcVertex;

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

		// WSキーで前後、ADキーで左右に移動
        if (keys[DIK_W]) {
            translate.z += 2.0f;
        }
        if (keys[DIK_S]) {
            translate.z -= 2.0f;
        }
        if (keys[DIK_A]) {
            translate.x -= 2.0f;
        }
        if (keys[DIK_D]) {
            translate.x += 2.0f;
        }

        rotate.y += 0.1f;

        // 各種行列の計算
		worldMatrix.MakeAffine({1.0f, 1.0f, 1.0f}, rotate, translate);
        cameraMatrix.MakeAffine({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, cameraPosition);
        viewMatrix = cameraMatrix.Inverse();
        projectionMatrix = MakePerspectiveFovMatrix(0.45f, kWinWidth / kWinHeight, 0.1f, 100.0f);
        wvpMatrix = worldMatrix * (viewMatrix * projectionMatrix);
        viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, kWinWidth, kWinHeight, 0.0f, 1.0f);
		for (int i = 0; i < 3; i++) {
            ndcVertex = kLocalVertices[i].Transform(wvpMatrix);
            screenVertices[i] = ndcVertex.Transform(viewportMatrix);
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

        VectorScreenPrintf(0, 0, v1.Cross(v2), "Cross");

        Novice::DrawTriangle(
            static_cast<int>(screenVertices[0].x),
            static_cast<int>(screenVertices[0].y),
            static_cast<int>(screenVertices[1].x),
            static_cast<int>(screenVertices[1].y),
            static_cast<int>(screenVertices[2].x),
            static_cast<int>(screenVertices[2].y),
            RED,
			kFillModeSolid
        );

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
