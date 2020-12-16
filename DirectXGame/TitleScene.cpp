#include "SceneManager.h"
#include "TitleScene.h"
#include "WinApp.h"

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
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png"))
	{
		assert(0);
		return;
	}
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み	↓1番目に読込
	if (!Sprite::LoadTexture(1, L"Resources/title.png")) {
		assert(0);
		return;
	}
	//画像					↓二番目に読込
	if (!Sprite::LoadTexture(2, L"Resources/tex1.png"))
	{
		assert(0);
		return;
	}

	// 3Dオブジェクト生成
	//object3d = Object3d::Create();
	//object3d->Update();
	//背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });

#pragma region wip
	//x,y
	wip_x = 0.0f;
	wip_y = 0.0f;
	timer = 0;
	wip = Sprite::Create(2, { wip_x,wip_y });
	//ワイプ生成処
	//wip->Sprite::SetPosition({ 0,0 });
	wip->Sprite::SetSize({ wip_x ,wip_y });//


//spriteBG->SetPosition({ 100,100 });
#pragma endregion
	alpha = 0;
	//alpha2 = 1;
}


void TitleScene::Update()
{
#pragma region BGM再生
	//※変更必要（「.wav」のデータResourcesフォルダに入れたやつ読み込めず{Alarm01.wav}のみ再生可）
	//audio->PlayWaveBGM("Resources/Alarm01.wav");
#pragma endregion

	alpha += 0.01f;
	timer += 1;
	spriteBG->SetColor({ 1,1,1,alpha });//テクスチャの色とα値名
	wip->SetColor({ 0,0,0,1 });
	//if (wips == false)
	//{
	//wip->SetColor({ 0,1,1,alpha });

	if (alpha > 0.9f)
	{
		if (wips == false)
		{
			//wip->SetPosition({ wip_x,wip_y });
			wip_x += 7;
			wip_y += 4;
			wip->Sprite::SetSize({ wip_x,wip_y });
			if (wip_x > 1280)
			{
				wips = true;
			}
			
		}
		else if (wips == true)
		{
			if (wip_x > 1280)
			{
				wip_x += 0;
				wip_y+= 0;
				wip->Sprite::SetSize({ wip_x,wip_y });

				wips == true;
			}
			if (input->PushKey(DIK_1)|| input->PushKey(DIK_2))
			{
				wips = false;
			}

		}
	}

	//}
	//else if (wips == true)
	//{
	//	//alpha2 -= 0.0095f;
	//	//wip->SetColor({ 1,1,1,alpha2 });
	//	wips = false;
	//	//delete wip;
	//}
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
