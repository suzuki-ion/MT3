#include <Novice.h>
#include "MathFunctions/Vector3.h"
#include "MathFunctions/Matrix4x4.h"
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

        MatrixScreenPrintf(0, 0, Matrix4x4().MakeAffine(scale, rotate, translate), "worldMatrix");

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
