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
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private://�ÓI�����o�ϐ�
	static const int debugTextTexNumber = 0;
public:
	TitleScene();
	//�f�X�g���N�^
	~TitleScene();
	//������
	virtual void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio) override;



	//���t���[���Ǘ�
	virtual void Update() override;

	//�`��
	virtual void Draw() override;

private://�����o�ϐ�

	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;

	Sprite* spriteBG = nullptr;
	Object3d* object3d = nullptr;
};