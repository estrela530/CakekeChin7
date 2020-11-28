#pragma once

#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"

#include "DebugText.h"
#include "Audio.h"
#include "Ball.h"
#include "Block.h"
#include "BaseScene.h"

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

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	Sprite* spriteBG = nullptr;
	Object3d* object3d = nullptr;
	Ball* ball = nullptr;
	Block* block = nullptr;
	Block* block1 = nullptr;
	Block* block2 = nullptr;
	Block* block3 = nullptr;
	Block* block4 = nullptr;
	Block* block5 = nullptr;
	Block* block6 = nullptr;
	Block* block7 = nullptr;
	Block* block8 = nullptr;
	Block* block9 = nullptr;
	//Object3d2* object3d2 = nullptr;

	int blockGeneratorSeconds;
	int notBallJumpSeconds = 0;
	//Block::List<block> blockList = new List<block>();
	float alpha;
};

