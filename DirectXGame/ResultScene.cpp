#include "ResultScene.h"
#include <cassert>//�w�b�_�Ŏ����^�ł��邱�Ƃ�\��


ResultScene::ResultScene(SceneManager* smane) :smane(smane)
{
}

ResultScene::~ResultScene()
{
	delete spriteBG;

}


void ResultScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	//nullptr�`�F�b�N
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/RESULT.png"))
	{
		assert(0);
		return;
	}
	debugText.Initialize(debugTextTexNumber);

	// �e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(1, L"Resources/Result555.png")) {
		assert(0);
		return;
	}

	///	// 3D�I�u�W�F�N�g����
	//object3d = Object3d::Create();
	//object3d->Update();
	//�w�i�X�v���C�g����
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });

	fade = 0;
}


void ResultScene::Update()
{
	fade += 0.004f;
	spriteBG->SetColor({ 1,1,1,fade });

	//	//�������ύX
	//	/*debugText.Print(gameScene->sco)*/
		////debugText2.Print2(std::to_string(gameScene->sco).c_str(), 140, 130, 1.0f);//�X�R�A���W
		////debugText.Print(ranking->scoreRankingVec.begin(), 160, 150, 1.0f);//�X�R�A���W
		////debugText.Print("Hit", 160, 150, 1.0f);//�X�R�A���W

	if (input->PushKey(DIK_SPACE))
	{
		smane->ChangeScene(SCENE::TITLE);
	}

}

void ResultScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region �`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	// �w�i�X�v���C�g�`��
	spriteBG->Draw();


	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
	// �[�x�o�b�t�@�N���A
	dxCommon->ClearDepthBuffer();

	Sprite::PreDraw(cmdList);

	//�f�o�b�O�e�L�X�g�̕`��
	debugText.DrawAll(cmdList);
	//�X�v���C�g�`���̏���
	Sprite::PostDraw();
#pragma endregion 

}
