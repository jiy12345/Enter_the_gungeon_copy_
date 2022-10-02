struct VS_in
{
	float3 p : POSITION;
	float4 color : COLOR;
	float2 tex : TEXTURE;
};
struct VS_out
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};
VS_out VS(VS_in input) 
{
	VS_out output = (VS_out)0;

	output.p = float4(input.p,1.0f);
	output.c = input.color;
	output.t = input.tex;
	return output;
}

SamplerState MeshTextureSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};
Texture2D    g_txTex : register(t0);

struct PS_input
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};
float4 PS(PS_input input) : SV_Target
{
	float4 vColor = g_txTex.Sample(MeshTextureSampler, input.t);
	return vColor;
}