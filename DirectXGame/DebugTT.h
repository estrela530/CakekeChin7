#pragma once

#include "Sprite.h"
#include <Windows.h>
#include <string>


class DebugTT
{
public:
	static const int MaxCharCt = 256;//最大文字数
	static const int fontWidth2 = 16;// フォント画像内1文字分の横幅
	static const int fontHeight2 = 32;// フォント画像内1文字分の縦幅
	static const int fontLineCount2 = 10;// フォント画像内1行分の文字数


	DebugTT();
	~DebugTT();

	void Init(UINT texnumber2);//Initialize
	void Print2(const std::string & text2, float x2,
		float y2, float size2);//debugtextのint番作成
	void DrawAll2(ID3D12GraphicsCommandList * cmdList2);

private:
	//スプライトデータの配列
	Sprite* spriteDates2[MaxCharCt] = {};
	//スプライトデータの配列の添え字番号
	int spriteindex2 = 0;
};