Texture2D depthMapTexture1 : register(t0);
Texture2D depthMapTexture2 : register(t1);
Texture2D depthMapTexture3 : register(t2);
Texture2D depthMapTexture4 : register(t3);

SamplerState SampleTypeClamp : register(s0);

#define numLights 4

struct InputType
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

float4 main(InputType input) : SV_TARGET
{
	float bias;
    float4 color;
    float2 projectTexCoord;
    float depthValue;
    float lightDepthValue;
    float lightIntensity;
	float3 lightPos[numLights];
	float4 lightViewPosition[numLights];
	Texture2D depthMapTexture[numLights];
	
	depthMapTexture[0] = depthMapTexture1;
	depthMapTexture[1] = depthMapTexture2;
	depthMapTexture[2] = depthMapTexture3;
	depthMapTexture[3] = depthMapTexture4;
	lightPos[0] = input.lightPos1;
	lightPos[1] = input.lightPos2;
	lightPos[2] = input.lightPos3;
	lightPos[3] = input.lightPos4;
	lightViewPosition[0] = input.lightViewPosition1;
	lightViewPosition[1] = input.lightViewPosition2;
	lightViewPosition[2] = input.lightViewPosition3;
	lightViewPosition[3] = input.lightViewPosition4;

    // Set the bias value for fixing the floating point precision issues.
    bias = 0.001f;

    // Set the default output color to be black (shadow).
    color = float4(0.0f, 0.0f, 0.0f, 1.0f);	

	for (int i = 0; i < numLights; i++)
	{
		// Calculate the projected texture coordinates.
		projectTexCoord.x = lightViewPosition[i].x / lightViewPosition[i].w / 2.0f + 0.5f;
		projectTexCoord.y = -lightViewPosition[i].y / lightViewPosition[i].w / 2.0f + 0.5f;

		// Determine if the projected coordinates are in the 0 to 1 range.  If so then this pixel is in the view of the light.
		if ((saturate(projectTexCoord.x) == projectTexCoord.x) && (saturate(projectTexCoord.y) == projectTexCoord.y))
		{
			// Sample the shadow map depth value from the depth texture using the sampler at the projected texture coordinate location.
			depthValue = depthMapTexture[i].Sample(SampleTypeClamp, projectTexCoord).r;

			// Calculate the depth of the light.
			lightDepthValue = lightViewPosition[i].z / lightViewPosition[i].w;

			// Subtract the bias from the lightDepthValue.
			lightDepthValue = lightDepthValue - bias;

			// Compare the depth of the shadow map value and the depth of the light to determine whether to shadow or to light this pixel.
			// If the light is in front of the object then light the pixel, if not then shadow this pixel since an object (occluder) is casting a shadow on it.
			if (lightDepthValue < depthValue)
			{
				// Calculate the amount of light on this pixel.
				lightIntensity = saturate(dot(input.normal, lightPos[i]));

				// If this pixel is illuminated then set it to pure white (non-shadow).
				if (lightIntensity > 0.0f)
				{
					color = float4(1.0f, 1.0f, 1.0f, 1.0f);
					break;
				}
			}
		}
	}

    return color;
}