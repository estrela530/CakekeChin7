#include "ParticleSH.hlsli"

//四角形の頂点数
static const uint vnum = 4;

//センターからのオフセット
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


//点の入力から、四角形を入力
[maxvertexcount(vnum)]
void main(
	point VSOutput input[1] : SV_POSITION,
	inout TriangleStream< GSOutput > output
)
{
	GSOutput element;

	float4 offset = float4(0, 0, 0, 0);

	for (uint i = 0; i < vnum; i++) {
		// 中心からのオフセットをスケーリング
		offset = offset_array[i] * input[0].scale;
		// 中心からのオフセットをビルボード回転（モデル座標）
		offset = mul(matBillboard, offset);
		// オフセット分ずらす（ワールド座標）
		element.svpos = input[0].pos + offset;
		// ビュープロジェクション変換
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
//	//4点分まわす
//	for (uint i = 0; i < vnum; i++)
//	{
//		//ワールド座標ベースで、ずらす
//		element.svpos = input[0].pos + offset_array[i];
//		//ビュー、射影変換
//		element.svpos = mul(mat, element.svpos);
//		//element.uv = float2(0.5f, 0.5f);
//		element.uv = uv_array[i];
//		output.Append(element);
//	}
//}

//三角形の入力から、点を1つ入力するサンプル
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
//	//点ストリーム
//	inout TriangleStream<GSOutput>output)
//{
//	for (uint i = 0; i < 3; i++)
//	{
//		GSOutput element;
//		element.svpos = input[i].svpos;//頂点座標をコピー
//		element.normal = input[i].normal;//法線をコピー
//		element.uv = input[i].uv;//UVをコピー
//		//頂点を1つ入力(出力リストに追加)
//		output.Append(element);
//	}
//}
