#pragma once
#include "BaseScene.h"
#include "GameScene.h"
#include "TitleScene.h"
#include <map>

enum SCENE
{
	TITLE,
	GAME,

	NONE
};

class SceneManager
{
public:

	void Init(DirectXCommon* dxcommon, Input* input, Audio* audio);

	std::map<SCENE, BaseScene*> scenes;
	// �V�[����ǉ�
	void AddScene(SCENE sceneEnum, BaseScene* scene);
	//�V�[���������ɂ���ĕς���֐�
	void ChangeScene(SCENE scene);
	//static void Initialize();
	//���݂̃V�[���X�V
	void Update();
	//�`��֐�
	void Draw();
private:
	BaseScene* m_pScene = nullptr;//���݂̃V�[���@

	DirectXCommon* m_DXCommon;
	Input* m_Input;
	Audio* m_Audio;
};