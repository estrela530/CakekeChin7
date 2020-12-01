#pragma once
#include "Block.h"
#include <vector>

class BlockManager
{
public:

	void Init(DirectXCommon* dxcommon, Input* input, Audio* audio);

	//// ブロックを追加（生成）
	//static void AddBlock(Block* block);
	////（今のところ細かく決まってないので仮記入「手前（Z軸）が一定を超えたら」とか、
	////「生成されてからの経過時間（生存時間を設ける）」）関数
	//static void DeleteBlock(Block* block);
	////（positionやspeedなどの）更新
	//static void Update(int blockNumber);
	////描画関数
	//static void Draw(int blockNumber);

	// ブロックを追加（生成）
	void AddBlock(Block* block);
	//（今のところ細かく決まってないので仮記入「手前（Z軸）が一定を超えたら」とか、
	//「生成されてからの経過時間（生存時間を設ける）」）関数
	void DeleteBlock(Block* block);
	//（positionやspeedなどの）更新
	void Update(int blockNumber);
	//描画関数
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