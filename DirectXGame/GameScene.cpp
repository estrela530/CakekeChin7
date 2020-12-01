#include "GameScene.h"

#include "BaseScene.h"
#include "SceneManager.h"
#include "Ball.h"

#include "Object3d.h"
#include <cassert>
#include <time.h>
#include <sstream>
#include <iomanip>

using namespace DirectX;


GameScene::GameScene()
{

}

GameScene::~GameScene()
{
	delete spriteBG;
	delete object3d;
	//	delete object3d2;//追加(SZK)
	delete ball;
	delete block;
	delete block1;
	delete block2;
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio * audio)
{

	// nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	blockGeneratorSeconds = 0;

	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	//new
	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(dTTN2, L"Resources/suuji.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	debugText2.Init(dTTN2);
	//new
	
	// テクスチャ読み込み
	if (!Sprite::LoadTexture(1, L"Resources/back1111.png")) {
		assert(0);
		return;
	}
	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	// 3Dオブジェクト生成
	object3d = Object3d::Create();
	object3d->Update();

	// 3Dオブジェクト2生成(SZK) 追加
	//object3d2 = Object3d2::Create();
	//object3d2->Update();

	//ボール生成
	ball = Ball::Create();
	ball->Update();
#pragma region 
	//生成ループ化のためにコメントアウト
	//ブロック1生成
	block = Block::Create();
	//ブロック2生成
	block1 = Block::Create();
	//ブロック3生成
	block2 = Block::Create();
	//ブロック4生成
	block3 = Block::Create();
	//ブロック5生成
	block4 = Block::Create();
	//ブロック6生成
	block5 = Block::Create();
	//ブロック7生成
	block6 = Block::Create();
	//ブロック8生成
	block7 = Block::Create();
	//ブロック9生成
	block8 = Block::Create();
	//ブロック10生成
	block9 = Block::Create();

	block->SetPosition({ 0,-30,50 });
	block1->SetPosition({ 0,-30,150 });
	block2->SetPosition({ 0,-30,250 });
	block3->SetPosition({ 0,-30,350 });
	block4->SetPosition({ 0,-30,450 });
	block5->SetPosition({ 0,-30,550 });
	block6->SetPosition({ 0,-30,650 });
	block7->SetPosition({ 0,-30,750 });
	block8->SetPosition({ 0,-30,850 });
	block9->SetPosition({ 0,-30,950 });
#pragma endregion
	//フェード
	alpha = 1;
	time = 0.0f;

}

void GameScene::Update()
{
#pragma region シュレフェード作
	//フェード
	time += 0.1f;
	//spriteBG->SetColor({ 1,1,1,alpha });//背景色
	//alpha -= 0.01f;
	//spriteBG->SetColor({ 1,1,0,alpha });
	if (alal == true)
	{

		alpha -= 0.01f;
		/*	cc-= 0.001f;
			if (cc < 1)
			{
				aa -= 0.005f;
			}
			if (aa >0)
			{
				aa += 0.005f;
				bb -= 0.005f;
			}
	*/
		spriteBG->SetColor({ aa,bb,cc,alpha });

		if (alpha < 0.35)
		{
			alal = false;
			aa -= 0.004f;
			bb -= 0.004f;
		}
	}
	else if (alal == false)
	{
		alpha += 0.01f;
		spriteBG->SetColor({ aa,bb,cc,alpha });
		cc += 0.005f;
		if (alpha > 1)
		{
			alal = true;
		}
		/*	if (aa < 0.3|| bb < 0.3)
			{
				aa += 0.004f;
				bb += 0.004f;
			}*/
	}
	if (aa < 0 || bb < 0)
	{
		aa += 0.04f;
		bb += 0.04f;
	}

	/*while (alpha < 0.3f)
	{
		spriteBG->SetColor({ 1,1,0,alpha });
	}*/
	//if (a>=0.6f)
	//{
	//	a -= 0.01f;
	//	spriteBG->SetColor({ 1,1,1,a });
	//}
	//else if(a<=0.6f )
	//{
	//	a += 0.01f;
	//	spriteBG->SetColor({ 1,1,1,a });
	//}
#pragma endregion
	//blockGeneratorSeconds += 1;
	////ブロック生成処理
	//for (int i = 0; i < 20; i++)
	//{
	//	if (blockGeneratorSeconds >= 2)
	//	{
	//		block = Block::Create();
	//		block->SetPosition({ 0,-30,450 });
	//		blockGeneratorSeconds = 0;
	//	}
	//}

#pragma region //(SZK・・・・復活させた↓)
	//(SZK・・・・復活させた↓)
	// 現在の座標を取得
	XMFLOAT3 position = object3d->GetPosition();

	// オブジェクト移動
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{

		//// 移動後の座標を計算
		//if (input->PushKey(DIK_UP)) { position.y += 1.0f; }
		//else if (input->PushKey(DIK_DOWN)) { position.y -= 1.0f; }
		//if (input->PushKey(DIK_RIGHT)) { position.x += 1.0f; }
		//else if (input->PushKey(DIK_LEFT)) { position.x -= 1.0f; }
	}
	// 座標の変更を反映
	object3d->SetPosition(position);
	object3d->Update();
	//(SZK・・・・復活させた↑)
#pragma endregion
#pragma region カメラまわり

	// カメラ移動
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{
		//if (input->PushKey(DIK_W)) { Ball::CameraMoveVector({ 0.0f,+1.0f,0.0f }); }
		//else if (input->PushKey(DIK_S)) { Ball::CameraMoveVector({ 0.0f,-1.0f,0.0f }); }
		//if (input->PushKey(DIK_D)) { Ball::CameraMoveVector({ +1.0f,0.0f,0.0f }); }
		//else if (input->PushKey(DIK_A)) { Ball::CameraMoveVector({ -1.0f,0.0f,0.0f }); }
	}


	// ボール移動
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT) || input->PushKey(DIK_SPACE))
	{
		//// 現在の座標を取得
		//XMFLOAT3 position = ball->GetPosition();

		//// 移動後の座標を計算
		//if (input->PushKey(DIK_UP)) { position.y += 1.0f; }
		//else if (input->PushKey(DIK_DOWN)) { position.y -= 1.0f; }
		//if (input->PushKey(DIK_RIGHT)) { position.x += 1.0f; }
		//else if (input->PushKey(DIK_LEFT)) { position.x -= 1.0f; }
		//if (input->PushKey(DIK_SPACE))
		//{
		//	position.z += 1.0f;
		//}
		//// 座標の変更を反映
		//ball->SetPosition(position);
	}

	// ブロック移動
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		// 現在の座標を取得
		//XMFLOAT3 position = ball->GetPosition();

		//// 移動後の座標を計算
		//if (input->PushKey(DIK_UP)) { position.y += 1.0f; }
		//else if (input->PushKey(DIK_DOWN)) { position.y -= 1.0f; }
		//if (input->PushKey(DIK_RIGHT)) { position.x += 1.0f; }
		//else if (input->PushKey(DIK_LEFT)) { position.x -= 1.0f; }

		//// 座標の変更を反映
		//block->SetPosition(position);
	}

#pragma region オブジェクト2の座標系
	// オブジェクト2の座標を取得
	//XMFLOAT3 position2 = object3d2->GetPosition();
	// オブジェクト2の座標の変更を反映
	//object3d2->SetPosition(position2);

#pragma endregion
#pragma endregion
#pragma region 当たり判定処理
	////ヒット通知
	//bool hit = false;
	////座標の差を求める
	//XMVECTOR pos_sub = XMVectorSet(
	//	position.x - position2.x,
	//	position.y - position2.y,
	//	position.z - position2.z,
	//	0);
	////2つの距離を計算
	//pos_sub = XMVector3Length(pos_sub);
	//float dist = pos_sub.m128_f32[0];

	//if (dist <= object3d->radius + object3d2->radius2)
	//{
	//	hit = true;
	//}

	//if (hit)
	//{
	//	ss = 1;
	//	debugText.Print("Hit", 0, 0, 10);
	//}

#pragma region 上限へ行ったらssを0に(SZK)

	//下に変更
	/*if (position2.y > 30)
	{
		ss = 0;
	}*/
#pragma endregion

#pragma region 変数1を使った重力加速(SZK)
	//下へ行く処理
	//if (ss == 0)
	//{
	//	fy = k * vy;//空気抵抗
	//	ay = g - (fy / m);//自由落下
	//	position2.y -= ay;
	//}
#pragma endregion

#pragma region 変数1を使った反発(SZK)
	//反発
	//if (ss == 1)
	//{
	//	fy = k * vy;//空気抵抗
	//	ay = g - (fy / m);//自由落下
	//	position2.y += ay;
	//}
#pragma endregion


#pragma endregion
#pragma region score 処理

	//座標読び
//※とりあえず動いた、細かい調整必要※
	bool score = true;

	if (score == true)
	{
		sco += 1;
	}
	else
	{
		score = true;
	}

	//ball->GetPosition
	debugText.Print("Score:", 50, 200, 1.0f);
	debugText2.Print2(std::to_string(sco).c_str(),
		110, 200, 1.0f);//数字出し方
//	char *numStr;
//	printf("%d\n", sco);

	//scanf()
		//	debugText.Print(, 110, 200, 3.0f);
		//
		//std::ostringstream spherestr;
		//XMVECTOR inter;
		//spherestr << "("
		//	<< std::fixed << std::setprecision(2)
		//	<< ball->GetPosition.m128_f32[0] << ","
		//	<< ball->GetPosition.m128_f32[1] << ","
		//	<< ball->GetPosition.m128_f32[2] << ")";
		//
		//
		//spherestr.str("");
		//spherestr.clear();
		//spherestr << "("
		//	<< std::fixed << std::setprecision(2)
		//	<< inter.m128_f32[0] << ","
		//	<< inter.m128_f32[1] << ","
		//	<< inter.m128_f32[2] << ")";

#pragma endregion 


	// 座標の変更を反映
	object3d->SetPosition(position);
	object3d->Update();
	ball->Update();
	block->Update();
	block1->Update();
	block2->Update();
	block3->Update();
	block4->Update();
	block5->Update();
	block6->Update();
	block7->Update();
	block8->Update();
	block9->Update();


}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	ID3D12GraphicsCommandList* cmdList2 = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	spriteBG->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);

	// 3Dオブジェクト2描画前処理
	//Object3d2::PreDraw(cmdList);

	//ボール描画前処理
	Ball::PreDraw(cmdList);

	//ブロック描画前処理
	Block::PreDraw(cmdList);

	// 3Dオブクジェクトの描画
	//object3d->Draw();

	//// 3Dオブクジェクト2の描画
	//object3d2->Draw();
#pragma region Ball

	////ボールの描画
	ball->Draw();

	//ブロックの描画
	block->Draw();
	//ブロック2の描画
	block1->Draw();
	//ブロック3の描画
	block2->Draw();
	//ブロック4の描画
	block3->Draw();
	//ブロック5の描画
	block4->Draw();
	//ブロック6の描画
	block5->Draw();
	//ブロック7の描画
	block6->Draw();
	//ブロック8の描画
	block7->Draw();
	//ブロック9の描画
	block8->Draw();
	//ブロック10の描画
	block9->Draw();

#pragma endregion 

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();

	// 3Dオブジェクト2描画後処理
	//Object3d2::PostDraw();

	//ボール描画後処理
	Ball::PostDraw();

	//ブロック描画後処理
	Block::PostDraw();

#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion


	Sprite::PreDraw(cmdList2);
	debugText2.DrawAll2(cmdList2);
	Sprite::PostDraw();
}
