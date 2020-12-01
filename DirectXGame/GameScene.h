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
<<<<<<< HEAD


=======
	static const int dTTN2 = 0;
>>>>>>> origin/pooooooooooooooooo
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

	Block* block = nullptr;
#pragma region BlockManager作成に伴いコメントアウト
	//Block* block1 = nullptr;
	//Block* block2 = nullptr;
	//Block* block3 = nullptr;
	//Block* block4 = nullptr;
	//Block* block5 = nullptr;
	//Block* block6 = nullptr;
	//Block* block7 = nullptr;
	//Block* block8 = nullptr;
	//Block* block9 = nullptr;
#pragma endregion
	//Object3d2* object3d2 = nullptr;

	int blockGeneratorSeconds;
	int notBallJumpSeconds = 0;
	//Block::List<block> blockList = new List<block>();
	float alpha;
<<<<<<< HEAD
	float blockCreateTime = 0;
	int blockCreateCount = 0;
	std::vector<Block*> blocks;
	float blockXPosition = 0;
=======
	int sco = 0;
	int ss = 0;

	float k = 4.1f;
	float t = 0.0f;
	float m = 8.0f;//質量
	float v = 1.0f;
	float g = 1.5f;//重力加速度
	float ve;

	float vy = 0.5f;//物体の速度
	float fy;//Y軸に働く力
	float ay;//Y軸の加速度
	int time = 0.0f;
	bool alal = true;//背景点滅余
	float aa = 1;
	float bb = 1;
	float cc = 0;
>>>>>>> origin/pooooooooooooooooo
};

