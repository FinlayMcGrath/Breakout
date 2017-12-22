#define numLights 4

cbuffer MatrixBuffer : register(cb0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
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

cbuffer CameraBuffer : register(cb2)
{
	float3 cameraPosition;
	float padding;
};

struct InputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct OutputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
	float4 viewPosition : TEXCOORD1;
	float3 lightPos1 : TEXCOORD2;
	float3 lightPos2 : TEXCOORD3;
	float3 lightPos3 : TEXCOORD4;
	float3 lightPos4 : TEXCOORD5;
	float3 viewDirection1 : TEXCOORD6;
	float3 viewDirection2 : TEXCOORD7;
	float3 viewDirection3 : TEXCOORD8;
	float3 viewDirection4 : TEXCOORD9;
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

    // Store the position of the vertice as viewed by the camera in a separate variable.
    output.viewPosition = output.position;

    // Store the texture coordinates for the pixel shader.
    output.tex = input.tex;
    
    // Calculate the normal vector against the world matrix only.
    output.normal = mul(input.normal, (float3x3)worldMatrix);
	
    // Normalize the normal vector.
    output.normal = normalize(output.normal);

    // Calculate the position of the vertex in the world.
    worldPosition = mul(input.position, worldMatrix);
	
	//Light 1

	// Determine the light position based on the position of the light and the position of the vertex in the world.
	output.lightPos1 = lightPosition1.xyz - worldPosition.xyz;

	// Normalize the light position vector.
	output.lightPos1 = normalize(output.lightPos1);	
	
	// Determine the viewing direction based on the position of the camera and the position of the vertex in the world.
	output.viewDirection1 = cameraPosition.xyz - worldPosition.xyz;

	// Normalize the viewing direction vector.
	output.viewDirection1 = normalize(output.viewDirection1);

	//Light 2

	// Determine the light position based on the position of the light and the position of the vertex in the world.
	output.lightPos2 = lightPosition2.xyz - worldPosition.xyz;

	// Normalize the light position vector.
	output.lightPos2 = normalize(output.lightPos2);	
	
	// Determine the viewing direction based on the position of the camera and the position of the vertex in the world.
	output.viewDirection2 = cameraPosition.xyz - worldPosition.xyz;

	// Normalize the viewing direction vector.
	output.viewDirection2 = normalize(output.viewDirection2);

	//Light 3

	// Determine the light position based on the position of the light and the position of the vertex in the world.
	output.lightPos3 = lightPosition3.xyz - worldPosition.xyz;

	// Normalize the light position vector.
	output.lightPos3 = normalize(output.lightPos3);	
	
	// Determine the viewing direction based on the position of the camera and the position of the vertex in the world.
	output.viewDirection3 = cameraPosition.xyz - worldPosition.xyz;

	// Normalize the viewing direction vector.
	output.viewDirection3 = normalize(output.viewDirection3);

	//Light 4

	// Determine the light position based on the position of the light and the position of the vertex in the world.
	output.lightPos4 = lightPosition4.xyz - worldPosition.xyz;

	// Normalize the light position vector.
	output.lightPos4 = normalize(output.lightPos4);	

	// Determine the viewing direction based on the position of the camera and the position of the vertex in the world.
	output.viewDirection4 = cameraPosition.xyz - worldPosition.xyz;

	// Normalize the viewing direction vector.
	output.viewDirection4 = normalize(output.viewDirection4);

    return output;
}