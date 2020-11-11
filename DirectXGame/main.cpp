#include "WinApp.h"
#include "DirectXCommon.h"
#include "Audio.h"
#include "GameScene.h"
#include "BaseScene.h"
#include "SceneManager.h"
#include "Input.h"
#include "TitleScene.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// 汎用機能
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	GameScene* gameScene = nullptr;
	TitleScene* T_Scene = nullptr;
	SceneManager* smane = nullptr;

	// ゲームウィンドウの作成
	win = new WinApp();
	win->CreateGameWindow();

	//DirectX初期化処理
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(win);

#pragma region 汎用機能初期化
	// 入力の初期化
	input = new Input();
	if (!input->Initialize(win->GetInstance(), win->GetHwnd())) {
		assert(0);
		return 1;
	}
	// オーディオの初期化
	audio = new Audio();
	if (!audio->Initialize()) {
		assert(0);
		return 1;
	}
	// スプライト静的初期化
	if (!Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}

	// 3Dオブジェクト静的初期化
	if (!Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}

	// 3Dオブジェクト2静的初期化
	if (!Object3d2::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}

	// ボールの静的初期化
	if (!Ball::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}

	// ブロックの静的初期化
	if (!Block::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}

#pragma endregion

	// ゲームシーンの初期化
#pragma region //シーンマネージャー用＠Shu
	gameScene = new GameScene();
	gameScene->Initialize(dxCommon, input, audio);
	smane = new SceneManager();//追加ーーーー
	smane->Init(dxCommon, input, audio);

	smane->AddScene(SCENE::TITLE, new TitleScene());
	smane->AddScene(SCENE::GAME, new GameScene());
	smane->ChangeScene(GAME);//ここでシーン切り替え
#pragma endregion 

	// メインループ
	while (true)
	{
		// メッセージ処理
		if (win->ProcessMessage()) { break; }

		// 入力関連の毎フレーム処理
		input->Update();
		// ゲームシーンの毎フレーム処理
		smane->Update();

		// 描画開始
		dxCommon->PreDraw();
		// ゲームシーンの描画
		smane->Draw();

		if (input->PushKey(DIK_1))
		{
			smane->ChangeScene(TITLE);
		}
		if (input->PushKey(DIK_2))
		{
			smane->ChangeScene(GAME);
		}
	
		// 描画終了
		dxCommon->PostDraw();
	}
	// 各種解放
	safe_delete(smane);
	safe_delete(audio);
	safe_delete(input);
	safe_delete(dxCommon);
	

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();
	safe_delete(win);

	return 0;
}