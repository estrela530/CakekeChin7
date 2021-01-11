#pragma once
#include <vector>

class Ranking
{
public:

	//更新処理
	void Update(int x);
	//降順ソート
	void Sort();
	//描画関数
	void Draw(int blockNumber);

public:
	//ランキング機能関連
	std::vector<int> scoreRankingVec;

};