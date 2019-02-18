#version 400

out vec4 frag_colour;

in VertexData
{
	vec2 texcoord;
}	inData;

uniform sampler2D emissiveTex;

void main()
{
	frag_colour = texture(emissiveTex, inData.texcoord) * 1.5f;
}