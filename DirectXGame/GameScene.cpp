#include "GameScene.h"
#include "BaseScene.h"
#include "SceneManager.h"
//#include "BlockManager.h"
#include "Object3d.h"
#include <cassert>
#include <iostream>
#include <ctime>
#include "Ball.h"

#include <time.h>
#include <sstream>
#include <iomanip>

using namespace DirectX;
using namespace std;

int ss = 0;
float k = 1.0f;
float t = 0.0f;
float m = 8.0f;//質量
float v = 1.0f;
float g = 2.5f;//重力加速度
float ve;
float vy = 0.5f;//物体の速度
float fy;//Y軸に働く力
float ay;//Y軸の加速度

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete spriteBG;
	delete object3d;
	delete score;
	delete ball;

#pragma region BlockManager作成に伴いコメントアウト
	//delete block;
	//delete block1;
	//delete block2;
#pragma endregion
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
	//上記テクスチャ

	//下記背景

	// テクスチャ読み込み
	if (!Sprite::LoadTexture(1, L"Resources/back1111.png")) {
		assert(0);
		return;
	}
	//スコア
	if (!Sprite::LoadTexture(1, L"Resources/score.png")) {
		assert(0);
		return;
	}




	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	// 3Dオブジェクト生成
	object3d = Object3d::Create();
	//zahyou 
	score = Sprite::Create(1, { 1,126 });//スコア画像サイズ
	score->Sprite::SetSize({ 135.0f,38.0f });//画像サイズ
	object3d->Update();



	//ボール生成
	ball = Ball::Create();
	ball->Update();

#pragma region BlockManager作成に伴いコメントアウト
	////生成ループ化のためにコメントアウト
	//ブロック1生成
	//block = Block::Create();
	////ブロック2生成
	//block1 = Block::Create();
	////ブロック3生成
	//block2 = Block::Create();
	////ブロック4生成
	//block3 = Block::Create();
	////ブロック5生成
	//block4 = Block::Create();
	////ブロック6生成
	//block5 = Block::Create();
	////ブロック7生成
	//block6 = Block::Create();
	////ブロック8生成
	//block7 = Block::Create();
	////ブロック9生成
	//block8 = Block::Create();
	//ブロック10生成
	block9 = Block::Create();

	//block->SetPosition({ 0,-30,150 });

	//block->SetPosition({ 0,-30,50 });
	//block1->SetPosition({ 0,-30,150 });
	//block2->SetPosition({ 0,-30,250 });
	//block3->SetPosition({ 0,-30,350 });
	//block4->SetPosition({ 0,-30,450 });
	//block5->SetPosition({ 0,-30,550 });
	//block6->SetPosition({ 0,-30,650 });
	//block7->SetPosition({ 0,-30,750 });
	//block8->SetPosition({ 0,-30,850 });
	block9->SetPosition({ 0,-30,950 });
#pragma endregion


	//フェード
	alpha = 0;

	notBallJumpSeconds = 0;

}

void GameScene::Update()
{
#pragma region シュレフェード試作
	//フェード
	alpha += 0.01f;
	spriteBG->SetColor({ 1,1,1,alpha });//背景色

	notBallJumpSeconds += 1;

	time += 0.1f;
	//spriteBG->SetColor({ 1,1,1,alpha });//背景色
	//alpha -= 0.01f;
	//spriteBG->SetColor({ 1,1,0,alpha });
	if (alal == true)
	{

		alpha -= 0.01f;
		cc -= 0.001f;
		if (cc < 1)
		{
			aa -= 0.005f;
		}
		if (aa > 0)
		{
			aa += 0.005f;
			bb -= 0.005f;
		}

		spriteBG->SetColor({ aa,bb,cc,alpha });

		/*if (alpha < 0.35)
		{
			alal = false;
			aa -= 0.004f;
			bb -= 0.004f;
		}*/
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
		else if (aa < 0.3)
		{
			aa += 0.004f;
			bb += 0.004f;
		}
	}
	if (aa < 0 || bb < 0)
	{
		aa += 0.04f;
		bb += 0.04f;
	}


#pragma endregion


#pragma region BlockManager作成に伴い追加

	//BlockManager::AddBlock(block);

	blockCreateTime += 1;

	if (blockCreateTime > 30)
	{
		block = Block::Create();
		blockXPosition = rand() % 101 + (-50);
		block->SetPosition({ blockXPosition,-30,550 });
		blocks.push_back(block);
		blockCreateTime = 0;
	}
	//blocks.push_back(block);
	//blocks.push_back(block1);
	//blockCreateTime = 0;


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
	XMFLOAT3 ballPosition = ball->GetPosition();

#pragma region BlockManager作成に伴いコメントアウト
	//XMFLOAT3 blockPosition = block->GetPosition();
	//XMFLOAT3 block1Position = block1->GetPosition();
	//XMFLOAT3 block2Position = block2->GetPosition();
	//XMFLOAT3 block3Position = block3->GetPosition();
	//XMFLOAT3 block4Position = block4->GetPosition();
	//XMFLOAT3 block5Position = block5->GetPosition();
	//XMFLOAT3 block6Position = block6->GetPosition();
	//XMFLOAT3 block7Position = block7->GetPosition();
	//XMFLOAT3 block8Position = block8->GetPosition();
	//XMFLOAT3 block9Position = block9->GetPosition();
#pragma endregion


	//// オブジェクト移動
	//if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	//{
	//	//// 移動後の座標を計算
	//	//if (input->PushKey(DIK_UP)) { position.y += 1.0f; }
	//	//else if (input->PushKey(DIK_DOWN)) { position.y -= 1.0f; }
	//	//if (input->PushKey(DIK_RIGHT)) { position.x += 1.0f; }
	//	//else if (input->PushKey(DIK_LEFT)) { position.x -= 1.0f; }
	//}
	// 座標の変更を反映
	object3d->SetPosition(position);
	object3d->Update();
	//(SZK・・・・復活させた↑)
#pragma endregion

#pragma region カメラまわり

	// カメラ移動
	/*if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{*/
	//if (input->PushKey(DIK_W)) { Ball::CameraMoveVector({ 0.0f,+1.0f,0.0f }); }
	//else if (input->PushKey(DIK_S)) { Ball::CameraMoveVector({ 0.0f,-1.0f,0.0f }); }
	//if (input->PushKey(DIK_D)) { Ball::CameraMoveVector({ +1.0f,0.0f,0.0f }); }
	//else if (input->PushKey(DIK_A)) { Ball::CameraMoveVector({ -1.0f,0.0f,0.0f }); }
//}

// ボール移動
//if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT) || input->PushKey(DIK_SPACE))
//{
//	//// 現在の座標を取得
//	//XMFLOAT3 position = ball->GetPosition();

//	//// 移動後の座標を計算
//	//if (input->PushKey(DIK_UP)) { position.y += 1.0f; }
//	//else if (input->PushKey(DIK_DOWN)) { position.y -= 1.0f; }
//	//if (input->PushKey(DIK_RIGHT)) { position.x += 1.0f; }
//	//else if (input->PushKey(DIK_LEFT)) { position.x -= 1.0f; }
//	//if (input->PushKey(DIK_SPACE))
//	//{
//	//	position.z += 1.0f;
//	//}
//	//// 座標の変更を反映
//	//ball->SetPosition(position);
//}

//// ブロック移動
//if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
//{
//	// 現在の座標を取得
//	//XMFLOAT3 position = ball->GetPosition();

//	//// 移動後の座標を計算
//	//if (input->PushKey(DIK_UP)) { position.y += 1.0f; }
//	//else if (input->PushKey(DIK_DOWN)) { position.y -= 1.0f; }
//	//if (input->PushKey(DIK_RIGHT)) { position.x += 1.0f; }
//	//else if (input->PushKey(DIK_LEFT)) { position.x -= 1.0f; }

//	//// 座標の変更を反映
//	//block->SetPosition(position);
//}

#pragma region オブジェクト2の座標系
	// オブジェクト2の座標を取得
	//XMFLOAT3 position2 = object3d2->GetPosition();
	// オブジェクト2の座標の変更を反映
	//object3d2->SetPosition(position2);

#pragma endregion
#pragma endregion

#pragma region 当たり判定処理
	//ヒット通知
	bool hit = false;

#pragma region BlockManager作成に伴いコメントアウト
	////座標の差を求める
	//XMVECTOR pos_sub = XMVectorSet(
	//	blockPosition.x - ballPosition.x,
	//	blockPosition.y - ballPosition.y,
	//	blockPosition.z - ballPosition.z,
	//	0);

	////座標の差を求める
	//XMVECTOR pos_sub1 = XMVectorSet(
	//	block1Position.x - ballPosition.x,
	//	block1Position.y - ballPosition.y,
	//	block1Position.z - ballPosition.z,
	//	0);
	////座標の差を求める
	//XMVECTOR pos_sub2 = XMVectorSet(
	//	block2Position.x - ballPosition.x,
	//	block2Position.y - ballPosition.y,
	//	block2Position.z - ballPosition.z,
	//	0);
	////座標の差を求める
	//XMVECTOR pos_sub3 = XMVectorSet(
	//	block3Position.x - ballPosition.x,
	//	block3Position.y - ballPosition.y,
	//	block3Position.z - ballPosition.z,
	//	0);
	////座標の差を求める
	//XMVECTOR pos_sub4 = XMVectorSet(
	//	block4Position.x - ballPosition.x,
	//	block4Position.y - ballPosition.y,
	//	block4Position.z - ballPosition.z,
	//	0);
	////座標の差を求める
	//XMVECTOR pos_sub5 = XMVectorSet(
	//	block5Position.x - ballPosition.x,
	//	block5Position.y - ballPosition.y,
	//	block5Position.z - ballPosition.z,
	//	0);
	////座標の差を求める
	//XMVECTOR pos_sub6 = XMVectorSet(
	//	block6Position.x - ballPosition.x,
	//	block6Position.y - ballPosition.y,
	//	block6Position.z - ballPosition.z,
	//	0);
	////座標の差を求める
	//XMVECTOR pos_sub7 = XMVectorSet(
	//	block7Position.x - ballPosition.x,
	//	block7Position.y - ballPosition.y,
	//	block7Position.z - ballPosition.z,
	//	0);
	////座標の差を求める
	//XMVECTOR pos_sub8 = XMVectorSet(
	//	block8Position.x - ballPosition.x,
	//	block8Position.y - ballPosition.y,
	//	block8Position.z - ballPosition.z,
	//	0);
	////座標の差を求める
	//XMVECTOR pos_sub9 = XMVectorSet(
	//	block9Position.x - ballPosition.x,
	//	block9Position.y - ballPosition.y,
	//	block9Position.z - ballPosition.z,
	//	0);

	////2つの距離を計算
	//pos_sub = XMVector3Length(pos_sub);
	//float dist = pos_sub.m128_f32[0];

	////2つの距離を計算
	//pos_sub1 = XMVector3Length(pos_sub1);
	//float dist1 = pos_sub1.m128_f32[0];
	////2つの距離を計算
	//pos_sub2 = XMVector3Length(pos_sub2);
	//float dist2 = pos_sub2.m128_f32[0];
	////2つの距離を計算
	//pos_sub3 = XMVector3Length(pos_sub3);
	//float dist3 = pos_sub3.m128_f32[0];
	////2つの距離を計算
	//pos_sub4 = XMVector3Length(pos_sub4);
	//float dist4 = pos_sub4.m128_f32[0];
	////2つの距離を計算
	//pos_sub5 = XMVector3Length(pos_sub5);
	//float dist5 = pos_sub5.m128_f32[0];
	////2つの距離を計算
	//pos_sub6 = XMVector3Length(pos_sub6);
	//float dist6 = pos_sub6.m128_f32[0];
	////2つの距離を計算
	//pos_sub7 = XMVector3Length(pos_sub7);
	//float dist7 = pos_sub7.m128_f32[0];
	////2つの距離を計算
	//pos_sub8 = XMVector3Length(pos_sub8);
	//float dist8 = pos_sub8.m128_f32[0];


	////if (dist <= ballPosition.y + blockPosition.y || 
	////	dist <= ballPosition.y + block1Position.y || 
	////	dist <= ballPosition.y + block2Position.y)
	////{
	////	hit = true;
	////}
	///*if(ballPosition.y <= -20 && notBallJumpSeconds < 600)
	//{
	//	hit = true;
	//}*/


	//if (dist <= ball->radius + block->radius)
	//{
	//	hit = true;
	//}
	//if (dist1 <= ball->radius + block1->radius)
	//{
	//	hit = true;
	//}
	//if (dist2 <= ball->radius + block2->radius)
	//{
	//	hit = true;
	//}
	//if (dist3 <= ball->radius + block3->radius)
	//{
	//	hit = true;
	//}
	//if (dist4 <= ball->radius + block4->radius)
	//{
	//	hit = true;
	//}
	//if (dist5 <= ball->radius + block5->radius)
	//{
	//	hit = true;
	//}
	//if (dist6 <= ball->radius + block6->radius)
	//{
	//	hit = true;
	//}
	//if (dist7 <= ball->radius + block7->radius)
	//{
	//	hit = true;
	//}
	//if (dist8 <= ball->radius + block8->radius)
	//{
	//	hit = true;
	//}
#pragma endregion

#pragma region 新しい挙動まわりの処理(SZK)
	ballPosition.y -= g;//重力
	if (hit)
	{
		//ss = 1;
		sec += 1;
		k -= 0.1;

		ballPosition.y += k;//反発
		if (sec > 38)
		{
			hit = false;
			k = 7.0;
			sec = 0;
		}
		debugText.Print("Hit", 0, 0, 10);
	}
	else
	{
		k = 5.5;
	}

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
	debugText2.Print2(std::to_string(sco).c_str(),140, 130, 1.0f);//スコア座標
#pragma endregion 

	// 座標の変更を反映
	object3d->SetPosition(position);
	ball->SetPosition(ballPosition);
	object3d->Update();
	ball->Update();

#pragma region BlockManager作成に伴い追加

	/*for (size_t i = 0; i < BlockManager::blocks.size(); i++)
	{
		BlockManager::Update(i);
	}*/

	/*for (size_t i = 0; i < blocks.size(); i++)
	{
		blocks.at(i)->Update();
	}*/

	for (Block* &x : blocks)
	{
		x->Update();
	}


	//blocks.at(0)->Update();
	//blocks.at(1)->Update();

#pragma endregion
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
	score->Draw();
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

	////ボールの描画
	ball->Draw();

#pragma region BlockManager作成に伴い追加

	/*for (size_t i = 0; i < BlockManager::blocks.size(); i++)
	{
		BlockManager::Draw(i);
	}*/

	/*for (size_t i = 0; i < blocks.size(); i++)
	{
		blocks.at(i)->Draw();
	}*/

	for (Block* &x : blocks)
	{
		x->Draw();
	}

#pragma endregion


#pragma region BlockManager作成に伴いコメントアウト
	////ブロックの描画
	//block->Draw();
	////ブロック2の描画
	//block1->Draw();
	////ブロック3の描画
	//block2->Draw();
	////ブロック4の描画
	//block3->Draw();
	////ブロック5の描画
	//block4->Draw();
	////ブロック6の描画
	//block5->Draw();
	////ブロック7の描画
	//block6->Draw();
	////ブロック8の描画
	//block7->Draw();
	////ブロック9の描画
	//block8->Draw();
	////ブロック10の描画
	////block9->Draw();
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

#pragma region スコア数字

	Sprite::PreDraw(cmdList2);
	debugText2.DrawAll2(cmdList2);
	Sprite::PostDraw();

#pragma endregion

}