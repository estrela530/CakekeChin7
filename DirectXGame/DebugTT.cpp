#include "DebugTT.h"

DebugTT::DebugTT()
{
}
DebugTT::~DebugTT()
{
	for (int i = 0; i < _countof(spriteDates2); i++)
	{
		delete spriteDates2[i];
	}
}

void DebugTT::Init(UINT texnumber2)
{
	for (int i = 0; i < _countof(spriteDates2); i++)
	{
		spriteDates2[i] = Sprite::Create(texnumber2, { 0,0 });
	}
}

//�ꕶ���ǉ�
void DebugTT::Print2(const std::string & text2, float x2, float y2, float scale = 1.0f)
{
	for (int i = 0; i < text2.size(); i++)
	{
		// �ő啶��������
		if (spriteindex2 >= MaxCharCt) {
			break;
		}

		// 1�������o��(��ASCII�R�[�h�ł������藧���Ȃ�)
		const unsigned char& character = text2[i];

		int fontIndex = character-8;//
		if (character >= 0x7f) {
			fontIndex = 0;
		}

		int fontIndexY = fontIndex / fontLineCount2;
		int fontIndexX = fontIndex % fontLineCount2;

		// ���W�v�Z
		spriteDates2[spriteindex2]->SetPosition({ x2 + fontWidth2 * scale * i, y2 });
		spriteDates2[spriteindex2]->SetTextureRect({ (float)fontIndexX *
			fontWidth2, (float)fontIndexY * fontHeight2 },
			{ (float)fontWidth2, (float)fontHeight2 });
		spriteDates2[spriteindex2]->SetSize({ fontWidth2 * scale,
			fontHeight2 * scale });

		// �������P�i�߂�
		spriteindex2++;
	}
}

//�`��
void DebugTT::DrawAll2(ID3D12GraphicsCommandList* cmdList2)
{
	for (int i = 0; i < spriteindex2; i++)
	{
		spriteDates2[i]->Draw();
	}

	spriteindex2 = 0;
}