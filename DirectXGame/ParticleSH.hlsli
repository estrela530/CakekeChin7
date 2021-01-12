cbuffer cbuff0 : register(b0)
{
	//float4 color; // �F(RGBA)
	matrix mat; // �R�c�ϊ��s��
	matrix matBillboard; // �R�c�ϊ��s��

};

// ���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�ւ̂����Ɏg�p����\����
struct VSOutput
{
	//float4 svpos : SV_POSITION; // �V�X�e���p���_���W
	//float3 normal :NORMAL; // �@���x�N�g��
	//float2 uv  :TEXCOORD; // uv�l

	float4 pos:POSITION;//���_���W
	float scale : TEXCOORD;
};

// �W�I���g���V�F�[�_�[����s�N�Z���V�F�[�_�[�֏o��
struct GSOutput
{
	float4 svpos : SV_POSITION; // �V�X�e���p���_���W
	float2 uv  :TEXCOORD; // uv�l
};