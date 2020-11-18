#include "Block.h"
#include "BlockManager.h"

void BlockManager::Init(DirectXCommon * dxcommon, Input * input, Audio * audio)
{
	m_DXCommon = dxcommon;
	m_Audio = audio;
	m_Input = input;
}

//vector�ɂ��ꂽ�u���b�N�������Ƃ��p�֐�
void BlockManager::AddBlock()
{
	block = Block::Create();
	blocks.push_back(block);
}

//vector�ɂ��ꂽ�u���b�N�������Ƃ��p�֐�
void BlockManager::DeleteBlock()
{
	//pop_back�͖����̗v�f���폜
	//blocks.pop_back();

	//erase�͏��������悾���Ǎ���̏������́ivector���ɍ������Ă��钆�Łj��ԍŏ��̗v�f���폜
	blocks.erase(blocks.begin());

};

//�X�V����
void BlockManager::Update()
{

};

//�`��p�����ǃu���b�N�N���X�̂���������Ɏ����Ă��Ȃ��Ƃ����Ȃ�
void BlockManager::Draw()
{

};
