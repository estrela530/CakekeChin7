#include "SceneManager.h"
#include "TitleScene.h"

#include <cassert>//�w�b�_�Ŏ����^�ł��邱�Ƃ�\��


TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	delete spriteBG;
}


void TitleScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	//nullptr�`�F�b�N
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/title.png"))
	{
		assert(0);
		return;
	}
	debugText.Initialize(debugTextTexNumber);

	// �e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(1, L"Resources/title.png")) {
		assert(0);
		return;
	}

	///	// 3D�I�u�W�F�N�g����
	//object3d = Object3d::Create();
	//object3d->Update();
	//�w�i�X�v���C�g����
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });

	//spriteBG->SetPosition({ 100,100 });
	alpha = 0;

}


void TitleScene::Update()
{
	alpha += 0.0095f;
	spriteBG->SetColor({ 1,1,1,alpha });//�e�N�X�`���̐F�ƃ��l��
}

void TitleScene::Draw()
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
