
cbuffer MatrixBuffer : register(cb0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer PositionBuffer
{
	static float3 g_positions[4] =
	{
		float3(-1, 1, 0),
		float3(-1, -1, 0),
		float3(1, 1, 0),
		float3(1, -1, 0)
	};
};

struct InputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct OutputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

[maxvertexcount(4)]
void main(point InputType input[1], inout TriangleStream<OutputType> triStream)
{
	OutputType output;
	
	// Change the position vector to be 4 units for proper matrix calculations.
    input[0].position.w = 1.0f;

	for (int i = 0; i < 4; i++)
	{
		float3 vposition = g_positions[i];
		//vposition *= 2;
		vposition = mul(vposition, (float3x3) worldMatrix) + input[0].position;
		output.position = mul(float4(vposition, 1.0), viewMatrix);
		output.position = mul(output.position, projectionMatrix);

		output.tex = input[0].tex;
		output.normal = input[0].normal;
		triStream.Append(output);
	}

	triStream.RestartStrip();
}