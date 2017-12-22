#define numLights 4

cbuffer MatrixBuffer : register(cb0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
	matrix lightViewMatrix1;
	matrix lightViewMatrix2;
	matrix lightViewMatrix3;
	matrix lightViewMatrix4;
	matrix lightProjectionMatrix1;
	matrix lightProjectionMatrix2;
	matrix lightProjectionMatrix3;
	matrix lightProjectionMatrix4;
};

cbuffer LightBuffer2 : register(cb1)
{
    //float3 lightPosition[numLights];
	float3 lightPosition1;
	float3 lightPosition2;
	float3 lightPosition3;
	float3 lightPosition4;
	float padding1;
	float padding2;
	float padding3;
	float padding4;
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
	float4 lightViewPosition1 : TEXCOORD1;
	float3 lightPos1 : TEXCOORD2;
	float4 lightViewPosition2 : TEXCOORD3;
	float3 lightPos2 : TEXCOORD4;
	float4 lightViewPosition3 : TEXCOORD5;
	float3 lightPos3 : TEXCOORD6;
	float4 lightViewPosition4 : TEXCOORD7;
	float3 lightPos4 : TEXCOORD8;
};

OutputType main(InputType input)
{
    OutputType output;
	float4 worldPosition;    

    // Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);    
	
    // Store the texture coordinates for the pixel shader.
    output.tex = input.tex;
    
    // Calculate the normal vector against the world matrix only.
    output.normal = mul(input.normal, (float3x3)worldMatrix);
	
    // Normalize the normal vector.
    output.normal = normalize(output.normal);

    // Calculate the position of the vertex in the world.
    worldPosition = mul(input.position, worldMatrix);

	//Light 1
    // Calculate the position of the vertice as viewed by the light source.
    output.lightViewPosition1 = mul(input.position, worldMatrix);
    output.lightViewPosition1 = mul(output.lightViewPosition1, lightViewMatrix1);
    output.lightViewPosition1 = mul(output.lightViewPosition1, lightProjectionMatrix1);

    // Determine the light position based on the position of the light and the position of the vertex in the world.
    output.lightPos1 = lightPosition1.xyz - worldPosition.xyz;

    // Normalize the light position vector.
    output.lightPos1 = normalize(output.lightPos1);

	//Light 2	
    // Calculate the position of the vertice as viewed by the light source.
    output.lightViewPosition2 = mul(input.position, worldMatrix);
    output.lightViewPosition2 = mul(output.lightViewPosition2, lightViewMatrix2);
    output.lightViewPosition2 = mul(output.lightViewPosition2, lightProjectionMatrix2);

    // Determine the light position based on the position of the light and the position of the vertex in the world.
    output.lightPos2 = lightPosition2.xyz - worldPosition.xyz;

    // Normalize the light position vector.
    output.lightPos2 = normalize(output.lightPos2);

	//Light 3
    // Calculate the position of the vertice as viewed by the light source.
    output.lightViewPosition3 = mul(input.position, worldMatrix);
    output.lightViewPosition3 = mul(output.lightViewPosition3, lightViewMatrix3);
    output.lightViewPosition3 = mul(output.lightViewPosition3, lightProjectionMatrix3);

    // Determine the light position based on the position of the light and the position of the vertex in the world.
    output.lightPos3 = lightPosition3.xyz - worldPosition.xyz;

    // Normalize the light position vector.
    output.lightPos3 = normalize(output.lightPos3);

	//Light 4
    // Calculate the position of the vertice as viewed by the light source.
    output.lightViewPosition4 = mul(input.position, worldMatrix);
    output.lightViewPosition4 = mul(output.lightViewPosition4, lightViewMatrix4);
    output.lightViewPosition4 = mul(output.lightViewPosition4, lightProjectionMatrix4);

    // Determine the light position based on the position of the light and the position of the vertex in the world.
    output.lightPos4 = lightPosition4.xyz - worldPosition.xyz;

    // Normalize the light position vector.
    output.lightPos4 = normalize(output.lightPos4);

    return output;
}