#pragma once
#include <vector>

class Ranking
{
public:

	//�X�V����
	void Update(int x);
	//�~���\�[�g
	void Sort();
	//�`��֐�
	void Draw(int blockNumber);

public:
	//�����L���O�@�\�֘A
	std::vector<int> scoreRankingVec;

};