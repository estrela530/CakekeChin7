#include "SceneManager.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "ResultScene.h"
//////////////////////////////////////////////////////////////////////////////////ì‹Æ•”‰®
BaseScene*SceneManager::m_pScene = NULL;
//SceneManager* s_mane(SceneManager smane);
void SceneManager::Init(DirectXCommon * dxcommon, Input * input, Audio * audio)
{
	m_DXCommon = dxcommon;
	m_Audio = audio;
	m_Input = input;
}

void SceneManager::ChangeScene(SCENE scene)
{
	if (m_pScene != nullptr) {
		delete m_pScene;
	}
	//	BaseScene* SceneManager::m_pScene = scene;
	switch (scene)
	{
	case SCENE::TITLE:
		m_pScene = new TitleScene(this);
		m_pScene->Initialize(m_DXCommon, m_Input, m_Audio);
		break;
	case SCENE::GAME:
		m_pScene = new GameScene(this);
		m_pScene->Initialize(m_DXCommon, m_Input, m_Audio);
		//->Initialize(m_DXCommon, m_Input, m_Audio);
		break;
	case SCENE::RESULT:
		m_pScene = new ResultScene(this);
		m_pScene->Initialize(m_DXCommon, m_Input, m_Audio);
		break;
	default:
		break;
	}
};

void SceneManager::Update()
{
	m_pScene->Update();
};
void SceneManager::Draw()
{
	m_pScene->Draw();
};
void SceneManager::shutdown()
{
	delete m_pScene;
}