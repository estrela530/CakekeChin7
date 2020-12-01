#include "Block.h"
#include "BlockManager.h"

void BlockManager::Init(DirectXCommon * dxcommon, Input * input, Audio * audio)
{
	m_DXCommon = dxcommon;
	m_Audio = audio;
	m_Input = input;
}

//vectorにいれたブロックをいれるとき用関数
void BlockManager::AddBlock(Block* block)
{
	//block = Block::Create();
	blocks.push_back(block);
}

//vectorにいれたブロックを消すとき用関数
void BlockManager::DeleteBlock(Block* block)
{
	//pop_backは末尾の要素を削除
	//blocks.pop_back();

	//eraseは書き方次第だけど今回の書き方は（vector内に今入っている中で）一番最初の要素を削除
	blocks.erase(blocks.begin());

};

//更新処理
void BlockManager::Update(int blockNumber)
{
	blocks.at(blockNumber)->Update();

};

//描画用だけどブロッククラスのやつをこっちに持ってこないといけない
void BlockManager::Draw(int blockNumber)
{
	blocks.at(blockNumber)->Draw();
};
