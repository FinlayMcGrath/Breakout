Texture2D shaderTexture : register(t0);
Texture2D shadowMapTexture : register(t1);

SamplerState SampleTypeWrap  : register(s0);
SamplerState SampleTypeClamp : register(s1);

#define numLights 4

cbuffer LightBuffer : register(cb0)
{
	float4 ambientColor;
	float4 diffuseColor1;
	float4 diffuseColor2;
	float4 diffuseColor3;
	float4 diffuseColor4;
};

struct InputType
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

float4 main(InputType input) : SV_TARGET
{
	float4 color = {0.0f, 0.0f, 0.0f, 0.0f};
	float lightIntensity = 1;
	float4 textureColor;
	float2 projectTexCoord;
	float shadowValue;
	float3 lightPos[numLights];
	float4 diffuseColor[numLights];
	float3 viewDirection[numLights];
	float3 reflection;
	float4 specular;
	float4 finalSpec = { 0.0f, 0.0f, 0.0f, 0.0f };
	float4 specularColour = {1.0f, 1.0f, 1.0f, 1.0f};
	float3 direction;
	float specularPower = 5.0f;

	lightPos[0] = input.lightPos1;
	lightPos[1] = input.lightPos2;
	lightPos[2] = input.lightPos3;
	lightPos[3] = input.lightPos4;
	diffuseColor[0] = diffuseColor1;
	diffuseColor[1] = diffuseColor2;
	diffuseColor[2] = diffuseColor3;
	diffuseColor[3] = diffuseColor4;
	viewDirection[0] = input.viewDirection1;
	viewDirection[1] = input.viewDirection2;
	viewDirection[2] = input.viewDirection3;
	viewDirection[3] = input.viewDirection4;

	// Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;
	
	// Set the default output color to the ambient light value for all pixels.
	color = ambientColor;
	for (int i = 0; i < numLights; i++)
	{
		// Calculate the amount of light on this pixel.
		lightIntensity = saturate(dot(input.normal, lightPos[i]));
		if (lightIntensity > 0.0f)
		{
			// Determine the light color based on the diffuse color and the amount of light intensity.
			color += (diffuseColor[i] * lightIntensity); 

			// Saturate the light color.
			color = saturate(color);

			// Calculate light direction based upon position and look at
			direction = lightPos[i] - viewDirection[i];

			// Calculate reflection vector based on the light intensity, normal vector and light direction
			reflection = reflect(direction, input.normal);

			// Determine the amount of specular light based on the reflection vector, viewing direction, and specular power.
			specular = pow(saturate(dot(reflection, viewDirection[i]) + 0.5), specularPower);

			//sum up specular light
			finalSpec = diffuseColor[i] * specular;
		}
	}			

	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColor = shaderTexture.Sample(SampleTypeWrap, input.tex);

	// Combine the light and texture color.
	color = color * textureColor;

	// Calculate the projected texture coordinates to be used with the shadow texture.
	projectTexCoord.x = input.viewPosition.x / input.viewPosition.w / 2.0f + 0.5f;
	projectTexCoord.y = -input.viewPosition.y / input.viewPosition.w / 2.0f + 0.5f;

	// Sample the shadow value from the shadow texture using the sampler at the projected texture coordinate location.
	shadowValue = shadowMapTexture.Sample(SampleTypeClamp, projectTexCoord).r;

	// Combine the shadows with the final color.
	color = color * shadowValue;

	//reduce specular so it isn't so bright
	finalSpec = finalSpec / numLights;

	// Add the specular component last to the output colour.
	color = saturate(color + finalSpec);

    return color;
}