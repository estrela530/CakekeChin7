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

//SZK　変数
int ss = 0;
float k = 1.0f;
float g = 2.5f;//重力加速度
float ve;
int sec = 0;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete spriteBG;
	delete object3d;
	delete score;
	delete ball;

#pragma region 最初の確定沸きBlock5っ
	delete block1;
	delete block2;
	delete block3;
	delete block4;
	delete block5;
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

#pragma region 最初の確定沸きBlock5っ

	//ブロック1生成
	block1 = Block::Create();
	//ブロック2生成
	block2 = Block::Create();
	//ブロック3生成
	block3 = Block::Create();
	//ブロック4生成
	block4 = Block::Create();
	//ブロック5生成
	block5 = Block::Create();

	block1->SetPosition({ 0,-30,50 }); //変更前　150
	block2->SetPosition({ 0,-30,200 });
	block3->SetPosition({ 0,-30,380 });
	block4->SetPosition({ 0,-30,560 });
	block5->SetPosition({ 0,-30,740 });

#pragma endregion

	//フェード
	alpha = 0;

	notBallJumpSeconds = 0;
}

void GameScene::Update()
{
#pragma region BGM再生
	//※変更必要（「.wav」のデータResourcesフォルダに入れたやつ読み込めず{Alarm01.wav}のみ再生可）
	audio->PlayWave("Resources/Alarm01.wav");
#pragma endregion


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


#pragma region Blockのランダム生成＆連続生成

	blockCreateTime += 1;

	if (blockCreateTime > 57)
	{
		block = Block::Create();
		blockXPosition = rand() % 101 + (-50);
		block->SetPosition({ blockXPosition,-30,730 });//変更前　ｚ座標　550
		blocks.push_back(block);
		blockCreateTime = 0;
	}

#pragma endregion

#pragma region //(SZK・・・・復活させた↓)
	//(SZK・・・・復活させた↓)
	// 現在の座標を取得
	XMFLOAT3 position = object3d->GetPosition();
	XMFLOAT3 ballPosition = ball->GetPosition();

	// オブジェクト移動
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		// 移動後の座標を計算
		if (input->PushKey(DIK_RIGHT)) { ballPosition.x += 1.0f; }
		else if (input->PushKey(DIK_LEFT)) { ballPosition.x -= 1.0f; }
	}
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

#pragma region 最初の確定沸きBlock5っ

	XMFLOAT3 block1Position = block1->GetPosition();
	XMFLOAT3 block2Position = block2->GetPosition();
	XMFLOAT3 block3Position = block3->GetPosition();
	XMFLOAT3 block4Position = block4->GetPosition();
	XMFLOAT3 block5Position = block5->GetPosition();

#pragma endregion

#pragma region 当たり判定処理

#pragma region 最初の確定沸きBlock5っ

#pragma region 座標の差を求める

	//座標の差を求める
	XMVECTOR pos_sub1 = XMVectorSet(
		block1Position.x - ballPosition.x,
		block1Position.y - ballPosition.y,
		block1Position.z - ballPosition.z,
		0);
	//座標の差を求める
	XMVECTOR pos_sub2 = XMVectorSet(
		block2Position.x - ballPosition.x,
		block2Position.y - ballPosition.y,
		block2Position.z - ballPosition.z,
		0);
	//座標の差を求める
	XMVECTOR pos_sub3 = XMVectorSet(
		block3Position.x - ballPosition.x,
		block3Position.y - ballPosition.y,
		block3Position.z - ballPosition.z,
		0);
	//座標の差を求める
	XMVECTOR pos_sub4 = XMVectorSet(
		block4Position.x - ballPosition.x,
		block4Position.y - ballPosition.y,
		block4Position.z - ballPosition.z,
		0);
	//座標の差を求める
	XMVECTOR pos_sub5 = XMVectorSet(
		block5Position.x - ballPosition.x,
		block5Position.y - ballPosition.y,
		block5Position.z - ballPosition.z,
		0);

#pragma endregion

#pragma region 2つの距離を計算
	//2つの距離を計算
	pos_sub1 = XMVector3Length(pos_sub1);
	float dist1 = pos_sub1.m128_f32[0];
	//2つの距離を計算
	pos_sub2 = XMVector3Length(pos_sub2);
	float dist2 = pos_sub2.m128_f32[0];
	//2つの距離を計算
	pos_sub3 = XMVector3Length(pos_sub3);
	float dist3 = pos_sub3.m128_f32[0];
	//2つの距離を計算
	pos_sub4 = XMVector3Length(pos_sub4);
	float dist4 = pos_sub4.m128_f32[0];
	//2つの距離を計算
	pos_sub5 = XMVector3Length(pos_sub5);
	float dist5 = pos_sub5.m128_f32[0];
#pragma endregion

#pragma region 2つの半径以下ならHit判定
	if (dist1 <= ball->radius + block1->radius)
	{
		hit = true;
	}
	if (dist2 <= ball->radius + block2->radius)
	{
		hit = true;
	}
	if (dist3 <= ball->radius + block3->radius)
	{
		hit = true;
	}
	if (dist4 <= ball->radius + block4->radius)
	{
		hit = true;
	}
	if (dist5 <= ball->radius + block5->radius)
	{
		hit = true;
	}
#pragma endregion

#pragma region vector型 Block達の当たり判定

	for (Block* &x : blocks)
	{
		XMFLOAT3 blocksPosition = x->GetPosition();

		//座標の差を求める
		XMVECTOR pos_subs = XMVectorSet(
			blocksPosition.x - ballPosition.x,
			blocksPosition.y - ballPosition.y,
			blocksPosition.z - ballPosition.z,
			0);

		//2つの距離を計算
		pos_subs = XMVector3Length(pos_subs);
		float dists = pos_subs.m128_f32[0];

		if (dists <= ball->radius + block->radius)
		{
			hit = true;
		}
	}

#pragma endregion

#pragma endregion
#pragma endregion

#pragma region 新しい挙動まわりの処理(SZK)
	ballPosition.y -= g;//重力
	if (hit)
	{
		sec += 1;
		k -= 0.1;

		ballPosition.y += k;//反発
		if (sec > 45) //38
		{
			hit = false;
			k = 7.0;
			sec = 0;
		}

		//ballPosition.y += 20.0f;
		debugText.Print("Hit", 50, 50, 3);
	}
	else
	{
		k = 5.5;
	}

#pragma endregion

#pragma region score 処理

	if (sec == 1)
	{
		sco += 10;
#pragma region BGM再生
		//※変更必要（「.wav」のデータResourcesフォルダに入れたやつ読み込めず{Alarm01.wav}のみ再生可）
		audio->PlayWave("Resources/Alarm01.wav");
#pragma endregion

	}

#pragma region 
	if (input->PushKey(DIK_2)||input->PushKey(DIK_R))
	{
		sco = 0;
	}

#pragma endregion 
	debugText2.Print2(std::to_string(sco).c_str(), 140, 130, 1.0f);//スコア座標

#pragma endregion 

	// 座標の変更を反映
	object3d->SetPosition(position);
	ball->SetPosition(ballPosition);
	object3d->Update();
	ball->Update();

#pragma region blocksのUpdate処理

	for (Block* &x : blocks)
	{
		x->Update();
	}

#pragma endregion

#pragma region 最初の確定沸きBlock5っ
	block1->Update();
	block2->Update();
	block3->Update();
	block4->Update();
	block5->Update();
#pragma endregion
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

	//ボール描画前処理
	Ball::PreDraw(cmdList);

	//ブロック描画前処理
	Block::PreDraw(cmdList);

	//ボールの描画
	ball->Draw();

#pragma region blocksのDraw処理

	for (Block* &x : blocks)
	{
		x->Draw();
	}

#pragma endregion


#pragma region 最初の確定沸きBlock5っ
	//ブロック1の描画
	block1->Draw();
	//ブロック2の描画
	block2->Draw();
	//ブロック3の描画
	block3->Draw();
	//ブロック4の描画
	block4->Draw();
	//ブロック5の描画
	block5->Draw();
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