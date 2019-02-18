#version 400

layout (location = 0) in vec3 vertexPosition;
 
uniform mat4 view;	// View matrix
uniform mat4 proj;	// Projection matrix (perspective)
 
out vec3 direction;	// Direction we're going to sample the cubemap with
 
void main()
{
    direction = vertexPosition;	// This will be interpolated for us
	gl_Position = proj * view * vec4(vertexPosition, 1.0);
}