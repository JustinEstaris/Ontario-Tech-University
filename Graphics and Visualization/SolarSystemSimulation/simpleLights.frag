#version 400

out vec4 frag_colour;

in VertexData
{
	vec3 normal;
	vec3 worldPos;
	vec3 eyePos;
	vec2 texcoord;
}	inData;

uniform sampler2D diffuseTex;
uniform sampler2D specularTex; // It's already here

uniform float specPower;

vec3 sunPosition = vec3(0); // Sun is at the origin

void main()
{
	float luminance = 1.2f;
	vec3 light = normalize(sunPosition - inData.worldPos);
	vec3 normal = normalize(inData.normal);
	float NoL = max(0.0f, dot(normal, light));
	vec3 V = normalize(inData.worldPos - inData.eyePos);

	vec4 diffuseTexture = texture(diffuseTex, inData.texcoord);
	float specularTexture = texture(specularTex, inData.texcoord).r;

	// Do diffuse light
	vec3 diffuse = diffuseTexture.rgb * vec3(NoL) * luminance;
	
	// Do specular light
	vec3 R = normalize(reflect(-light, normal));
	float VoR = max(0.0f, dot(-V, R));
	vec3 specColor = vec3(1,1,1) * specularTexture;
	vec3 specular = specColor * pow(VoR, specularTexture * specPower) * (NoL > 0.0 ? 1.0 : 0.0);

	frag_colour.rgb = diffuse + specular;
	frag_colour.a = 1.0f;
}