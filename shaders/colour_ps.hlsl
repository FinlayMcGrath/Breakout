// Colour pixel/fragment shader
// Basic fragment shader outputting a colour


struct InputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float4 colour : TEXCOORD1;
};


float4 main(InputType input) : SV_TARGET
{
	float4 colour = float4(input.colour);
	return colour;
}