#pragma once

#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"

#include "DebugText.h"
#include "DebugTT.h"
#include "Audio.h"
#include "Ball.h"
#include "Block.h"
#include "BaseScene.h"
//#include "BlockManager.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene :public BaseScene
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // 静的メンバ変数
	static const int debugTextTexNumber = 0;
	static const int dTTN2 = 0;
public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;
	DebugTT debugText2;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	Sprite* spriteBG = nullptr;
	Object3d* object3d = nullptr;
	Ball* ball = nullptr;
	Sprite* score = nullptr;

	Block* block = nullptr;

#pragma region 最初の確定沸きBlock4っ
	Block* block1 = nullptr;
	Block* block2 = nullptr;
	Block* block3 = nullptr;
	Block* block4 = nullptr;
	Block* block5 = nullptr;
#pragma endregion

	int blockGeneratorSeconds;
	int notBallJumpSeconds = 0;
	float alpha;
	float blockCreateTime = 0;
	int blockCreateCount = 0;
	std::vector<Block*> blocks;
	float blockXPosition = 0;

	int sco = 0;//フェード
	int ss = 0;
	int time = 0.0f;

	float k = 1.0f;
	float g = 2.5f;//重力加速度
	float ve;

	//フェード
	bool alal = true;//背景点滅余
	float aa = 1;
	float bb = 1;
	float cc = 0;

	int sec = 0;
	bool hit = false;

};

