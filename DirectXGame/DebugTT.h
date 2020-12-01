#pragma once

#include "Sprite.h"
#include <Windows.h>
#include <string>


class DebugTT
{
public:
	static const int MaxCharCt = 256;//�ő啶����
	static const int fontWidth2 = 16;// �t�H���g�摜��1�������̉���
	static const int fontHeight2 = 32;// �t�H���g�摜��1�������̏c��
	static const int fontLineCount2 = 10;// �t�H���g�摜��1�s���̕�����


	DebugTT();
	~DebugTT();

	void Init(UINT texnumber2);//Initialize
	void Print2(const std::string & text2, float x2,
		float y2, float size2);//debugtext��int�ԍ쐬
	void DrawAll2(ID3D12GraphicsCommandList * cmdList2);

private:
	//�X�v���C�g�f�[�^�̔z��
	Sprite* spriteDates2[MaxCharCt] = {};
	//�X�v���C�g�f�[�^�̔z��̓Y�����ԍ�
	int spriteindex2 = 0;
};