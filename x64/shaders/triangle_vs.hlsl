cbuffer MatrixBuffer : register(cb0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

struct InputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

InputType main(InputType input)
{
    // Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices.
	input.position = mul(input.position, worldMatrix);
    //input.position = mul(input.position, viewMatrix);
    input.position = mul(input.position, projectionMatrix);

	// Calculate the normal vector against the world matrix only.
    input.normal = mul(input.normal, (float3x3)worldMatrix);
	
    // Normalize the normal vector.
    input.normal = normalize(input.normal);
    
    return input;
}