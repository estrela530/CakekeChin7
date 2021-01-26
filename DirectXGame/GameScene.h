#pragma once
#include "SceneManager.h"
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

#include "ParticleManager.h"
#include "DebugCamera.h"
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
#pragma region 
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene(SceneManager* smane);

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
#pragma endregion

private: // メンバ変数
	SceneManager* smane;
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;
	DebugTT debugText2;

	//追加
	DebugCamera* camera = nullptr;
	ParticleManager* particleManager = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	Sprite* spriteBG = nullptr;
	Object3d* object3d = nullptr;
	Ball* ball = nullptr;
	Sprite* score = nullptr;
	Block* block = nullptr;
	Model* modelSphere = nullptr;

	//フェード画像
private:
	Sprite* fade_1 = nullptr;
	Sprite* fade_saku = nullptr;
	//スコア+時の描画画像
	Sprite* score10 = nullptr;
	//Sprite* score100 = nullptr;
public:
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
	//int time = 0.0f;

	float k = 1.0f;
	float g = 2.5f;//重力加速度
	float ve;

	//フェード
	bool alal = false;//背景点滅余
	bool alalal = false;
	float aa = 1;
	float bb = 1;
	float cc = 1;

	int sec = 0;
	bool hit = false;
	//シュレ
	int timer = 0;
	//開幕フェード処理
	//bool fade_i= false;
	float gwip_x;
	float gwip_y;
	float alpha_f;
	float alpha_f2;
	bool sososo = false;
	//試作調整用＠シュ
	int afk = 0;
	//score＋用
	float sal;
	bool sal2 = false;
	float  sco_x;
	float sco_y;
	//float score___y;

	//2点間の距離の差（Block）
	int distance;

	//ランキング機能関連
	std::vector<int> scoreRankingVec;
	//Ranking* ranking;
	//bool check_bgm=false;

};

