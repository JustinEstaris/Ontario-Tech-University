#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexCoord;

out VertexData
{
	vec3 normal;
	vec3 worldPos;
	vec3 eyePos;
	vec2 texcoord;
}	outData;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 norm;

uniform vec3 cameraPos;

void main()
{
	outData.worldPos	= vec3(model * vec4(vertexPosition, 1.0f));
	outData.eyePos		= cameraPos;
    outData.normal		= normalize(vec3(norm * vec4(vertexNormal, 1.0f)));
	outData.texcoord	= vertexTexCoord;

	outData.texcoord.x  = 1.0f - outData.texcoord.x;

    gl_Position = proj * view * model * vec4(vertexPosition, 1.0f);

}