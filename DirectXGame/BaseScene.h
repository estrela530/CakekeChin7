#pragma once
#include"DirectXCommon.h"
#include"input.h"
#include "Audio.h"
class BaseScene
{
public:

	//virtual void Initialize() = 0;
	//�X�V����
	virtual void Update() = 0;
	//�`�揈��
	virtual void Draw() = 0;
	virtual void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio) = 0;
private:

};