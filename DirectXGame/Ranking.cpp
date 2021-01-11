#include "Ranking.h"
#include <algorithm>
#include <vector>

using namespace std;

void Ranking::Update(int x)
{
	scoreRankingVec.push_back(x);
}

void Ranking::Sort()
{
	sort(scoreRankingVec.begin(), scoreRankingVec.end(), greater<int>());
}

