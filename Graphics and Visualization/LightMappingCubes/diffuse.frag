#version 330 core

uniform vec4 lightPosDir;
uniform vec4 lightColor;
uniform sampler2D diffuseSampler;
uniform sampler2D specSampler;

struct Light
{
	int type;
	vec3 direction;
	vec3 position;
	vec3 color;
	float intensity;
} light;

in vec3 normal;
in vec2 uv;
in vec3 worldPos;
out vec4 outColor;
uniform int lightType;

void main()
{
	// Create the light source
	light.type = int(lightPosDir.w); 
	light.color = lightColor.rgb;
	light.intensity = lightColor.a;
	if (lightType == 0)	// If it's a directional light, set the direction
	{
		light.position = vec3(0);
		light.direction = -normalize(lightPosDir.xyz);
		light.intensity = light.intensity / 150.0f; 
	}
	else if (lightType == 1 || lightType == 2)	// If it's a point light, set the position
	{
		light.position = lightPosDir.xyz;
		light.direction = normalize(worldPos - light.position);
	}
	
	// Use light source
	vec3 ambient = vec3(0.1f);
	vec3 diffuse = vec3(0.0f);
	vec3 specular = vec3(0.1f);	// Specular is going to stay black for today

	float specSamplerFl = texture(specSampler, uv).r;
	vec3 specColor = vec3(1,1,1) * specSamplerFl;

	vec3 reflection = normalize(reflect(-light.position, normal));
	float VdotR = max(0.0f, dot(-worldPos, reflection));

	if (lightType == 0)
	{
		float NdotL = dot(normal, -1.0f * light.direction);

		if (NdotL > 0.0f)
		{
			diffuse = NdotL * light.color * light.intensity;
			specular = specColor * pow(VdotR, specSamplerFl);
		}
	}
	else if (lightType == 1)
	{
		float attenuation = 1.0f / pow(length(worldPos - light.position), 2.0f);
		
		float NdotL = dot(normal, -1.0f * light.direction);
		
		if (NdotL > 0.0f)
		{
			diffuse = NdotL * light.color * light.intensity * attenuation;
			specular = specColor * pow(VdotR, specSamplerFl) * attenuation;
		}
	}
	else if(lightType == 2){
		float attenuation = 1.0f / pow(length(worldPos - light.position), 2.0f);
		
		float NdotL = dot(normal, -1.0f * light.direction);

		float fovInDegrees = 45.0f;
		float fovInRadians = fovInDegrees * (180.0f / 3.1415f);

		if (NdotL > cos(fovInRadians)) // 45deg
		{
			diffuse = NdotL * light.color * light.intensity * attenuation;
			specular = specColor * pow(VdotR, specSamplerFl) * attenuation;
		}
	}

	vec3 shapeTexture = texture(diffuseSampler, uv).rgb;

	outColor.rgb = shapeTexture * (ambient + diffuse + specular);
	outColor.a = 1.0f;
}