#pragma once
#include "Block.h"
#include <vector>

class BlockManager
{
public:

	void Init(DirectXCommon* dxcommon, Input* input, Audio* audio);

	// ブロックを追加（生成）
	void AddBlock();
	//（今のところ細かく決まってないので仮記入「手前（Z軸）が一定を超えたら」、
	//「生成されてからの経過時間（生存時間を設ける）」）関数
	void DeleteBlock();
	//（positionやspeedなどの）更新
	void Update();
	//描画関数
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