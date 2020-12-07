#include "SceneManager.h"
#include "TitleScene.h"

#include <cassert>//ヘッダで式が真であることを表す


TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	delete spriteBG;
	delete wip;
}


void TitleScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	//nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/title.png"))
	{
		assert(0);
		return;
	}
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	if (!Sprite::LoadTexture(1, L"Resources/title.png")) {
		assert(0);
		return;
	}

	if (!Sprite::LoadTexture(1, L"Resources/tex1.png"))
	{
		assert(0);
		return;
	}

	///	// 3Dオブジェクト生成
	//object3d = Object3d::Create();
	//object3d->Update();
	//背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	//ワイプ生成処
	wip = Sprite::Create(1, { 0.0f,0.0 });
	wip->Sprite::SetSize({ 128.0f,72.0f });//実験３
	//spriteBG->SetPosition({ 100,100 });
	alpha = 0;
	//alpha2 = 1;
	timer = 0.0f;

}


void TitleScene::Update()
{
	alpha += 0.0095f;
	timer += 1;		
	spriteBG->SetColor({ 1,1,1,alpha });//テクスチャの色とα値名

	if (wips == false)
	{
		if (alpha > 1.0f)
		{
			//debugText.Print(std::string&,)
			wips = true;
		}
	}
	else if (wips == true)
	{

		//	alpha2 -= 0.0095f;
			//wip->SetColor({ 1,1,1,alpha2 });
		if (timer <=1000)
		{
			wips = false;
			//delete wip;
		}
	}




}

void TitleScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	spriteBG->Draw();
	wip->Draw();

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

#pragma region ワイプ




#pragma endregion 
}
