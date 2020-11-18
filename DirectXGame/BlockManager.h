#pragma once
#include "Block.h"
#include <vector>

class BlockManager
{
public:

	void Init(DirectXCommon* dxcommon, Input* input, Audio* audio);

	// �u���b�N��ǉ��i�����j
	void AddBlock();
	//�i���̂Ƃ���ׂ������܂��ĂȂ��̂ŉ��L���u��O�iZ���j�����𒴂�����v�A
	//�u��������Ă���̌o�ߎ��ԁi�������Ԃ�݂���j�v�j�֐�
	void DeleteBlock();
	//�iposition��speed�Ȃǂ́j�X�V
	void Update();
	//�`��֐�
	void Draw();
private:

	DirectXCommon* m_DXCommon;
	Input* m_Input;
	Audio* m_Audio;
	//Block* blocks[5];
	Block* block = nullptr;
	std::vector<Block*> blocks;

	//push back
};