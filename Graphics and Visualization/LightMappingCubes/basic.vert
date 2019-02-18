#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vUV;

uniform mat4 normalMat;
uniform mat4 modelMat;
uniform mat4 viewProjMat;

out vec3 normal;
out vec2 uv;
out vec3 worldPos;

void main()
{
	gl_Position = viewProjMat * modelMat * vec4(vPosition, 1.0);
	worldPos = (modelMat * vec4(vPosition, 1.0)).xyz;
	normal = (normalMat * vec4(vNormal, 1.0)).xyz;

	// This week, we added in a UV coordinate. This is a 2D coordinate, used to look up the
	// color of our pixel from a 2D texture.
	uv = vUV;
}