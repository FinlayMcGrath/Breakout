// Light pixel shader
// Calculate ambient and diffuse lighting for a single light (also texturing)

#define numLights 2

Texture2D shaderTexture : register(t0);
SamplerState SampleType : register(s0);

cbuffer LightBuffer : register(cb0)
{
	float4 diffuseColour[numLights];
	float4 ambientColour[numLights];
	//float specularPower[numLights];
	//float4 specularColour[numLights];
	float4 position[numLights];
};

struct InputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 position3D : TEXCOORD2;
	float3 viewDirection : TEXCOORD1;
};

float4 main(InputType input) : SV_TARGET
{
	float4 textureColour;
	float3 lightDir;
	float lightIntensity;
	float4 colour = { 0.0f, 0.0f, 0.0f, 0.0f };
	float3 reflection;
	float4 specular;
	float4 finalSpec = { 0.0f, 0.0f, 0.0f, 0.0f };

	// Sample the pixel color from the texture using the sampler at this texture 	coordinate location.
	textureColour = shaderTexture.Sample(SampleType, input.tex);

	for (int i = 0; i < numLights; i++)
	{
		// Set the default output color to the ambient light value for all pixels.
		colour = ambientColour[i];

		// Invert the light direction for calculations.
		lightDir = normalize(input.position3D - position[i]);

		// Calculate the amount of light on this pixel.
		lightIntensity = saturate(dot(input.normal, -lightDir));

		if (lightIntensity > 0.0f)
		{
			// Determine the final diffuse color based on the diffuse color and the amount 	of light intensity.
			colour += (diffuseColour[i] * lightIntensity);

			// Saturate the ambient and diffuse color.
			colour = saturate(colour);

			// Calculate reflection vector based on the light intensity, normal vector and light direction
			//reflection = reflect(direction[i], input.normal);

			// Determine the amount of specular light based on the reflection vector, viewing direction, and specular power.
			//specular = pow(saturate(dot(reflection, input.viewDirection)), specularPower[i]);

			//sum up specular light
			//finalSpec = specularColour[i] * specular;
		}
	}

	// Multiply the texture pixel and the final diffuse colour
	colour = colour * textureColour;

	// Add the specular component last to the output colour.
	//colour = saturate(colour + finalSpec);
	colour = saturate(colour);
	return colour;
}
