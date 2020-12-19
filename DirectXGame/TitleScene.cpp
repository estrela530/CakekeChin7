#include "SceneManager.h"
#include "TitleScene.h"
#include "WinApp.h"

#include <cassert>//�w�b�_�Ŏ����^�ł��邱�Ƃ�\��


TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	delete spriteBG;
	delete sima;
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
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png"))
	{
		assert(0);
		return;
	}
	debugText.Initialize(debugTextTexNumber);

	// �e�N�X�`���ǂݍ���	��1�ԖڂɓǍ�
	if (!Sprite::LoadTexture(1, L"Resources/title.png")) {
		assert(0);
		return;
	}
	//�摜					����ԖڂɓǍ�
	if (!Sprite::LoadTexture(2, L"Resources/tex1.png"))
	{
		assert(0);
		return;
	}
	//�摜�Q�@				���摜�I�ɂ�2�Ԗڂɕ\�L����Ă���B
	if (!Sprite::LoadTexture(3, L"Resources/170.png"))
	{
		assert(0);
		return;
	}

	// 3D�I�u�W�F�N�g����
	//object3d = Object3d::Create();
	//object3d->Update();
	//�w�i�X�v���C�g����
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });

#pragma region wip

	//x,y
	wip_x = 1280.0f;
	wip_y = 720.0f;
	timer = 0;
	//x2�Ay2
	w2x = 0.0f;
	w2y = 720.0f;

	wip = Sprite::Create(2, { 0	,0 });
	//���C�v������
	//wip->Sprite::SetPosition({ 0,0 });
	wip->Sprite::SetSize({ wip_x ,wip_y });//
	//wip2 = Sprite::Create(2, { w2x,w2y });

	sima = Sprite::Create(3, { 0.0f,0.0f });
	sima->Sprite::SetSize({ 1280.0f,720.0f });
	//spriteBG->SetPosition({ 100,100 });
	alpha = 0;
	alpha2 = 0;
	alpha3 = 0;

	//alpha2 = 1;
#pragma endregion
}


void TitleScene::Update()
{
#pragma region BGM�Đ�
	//���ύX�K�v�i�u.wav�v�̃f�[�^Resources�t�H���_�ɓ��ꂽ��ǂݍ��߂�{Alarm01.wav}�̂ݍĐ��j
	//audio->PlayWaveBGM("Resources/Alarm01.wav");
#pragma endregion

	alpha += 0.01f;
	timer += 1;
	spriteBG->SetColor({ 1,1,1,alpha });//�e�N�X�`���̐F�ƃ��l��
	sima->SetColor({ 1,1,1,alpha2 });
	wip->SetColor({ 0,0,0,alpha3 });
	//	wip2->SetColor({ 0,0,0,1 });


		//if (wips == false)
		//{
		//wip->SetColor({ 0,1,1,alpha });

	if (alpha > 0.9f)
	{
		alpha2 += 0.008f;
	}

	if (alpha > 1.2f)
	{
		alpha3 += 0.03f;

		if (wips == false)
		{
			//wip->SetPosition({ wip_x,wip_y });
			wip_x += 7;
			wip_y += 4;
			//sima->Sprite::SetPosition({ 0,0 });
			wip->Sprite::SetSize({ wip_x,wip_y });
			if (wip_x > 1280)
			{
				wips = true;
			}
		}
		else if (wips == true)
		{
			if (wip_x > 1280)
			{
				//���C�v�摜���W��0�ɌŒ�
				/*wip_x += 0;
				wip_y += 0;*/
				//wip->Sprite::SetSize({ wip_x,wip_y });

				wips == true;
			}
			if (input->PushKey(DIK_1) || input->PushKey(DIK_2))
			{
				wips = false;
			}
			if (alpha3 > 1.0f)
			{
				
			}
		}
	}

	//}
	//else if (wips == true)
	//{
	//	//alpha2 -= 0.0095f;
	//	//wip->SetColor({ 1,1,1,alpha2 });
	//	wips = false;
	//	//delete wip;
	//}
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
	sima->Draw();
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
