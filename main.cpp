#include <Novice.h>
#include "MathFunctions/Vector3.h"
#include "MathFunctions/Matrix4x4.h"
#include "MathFunctions/AffineMatrix.h"
#include "MathFunctions/RenderingPipeline.h"
#include "MathFunctions/ScreenPrintf.h"

const char kWindowTitle[] = "LE2A_12_スズキ_イオン_MT3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//--------- 変数 ---------//

	Vector3 scale(1.2f, 0.79f, -2.1f);
    Vector3 rotate(0.4f, 1.43f, -0.8f);
    Vector3 translate(2.7f, -4.15f, 1.57f);
    AffineMatrix affineMatrix(scale, rotate, translate);

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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

        MatrixScreenPrintf(
			0, 0,
			MakeOrthographicMatrix(-160.0f, 160.0f, 200.0f, 300.0f, 0.0f, 1000.0f),
			"orthographicsMatrix"
		);
        MatrixScreenPrintf(0, 16 * 5,
			MakePerspectiveFovMatrix(0.63f, 1.33f, 0.1f, 1000.0f),
			"perspectiveFovMatrix"
		);
        MatrixScreenPrintf(0, 16 * 10,
			MakeViewportMatrix(100.0f, 200.0f, 600.0f, 300.0f, 0.0f, 1.0f),
			"viewportMatrix"
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
