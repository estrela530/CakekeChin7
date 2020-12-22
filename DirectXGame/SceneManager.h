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
	// �V�[����ǉ�
	//void AddScene(SCENE sceneEnum, BaseScene* scene);
	//�V�[���������ɂ���ĕς���֐�
	virtual	void ChangeScene(SCENE scene);

	//���݂̃V�[���X�V
	virtual void Update();
	//�`��֐�
	virtual void Draw();
	void shutdown();
private:
	static BaseScene* m_pScene;//���݂̃V�[���@

	DirectXCommon* m_DXCommon;
	Audio* m_Audio;
	Input* m_Input;


};