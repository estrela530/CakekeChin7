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
//Å‰‚ÌƒV[ƒ“‚Í‹ó
//void SceneManager::AddScene(SCENE sceneEnum, BaseScene * scene)
//{
//	scene = scenes[sceneEnum];
//}

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
		//TitleScene(scene);
	//m_pScene->Initialize(m_DXCommon, m_Input, m_Audio);
		break;
	case SCENE::GAME:
		m_pScene = new GameScene(this);
		m_pScene->Initialize(m_DXCommon, m_Input, m_Audio);
		//m_pScene;
		//GameScene::Initialize(dxCommon,input,audio);
		//m_pScene->Initialize( m_DXCommon,);
		//m_pScene->Initialize(m_DXCommon, m_Input, m_Audio);
		//m_pScene->Draw();
		//->Initialize(m_DXCommon, m_Input, m_Audio);
		break;
	case SCENE::RESULT:
		m_pScene = new ResultScene(this);
		m_pScene->Initialize(m_DXCommon, m_Input, m_Audio);
		//m_pScene->Initialize(m_DXCommon, m_Input, m_Audio);
		//	m_pScene->Initialize();
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