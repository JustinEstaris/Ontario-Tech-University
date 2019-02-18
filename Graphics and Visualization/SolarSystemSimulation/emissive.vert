#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 2) in vec2 vertexTexCoord;

out VertexData
{
	vec2 texcoord;
}	outData;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	outData.texcoord	= vertexTexCoord;

    gl_Position = proj * view * model * vec4(vertexPosition, 1.0f);

}