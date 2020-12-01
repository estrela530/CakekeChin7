#pragma once
#include "Block.h"
#include <vector>

class BlockManager
{
public:

	void Init(DirectXCommon* dxcommon, Input* input, Audio* audio);

	//// �u���b�N��ǉ��i�����j
	//static void AddBlock(Block* block);
	////�i���̂Ƃ���ׂ������܂��ĂȂ��̂ŉ��L���u��O�iZ���j�����𒴂�����v�Ƃ��A
	////�u��������Ă���̌o�ߎ��ԁi�������Ԃ�݂���j�v�j�֐�
	//static void DeleteBlock(Block* block);
	////�iposition��speed�Ȃǂ́j�X�V
	//static void Update(int blockNumber);
	////�`��֐�
	//static void Draw(int blockNumber);

	// �u���b�N��ǉ��i�����j
	void AddBlock(Block* block);
	//�i���̂Ƃ���ׂ������܂��ĂȂ��̂ŉ��L���u��O�iZ���j�����𒴂�����v�Ƃ��A
	//�u��������Ă���̌o�ߎ��ԁi�������Ԃ�݂���j�v�j�֐�
	void DeleteBlock(Block* block);
	//�iposition��speed�Ȃǂ́j�X�V
	void Update(int blockNumber);
	//�`��֐�
	void Draw(int blockNumber);

private:

	DirectXCommon* m_DXCommon;
	Input* m_Input;
	Audio* m_Audio;
	//Block* blocks[5];
	//Block* block = nullptr;
	//std::vector<Block*> blocks;
	Block* block = nullptr;
	//std::vector<Block*> blocks;

public:

	//Block* block = nullptr;
	std::vector<Block*> blocks;
	int blockNumber;
};