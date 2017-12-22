// Light pixel shader
// Calculate ambient and diffuse lighting for a single light (also texturing)

Texture2D shaderTexture : register(t0);
SamplerState SampleType : register(s0);

cbuffer LightBuffer : register(cb0)
{
    float4 diffuseColour;
	float4 ambientColour;
	float3 direction;
	float padding;
};

struct InputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

float4 main(InputType input) : SV_TARGET
{
	float4 textureColour;
	float3 lightDir;
	float lightIntensity;
	float4 colour;

	// Sample the pixel colour from the texture.
	textureColour = shaderTexture.Sample(SampleType, input.tex);

	// Set the default output colour to the ambient light value for all pixels.
	colour = ambientColour;

	// Calculate the amount of light on this pixel.
	lightIntensity = saturate(dot(input.normal, -direction));

	if (lightIntensity > 0.0f)
	{
		colour += (diffuseColour * lightIntensity);
	}

	colour = colour * textureColour;
	
	return colour;
}


