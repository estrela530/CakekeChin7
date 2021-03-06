#pragma once

#include "SafeDelete.h"
#include "SceneManager.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "DebugText.h"
#include "Audio.h"
#include "BaseScene.h"

class TitleScene :public BaseScene
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private://静的メンバ変数
	static const int debugTextTexNumber = 0;
public:
	TitleScene(SceneManager* smane);
	//デストラクタ
	~TitleScene();
	//初期化
	virtual void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio) override;
	//毎フレーム管理
	virtual void Update() override;
	//描画
	virtual void Draw() override;

private://メンバ変数
	SceneManager* smane;
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;

	Sprite* spriteBG = nullptr;
	Object3d* object3d = nullptr;
	Sprite* wip = nullptr;
	Sprite* wip2 = nullptr;
	Sprite* sima = nullptr;
	Sprite* spel = nullptr;

	float alpha;
	int timer;
	bool wips = false;
	float wip_x;
	float wip_y;
	float alpha2;
	float alpha3;
	float w2x;
	float w2y;

	bool goGameScene;
	//タイトルの試作＠シュレ
	int tspel;
	float tspel_alpha;
	bool spelcheck;
	/*bool aks;*/
};