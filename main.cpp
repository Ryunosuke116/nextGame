#include "DxLib.h"
#include<vector>
#include"player.h"
#include"Camera.h"
#include "Map.h"

/// <summary>
/// メイン関数
/// </summary>
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	// 画面モードのセット
	ChangeWindowMode(TRUE);
	SetGraphMode(1600, 900, 16);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	Player* player = new Player();
	Camera* camera = new Camera();
	Map*	map	   = new Map();

	//初期化
	player->Initilize();

	//ロード
	map->Load();

	// エスケープキーが押されるかウインドウが閉じられるまでループ
	LONGLONG frameTime = 0;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		frameTime = GetNowHiPerformanceCount();

		player->Update(*map);
		camera->Update(*player);

		//画面の初期化
		ClearDrawScreen();

		// デバッグ描画
		// XYZ軸
		float lineSize = 300.0f;
		DrawLine3D(VGet(-lineSize, 0, 0), VGet(lineSize, 0, 0), GetColor(255, 0, 0));
		DrawLine3D(VGet(0, -lineSize, 0), VGet(0, lineSize, 0), GetColor(0, 255, 0));
		DrawLine3D(VGet(0, 0, -lineSize), VGet(0, 0, lineSize), GetColor(0, 0, 255));

		map->Draw();
		player->Draw();

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();

		// 雑に60fps固定
		while ((GetNowHiPerformanceCount() - frameTime) < 16667) {}
	}	


	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}