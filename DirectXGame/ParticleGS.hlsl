#include "ParticleSH.hlsli"

//�l�p�`�̒��_��
static const uint vnum = 4;

//�Z���^�[����̃I�t�Z�b�g
static const float4 offset_array[vnum] =
{
	/*float4(-0.5f,-0.5f,0,0),
	float4(-0.5f,+0.5f,0,0),
	float4(+0.5f,-0.5f,0,0),
	float4(+0.5f,+0.5f,0,0)*/

	float4(-0.25f,-0.25f,0,0),
	float4(-0.25f,+0.25f,0,0),
	float4(+0.25f,-0.25f,0,0),
	float4(+0.25f,+0.25f,0,0)
};

static const float2 uv_array[vnum] =
{
	float2(0,1),
	float2(0,0),
	float2(1,1),
	float2(1,0)
};


//�_�̓��͂���A�l�p�`�����
[maxvertexcount(vnum)]
void main(
	point VSOutput input[1] : SV_POSITION,
	inout TriangleStream< GSOutput > output
)
{
	GSOutput element;

	float4 offset = float4(0, 0, 0, 0);

	for (uint i = 0; i < vnum; i++) {
		// ���S����̃I�t�Z�b�g���X�P�[�����O
		offset = offset_array[i] * input[0].scale;
		// ���S����̃I�t�Z�b�g���r���{�[�h��]�i���f�����W�j
		offset = mul(matBillboard, offset);
		// �I�t�Z�b�g�����炷�i���[���h���W�j
		element.svpos = input[0].pos + offset;
		// �r���[�v���W�F�N�V�����ϊ�
		element.svpos = mul(mat, element.svpos);
		element.uv = uv_array[i];
		output.Append(element);
	}
}

//void main(
//	point VSOutput input[1] : SV_POSITION,
//	inout TriangleStream< GSOutput > output
//)
//{
//	GSOutput element;
//	//4�_���܂킷
//	for (uint i = 0; i < vnum; i++)
//	{
//		//���[���h���W�x�[�X�ŁA���炷
//		element.svpos = input[0].pos + offset_array[i];
//		//�r���[�A�ˉe�ϊ�
//		element.svpos = mul(mat, element.svpos);
//		//element.uv = float2(0.5f, 0.5f);
//		element.uv = uv_array[i];
//		output.Append(element);
//	}
//}

//�O�p�`�̓��͂���A�_��1���͂���T���v��
//[maxvertexcount(3)]

//void main(
//	triangle float4 input[3] : SV_POSITION, 
//	inout TriangleStream< GSOutput > output
//)
//{
//	for (uint i = 0; i < 3; i++)
//	{
//		GSOutput element;
//		element.pos = input[i];
//		output.Append(element);
//	}
//}

//void main(triangle VSOutput input[3]:SV_POSITION,
//	//�_�X�g���[��
//	inout TriangleStream<GSOutput>output)
//{
//	for (uint i = 0; i < 3; i++)
//	{
//		GSOutput element;
//		element.svpos = input[i].svpos;//���_���W���R�s�[
//		element.normal = input[i].normal;//�@�����R�s�[
//		element.uv = input[i].uv;//UV���R�s�[
//		//���_��1����(�o�̓��X�g�ɒǉ�)
//		output.Append(element);
//	}
//}
