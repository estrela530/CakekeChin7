#include "SceneManager.h"
#include "TitleScene.h"

#include <cassert>//�w�b�_�Ŏ����^�ł��邱�Ƃ�\��


TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	delete spriteBG;
	delete wip;
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

	if (!Sprite::LoadTexture(1, L"Resources/tex1.png"))
	{
		assert(0);
		return;
	}

	///	// 3D�I�u�W�F�N�g����
	//object3d = Object3d::Create();
	//object3d->Update();
	//�w�i�X�v���C�g����
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	//���C�v������
	wip = Sprite::Create(1, { 0.0f,0.0 });
	wip->Sprite::SetSize({ 128.0f,72.0f });//�����R
	//spriteBG->SetPosition({ 100,100 });
	alpha = 0;
	//alpha2 = 1;
	timer = 0.0f;

}


void TitleScene::Update()
{
	alpha += 0.0095f;
	timer += 1;		
	spriteBG->SetColor({ 1,1,1,alpha });//�e�N�X�`���̐F�ƃ��l��

	if (wips == false)
	{
		if (alpha > 1.0f)
		{
			//debugText.Print(std::string&,)
			wips = true;
		}
	}
	else if (wips == true)
	{

		//	alpha2 -= 0.0095f;
			//wip->SetColor({ 1,1,1,alpha2 });
		if (timer <=1000)
		{
			wips = false;
			//delete wip;
		}
	}




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
	wip->Draw();

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

#pragma region ���C�v




#pragma endregion 
}
