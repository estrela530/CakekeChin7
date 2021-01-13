#include "ResultScene.h"
#include <cassert>//ヘッダで式が真であることを表す


ResultScene::ResultScene(SceneManager* smane) :smane(smane)
{
}

ResultScene::~ResultScene()
{
	delete spriteBG;

}


void ResultScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	//nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/RESULT.png"))
	{
		assert(0);
		return;
	}
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	if (!Sprite::LoadTexture(1, L"Resources/Result555.png")) {
		assert(0);
		return;
	}

	///	// 3Dオブジェクト生成
	//object3d = Object3d::Create();
	//object3d->Update();
	//背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });

	fade = 0;
}


void ResultScene::Update()
{
	fade += 0.004f;
	spriteBG->SetColor({ 1,1,1,fade });

	//	//↓岩﨑変更
	//	/*debugText.Print(gameScene->sco)*/
		////debugText2.Print2(std::to_string(gameScene->sco).c_str(), 140, 130, 1.0f);//スコア座標
		////debugText.Print(ranking->scoreRankingVec.begin(), 160, 150, 1.0f);//スコア座標
		////debugText.Print("Hit", 160, 150, 1.0f);//スコア座標

	if (input->PushKey(DIK_SPACE))
	{
		smane->ChangeScene(SCENE::TITLE);
	}

}

void ResultScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	spriteBG->Draw();


	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();

	Sprite::PreDraw(cmdList);

	//デバッグテキストの描画
	debugText.DrawAll(cmdList);
	//スプライト描画後の処理
	Sprite::PostDraw();
#pragma endregion 

}
