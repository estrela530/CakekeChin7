#pragma once
#include "BaseScene.h"
#include <map>

enum SCENE
{
	TITLE,
	GAME,
	RESULT,
};

class SceneManager
{
public:

	void Init(DirectXCommon* dxcommon, Input* input, Audio* audio);

	//std::map<SCENE, BaseScene*> scenes;
	//static BaseScene* m_pScene;
	// シーンを追加
	//void AddScene(SCENE sceneEnum, BaseScene* scene);
	//シーンを引数によって変える関数
	virtual	void ChangeScene(SCENE scene);

	//現在のシーン更新
	virtual void Update();
	//描画関数
	virtual void Draw();
	void shutdown();
private:
	static BaseScene* m_pScene;//現在のシーン　

	DirectXCommon* m_DXCommon;
	Audio* m_Audio;
	Input* m_Input;


};