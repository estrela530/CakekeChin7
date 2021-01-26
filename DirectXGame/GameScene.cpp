#include "GameScene.h"
#include "BaseScene.h"

//#include "BlockManager.h"
//#include "Object3d.h"
#include <cassert>
#include <iostream>
#include <ctime>

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

GameScene::GameScene(SceneManager* smane) :smane(smane)
{
}

GameScene::~GameScene()
{
	delete spriteBG;
	delete object3d;
	delete score;
	delete ball;
	//フェード・画像
	delete fade_1;
	delete fade_saku;
	//画像
	delete score10;
	//delete score100;
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
	audio->Initialize();

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
	if (!Sprite::LoadTexture(1, L"Resources/haikei.png")) {
		assert(0);
		return;
	}
	//スコア
	if (!Sprite::LoadTexture(2, L"Resources/score.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(3, L"Resources/black.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(4, L"Resources/170.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(5, L"Resources/10.png"))
	{
		assert(0);
		return;
	}
	//if (!Sprite::LoadTexture(6, L"Resources/100.png"))
	//{
	//	assert(0);
	//	return;
	//}
	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	// 3Dオブジェクト生成
	object3d = Object3d::Create();
	//zahyou 
	score = Sprite::Create(2, { 1,126 });//スコア画像サイズ
	score->Sprite::SetSize({ 135.0f,38.0f });//画像サイズ
	object3d->Update();

	// モデル読み込み
	modelSphere = Model::CreateFromOBJ("sphere", true);

	//ボール生成
	ball = Ball::Create(modelSphere);


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

#pragma region BGM再生
	//※変更必要（「.wav」のデータResourcesフォルダに入れたやつ読み込めず{Alarm01.wav}のみ再生可）

#pragma endregion

#pragma region パーティクル関連
	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);

	// 3Dオブジェクトにカメラをセット
	//Object3d::SetCamera(camera);

	// パーティクルマネージャ生成
	particleManager = ParticleManager::GetInstance();
	particleManager->SetCamera(camera);

	// カメラ注視点をセット
	camera->SetTarget({ 0, 1, 0 });
	camera->SetDistance(3.0f);
#pragma endregion

#pragma region 変数
	//フェード
	alpha = 0;
	//fade 生成
	fade_1 = Sprite::Create(3, { 0.0f,0.0f });
	gwip_x = 1280.0f;
	gwip_y = 720.0f;
	//fade_1->Sprite::SetSize({ 0,0 });
	//フェード
	alpha = 0;
	timer = 0;
	alpha_f = 1;
	alpha_f2 = 1;
	fade_saku = Sprite::Create(4, { 0.0f,0.0f });
	fade_saku->Sprite::SetSize({ gwip_x,gwip_y });
	//score10 = Sprite::Create(5, { 130.0f,130.0f });
	sco_x = 130.0f;
	sco_y = 130.0f;
	//score___y = 0;
	score10 = Sprite::Create(5, { sco_x,sco_y });
	sal = 0;
	sososo = false;
	sal2 = false;
	notBallJumpSeconds = 0;
	distance = 18;
#pragma endregion
	audio->PlayWaveBGM("Resources/aladdin.wav");
	alal = false;
	alalal = false;
}

void GameScene::Update()
{

#pragma region BGM再生
	//Spaceを押したらストップする実験用
	if (input->PushKey(DIK_SPACE))
	{
		audio->StopWave();
	}
#pragma endregion

#pragma region パーティクルの更新
	// パーティクル生成
	camera->Update();
	particleManager->Update();
#pragma endregion

#pragma region シュレフェード試作
	////フェード
	//alpha += 0.01f;
	//spriteBG->SetColor({ 1,1,1,alpha });//背景色

	notBallJumpSeconds += 1;

	//フェード
	alpha += 0.01f;//背景フェード（試作
	spriteBG->Sprite::SetColor({ 0,0,0,alpha });
	timer += 1;//ゲームシーンまでのタイム
	alpha_f -= 0.008f;//黒い画面
	//alpha_f2 -= 0.05f;
	fade_1->Sprite::SetColor({ 0,0,0,alpha_f });
	fade_1->Sprite::SetSize({ gwip_x,gwip_y });

	alpha_f2 -= 0.008f;//柵
	fade_saku->Sprite::SetColor({ 0,0,0,alpha_f2 });
	score10->Sprite::SetColor({ 1,1,1, sal });
	//if (alpha_f < 0.3f)
	//{
	//	timer += 1;
	//}
	if (timer > 70)//ゲームシーンの中身開始時間
	{
		spriteBG->SetColor({ 1,1,1,alpha });//背景色

		////if (alal == true)
		////{
		////	alpha -= 0.01f;
		////	bb -= 0.00001f;
		////	if (bb > 0.01f)
		////	{
		////		bb += 0.0001f;
		////	}
		////	/*cc -= 0.001f;
		////	if (cc < 1)
		////	{
		////		aa -= 0.005f;
		////		bb -= 0.005f;
		////	}
		////	if (aa == 0.3 || bb == 0.3)
		////	{
		////		aa += 0.005f;
		////		cc += 0.005f;
		////	}*/
		////	/*	if (aa > 0)
		////		{
		////			aa += 0.005f;
		////		}*/
		////		//if (alpha < 0.35)
		////		//{
		////		//	alal = false;
		////		//	aa -= 0.0004f;
		////		//	//bb -= 0.004f;
		////		//	cc += 0.0001f;
		////		//}
		////}
		///*	else if (alal == false)
		//	{
		//		alpha += 0.01f;
		//		spriteBG->SetColor({ aa,bb,cc,alpha });
		//		cc += 0.0005f;

		//		if (alpha < 1)
		//		{
		//			alal = true;
		//		}
		//		else if (aa < 0.3)
		//		{
		//			aa += 0.004f;
		//			bb += 0.004f;
		//		}
		//	}*/
		//	//if (aa < 1 )
		//	//{
		//	////	aa -= 0.04f;
		//	//	bb += 0.04f;
		//	//	cc += 0.001f;
		//	//	if (aa > 0.8)
		//	//	{
		//	//		aa += 0.04f;
		//	//	}
		//	//}
		spriteBG->SetColor({ aa,bb,cc,alpha });

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
		if (dist1 <= ball->radius + distance)
		{
			hit = true;
		}
		if (dist2 <= ball->radius + distance)
		{
			hit = true;
		}
		if (dist3 <= ball->radius + distance)
		{
			hit = true;
		}
		if (dist4 <= ball->radius + distance)
		{
			hit = true;
		}
		if (dist5 <= ball->radius + distance)
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

			//岩崎変更
			if (dists <= ball->radius + distance)
			{
				hit = true;
			}
		}

#pragma endregion

#pragma endregion
#pragma endregion

#pragma region パーティクルの描画と挙動
		//X,Y,Z{-5.0f,+5.0f}でランダムに分布
		const float rnd_pos = 4.0f;

		//X,Y,Z{-0.05f,+0.05f}でランダムに分布
		const float rnd_vel = 0.5f;
		XMFLOAT3 vel{};//速度
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y += (float)rand() / RAND_MAX * rnd_vel + rnd_vel / 2.0f;

		//重力に見立ててYのみ[-0.001f,0]でランダム分布
		XMFLOAT3 acc{};//加速度
		const float rnd_acc = 0.001f;
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;
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

			//パーティクルの描画
			particleManager->Add(5, XMFLOAT3{ ballPosition.x ,0.8f,1.8f }, vel, acc, 0.5f, 1.5f);//描画

			//ballPosition.y += 20.0f;
			//debugText.Print("Hit", 50, 50, 3);
		}
		else
		{
			k = 5.5;
		}

#pragma endregion

#pragma region score 処理(+score)

		if (sec == 1)
		{
			//	sco += 10;
			afk++;
			sososo = true;
			sal2 = true;

			audio->PlayWaveSE("Resources/button.wav");
		}
		if (sososo == true)
		{
			sco++;
			//sco =+ 1000;
			if (sco > 10 * afk)
			{
				sco -= 1;
				sososo = false;
			}
		}
		if (sososo == false)
		{
			if (sco < 10 * afk)
			{
				sososo = true;
			}
		}
		if (sal2 == true)
		{
			sal += 0.07f;//+scoreの明るくなるまでの時間
			//score___y -= 0.1f;
			if (sal > 0.9f)
			{
				sco_y -= 1.0f;
				sal += 0.1f;
				if (sco_y == 126.0f)
				{
					sco_y = 130.0f;
				}
				if (sco > 999)
				{
					sco_x = 145;
				}
				score10->SetPosition({ sco_x,sco_y });
				sal2 = false;
			}
		}
		if (sal2 == false)
		{
			sal -= 0.05f;
			if (sal < 0.001f)
			{
				sal = 0;
			}
			//sal = true;
		}
		if (hit)
		{
#pragma region BGM再生
			//※変更必要（「.wav」のデータResourcesフォルダに入れたやつ読み込めず{Alarm01.wav}のみ再生可）
			//audio->PlayWaveSE("Resources/file_20131208_Cursor3.wav");
			//audio->StopWave();
#pragma endregion
		}
		aa = sco * 0.001f;
		bb = sco * 0.001f;
		cc = sco * 0.001f;
#pragma region 
		if (input->PushKey(DIK_2) || input->PushKey(DIK_R))
		{
			sco = 0;
			afk = 0;
			//audio->StopWave();
		}
#pragma endregion 
		debugText2.Print2(std::to_string(sco).c_str(), 140, 130, 1.0f);//スコア座標
		//背景変色箇所スコア⇒変換
		//if (sco < 50)
		//{
		//	alal = true;
		//	//alalal = false;
		//}
		if (alal == false)
		{
			//	//aa = R //  bb  =G  //cc =B//abc->rgb
			//	aa -= 0.0001f;
			//	bb -= 0.0001f;
			//	cc += 0.0001f;
			//	
			//	if (sco == 100)
			//	{
			//		cc -= 0.001f;
			//	}
			//}
			//if (alal == false)
			//{
			//	cc -= 0.001f;
			//}
			//if (sco == 150)
			//{
			//	alal = false;
			//	alalal = true;
			//	//	cc = 0.5f;
			//}
			//if (alalal = true)
			//{
			//	aa += 0.002f;
			//	bb += 0.0001f;
			//	cc += 0.0001f;

			///////////////////////////////////////
			//aa = sco /-100;
			//bb = sco / -100;

		}
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
		//※更新した後に下記ないとシーン変更出来ず
		//if (sco == 150)
		//{
		//	smane->ChangeScene(SCENE::RESULT);
		//}
//audio->StopWave();
		if (ballPosition.y <= -70)
		{
			smane->ChangeScene(SCENE::RESULT);
		}

	}

}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	//ID3D12GraphicsCommandList* cmdList2 = dxCommon->GetCommandList();

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

#pragma region パーティクルの描画
	// パーティクルの描画
	particleManager->Draw(cmdList);
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

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
	//ボール描画後処理
	Ball::PostDraw();

	//ブロック描画後処理
	Block::PostDraw();

#pragma endregion

#pragma region スコア数字

	Sprite::PreDraw(cmdList);
	debugText2.DrawAll2(cmdList);
	score10->Draw();
	Sprite::PostDraw();

#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	fade_saku->Draw();
	fade_1->Draw();
	// デバッグテキストの描画
	debugText.DrawAll(cmdList);
	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}